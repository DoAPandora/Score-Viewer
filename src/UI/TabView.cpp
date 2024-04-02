#include "main.hpp"

#include "TabView.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/utilities.hpp"

DEFINE_TYPE(ScoreViewer, ScoreMenu);
DEFINE_TYPE(ScoreViewer, ScoreMenuStatus);

namespace ScoreViewer {

    void ScoreMenu::AddTab()
    {
        DEBUG("Adding tab");
        BSML::Register::RegisterGameplaySetupTab("Score Viewer", [this](UnityEngine::GameObject* go, bool firstActivation)
        {
            if (firstActivation)
        });
    }

    void ScoreMenu::RemoveTab()
    {
        DEBUG("Removing tab");
        BSML::Register::UnRegisterGameplaySetupTab("Score Viewer");
    }

    void ScoreMenu::ResetScoreMenu()
    {
        DEBUG("BSMLParserParams: {}", fmt::ptr(bsmlParserParams.get()));
        bsmlParserParams->EmitEvent("hide-keyboard");
        noLevelBg->get_gameObject()->SetActive(true);
        ScoreDetails->get_gameObject()->SetActive(false);
        SetButtonState(false);

        if (!getModConfig().enabled.GetValue())

        if (!currentLevel)
        {
            noLevelText->SetTextInternal("No Level Selected");
            return;
        }
    }

        if (currentLevel)
        {
            CheckEntitlementAndEnableSearch(currentLevel);
        }

        {
            return;
        }

        auto officialConfig = *currentLevel->configByMapper;
        deleteConfigButton->get_gameObject()->SetActive(!officialConfig);

        switch (currentLevel->GettingDataState) {
                cancelGettingSongDataButtonText->SetTextInternal("Cancel");
                deleteVideoButton->get_transform()->Find(
                        "Underline")->get_gameObject()->GetComponent<UnityEngine::UI::Image *>()->set_color(
                        UnityEngine::Color::get_gray());
                break;
        }
}

    void ScoreMenu::CheckEntitlementAndEnableSearch(GlobalNamespace::IPreviewBeatmapLevel *level)
    {
        //auto entitlement =
    }

    void ScoreMenu::SetThumbnail(std::optional<std::string> url)
    {
        if (url != std::nullopt && url == thumbnailURL)
        {
            return;
        }

        thumbnailURL = url;

        if (url == std::nullopt)
        {
            SetThumbnailFromCover(currentLevel);
            return;
        }

        BSML::Utilities::SetImage(videoThumbnail, *url);
    }

    void ScoreMenu::SetThumbnailFromCover(GlobalNamespace::IPreviewBeatmapLevel *level) {}

    void ScoreMenu::SetSelectedLevel(GlobalNamespace::IPreviewBeatmapLevel *level)
    {
        if (currentLevel && currentLevel->get_levelID() == level->get_levelID())
        {
            return;
        }

        DEBUG("Setting level to {}", level->get_levelID());
        HandleDidSelectLevel(level);
    }

    void ScoreMenu::HandleDidSelectLevel(GlobalNamespace::IPreviewBeatmapLevel *level, bool isPlaylistSong)
    {
        extraSongData = std::nullopt;
        difficultyData = std::nullopt;

        if (!getModConfig().enabled.GetValue() || !level)
        {
            return;
        }

    void ScoreMenu::OnLevelSelected(GlobalNamespace::IPreviewBeatmapLevel *level)
    {
        HandleDidSelectLevel(level);
    }

    void ScoreMenu::OnDifficultySelected(ScoreViewer::ExtraSongDataArgs extraSongDataArgs)
    {
        extraSongData = extraSongDataArgs.songData;
        difficultyData = extraSongDataArgs.selectedDifficultyData;
        if(currentLevel != nullptr)
    }
}