#include "ConfigMenu.hpp"
#include "../MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../TriggerBot.h"
#include "../AimBot.hpp"
#include <filesystem>

namespace ConfigMenu {

    void RenderConfigMenu() {
		// Config
		if (ImGui::BeginTabItem(u8"≈‰÷√ "))
		{
			static char configNameBuffer[128] = "";

			ImGui::InputText(u8"–¬≈‰÷√√˚", configNameBuffer, sizeof(configNameBuffer));

			if (ImGui::Button(u8"¥¥Ω®≈‰÷√"))
			{
				std::string configFileName = std::string(configNameBuffer) + ".config";
				MyConfigSaver::SaveConfig(configFileName);
			}

			ImGui::Separator();

			static int selectedConfig = -1;

			const std::string configDir = std::filesystem::current_path().string();
			static std::vector<std::string> configFiles;

			configFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(configDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".config")
				{
					configFiles.push_back(entry.path().filename().string());
				}
			}

			for (int i = 0; i < configFiles.size(); ++i)
			{
				if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
				{
					selectedConfig = i;
				}
			}

			if (selectedConfig != -1)
			{
				ImGui::Text(u8"—°‘Òµƒ≈‰÷√: %s", configFiles[selectedConfig].c_str());
			}

			if (ImGui::Button(u8"‘ÿ»Î≈‰÷√") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::LoadConfig(selectedConfigFile);
			}

			if (ImGui::Button(u8"±£¥Ê≈‰÷√") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
			}

			ImGui::Separator();

			if (ImGui::Button(u8"…æ≥˝≈‰÷√") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				std::string fullPath = configDir + "/" + selectedConfigFile;
				if (std::remove(fullPath.c_str()) == 0)
				{
					configFiles.erase(configFiles.begin() + selectedConfig);
					selectedConfig = -1;
				}
				else
				{
				}
			}

			if (ImGui::Button(u8"÷ÿ÷√Œ™ƒ¨»œ÷µ"))
			{
				ConfigMenu::ResetToDefault();
			}

			ImGui::EndTabItem();
		}
    }

    void ResetToDefault() {
		MenuConfig::ShowBoneESP = true;
		MenuConfig::ShowBoxESP = true;
		MenuConfig::ShowHealthBar = true;
		MenuConfig::ShowWeaponESP = true;
		MenuConfig::ShowDistance = true;
		MenuConfig::ShowEyeRay = true;
		MenuConfig::ShowPlayerName = true;
		MenuConfig::AimBot = true;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		MenuConfig::BoneColor = ImVec4(255, 255, 255, 255);
		MenuConfig::BoxColor = ImVec4(255, 255, 255, 255);
		MenuConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowRadar = true;
		MenuConfig::RadarRange = 150;
		MenuConfig::ShowRadarCrossLine = true;
		MenuConfig::RadarCrossLineColor = ImVec4(34, 34, 34, 180);
		MenuConfig::RadarType = 2;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::Proportion = 2230;
		MenuConfig::TriggerBot = true;
		MenuConfig::TeamCheck = true;
		MenuConfig::VisibleCheck = true;
		MenuConfig::ShowHeadShootLine = true;
		MenuConfig::HeadShootLineColor = ImVec4(255, 255, 255, 255);
		MenuConfig::AimBotHotKey = 0;
		MenuConfig::ShowLineToEnemy = false;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		AimControl::RCSBullet = 1;
		TriggerBot::HotKey = VK_LMENU;
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
		MenuConfig::ShowCrossHair = true;
		MenuConfig::CrossHairColor = ImColor(45, 45, 45, 255);
		MenuConfig::CrossHairSize = 150;
		MenuConfig::ShowAimFovRange = true;
		MenuConfig::AimFovRangeColor= ImColor(230, 230, 230, 255);
		MenuConfig::OBSBypass = true;
		MenuConfig::BunnyHop = false;
    }
}
