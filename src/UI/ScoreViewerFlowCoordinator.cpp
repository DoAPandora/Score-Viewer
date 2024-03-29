#include "UI/ScoreViewerFlowCoordinator.hpp"

#include "bsml/shared/Helpers/creation.hpp"
#include "bsml/shared/Helpers/getters.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "UnityEngine/Resources.hpp"

DEFINE_TYPE(ScoreViewer::UI, GraphicsTweaksFlowCoordinator);

void ScoreViewer::UI::ScoreViewerFlowCoordinator::Awake() {
    fcInstance = this;
    if (!settings) {
        settings = BSML::Helpers::CreateViewController<ScoreViewer::UI::Settings*>();
       }
}

void ScoreViewer::UI::ScoreViewerFlowCoordinator::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    SetTitle(il2cpp_utils::newcsstr("Score Viewer"), HMUI::ViewController::AnimationType::In);
    this->____showBackButton = true;
    ProvideInitialViewControllers(settings, advancedSettings, nullptr, nullptr);
}

void ScoreViewer::UI::ScoreViewerFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    this->Close();
}

void ScoreViewer::UI::ScoreViewerFlowCoordinator::Close(bool immediately){
    // Do nothing if there's no parent flow coordinator
}