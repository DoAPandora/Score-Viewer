#include "main.hpp"
#include "config-utils/shared/config-utils.hpp"

{
    auto object = ::QuestUI::BeatSaberUI::CreateToggle(parent, configValue.GetName(), configValue.GetValue()),
}
    bool operator==(const ConfigValue<ValueType>& other) const {
                return *value == other.GetValue()
                    && defaultValue == other.GetDefaultValue()
                    && ScoreViewer == other.GetName()
}