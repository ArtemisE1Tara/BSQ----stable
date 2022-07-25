#pragma once
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(QuestUI, IncrementSetting, UnityEngine::MonoBehaviour,

    DECLARE_INSTANCE_FIELD(int, Decimals);
    DECLARE_INSTANCE_FIELD(float, Increment);
    DECLARE_INSTANCE_FIELD(float, CurrentValue);
    DECLARE_INSTANCE_FIELD(bool, HasMin);
    DECLARE_INSTANCE_FIELD(bool, HasMax);
    DECLARE_INSTANCE_FIELD(float, MinValue);
    DECLARE_INSTANCE_FIELD(float, MaxValue);
    public:
        std::function<void(float)> OnValueChange;
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, Text);

    DECLARE_INSTANCE_METHOD(StringW, GetRoundedString);
    DECLARE_INSTANCE_METHOD(void, IncButtonPressed);
    DECLARE_INSTANCE_METHOD(void, DecButtonPressed);
    DECLARE_INSTANCE_METHOD(void, UpdateValue);

)