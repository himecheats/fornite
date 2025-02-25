#pragma once
#include "Ofssets.h"

class Color 
{
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) 
	{
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

typedef void(__fastcall* SilentHeli)(void*, void*);
SilentHeli Orig_HeliSendProjectileAttack{ };

typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
SendProjectileAttack_fn Orig_SendProjectileAttack{ };

typedef void(__fastcall* SetFlying_fn)(void*, void*);
SetFlying_fn original_setflying{};

__declspec(selectany) uintptr_t TargetSilentPlayer = NULL;
__declspec(selectany) uintptr_t TargetPSilentPlayer = NULL;
__declspec(selectany) uintptr_t closestPlayer = NULL;


typedef bool(__fastcall* Can_Attack)(void*, void*);
inline Can_Attack Orig_CanAttack;

typedef float(__fastcall* GetSpeed)(float* a1, float* a2);
inline GetSpeed Orig_GetSpeed;

__declspec(selectany) uintptr_t PlayerTarget = NULL;

typedef Vector3(__fastcall* clientinput)(DWORD64, DWORD64);
inline clientinput original_clientinput;

typedef void(__fastcall* BlockSprint)(void*);
inline BlockSprint Orig_BlockSprint;

typedef bool(__fastcall* Is_Admin)(void*, void*);
inline Is_Admin Orig_IsAdmin;

typedef bool(__fastcall* swimonground)(void*, void*);
inline swimonground original_swiming;

typedef void(__fastcall* Blockt)(void*, D2D1::ColorF);
inline Blockt Orig_CHAMSESP;

typedef DWORD64(__fastcall* playerChams_fn)(DWORD64, float);
playerChams_fn original_playerChams{};

typedef bool(__fastcall* cancan)(void*, void*);
inline cancan original_canholditems;

typedef void(__fastcall* HandleRunning_fn)(void* a1, void* a2, bool);
inline HandleRunning_fn orig_handleRunning;

typedef void(__fastcall* FastHeal_)(void* a1, void* a2);
inline FastHeal_ Orig_Heal;

typedef void(__fastcall* hitsound_fn)(DWORD64);
inline hitsound_fn original_sound;

typedef uintptr_t(__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef bool(__fastcall* issemiauto)(DWORD64);
inline issemiauto original_issemiauto;

typedef float(__fastcall* GetIndexedSpreadScalar)(int*, int*);
inline GetIndexedSpreadScalar Orig_GetIndexedSpreadScalar{ };

typedef void(__fastcall* AntiAim)(void*);
inline AntiAim original_sendclienttick;

typedef void(__fastcall* NightMode_)(void* a1, void* a2);
inline NightMode_ original_mode;


void __fastcall NightMode(void* a1, void* a2) {
	if (Vars::Visuals::NightMode) {
		typedef void(__stdcall* F)(float);
		typedef void(__stdcall* I)(int);
		typedef void(__stdcall* C)(D2D1::ColorF);
		((I)(GetModBase(StrW(L"GameAssembly.dll")) + 0x1866840))(3);// public static void set_ambientMode(AmbientMode value) { }
		((F)(GetModBase(StrW(L"GameAssembly.dll")) + 0x1866780))(1.f);//public static void set_ambientIntensity(float value) { }
		((C)(GetModBase(StrW(L"GameAssembly.dll")) + 0x1866800))(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f));//public static void set_ambientLight(Color value) { }
	}
	return  original_mode(a1, a2);
}

DWORD64 __fastcall GetSkinColor(DWORD64 skinset, float skinNumber) {
	DWORD64 color = original_playerChams(skinset, skinNumber);
	if (Vars::Visuals::ShowPlayerChams) {
		safe_write(color + 0x0, 129.f, float);
		safe_write(color + 0x4, 171.f, float);
		safe_write(color + 0x8, 255.f, float);
		safe_write(color + 0xC, 1.f, float);
	}
	return color;
}

void __fastcall ChamsESP(void* a1, D2D1::ColorF)
{
	if (Vars::Visuals::ShowHandChams)
		return Orig_CHAMSESP(a1, D2D1::ColorF(255, 255, 255, 1));
}

__declspec(selectany) uintptr_t TargetSilientHeli = NULL;

inline void __fastcall hook_sendclienttick(void* self)
{
	if (Vars::Misc::AntiAim)
	{
		auto input = safe_read(self + 0x4C8, uintptr_t);
		if (!input)
		{
			return original_sendclienttick(self);
		}

		auto state = safe_read(input + 0x20, uintptr_t);
		if (!state)
		{
			return original_sendclienttick(self);
		}

		auto current = safe_read(state + 0x10, uintptr_t);
		if (!current)
		{
			return original_sendclienttick(self);
		}
		safe_write(current + 0x18, Vector3(100, rand() % 999 + -999, rand() % 999 + -999), Vector3);//public Vector3 aimAngles; // 0x18
	
	}
	
	return original_sendclienttick(self);
}


inline uintptr_t __fastcall CreateProjectile(void* BaseProjectile, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) 
{
	uintptr_t projectile = original_create_projectile(BaseProjectile, prefab_pathptr, pos, forward, velocity);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(closestPlayer);
	safe_write(projectile + 0x114, true, bool);
	if (Vars::AimBot::Fake_Dist)
	{
		safe_write(projectile + 0x130, 1337.f, float);
	}
	if (Vars::AimBot::FatBullet) {
		safe_write(projectile + 0x2C, 2.f, float);
	}
	else {
		safe_write(projectile + 0x2C, 0.1f, float);
	}
	return projectile;
}

bool __fastcall CanHoldItems(void* a1, void* a2) {
	if (Vars::Misc::canHoldItems)
		return true;
	return original_canholditems(a1, a2);
}

void __fastcall Fake_handleRunning(void* a1, void* a2, bool wantsRun)
{
	if (Vars::Misc::SlideWalk)
		return orig_handleRunning(a1, a2, true);
	return orig_handleRunning(a1, a2, wantsRun);

	if (Vars::Misc::OmniSpread)
		wantsRun = true;
	return orig_handleRunning(a1, a2, wantsRun);
}

inline float __fastcall Fake_GetSpeed(float* a1, float* a2)
{
	if (Vars::Misc::SpeedHack)
	{
		return Vars::Misc::SpeedValue;
	}
	return  Orig_GetSpeed(a1, a2);
}
__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) 
{
	Vector3 dir = Src - Dst;

	return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
}

inline bool __fastcall Fake_Can_Attack(void* a1, void* a2)
{
	if (Vars::Misc::JumpAiming)
		return true;
	return Orig_CanAttack(a1, a2);
}

//void DoMeleeAttack(AimResult target, DWORD64 active, bool transform = true) {
//	if (!target.valid || !active) return;
//
//	Vector3 lp = LocalPlayer.BasePlayer->GetBoneByID(head);
//	typedef float(__stdcall* A)();
//
//	float time = ((A)(Vars::Storage::gBase + 0x14E8310))();
//	if (safe_read(active + 0x230, float) >= time) { //nextattacktime
//		return;
//	}
//
//	if (safe_read(active + 0x23C, float) < safe_read(active + 0x1D8, float)) {
//		return;
//	}
//
//	//HitTest
//	DWORD64 htstatic = safe_read(Vars::Storage::gBase + 0x29BEE10, DWORD64);
//	if (!htstatic) return;
//
//	DWORD64 New = Vars::Storage::gBase + 0x2A38BF3;
//	typedef DWORD64(__stdcall* NNew)(DWORD64);
//
//	DWORD64 HitTest = ((NNew)New)(htstatic);
//
//	Ray ray = Ray(lp, (target.pos - lp).Normalized());
//	safe_write(HitTest + 0x34, 1000.f, float); //MaxDistance
//	DWORD64 trans;
//	if (transform) {
//		trans = target.entity->GetTransform(Vars::AimBot::AimHead ? BoneList::head : BoneList::spine3);
//	}
//	else {
//		typedef DWORD64(__stdcall* GetTr)(DWORD64);
//		trans = ((GetTr)(Vars::Storage::gBase + 0x145E370))((DWORD64)target.entity);
//	}
//	if (!trans) return;
//
//	safe_write(HitTest + 0xB0, trans, DWORD64); //HitTransform
//	safe_write(HitTest + 0x14, ray, Ray);
//	safe_write(HitTest + 0xC0, Str((L"Flesh")), Str); //HitMaterial
//	safe_write(HitTest + 0x66, true, bool); //DidHit
//	safe_write(HitTest + 0x88, target.entity, BasePlayer*); //HitEntity
//
//	typedef Vector3(__stdcall* ITP)(DWORD64, Vector3);
//	Vector3 hitpoint = ((ITP)(Vars::Storage::gBase + 0x1AB1E50))(trans, target.pos);
//	safe_write(HitTest + 0x90, hitpoint, Vector3); //HitPoint
//	safe_write(HitTest + 0x9C, Vector3(0, 0, 0), Vector3); //HitNormal
//	safe_write(HitTest + 0xC0, safe_read(active + 0x268, DWORD64), DWORD64); //damageProperties
//
//	typedef void(__stdcall* Atk)(DWORD64, DWORD64);
//
//	float kd = safe_read(active + 0x1DC, float);
//	typedef void(__stdcall* StartKD)(DWORD64, float);
//	((StartKD)(Vars::Storage::gBase + 0x2DD660))(active, kd);
//	return ((Atk)(Vars::Storage::gBase + 0x281E70))(active, HitTest);
//}

void __fastcall HitSound(DWORD64 info) {
	if (Vars::Misc::HitSound) {
		PlaySoundW((L"C:/udefhitsounds/1.wav"), NULL, SND_ASYNC);
	}
	else {
		return original_sound(info);
	}
}

inline bool __fastcall isswiming(void* a1, void* a2)
{
	if (Vars::Misc::NewSwimOnGround)
	{
		return true;
	}
	return original_swiming(a1, a2);
}

inline bool __fastcall Fake_IsAdmin(void* a1, void* a2)
{
	if (Vars::Misc::NewFakeAdmin)
		return true;

	return Orig_IsAdmin(a1, a2);
}

inline void __fastcall Fake_BlockSprint(void* a1)
{
	if (Vars::Misc::JumpAiming)
		return;

	return Orig_BlockSprint(a1);
}

bool __fastcall get_isSemiAuto(DWORD64 BaseProjectile) {
	if (Vars::Misc::Automatic) {
		return false;
	}
	return original_issemiauto(BaseProjectile);
}

bool IsUsing_FastHeal = true;
float Use_Last_FastHeal;

inline void __fastcall Fake_SendProjectileAttack(void* a1, void* a2) 
{
	uintptr_t PlayerAttack = safe_read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	uintptr_t Attack = safe_read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
	if (Vars::AimBot::EnableSilentAim)
	{
		if (TargetSilentPlayer != NULL) 
		{
			safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
			safe_write(Attack + 0x64, 16144115, uint32_t); // public uint hitPartID;
			if (Vars::AimBot::ThroughWall) 
			{
				safe_write(Attack + 0x4C, Vector3(0.f, -1000.f, 0.f) * -10000.f, Vector3);
			}
			safe_write(Attack + 0x2C, safe_read(safe_read(TargetSilentPlayer + 0x50, uintptr_t) + 0x10, uint32_t), uint32_t);
		}
	}
	if (Vars::AimBot::AlwaysHeadshot) 
	{
		safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
	}
	return Orig_SendProjectileAttack(a1, a2);
}

inline float __fastcall Fake_GetIndexedSpreadScalar(int* a1, int* a2)
{
	if (Vars::Misc::ShotGunTochka)
	{
		return 0;
	}
	return  Orig_GetIndexedSpreadScalar(a1, a2);
}

void __fastcall SetFlying(void* a1, void* a2) 
{
	if(Vars::Misc::FakeAdmin)
		return;
}

inline void CreateHook(void* Function, void** Original, void* Detour, bool autoEnable = true)
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	if (autoEnable)
		MH_EnableHook(Function);
}

typedef Vector3(__fastcall* aimconedirection)(float, Vector3, bool);
inline aimconedirection original_aimconedirection;

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone);

typedef pUncStr(__fastcall* consoleRun)(uintptr_t, pUncStr, DWORD64);
inline consoleRun original_consolerun{};

pUncStr __fastcall Run(uintptr_t options, pUncStr strCommand, DWORD64 args) {
	bool IsFromServer = safe_read(options + 0x6, bool);
	if (IsFromServer) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find(L"noclip") != std::wstring::npos || cmd.find(L"debugcamera") != std::wstring::npos || cmd.find(L"camspeed") != std::wstring::npos || cmd.find(L"admintime") != std::wstring::npos) {
			strCommand = nullptr;
		}
	}
	return original_consolerun(options, strCommand, args);
}

inline void __fastcall silentheli(void* a1, void* a2)
{
	if (Vars::AimBot::HeliSilent)
	{
		{
			if (TargetSilientHeli != NULL)
			{
				const auto PlayerAttack = safe_read((uintptr_t)a2 + 0x18, uintptr_t);
				const auto Attack = safe_read(PlayerAttack + 0x18, uintptr_t);
				int health = (int)ceil(safe_read(TargetSilientHeli + 0x1F4, float)); // Player_Health ,// public float attackSpacing;
				if (health <= 5000)
				{
					safe_write(Attack + 0x2C, 224139191, uint32_t); //public uint hitID;
				}
				else
				{
					safe_write(Attack + 0x2C, 2699525250, uint32_t); //public uint hitID;
				}
			}
		}
	}
	return Orig_HeliSendProjectileAttack(a1, a2);
}

Vector3 __fastcall pSilent(float aimCone, Vector3 inputVec, bool anywhereInside = true) // wanna hang myself
{
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(TargetPSilentPlayer);
	Vector3 dir = (Prediction(LocalPlayer.BasePlayer->GetBoneByID(head), TargetPlayer, head) - LocalPlayer.BasePlayer->GetBoneByID(head)).Normalized();
	if (Vars::AimBot::pSilent) {
		if (!(TargetPlayer->GetBoneByID(spine1).x == 0 && TargetPlayer->GetBoneByID(spine1).y == 0 && TargetPlayer->GetBoneByID(spine1).z == 0)) {
			return original_aimconedirection(0.f, dir, anywhereInside);
		}
		else {
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
	}
	if (Vars::AimBot::psilentAlwaysHeadshot)
	{
		safe_write(TargetPlayer + 0x30, 698017942, uint32_t); // public uint hitBone;
	}
	else return original_aimconedirection(aimCone, inputVec, anywhereInside);
}

Vector3 PredictionPS(Vector3 LP_Pos, BasePlayer* Player, BoneList Bone)
{
	WeaponData* active = LocalPlayer.BasePlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	if (Vars::AimBot::psilentAlwaysBody) {
		Vector3 BonePos = Player->GetBoneByID(spine1);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);
		if (Dist > 0.001f) {
			float speed = GetBulletSpeedPS(tar, ammo) * Vars::AimBot::Velocity;
			if (!speed) speed = 250.f;
			float BulletTime = Dist / speed;
			Vector3 vel = Player->GetVelocity();
			Vector3 PredictVel = vel * BulletTime * 0.75f;
			BonePos += PredictVel;
			float gravity = GetGravityPS(ammo);
			BonePos.y += (4.905f * BulletTime * BulletTime) * gravity; // 4.905f
		}
		return BonePos;
	}
}

void __fastcall ClientInput(DWORD64 baseplayah, DWORD64 ModelState) 
{
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (Vars::Misc::Flyhack)
		LocalPlayer.BasePlayer->AddFlag(32);
	if (Vars::Misc::SilentWalk)
		LocalPlayer.BasePlayer->SetRemoveFlag(4);
	typedef void(__stdcall* SeNpai6275)(float);
	if (Vars::Misc::speedhack && GetAsyncKeyState(Vars::Misc::speedhackkey)) {
		SeNpai6275 ss = (SeNpai6275)(Vars::Storage::gBase + O::UnityEngine_Time::set_timeScale); //set_timescale
		ss(2);
	}
	else {
		SeNpai6275 ss = (SeNpai6275)(Vars::Storage::gBase + O::UnityEngine_Time::set_timeScale); //set_timescale
		ss(1);
	}
}

inline void InitHook()
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;
	}
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x7E5950)), reinterpret_cast<void**>(&original_aimconedirection), pSilent);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x22759F0)), reinterpret_cast<void**>(&original_consolerun), Run);//&public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x808B50)), reinterpret_cast<void**>(&Orig_CHAMSESP), ChamsESP);//private void SetSkinColor(Color skinColor) { }



	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::PlayerModel::GetSkinColor)), reinterpret_cast<void**>(&original_playerChams), GetSkinColor);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BaseCombatEntity::DoHitNotify)), reinterpret_cast<void**>(&original_sound), HitSound); //public void DoHitNotify(HitInfo info) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BaseProjectile::CreateProjectile)), reinterpret_cast<void**>(&original_create_projectile), CreateProjectile);// private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::TOD_Sky::get_Instance)), reinterpret_cast<void**>(&original_mode), NightMode);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::ClientInput)), reinterpret_cast<void**>(&original_clientinput), ClientInput);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BaseProjectile::CreateProjectile)), reinterpret_cast<void**>(&Orig_HeliSendProjectileAttack), silentheli);// public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::get_IsAdmin)), reinterpret_cast<void**>(&Orig_IsAdmin), Fake_IsAdmin); //public bool get_IsAdmin() { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::ModelState::set_flying)), reinterpret_cast<void**>(&original_setflying), SetFlying);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::SendProjectileAttack)), reinterpret_cast<void**>(&Orig_SendProjectileAttack), Fake_SendProjectileAttack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::CanAttack)), reinterpret_cast<void**>(&Orig_CanAttack), Fake_Can_Attack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::BlockSprint)), reinterpret_cast<void**>(&Orig_BlockSprint), Fake_BlockSprint);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BaseMountable::CanHoldItems)), reinterpret_cast<void**>(&original_canholditems), CanHoldItems);
	//CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetSpeed)), reinterpret_cast<void**>(&Orig_GetSpeed), Fake_GetSpeed);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::ItemModProjectile::GetIndexedSpreadScalar)), reinterpret_cast<void**>(&Orig_GetIndexedSpreadScalar), Fake_GetIndexedSpreadScalar);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::PlayerWalkMovement::HandleRunDuckCrawl)), reinterpret_cast<void**>(&orig_handleRunning), Fake_handleRunning);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + O::BasePlayer::SendClientTick)), reinterpret_cast<void**>(&original_sendclienttick), hook_sendclienttick);

}
