#pragma once
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "HMUI/Screen.hpp"

DECLARE_CLASS_CODEGEN(QuestUI, FloatingScreen, HMUI::Screen,

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, bgGo);
    DECLARE_INSTANCE_FIELD(UnityEngine::Vector2, screenSize);
    DECLARE_INSTANCE_FIELD(UnityEngine::Vector3, screenPosition);
    DECLARE_INSTANCE_FIELD(UnityEngine::Quaternion, screenRotation);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, handle);
    DECLARE_INSTANCE_FIELD(bool, showHandle);
    DECLARE_INSTANCE_FIELD(int, handleSide);

    DECLARE_INSTANCE_METHOD(void, set_showHandle, bool value);
    DECLARE_INSTANCE_METHOD(void, set_screenSize, UnityEngine::Vector2 size);
    DECLARE_INSTANCE_METHOD(void, set_bgGo, UnityEngine::GameObject* bg);
    DECLARE_INSTANCE_METHOD(void, createHandle);
    DECLARE_INSTANCE_METHOD(void, updateHandle);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, get_handle);
    DECLARE_INSTANCE_METHOD(int, get_side);
    DECLARE_INSTANCE_METHOD(void, set_side, int side);
)
