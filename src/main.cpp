#include "main.hpp"

#include "include/ScoreSaberData.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

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
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    
    getLogger().info("Installed all hooks!");
}

namespace ScoreSaber::Data
{
    LeaderboardPlayer::LeaderboardPlayer(const rapidjson::Value&& value)
    {
        auto idItr = value.FindMember("id");
        if (idItr != value.MemberEnd())
        {
            id = std::make_optional(std::string(idItr->value.GetString()));
        }

        auto nameItr = value.FindMember("name");
        if (nameItr != value.MemberEnd())
        {
            name = std::make_optional(to_utf16(std::string(nameItr->value.GetString())));
        }

        profilePicture = value["profilePicture"].GetString();

        auto countryItr = value.FindMember("country");
        if (countryItr != value.MemberEnd())
        {
            country = std::make_optional(std::string(countryItr->value.GetString()));
        }

        auto permissionsItr = value.FindMember("permissions");
        if (permissionsItr != value.MemberEnd())
        {
            permissions = std::make_optional(int(permissionsItr->value.GetInt()));
        }

        auto roleItr = value.FindMember("role");
        if (roleItr != value.MemberEnd() && roleItr->value.IsString())
            role = std::make_optional(std::string(roleItr->value.GetString()));
    }
}