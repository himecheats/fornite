#pragma once
#include <D2D1.h>
#include <dwrite_1.h>
#include <D3D11.h>
#include "Vector.h"
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")

class RenderClass
{
private:
	//render context
	ID2D1Factory* Interface = nullptr;
	ID2D1RenderTarget* Canvas = nullptr;
	IDWriteFactory1* TextEngine = nullptr;
	IDWriteTextFormat* TextFormat = nullptr;
	ID2D1SolidColorBrush* SolidColor = nullptr;

	//fast get wstring length
	__forceinline UINT wcslen(const wchar_t* Str)
	{
		const wchar_t* TempStr = Str;
		for (; *TempStr; ++TempStr);
		return (UINT)(TempStr - Str);
	}

	__declspec(noinline) bool InitRender(IDXGISwapChain* SwapChain)
	{
		//prep d2d render & text engine
		static bool initialized;
		if (!initialized)
		{
			initialized = true; D2D1_FACTORY_OPTIONS CreateOpt = { D2D1_DEBUG_LEVEL_NONE };
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(TextEngine), (IUnknown**)&TextEngine);
			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &CreateOpt, (void**)&Interface);
			TextEngine->CreateTextFormat(L"Bold Script", NULL, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED, 12.f, L"", &TextFormat);
			if (!Interface || !TextEngine || !TextFormat) return false;
		}
		//get window flags var
		ID3D11Device* d3d_device;
		if (SwapChain->GetDevice(IID_PPV_ARGS(&d3d_device))) return false;
		WORD flagsOffset = *(WORD*)((*(DWORD64**)d3d_device)[38] + 2); //x64
		int& flags = *(INT*)((DWORD64)d3d_device + flagsOffset);
		d3d_device->Release();
		//get d3d backbuffer
		IDXGISurface* d3d_bbuf;
		if (SwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d_bbuf)))
			return false;
		//create canvas & cleanup
		D2D1_RENDER_TARGET_PROPERTIES d2d_prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		flags |= 0x20; HRESULT canvas_state = Interface->CreateDxgiSurfaceRenderTarget(d3d_bbuf, d2d_prop, &Canvas); flags &= ~0x20; d3d_bbuf->Release(); if (canvas_state) return false;
		if (!SolidColor) Canvas->CreateSolidColorBrush({}, &SolidColor); return true;
	}

public:
	//canvas mgr
	__forceinline bool NewFrame(IDXGISwapChain* SwapChain)
	{
		//need prep d2d canvas
		if (!Canvas && !InitRender(SwapChain))
			return false;

		//draw start
		Canvas->BeginDraw();
		return true;
	}

	__forceinline Vector2 CanvasSize()
	{
		D2D1_SIZE_F Size = Canvas->GetSize();
		return Vector2{ Size.width, Size.height };
	}

	__forceinline void ResetCanvas() {
		if (Canvas)
		{
			Canvas->Release();
			Canvas = nullptr;
		}
	}

	__forceinline void EndFrame()
	{
		HRESULT state = Canvas->EndDraw();
		if (state == D2DERR_RECREATE_TARGET)
			ResetCanvas();
	}

#pragma region Line

	__forceinline void Line(const Vector2& Start, const Vector2& End, const D2D1::ColorF& Clr, float Thick = 1.5f)
	{
		SolidColor->SetColor(Clr); Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}

#pragma endregion 

#pragma region Circle

	__forceinline void Ellipse(const Vector2& Start, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f)
	{
		SolidColor->SetColor(Clr);
		Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);
	}

	__forceinline void FillEllipse(const Vector2& Start, const D2D1::ColorF& Clr, float Rad)
	{
		SolidColor->SetColor(Clr);
		Canvas->FillEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor);
	}

#pragma endregion 

#pragma region Rectangle

	__forceinline void Rectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Thick = 1.5f)
	{
		SolidColor->SetColor(Clr);
		Canvas->DrawRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor, Thick);
	}

	__forceinline void FillRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr)
	{
		SolidColor->SetColor(Clr);
		Canvas->FillRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor);
	}

	__forceinline void RoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f)
	{
		SolidColor->SetColor(Clr);
		Canvas->DrawRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, Rad, Rad }, SolidColor, Thick);
	}

	__forceinline void FillRoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad)
	{
		SolidColor->SetColor(Clr);
		Canvas->FillRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y}, Rad, Rad }, SolidColor);
	}

#pragma endregion 

	Vector2 RenderString(const Vector2& pos, const wchar_t* text, bool center = false, const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::White), bool Shadow = true)
	{
		Vector2 Result;
		if (center)
		{
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 400.f, 200.f, &TextLayout);
			DWRITE_TEXT_METRICS TextInfo;
			TextLayout->GetMetrics(&TextInfo);
			Vector2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };

			if (Shadow)
			{
				const auto x = pos.x - TextSize.x;
				const auto y = pos.y - TextSize.y;
				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}

			SolidColor->SetColor(color);

			Canvas->DrawTextLayout({ pos.x - TextSize.x, pos.y - TextSize.y }, TextLayout, SolidColor);
			TextLayout->Release();
			Result = TextSize;
		}
		else
		{
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 400.f, 200.f, &TextLayout);
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

			if (Shadow)
			{
				const auto x = pos.x;
				const auto y = pos.y;

				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}



			/*SolidColor->SetColor(color);
			Canvas->DrawTextA(text, wcslen(text), TextFormat, { pos.x, pos.y, FLT_MAX, FLT_MAX }, SolidColor);*/

			TextLayout->Release();
			Result = { 0,0 };
		}

		return Result;
	}
}; #pragma once
