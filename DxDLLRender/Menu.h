
using namespace ImGui;

ImFont* NameFont;
ImFont* TabsFont;
ImFont* MainFont;
ImFont* IconsFont;
#pragma region old tabs

static int tabs = 1;
#include <mutex>

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("|?|");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


ImFont* Veranda;

struct animation {
	bool clicked;
	bool reverse;
	float size;
	float mult;
};

void MenuSteep() {

	auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::SetNextWindowSize({ 810,490 });
	ImGui::Begin("##menu", nullptr, flags);
	{

		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();

		if (Vars::Theams::Dark)
		{
			draw->AddRectFilled({ pos.x,pos.y }, { pos.x + 830,pos.y + 499 }, ImColor(18, 18, 18), 5.f, ImDrawCornerFlags_Top);
			draw->AddRectFilled({ pos.x ,pos.y + 50 }, { pos.x + 830,pos.y + 499 }, ImColor(20, 20, 20), 5.f, ImDrawCornerFlags_All);
		}

		if (Vars::Theams::Light)
		{
			draw->AddRectFilled({ pos.x,pos.y }, { pos.x + 830,pos.y + 499 }, ImColor(5, 64, 158), 5.f, ImDrawCornerFlags_Top);
			draw->AddRectFilled({ pos.x ,pos.y + 50 }, { pos.x + 830,pos.y + 499 }, ImColor(5, 64, 158), 5.f, ImDrawCornerFlags_All);
		}

		draw->AddText(Veranda, 19.f, ImVec2(pos.x + 16, pos.y + 16), ImColor(255, 255, 255), "UdefParasha");

		static int tab = 0;
		static int subtab = 1;

		ImGui::SetCursorPos({ 15,25 - ImGui::CalcTextSize("UdefParasha").y / 2 });
		ImGui::SetCursorPos({ 150,1 });

		ImGui::BeginGroup();
		{
			if (Tab("", ("Aimot"), ("Rage,Legit"), ImVec2(100, 50), tab == 0 ? true : false))
				tab = 0;
			ImGui::SameLine();
			if (Tab("", ("Visuals"), ("Player,Bot"), ImVec2(96, 50), tab == 1 ? true : false))
				tab = 1;
			ImGui::SameLine();
			if (Tab("", ("Misc"), ("Weapon,Main"), ImVec2(95, 50), tab == 2 ? true : false))
				tab = 2;
			ImGui::SameLine();
			if (Tab("", ("Other"), ("Config,Theams"), ImVec2(99, 50), tab == 5 ? true : false))
				tab = 5;
			ImGui::SameLine();

		}
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 10,60 });
		ImGui::BeginGroup();
		{
			if (tab == 0)
			{

				if (SubTab(("Rage"), ImVec2(150, 25), subtab == 1 ? true : false))
					subtab = 1;

				if (SubTab(("Legit"), ImVec2(150, 25), subtab == 56 ? true : false))
					subtab = 56;

				if (SubTab(("Anti-Aim"), ImVec2(150, 25), subtab == 57 ? true : false))
					subtab = 57;


			}
			if (tab == 1)
			{
				if (SubTab(("Players"), ImVec2(150, 25), subtab == 4 ? true : false))
					subtab = 4;

				if (SubTab(("Bots"), ImVec2(150, 25), subtab == 5 ? true : false))
					subtab = 5;

				if (SubTab(("World"), ImVec2(150, 25), subtab == 6 ? true : false))
					subtab = 6;

				if (SubTab(("Radar"), ImVec2(150, 25), subtab == 11 ? true : false))
					subtab = 11;
			}
			if (tab == 2)
			{
				if (SubTab(("Main"), ImVec2(150, 25), subtab == 7 ? true : false))
					subtab = 7;

				if (SubTab(("Weapon"), ImVec2(150, 25), subtab == 8 ? true : false))
					subtab = 8;

				if (SubTab(("World"), ImVec2(150, 25), subtab == 78 ? true : false))
					subtab = 78;

			}
			if (tab == 5)
			{

				if (SubTab(("Config"), ImVec2(150, 25), subtab == 12 ? true : false))
				subtab = 12;

				if (SubTab(("Theams"), ImVec2(150, 25), subtab == 13 ? true : false))
				subtab = 13;

				if (SubTab(("Watermark"), ImVec2(150, 25), subtab == 14 ? true : false))
					subtab = 14;
			}


		}
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 170,60 });
		ImGui::BeginGroup();
		{
			ImGui::BeginChild("items", { 360, 400 });
			{

				ImGui::SetCursorPos({ 10,20 });
				ImGui::BeginGroup();
				{
					if (tab == 0)
					{

						if (subtab == 1)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox(("pSilent"), &Vars::AimBot::pSilent);
							if (Vars::AimBot::pSilent) {
								Checkbox("Draw pSilent Fov", &Vars::AimBot::DrawPSilentFov);
								if (Vars::AimBot::DrawPSilentFov) {
									Checkbox("pSilent Fill Fov", &Vars::AimBot::pSilentFillFov);
									SliderFloat("Psilent Fov", &Vars::AimBot::PSilentFov, 0, 800);
									SliderFloat("Psilent Distance", &Vars::AimBot::LimitDist, 0, 300);
								}
							}
								Checkbox(("HeliSilent"), &Vars::AimBot::HeliSilent);
								Checkbox(("Always Headshot"), &Vars::AimBot::psilentAlwaysHeadshot);
								Checkbox(("Force Body"), &Vars::AimBot::psilentAlwaysBody);
								//Checkbox("Visual check", &Vars::AimBot::VisibleCheck);
								Checkbox("Cleaning target", &Vars::AimBot::PSilentClear);
								if (Vars::AimBot::PSilentClear)
								{
									Hotkey(("Clear Button"), &Vars::AimBot::Psilentclearkey, ImVec2(130, 0));
								}
								Checkbox("Fat Bullet", &Vars::AimBot::FatBullet2);
								//Checkbox("MeleeAttack", &Vars::AimBot::DoMeleeAttack);
								//if (Vars::AimBot::SilentClear)
								//{
								//	Checkbox("HeadMeleeAttack", &Vars::AimBot::AimHead);
								//}

						}

					}
					if (tab == 0)
					{
						if (subtab == 56)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("Aimbot", &Vars::AimBot::Activate);
							if (Vars::AimBot::Activate)
							{
								Hotkey(("AimKey"), &Vars::AimBot::aimkey, ImVec2(100, 0));
								Checkbox(("BodyAim"), &Vars::AimBot::BodyAim);
								Checkbox(("RCS"), &Vars::AimBot::RCS);
								Checkbox(("Standalone"), &Vars::AimBot::Standalone);
								Checkbox(("Draw Fov"), &Vars::AimBot::DrawFov);
								if (Vars::AimBot::DrawFov)
								{
									Checkbox("Fill Fov", &Vars::AimBot::FillFov);
									SliderFloat("Fov", &Vars::AimBot::Fov,0, 100);
									SliderFloat("Distance", &Vars::AimBot::Range, 0, 400);
								}
								Checkbox(("Visible Check"), &Vars::AimBot::VisibleCheck);
								Checkbox(("Ignore Team"), &Vars::AimBot::IgnoreTeam);
								Checkbox(("Ignore Npc"), &Vars::AimBot::IgnoreNpc);
								Checkbox(("Ignore Sleepers"), &Vars::AimBot::IgnoreSleepers);
							}

						}

					}
					if (tab == 0)
					{
						if (subtab == 57)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("Anti-Aim", &Vars::Misc::AntiAim);
							Checkbox("Fakelag", &Vars::Misc::FakeLag);
							if (Vars::Misc::FakeLag)
							{
								SliderFloat("Fakelag Ticks", &Vars::Misc::FakeLagTicks, 0, 14);
							}

						}

					}
					if (tab == 1)
					{

						if (subtab == 4)
						{
							draw->AddRectFilled(ImVec2(pos.x + 540, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 513, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("PlayerESP", &Vars::Visuals::PlayerESP);
							Checkbox("PlayerName", &Vars::Visuals::ShowPlayerName);
							//ImGui::ColorEdit4("Color##3", (float*)&Vars::Color::NameColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
							if (Vars::Visuals::ShowPlayerName)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 135), ImColor(0, 0, 0), "Name");
							}
							Checkbox("PlayerWeapon", &Vars::Visuals::ShowPlayerWeapon);
							if (Vars::Visuals::ShowPlayerWeapon)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 150), ImColor(0, 0, 0), "M39");
							}
							Checkbox("PlayerHealth and Dist", &Vars::Visuals::ShowPlayerHealth);
							if (Vars::Visuals::ShowPlayerHealth)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 165), ImColor(0, 0, 0), "[100 HP][142 M]");
							}
							if (ImGui::BeginCombo("HealthBars", "Chose Style HealthBar"))
							{
								Checkbox("Left", &Vars::Visuals::ShowPlayerHealthBar);
								Checkbox("Bottom", &Vars::Visuals::ShowPlayerHealthBarBottom);
								End();
							}
							if (Vars::Visuals::ShowPlayerHealthBar)
							{
									draw->AddLine(ImVec2(pos.x + 570, pos.y + 140), ImVec2(pos.x + 570, pos.y + 410), ImColor(51, 255, 51), 5);
							}
							Checkbox("PlayerFillBox", &Vars::Visuals::FillBox);
							if (Vars::Visuals::FillBox)
							{
								draw->AddRectFilled(ImVec2(pos.x + 582, pos.y + 132), ImVec2(pos.x + 718, pos.y + 418), ImColor(16, 16, 16));
							}
							Checkbox("PlayerSkeleton", &Vars::Visuals::SkeletonPlayer);
							//if (Vars::Visuals::SkeletonPlayer)
							//{
							//  draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 650, pos.y + 290), ImColor(0, 0, 0), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 690, pos.y + 410), ImColor(0, 0, 0), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 610, pos.y + 410), ImColor(0, 0, 0), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 710, pos.y + 260), ImColor(0, 0, 0), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 590, pos.y + 260), ImColor(0, 0, 0), 2);
							//}
							Checkbox("OwnChams", &Vars::Visuals::ShowPlayerChams);
							//if (Vars::Visuals::ShowPlayerChams)
							//{
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 650, pos.y + 290), ImColor(129, 171, 255), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 690, pos.y + 410), ImColor(129, 171, 255), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 610, pos.y + 410), ImColor(129, 171, 255), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 710, pos.y + 260), ImColor(129, 171, 255), 2);
							//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 590, pos.y + 260), ImColor(129, 171, 255), 2);
							//}
							Checkbox("HandChams", &Vars::Visuals::ShowHandChams);
							if (ImGui::BeginCombo("Boxes", "Chose Style Box"))
							{
								Checkbox("Default", &Vars::Visuals::ShowPlayerBox);
								Checkbox("Corner", &Vars::Visuals::ShowPlayerCornerBox);
								End();
							}
							if (Vars::Visuals::ShowPlayerBox)
							{
								draw->AddRect(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 720, pos.y + 420), ImColor(0, 0, 0), 2, 2, 2);
							}
							if (Vars::Visuals::ShowPlayerCornerBox)
							{
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 580, pos.y + 190), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 620, pos.y + 130), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 719, pos.y + 130), ImVec2(pos.x + 719, pos.y + 190), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 720, pos.y + 130), ImVec2(pos.x + 680, pos.y + 130), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 360), ImVec2(pos.x + 580, pos.y + 420), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 419), ImVec2(pos.x + 620, pos.y + 419), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 719, pos.y + 360), ImVec2(pos.x + 719, pos.y + 420), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 720, pos.y + 419), ImVec2(pos.x + 680, pos.y + 419), ImColor(0, 0, 0), 2);
							}
							Checkbox("IgnoreSleepers", &Vars::Visuals::IgnoreSleepers);
							//ImGui::Checkbox("Rainbow Esp", &Vars::GG::rainbow);
							//if (Vars::GG::rainbow)
							//{
							//	ImGui::SliderFloat("Speed Rainbow", &Vars::GG::RbTime, 0.f, 5.f);
							//}
							if (ImGui::BeginCombo("Tracers", "Chose Style Tracer"))
							{
								Checkbox("Bottom", &Vars::Visuals::TracersBottom);
								Checkbox("Center", &Vars::Visuals::Tracers);
								End();
							}
							//Checkbox("Target Tracers", &Vars::Visuals::TargetTracers);
							Checkbox("ActiveSlot Dark", &Vars::Visuals::ActiveSlot);
							Checkbox("ActiveSlot Light", &Vars::Visuals::ActiveSlotLight);
							if (Vars::Visuals::ActiveSlot || Vars::Visuals::ActiveSlotLight)
							{
								ImGui::SliderFloat("Pos X", &Vars::Visuals::ActiveSlotPos_X, 0.f, 1500.f);
								ImGui::SliderFloat("Pos Y", &Vars::Visuals::ActiveSlotPos_Y, 0.f, 1500.f);
							}
						}
						if (subtab == 5)
						{
							draw->AddRectFilled(ImVec2(pos.x + 540, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 513, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("BotESP", &Vars::Visuals::BotsESP);
							Checkbox("BotName", &Vars::Visuals::BotsName);
							if (Vars::Visuals::BotsName)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 135), ImColor(0, 0, 0), "Bot");
							}
							Checkbox("BotWeapon", &Vars::Visuals::BotsWeapon);
							if (Vars::Visuals::BotsWeapon)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 165), ImColor(0, 0, 0), "LR-300");
							}
							Checkbox("BotHealth", &Vars::Visuals::BotsHealth);
							if (Vars::Visuals::BotsHealth)
							{
								draw->AddText(ImVec2(pos.x + 725, pos.y + 165), ImColor(0, 0, 0), "[300 HP][64 M]");
								Checkbox("BotHealthBar", &Vars::Visuals::BotsHealthBar);
								if (Vars::Visuals::BotsHealth)
								{
									draw->AddLine(ImVec2(pos.x + 570, pos.y + 140), ImVec2(pos.x + 570, pos.y + 410), ImColor(51, 255, 51), 5);
								}
							}
							Checkbox("Fill Box", &Vars::Visuals::BotsFillBox);
							if (Vars::Visuals::BotsFillBox)
							{
								draw->AddRectFilled(ImVec2(pos.x + 582, pos.y + 132), ImVec2(pos.x + 718, pos.y + 418), ImColor(16, 16, 16));
							}
							Checkbox("BotSkeleton", &Vars::Visuals::BotsSkeleton);
							if (Vars::Visuals::BotsSkeleton)
							{
								//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 650, pos.y + 290), ImColor(0, 0, 0), 2);
								//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 690, pos.y + 410), ImColor(0, 0, 0), 2);
								//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 290), ImVec2(pos.x + 610, pos.y + 410), ImColor(0, 0, 0), 2);
								//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 710, pos.y + 260), ImColor(0, 0, 0), 2);
								//	draw->AddLine(ImVec2(pos.x + 650, pos.y + 160), ImVec2(pos.x + 590, pos.y + 260), ImColor(0, 0, 0), 2);
							}
							if (ImGui::BeginCombo("Boxes", "Chose Style Box"))
							{
								Checkbox("Default", &Vars::Visuals::BotsBox);
								Checkbox("Corner", &Vars::Visuals::BotsBoxCorner);
								End();
							}
							if (Vars::Visuals::BotsBoxCorner)
							{
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 580, pos.y + 190), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 620, pos.y + 130), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 719, pos.y + 130), ImVec2(pos.x + 719, pos.y + 190), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 720, pos.y + 130), ImVec2(pos.x + 680, pos.y + 130), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 360), ImVec2(pos.x + 580, pos.y + 420), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 580, pos.y + 419), ImVec2(pos.x + 620, pos.y + 419), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 719, pos.y + 360), ImVec2(pos.x + 719, pos.y + 420), ImColor(0, 0, 0), 2);
								draw->AddLine(ImVec2(pos.x + 720, pos.y + 419), ImVec2(pos.x + 680, pos.y + 419), ImColor(0, 0, 0), 2);
							}
							if (Vars::Visuals::BotsBox)
							{
								draw->AddRect(ImVec2(pos.x + 580, pos.y + 130), ImVec2(pos.x + 720, pos.y + 420), ImColor(0, 0, 0), 2, 2, 2);
							}
						}
						if (subtab == 6)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							if (ImGui::CollapsingHeader("Ores"))
							{
								//Checkbox("Resourses Box", &Vars::Visuals::EnableBoxResourses);       
								Checkbox("Sulphur", &Vars::Visuals::Sulphur);
								if (Vars::Visuals::Sulphur)
								{
									ImGui::SliderFloat("Sulphur Distance", &Vars::Visuals::SulphurOreDistation, 0.f, 2500.f);
								}
								Checkbox("Metal", &Vars::Visuals::Metal);
								if (Vars::Visuals::Metal)
								{
									ImGui::SliderFloat("Metal Distance", &Vars::Visuals::MetalOreDistation, 0.f, 2500.f);
								}
								Checkbox("Stone", &Vars::Visuals::Stone);
								if (Vars::Visuals::Stone)
								{
									ImGui::SliderFloat("Stone Distance", &Vars::Visuals::MetalOreDistation, 0.f, 2500.f);
								}
							}
							if (ImGui::CollapsingHeader("Crates"))
							{
								Checkbox("AirDrop", &Vars::Visuals::Supply);
								if (Vars::Visuals::Supply)
								{
									ImGui::SliderFloat("AirDrop Distance", &Vars::Visuals::SupplyDistation, 0.f, 2500.f);
								}
								Checkbox("Chinook Crate", &Vars::Visuals::Crate);
								if (Vars::Visuals::Crate)
								{
									ImGui::SliderFloat("Chinook Crate Distance", &Vars::Visuals::CrateDistation, 0.f, 2500.f);
								}
							}
							if (ImGui::CollapsingHeader("Vehicles"))
							{
								Checkbox("Minicopters", &Vars::Visuals::Minicopter);
								if (Vars::Visuals::Minicopter)
								{
									ImGui::SliderFloat("Minicopters Distance", &Vars::Visuals::MinicopterDistation, 0.f, 2500.f);
								}
								Checkbox("Scrap Copters", &Vars::Visuals::ScrapCopter);
								if (Vars::Visuals::ScrapCopter)
								{
									ImGui::SliderFloat("Scrap Copter Distance", &Vars::Visuals::ScrapCopterDistation, 0.f, 2500.f);
								}
								Checkbox("Boats", &Vars::Visuals::Boat);
								if (Vars::Visuals::Boat)
								{
									ImGui::SliderFloat("Boat Distance", &Vars::Visuals::BoatDistation, 0.f, 2500.f);
								}
								Checkbox("RHIB's", &Vars::Visuals::RHIB);
								if (Vars::Visuals::RHIB)
								{
									ImGui::SliderFloat("RHIB Distance", &Vars::Visuals::RHIBDistation, 0.f, 2500.f);
								}
								Checkbox("Patrul", &Vars::Visuals::Patrul);
								if (Vars::Visuals::Patrul)
								{
									ImGui::SliderFloat("Patrul Distance", &Vars::Visuals::PatrulDistation, 0.f, 2500.f);
								}
								Checkbox("Bardley", &Vars::Visuals::Bardley);
								if (Vars::Visuals::Bardley)
								{
									ImGui::SliderFloat("Bardley Distance", &Vars::Visuals::BardleylDistation, 0.f, 2500.f);
								}
							}
							if (ImGui::CollapsingHeader("Traps"))
							{
								Checkbox("Auto Turrets", &Vars::Visuals::AutoTurrets);
								if (Vars::Visuals::AutoTurrets)
								{
									SliderFloat("Auto Turrets Distance", &Vars::Visuals::AutoTurretsDistation, 0.f, 2500.f);
								}
								Checkbox("Flame Turrets", &Vars::Visuals::FlameTurrets);
								if (Vars::Visuals::FlameTurrets)
								{
									SliderFloat("Flame Turrets Distance", &Vars::Visuals::FlameTurretsDistation, 0.f, 2500.f);
								}
								Checkbox("Shotgun Traps", &Vars::Visuals::ShotgunTraps);
								if (Vars::Visuals::ShotgunTraps)
								{
									SliderFloat("Shotgun Traps Distance", &Vars::Visuals::ShotgunTrapsDistation, 0.f, 2500.f);
								}
								Checkbox("Land-Air Turret", &Vars::Visuals::LandAirTurret);
								if (Vars::Visuals::LandAirTurret)
								{
									SliderFloat("Land-Air Turret Distance", &Vars::Visuals::LandAirTurretDistation, 0.f, 2500.f);
								}
							}
							if (ImGui::CollapsingHeader("Misc"))
							{
								if (ImGui::CollapsingHeader("House"))
								{
									Checkbox("Workbench1", &Vars::House::workbench1);
									if (Vars::House::workbench1)
									{
										ImGui::SliderFloat("Workbench1 Distance", &Vars::House::workbench1Distation, 0.f, 2500.f);
									}
									Checkbox("Workbench2", &Vars::House::workbench2);
									if (Vars::House::workbench2)
									{
										ImGui::SliderFloat("Workbench2 Distance", &Vars::House::workbench2Distation, 0.f, 2500.f);
									}
									Checkbox("Workbench3", &Vars::House::workbench3);
									if (Vars::House::workbench3)
									{
										ImGui::SliderFloat("Workbench3 Distance", &Vars::House::workbench3Distation, 0.f, 2500.f);
									}
									Checkbox("Cupboard", &Vars::House::cupboard);
									if (Vars::House::cupboard)
									{
										ImGui::SliderFloat("Cupboard Distance", &Vars::House::cupboardDistation, 0.f, 2500.f);
									}
									Checkbox("Chest", &Vars::House::chest);
									if (Vars::House::chest)
									{
										ImGui::SliderFloat("Chest Distance", &Vars::House::chestDistation, 0.f, 2500.f);
									}
								}
								if (ImGui::CollapsingHeader("Other"))
								{
									Checkbox("Stash", &Vars::Visuals::Stash);
									if (Vars::Visuals::Stash)
									{
										ImGui::SliderFloat("Stash Distance", &Vars::Visuals::StashDistation, 0.f, 2500.f);
									}
									Checkbox("Hemp", &Vars::Visuals::Hemp);
									if (Vars::Visuals::Hemp)
									{
										ImGui::SliderFloat("Hemp Distance", &Vars::Visuals::HempDistation, 0.f, 2500.f);
									}
									Checkbox("Corpse", &Vars::Visuals::Corpse);
									if (Vars::Visuals::Corpse)
									{
										ImGui::SliderFloat("Corpse Distance", &Vars::Visuals::CorpseDistation, 0.f, 2500.f);
									}
								}
								if (ImGui::CollapsingHeader("Weapons"))
								{
									Checkbox("Weapon", &Vars::Visuals::show_Weapons);
									if (Vars::Visuals::Stash)
									{
										ImGui::SliderFloat("Weapon Distance", &Vars::Visuals::show_WeaponsDistation, 0.f, 2500.f);
									}
								}
							}
						}
					}
					if (tab == 2)
					{

						if (subtab == 7)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("AutoHeal(sometimes kick from the server)", &Vars::Misc::FastHeal);
							Checkbox("InfinityJump", &Vars::Misc::InfinityJump);
							Checkbox("JumpAiming", &Vars::Misc::JumpAiming);
							Checkbox("LongHand", &Vars::Misc::LongHand);
							Checkbox("FatHand", &Vars::Misc::FatHand);
							Checkbox("Long Neck", &Vars::Misc::LongNeck);
							if (Vars::Misc::LongNeck)
							{
								Hotkey(("LongNeck Key"), &Vars::Misc::lnkey, ImVec2(130, 0));
							}
							Checkbox("NoHeavyReduct", &Vars::Misc::NoHeavyReduct);
							Checkbox("RunOnHit", &Vars::Misc::RunOnHit);
							Checkbox("CanHoldItems", &Vars::Misc::canHoldItems);
							Checkbox("Silent Walk", &Vars::Misc::SilentWalk);
							Checkbox("Slide Walk", &Vars::Misc::SlideWalk);
							Checkbox("Spoof OnLadder", &Vars::Misc::Flyhack);
							Checkbox("SpiderMan", &Vars::Misc::SpiderMan);
							//Checkbox("Roll Buildings", &Vars::Misc::BuildAsUWant);
							//if (Vars::Misc::BuildAsUWant)
							//{
							//	Hotkey("Roll Buildings", &Vars::Misc::buildkey, ImVec2(130, 0));
							//}
							//Checkbox("AirStop", &Vars::Misc::AirStuck);
							//if (Vars::Misc::AirStuck)
							//{
							//	Hotkey(("AirStuck Key"), &Vars::Misc::airkey, ImVec2(130, 0));
							//}
						  }
						if (subtab == 8)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("NoRecoil", &Vars::Misc::NoRecoil);
							if (Vars::Misc::NoRecoil)
							{
								ImGui::SliderFloat("YawMin", &Vars::Misc::YawMin, 0.0f, 5.0f);
								ImGui::SliderFloat("YawMax", &Vars::Misc::YawMax, 0.0f, 5.0f);
							}
							Checkbox("NoSway", &Vars::Misc::NoSway);
							Checkbox("NoSpread", &Vars::Misc::AntiSpread);
							Checkbox("NoBlockAiming", &Vars::Misc::AntiKastrulya);
							//Checkbox("RapidFire", &Vars::Misc::RapidFire);
							Checkbox("Automatic", &Vars::Misc::Automatic);
							Checkbox("100% Eoka", &Vars::Misc::SuperEoka);
							Checkbox("SuperBow", &Vars::Misc::SuperBow);
							Checkbox("ShotGunNoSpread", &Vars::Misc::ShotGunTochka);
						}
						if (subtab == 78)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox(u8"AlwaysDay", &Vars::Visuals::AlwaysDay);
							Checkbox(u8"Night Mode", &Vars::Visuals::NightMode);
							Checkbox("Zoom", &Vars::Misc::Zoom);
							if (Vars::Misc::Zoom)
							{
								Hotkey("Zoom Key", &Vars::Misc::zoomkey, ImVec2(120, 0));
							}
							Checkbox("FakeAdmin", &Vars::Misc::NewFakeAdmin);
							Checkbox("ThirdPerson", &Vars::Misc::ThirdPerson);
							Checkbox("AutoPickUp(sometimes kick from the server)", &Vars::Misc::AutoPickUp);
							Checkbox("DoorTouch(sometimes kick from the server)", &Vars::Misc::Door);
							Checkbox("WalkOnWater", &Vars::Misc::WalkOnWater);
							if (Vars::Misc::WalkOnWater)
							{
								Hotkey(("WalkOnWater Key"), &Vars::Misc::walkkey, ImVec2(150, 0));
							}
							Checkbox("SpeedHack", &Vars::Misc::speedhack);
							if (Vars::Misc::speedhack)
							{
								Hotkey(("Speedhack Key"), &Vars::Misc::speedhackkey, ImVec2(140, 0));
							}
							Checkbox("Custom Fov", &Vars::Misc::CustomFov);
							if (Vars::Misc::CustomFov)
							{
								ImGui::SliderFloat("Fov", &Vars::Misc::FovRange, 0.f, 180.f);
							}
							Checkbox(("HitSound"), &Vars::Misc::HitSound);
							if (ImGui::CollapsingHeader("Crosshaires"))
							{
								Checkbox("Default", &Vars::Misc::Crosshair1);
								Checkbox("Circle", &Vars::Misc::Crosshair2);
								Checkbox("Custom", &Vars::Misc::CrosshairCustom);
								if (Vars::Misc::CrosshairCustom)
								{
									ImGui::SliderFloat("X" "X-Pos", &Vars::Misc::X, 0.f, 100.f);
									ImGui::SliderFloat("Y" "Y-Pos", &Vars::Misc::Y, 0.f, 100.f);
									ImGui::Separator();
								}
							}
						}
					}
					if (tab == 5)
					{

						if (subtab == 12)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							ImGui::InputText("", Vars::Config::configname, 0x100);
							if (ImGui::Button(("Save Config"), ImVec2(100.f, 0))) {
								SaveCFG(Vars::Config::configname);
								Vars::Config::SaveConfig = true;
							}
							ImGui::SameLine();
							if (ImGui::Button(("Load Config"), ImVec2(100.f, 0))) {
								LoadCFG(Vars::Config::configname);
							}
							if (ImGui::Button(("Panic"), ImVec2(80.f, 0))) {
								Vars::Global::Panic = true;
							}
							ImGui::Spacing();
							ImGui::Spacing();
							Hotkey(("Panic Key"), &Vars::Global::PanicKey, ImVec2(130, 0));
							Hotkey(("Menu Key"), &Vars::Global::MenuKey, ImVec2(130, 0));
						}
					}
					if (tab == 1)
					{
						if (subtab == 11)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("Enable", &Vars::Radar::Enable);
							Checkbox("ShowRadarBackground", &Vars::Radar::ShowRadarBackground);
							Checkbox("ShowRadarPlayer", &Vars::Radar::ShowRadarPlayer);
							Checkbox("ShowRadarSleeper", &Vars::Radar::ShowRadarSleeper);
							ImGui::SliderFloat("Radar_X", &Vars::Radar::Pos_X, 0.f, 1669.f);
							ImGui::SliderFloat("Radar_Y", &Vars::Radar::Pos_Y, 0.f, 830.f);
							ImGui::SliderFloat("Radar Size", &Vars::Radar::Radar_Size, 0.f, 250.f);
							ImGui::SliderFloat("Radar Range", &Vars::Radar::Radar_Range, 0.f, 600.f);
						}
					}
					if (tab == 5)
					{
						if (subtab == 13)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("Dark", &Vars::Theams::Dark);
							Checkbox("Light", &Vars::Theams::Light);
						}
					}
					if (tab == 5)
					{
						if (subtab == 14)
						{
							draw->AddRectFilled(ImVec2(pos.x + 170, pos.y + 75), ImVec2(pos.x + 780, pos.y + 470), ImColor(25, 30, 35), 3);

							Checkbox("Watermark Dark", &Vars::Watermark::waterm);
							Checkbox("Watermark Light", &Vars::Watermark::watermL);
							if (Vars::Watermark::waterm)
							{
								ImGui::SliderFloat("Position X", &Vars::Watermark::PosX, 0.f, 1200.f);
								ImGui::SliderFloat("Position Y", &Vars::Watermark::PosY, 0.f, 1200.f);
							}
							if (Vars::Watermark::watermL)
							{
								ImGui::SliderFloat("Position X", &Vars::Watermark::PosX, 0.f, 1200.f);
								ImGui::SliderFloat("Position Y", &Vars::Watermark::PosY, 0.f, 1200.f);
							}
						}
					}
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();

	}
}