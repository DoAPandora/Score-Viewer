#include "UI/AdvancedSettings.hpp"
#include "assets.hpp"
#include "logging.hpp"

DEFINE_TYPE(ScoreViewer::UI, AdvancedSettings);

void ScoreViewer::UI::AdvancedSettings::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling)
{
    if (!firstActivation)
        return;

    INFO("AdvancedSettings activated");

    //BSML::parse_and_construct(Assets::AdvancedSettings_bsml, this->get_transform(), this);
    #ifdef HotReload
        fileWatcher->filePath = "/sdcard/bsml/ScoreViewer/AdvancedSettings.bsml";
    #endif
};