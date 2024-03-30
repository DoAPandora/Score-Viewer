#include "bsml/shared/BSML.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.
    if(firstActivation) {
        
        // Create a container that has a scroll bar
        UnityEngine::GameObject* container = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());

        BSML::Lite::CreateText(container->get_transform(), "Score Viewer");
    }
}