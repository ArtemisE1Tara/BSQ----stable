#include "main.hpp"

#include "custom-types/shared/register.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/UnityScenesHelper.hpp"
using namespace GlobalNamespace;

#include "TMPro/TextAlignmentOptions.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
using namespace TMPro;

#include "HMUI/CurvedTextMeshPro.hpp"

#include "UnityEngine/TextAnchor.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
using namespace UnityEngine;
using namespace UnityEngine::UI;

#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"

namespace cm {
	void updateMenuText(MainMenuViewController* self) {
		// My method didn't work, so I took one from BeatTogethor

		// my method:
		// UnityEngine::GameObject::Find(StringW("SoloButton"))->
		// GetComponent<TMPro::TextMeshProUGUI*>()->
		// set_text(getModConfig().SoloText.GetValue());

		// TODO: This should be using macros

		static auto* soloSearchPath = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("MainContent/SoloButton/Text");
    	TMPro::TextMeshProUGUI* soloButtonText = self->get_gameObject()->get_transform()->Find(soloSearchPath)->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
		soloButtonText->set_text(getModConfig().SoloText.GetValue());
		
		static auto* onlineSearchPath = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("MainContent/OnlineButton/Text");
    	TMPro::TextMeshProUGUI* onlineButtonText = self->get_gameObject()->get_transform()->Find(onlineSearchPath)->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
		onlineButtonText->set_text(getModConfig().OnlineText.GetValue());
		
		static auto* campaignSearchPath = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("MainContent/CampaignButton/Text");
    	TMPro::TextMeshProUGUI* campaignButtonText = self->get_gameObject()->get_transform()->Find(campaignSearchPath)->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
		campaignButtonText->set_text(getModConfig().CampaignText.GetValue());

		static auto* partySearchPath = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("MainContent/PartyButton/Text");
    	TMPro::TextMeshProUGUI* partyButtonText = self->get_gameObject()->get_transform()->Find(partySearchPath)->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
		partyButtonText->set_text(getModConfig().PartyText.GetValue());
	}
} // namespace cm
