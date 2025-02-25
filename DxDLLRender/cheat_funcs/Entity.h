bool mfound = false;
void ESP(BasePlayer* BP, BasePlayer* LP);
inline void RadarPlayer(BasePlayer* player);
void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y);
void RenderActiveSlotLight(BasePlayer* player, float Pos_x, float Pos_Y);
BasePlayer* Player;
void FindMatrix() {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64);
	if (!ObjMgr) return;
	UINT64 end = safe_read(ObjMgr, UINT64);
	for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = safe_read(Obj + 0x8, UINT64))
	{
		UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);
		if (Tag == 5)
		{
			UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
			UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
			LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);// 0xDC
			mfound = true;
			return;
		}
	}
}

void PickupItem(DWORD64 item)
{
	typedef void(__stdcall* Pick)(DWORD64, Str);
	return ((Pick)(GetModBase(L"GameAssembly.dll") + O::BaseEntity::ServerRPC))(item, Str(L"Pickup"));
}
int dlastKnock;
int dlastOpen;
void EbynMozga(DWORD64 Door) {
	typedef void(__stdcall* Daun)(DWORD64, BasePlayer*);
	float time = LocalPlayer.BasePlayer->GetTickTime();
	if (time > dlastKnock + 1.f)
	{	
		//0x493CC0
		((Daun)(GetModBase(L"GameAssembly.dll") + O::Door::Menu_KnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastKnock = time;
	}

	if (time > dlastOpen + 1.f) 
	{
		//0x493D40
		((Daun)(GetModBase(L"GameAssembly.dll") + O::Door::Menu_KnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastOpen = time;
	}

}

inline void FakeLag()
{
	if (Vars::Misc::FakeLag)
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + O::BasePlayer::clientTickInterval, Vars::Misc::FakeLagTicks, float);
	}
	else
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + O::BasePlayer::clientTickInterval, Vars::Misc::FakeLagTicks, float);
	}
}

class AimResult 
{
public:
	bool valid;
	BasePlayer* entity;
	Vector3 pos;
	float dist = 10000.f;
	float realdist = 0.f;
	float fov = 10000.f;

	bool operator<(const AimResult& b) 
	{
		if (fov == 10000.f) {
			return this->dist < b.dist;
		}
		else{
			return this->fov < b.fov;
		}
	}

	AimResult() {
		this->valid = false;
		this->fov = 10000.f;
	}
	AimResult(Vector3 target) 
	{
		this->valid = false;
		this->pos = target;
	}
};

float CurFOV;
BasePlayer* SilentTargetedPlayer = 0;

void Entity()
{
	bool LP_isValid = true;
	float FOV = 1000000.f;
	BasePlayer* AimEntity = 0;
	BasePlayer* TargetAimBotPlayer = nullptr;
	BasePlayer* AimEntity2 = 0;

	if (!LocalPlayer.pViewMatrix || !mfound)
	{
		FindMatrix();
	}

	DWORD64 BaseNetworkable;
	BaseNetworkable = safe_read(GetModBase(StrW(L"GameAssembly.dll")) + oBaseNetworkable, DWORD64);
	DWORD64 EntityRealm = safe_read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = safe_read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = safe_read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = safe_read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = safe_read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = safe_read(ClientEntities_values + 0x18, DWORD64);

	for (int i = 0; i <= EntityCount; i++)
	{
		DWORD64 Entity = safe_read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
		if (Entity <= 100000) continue;
		DWORD64 Object = safe_read(Entity + 0x10, DWORD64); //BaseObject
		if (Object <= 100000) continue;
		DWORD64 ObjectClass = safe_read(Object + 0x30, DWORD64); //Object
		//
		WORD tag = safe_read(ObjectClass + 0x54, WORD);
		uintptr_t localElement = safe_read(EntityBuffer + 0x20, uintptr_t);
		//
		if (ObjectClass <= 100000) continue;
		pUncStr name = safe_read(ObjectClass + 0x60, pUncStr);
		uintptr_t BaseObject = safe_read(ObjectClass + 0x30, uintptr_t);
		uintptr_t BaseEntity = safe_read(BaseObject + 0x18, uintptr_t);
		uintptr_t BaseHelicopter = safe_read(BaseEntity + 0x28, uintptr_t);
		uintptr_t BaseBradley = safe_read(BaseEntity + 0x28, uintptr_t);
		if (!name) continue;
		char* buff = name->stub;
		BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
		if (strstr(buff, StrA("Local"))) {
			Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
			if (!safe_read(Player + 0x4A8, DWORD64)) continue; 
			if (Player != LocalPlayer.BasePlayer ) 
            {
				
				mfound = false;
			}
			
			LocalPlayer.BasePlayer = Player;
			LP_isValid = true;

		}

		if (strstr(buff, "player.prefab") || (strstr(buff, "scientist")) && (!strstr(buff, "prop") && !strstr(buff, "corpse")))
		{
			BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64); //public ulong playerID;
			if (!safe_read(Player + 0x4A8, DWORD64)) continue;
			if (!Player->IsValid()) continue;
			bool ex = false;
			RadarPlayer(Player);
			//printf("Esp on %lld\n", Player->GetSteamID());
			ESP(Player, LocalPlayer.BasePlayer);

			if (Vars::Visuals::ActiveSlot && GetFov(Player, head) <= 150)
				RenderActiveSlot(Player, Vars::Visuals::ActiveSlotPos_X, Vars::Visuals::ActiveSlotPos_Y);

			if (Vars::Visuals::ActiveSlotLight && GetFov(Player, head) <= 150)
				RenderActiveSlotLight(Player, Vars::Visuals::ActiveSlotPos_X, Vars::Visuals::ActiveSlotPos_Y);

			if (Vars::Visuals::IgnoreSleepers && Player->HasFlags(16)) continue;

			if (Vars::AimBot::IgnoreSleepers && Player->IsSleeping()) continue;

			if (Vars::AimBot::IgnoreNpc && Player->IsNpc()) continue;
			
			if (ex) continue;
			//cut distance
			if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Vars::AimBot::Range)
				continue;

			//calc visible & low fov
			if (Player->IsVisible() && (FOV > (CurFOV = GetFov(Player, BoneList(Vars::Global::BoneToAim))))) 
			{
				if (CurFOV <= Vars::AimBot::Fov) 
				{
					FOV = CurFOV; AimEntity = Player;
				}
				if (CurFOV <= Vars::AimBot::SilentFov) 
				{
					TargetSilentPlayer = (uintptr_t)Player;
				}
				if (CurFOV <= Vars::AimBot::PSilentFov) 
				{
					TargetPSilentPlayer = (uintptr_t)Player;
				}
			}
		}
		DWORD64 ent = safe_read(Object + 0x28, UINT64);

		auto* weapon_ = LocalPlayer.BasePlayer->GetActiveWeapon();
		char* classname = weapon_->ClassName();
		bool weaponmelee = weapon_ && classname && (m_strcmp(classname, "BaseMelee") || m_strcmp(classname, "Jackhammer"));
		DWORD64 active = safe_read(weapon_ + O::Item::heldEntity, DWORD64);
		
		if (Vars::Misc::Door && m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64), "Door")) 
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + O::BaseEntity::ClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (ent && Math::Calc3D_Dist(local, pos) < 3.f) 
			{
				EbynMozga(ent);
			}
		}

		if (Vars::Misc::AutoPickUp && m_strstr(buff, "/collectable/")) 
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + O::BaseEntity::ClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (Math::Calc3D_Dist(local, pos) < 5.f) 
			{
				PickupItem(ent);
			}
		}
			else if (Vars::Misc::Door && m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64), ("Door"))) {
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);

			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);

			Vector3 local = ((CPoint)(GetModBase((L"GameAssembly.dll")) + O::BaseEntity::ClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (ent && Math::Calc3D_Dist(local, pos) < 3.f) {
				EbynMozga(ent);
			}
		}

		if (Vars::Visuals::Stone && strstr(buff, "stone-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;

			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Stone-Ore", L"[%d M]", distation);
				if (distation <= Vars::Visuals::StoneOreDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Gray);
			}
		}

		if (Vars::Visuals::Sulphur && strstr(buff, "sulfur-ore.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Sulfur ore [%d M]", distation);
				if (distation <= Vars::Visuals::SulphurOreDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Gold);
			}
		}

		if (Vars::Visuals::Metal && strstr(buff, "metal-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Metal ore [%d M]", distation);
				if (distation <= Vars::Visuals::MetalOreDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Brown);
			}
		}

		if (Vars::Visuals::Stash && strstr(buff, "small_stash_deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Stash [%d M]", distation);
				if (distation <= Vars::Visuals::StashDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Yellow);
			}
		}

		if (Vars::Visuals::Minicopter && strstr(buff, "minicopter.entity.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"minicopter [%d M]", distation);
				if (distation <= Vars::Visuals::MinicopterDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightBlue);
			}
		}
		if (Vars::Visuals::ScrapCopter && strstr(buff, "scraptransporthelicopter.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Scrap Copter [%d M]", distation);
				if (distation <= Vars::Visuals::ScrapCopterDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::RosyBrown);
			}
		}

		if (Vars::Visuals::Boat && strstr(buff, "rowboat.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Boat [%d M]", distation);
				if (distation <= Vars::Visuals::BoatDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::LightPink);
			}
		}

		if (Vars::Visuals::RHIB && strstr(buff, "rhib.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"RHIB [%d M]", distation);
				if (distation <= Vars::Visuals::RHIBDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
			}
		}

		if (Vars::Visuals::Patrul && strstr(buff, "patrolhelicopter.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			Vector2 tempHead;
			Vector2 tempFeetR, tempFeetL;
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				int health = (int)safe_read(BaseHelicopter + O::BaseCombatEntity::_health, float);
				wchar_t text[0x100];
				float maxheal = 100.f;
				float Entity_h = tempHead.y - tempFeet.y;
				float w = Entity_h / 4;
				float Entity_x = tempFeet.x - w;
				float Entity_y = tempFeet.y;
				float Entity_w = Entity_h /
				
				_swprintf(text, L"PatrulHeli [%d M][%d HP]", distation, health);
				if (distation <= Vars::Visuals::PatrulDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::BlueViolet);
				if (Vars::Visuals::ShowPlayerHealthBar)
				{
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), LocalPlayer.BasePlayer->GetBoneByID(head)) < 201)
					{
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / minheal) }, D2D1::ColorF::Magenta);
						if ((int)safe_read(BaseHelicopter + O::BaseCombatEntity::_health, float) <= 33)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)safe_read(BaseHelicopter + O::BaseCombatEntity::_health, float) >= 34 && (int)safe_read(BaseHelicopter + O::BaseCombatEntity::_health, float) <= 66)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)safe_read(BaseHelicopter + O::BaseCombatEntity::_health, float) >= 67)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
					}
				}
			}
		}

		if (Vars::Visuals::Bardley && strstr(buff, "bradleyapc.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {

				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos);
				int health = (int)safe_read(BaseBradley + O::BaseCombatEntity::_health, float);
				wchar_t res[90];

				_swprintf(res, L"Bradley [%d M][%d HP]", distation, health);
				if (distation <= Vars::Visuals::BardleylDistation)
				GUI::Render.String(Pos, res, D2D1::ColorF::DarkGreen);

			}
		}
		
		if (Vars::Visuals::ShotgunTraps && strstr(buff, "guntrap.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"ShotGun Trap [%d M]", distation);
				if (distation <= Vars::Visuals::ShotgunTrapsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Silver);
			}
		}
		if (Vars::Visuals::FlameTurrets && strstr(buff, "flameturret.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Flameturret [%d M]", distation);
				if (distation <= Vars::Visuals::FlameTurretsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Orange);
			}
		}
		if (Vars::Visuals::AutoTurrets && strstr(buff, "autoturret_deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Autoturret [%d M]", distation);
				if (distation <= Vars::Visuals::AutoTurretsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::DarkRed);
			}
		}
		if (Vars::Visuals::LandAirTurret && strstr(buff, "sam_site_turret_deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Land-Air Turret [%d M]", distation);
				if (distation <= Vars::Visuals::LandAirTurretDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Purple);
			}
		}

		if (Vars::Visuals::Hemp && strstr(buff, "hemp-collectable.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Hemp [%d M]", distation);
				if (distation <= Vars::Visuals::HempDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightGreen);
			}
		}

		if (strstr(buff, "supply_drop.prefab") && Vars::Visuals::Supply) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Airdrop [%d M]", distation);
				if (distation <= Vars::Visuals::SupplyDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::IndianRed);
			}
		}
		if (strstr(buff, "codelockedhackablecrate.prefab") && Vars::Visuals::Crate) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Chinook Crate [%d M]", distation);
				if (distation <= Vars::Visuals::CrateDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::Cyan);
			}
		}

		if (Vars::Visuals::Corpse && strstr(buff, "player_corpse.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				int name = (int)LocalPlayer.BasePlayer->GetName();
				wchar_t text[0x100];
				
				_swprintf(text, L"Corpse|%s [%d M]", distation,name);
				if (distation <= Vars::Visuals::CorpseDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::DarkGray);
			}
		}
		if (Vars::Visuals::Corpse && strstr(buff, "item_drop_backpack.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Backpack [%d M]", distation);
				if (distation <= Vars::Visuals::CorpseDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::DarkGray);
			}
		}

		if (Vars::House::workbench1 && strstr(buff, "workbench1.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Workbench-1 [%d M]", distation);
				if (distation <= Vars::House::workbench1Distation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Brown);
			}
		}

		if (Vars::House::workbench2 && strstr(buff, "workbench2.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Workbench-2 [%d M]", distation);
				if (distation <= Vars::House::workbench2Distation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Blue);
			}
		}

		if (Vars::House::workbench3 && strstr(buff, "workbench3.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Workbench-3 [%d M]", distation);
				if (distation <= Vars::House::workbench3Distation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Green);
			}
		}

		if (Vars::House::cupboard && strstr(buff, "cupboard.tool.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Cupboard [%d M]", distation);
				if (distation <= Vars::House::cupboardDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::SaddleBrown);
			}
		}

		if (Vars::House::chest && strstr(buff, "box.wooden.large.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Chest [%d M]", distation);
				if (distation <= Vars::House::chestDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::SandyBrown);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "lmg.m249")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M249 LMG [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.bolt")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"BOLT Sniper [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.ak")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"AK-47 Rifle [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.lr300")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"LR300 Rifle [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.l96")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"AWM Sniper [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.m39")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M39 Rifle [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Semi Auto Rifle [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.mp5"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"MP5 SMG [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.2")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"SMG Auto [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.thompson")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Thompson SMG [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.nailgun"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Nailgun Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.eoka"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"EOKA Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.m92"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M92 Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.python"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Python Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.revolver")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Revolver Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Semi Auto Pistol [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.pump")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Shotgun Pump [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.double"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Double Shotgun [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.spas12")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"SPAS-12 Shotgun [%d M]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, D2D1::ColorF::LightSalmon);
			}
		}

	}

	if (LP_isValid)
	{
		WeaponPatch();
		Aim(AimEntity);
		Misc();
		FakeLag();
	}

	//LP not valid
	else LocalPlayer.BasePlayer = nullptr;

	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64); if (!ObjMgr) return;

	for (DWORD64 Obj = safe_read(ObjMgr + 0x8, DWORD64); (Obj && (Obj != safe_read(ObjMgr, DWORD64))); Obj = safe_read(Obj + 0x8, DWORD64))
	{
		DWORD64 GameObject = safe_read(Obj + 0x10, DWORD64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);

		if (Tag == 6 || Tag == 5 || Tag == 20011)
		{
			DWORD64 ObjClass = safe_read(GameObject + 0x30, DWORD64);
			DWORD64	Entity = safe_read(ObjClass + 0x18, DWORD64);

			//entity
			if (Tag == 6)
			{
				BasePlayer* Player = (BasePlayer*)safe_read(Entity + 0x28, DWORD64);
				if (!Player->IsValid()) continue;

				//entity
				if (safe_read(safe_read(GameObject + 0x60, DWORD64), DWORD64) != 0x616C506C61636F4C)
				{
					//exec esp
					ESP(Player, LocalPlayer.BasePlayer);

					if (Vars::AimBot::IgnoreTeam) {
						DWORD64 EntitySID = Player->GetSteamID();
						for (int j = 0; j < LocalPlayer.BasePlayer->GetTeamSize(); j++) {
							DWORD64 SlotSID = LocalPlayer.BasePlayer->IsTeamMate(j);
							if (SlotSID == EntitySID) goto NextEnt;
						}
					}

					if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Vars::AimBot::Range)
						goto NextEnt;

				}

				//LP
				else 
				{
					LP_isValid = true;
					LocalPlayer.BasePlayer = Player;
				}
			}

			//camera
			else if (Tag == 5)
				LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);// 0xDC

			//sky
			else if (Tag == 20011 && Vars::Visuals::AlwaysDay) 
			{
				DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
				DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
				safe_write(TodCycle + 0x10, 13.37f, float);
			}

			else if (Tag == 20011 && Vars::Misc::CustomTime) 
			{
				DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
				DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
				safe_write(TodCycle + 0x10, Vars::Misc::Time, float);
			}

		}

		//goto next entity
	NextEnt: continue;
	}

	//GET MEMES
	if (LP_isValid)
	{
		WeaponPatch();
		Aim(AimEntity);
		Misc();
	}

	//LP not valid
	else LocalPlayer.BasePlayer = nullptr;
}