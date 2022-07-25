#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/ObstacleData.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "ModConfig.hpp"
using namespace GlobalNamespace;

MAKE_AUTO_HOOK_MATCH(ObstacleController_Init, &ObstacleController::Init, void, ObstacleController* self, ObstacleData* obstacleData,  float worldRotation, UnityEngine::Vector3 startPos, UnityEngine::Vector3 midPos, UnityEngine::Vector3 endPos, float move1Duration, float move2Duration, float singleLineWidth, float height){
    if(getModConfig().RotationEnabled.GetValue() && !getModConfig().SwapColours.GetValue()){
        worldRotation = getModConfig().RotationIncrement.GetValue();
    }
    else if (getModConfig().SwapColours.GetValue()){
        worldRotation = 180.0f;
    }
    ObstacleController_Init(self, obstacleData, worldRotation, startPos, midPos, endPos, move1Duration, move2Duration, singleLineWidth, height);
}

MAKE_AUTO_HOOK_MATCH(NoteController_Init, &NoteController::Init, void, NoteController* self, NoteData* noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity, float endRotation, float uniformScale, bool rotateTowardsPlayer, bool useRandomRotation){
    if(getModConfig().RotationEnabled.GetValue() && !getModConfig().SwapColours.GetValue()){
        worldRotation = getModConfig().RotationIncrement.GetValue();
    }
    else if (getModConfig().SwapColours.GetValue()){
        worldRotation = 180.0f;
    }
    NoteController_Init(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, endRotation, uniformScale, rotateTowardsPlayer, useRandomRotation);
}
MAKE_AUTO_HOOK_MATCH(BombNoteController_Init, &BombNoteController::Init, void, BombNoteController* self, NoteData* noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity){
    if(getModConfig().RotationEnabled.GetValue() && !getModConfig().SwapColours.GetValue()){
        worldRotation = getModConfig().RotationIncrement.GetValue();
    }
    else if (getModConfig().SwapColours.GetValue()){
        worldRotation = 180.0f;
    }
    BombNoteController_Init(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity);
}