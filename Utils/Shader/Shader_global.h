#ifndef SHADER_GLOBAL_H
#define SHADER_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(SHADER_LIBRARY)
#  define SHADER_API __declspec(dllexport)
#else
#  define SHADER_API __declspec(dllimport)
#endif

#endif // SHADER_GLOBAL_H
