#include "UI/Settings.hpp"
#include "bsml/shared/BSML.hpp"

#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/OVRPlugin.hpp"

#include "assets.hpp"
#include "logging.hpp"

DEFINE_TYPE(ScoreViewer::UI, Settings);

void ScoreViewer::UI::Settings::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling)
{
    if (!firstActivation)
        return;

    INFO("Settings activated");

    // Get possible values
    auto frequencies = GlobalNamespace::OVRPlugin::get_systemDisplayFrequenciesAvailable();
    // Create lists
    systemDisplayFrequenciesAvailableValues = ListW<float>::New();
    systemDisplayFrequenciesAvailableLabels = ListW<StringW>::New();
    for (const auto& item : frequencies) {
        systemDisplayFrequenciesAvailableValues->Add(item);
        systemDisplayFrequenciesAvailableLabels->Add(fmt::format("{}", item));
    }
  

    DEBUG("Got values");

    //BSML::parse_and_construct(Assets::Settings_bsml, this->get_transform(), this);

    #ifdef HotReload
        fileWatcher->checkInterval = 0.5f;
        fileWatcher->filePath = "/sdcard/bsml/ScoreViewer/Settings.bsml";
    #endif
};

void ScoreViewer::UI::Settings::PostParse() {
    DEBUG("Settings PostParse");

       void ScoreViewer::UI::Settings::UpdateSettings()
       INFO("Updating settings");

       INFO("Updated settings")
    }