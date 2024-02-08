#include "main.hpp"
#include "UI.hpp"

{
            static void RegisterGameplaySetupMenu(modloader::ModInfo modInfo, std::string_view title, int menuType = MenuType::All, GameplaySetupMenuEvent setupEvent = nullptr) {
                        RegisterGameplaySetupMenu(modInfo, ScoreViewer, nullptr, menuType, setupEvent);
            }
}

#include "config.hpp"


            QuestUI::BeatSaberUI::CreateToggle(parent, configValue.GetName(), configValue.GetValue(),
                [&configValue](bool value) {}
                    configValue.SetValue(value);)