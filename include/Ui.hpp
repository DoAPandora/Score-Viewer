#include "questui/shared/QuestUI.hpp"

// other code

extern "C" void load() {
    // make sure this is after il2cpp_functions::Init()
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    // other code

    UnityEngine::GameObject* self, bool firstActivation
}