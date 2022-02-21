#pragma once

#include "glad.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "utility/matrix.hpp"

class Shader
{

public:
    void       SetID(const std::size_t id) { this->id = id; }
    auto       GetID() { return this->id; }
    const auto GetID() const { return this->id; }

public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const std::string& vertexPath,
           const std::string& fragmentPath,
           const std::string& geometryPath = "")
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string   vertexCode;
        std::string   fragmentCode;
        std::string   geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
            if (!geometryPath.empty())
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"
                      << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        std::size_t vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        std::size_t geometry;
        if (!geometryPath.empty())
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry                = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        this->SetID(glCreateProgram());
        glAttachShader(this->GetID(), vertex);
        glAttachShader(this->GetID(), fragment);
        if (!geometryPath.empty())
            glAttachShader(this->GetID(), geometry);
        glLinkProgram(this->GetID());
        CheckCompileErrors(this->GetID(), "PROGRAM");
        // delete the shaders as they're linked into our program now and no
        // longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (!geometryPath.empty())
            glDeleteShader(geometry);
    }

    Shader(const std::string& computePath)
    {
        std::string   computeCode;
        std::ifstream cShaderFile;
        // ensure ifstream objects can throw exceptions:
        cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            cShaderFile.open(computePath);
            std::stringstream cShaderStream;
            cShaderStream << cShaderFile.rdbuf();
            cShaderFile.close();
            computeCode = cShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"
                      << std::endl;
        }
        std::size_t compute;

        const char* cShaderCode = computeCode.c_str();
        compute                 = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &cShaderCode, NULL);
        glCompileShader(compute);
        CheckCompileErrors(compute, "COMPUTE");

        // shader Program
        this->SetID(glCreateProgram());
        glAttachShader(this->GetID(), compute);
        glLinkProgram(this->GetID());
        CheckCompileErrors(this->GetID(), "PROGRAM");
        glDeleteShader(compute);
    }

public:
    // activate the shader
    // ------------------------------------------------------------------------
    void Use() const { glUseProgram(this->GetID()); }

    // disactivate the shader
    // ------------------------------------------------------------------------
    void Unuse() const { glUseProgram(0); }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(this->GetID(), name.c_str()),
                    (int)value);
    }
    // ------------------------------------------------------------------------
    void SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(this->GetID(), name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(this->GetID(), name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetVec2(const std::string& name, const Vector2f& value) const
    {
        glUniform2fv(
            glGetUniformLocation(this->GetID(), name.c_str()), 1, value.data());
    }
    void SetVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(this->GetID(), name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void SetVec3(const std::string& name, const Vector3f& value) const
    {
        glUniform3fv(
            glGetUniformLocation(this->GetID(), name.c_str()), 1, value.data());
    }
    void SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(this->GetID(), name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void SetVec4(const std::string& name, const Vector4f& value) const
    {
        const auto tmp = glGetUniformLocation(this->GetID(), name.c_str());
        glUniform4fv(
            glGetUniformLocation(this->GetID(), name.c_str()), 1, value.data());
    }
    void SetVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(
            glGetUniformLocation(this->GetID(), name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void SetMat2(const std::string& name, const Matrix2f& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(this->GetID(), name.c_str()),
                           1,
                           GL_FALSE,
                           mat.data());
    }
    // ------------------------------------------------------------------------
    void SetMat3(const std::string& name, const Matrix3f& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(this->GetID(), name.c_str()),
                           1,
                           GL_FALSE,
                           mat.data());
    }
    // ------------------------------------------------------------------------
    void SetMat4(const std::string& name, const Matrix4f& mat) const
    {
        std::vector<float> m{ mat.getCol(0)[0], mat.getCol(0)[1],
                              mat.getCol(0)[2], mat.getCol(0)[3],

                              mat.getCol(1)[0], mat.getCol(1)[1],
                              mat.getCol(1)[2], mat.getCol(1)[3],

                              mat.getCol(2)[0], mat.getCol(2)[1],
                              mat.getCol(2)[2], mat.getCol(2)[3],

                              mat.getCol(3)[0], mat.getCol(3)[1],
                              mat.getCol(3)[2], mat.getCol(3)[3] };
        glUniformMatrix4fv(glGetUniformLocation(this->GetID(), name.c_str()),
                           1,
                           GL_FALSE,
                           const_cast<float*>(m.data()));
    }

    void SetSampler2D(const std::string& name,
                      std::size_t        texture,
                      int                id) const
    {
        glActiveTexture(GL_TEXTURE0 + id);
        glBindTexture(GL_TEXTURE_2D, texture);
        this->SetInt(name, id);
    }
    void SetSampler3D(const std::string& name,
                      std::size_t        texture,
                      int                id) const
    {
        glActiveTexture(GL_TEXTURE0 + id);
        glBindTexture(GL_TEXTURE_3D, texture);
        this->SetInt(name, id);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint  success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout
                    << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
                    << "\n"
                    << infoLog
                    << "\n -- "
                       "---------------------------------------------------"
                       " -- "
                    << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout
                    << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << infoLog
                    << "\n -- "
                       "---------------------------------------------------"
                       " -- "
                    << std::endl;
            }
        }
    }

private:
    std::size_t id;
};
