#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int m_program;

    std::string OpenFile(std::string path);
public:
    Shader(std::string vertPath, std::string fragPath);
    void Use();
    void AddFloat(std::string name, float data);
    void AddVec3(std::string name, glm::vec3 data);
    void AddMat4(std::string name, glm::mat4 data);
};
