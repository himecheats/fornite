﻿	#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS
#define ALLOC_CONS 0
#define StrA
#define StrW

#define DebugConsole 1

#include "Icons.h"

#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <emmintrin.h>
#include "winternl.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "Ofssets.h"
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <thread>

#include "main.h"


#include "ImGUI/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "sdk/New.h"
#include "sdk/utils.h"
#include "sdk/safe.h"
#include "sdk_new/math.h"
#include "vars/vars.h"
#include "sdk/sdk.h"
#include "NGui.h"
#include "crt.h"

#include "Minhook/include/MinHook.h"
#include "Hook.h"

#include "cheat_funcs/Aim.h"
#include "cheat_funcs/Misc.h"
#include "cheat_funcs/Esp.h"

#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGui/imgui_internal.h"
#include <d3d11.h>
#include "imgui_elements.h"


#include "Cfg/SimpleIni.h"
#include "Config.h"
#include "Init.h"
#include "Menu.h"
#pragma comment(lib, "urlmon.lib")

#include <d3d11.h>
#include <D3Dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")

HMODULE g_hModule;
HWND hWnd = nullptr;
PDWORD64 origResize = nullptr;
PDWORD64 origPresent = nullptr;
ID3D11Device* pD11Device = nullptr;
ID3D11Device* g_pd3dDevice = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
IDXGISwapChain* dxSwapChain = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11DeviceContext* pD11DeviceContext = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
ID3D11RenderTargetView* pD11RenderTargetView = nullptr;

typedef HRESULT(__fastcall* DX11PresentFn) (IDXGISwapChain* pSwapChain, UINT syncintreval, UINT flags);
DX11PresentFn oPresent = nullptr;

typedef HRESULT(__stdcall* DX11ResizeFn)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
DX11ResizeFn oResize = nullptr;


#include "detours.h"
#if defined _M_X64
#pragma comment(lib, "detours.X64/detours.lib")
#elif defined _M_IX86
#pragma comment(lib, "detours.X86/detours.lib")
#endif



#pragma warning( disable : 4244 )


typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* D3D11ResizeBuffersHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef void(__stdcall* D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
typedef void(__stdcall* D3D11DrawHook) (ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation);
typedef void(__stdcall* D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall* D3D11DrawIndexedInstancedHook) (ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall* D3D11CreateQueryHook) (ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);


D3D11PresentHook phookD3D11Present = NULL;
D3D11ResizeBuffersHook phookD3D11ResizeBuffers = NULL;
D3D11PSSetShaderResourcesHook phookD3D11PSSetShaderResources = NULL;
D3D11DrawHook phookD3D11Draw = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11DrawIndexedInstancedHook phookD3D11DrawIndexedInstanced = NULL;
D3D11CreateQueryHook phookD3D11CreateQuery = NULL;

ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;

HWND window = nullptr;

void InitImGui()
{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();


		ImFontConfig font_config;
		font_config.OversampleH = 1;
		font_config.OversampleV = 1;
		font_config.PixelSnapH = true;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF,
			0x0400, 0x044F,
			0,
		};

		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 13.f);


		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		style->WindowPadding = ImVec2(2.f, 8.f);
		style->FramePadding = ImVec2(12.f, 3.f);
		style->ItemSpacing = ImVec2(9.f, 6.f);
		style->ItemInnerSpacing = ImVec2(7.f, 4.f);
		style->TouchExtraPadding = ImVec2(0.f, 0.f);
		style->IndentSpacing = 17.f;
		style->ScrollbarSize = 12.f;
		style->GrabMinSize = 11.f;
		style->WindowBorderSize = 0.f;
		style->ChildBorderSize = 0.f;
		style->PopupBorderSize = 1.f;
		style->FrameBorderSize = 0.f;
		style->TabBorderSize = 0.f;
		style->WindowRounding = 14.f;
		style->ChildRounding = 0.f;
		style->FrameRounding = 0.f;
		style->PopupRounding = 0.f;
		style->ScrollbarRounding = 9.f;
		style->GrabRounding = 0.f;
		style->TabRounding = 4.f;
		style->WindowTitleAlign = ImVec2(1.f, 1.f);
		style->WindowMenuButtonPosition = 1.f;
		style->ColorButtonPosition = 1.f;
		style->ButtonTextAlign = ImVec2(1.f, 1.f);
		style->SelectableTextAlign = ImVec2(0.f, 0.f);
		style->DisplaySafeAreaPadding = ImVec2(3.f, 3.f);


		colors[ImGuiCol_Text] = ImVec4(1.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60, 0.60, 0.60, 1.00);
		colors[ImGuiCol_WindowBg] = ImVec4(0.11, 0.10, 0.11, 1.00);
		colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_PopupBg] = ImVec4(0.06, 0.06, 0.06, 0.94);
		colors[ImGuiCol_Border] = ImVec4(0.86, 0.86, 0.86, 1.00);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_FrameBg] = ImVec4(0.21, 0.20, 0.21, 1.00);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06, 0.06, 0.06, 0.94);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00, 0.46, 0.65, 0.44);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00, 0.46, 0.65, 0.74);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_ComboBg] = ImVec4(0.15, 0.14, 0.15, 1.00);
		colors[ImGuiCol_CheckMark] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_Button] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.00, 0.49, 1.00, 0.59);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.00, 0.49, 1.00, 0.59);
		colors[ImGuiCol_Header] = ImVec4(0.00, 0.46, 0.65, 1.00);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.06, 0.06, 0.06, 0.94);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.06, 0.06, 0.06, 0.94);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00, 1.00, 1.00, 0.30);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00, 1.00, 1.00, 0.60);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00, 1.00, 1.00, 0.90);
		colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
		colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
		colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
		colors[ImGuiCol_CloseButton] = ImVec4(1.00, 0.10, 0.24, 1.00);
		colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00, 0.10, 0.24, 1.00);
		colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00, 0.10, 0.24, 1.00);
		colors[ImGuiCol_PlotLines] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.00, 0.00, 0.00, 1.00);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
}


ID3D11RenderTargetView* mainRenderTargetView;
WNDPROC oWndProc;
void unhook();
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    return true;
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}
		else
		return oPresent(pSwapChain, SyncInterval, Flags);
	}
	//create rendertarget
	if (GetAsyncKeyState(Vars::Global::MenuKey) & 1)
	{
		show = !show;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}

	if (GetAsyncKeyState(Vars::Global::PanicKey) & 1)
	{
		Vars::Global::Panic = true;
		//unhook();
	}
	if (!Vars::Global::Panic)
	{
		if (GUI::Render.NewFrame(pSwapChain))
		{
			InitCheat();
		}
		GUI::Render.EndFrame();

		//menu
		if (show)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			MenuSteep();
			ImGui::End();
			ImGui::Render();
			pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}
	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}
void unhook() 
{
	show = false;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
	DetourTransactionCommit();
}

//==========================================================================================================================


int MultisampleCount = 1;
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall InitHooks(LPVOID)
{
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle(L"dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);

	IDXGISwapChain* pSwapChain;
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = MultisampleCount;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	UINT createFlags = 0;
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBox(hWnd, L"Failed to create directX device and swapchain!", L"Error", MB_ICONERROR);
		return NULL;
	}
	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];
	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];
	phookD3D11Present = (D3D11PresentHook)(DWORD_PTR*)pSwapChainVtable[8];
	phookD3D11ResizeBuffers = (D3D11ResizeBuffersHook)(DWORD_PTR*)pSwapChainVtable[13];
	phookD3D11PSSetShaderResources = (D3D11PSSetShaderResourcesHook)(DWORD_PTR*)pContextVTable[8];
	phookD3D11Draw = (D3D11DrawHook)(DWORD_PTR*)pContextVTable[13];
	phookD3D11DrawIndexed = (D3D11DrawIndexedHook)(DWORD_PTR*)pContextVTable[12];
	phookD3D11DrawIndexedInstanced = (D3D11DrawIndexedInstancedHook)(DWORD_PTR*)pContextVTable[20];
	//phookD3D11CreateQuery = (D3D11CreateQueryHook)(DWORD_PTR*)pDeviceVTable[24];
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
	DetourTransactionCommit();
	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	while (true)
	{
		Sleep(10);
	}

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
	return NULL;
}

BOOL __stdcall DllMain(HINSTANCE hModule,  DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		DisableThreadLibraryCalls(hModule);
		
#ifdef DebugConsole
		//AllocConsole();
		freopen(StrA("CONIN$"), "r", stdin);
		freopen(StrA("CONOUT$"), "w", stderr);
		freopen(StrA("CONOUT$"), "w", stdout);
#endif
		GetModuleFileName(hModule, (LPWSTR)dlldir, 512);
		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
		CreateThread(NULL, 0, InitHooks, NULL, 0, NULL);
		InitHook();
		break;

	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
		DetourTransactionCommit();
		break;
	}
	return TRUE;
}
