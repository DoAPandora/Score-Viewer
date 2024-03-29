#pragma once

#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

DECLARE_CLASS_CODEGEN(ScoreViewer::UI, ScoreViewerFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(ScoreViewer::UI::Settings*, settings);

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::FlowCoordinator::DidActivate, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, BackButtonWasPressed, &HMUI::FlowCoordinator::BackButtonWasPressed, HMUI::ViewController* topViewController);

    void Close(bool immediately = false);

    )
