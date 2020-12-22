#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "Shader_global.h"

class SHADER_API SHADER
{
public:
    SHADER() = default;
    SHADER(const std::string& sVertexPath, const std::string& sFragPath);

    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& sVertexShader, const std::string& sFragmentShader);

    void Use();
    void SetBool(const std::string& sName, bool bValue) const;
    void SetInt(const std::string& sName, int iValue) const;
    void SetFloat(const std::string& sName, float fValue) const;

    unsigned int _iID;

protected:
};

#endif // SHADER_H
