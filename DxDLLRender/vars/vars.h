
uintptr_t closestHeli;
namespace Vars
{
	namespace Tabs
	{
		bool Aim, Silent, ESP, BOTESP, OtherESP, Player, Weapon, Color, Config = false;
		bool Preview = false;
	}
	namespace Global
	{
		
		Vector2 MenuPos = { 0, 0 };
		bool Panic = false;
		int PanicKey = 0;
		int MenuKey = 0;
		float ScreenHigh = 0;
		float ScreenWidth = 0;
		HWND hWindow = nullptr;
		bool MenuVisible = false;
		WNDPROC oWindproc = nullptr;

		Vector3 LastPos = { 0.f, 0.f, 0.f };
		ULONGLONG LastTime = 0;
		DWORD64 LastSteamID = 0;
		const wchar_t* LastName;
		Vector3 PlayerVeloc = { 0.f, 0.f, 0.f };

		int BoneToAim = 1;
		float BulletSpeed = 250.f;
		DWORD64 PresentDelta = 0;
		float CorX = 0.f;
		float CorY = 0.f;
		char ConfigName[0x100] = "Config";
	}
	namespace Test
	{

	}
	namespace Storage
	{
		__declspec(selectany) uintptr_t gBase = (DWORD64)GetModuleHandleA("GameAssembly.dll");
		__declspec(selectany) uintptr_t closestPlayer = NULL;
		__declspec(selectany) uintptr_t uBase = NULL;
		
	}
	namespace AimBot
	{
		
		bool pSilent = false;
		bool HeliSilent = false;
		bool DrawPSilentFov = false;
		bool pSilentFillFov = false;
		float pSilentFovSize = 10.f;

		
		float PSilentFov = 100.f;
		float LimitDist = 300.f;
		bool PSilentClear = false;
		int Psilentclearkey = 0;
		
		bool FatBullet2 = false;//Set_Psilent
		bool FatBullet = false;//Set_Psilent
		bool FastBullet = false;
		float SpeedBullet = 10.f;
		bool Fake_Dist = false;
		float distancefake = 500.f;
		bool Activate = false;
		bool RightMouseAiming = false;
		bool BodyAim = false;
		bool RCS = false;
		bool Standalone = false;
		bool DoMeleeAttack = false;
		bool AimHead = false;
		bool VisibleCheck = false;
		bool IgnoreSleepers = false;
		bool IgnoreTeam = false;
		bool IgnoreNpc = false;
		bool DrawFov = false;
		bool FillFov = false;
		
		float Range = 400.f;
		float Fov = 100.f;
		float FovSize = 10.f;

		int aimkey = 0;
		static int keystatus = 0;
		bool toggleaim = false;
		bool SilentBody = false;
		bool EnableSilentAim = false;
		bool AlwaysHeadshot = false;
		bool psilentAlwaysHeadshot = false;
		bool psilentAlwaysBody = false;
		bool ThroughWall = false;
		bool DrawSilentFov = false;
		float SilentDist = 500.f;
		float SilentFov = 100.f;
		bool SilentIgnoreBot = false;
		bool SilentIgnoreSleep = false;
		bool SilentIgnoreWounded = false;
		bool SilentClear = false;
		int silentclearkey = 0;
		float Velocity = 1.480f;

	}

	namespace Visuals
	{
		bool PlayerESP = false;
		bool FillBox = false;
		bool ShowPlayerChams = false;
		bool ShowHandChams = false;
		bool ShowPlayerBox = false;
		bool ShowPlayerName = false;
		bool ShowPlayerHealth = false;
		bool ShowPlayerHealthBar = false;
		bool ShowPlayerHealthBarBottom = false;
		bool ShowPlayerWeapon = false;
		bool ShowPlayerDist = false;
		bool ShowPlayerCornerBox = false;
		//bool CSnapLines = false;
		bool AlwaysDay = false;
		bool NightMode = false;
		bool IgnoreSleepers = false;
		bool SkeletonPlayer = false;
		bool Tracers = false;
		bool TracersBottom = false;
		bool TargetTracers = false;
		namespace Preview
		{
			bool Box, Health, Name, Weapon, Dist = false;
		}
		bool BotsESP = false;
		bool BotsHealth = false;
		bool BotsHealthBar = false;
		bool BotsBox = false;
		bool BotsBoxCorner = false;
		bool BotsSkeleton = false;
		bool BotsWeapon = false;
		bool BotsDist = false;
		bool BotsName = false;
		bool BotsFillBox = false;

		float ActiveSlotPos_X = 0.f;
		float ActiveSlotPos_Y = 0.f;
		bool ActiveSlot = false;
		bool ActiveSlotLight = false;
	}

	namespace GG
	{
		bool rainbow = false;
		float RbTime = 1.0f;
	}

	namespace Misc
	{
		bool AdminTools = false;
		bool MeleeAimPlayers = false;
		bool MeleeAutoFarm = false;
		bool Door = false;
		bool RapidFire = false;
		bool LongNeck = false;
		int lnkey = 0;
		bool AutoPickUp = false;
		bool FastHeal = false;

		bool FakeLag = false;
		float FakeLagTicks = 0.f;
		bool AntiAim = false;

		bool Noplayercollision = false;

		bool Zoom = false;
		int zoomkey = 0;
		bool SlideWalk = false;
		bool SilentWalk = false;
		bool Flyhack = false;
		bool ShotGunTochka = false;
		bool CustomTime = false;
		float Time = 1.0f;
		bool CustomFov = false; //Camera
		float FovRange = 90.f;
		float pred = 0.f;
		bool SpiderMan = false;
		bool InfinityJump = false;
		bool AntiSpread = false;
		bool NoRecoil = false;
		float YawMin = 0.f;
		float YawMax = 0.f;
		bool FastReload = false;
		bool OmniSpread = false;
		bool canHoldItems = false;
		bool Automatic = false;
		bool FastCompBow = false;
		bool FastMeele = false;
		bool SuperEoka = false;
		bool SkinChanger = false;
		bool BuildAsUWant = false;
		int buildkey = 0;
		bool NoSway = false;
		bool SuperBow = false;
		bool FakeAdmin = false; //need
		bool NewFakeAdmin = false; 
		bool NewSwimOnGround = false;
		bool SwimOnGround = false;
		float SetSwim = 0.f;
		bool ThirdPerson = false;
		bool LongHand = false;
		bool FatHand = false;
		bool RunOnHit = false;
		bool speedhack = false;
		int speedhackkey = 0;
		bool SpeedHack = false;
		float SpeedValue = 5;
		bool JumpAiming = false;
		int highkey = 0;
		////////////////////////////
		bool WalkOnWater = false;
		int walkkey = 0;
		///////////////////////////
		float JumpValue = 1.0f;
		bool NoFall = false;
		bool AirStuck = false;
		int  airkey = 0;
		bool AntiKastrulya = false;
		bool NoHeavyReduct = false;
		//meme dot

		bool Crosshair1 = false;
		bool Crosshair2 = false;
		bool CrosshairCustom = false;
		float X = 100.f;
		float Y = 100.f;

		bool HitSound = false;

	}

	namespace HvH
	{
		float Tick = 2.3f;
		float Tick2 = 2.3f;
		float FOV = 0.5f;
	}

	namespace Visuals
	{
		bool ore = false;
		bool EnableBoxResourses = false;
		bool Sulphur = false;
		float SulphurOreDistation = 2500.f;
		bool Metal = false;
		float MetalOreDistation = 2500.f;
		bool Stone = false;
		float StoneOreDistation = 2500.f;
		bool Stash = false;
		float StashDistation = 2500.f;
		bool Minicopter = false;
		float MinicopterDistation = 2500.f;
		bool ScrapCopter = false;
		float ScrapCopterDistation = 2500.f;
		bool Boat = false;
		float BoatDistation = 2500.f;
		bool RHIB = false;
		float RHIBDistation = 2500.f;
		bool Patrul = false;
		float PatrulDistation = 2500.f;
		bool Bardley = false;
		float BardleylDistation = 2500.f;
		bool ShotgunTraps = false;
		float ShotgunTrapsDistation = 2500.f;
		bool AutoTurrets = false;
		float AutoTurretsDistation = 2500.f;
		bool FlameTurrets = false;
		float FlameTurretsDistation = 2500.f;
		bool LandAirTurret = false;
		float LandAirTurretDistation = 2500.f;
		bool Hemp = false;
		float HempDistation = 2500.f;
		bool Supply = false;
		float SupplyDistation = 2500.f;
		bool Corpse = false;
		float CorpseDistation = 2500.f;
		bool Crate = false;
		float CrateDistation = 2500.f;
		
		
		//
		bool show_Weapons = false;
		float show_WeaponsDistation = 100.f;

	}

	namespace House
	{
		bool workbench1 = false;
		float workbench1Distation = 2500.f;
		bool workbench2 = false;
		float workbench2Distation = 2500.f;
		bool workbench3 = false;
		float workbench3Distation = 2500.f;
		bool cupboard = false;
		float cupboardDistation = 2500.f;
		bool chest = false;
		float chestDistation = 2500.f;
	}

	namespace Drop
	{
		bool Activate = false;
		bool supply_drop = false;
		bool WoodBox_bacpack = false;
		bool closestPlayer = false;
		bool inventoryESP = false;
	}

	namespace PicUpEsp
	{
		bool Activate = false;
		bool StonePicUp = false;
		bool MetalPicUp = false;
		bool SulfurPicUp = false;
		bool WoodPicUp = false;
		bool hempEsp = false;
	}

	namespace Color {
		float CSnapColor[] = { 255.f,255.f,255.f,255.f };
		
		float Fov[] = { 255.f, 255.f, 255.f };
		float PSilentFovColor[] = { 0.f, 0.f, 0.f };
		float SilentFovColor[] = { 0.f, 0.f, 0.f };
		float TriggerFovColor[] = { 0.f, 0.f, 0.f };

		
		/// <summary>
		float StoneEsp[] = { 255.f, 0.f, 0.f };
		float SulfurEsp[] = { 255.f, 0.f, 0.f };
		float MetalEsp[] = { 255.f, 0.f, 0.f };
		float StashEsp[] = { 255.f, 0.f, 0.f };
		float MinicopterEsp[] = { 255.f, 0.f, 0.f };
		float ScrapCopterEsp[] = { 255.f, 0.f, 0.f };
		float BoatEsp[] = { 255.f, 0.f, 0.f };
		float RHIBEsp[] = { 255.f, 0.f, 0.f };
		float PatrulEsp[] = { 255.f, 0.f, 0.f };
		float BardleyEsp[] = { 255.f, 0.f, 0.f };
		float ShotgunTrapsEsp[] = { 255.f, 0.f, 0.f };
		float AutoTurretsEsp[] = { 255.f, 0.f, 0.f };
		float FlameTurretsEsp[] = { 255.f, 0.f, 0.f };
		float LandAirTurretEsp[] = { 255.f, 0.f, 0.f };
		float HempEsp[] = { 255.f, 0.f, 0.f };
		float SupplyEsp[] = { 255.f, 0.f, 0.f };
		float CorpseEsp[] = { 255.f, 0.f, 0.f };
		float CrateEsp[] = { 255.f, 0.f, 0.f };
		float Workbench1Esp[] = { 255.f, 0.f, 0.f };
		float Workbench2Esp[] = { 255.f, 0.f, 0.f };
		float Workbench3Esp[] = { 255.f, 0.f, 0.f };
		float CupboardEsp[] = { 255.f, 0.f, 0.f };
		float ChestEsp[] = { 255.f, 0.f, 0.f };
		float show_WeaponsEsp[] = { 255.f, 0.f, 0.f };
		/// </summary>
		float SkeletonColor[] = { 255.f, 0.f, 0.f };
		float ChamsEsp[] = { 255.f, 255.f, 255.f };
		float LineEsp[] = { 255.f, 0.f, 0.f };
		float BoxColor[] = { 255.f, 0.f, 0.f };
		float NameColor[] = { 255.f, 0.f, 0.f };
		float PlayerHeath[] = { 255.f, 0.f, 0.f };
		float DistanceColor[] = { 255.f, 0.f, 0.f };
		float WeaponColor[] = { 255.f, 0.f, 0.f };
		float CrosshairColor[] = { 0.f, 255.f, 0.f };
		
		float BotNameEsp[] = { 255, 0, 255 };
		float BotBoxEsp[] = { 255, 0, 255 };
		float BotsSkeletonEsp[] = { 255, 0, 255 };
		float BotDistEsp[] = { 255, 0, 255 };
		float BotWeaponEsp[] = { 255, 0, 255 };
		float SilentColor[] = { 255, 255, 0 };
		float ColorPreview[] = { 25, 30, 35 };
		float Steep[] = { 255, 0, 255 };
	}

	namespace Other
	{
	    bool InfoTopLeft = false;
	}
	namespace Radar
	{
		bool Enable = false;
		bool ShowRadarBackground = false;
		bool ShowRadarPlayer = false;
		bool ShowRadarSleeper = false;
		float Pos_X = 0;
		float Pos_Y = 0;
		float Radar_Size = 250.f;
		float Radar_Range = 300.f;
	}

	namespace RadarColor
	{
		static float Radar[] = { 0,0,0,1, 0.5f };
		static float RadarBackground[] = { 0,0,0,1, 0.5f };
		static float RadarPlayerColor[] = { 1,0,0,1 };
		static float RadarPlayerSleeperColor[] = { 0,0,1,1 };
		static float RadarStoneOreColor[] = { 0.487,0.487,0.487,1 };
		static float RadarMettalOreColor[] = { 0.162,0.178,0.440,1 };
		static float RadarSulfureOreColor[] = { 0.392,0.353,0.84,1 };
	}

	namespace Config {
		static char configname[128] = "My";
		bool LoadConfig = false;
		bool SaveConfig = false;
		bool InitConfig = false;
	}

	namespace Theams 
	{
		bool Dark = true;
		bool Light = false;
	}


	namespace Watermark
	{
		bool waterm = true;
		bool watermL = false;

		float PosX = 24.f;
		float PosY = 10.f;
	}

}
