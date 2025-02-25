#pragma once
#include <direct.h>

CSimpleIniA cfg; //инициализируем объект

#pragma region Config Color

void SaveColorValue(const char* pSection, std::string name, float a_Value[4])
{
    int R, G, B, A;
    R = a_Value[0] * 1000;
    G = a_Value[1] * 1000;
    B = a_Value[2] * 1000;
    A = a_Value[3] * 1000;
    cfg.SetLongValue(pSection, (name + "_R").c_str(), R);
    cfg.SetLongValue(pSection, (name + "_G").c_str(), G);
    cfg.SetLongValue(pSection, (name + "_B").c_str(), B);
    cfg.SetLongValue(pSection, (name + "_A").c_str(), A);
}

void LoadColorValue(const char* pSection, std::string name, float a_Value[4])
{
    float R, G, B, A;
    R = cfg.GetLongValue(pSection, (name + "_R").c_str(), a_Value[0]);
    G = cfg.GetLongValue(pSection, (name + "_G").c_str(), a_Value[1]);
    B = cfg.GetLongValue(pSection, (name + "_B").c_str(), a_Value[2]);
    A = cfg.GetLongValue(pSection, (name + "_A").c_str(), a_Value[3]);
    a_Value[0] = R / 1000; a_Value[1] = G / 1000; a_Value[2] = B / 1000; a_Value[3] = A / 1000;
}

#pragma endregion 

inline bool folder_exists(const char* foldername)
{
    struct stat st;
    stat(foldername, &st);
    return st.st_mode & S_IFDIR;
}

void SaveCFG(const char* FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, "C:\\Windows\\Temp\\UdefHack\\");

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, "C:\\Windows\\Temp\\UdefHack\\%s.ini", FileName);

#pragma region AimBot
    cfg.SetBoolValue("Aim", "Enable", Vars::AimBot::Activate);
    cfg.SetLongValue("Aim", "Aim Bot Key", Vars::AimBot::aimkey);
    cfg.SetLongValue("Aim", "Distance", Vars::AimBot::Range);
    cfg.SetLongValue("Aim", "Fov", Vars::AimBot::Fov);
    cfg.SetLongValue("Aim", "Fov Size", Vars::AimBot::FovSize);
    cfg.SetLongValue("Aim", "Fill Fov", Vars::AimBot::FillFov);
    cfg.SetBoolValue("Aim", "Recoil Control System", Vars::AimBot::RCS);
    cfg.SetBoolValue("Aim", "RCS Standalone", Vars::AimBot::Standalone);
    cfg.SetBoolValue("Aim", "Show Fov", Vars::AimBot::DrawFov);
    cfg.SetBoolValue("Aim", "Visible Check", Vars::AimBot::VisibleCheck);
    cfg.SetBoolValue("Aim", "Body Aim", Vars::AimBot::BodyAim);
    cfg.SetBoolValue("Aim", "IgnoreSleepers", Vars::AimBot::IgnoreSleepers);
    cfg.SetBoolValue("Aim", "IgnoreTeam", Vars::AimBot::IgnoreTeam);
    cfg.SetBoolValue("Aim", "IgnoreNpc", Vars::AimBot::IgnoreNpc);
#pragma endregion

#pragma region pSilent
    cfg.SetBoolValue("pSilent", "Enable", Vars::AimBot::pSilent);
    cfg.SetLongValue("pSilent", "Draw pSilent Fov", Vars::AimBot::DrawPSilentFov);
    cfg.SetLongValue("pSilent", "pSilent Fill Fov", Vars::AimBot::pSilentFillFov);
    cfg.SetLongValue("pSilent", "pSilent Fov Size", Vars::AimBot::pSilentFovSize);
    cfg.SetLongValue("pSilent", "Psilent Fov", Vars::AimBot::PSilentFov);
    cfg.SetLongValue("pSilent", "Psilent Distance", Vars::AimBot::LimitDist);
    cfg.SetBoolValue("pSilent", "HeliSilent", Vars::AimBot::HeliSilent);
    cfg.SetBoolValue("pSilent", "Always Headshot", Vars::AimBot::AlwaysHeadshot);
    cfg.SetBoolValue("pSilent", "Cleaning target", Vars::AimBot::SilentClear);
    cfg.SetBoolValue("pSilent", "Clear Button", Vars::AimBot::silentclearkey);
    cfg.SetBoolValue("pSilent", "Fat Bullet", Vars::AimBot::FatBullet2);
#pragma endregion

#pragma region AntiAim
    cfg.SetBoolValue("AntiAim", "AntiAim", Vars::Misc::AntiAim);
    cfg.SetLongValue("AntiAim", "Fakelag", Vars::Misc::FakeLag);
    cfg.SetLongValue("AntiAim", "Fakelag Ticks", Vars::Misc::FakeLagTicks);
#pragma endregion

#pragma region MainMisc
    cfg.SetBoolValue("Main", "AutoHeal(sometimes kick from the server)", Vars::Misc::FastHeal);
    cfg.SetBoolValue("Main", "InfinityJump", Vars::Misc::InfinityJump);
    cfg.SetBoolValue("Main", "JumpAiming", Vars::Misc::JumpAiming);
    cfg.SetBoolValue("Main", "LongHand", Vars::Misc::LongHand);
    cfg.SetBoolValue("Main", "FatHand", Vars::Misc::FatHand);
    cfg.SetBoolValue("Main", "LongNeck", Vars::Misc::LongNeck);
    cfg.SetBoolValue("Main", "LongNeck Key", Vars::Misc::lnkey);
    cfg.SetBoolValue("Main", "RunOnHit", Vars::Misc::RunOnHit);
    cfg.SetBoolValue("Main", "CanHoldItems", Vars::Misc::canHoldItems);
    cfg.SetBoolValue("Main", "SilentWalk", Vars::Misc::SilentWalk);
    cfg.SetBoolValue("Main", "SlideWalk", Vars::Misc::SlideWalk);
    cfg.SetBoolValue("Main", "Spoof OnLadder", Vars::Misc::Flyhack);
    cfg.SetBoolValue("Main", "SpiderMan", Vars::Misc::SpiderMan);
    cfg.SetBoolValue("Main", "AirStuck", Vars::Misc::AirStuck);
    cfg.SetBoolValue("Main", "AirStuck Key", Vars::Misc::airkey);
#pragma endregion

#pragma region WeaponMisk
    cfg.SetBoolValue("Weapon", "No Recoil", Vars::Misc::NoRecoil);
    cfg.SetBoolValue("Weapon", "YawMin", Vars::Misc::YawMin);
    cfg.SetBoolValue("Weapon", "YawMax", Vars::Misc::YawMax);
    cfg.SetBoolValue("Weapon", "No Spread", Vars::Misc::AntiSpread);
    cfg.SetBoolValue("Weapon", "NoHeavyReduct", Vars::Misc::NoHeavyReduct);
    cfg.SetBoolValue("Weapon", "NoBlockAiming", Vars::Misc::AntiKastrulya);
    cfg.SetBoolValue("Weapon", "Automatic", Vars::Misc::Automatic);
    cfg.SetBoolValue("Weapon", "No Sway", Vars::Misc::NoSway);
    cfg.SetBoolValue("Weapon", "100% EOKA", Vars::Misc::SuperEoka);
    cfg.SetBoolValue("Weapon", "Shot Gun No Spread", Vars::Misc::ShotGunTochka);
#pragma endregion

#pragma region WorldMisk
    cfg.SetLongValue("World", "AlwaysDay", Vars::Visuals::AlwaysDay);
    cfg.SetLongValue("World", "NightMode",Vars::Visuals::NightMode);
    cfg.SetLongValue("World", "FakeAdmin", Vars::Misc::NewFakeAdmin);
    cfg.SetLongValue("World", "ThirdPerson", Vars::Misc::ThirdPerson);
    cfg.SetLongValue("World", "AutoPickUp", Vars::Misc::AutoPickUp);
    cfg.SetLongValue("World", "Door", Vars::Misc::Door);
    cfg.SetLongValue("World", "WalkOnWater", Vars::Misc::WalkOnWater);
    cfg.SetLongValue("World", "WalkOnWater Key", Vars::Misc::walkkey);
    cfg.SetLongValue("World", "SpeedHack", Vars::Misc::speedhack);
    cfg.SetLongValue("World", "Speedhack Key", Vars::Misc::speedhackkey);
    cfg.SetLongValue("World", "CustomFov", Vars::Misc::CustomFov);
    cfg.SetLongValue("World", "Fov", Vars::Misc::FovRange);
    cfg.SetLongValue("World", "Default", Vars::Misc::Crosshair1);
    cfg.SetLongValue("World", "Circle", Vars::Misc::Crosshair2);
    cfg.SetLongValue("World", "Custom", Vars::Misc::CrosshairCustom);
    cfg.SetLongValue("World", "HitSound", Vars::Misc::HitSound);
#pragma endregion

#pragma region Player ESP
    cfg.SetLongValue("Player", "PlayerEsp", Vars::Visuals::PlayerESP);
    cfg.SetLongValue("Player", "Default", Vars::Visuals::ShowPlayerBox);
    cfg.SetLongValue("Player", "Corner", Vars::Visuals::ShowPlayerCornerBox);
    cfg.SetLongValue("Player", "Health", Vars::Visuals::ShowPlayerHealth);
    cfg.SetLongValue("Player", "Distance", Vars::Visuals::ShowPlayerDist);
    cfg.SetLongValue("Player", "Weapon", Vars::Visuals::ShowPlayerWeapon);
    cfg.SetLongValue("Player", "Skeleton", Vars::Visuals::SkeletonPlayer);
    cfg.SetLongValue("Player", "Ignore Sleepers", Vars::Visuals::IgnoreSleepers);
    cfg.SetLongValue("Player", "OwnChams", Vars::Visuals::ShowPlayerChams);
    cfg.SetLongValue("Player", "HandChams", Vars::Visuals::ShowHandChams);
    cfg.SetLongValue("Player", "ActiveSlot Dark", Vars::Visuals::ActiveSlot);
    cfg.SetLongValue("Player", "ActiveSlot Light", Vars::Visuals::ActiveSlotLight);
    cfg.SetLongValue("Player", "Pos X", Vars::Visuals::ActiveSlotPos_X);
    cfg.SetLongValue("Player", "Pos Y", Vars::Visuals::ActiveSlotPos_Y);
#pragma endregion

#pragma region Bots ESP
    cfg.SetLongValue("Bots", "BotEsp", Vars::Visuals::BotsESP);
    cfg.SetLongValue("Bots", "Default", Vars::Visuals::BotsBox);
    cfg.SetLongValue("Bots", "Corner", Vars::Visuals::BotsBoxCorner);
    cfg.SetLongValue("Bots", "Skeleton", Vars::Visuals::BotsSkeleton);
    cfg.SetLongValue("Bots", "Name", Vars::Visuals::BotsName);
    cfg.SetLongValue("Bots", "Distancy", Vars::Visuals::BotsDist);
    cfg.SetLongValue("Bots", "Weapon", Vars::Visuals::BotsWeapon);
    cfg.SetLongValue("Bots", "HealthBar", Vars::Visuals::BotsHealth);
    cfg.SetLongValue("Bots", "FillBox", Vars::Visuals::BotsFillBox);
#pragma endregion

#pragma region ResourcesESP
    cfg.SetBoolValue("Resources", "Sulphur", Vars::Visuals::Sulphur);
    cfg.SetBoolValue("Resources", "Sulphur Distance", Vars::Visuals::SulphurOreDistation);
    cfg.SetBoolValue("Resources", "Metal", Vars::Visuals::Metal);
    cfg.SetBoolValue("Resources", "Metal Distance", Vars::Visuals::MetalOreDistation);
    cfg.SetBoolValue("Resources", "Stone", Vars::Visuals::Stone);
    cfg.SetBoolValue("Resources", "Stone Distance", Vars::Visuals::StoneOreDistation);
#pragma endregion

#pragma region WorldEsp
      cfg.SetBoolValue("WorldEsp", "AirDrop", Vars::Visuals::Supply);
      cfg.SetBoolValue("WorldEsp", "AirDrop Distance", Vars::Visuals::SupplyDistation);
      cfg.SetLongValue("WorldEsp", "Chinook Crate", Vars::Visuals::Crate);
      cfg.SetBoolValue("WorldEsp", "Chinook Crate Distance", Vars::Visuals::CrateDistation);
      cfg.SetLongValue("WorldEsp", "Minicopters", Vars::Visuals::Minicopter);
      cfg.SetLongValue("WorldEsp", "Minicopters Distance", Vars::Visuals::MinicopterDistation);
      cfg.SetBoolValue("WorldEsp", "Scrap Copters", Vars::Visuals::ScrapCopter);
      cfg.SetLongValue("WorldEsp", "Scrap Copter Distance", Vars::Visuals::ScrapCopterDistation);
      cfg.SetLongValue("WorldEsp", "Boats", Vars::Visuals::Boat);
      cfg.SetBoolValue("WorldEsp", "Boat Distance", Vars::Visuals::BoatDistation);
      cfg.SetLongValue("WorldEsp", "RHIB's", Vars::Visuals::RHIB);
      cfg.SetLongValue("WorldEsp", "RHIB Distance", Vars::Visuals::RHIBDistation);
      cfg.SetBoolValue("WorldEsp", "Bardley", Vars::Visuals::Bardley);
      cfg.SetLongValue("WorldEsp", "Bardley Distance", Vars::Visuals::BardleylDistation);
      cfg.SetLongValue("WorldEsp", "Patrul", Vars::Visuals::Patrul);
      cfg.SetBoolValue("WorldEsp", "Patrul Distance", Vars::Visuals::PatrulDistation);
      cfg.SetLongValue("WorldEsp", "Auto Turrets", Vars::Visuals::AutoTurrets);
      cfg.SetBoolValue("WorldEsp", "Auto Turrets Distance", Vars::Visuals::AutoTurretsDistation);
      cfg.SetLongValue("WorldEsp", "Flame Turrets", Vars::Visuals::FlameTurrets);
      cfg.SetBoolValue("WorldEsp", "Flame Turrets Distance", Vars::Visuals::FlameTurretsDistation);
      cfg.SetLongValue("WorldEsp", "Shotgun Traps", Vars::Visuals::ShotgunTraps);
      cfg.SetBoolValue("WorldEsp", "Shotgun Traps Distance", Vars::Visuals::ShotgunTrapsDistation);
      cfg.SetLongValue("WorldEsp", "Land-Air Turret", Vars::Visuals::LandAirTurret);
      cfg.SetBoolValue("WorldEsp", "Land-Air Turret Distance", Vars::Visuals::LandAirTurretDistation);
      cfg.SetLongValue("WorldEsp", "Workbench1", Vars::House::workbench1);
      cfg.SetBoolValue("WorldEsp", "Workbench1 Distance", Vars::House::workbench1Distation);
      cfg.SetLongValue("WorldEsp", "Workbench2", Vars::House::workbench2);
      cfg.SetBoolValue("WorldEsp", "Workbench2 Distance", Vars::House::workbench2Distation);
      cfg.SetLongValue("WorldEsp", "Workbench3", Vars::House::workbench3);
      cfg.SetBoolValue("WorldEsp", "Workbench3 Distance", Vars::House::workbench3Distation);
      cfg.SetLongValue("WorldEsp", "Cupboard", Vars::House::cupboard);
      cfg.SetBoolValue("WorldEsp", "Cupboard Distance", Vars::House::cupboardDistation);
      cfg.SetLongValue("WorldEsp", "Chest", Vars::House::chest);
      cfg.SetBoolValue("WorldEsp", "Chest Distance", Vars::House::chestDistation);
      cfg.SetLongValue("WorldEsp", "Stash", Vars::Visuals::Stash);
      cfg.SetBoolValue("WorldEsp", "Stash Distance", Vars::Visuals::StashDistation);
      cfg.SetLongValue("WorldEsp", "Hemp", Vars::Visuals::Hemp);
      cfg.SetBoolValue("WorldEsp", "Hemp Distance", Vars::Visuals::HempDistation);
      cfg.SetLongValue("WorldEsp", "Corpse", Vars::Visuals::Corpse);
      cfg.SetBoolValue("WorldEsp", "Corpse Distance", Vars::Visuals::CorpseDistation);
#pragma endregion 

#pragma region Color
    SaveColorValue("Color", "Box", Vars::Color::BoxColor);
    SaveColorValue("Color", "Skeleton", Vars::Color::SkeletonColor);
    SaveColorValue("Color", "Name", Vars::Color::NameColor);
    SaveColorValue("Color", "Weapon", Vars::Color::WeaponColor);
    SaveColorValue("Color", "Distance", Vars::Color::DistanceColor);
    SaveColorValue("Color", "Fov", Vars::Color::Fov);
    SaveColorValue("Color", "pSilentFov", Vars::Color::PSilentFovColor);
    SaveColorValue("Color", "CrossHair", Vars::Color::CrosshairColor);
    SaveColorValue("Color", "Bot Box", Vars::Color::BotBoxEsp);
    SaveColorValue("Color", "Bot Skeleton", Vars::Color::BotsSkeletonEsp);
    SaveColorValue("Color", "Bot Name", Vars::Color::BotNameEsp);
    SaveColorValue("Color", "Bot Weapon", Vars::Color::BotWeaponEsp);
    SaveColorValue("Color", "Bot Distance", Vars::Color::BotDistEsp);
    SaveColorValue("Color", "Sulfur", Vars::Color::SulfurEsp);
    SaveColorValue("Color", "Metal", Vars::Color::MetalEsp);
    SaveColorValue("Color", "Stone", Vars::Color::StoneEsp);
    SaveColorValue("Color", "AirDrop", Vars::Color::SupplyEsp);
    SaveColorValue("Color", "Crate", Vars::Color::CrateEsp);
    SaveColorValue("Color", "Minicopter", Vars::Color::MinicopterEsp);
    SaveColorValue("Color", "ScrapCopter", Vars::Color::ScrapCopterEsp);
    SaveColorValue("Color", "Boat", Vars::Color::BoatEsp);
    SaveColorValue("Color", "RHIB", Vars::Color::RHIBEsp);
    SaveColorValue("Color", "Patrul", Vars::Color::PatrulEsp);
    SaveColorValue("Color", "Bardley", Vars::Color::BardleyEsp);
    SaveColorValue("Color", "ShotgunTrap", Vars::Color::ShotgunTrapsEsp);
    SaveColorValue("Color", "AutoTurret", Vars::Color::AutoTurretsEsp);
    SaveColorValue("Color", "FlameTurret", Vars::Color::FlameTurretsEsp);
    SaveColorValue("Color", "LandAirTurret", Vars::Color::LandAirTurretEsp);
    SaveColorValue("Color", "Workbench1", Vars::Color::Workbench1Esp);
    SaveColorValue("Color", "Workbench2", Vars::Color::Workbench2Esp);
    SaveColorValue("Color", "Workbench3", Vars::Color::Workbench3Esp);
    SaveColorValue("Color", "Cupboard", Vars::Color::CupboardEsp);
    SaveColorValue("Color", "Chest", Vars::Color::ChestEsp);
    SaveColorValue("Color", "Hemp", Vars::Color::HempEsp);
    SaveColorValue("Color", "Stash", Vars::Color::StashEsp);
    SaveColorValue("Color", "Corpse", Vars::Color::CorpseEsp);
#pragma endregion

#pragma region Radar
     cfg.SetBoolValue("Radar", "Enable", Vars::Radar::Enable);
     cfg.SetBoolValue("Radar", "Show Radar Background", Vars::Radar::ShowRadarBackground);
     cfg.SetBoolValue("Radar", "Show Radar Player", Vars::Radar::ShowRadarPlayer);
     cfg.SetBoolValue("Radar", "Show Radar Sleeper", Vars::Radar::ShowRadarSleeper);
     cfg.SetLongValue("Radar", "Pos X", Vars::Radar::Pos_X);
     cfg.SetLongValue("Radar", "Pos Y", Vars::Radar::Pos_Y);
     cfg.SetLongValue("Radar", "Radar Size", Vars::Radar::Radar_Size);
     cfg.SetLongValue("Radar", "Radar Range", Vars::Radar::Radar_Range);
#pragma endregion

    cfg.SaveFile(result);
}

void LoadCFG(const char* FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, "C:\\Windows\\Temp\\{%lu}\\", SerialNumber);

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, "C:\\Windows\\Temp\\{%lu}\\%s.ini", SerialNumber, FileName);
    cfg.LoadFile(result);

#pragma region AimBot
    cfg.SetBoolValue("Aim", "Enable", Vars::AimBot::Activate);
    cfg.SetLongValue("Aim", "Aim Bot Key", Vars::AimBot::aimkey);
    cfg.SetLongValue("Aim", "Distance", Vars::AimBot::Range);
    cfg.SetLongValue("Aim", "Fov", Vars::AimBot::Fov);
    cfg.SetLongValue("Aim", "Fov Size", Vars::AimBot::FovSize);
    cfg.SetLongValue("Aim", "Fill Fov", Vars::AimBot::FillFov);
    cfg.SetBoolValue("Aim", "Recoil Control System", Vars::AimBot::RCS);
    cfg.SetBoolValue("Aim", "RCS Standalone", Vars::AimBot::Standalone);
    cfg.SetBoolValue("Aim", "Show Fov", Vars::AimBot::DrawFov);
    cfg.SetBoolValue("Aim", "Visible Check", Vars::AimBot::VisibleCheck);
    cfg.SetBoolValue("Aim", "Body Aim", Vars::AimBot::BodyAim);
    cfg.SetBoolValue("Aim", "IgnoreSleepers", Vars::AimBot::IgnoreSleepers);
    cfg.SetBoolValue("Aim", "IgnoreTeam", Vars::AimBot::IgnoreTeam);
    cfg.SetBoolValue("Aim", "IgnoreNpc", Vars::AimBot::IgnoreNpc);
#pragma endregion

#pragma region pSilent
    cfg.SetBoolValue("pSilent", "Enable", Vars::AimBot::pSilent);
    cfg.SetLongValue("pSilent", "Draw pSilent Fov", Vars::AimBot::DrawPSilentFov);
    cfg.SetLongValue("pSilent", "pSilent Fill Fov", Vars::AimBot::pSilentFillFov);
    cfg.SetLongValue("pSilent", "pSilent Fov Size", Vars::AimBot::pSilentFovSize);
    cfg.SetLongValue("pSilent", "Psilent Fov", Vars::AimBot::PSilentFov);
    cfg.SetLongValue("pSilent", "Psilent Distance", Vars::AimBot::LimitDist);
    cfg.SetBoolValue("pSilent", "HeliSilent", Vars::AimBot::HeliSilent);
    cfg.SetBoolValue("pSilent", "Always Headshot", Vars::AimBot::AlwaysHeadshot);
    cfg.SetBoolValue("pSilent", "Cleaning target", Vars::AimBot::SilentClear);
    cfg.SetBoolValue("pSilent", "Clear Button", Vars::AimBot::silentclearkey);
    cfg.SetBoolValue("pSilent", "Fat Bullet", Vars::AimBot::FatBullet2);
#pragma endregion

#pragma region AntiAim
    cfg.SetBoolValue("AntiAim", "AntiAim", Vars::Misc::AntiAim);
    cfg.SetLongValue("AntiAim", "Fakelag", Vars::Misc::FakeLag);
    cfg.SetLongValue("AntiAim", "Fakelag Ticks", Vars::Misc::FakeLagTicks);
#pragma endregion

#pragma region MainMisc
    cfg.SetBoolValue("Main", "AutoHeal(sometimes kick from the server)", Vars::Misc::FastHeal);
    cfg.SetBoolValue("Main", "InfinityJump", Vars::Misc::InfinityJump);
    cfg.SetBoolValue("Main", "JumpAiming", Vars::Misc::JumpAiming);
    cfg.SetBoolValue("Main", "LongHand", Vars::Misc::LongHand);
    cfg.SetBoolValue("Main", "FatHand", Vars::Misc::FatHand);
    cfg.SetBoolValue("Main", "LongNeck", Vars::Misc::LongNeck);
    cfg.SetBoolValue("Main", "LongNeck Key", Vars::Misc::lnkey);
    cfg.SetBoolValue("Main", "RunOnHit", Vars::Misc::RunOnHit);
    cfg.SetBoolValue("Main", "CanHoldItems", Vars::Misc::canHoldItems);
    cfg.SetBoolValue("Main", "SilentWalk", Vars::Misc::SilentWalk);
    cfg.SetBoolValue("Main", "SlideWalk", Vars::Misc::SlideWalk);
    cfg.SetBoolValue("Main", "Spoof OnLadder", Vars::Misc::Flyhack);
    cfg.SetBoolValue("Main", "SpiderMan", Vars::Misc::SpiderMan);
    cfg.SetBoolValue("Main", "AirStuck", Vars::Misc::AirStuck);
    cfg.SetBoolValue("Main", "AirStuck Key", Vars::Misc::airkey);
#pragma endregion

#pragma region WeaponMisk
    cfg.SetBoolValue("Weapon", "No Recoil", Vars::Misc::NoRecoil);
    cfg.SetBoolValue("Weapon", "YawMin", Vars::Misc::YawMin);
    cfg.SetBoolValue("Weapon", "YawMax", Vars::Misc::YawMax);
    cfg.SetBoolValue("Weapon", "No Spread", Vars::Misc::AntiSpread);
    cfg.SetBoolValue("Weapon", "NoHeavyReduct", Vars::Misc::NoHeavyReduct);
    cfg.SetBoolValue("Weapon", "NoBlockAiming", Vars::Misc::AntiKastrulya);
    cfg.SetBoolValue("Weapon", "Automatic", Vars::Misc::Automatic);
    cfg.SetBoolValue("Weapon", "No Sway", Vars::Misc::NoSway);
    cfg.SetBoolValue("Weapon", "100% EOKA", Vars::Misc::SuperEoka);
    cfg.SetBoolValue("Weapon", "Shot Gun No Spread", Vars::Misc::ShotGunTochka);
#pragma endregion

#pragma region WorldMisk
    Vars::Radar::Enable = cfg.SetLongValue("World", "AlwaysDay", Vars::Visuals::AlwaysDay);
    Vars::Radar::Enable = cfg.SetLongValue("World", "NightMode", Vars::Visuals::NightMode);
    Vars::Radar::Enable = cfg.SetLongValue("World", "FakeAdmin", Vars::Misc::NewFakeAdmin);
    Vars::Radar::Enable = cfg.SetLongValue("World", "ThirdPerson", Vars::Misc::ThirdPerson);
    Vars::Radar::Enable = cfg.SetLongValue("World", "AutoPickUp", Vars::Misc::AutoPickUp);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Door", Vars::Misc::Door);
    Vars::Radar::Enable = cfg.SetLongValue("World", "WalkOnWater", Vars::Misc::WalkOnWater);
    Vars::Radar::Enable = cfg.SetLongValue("World", "WalkOnWater Key", Vars::Misc::walkkey);
    Vars::Radar::Enable = cfg.SetLongValue("World", "SpeedHack", Vars::Misc::speedhack);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Speedhack Key", Vars::Misc::speedhackkey);
    Vars::Radar::Enable = cfg.SetLongValue("World", "CustomFov", Vars::Misc::CustomFov);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Fov", Vars::Misc::FovRange);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Default", Vars::Misc::Crosshair1);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Circle", Vars::Misc::Crosshair2);
    Vars::Radar::Enable = cfg.SetLongValue("World", "Custom", Vars::Misc::CrosshairCustom);
    Vars::Radar::Enable = cfg.SetLongValue("World", "HitSound", Vars::Misc::HitSound);
#pragma endregion

#pragma region Player ESP
    Vars::Visuals::PlayerESP = cfg.GetLongValue("Player", "PlayerEsp", Vars::Visuals::PlayerESP);
    Vars::Visuals::ShowPlayerBox = cfg.GetLongValue("Player", "Default", Vars::Visuals::ShowPlayerBox);
    Vars::Visuals::ShowPlayerCornerBox = cfg.GetLongValue("Player", "Corner", Vars::Visuals::ShowPlayerCornerBox);
    Vars::Visuals::ShowPlayerHealth = cfg.GetLongValue("Player", "Health", Vars::Visuals::ShowPlayerHealth);
    Vars::Visuals::ShowPlayerDist = cfg.GetLongValue("Player", "Distance", Vars::Visuals::ShowPlayerDist);
    Vars::Visuals::ShowPlayerWeapon = cfg.GetLongValue("Player", "Weapon", Vars::Visuals::ShowPlayerWeapon);
    Vars::Visuals::SkeletonPlayer = cfg.GetLongValue("Player", "Skeleton", Vars::Visuals::SkeletonPlayer);
    Vars::Visuals::IgnoreSleepers = cfg.GetLongValue("Player", "Ignore Sleepers", Vars::Visuals::IgnoreSleepers);
    Vars::Visuals::ShowPlayerChams = cfg.GetLongValue("Player", "OwnChams", Vars::Visuals::ShowPlayerChams);
    Vars::Visuals::ShowHandChams = cfg.GetLongValue("Player", "HandChams", Vars::Visuals::ShowHandChams);
    Vars::Visuals::ActiveSlot = cfg.GetLongValue("Player", "ActiveSlot Dark", Vars::Visuals::ActiveSlot);
    Vars::Visuals::ActiveSlotLight = cfg.GetLongValue("Player", "ActiveSlot Light", Vars::Visuals::ActiveSlotLight);
    Vars::Visuals::ActiveSlotPos_X = cfg.GetLongValue("Player", "Pos X", Vars::Visuals::ActiveSlotPos_X);
    Vars::Visuals::ActiveSlotPos_Y = cfg.GetLongValue("Player", "Pos Y", Vars::Visuals::ActiveSlotPos_Y);
#pragma endregion

#pragma region Bots ESP
    Vars::Visuals::BotsESP = cfg.GetLongValue("Bots", "BotEsp", Vars::Visuals::BotsESP);
    Vars::Visuals::BotsBox = cfg.GetLongValue("Bots", "Default", Vars::Visuals::BotsBox);
    Vars::Visuals::BotsBoxCorner = cfg.GetLongValue("Bots", "Corner", Vars::Visuals::BotsBoxCorner);
    Vars::Visuals::BotsSkeleton = cfg.GetLongValue("Bots", "Skeleton", Vars::Visuals::BotsSkeleton);
    Vars::Visuals::BotsName = cfg.GetLongValue("Bots", "Name", Vars::Visuals::BotsName);
    Vars::Visuals::BotsDist = cfg.GetLongValue("Bots", "Distancy", Vars::Visuals::BotsDist);
    Vars::Visuals::BotsWeapon = cfg.GetLongValue("Bots", "Weapon", Vars::Visuals::BotsWeapon);
    Vars::Visuals::BotsHealth = cfg.GetLongValue("Bots", "HealthBar", Vars::Visuals::BotsHealth);
    Vars::Visuals::BotsFillBox = cfg.GetLongValue("Bots", "FillBox", Vars::Visuals::BotsFillBox);
#pragma endregion

#pragma region ResourcesESP
    Vars::Visuals::Sulphur = cfg.GetBoolValue("Resources", "Sulphur", Vars::Visuals::Sulphur);
    Vars::Visuals::SulphurOreDistation = cfg.GetBoolValue("Resources", "Sulphur Distance", Vars::Visuals::SulphurOreDistation);
    Vars::Visuals::Metal = cfg.GetBoolValue("Resources", "Metal", Vars::Visuals::Metal);
    Vars::Visuals::MetalOreDistation = cfg.GetBoolValue("Resources", "Metal Distance", Vars::Visuals::MetalOreDistation);
    Vars::Visuals::Stone = cfg.GetBoolValue("Resources", "Stone", Vars::Visuals::Stone);
    Vars::Visuals::StoneOreDistation = cfg.GetBoolValue("Resources", "Stone Distance", Vars::Visuals::StoneOreDistation);
#pragma endregion

#pragma region WorldEsp
    Vars::Visuals::Supply = cfg.GetBoolValue("WorldEsp", "AirDrop", Vars::Visuals::Supply);
    Vars::Visuals::SupplyDistation = cfg.GetBoolValue("WorldEsp", "AirDrop Distance", Vars::Visuals::SupplyDistation);
    Vars::Visuals::Crate = cfg.GetLongValue("WorldEsp", "Chinook Crate", Vars::Visuals::Crate);
    Vars::Visuals::CrateDistation = cfg.GetBoolValue("WorldEsp", "Chinook Crate Distance", Vars::Visuals::CrateDistation);
    Vars::Visuals::Minicopter = cfg.GetLongValue("WorldEsp", "Minicopters", Vars::Visuals::Minicopter);
    Vars::Visuals::MinicopterDistation = cfg.GetLongValue("WorldEsp", "Minicopters Distance", Vars::Visuals::MinicopterDistation);
    Vars::Visuals::ScrapCopter = cfg.GetBoolValue("WorldEsp", "Scrap Copters", Vars::Visuals::ScrapCopter);
    Vars::Visuals::ScrapCopterDistation = cfg.GetLongValue("WorldEsp", "Scrap Copter Distance", Vars::Visuals::ScrapCopterDistation);
    Vars::Visuals::Boat = cfg.GetLongValue("WorldEsp", "Boats", Vars::Visuals::Boat);
    Vars::Visuals::BoatDistation = cfg.GetBoolValue("WorldEsp", "Boat Distance", Vars::Visuals::BoatDistation);
    Vars::Visuals::RHIB = cfg.GetLongValue("WorldEsp", "RHIB's", Vars::Visuals::RHIB);
    Vars::Visuals::RHIBDistation = cfg.GetLongValue("WorldEsp", "RHIB Distance", Vars::Visuals::RHIBDistation);
    Vars::Visuals::Bardley = cfg.GetBoolValue("WorldEsp", "Bardley", Vars::Visuals::Bardley);
    Vars::Visuals::BardleylDistation = cfg.GetLongValue("WorldEsp", "Bardley Distance", Vars::Visuals::BardleylDistation);
    Vars::Visuals::Patrul = cfg.GetLongValue("WorldEsp", "Patrul", Vars::Visuals::Patrul);
    Vars::Visuals::PatrulDistation = cfg.GetBoolValue("WorldEsp", "Patrul Distance", Vars::Visuals::PatrulDistation);
    Vars::Visuals::AutoTurrets = cfg.GetLongValue("WorldEsp", "Auto Turrets", Vars::Visuals::AutoTurrets);
    Vars::Visuals::AutoTurretsDistation = cfg.GetBoolValue("WorldEsp", "Auto Turrets Distance", Vars::Visuals::AutoTurretsDistation);
    Vars::Visuals::FlameTurrets = cfg.GetLongValue("WorldEsp", "Flame Turrets", Vars::Visuals::FlameTurrets);
    Vars::Visuals::FlameTurretsDistation = cfg.GetBoolValue("WorldEsp", "Flame Turrets Distance", Vars::Visuals::FlameTurretsDistation);
    Vars::Visuals::ShotgunTraps = cfg.GetLongValue("WorldEsp", "Shotgun Traps", Vars::Visuals::ShotgunTraps);
    Vars::Visuals::ShotgunTrapsDistation = cfg.GetBoolValue("WorldEsp", "Shotgun Traps Distance", Vars::Visuals::ShotgunTrapsDistation);
    Vars::Visuals::LandAirTurret = cfg.GetLongValue("WorldEsp", "Land-Air Turret", Vars::Visuals::LandAirTurret);
    Vars::Visuals::LandAirTurretDistation = cfg.GetBoolValue("WorldEsp", "Land-Air Turret Distance", Vars::Visuals::LandAirTurretDistation);
    Vars::House::workbench1 = cfg.GetLongValue("WorldEsp", "Workbench1", Vars::House::workbench1);
    Vars::House::workbench1Distation = cfg.GetBoolValue("WorldEsp", "Workbench1 Distance", Vars::House::workbench1Distation);
    Vars::House::workbench2 = cfg.GetLongValue("WorldEsp", "Workbench2", Vars::House::workbench2);
    Vars::House::workbench2Distation = cfg.GetBoolValue("WorldEsp", "Workbench2 Distance", Vars::House::workbench2Distation);
    Vars::House::workbench3 = cfg.GetLongValue("WorldEsp", "Workbench3", Vars::House::workbench3);
    Vars::House::workbench3Distation = cfg.GetBoolValue("WorldEsp", "Workbench3 Distance", Vars::House::workbench3Distation);
    Vars::House::cupboard = cfg.GetLongValue("WorldEsp", "Cupboard", Vars::House::cupboard);
    Vars::House::cupboardDistation = cfg.GetBoolValue("WorldEsp", "Cupboard Distance", Vars::House::cupboardDistation);
    Vars::House::chest = cfg.GetLongValue("WorldEsp", "Chest", Vars::House::chest);
    Vars::House::chestDistation = cfg.GetBoolValue("WorldEsp", "Chest Distance", Vars::House::chestDistation);
    Vars::Visuals::Stash = cfg.GetLongValue("WorldEsp", "Stash", Vars::Visuals::Stash);
    Vars::Visuals::StashDistation = cfg.GetBoolValue("WorldEsp", "Stash Distance", Vars::Visuals::StashDistation);
    Vars::Visuals::Hemp = cfg.GetLongValue("WorldEsp", "Hemp", Vars::Visuals::Hemp);
    Vars::Visuals::HempDistation = cfg.GetBoolValue("WorldEsp", "Hemp Distance", Vars::Visuals::HempDistation);
    Vars::Visuals::Corpse = cfg.GetLongValue("WorldEsp", "Corpse", Vars::Visuals::Corpse);
    Vars::Visuals::CorpseDistation = cfg.GetBoolValue("WorldEsp", "Corpse Distance", Vars::Visuals::CorpseDistation);
#pragma endregion 

#pragma region Color
    LoadColorValue("Color", "Box", Vars::Color::BoxColor);
    LoadColorValue("Color", "Skeleton", Vars::Color::SkeletonColor);
    LoadColorValue("Color", "Name", Vars::Color::NameColor);
    LoadColorValue("Color", "Weapon", Vars::Color::WeaponColor);
    LoadColorValue("Color", "Distance", Vars::Color::DistanceColor);
    LoadColorValue("Color", "Fov", Vars::Color::Fov);
    LoadColorValue("Color", "pSilentFov", Vars::Color::PSilentFovColor);
    LoadColorValue("Color", "CrossHair", Vars::Color::CrosshairColor);
    LoadColorValue("Color", "Bot Box", Vars::Color::BotBoxEsp);
    LoadColorValue("Color", "Bot Skeleton", Vars::Color::BotsSkeletonEsp);
    LoadColorValue("Color", "Bot Name", Vars::Color::BotNameEsp);
    LoadColorValue("Color", "Bot Weapon", Vars::Color::BotWeaponEsp);
    LoadColorValue("Color", "Bot Distance", Vars::Color::BotDistEsp);
    LoadColorValue("Color", "Sulfur", Vars::Color::SulfurEsp);
    LoadColorValue("Color", "Metal", Vars::Color::MetalEsp);
    LoadColorValue("Color", "Stone", Vars::Color::StoneEsp);
    LoadColorValue("Color", "AirDrop", Vars::Color::SupplyEsp);
    LoadColorValue("Color", "Crate", Vars::Color::CrateEsp);
    LoadColorValue("Color", "Minicopter", Vars::Color::MinicopterEsp);
    LoadColorValue("Color", "ScrapCopter", Vars::Color::ScrapCopterEsp);
    LoadColorValue("Color", "Boat", Vars::Color::BoatEsp);
    LoadColorValue("Color", "RHIB", Vars::Color::RHIBEsp);
    LoadColorValue("Color", "Patrul", Vars::Color::PatrulEsp);
    LoadColorValue("Color", "Bardley", Vars::Color::BardleyEsp);
    LoadColorValue("Color", "ShotgunTrap", Vars::Color::ShotgunTrapsEsp);
    LoadColorValue("Color", "AutoTurret", Vars::Color::AutoTurretsEsp);
    LoadColorValue("Color", "FlameTurret", Vars::Color::FlameTurretsEsp);
    LoadColorValue("Color", "LandAirTurret", Vars::Color::LandAirTurretEsp);
    LoadColorValue("Color", "Workbench1", Vars::Color::Workbench1Esp);
    LoadColorValue("Color", "Workbench2", Vars::Color::Workbench2Esp);
    LoadColorValue("Color", "Workbench3", Vars::Color::Workbench3Esp);
    LoadColorValue("Color", "Cupboard", Vars::Color::CupboardEsp);
    LoadColorValue("Color", "Chest", Vars::Color::ChestEsp);
    LoadColorValue("Color", "Hemp", Vars::Color::HempEsp);
    LoadColorValue("Color", "Stash", Vars::Color::StashEsp);
    LoadColorValue("Color", "Corpse", Vars::Color::CorpseEsp);
#pragma endregion

#pragma region Radar
    Vars::Radar::Enable = cfg.GetBoolValue("Radar", "Enable", Vars::Radar::Enable);
    Vars::Radar::ShowRadarBackground = cfg.GetBoolValue("Radar", "Show Radar Background", Vars::Radar::ShowRadarBackground);
    Vars::Radar::ShowRadarPlayer = cfg.GetBoolValue("Radar", "Show Radar Player", Vars::Radar::ShowRadarPlayer);
    Vars::Radar::ShowRadarSleeper = cfg.GetBoolValue("Radar", "Show Radar Sleeper", Vars::Radar::ShowRadarSleeper);
    Vars::Radar::Pos_X = cfg.GetLongValue("Radar", "Pos X", Vars::Radar::Pos_X);
    Vars::Radar::Pos_Y = cfg.GetLongValue("Radar", "Pos Y", Vars::Radar::Pos_Y);
    Vars::Radar::Radar_Size = cfg.GetLongValue("Radar", "Radar Size", Vars::Radar::Radar_Size);
    Vars::Radar::Radar_Range = cfg.GetLongValue("Radar", "Radar Range", Vars::Radar::Radar_Range);
#pragma endregion
};