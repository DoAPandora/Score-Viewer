#include "main.hpp"
#include "include/BeatLeader.hpp"

Player::Player(rapidjson::Value const& userModInterface) {

    id = userModInterface["id"].GetString();
    name = userModInterface["name"].GetString();
    country = userModInterface["country"].GetString();
    avatar = userModInterface["avatar"].GetString();
    role = userModInterface["role"].GetString();

    // For standard context and players from v3/scores (where contextExtension is null cause we request for one context) we use the main player
    //int currentContext = getConfig();
    std::optional<rapidjson::GenericArray<true, rapidjson::Value>> contextExtensions = userModInterface.HasMember("contextExtensions") && !userModInterface["contextExtensions"].IsNull() ? userModInterface["contextExtensions"].GetArray() : std::optional<rapidjson::GenericArray<true, rapidjson::Value>>();
    // If we are Standard Context or we have no contexts or our selected context is not in contextextensions we use the normal rank. Else we use the correct context extension rank
    rapidjson::Value const& contextRank = currentContext == 0 || !contextExtensions || currentContext - 1 >= contextExtensions.value().Size() ? userModInterface : contextExtensions.value()[currentContext - 1];

    rank = contextRank["rank"].GetInt();
    countryRank = contextRank["countryRank"].GetInt();
    pp = contextRank["pp"].GetFloat();
}
