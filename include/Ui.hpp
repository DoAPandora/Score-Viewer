#include "questui/shared/QuestUI.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/UI/Button.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

// other code

extern "C" void load() {
    // make sure this is after il2cpp_functions::Init()
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    // other code

    UnityEngine::GameObject* self, bool firstActivation;
}