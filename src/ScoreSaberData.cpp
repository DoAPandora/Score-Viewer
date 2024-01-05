#include "beatsaber-hook/shared/utils/utils.h"
#include "include/ScoreSaberData.hpp"

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