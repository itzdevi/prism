#pragma once

class Texture2D {
private:
    unsigned int m_texture;
public:
    Texture2D(std::string path);
    void Bind();
};