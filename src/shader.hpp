#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader{
public:
  // Program id
  unsigned int ID;

  // constructor reads and builds the shader
  Shader(std::string vertexPath, std::string fragmentPath);
  // use/activate the shader
  void use();

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;  
  void setInt(const std::string &name, int value) const;   
  void setFloat(const std::string &name, float value) const;
};

#endif
