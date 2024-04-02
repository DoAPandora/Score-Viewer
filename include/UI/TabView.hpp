#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"

#include "songcore/shared/SongCore.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "bsml/shared/BSML/Components/CustomListTableData.hpp"
#include "bsml/shared/BSML/Components/Keyboard/ModalKeyboard.hpp"
#include "bsml/shared/BSML/Parsing/BSMLParserParams.hpp"

DECLARE_CLASS_CODEGEN(ScoreViewer, ScoreMenu, UnityEngine::MonoBehaviour,

public:

    UnorderedEventCallback<> didEnable;
    UnorderedEventCallback<> didDisable;

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnDisable);

    DECLARE_DEFAULT_CTOR();
)

DECLARE_CLASS_CODEGEN(ScoreViewer, ScoreMenu, UnityEngine::MonoBehaviour,

    //Menu status + detail view controller
    DECLARE_INSTANCE_FIELD(ScoreMenuStatus*, menuStatus);
    DECLARE_INSTANCE_FIELD(bool, scoreMenuInitialized);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::IPreviewBeatmapLevel*, currentLevel);
    DECLARE_INSTANCE_FIELD(bool, currentLevelIsPlaylistSong); // is this even needed on quest ?
    DECLARE_INSTANCE_FIELD(int, selectedCell);

    static inline ScoreMenu* instance;

public:

    static ScoreMenu* get_instance();

    std::optional<ExtraSongData::ExtraSongData> extraSongData;
    std::optional<ExtraSongData::DifficultyData> difficultyData;

    std::shared_ptr<BSML::BSMLParserParams> bsmlParserParams;
    // download controller, search controller, result array

    DECLARE_DEFAULT_CTOR();

    DECLARE_INSTANCE_METHOD(void, Init);
    DECLARE_INSTANCE_METHOD(void, CreateStatusListener);
    DECLARE_INSTANCE_METHOD(void, AddTab);
    DECLARE_INSTANCE_METHOD(void, RemoveTab);
    DECLARE_INSTANCE_METHOD(void, ResetScoreViewerMenu);
    DECLARE_INSTANCE_METHOD(void, SetButtonState, bool state);
    DECLARE_INSTANCE_METHOD(void, SetupScoreDetails);
    DECLARE_INSTANCE_METHOD(void, SetThumbnailFromCover, GlobalNamespace::IPreviewBeatmapLevel* level);
    DECLARE_INSTANCE_METHOD(void, SetSelectedLevel, GlobalNamespace::IPreviewBeatmapLevel* level);
    DECLARE_INSTANCE_METHOD(void, HandleDidSelectLevel, GlobalNamespace::IPreviewBeatmapLevel* level, bool isPlaylistSong = false);
    DECLARE_INSTANCE_METHOD(void, OnLevelSelected, GlobalNamespace::IPreviewBeatmapLevel* level);
    DECLARE_INSTANCE_METHOD(void, StatusViewerDidEnable);
    DECLARE_INSTANCE_METHOD(void, StatusViewerDidDisable);
    DECLARE_INSTANCE_METHOD(void, ApplyOffset, int offset);
    DECLARE_INSTANCE_METHOD(void, SearchAction);
    DECLARE_INSTANCE_METHOD(void, ShowKeyboard);
    DECLARE_INSTANCE_METHOD(void, OnRefineAction);
    DECLARE_INSTANCE_METHOD(void, OnDeleteVideoAction);
    DECLARE_INSTANCE_METHOD(void, OnDeleteConfigAction);
    DECLARE_INSTANCE_METHOD(void, OnBackAction);
    DECLARE_INSTANCE_METHOD(void, SearchFinished);
    DECLARE_INSTANCE_METHOD(void, ResetSearchView);
    DECLARE_INSTANCE_METHOD(void, OnQueryAction, StringW query);
    DECLARE_INSTANCE_METHOD(void, OnSelectCell, HMUI::TableView* view, int idx);

    DECLARE_INSTANCE_METHOD(void, set_CustomizeOffset, bool value);
    DECLARE_INSTANCE_METHOD(bool, get_CustomizeOffset);

public:

    void OnDownloadProgress(ScoreConfigPtr scoreConfig);
    void CheckEntitlementAndEnableSearch(GlobalNamespace::IPreviewBeatmapLevel* level);
    void SetupLevelDetailView(ScoreConfigPtr scoreConfig);
    void UpdateStatusText(ScoreConfigPtr scoreConfig);
    void OnDifficultySelected(ExtraSongDataArgs extraSongDataArgs);
)