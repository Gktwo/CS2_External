#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"

void Cheats::Menu()
{
	static bool IsMenuInit = false;
	if (!IsMenuInit)
	{
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.75;
		IsMenuInit = true;
	}

	ImGui::Begin(u8"菜单 [HOME] 开/关 ",nullptr,ImGuiWindowFlags_AlwaysAutoResize);
	{
		ImGui::BeginTabBar(u8"Cheat");
		// esp menu
		if (ImGui::BeginTabItem(u8"透视"))
		{
			
			// TeamCheck
			Gui.MyCheckBox(u8"友军开关", &MenuConfig::TeamCheck);

			Gui.MyCheckBox(u8"显示方框", &MenuConfig::ShowBoxESP);			
			
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##方框颜色", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Combo(u8"方框类型", &MenuConfig::BoxType, u8"宽的\0窄的");

			Gui.MyCheckBox(u8"显示骨骼", &MenuConfig::ShowBoneESP);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##骨骼颜色", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);

			Gui.MyCheckBox(u8"显示视线", &MenuConfig::ShowEyeRay);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##视线颜色", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);

			Gui.MyCheckBox(u8"显示血量", &MenuConfig::ShowHealthBar);
			ImGui::Combo(u8"血条类型", &MenuConfig::HealthBarType, u8"竖向\0横向");

			Gui.MyCheckBox(u8"显示武器", &MenuConfig::ShowWeaponESP);
			Gui.MyCheckBox(u8"显示角色", &MenuConfig::ShowPlayerName);

			Gui.MyCheckBox(u8"爆头线", &MenuConfig::ShowHeadShootLine);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##爆头线颜色", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);

			Gui.MyCheckBox(u8"FovLine", &MenuConfig::ShowFovLine);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##FovLineColor", reinterpret_cast<float*>(&MenuConfig::FovLineColor), ImGuiColorEditFlags_NoInputs);
			float FovLineSizeMin = 20.f, FovLineSizeMax = 120.f;
			Gui.SliderScalarEx1(u8"FovLineSize", ImGuiDataType_Float, &MenuConfig::FovLineSize, &FovLineSizeMin, &FovLineSizeMax, "%.1f", ImGuiSliderFlags_None);
		
			Gui.MyCheckBox(u8"敌人射线", &MenuConfig::ShowLineToEnemy);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##敌人射线颜色", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);


		
			ImGui::EndTabItem();
		}

		// aimbot menu
		if (ImGui::BeginTabItem(u8"自瞄 "))
		{
			Gui.MyCheckBox(u8"自瞄", &MenuConfig::AimBot);

			if (ImGui::Combo(u8"快按键", &MenuConfig::AimBotHotKey, "MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				AimControl::SetHotKey(MenuConfig::AimBotHotKey);
			}

			float FovMin = 0.1f, FovMax = 89.f;
			float SmoothMin = 0.1f, SmoothMax = 1.f;
			Gui.SliderScalarEx1(u8"自瞄范围", ImGuiDataType_Float, &AimControl::AimFov, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);
			Gui.MyCheckBox(u8"显示圆圈", &MenuConfig::ShowAimFovRange);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##圆圈颜色", reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);

			Gui.SliderScalarEx1(u8"平滑", ImGuiDataType_Float, &AimControl::Smooth, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);
			if (ImGui::Combo(u8"自瞄部位", &MenuConfig::AimPosition, u8"头\0颈部\0胸部"))
			{
				switch (MenuConfig::AimPosition)
				{
				case 0:
					MenuConfig::AimPositionIndex = BONEINDEX::head;
					break;
				case 1:
					MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
					break;
				case 2:
					MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
					break;
				default:
					break;
				}
			}
			int BulletMin = 1, BulletMax = 6;
			float RecoilMin = 0.f, RecoilMax = 2.f;
			Gui.SliderScalarEx1(u8"Start Bullet", ImGuiDataType_U32, &AimControl::RCSBullet, &BulletMin, &BulletMax, "%d", ImGuiSliderFlags_None);
			Gui.SliderScalarEx1(u8"RCS Yaw", ImGuiDataType_Float, &AimControl::RCSScale.x, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
			Gui.SliderScalarEx1(u8"RCS Pitch", ImGuiDataType_Float, &AimControl::RCSScale.y, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
			Gui.MyCheckBox(u8"掩体判断", &MenuConfig::VisibleCheck);
		
			ImGui::EndTabItem();
		}

		// Radar menu
		if (ImGui::BeginTabItem(u8"雷达 "))
		{
			Gui.MyCheckBox(u8"雷达", &MenuConfig::ShowRadar);
			ImGui::Combo(u8"显示类型", &MenuConfig::RadarType, u8"圆形\0箭头\0带箭头的圆形");

			Gui.MyCheckBox(u8"显示坐标系", &MenuConfig::ShowRadarCrossLine);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##坐标系颜色", reinterpret_cast<float*>(&MenuConfig::RadarCrossLineColor), ImGuiColorEditFlags_NoInputs);

			float ProportionMin = 500.f, ProportionMax = 3300.f;
			float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
			float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
			Gui.SliderScalarEx1(u8"点位大小", ImGuiDataType_Float, &MenuConfig::RadarPointSizeProportion, &RadarPointSizeProportionMin, &RadarPointSizeProportionMax, "%.1f", ImGuiSliderFlags_None);
			Gui.SliderScalarEx1(u8"比例", ImGuiDataType_Float, &MenuConfig::Proportion, &ProportionMin, &ProportionMax, "%.1f", ImGuiSliderFlags_None);
			Gui.SliderScalarEx1(u8"侦测范围", ImGuiDataType_Float, &MenuConfig::RadarRange, &RadarRangeMin, &RadarRangeMax, "%.1f", ImGuiSliderFlags_None);
		
			ImGui::EndTabItem();
		}

		// TriggerBot
		if (ImGui::BeginTabItem(u8"开枪 "))
		{
			Gui.MyCheckBox(u8"开枪", &MenuConfig::TriggerBot);

			if (ImGui::Combo(u8"热键", &MenuConfig::TriggerHotKey, "MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
			}

			DWORD TriggerDelayMin = 15, TriggerDelayMax = 170;
			Gui.SliderScalarEx1(u8"延迟", ImGuiDataType_U32, &TriggerBot::TriggerDelay, &TriggerDelayMin, &TriggerDelayMax, "%d", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}
		//misc
		if (ImGui::BeginTabItem(u8"其它 "))
		{

			// OBS Bypass
			Gui.MyCheckBox(u8"屏蔽截图", &MenuConfig::OBSBypass);
			ImGui::SameLine();
			//Bunnyhopping
			Gui.MyCheckBox(u8"大跳", &MenuConfig::BunnyHop);
			
			//CrossHair
			Gui.MyCheckBox(u8"十字准线", &MenuConfig::ShowCrossHair);
			ImGui::SameLine();
			ImGui::ColorEdit4(u8"##十字准线颜色", reinterpret_cast<float*>(&MenuConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);
			float CrossHairSizeMin = 15, CrossHairSizeMax = 200;
			Gui.SliderScalarEx1(u8"准心大小", ImGuiDataType_Float, &MenuConfig::CrossHairSize, &CrossHairSizeMin, &CrossHairSizeMax, "%.1f", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}
		// Render config saver
		ConfigMenu::RenderConfigMenu();
		
		ImGui::Separator();





		ImGui::EndTabBar();
	}ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	// Radar window
	ImGui::Begin(u8"雷达", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });

	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::Run()
{
	// Show menu
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_HOME)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		// Check key state per 150ms once to avoid loop.
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		LastTimePoint = CurTimePoint;
	}

	if(MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if(!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix,64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;
	
	// LocalEntity
	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
			continue;
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		if (!Entity.IsAlive())
			continue;

		// Add entity to radar
		if(MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({Gui.Window.Size.x / 2,Gui.Window.Size.y / 2});


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;
			if (MenuConfig::VisibleCheck && Entity.Pawn.bSpottedByMask > 0 || !MenuConfig::VisibleCheck)
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		// Draw Bone
		if(MenuConfig::ShowBoneESP)
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);

		// Draw eyeRay
		if(MenuConfig::ShowEyeRay)
			Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);

		// Box
		ImVec4 Rect;
		switch (MenuConfig::BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		default:
			break;
		}

		// Line to enemy
		if (MenuConfig::ShowLineToEnemy)
			Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

		// Draw Box
		if (MenuConfig::ShowBoxESP)
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3);

		// Draw HealthBar
		if (MenuConfig::ShowHealthBar)
		{
			ImVec2 HealthBarPos, HealthBarSize;
			if (MenuConfig::HealthBarType == 0)
			{
				// Vertical
				HealthBarPos = { Rect.x - 7.f,Rect.y };
				HealthBarSize = { 7 ,Rect.w };
			}
			else
			{
				// Horizontal
				HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
				HealthBarSize = { 70,8 };
			}
			Render::DrawHealthBar(EntityAddress, 100, Entity.Controller.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
		}

		// Draw weaponName
		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
		}

	}

	// Fov line
	if (MenuConfig::ShowFovLine)
		Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// Radar render
	if (MenuConfig::ShowRadar)
	{
		Radar.Render();
		//End for radar window
		ImGui::End();
	}

	// TriggerBot
	if (MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey))
		TriggerBot::Run(LocalEntity);

	// HeadShoot Line
	if(MenuConfig::ShowHeadShootLine)
		Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);

	// CrossHair
	if (MenuConfig::ShowCrossHair)
		Render::DrawCrossHair();

	// Fov circle
	if(MenuConfig::ShowAimFovRange)
		Render::DrawFovCircle(LocalEntity);
	
	if (MenuConfig::BunnyHop)
		Bunnyhop::Run(LocalEntity);

	if (MenuConfig::AimBot && GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}
