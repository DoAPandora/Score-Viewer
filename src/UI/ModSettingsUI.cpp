#include "bsml/shared/BSML.hpp"
#include "ScoreViewerFlowCoordinator.hpp"

        static inline bool RegisterSettingsMenu(std::string_view ScoreViewer, bool enableExtraButtons = false) {
            return RegisterSettingsMenu(ScoreViewer, csTypeOf(T), MenuSource::ViewController, enableExtraButtons);
        }
        
        bool RegisterSettingsMenu(std::string_view ScoreViewer, std::function<void(HMUI::ViewController*, bool, bool, bool)> viewControllerDidActivate, bool enableExtraButtons);
        