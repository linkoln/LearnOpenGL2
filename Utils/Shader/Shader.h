#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "Shader_global.h"

class SHADER_API SHADER
{
public:
    SHADER();

    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif // SHADER_H
