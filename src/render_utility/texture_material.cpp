#include "texture_material.h"

#include "stb_image.h"

TextureMaterial::TextureMaterial(const std::string& textureFileName)
    : IMaterial(textureFileName)
    , shader(nullptr)
    , texture(-1)
    , textureFileName(textureFileName)
{
}

void TextureMaterial::Use() const
{
    glBindTexture(GL_TEXTURE_2D, texture);

    this->shader->Use();
}

void TextureMaterial::Unuse() const
{
    this->shader->Unuse();
}

bool TextureMaterial::Initialize()
{
    this->shader = std::make_unique<Shader>("shaders/texture.vert",
                                            "shaders/texture.frag");

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,
                  texture); // all upcoming GL_TEXTURE_2D operations now have
                            // effect on this texture object
                            // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_REPEAT); // set texture wrapping to GL_REPEAT
                                // (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    unsigned char* data =
        stbi_load(textureFileName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    this->shader->setInt("ourTexture", 0);

    return true;
}

void TextureMaterial::Release()
{
    this->shader.release();
    this->shader = nullptr;
}
