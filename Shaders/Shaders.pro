TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        glad.c \
        main.cpp

GLFW = "E:\librarys\glfw"
GLAD = "E:\librarys\glad"

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    LIBS += -L$$PWD/../Utils/Shader/lib/$$BUILD_TYPE -lShaderd
} else {
    BUILD_TYPE = release
    LIBS += -L$$PWD/../Utils/Shader/lib/$$BUILD_TYPE -lShader
}

message($$QMAKE_HOST.arch $$QMAKE_HOST.name)

INCLUDEPATH += $$GLFW/$$BUILD_TYPE/include
INCLUDEPATH += $$GLAD/include
INCLUDEPATH += $$PWD/../Utils/Shader/include

LIBS += -L$$GLFW/$$BUILD_TYPE/lib -lglfw3
LIBS += -lopengl32 -lgdi32 -luser32

RESOURCES += \
    shaders.qrc

