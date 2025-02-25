#include <d3d9.h>
#include "../ImGUI/imgui_internal.h"

inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF ColorRectangle = D2D1::ColorF::Lime)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);
	
	if (Vars::Visuals::FillBox)
	{
		GUI::Render.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0, 0, 0, 0.45));
	}
}

inline void DefaultBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF ColorRectangle = D2D1::ColorF::Lime)
{
		GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 2.f,Entity_y }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 2.f }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 2.f }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 2.f }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 2.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
		GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 2.f }, D2D1::ColorF::Black);
		
		if (Vars::Visuals::FillBox)
		{
			GUI::Render.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0, 0, 0, 0.45));
		}
}

inline void BotCornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF ColorRectangle = D2D1::ColorF::Lime)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);

	if (Vars::Visuals::BotsFillBox)
	{
		GUI::Render.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0, 0, 0, 0.45));
	}
}

inline void BotDefaultBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF ColorRectangle = D2D1::ColorF::Lime)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 2.f,Entity_y }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 2.f }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 2.f }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 2.f }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 2.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 2.f }, D2D1::ColorF::Black);

	if (Vars::Visuals::BotsFillBox)
	{
		GUI::Render.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0, 0, 0, 0.45));
	}
}

D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
void Skeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}
	if ((int)BasePlayer->GetHealth() > 0)
	{
		if (LocalPlayer.BasePlayer->IsTeamMate(BasePlayer->GetSteamID()))
		{
			for (int j = 0; j < 15; j += 3) {
				GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen, 0.5f);
				GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen);
				GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen, 0.5f);
				GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen);
			}

			//draw add lines
			GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
			GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
			GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
			GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
		}
		else
		{
			for (int j = 0; j < 15; j += 3) {
				GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::White, 0.5f);
				GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::White);
				GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::White, 0.5f);
				GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::White);
			}

			//draw add lines
			GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White);
			GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White);
			GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White);
			GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White);
		}

	}
	else
	{
		for (int j = 0; j < 15; j += 3) {
			GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red);
			GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red, 0.5f);
			GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red);
		}

		//draw add lines
		GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
		GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
		GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
		GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
		GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
		GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
		GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
		GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
	}
	//draw main lines

}

void BotSkeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	for (int j = 0; j < 15; j += 3) {
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF(63, 235, 229), 0.5f);
		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF(63, 235, 229), 0.5f);
	}

	//draw add lines
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF(63, 235, 229), 0.5f);
	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF(63, 235, 229), 0.5f);
	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF(63, 235, 229), 0.5f);
	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF(63, 235, 229), 0.5f);

}

void MemeBox(const D2D1::ColorF& PlayerClr, BasePlayer* BasePlayer)
{
	BoneList Bones[4] = {
		/*UP*/l_upperarm, r_upperarm,
		/*DOWN*/r_foot, l_foot
	}; Vector2 BonesPos[4];

	//get bones screen pos
	for (int j = 0; j < 4; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, D2D1::ColorF::White, 3.f);
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, D2D1::ColorF::White, 3.f);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, D2D1::ColorF::White, 3.f);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, D2D1::ColorF::White, 3.f);
}

void Crosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	GUI::Render.Line(Vector2{ xs, ys - -10 }, Vector2{ xs , ys + 5 }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs - -10, ys }, Vector2{ xs + 5, ys }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + -10 }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + -10, ys }, D2D1::ColorF::White);
}


void CircleCrosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Vars::Misc::Crosshair2)
	{
		GUI::Render.Ñircle(Vector2{ xs - 3, ys }, D2D1::ColorF::White, Vars::HvH::Tick2);
	}
}

void CrosshairCustom()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	GUI::Render.Line(Vector2{ xs, ys - Vars::Misc::Y }, Vector2{ xs , ys + Vars::Misc::Y }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs - Vars::Misc::X, ys }, Vector2{ xs + Vars::Misc::X, ys }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs, ys - Vars::Misc::Y }, Vector2{ xs , ys + Vars::Misc::Y }, D2D1::ColorF::White);
	GUI::Render.Line(Vector2{ xs - Vars::Misc::X, ys }, Vector2{ xs + Vars::Misc::X, ys }, D2D1::ColorF::White);
}

void DrawFOV()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.FillCircle(Vector2{ xs, ys }, D2D1::ColorF(0, 0, 0, 0.7f), Vars::AimBot::Fov / Vars::AimBot::FillFov);
	GUI::Render.Ñircle(Vector2{ xs, ys }, D2D1::ColorF::White, Vars::AimBot::Fov, 1.f);
	GUI::Render.Ñircle(Vector2{ xs, ys }, D2D1::ColorF::White, Vars::AimBot::Fov);
}

void DrawPSilentFov()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.FillCircle(Vector2{ xs, ys }, D2D1::ColorF(0, 0, 0, 0.7f), Vars::AimBot::PSilentFov / Vars::AimBot::pSilentFillFov);
	GUI::Render.Ñircle(Vector2{ xs, ys }, D2D1::ColorF::White, Vars::AimBot::PSilentFov, 1.f);
	GUI::Render.Ñircle(Vector2{ xs, ys }, D2D1::ColorF::White, Vars::AimBot::PSilentFov);
}



#pragma region Player ESP

void ESP(BasePlayer* BP, BasePlayer* LP)
{
	bool PlayerSleeping = BP->HasFlags(16);
	bool PlayerWounded = BP->HasFlags(64);
	if (Vars::Visuals::IgnoreSleepers && PlayerSleeping)
		return;

	if (Vars::Visuals::SkeletonPlayer && BP->GetSteamID() > 1000000000)
	{
		Skeleton(BP);
	}

	else if (Vars::Visuals::BotsSkeleton && BP->GetSteamID() < 1000000000)
	{
		BotSkeleton(BP);
	}

	Vector2 tempFeetR, tempFeetL;
	if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL))
	{
		Vector2 tempHead;
		if (LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
		{
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;

			bool PlayerWounded = BP->HasFlags(64);
			D2D1::ColorF::Enum PlayerClr = PlayerSleeping ? D2D1::ColorF::BlueViolet : PlayerWounded ? D2D1::ColorF::DarkOrange : D2D1::ColorF::Gold;

			int CurPos = 0;

			if (Vars::Visuals::PlayerESP && BP->GetSteamID() > 1000000000)
			{
				if (Vars::Visuals::ShowPlayerName)
				{
					wchar_t name[64];
					_swprintf(name, L"%s", BP->GetName());

					if (!PlayerSleeping)
					{
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 10.f }, name, D2D1::ColorF::LimeGreen);
							}
							else
							{
								GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 10.f }, name, D2D1::ColorF::White);
							}
						}
						else
						{
							GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 10.f }, name, D2D1::ColorF::Red);
						}
					}
					else
					{
						GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 10.f }, name, D2D1::ColorF::Orange);
					}
					CurPos += 15;
				}

				if (Vars::Visuals::ShowPlayerCornerBox)
				{
					if ((int)BP->GetHealth() > 0)
					{
						if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
						{
							CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::LimeGreen);
						}
						else
						{
							CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::White);
						}
					}
					else
					{
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Red);
					}
				}

				if (Vars::Visuals::ShowPlayerBox)
				{
					if ((int)BP->GetHealth() > 0)
					{
						if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
						{
							DefaultBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::LimeGreen);
						}
						else
						{
							DefaultBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::White);
						}
					}
					else
					{
						DefaultBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Red);
					}
				}


					if (Vars::Visuals::ShowPlayerHealth) {
						int health = (int)BP->GetHealth();
						float maxheal = 100.f;

						wchar_t healtht[64];
						_swprintf(healtht, L"[%d HP][%d M]", (int)BP->GetHealth(), (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));
						if (!PlayerSleeping)
						{
							if ((int)BP->GetHealth() > 0)
							{
								if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
								{
									GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, healtht, D2D1::ColorF::LimeGreen);
								}
								else
								{
									GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, healtht, D2D1::ColorF::White);
								}
							}
							else
							{
								GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, healtht, D2D1::ColorF::Red);
							}
						}
						else
						{
							GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, healtht, D2D1::ColorF::Orange);
						}
						CurPos += 15;

						if (Vars::Visuals::ShowPlayerHealthBar)
						{
							if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
							{
								//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
								//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / minheal) }, D2D1::ColorF::Magenta);
								if ((int)BP->GetHealth() <= 33)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
								}
								if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
								}
								if ((int)BP->GetHealth() >= 67)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
								}
								GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w, Entity_y - 8.f }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
							}
						}
						if (Vars::Visuals::ShowPlayerHealthBarBottom)
						{
							if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
							{
								//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
								//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / minheal) }, D2D1::ColorF::Magenta);
								if ((int)BP->GetHealth() <= 33)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, Vector2{ 5, Entity_w * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
								}
								if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, Vector2{ 5, Entity_w * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
								}
								if ((int)BP->GetHealth() >= 67)
								{
									GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, Vector2{ 5, Entity_w * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
								}
								GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 36.f }, Vector2{ 5, Entity_w }, D2D1::ColorF::Black, 0.5f);
							}
						}
					}

					if (Vars::Visuals::ShowPlayerWeapon && !BP->IsNpc())
					{

						const wchar_t* ActiveWeaponName;
						WeaponData* ActWeapon = BP->GetActiveWeapon();
						ActiveWeaponName = ActWeapon->GetName();
						if (!ActWeapon)
						{

							ActiveWeaponName = L"[----]";
						}
						else
						{
							ActiveWeaponName = ActWeapon->GetName();
						}
						if (!PlayerSleeping)
						{
							if ((int)BP->GetHealth() > 0)
							{
								if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
								{
									GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 23.f }, ActiveWeaponName, D2D1::ColorF::LimeGreen);
								}
								else
								{
									GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 23.f }, ActiveWeaponName, D2D1::ColorF::White);
								}
							}
							else
							{
								GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 23.f }, ActiveWeaponName, D2D1::ColorF::Red);
							}
						}
						else
						{
							GUI::Render.String(Vector2{ Entity_x + Entity_w - 8.f, Entity_y + 23.f }, ActiveWeaponName, D2D1::ColorF::Orange);
						}
					}
					if (Vars::Visuals::Tracers && !PlayerSleeping && !BP->IsNpc())
					{
						static float screenX = GetSystemMetrics(SM_CXSCREEN);
						static float screenY = GetSystemMetrics(SM_CYSCREEN);
						static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 450.f);
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::LimeGreen, 0.5f);
							}
							else
							{
								GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::White, 0.5f);
							}
						}
						else
						{
							GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::Red, 0.5f);
						}
					}
					if (Vars::Visuals::TracersBottom && !PlayerSleeping && !BP->IsNpc())
					{
						static float screenX = GetSystemMetrics(SM_CXSCREEN);
						static float screenY = GetSystemMetrics(SM_CYSCREEN);
						static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 70.f);
						if ((int)BP->GetHealth() > 0)
						{
							if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
							{
								GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::LimeGreen, 0.5f);
							}
							else
							{
								GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::White, 0.5f);
							}
						}
						else
						{
							GUI::Render.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::Red, 0.5f);
						}
					}

			}
			else if (Vars::Visuals::BotsESP && BP->GetSteamID() < 1000000000)
			{
			if (Vars::Visuals::BotsBox && BP->IsNpc())
			{
				BotDefaultBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Turquoise);
			}
			if (Vars::Visuals::BotsBoxCorner && BP->IsNpc())
			{
				BotCornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Turquoise);
			}
			if (Vars::Visuals::BotsName && BP->IsNpc())
			{
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h) }, L"Bot", D2D1::ColorF::Turquoise);
			}
			if (Vars::Visuals::BotsHealth && BP->IsNpc())
			{
				int health = (int)BP->GetHealth();
				float maxheal = 300.f;

				wchar_t healtht[64];
				_swprintf(healtht, L"[%d HP][%d M]", (int)BP->GetHealth(), (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));
				GUI::Render.String(Vector2{ Entity_x + 7.f, Entity_y + Entity_h + CurPos }, healtht, D2D1::ColorF::Turquoise);
				CurPos += 15;
				if (Vars::Visuals::BotsHealthBar)
				{
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
					{
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / minheal) }, D2D1::ColorF::Magenta);
						if ((int)BP->GetHealth() <= 33)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->GetHealth() >= 67)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
					}
				}
			}
			if (Vars::Visuals::BotsWeapon && BP->IsNpc())
			{
				const wchar_t* ActiveWeaponName;
				WeaponData* ActWeapon = BP->GetActiveWeapon();
				ActiveWeaponName = ActWeapon->GetName();
				if (!ActWeapon)
				{
					ActiveWeaponName = L"[----]";
				}
				else
				{
					ActiveWeaponName = ActWeapon->GetName();
				}
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, ActiveWeaponName, D2D1::ColorF::Turquoise);
				CurPos += 10;
			}

			}
		}
	}
}
__forceinline float Distance3D(const Vector3& Src, const Vector3& Dst)
{
	return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
}

void RadarPlayer(BasePlayer* player)
{
	if (LocalPlayer.BasePlayer)
	{
		if (Vars::Radar::Enable)
		{
			if (Vars::Radar::ShowRadarPlayer || Vars::Radar::ShowRadarSleeper)
			{
				if (!player->IsDead() && player->GetHealth() >= 0.2f)
				{
					const Vector3 LocalPos = LocalPlayer.BasePlayer->GetPosition();
					const Vector3 PlayerPos = player->GetPosition();
					const float Distance = Distance3D(LocalPos, PlayerPos);
					const float y = LocalPos.x - PlayerPos.x;
					const float x = LocalPos.z - PlayerPos.z;
					Vector3 LocalEulerAngles;
					const float num = atan2(y, x) * 57.29578f - 270.f - LocalEulerAngles.y;
					float PointPos_X = Distance * cos(num * 0.0174532924f);
					float PointPos_Y = Distance * sin(num * 0.0174532924f);
					PointPos_X = PointPos_X * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 1.f;
					PointPos_Y = PointPos_Y * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 1.f;
					if (!player->HasFlags(16) && Vars::Radar::ShowRadarPlayer)
					{
						if (Distance <= Vars::Radar::Radar_Range)
						{
							GUI::Render.Ñircle({ Vars::Radar::Pos_X + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, Vars::Radar::Pos_Y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF(97, 250, 227, 0.7), 1.f);
						}
					}

					/*	if (Vars::Radar::ShowRadarBackground)
						{
							GUI::Render.FillCircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, D2D1::ColorF(Vars::BotsRGBA::BR / 0.f, Vars::BotsRGBA::BG / 0.f, Vars::BotsRGBA::BB / 0.f, Vars::BotsRGBA::BA / 55.f), Rad / 2);
							GUI::Render.Ñircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, ConverToRGB(20, 15, 52), Rad / 2);
						}*/

					else if (player->HasFlags(16) && Vars::Radar::ShowRadarSleeper)
					{
						if (Distance <= Vars::Radar::Radar_Range)
						{
							GUI::Render.Ñircle({ Vars::Radar::Pos_X + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, Vars::Radar::Pos_Y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF(255, 36, 36, 0.7), 1.f);
						}
					}
				}
			}
		}
	}
}

inline void RenderRadarBackground(float Pos_x, float Pos_Y, float Rad)
{

  if (Vars::Radar::ShowRadarBackground)
  GUI::Render.FillCircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, D2D1::ColorF(0,0,0,0.5), Rad / 2);
  GUI::Render.Ñircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, D2D1::ColorF(0, 0, 0), Rad / 2, 1.f);
}


inline void RenderActiveSlot(BasePlayer* player,  float Pos_x, float Pos_Y)
{
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		static int cases = 0;
		switch (cases)
		{
		case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		float maxheal = 100.f;
		int health = player->GetHealth();
		const float Height = 180.f;
		const float With = 160.f;
		GUI::Render.FillRoundedRectangle({ Pos_x, Pos_Y }, { With, Height }, D2D1::ColorF(0, 0, 0, 0.8), 4);
		GUI::Render.FillRectangle(Vector2{ Pos_x + 130, Pos_Y + 40 }, Vector2{ 5, 100.f * (health / maxheal) }, D2D1::ColorF::LightGreen);
		GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 5 }, player->GetName(), true, D2D1::ColorF::White);
		float Pos = 0;
		for (int i = 0; i < 6; i++)
		{
			WeaponData* GetWeaponInfo = player->GetWeaponInfo(i);
			if (GetWeaponInfo)
			{
				const wchar_t* Item = player->GetWeaponInfo(i)->GetName();
				if (wcslen(Item) < 20)
				{
					GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, Item, true);
				}
			}
			else
			{
				GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, L"----", true, D2D1::ColorF::White);
			}
			Pos += 15;
		}
}

inline void RenderActiveSlotLight(BasePlayer* player, float Pos_x, float Pos_Y)
{
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		static int cases = 0;
		switch (cases)
		{
		case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		float maxheal = 100.f;
		int health = player->GetHealth();
		const float Height = 180.f;
		const float With = 160.f;
		GUI::Render.FillRoundedRectangle({ Pos_x, Pos_Y }, { With, Height }, D2D1::ColorF(5, 64, 158, 0.8), 4);
		GUI::Render.FillRectangle(Vector2{ Pos_x + 130, Pos_Y + 40 }, Vector2{ 5, 100.f * (health / maxheal) }, D2D1::ColorF::LightGreen);
		GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 5 }, player->GetName(), true, D2D1::ColorF::Black);
		float Pos = 0;
		for (int i = 0; i < 6; i++)
		{
			WeaponData* GetWeaponInfo = player->GetWeaponInfo(i);
			if (GetWeaponInfo)
			{
				const wchar_t* Item = player->GetWeaponInfo(i)->GetName();
				if (wcslen(Item) < 20)
				{
					GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, Item, true, D2D1::ColorF::Black);
				}
			}
			else
			{
				GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, L"----", true, D2D1::ColorF::Black);
			}
			Pos += 15;
		}
}


#pragma endregion

