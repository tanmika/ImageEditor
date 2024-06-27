//
// Created by 檀木筪 on 2024/6/21.
//

// 消除macOS下OpenGL的警告
#define GL_SILENCE_DEPRECATION

#ifndef QT_PRJ_IMAGE_EDITOR_DEFINE_H
#define QT_PRJ_IMAGE_EDITOR_DEFINE_H

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <memory>
#include <unordered_set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DebugExec 1
#define DebugExecLoop 0
#define DebugAssert 1

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#if DebugExec
#if DebugExecLoop
#define DEBUG_EXEC(statement, obj) do{statement;}while(0);
#define DEBUG_EXEC_THIS(statement) do{statement;}while(0);
#else
#define DEBUG_EXEC(statement, obj)                               \
do {                                                             \
    static std::unordered_set<const void*> executedObjects;      \
    if (executedObjects.find(&(obj)) == executedObjects.end()) { \
        executedObjects.insert(&(obj));                          \
        do {                                                     \
            statement;                                           \
        } while (0);                                             \
    }                                                            \
} while (0);
#define DEBUG_EXEC_THIS(statement) DEBUG_EXEC(statement, *this)
#endif
#else
#define DEBUG_EXEC(statement, obj) /* nothing */
#define DEBUG_EXEC_THIS(statement) /* nothing */
#endif
#if DebugAssert
#define assertMsg(condition, message) \
    assert((condition) && message)
#else
#define assertMsg(condition, message) /* nothing */
#endif

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

template<typename T>
using Vector= std::vector<T>;

template<typename T>
using Deque = std::deque<T>;

using String = std::string;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

extern float G_WND_WIDTH;
extern float G_WND_HEIGHT;

static const char* TO_ROOT_PATH = "../../../../";
static const char* SHADER_PATH = "Shader/file/";
static const char* PICTURE_PATH = "Resource/Texture/";

static const int OPERATION_STACK_DEPTH = 10;

#endif //QT_PRJ_IMAGE_EDITOR_DEFINE_H
