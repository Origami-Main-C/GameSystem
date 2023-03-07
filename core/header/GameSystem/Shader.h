#pragma once

#include <GameSystem/File.h>
#include <GameSystem/Log.h>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  // Print the Error information
  bool checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        LOG_Error("SHADER", type + "_SHADER_COMPILATION_ERROR\n", infoLog);
        return false;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        LOG_Error("SHADER", "PROGRAM_LINKING_ERROR\n", infoLog);
      }
    }
  }

public:
  unsigned int ID;

  // Source path
  Shader(std::string vertexPath, std::string fragmentPath,
         std::string geometryPath = "") {
    std::string vCode = read_file(vertexPath);
    std::string fCode = read_file(fragmentPath);
    const char *vShaderCode = vCode.c_str();
    const char *fShaderCode = fCode.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    bool vertexShaderCompileSuccess = checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    bool fragmentShaderCompileSuccess =
        checkCompileErrors(fragment, "FRAGMENT");
    unsigned int geometry;
    bool geometryShaderCompileSuccess;
    if (!geometryPath.empty()) {
      std::string gCode = read_file(geometryPath);
      const char *gShaderCode = gCode.c_str();
      geometry = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(geometry, 1, &gShaderCode, NULL);
      glCompileShader(geometry);
      geometryShaderCompileSuccess = checkCompileErrors(geometry, "GEOMETRY");
    }
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (!geometryPath.empty()) {
      glAttachShader(ID, geometry);
    }
    glLinkProgram(ID);
    bool linkSuccess = checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!geometryPath.empty()) {
      glDeleteShader(geometry);
    }
    if (geometryPath.empty()) {
      if (vertexShaderCompileSuccess && fragmentShaderCompileSuccess &&
          linkSuccess) {
        LOG_Log("SHADER", "CREAT_SHADER",
                "Shader" + std::to_string(ID) + ":    " + vertexPath + "   " +
                    fragmentPath);
      }

    } else {
      if (vertexShaderCompileSuccess && fragmentShaderCompileSuccess &&
          linkSuccess && geometryShaderCompileSuccess) {
        LOG_Log("SHADER", "CREAT_SHADER",
                "Shader" + std::to_string(ID) + ":    " + vertexPath + "   " +
                    fragmentPath + "    " + geometryPath);
      }
    }
  }

  ~Shader() { glDeleteProgram(ID); }

  void use() { glUseProgram(ID); }

  // Set uniforms
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }

  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }

  void setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
  }

  void setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }

  void setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
  }

  void setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }

  void setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
  }

  void setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

  void setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

  void setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }
};