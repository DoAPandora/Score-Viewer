#include "questui/shared/QuestUI.hpp"

    void(*DidActivateEvent)(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
        void(*GameplaySetupMenuEvent)(UnityEngine::GameObject* self, bool firstActivation);