#include "main.hpp"
#include "UI.hpp"
#include "Config.hpp"

#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(ScoreViewer, SettingsViewController);

void ScoreViewer::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if(!firstActivation)
        return;

    auto container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform())->get_transform();

    AddConfigValueToggle(container, getModConfig().Enabled);
    AddConfigValueToggle(container, getModConfig().DifferentColor);
    AddConfigValueToggle(container, getModConfig().DifferentText);
}