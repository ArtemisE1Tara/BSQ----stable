#include "UI/Settings/CmSettingsViewController.hpp"
#include "main.hpp"
using namespace cm;

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/TextAnchor.hpp"
using namespace UnityEngine;
using namespace UnityEngine::UI;

#include "TMPro/TextAlignmentOptions.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
using namespace TMPro;

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
using namespace QuestUI;

#include "modloader/shared/modloader.hpp"

#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"

DEFINE_TYPE(cm, CmSettingsViewController);

#define SETTING_INPUT(configType, savefunction) \
	BeatSaberUI::CreateStringSetting(layout->get_transform(), StringW(getModConfig().configType.GetHoverHint()), StringW(getModConfig().configType.GetValue()), savefunction);

void saveSolo(StringW value)		{ getModConfig().SoloText.SetValue(value);		}
void saveOnline(StringW value)		{ getModConfig().OnlineText.SetValue(value);	}
void saveCampaign(StringW value)	{ getModConfig().CampaignText.SetValue(value);	}
void saveParty(StringW value)		{ getModConfig().PartyText.SetValue(value);		}

void CmSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
	if (!(firstActivation && addedToHierarchy))
		return;

	VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(this->get_rectTransform());
	layout->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredWidth(80.0f);
	layout->set_childAlignment(UnityEngine::TextAnchor::UpperCenter);
	layout->set_childControlHeight(false);
	layout->set_childForceExpandHeight(false);

	SETTING_INPUT(SoloText, saveSolo);
	SETTING_INPUT(OnlineText, saveOnline);
	SETTING_INPUT(CampaignText, saveCampaign);
	SETTING_INPUT(PartyText, saveParty);

}