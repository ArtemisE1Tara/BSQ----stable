#include "main.hpp"
#include "ModConfig.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"
#include "hooks.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

DEFINE_CONFIG(ModConfig);
float scale = 0.2f;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Think of these as C#, using MainMenuViewController, using UnityEngine.UI.Button, using HMUI.CurvedTextMeshPro ect.
// Classes without a namespace are assigned to the GlobalNamespace
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

// Create a hook struct, named MainMenuUIHook.
// Target "void MainMenuViewController::DidActivate" and takes the following arguments:
// bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling

// General format: MAKE_HOOK_MATCH(HookName, method, method return type, method class pointer, arguments...) { 
//  HookName(arguments...);
//  // your code here 
//}

/*MAKE_AUTO_HOOK_MATCH(MainMenuUIHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    
    // Run the original method before our code.
    // Note, you can run the original method after our code if you want to change arguments.
    MainMenuUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling); 
    
    // Get the _soloButton text using the dyn_ method and simple unity jazz. dyn_ safely get fields and shouldn't change
    //much during updates.

    
    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();


    if(getModConfig().ModEnabled.GetValue()){ 

        soloMenuText->SetText("Skill Issue"); 
    }

    else {
        soloMenuText->SetText("SOLO");
    }
    // add your code here
    
    // Set the text to "Skill Issue"
}
*/

#include "main.hpp"

#include "custom-types/shared/register.hpp"

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
using namespace GlobalNamespace;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
using namespace UnityEngine;

#include "UnityEngine/UI/Button.hpp"
using namespace UnityEngine::UI;

#include "HMUI/ImageView.hpp"
using namespace HMUI;

MAKE_AUTO_HOOK_MATCH(m_DidActivate,
                &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
                void,
                GlobalNamespace::StandardLevelDetailViewController* self,
                bool firstActivation,
                bool addedToHeirarchy,
                bool screenSystemEnabling) {

    m_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    if(getModConfig().ImageCoverExpanderEnabled.GetValue()) {

    auto* imageCoverTransform = self->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

    imageCoverTransform->set_sizeDelta(Vector2(70.5, 58.0));
    imageCoverTransform->set_localPosition(Vector3(-34.4, -56, 0));
    imageCoverTransform->SetAsFirstSibling();

    auto* imageView = imageCoverTransform->GetComponent<ImageView*>();

    imageView->set_color(Color(0.5, 0.5, 0.5, 1));
    imageView->set_preserveAspect(false);
    imageView->dyn__skew() = 0.0f;
    }
    else{
        m_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);
    }
}

#include "main.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

using namespace GlobalNamespace;
using namespace TMPro;

static void setFullComboUI(UnityEngine::GameObject *clearedBannerGo)
{
    try
    {
        clearedBannerGo->GetComponentsInChildren<TextMeshProUGUI *>()[0]->set_text(il2cpp_utils::newcsstr("FULL COMBO"));
    }
    catch (const std::exception &e)
    {
        getLogger().log(Logging::ERROR, "Failed to set text to cleared info.");
        getLogger().log(Logging::ERROR, std::string(e.what()));
    }

    try
    {
        clearedBannerGo->GetComponentsInChildren<HMUI::ImageView *>()[0]->set_color(UnityEngine::Color::get_yellow());
    }
    catch (const std::exception &e)
    {
        getLogger().log(Logging::ERROR, "Failed to set color to background of cleared info.");
        getLogger().log(Logging::ERROR, std::string(e.what()));
    }
}

static void setNotFullComboUI(UnityEngine::GameObject *clearedBannerGo)
{
    // no need to reset text to LEVEL CLEARED

    // reset background to red color
    try
    {
        const auto originColor = UnityEngine::Color(1, 0.374, 0, 1);
        clearedBannerGo->GetComponentsInChildren<HMUI::ImageView *>()[0]->set_color(originColor);
    }
    catch (const std::exception &e)
    {
        getLogger().log(Logging::ERROR, "Failed to reset color to background of cleared info.");
        getLogger().log(Logging::ERROR, std::string(e.what()));
    }
}

MAKE_AUTO_HOOK_MATCH(Results, &ResultsViewController::SetDataToUI, void, ResultsViewController *self)
{
    Results(self);

    if(getModConfig().FullComboEffectsEnabled.GetValue()){

    if (self->dyn__levelCompletionResults()->dyn_levelEndStateType() == LevelCompletionResults::LevelEndStateType::Cleared)
    {
        if (self->dyn__levelCompletionResults()->dyn_fullCombo())
        {
            self->dyn__newHighScore() = true; // for trigger sounds and fireworks
            setFullComboUI(self->dyn__clearedBannerGo());
        } else {
            setNotFullComboUI(self->dyn__clearedBannerGo());
        }
    }
}
    else {
        Results(self);
    }
}

//searchfixes
#include "main.hpp"

#include "GlobalNamespace/BeatmapLevelFilterModel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
using namespace GlobalNamespace;

#include "System/StringComparison.hpp"

void toLower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool findSubstring(std::string str, std::string substr) {
    toLower(str);
    toLower(substr);
    return str.find(substr) != std::string::npos;
}

MAKE_AUTO_HOOK_MATCH(BeatmapLevelFilterModel_LevelContainsText, &BeatmapLevelFilterModel::LevelContainsText, bool, IPreviewBeatmapLevel* beatmapLevel, ArrayW<StringW> searchTexts) {
    int words = 0;
    int matches = 0;

    auto songName = beatmapLevel->get_songName();
    auto songSubName = beatmapLevel->get_songSubName();
    auto songAuthorName = beatmapLevel->get_songAuthorName();
    auto levelAuthorName = beatmapLevel->get_levelAuthorName();

    auto arrayLen = searchTexts.Length();

    for (int i = 0; i < arrayLen; i++)
    {

        StringW searchTerm = searchTexts[i];

        // getLogger().debug("Searching for '%s' in '%s'", static_cast<std::string>(searchTerm).c_str(), static_cast<std::string>(songName).c_str()); // Debugging Stuff

        if (searchTerm->get_Length() == 0)
            continue;

        words++;

        bool found = findSubstring(songName, searchTerm) ||
            findSubstring(songSubName, searchTerm) ||
            findSubstring(songAuthorName, searchTerm) ||
            findSubstring(levelAuthorName, searchTerm);

        /* Debugging stuff
        getLogger().debug("songName: '%s'; songSubName: '%s'; songAuthorName: '%s'; levelAuthorName: '%s'; searchTermString: %s", static_cast<std::string>(songName).c_str(), static_cast<std::string>(songSubName).c_str(), static_cast<std::string>(songAuthorName).c_str(), static_cast<std::string>(levelAuthorName).c_str(), searchTermString.c_str());
        getLogger().debug("Found: %s", found ? "true" : "false");
        getLogger().debug("");
        */


        if (found) matches++;

    }

    return matches == words;
}

//custommenutext
#include "main.hpp"
#include "UI/Settings/CmSettingsViewController.hpp"
#include "TextHandler.hpp"

#include "custom-types/shared/register.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "GlobalNamespace/MainMenuViewController.hpp"
using namespace GlobalNamespace;

#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"

MAKE_AUTO_HOOK_MATCH(
    MainMenuViewController_DidActivate,
    &MainMenuViewController::DidActivate,
    void,
    MainMenuViewController* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    cm::updateMenuText(self);
}

//redbar
#include "main.hpp"
#include "ModConfig.hpp"
#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/OverrideEnvironmentSettings.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/PracticeSettings.hpp"
#include "GlobalNamespace/StandardLevelScenesTransitionSetupDataSO.hpp"
#include "GlobalNamespace/MultiplayerLevelScenesTransitionSetupDataSO.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"

#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"

#include "RedBarViewController.hpp"

#include "questui/shared/QuestUI.hpp"
#include "custom-types/shared/register.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace QuestUI;

    UnityEngine::Material* energyBarMaterialStore = nullptr;
    UnityEngine::UI::Image* energyBarStore = nullptr;
    float energyy = 0.0;
    int pos = 0;

void SetColor(GameEnergyUIPanel* self, float energy) {
    UnityEngine::Color color;

    color = getModConfig().Defhp.GetValue();
    color.a = getModConfig().Alpha.GetValue();
    
    UnityEngine::UI::Image* energyBar = self->dyn__energyBar();
    

    
    UnityEngine::Material* energyBarMaterial = energyBar->get_material();

    if (energyBarMaterialStore != energyBarMaterial || energyBarStore != energyBar) {
        energyBarMaterialStore = energyBarMaterial;
        energyBarStore = energyBar;
    }
    if (energy != energyy) {
        energyy = energy;
    }

    if(getModConfig().FullFade.GetValue()) {
        double fraction = energy;
        color.r = getModConfig().Diehp.GetValue().r + (getModConfig().Highhp.GetValue().r - getModConfig().Diehp.GetValue().r) * fraction;
        color.g = getModConfig().Diehp.GetValue().g + (getModConfig().Highhp.GetValue().g - getModConfig().Diehp.GetValue().g) * fraction;
        color.b = getModConfig().Diehp.GetValue().b + (getModConfig().Highhp.GetValue().b - getModConfig().Diehp.GetValue().b) * fraction;
    } else {
        if (energy < 0.15) {
            if (!getModConfig().AlwaysRainbow.GetValue()) {
                color.r = getModConfig().Diehp.GetValue().r;
                color.g = getModConfig().Diehp.GetValue().g;
                color.b = getModConfig().Diehp.GetValue().b;
            }
        } else if (energy < 0.5) {
            if (!getModConfig().AlwaysRainbow.GetValue()) {
                double fraction = (energy - 0.15f)*2.8571428f;
                color.r = getModConfig().Diehp.GetValue().r + (getModConfig().Lowhp.GetValue().r - getModConfig().Diehp.GetValue().r) * fraction;
                color.g = getModConfig().Diehp.GetValue().g + (getModConfig().Lowhp.GetValue().g - getModConfig().Diehp.GetValue().g) * fraction;
                color.b = getModConfig().Diehp.GetValue().b + (getModConfig().Lowhp.GetValue().b - getModConfig().Diehp.GetValue().b) * fraction;
            }
        } else if (energy > 0.5 && energy < 0.7) {
            if (!getModConfig().AlwaysRainbow.GetValue()) {
                double fraction = (energy - 0.5f)*5.0f;
                color.r = getModConfig().Lowhp.GetValue().r + (getModConfig().Defhp.GetValue().r - getModConfig().Lowhp.GetValue().r) * fraction;
                color.g = getModConfig().Lowhp.GetValue().g + (getModConfig().Defhp.GetValue().g - getModConfig().Lowhp.GetValue().g) * fraction;
                color.b = getModConfig().Lowhp.GetValue().b + (getModConfig().Defhp.GetValue().b - getModConfig().Lowhp.GetValue().b) * fraction;
            }
        } else if (energy > 0.95) {
            if (!getModConfig().Rainbow.GetValue()) {
                double fraction = (energy - 0.95f)*20.0f;
                color.r = getModConfig().Midhp.GetValue().r + (getModConfig().Highhp.GetValue().r - getModConfig().Midhp.GetValue().r) * fraction;
                color.g = getModConfig().Midhp.GetValue().g + (getModConfig().Highhp.GetValue().g - getModConfig().Midhp.GetValue().g) * fraction;
                color.b = getModConfig().Midhp.GetValue().b + (getModConfig().Highhp.GetValue().b - getModConfig().Midhp.GetValue().b) * fraction;
            }
        } else if (energy > 0.7) {
            if (!getModConfig().AlwaysRainbow.GetValue()) {
                double fraction = (energy - 0.7f)*3.3333333f;
                color.r = getModConfig().Defhp.GetValue().r + (getModConfig().Midhp.GetValue().r - getModConfig().Defhp.GetValue().r) * fraction;
                color.g = getModConfig().Defhp.GetValue().g + (getModConfig().Midhp.GetValue().g - getModConfig().Defhp.GetValue().g) * fraction;
                color.b = getModConfig().Defhp.GetValue().b + (getModConfig().Midhp.GetValue().b - getModConfig().Defhp.GetValue().b) * fraction;
            }
        }
    }
    
    if (energy > 0.85 && getModConfig().Fadeout.GetValue()) {
        color.a = (6.667+(-6.667*energy))*getModConfig().Alpha.GetValue();
    } else {
        color.a = getModConfig().Alpha.GetValue();
    }
    //getLogger().info("r: " + std::to_string(color.r) + " g: " + std::to_string(color.g) + " b: " + std::to_string(color.g) + " a: " + std::to_string(color.a));
    energyBar->set_color(color);
}


MAKE_AUTO_HOOK_MATCH(GameEnergyUIPanel_Start, &GameEnergyUIPanel::Start, void, GameEnergyUIPanel* self) {
    //getLogger().info("LateUpdate RedBar");
    GameEnergyUIPanel_Start(self);
    SetColor(self, 0.5f);
}

MAKE_AUTO_HOOK_MATCH(GameEnergyUIPanel_HandleGameEnergyDidChange, &GameEnergyUIPanel::RefreshEnergyUI, void, GameEnergyUIPanel* self, float energy) {
    GameEnergyUIPanel_HandleGameEnergyDidChange(self, energy);
    //getLogger().info(std::to_string(energy));
    SetColor(self, energy);
}



float * Wheel(int WheelPos) {
  static int c[3];
  static float epic[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  epic[0] = (float) c[0] / 255.0;
  epic[1] = (float) c[1] / 255.0;
  epic[2] = (float) c[2] / 255.0;
 
  return epic;
}


MAKE_AUTO_HOOK_MATCH(GameEnergyCounter_LateUpdate, &GameEnergyCounter::LateUpdate, void, GameEnergyCounter* self) {
    //getLogger().info("LateUpdate RedBar");
    GameEnergyCounter_LateUpdate(self);
    if ((energyBarMaterialStore != nullptr && energyBarStore != nullptr && energyy == 1.0 && getModConfig().Rainbow.GetValue()) || (energyBarMaterialStore != nullptr && energyBarStore != nullptr && getModConfig().AlwaysRainbow.GetValue())) {
        float* Heck = Wheel(pos);
        UnityEngine::Color color;
        color.a = 1.0;
        color.r = Heck[0];
        color.g = Heck[1];
        color.b = Heck[2];
        energyBarStore->set_color(color);
        pos++;
        if (pos > 255) {
            pos = 0;
        }
    }
}

MAKE_AUTO_HOOK_MATCH(SceneManager_ActiveSceneChanged, &UnityEngine::SceneManagement::SceneManager::Internal_ActiveSceneChanged, void, UnityEngine::SceneManagement::Scene previousActiveScene, UnityEngine::SceneManagement::Scene nextActiveScene) {
    SceneManager_ActiveSceneChanged(previousActiveScene, nextActiveScene);
    energyBarStore = nullptr;
    energyBarMaterialStore = nullptr;
}


#include "main.hpp"
#include "hooks.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/Resources.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
//add level editor
MAKE_AUTO_HOOK_MATCH(LevelEditor, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    UnityEngine::UI::Button *beatmapEditorButton = self->dyn__beatmapEditorButton();
    UnityEngine::GameObject *gameObject = beatmapEditorButton->get_gameObject();

    if(getModConfig().LevelEditor.GetValue()){

        gameObject->SetActive(true);

    }
    else{

        LevelEditor(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    }

}

#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "HMUI/ViewController.hpp"

MAKE_AUTO_HOOK_MATCH(energy, &GameEnergyCounter::ProcessEnergyChange, void, GameEnergyCounter* self, float energyChange){
    if(getModConfig().ENABLED.GetValue()){
        energyChange = 100.0f;
    }
    else{
        energy(self, energyChange);
    }

}


extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load();
	
    getLogger().info("Completed setup!");
}

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.

    if(firstActivation) {
        
        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
        QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "BSQ+", [&](){
        });
        //QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Unofficial");

        //AddConfigValueToggle(container->get_transform(), getModConfig().ModEnabled);
        AddConfigValueToggle(container->get_transform(), getModConfig().LevelEditor);
        AddConfigValueToggle(container->get_transform(), getModConfig().ImageCoverExpanderEnabled);
        AddConfigValueToggle(container->get_transform(), getModConfig().FullComboEffectsEnabled);
        //QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Godmode by KodenameKRAK");
        AddConfigValueToggle(container->get_transform(), getModConfig().ENABLED);
        AddConfigValueToggle(container->get_transform(), getModConfig().RotationEnabled);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().RotationIncrement, 0, 5.0f, -180.0f, 180.0f);

        //redbar
        QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "RedBar", [&](){
        });
        //self->get_gameObject()->AddComponent<Touchable*>();

        QuestUI::BeatSaberUI::AddHoverHint(AddConfigValueToggle(container->get_transform(), getModConfig().Rainbow)->get_gameObject(), "overrides Fadeout");

        // AlwaysRainbow
        QuestUI::BeatSaberUI::AddHoverHint(AddConfigValueToggle(container->get_transform(), getModConfig().AlwaysRainbow)->get_gameObject(), "overrides Fadeout, Fade red to green and Rainbow");

        // Fadeout
        AddConfigValueToggle(container->get_transform(), getModConfig().Fadeout);

        // Alpha
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().Alpha, 1, 0.1f, 0.0f, 1.0f);

        //QuestUI::BeatSaberUI::CreateText(container->get_transform(), "\n\n                                          Values under 0.0 will be 0.0");
        //QuestUI::BeatSaberUI::CreateText(container->get_transform(), "\n                                          Values over 1.0 will be 1.0");
        
        // FullFade
        QuestUI::BeatSaberUI::AddHoverHint(AddConfigValueToggle(container->get_transform(), getModConfig().FullFade)->get_gameObject(), "Fades between the 15% and 95% Color");


        AddConfigValueColorPicker(container->get_transform(), getModConfig().Diehp);

        AddConfigValueColorPicker(container->get_transform(), getModConfig().Lowhp);

        AddConfigValueColorPicker(container->get_transform(), getModConfig().Defhp);

        AddConfigValueColorPicker(container->get_transform(), getModConfig().Midhp);

        AddConfigValueColorPicker(container->get_transform(), getModConfig().Highhp);

    }
}

extern "C" void load() {
    il2cpp_functions::Init();
    QuestUI::Init();
    //LoggerContextObject logger = getLogger().WithContext("load");
    //QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterMainMenuModSettingsViewController<cm::CmSettingsViewController*>({"Custom Menu Text+"});
    
    il2cpp_functions::Init();
    getModConfig().Init(modInfo);

    //yoinked from krak
    QuestUI::Init();

    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    //end
    
    //INSTALL_HOOK(getLogger(), MainMenuUIHook);

    /*INSTALL_HOOK(getLogger(), Results);

    INSTALL_HOOK(getLogger(), m_DidActivate);

    INSTALL_HOOK(getLogger(), MainMenuViewController_DidActivate);

    INSTALL_HOOK(getLogger(), BeatmapLevelFilterModel_LevelContainsText);

    //redbar
    INSTALL_HOOK(logger, GameEnergyUIPanel_HandleGameEnergyDidChange);
    INSTALL_HOOK(logger, GameEnergyCounter_LateUpdate);
    INSTALL_HOOK(logger, GameEnergyUIPanel_Start);
    INSTALL_HOOK(logger, SceneManager_ActiveSceneChanged);
    */
    getLogger().info("Installed all hooks!");
}