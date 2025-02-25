void Misc()
{
	////air stuck
	//if (Vars::Misc::AirStuck) {
	//	if (FC(user32, GetAsyncKeyState, Vars::Misc::airkey))
	//		LocalPlayer.BasePlayer->AirStuck(true);
	//	else LocalPlayer.BasePlayer->AirStuck(false);
	//}

	if (Vars::Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();

	if (Vars::Misc::Zoom) {
		if (FC(user32, GetAsyncKeyState, Vars::Misc::zoomkey))
			LocalPlayer.BasePlayer->Zoom(true);
		else LocalPlayer.BasePlayer->Zoom(false);
	}

	//on aim on kastrulya
	if (Vars::Misc::AntiKastrulya)
		LocalPlayer.BasePlayer->NoBlockAiming();

	//boost speed on heavy armor
	if (Vars::Misc::NoHeavyReduct)
		LocalPlayer.BasePlayer->NoHeavyReduct();

	if (Vars::Misc::LongNeck && GetAsyncKeyState(Vars::Misc::lnkey))
		LocalPlayer.BasePlayer->LongNeck();

	//spider man
	if (Vars::Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();

	if (Vars::Misc::ThirdPerson)
		LocalPlayer.BasePlayer->FakeThirdPerson(1024);

	//if (Vars::Misc::InfinityJump)
	//	if (FC(user32, GetAsyncKeyState, VK_SPACE))
	//	LocalPlayer.BasePlayer->InfinityJump();
	//remove weapon sway
	if (Vars::Misc::NoSway)
		LocalPlayer.BasePlayer->NoSway();

	if (Vars::Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin(4);

	//if (Vars::Misc::WalkOnWater && GetAsyncKeyState(Vars::Misc::walkkey))
	//	LocalPlayer.BasePlayer->WalkWater();

	if (Vars::Visuals::NightMode) {
		LocalPlayer.BasePlayer->Pizda228();
		return;
	}
}
