#pragma once
#include "Game.h"
#include "Bone.h"

namespace MenuConfig
{
	inline bool ShowBoneESP = false;
	inline bool ShowBoxESP = false;
	inline bool ShowHealthBar = false;
	inline bool ShowWeaponESP = false;
	inline bool ShowEyeRay = false;
	inline bool ShowPlayerName = false;

	inline bool AimBot = false;
	inline int AimBotHotKey = 0;
	// 0: head 1: neck 3: spine
	inline int  AimPosition = 0;
	inline bool ShowAimFovRange = false;
	inline ImColor AimFovRangeColor = ImColor(230, 230, 230, 255);
	inline DWORD  AimPositionIndex = BONEINDEX::head;
	inline bool VisibleCheck = false;
	// 0: normal 1: dynamic
	inline int  BoxType = 0;
	// 0: Vertical 1: Horizontal
	inline int  HealthBarType = 0;

	inline ImColor BoneColor = ImColor(255, 255, 255, 255);
	inline ImColor BoxColor = ImColor(255, 255, 255, 255);
	inline ImColor EyeRayColor = ImColor(255, 0, 0, 255);

	inline bool ShowMenu = true;

	inline bool ShowRadar = false;
	inline float RadarRange = 150;
	inline float RadarPointSizeProportion = 1.f;
	inline bool ShowRadarCrossLine = false;
	inline ImColor RadarCrossLineColor = ImColor(220, 220, 220, 255);
	// 0: circle 1: arrow 2: circle with arrow
	inline int RadarType = 2;
	inline float Proportion = 2230;

	inline bool TriggerBot = false;
	inline int TriggerHotKey = 0;

	inline bool TeamCheck = false;
	inline bool OBSBypass = true;

	inline bool BunnyHop = false;
	
	inline bool ShowHeadShootLine = false;
	inline ImColor HeadShootLineColor = ImColor(255, 255, 255, 255);

	inline bool ShowFovLine = false;
	inline ImColor FovLineColor = ImColor(55, 55, 55, 220);
	inline float FovLineSize = 60.f;

	inline bool ShowLineToEnemy = false;
	inline ImColor LineToEnemyColor = ImColor(255, 255, 255, 220);

	inline bool ShowCrossHair = false;
	inline ImColor CrossHairColor = ImColor(45, 45, 45, 255);
	inline float CrossHairSize = 150;
}