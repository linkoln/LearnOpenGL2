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
} else {
    BUILD_TYPE = release
}

INCLUDEPATH += $$GLFW/$$BUILD_TYPE/include
INCLUDEPATH += $$GLAD/include

LIBS += -L$$GLFW/$$BUILD_TYPE/lib -lglfw3
LIBS += -lopengl32 -lgdi32 -luser32
