#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(ModEnabled, bool, "Custom solo text. (Skill Issue)", false);
    CONFIG_VALUE(ImageCoverExpanderEnabled, bool, "Image Cover Expander.", false);
    CONFIG_VALUE(FullComboEffectsEnabled, bool, "Full Combo Effects.", false);
    CONFIG_VALUE(SearchFixesEnabled, bool, "Enable Search Fixes.", false);
    CONFIG_VALUE(NoteJumpSpeed, float, "Note Jump Speed", 1.0f);
    CONFIG_VALUE(NoteJumpSpeedEnabled, bool, "Enable custom note jump speed", false);
    CONFIG_VALUE(Clicked, int, "Clicked", 0);
    CONFIG_VALUE(RotationEnabled, bool, "Enable Rotation", false);
    CONFIG_VALUE(RotationIncrement, float, "Rotation Increment", 0.0f);
    CONFIG_VALUE(Test, std::string, "Test", "TEST!");
    CONFIG_VALUE(SwapColours, bool, "A jank colour swap", false);
    CONFIG_VALUE(ScreenTextChanger, bool, "Respawns the screen ", false);
    CONFIG_VALUE(NJSTEST, float, "NJSTEST", 0.0f);
    CONFIG_VALUE(XPos, float, "XPos", 0);
    CONFIG_VALUE(YPos, float, "YPos", 0);
    CONFIG_VALUE(ZPos, float, "ZPos", 0);
    CONFIG_VALUE(XRot, float, "XRot", 0);
    CONFIG_VALUE(YRot, float, "YRot", 0);
    CONFIG_VALUE(ZRot, float, "ZRot", 0);
    CONFIG_VALUE(Scale, float, "Scale", 0.2f);
    CONFIG_VALUE(SoloText, std::string, "Solo Button Text", "SOLO!");
	CONFIG_VALUE(OnlineText, std::string, "Online Button Text", "ONLINE!");
	CONFIG_VALUE(CampaignText, std::string, "Campaign Button Text", "CAMPAIGN!");
	CONFIG_VALUE(PartyText, std::string, "Party Button Text", "PARTY!");
    CONFIG_VALUE(Rainbow, bool, "Rainbow Bar when full energy", true);
    CONFIG_VALUE(AlwaysRainbow, bool, "Always Rainbow Bar", false);
    CONFIG_VALUE(Fadeout, bool, "Fadeout", false);
    CONFIG_VALUE(FullFade, bool, "Use fade between 15% and 95% colors", false);
    CONFIG_VALUE(Alpha, float, "Alpha", 1.0);
    CONFIG_VALUE(Diehp, UnityEngine::Color, "under 15% energy", UnityEngine::Color(1.0f, 0.0f, 0.0f, 0.0f));
    CONFIG_VALUE(Lowhp, UnityEngine::Color, "under 50% energy", UnityEngine::Color(1.0f, 0.0f, 0.0f, 0.0f));
    CONFIG_VALUE(Midhp, UnityEngine::Color, "over 70% energy", UnityEngine::Color(0.0f, 1.0f, 0.0f, 0.0f));
    CONFIG_VALUE(Highhp, UnityEngine::Color, "over 95% energy", UnityEngine::Color(0.0f, 1.0f, 1.0f, 0.0f));
    CONFIG_VALUE(Defhp, UnityEngine::Color, "over 50% energy", UnityEngine::Color(1.0f, 1.0f, 1.0f, 0.0f));



    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(ModEnabled);
        CONFIG_INIT_VALUE(ImageCoverExpanderEnabled);
        CONFIG_INIT_VALUE(FullComboEffectsEnabled);
        CONFIG_INIT_VALUE(SearchFixesEnabled);
        CONFIG_INIT_VALUE(NoteJumpSpeed);
        CONFIG_INIT_VALUE(NoteJumpSpeedEnabled);
        CONFIG_INIT_VALUE(Clicked);
        CONFIG_INIT_VALUE(RotationEnabled);
        CONFIG_INIT_VALUE(RotationIncrement);
        CONFIG_INIT_VALUE(Test);
        CONFIG_INIT_VALUE(SwapColours);
        CONFIG_INIT_VALUE(ScreenTextChanger);
        CONFIG_INIT_VALUE(NJSTEST);
        CONFIG_INIT_VALUE(XPos);
        CONFIG_INIT_VALUE(YPos);
        CONFIG_INIT_VALUE(ZPos);
        CONFIG_INIT_VALUE(XRot);
        CONFIG_INIT_VALUE(YRot);
        CONFIG_INIT_VALUE(ZRot);
        CONFIG_INIT_VALUE(Scale);
        CONFIG_INIT_VALUE(SoloText);
		CONFIG_INIT_VALUE(OnlineText);
		CONFIG_INIT_VALUE(CampaignText);
		CONFIG_INIT_VALUE(PartyText);
        CONFIG_INIT_VALUE(Rainbow);
        CONFIG_INIT_VALUE(AlwaysRainbow);
        CONFIG_INIT_VALUE(Fadeout);
        CONFIG_INIT_VALUE(FullFade);
        CONFIG_INIT_VALUE(Alpha);
        CONFIG_INIT_VALUE(Diehp);
        CONFIG_INIT_VALUE(Lowhp);
        CONFIG_INIT_VALUE(Midhp);
        CONFIG_INIT_VALUE(Highhp);
        CONFIG_INIT_VALUE(Defhp);




    )
)