#ifndef SHADER_GLOBAL_H
#define SHADER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHADER_LIBRARY)
#  define SHADER_EXPORT Q_DECL_EXPORT
#else
#  define SHADER_EXPORT Q_DECL_IMPORT
#endif

#endif // SHADER_GLOBAL_H
