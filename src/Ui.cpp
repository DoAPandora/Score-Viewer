#include "Ui.hpp"
#include "main.hpp"
#include "bsml-lite/shared/Image.hpp"
#include "assets.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.
    if(firstActivation) {
        // Create a container that has a scroll bar
        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        // Create a text that says "Score Viewer" and set the parent to the container.
        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Score Viewer");

        // Button for showing your rank on that song
        button = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "Get Song Rank Data", UnityEngine::Vector2(-70, 30), UnityEngine::Vector2(9.0f, 9.0f)),

        BSML::ClickableImage* CreateClickableImage(const TransformWrapper& parent, UnityEngine::Sprite* sprite, std::function<void()> onClick = nullptr, UnityEngine::Vector2 anchoredPosition = {-70, 30}, UnityEngine::Vector2 sizeDelta = {9.0f, 9.0f});
    }
}