cmake_minimum_required(VERSION 3.5)

project(qt_prj_image_editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/glew/2.2.0_1/lib/cmake/glew")
set(LOCAL_H /usr/local/include)
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLFW_H /usr/local/Cellar/glfw/3.4/include)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    src/*.c
    header/*.h
    OpenGLWidget/*.h
    OpenGLWidget/*.cpp
    OperationStack/*.h
    OperationStack/*.cpp
    Picture/*.h
    Picture/*.cpp
    Qt/*.h
    Qt/*.cpp
    Renderable/*.h
    Renderable/*.cpp
    Shader/*.h
    Shader/*.cpp
    Shape/*.h
    Shape/*.cpp
    Texture/*.h
    Texture/*.cpp
    Timer/*.h
    Timer/*.cpp
    Transform/*.h
    Transform/*.cpp
    UI/*.ui
    VertexBuilder/*.h
    VertexBuilder/*.inl
    VertexBuilder/*.cpp
)

set(CMAKE_AUTOUIC_SEARCH_PATHS "UI")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_prj_image_editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt_prj_image_editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt_prj_image_editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt_prj_image_editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(COMMON_INCLUDE_DIRS
        header
        OpenGLWidget
        OperationStack
        Picture
        Qt
        Renderable
        Shader
        Shape
        Texture
        Timer
        Transform
        VertexBuilder
        ${LOCAL_H}
        ${GLEW_H}
        ${GLFW_H}
        ${OPENGL_INCLUDE_DIRS}
        )

target_include_directories(qt_prj_image_editor PRIVATE ${COMMON_INCLUDE_DIRS})

target_link_libraries(qt_prj_image_editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qt_prj_image_editor)
endif()
set_target_properties(qt_prj_image_editor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS qt_prj_image_editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_prj_image_editor)
endif()

set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.4/lib/libglfw.3.dylib)
target_link_libraries(qt_prj_image_editor PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLEW_LINK}
        ${GLFW_LINK}
        )
if(APPLE)
    target_link_libraries(qt_prj_image_editor PUBLIC
            "-framework OpenGL"
            "-framework GLUT"
            )
endif()
