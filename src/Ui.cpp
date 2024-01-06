
#include "main.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML/Components/ClickableImage.hpp"
#include "questui/shared/QuestUI.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.
    if(firstActivation) {
        
        BSML::ClickableImage* CreateClickableImage(const TransformWrapper& parent, UnityEngine::Sprite* sprite, std::function<void()> onClick = nullptr, UnityEngine::Vector2 anchoredPosition = {-70, 30}, UnityEngine::Vector2 sizeDelta = {9.0f, 9.0f}
    }
}
