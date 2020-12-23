#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

#define LOG_SIZE 512

SHADER::SHADER(const string& sVertexPath, const string& sFragPath)
{
    ifstream oVertexFile, oFragFile;
    oVertexFile.exceptions(ifstream::failbit | ifstream::badbit);
    oFragFile.exceptions(ifstream::failbit | ifstream::badbit);
    string sVertexShader, sFragShader;
    try
    {
        oVertexFile.open(sVertexPath);
        oFragFile.open(sFragPath);
        std::stringstream ssShaderStream, ssFragStream;
        ssShaderStream << oVertexFile.rdbuf();
        ssFragStream << oFragFile.rdbuf();
        oVertexFile.close();
        oFragFile.close();
        sVertexShader = ssShaderStream.str();
        sFragShader = ssFragStream.str();
    }
    catch (ifstream::failure& e)
    {
        cout << __func__ << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    _iID = CreateShader(sVertexShader, sFragShader);
}

unsigned int SHADER::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(type, 512, nullptr, infoLog);
        cout << "ERROR::CompileShader" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "\n" << infoLog << endl;
    }

    return id;
}

unsigned int SHADER::CreateShader(const std::string& sVertexShader, const std::string& sFragmentShader)
{
    unsigned int iProgram = glCreateProgram();
    unsigned int iVertexCode = CompileShader(GL_VERTEX_SHADER, sVertexShader);
    unsigned int iFragCode = CompileShader(GL_FRAGMENT_SHADER, sFragmentShader);

    glAttachShader(iProgram, iVertexCode);
    glAttachShader(iProgram, iFragCode);
    glLinkProgram(iProgram);

    int result;
    char infoLog[LOG_SIZE];
    glGetProgramiv(iProgram, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(iProgram, LOG_SIZE, nullptr, infoLog);
        cout << "ERROR::CreateShader\n" << infoLog << endl;
    }

    glValidateProgram(iProgram);

    glDeleteShader(iVertexCode);
    glDeleteShader(iFragCode);

    return iProgram;
}

void SHADER::Use()
{
    glUseProgram(_iID);
}

void SHADER::SetBool(const std::string& sName, bool bValue) const
{
    glUniform1i(glGetUniformLocation(_iID, sName.c_str()), bValue);
}

void SHADER::SetInt(const std::string& sName, int iValue) const
{
    glUniform1i(glGetUniformLocation(_iID, sName.c_str()), iValue);
}

void SHADER::SetFloat(const std::string& sName, float fValue) const
{
    glUniform1f(glGetUniformLocation(_iID, sName.c_str()), fValue);
}
