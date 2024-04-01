#include "main.hpp"

#include "ModSettingsView.hpp"
#include "bsml/shared/BSML.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"

#include "GlobalNamespace/LevelListTableCell.hpp"
#include "paper/shared/logger.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "HMUI/ImageView.hpp"
#include "TMPro/TMP_Text.hpp"
#include "song-details/shared/SongDetails.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

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

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

using namespace GlobalNamespace;

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

bool hasLoaded = false;

MAKE_HOOK_MATCH(MainMenuViewControllerDidActivate, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuViewControllerDidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if(firstActivation) {
        hasLoaded = true;
    }
}

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
extern "C" void setup(CModInfo& info) {
    info.id = modInfo.id.c_str();
    info.version = modInfo.version.c_str();
    info.version_long = modInfo.versionLong;

    Paper::Logger::RegisterFileContextId(MOD_ID);

    getConfig().Load();
    logger.info("Completed setup!");
}

extern "C" void load() {
    il2cpp_functions::Init();
    BSML::Init();
    BSML::Register::RegisterSettingsMenu("Score Viewer", DidActivate, false);

    if(!getConfig().config.HasMember("Enabled")) {
        getConfig().config.AddMember("Enabled", true, getConfig().config.GetAllocator());
        getConfig().Write();
    }

    logger.info("Registered Mod Settings!");


    logger.info("Installing hooks...");
    INSTALL_HOOK(logger, MainMenuViewControllerDidActivate);
    logger.info("Installed all hooks!");
}
