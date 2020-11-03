QT -= gui

TEMPLATE = lib
DEFINES += SHADER_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

SOURCES += \
    Shader.cpp \
    glad.c

HEADERS += \
    Shader_global.h \
    Shader.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
