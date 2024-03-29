#include "main.hpp"

#include "config.hpp"
#include "bsml/shared/BSML.hpp"
#include "UI/ScoreViewerFlowCoordinator.hpp"

#include "logging.hpp"

#include "GlobalNamespace/LevelListTableCell.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "HMUI/ImageView.hpp"

#include "TMPro/TMP_Text.hpp"

#include "song-details/shared/SongDetails.hpp"

SongDetailsCache::SongDetails* songDetails;

enum class RankedStatus {
    Beatleader,
    Scoresaber,
    Ranked,
    None
};

std::map<RankedStatus, std::string> texts = {
    {RankedStatus::None, "new"}, // default cell text
    {RankedStatus::Ranked, "Ranked"},
    {RankedStatus::Beatleader, "BL Ranked"},
    {RankedStatus::Scoresaber, "SS Ranked"}
};

RankedStatus GetRankedStatus(std::string hash)
{
    const SongDetailsCache::Song* song;
    if(!songDetails->songs.FindByHash(hash, song))
        return RankedStatus::None;

    using Ranked = SongDetailsCache::RankedStates;
    auto& states = song->rankedStates;

    if(SongDetailsCache::hasFlags(states, Ranked::BeatleaderRanked) && SongDetailsCache::hasFlags(states, Ranked::ScoresaberRanked))
        return RankedStatus::Ranked;
    if(SongDetailsCache::hasFlags(states, Ranked::BeatleaderRanked))
        return RankedStatus::Beatleader;
    if(SongDetailsCache::hasFlags(states, Ranked::ScoresaberRanked))
        return RankedStatus::Scoresaber;

    return RankedStatus::None;
}

MAKE_HOOK_MATCH(LevelListTableCell_SetDataFromLevelAsync, &GlobalNamespace::LevelListTableCell::SetDataFromLevelAsync, void, GlobalNamespace::LevelListTableCell* self, GlobalNamespace::IPreviewBeatmapLevel* level, bool isFavorite, bool isPromoted, bool isUpdated)
{
    LevelListTableCell_SetDataFromLevelAsync(self, level, isFavorite, isPromoted, isUpdated);
    if(!songDetails->songs.get_isDataAvailable())
        return;


    RankedStatus rankedStatus = RankedStatus::None;

    if(level->get_levelID()->StartsWith("custom_level"))
    {
        StringW hash = level->get_levelID()->Substring(13);
        rankedStatus = GetRankedStatus(static_cast<std::string>(hash));
    }

    bool isRanked = rankedStatus != RankedStatus::None;
}
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
extern "C" void load()
{
    il2cpp_functions::Init();

    songDetails = SongDetailsCache::SongDetails::Init(0).get();

    // BSML::Register::RegisterMenuButton<
    BSML::Register::RegisterSettingsMenu<ScoreViewer::UI::ScoreViewerFlowCoordinator*>("ScoreViewer");
    INFO("Registered settings menu!");
    INFO("ScoreViewer loaded!");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), LevelListTableCell_SetDataFromLevelAsync);
    getLogger().info("Installed all hooks!");
}
