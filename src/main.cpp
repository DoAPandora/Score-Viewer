#include "main.hpp"

#include "include/ScoreSaberData.hpp"
#include "include/BeatLeaderData.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

MAKE_HOOK_MATCH(MainMenuUIHook, &GlobalNamespace::MainMenuViewController::DidActivate, void,
 GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
MainMenuUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

UnityEngine::UI::Button* soloMenuButton = self->soloButton;
    UnityEngine::GameObject* gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro* soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro*>();

    // Set the text to "Score Viewer"
    soloMenuText->SetText("Score Viewer");

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

// Regsiter our Settings
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), ActivateFlowCoordinatorHook);
    INSTALL_HOOK(getLogger(), FixedUpdateHook);
    INSTALL_HOOK(getLogger(), LevelSelectionNavigationControllerDidActivate);
    INSTALL_HOOK(getLogger(), LevelSelectionNavigationControllerDidDeactivate);
    INSTALL_HOOK(getLogger(), MainMenuUIHook);
    getLogger().info("Installed all hooks!");
    
}
