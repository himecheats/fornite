#include "cheat_funcs/Entity.h"
void InitCheat()
{
	float Y = GetSystemMetrics(SM_CYSCREEN);

	Vector2 kek = GUI::Render.CanvasSize();
	Vars::Global::ScreenWidth = kek.x;
	Vars::Global::ScreenHigh = kek.y;


	if (Vars::AimBot::BodyAim) Vars::Global::BoneToAim = 21;
	else Vars::Global::BoneToAim = 46;

	if (Vars::AimBot::DrawFov)
		DrawFOV();

	if (Vars::Misc::Crosshair1)
		Crosshair();

	if (Vars::Misc::CrosshairCustom)
		CrosshairCustom();

	if (Vars::Misc::Crosshair2)
		CircleCrosshair();

	if (Vars::Radar::Enable)
		RenderRadarBackground(Vars::Radar::Pos_X, Vars::Radar::Pos_Y, Vars::Radar::Radar_Size);

	/*if (Vars::Visuals::Preview::On)
		EspPreview();
    */

	if (Vars::AimBot::DrawPSilentFov)
		DrawPSilentFov();

	if (GetAsyncKeyState(Vars::AimBot::silentclearkey) && Vars::AimBot::SilentClear)
		TargetSilentPlayer = NULL;

	if (GetAsyncKeyState(Vars::AimBot::Psilentclearkey) && Vars::AimBot::PSilentClear)
		TargetPSilentPlayer = NULL;

	if (PlayerTarget != NULL && Vars::Visuals::TargetTracers) // && Player->GetSteamID() < 1000000000
	{
		auto* TargetPlayer = reinterpret_cast<BasePlayer*>(PlayerTarget);
		Vector2 ScreenPos;
		const Vector2 ScreenSize = GUI::Render.CanvasSize();
		Vars::Global::ScreenWidth = ScreenSize.x;
		Vars::Global::ScreenHigh = ScreenSize.y;
		if (Vars::Visuals::TargetTracers)
		{
			if (!(TargetPlayer->GetBoneByID(head).x == 0 && TargetPlayer->GetBoneByID(head).y == 0 && TargetPlayer->GetBoneByID(head).z == 0)) {
				if (LocalPlayer.WorldToScreen(TargetPlayer->GetBoneByID(head), ScreenPos))
					GUI::Render.Line({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, ScreenPos, D2D1::ColorF::Red);
			}
		}
	}

	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	const int MenuHeight = 120;
	switch (cases)
	{
	case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}

	if (Vars::Watermark::waterm)
	{
		GUI::Render.FillRoundedRectangle({ (Vars::Watermark::PosX), (Vars::Watermark::PosY) }, { MenuHeight,  30 }, D2D1::ColorF(0, 0, 0, 0.8), 4);
		GUI::Render.String({ (Vars::Watermark::PosX), (Vars::Watermark::PosY) }, (L"UdefParasha"), D2D1::ColorF::White);
	}

	if (Vars::Watermark::watermL)
	{
		GUI::Render.FillRoundedRectangle({ (Vars::Watermark::PosX), (Vars::Watermark::PosY) }, { MenuHeight,  30 }, D2D1::ColorF(255, 255, 255, 0.8), 4);
		GUI::Render.String({ (Vars::Watermark::PosX), (Vars::Watermark::PosY) }, (L"UdefParasha"), D2D1::ColorF::Black);
	}
	auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(Vars::Storage::closestPlayer);
	wchar_t name[64];
	if (Vars::Other::InfoTopLeft)
	{
		if (Vars::Storage::closestPlayer != NULL)
		{
			float curhealth = (int)TargetPlayerA->GetHealth();
			if (!TargetPlayerA->IsNpc())
			{
				float maxheal = 100.f;
				if ((int)TargetPlayerA->GetHealth() <= 33)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxheal), 15 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
				}
				if ((int)TargetPlayerA->GetHealth() >= 34 && (int)TargetPlayerA->GetHealth() <= 66)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxheal), 15 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
				}
				if ((int)TargetPlayerA->GetHealth() >= 67)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxheal), 15 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
				}
			}
			else
			{
				float maxhealxd = 150.f;
				if ((int)TargetPlayerA->GetHealth() <= 33)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxhealxd), 15 }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
				}
				if ((int)TargetPlayerA->GetHealth() >= 34 && (int)TargetPlayerA->GetHealth() <= 66)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxhealxd), 15 }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
				}
				if ((int)TargetPlayerA->GetHealth() >= 67)
				{
					GUI::Render.FillRectangle(Vector2{ 100, 90 }, Vector2{ 150 * (curhealth / maxhealxd), 15 }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
				}
			}
			WeaponData* ActWeapon = TargetPlayerA->GetActiveWeapon();
			GUI::Render.Rectangle(Vector2{ 100, 90 }, Vector2{ 150, 15 }, D2D1::ColorF::Black, 0.5f);
			if (!ActWeapon)
			{
				_swprintf(name, L"%s [%d m] [%d HP] [----]", TargetPlayerA->GetName(), (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), TargetPlayerA->GetBoneByID(head)), (int)TargetPlayerA->GetHealth());
			}
			else
			{
				_swprintf(name, L"%s [%d m] [%d HP] [%s]", TargetPlayerA->GetName(), (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), TargetPlayerA->GetBoneByID(head)), (int)TargetPlayerA->GetHealth(), ActWeapon->GetName());
			}
		}
		else
		{
			_swprintf(name, L"No target");
		}
		GUI::Render.String(Vector2(100, 70), name, D2D1::ColorF::White);
	}
  Entity();
}