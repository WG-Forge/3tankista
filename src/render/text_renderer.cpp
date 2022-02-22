#include "render/text_renderer.hpp"

#include "game/game_configuration.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <iostream>

#include "render/materials/imaterial.h"

#include "utility/matrix_transform.h"

TextRenderer::TextRenderer()
    : shader(nullptr)
{
    this->shader = std::make_unique<Shader>("shaders/text.vert", "shaders/text.frag");

    Matrix4f projection =
        ortho(0.0f, static_cast<float>(GAME_WINDOW_WIDTH), static_cast<float>(GAME_WINDOW_HEIGHT), 0.0f);

    this->shader->Use();
    this->shader->SetInt("text", 0);
    this->shader->SetMat4(PROJECTION_UNIFORM_NAME, projection);
    this->shader->Unuse();

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::Load(const std::string& font, unsigned int fontSize)
{
    this->characters.clear();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERRPR::FREETYPE: Could not init FreeType Library" << std::endl << std::flush;
    }

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl << std::flush;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 255; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl << std::flush;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = { texture,
                                Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                static_cast<unsigned int>(face->glyph->advance.x) };
        characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::AddText(const std::string& text, const Vector2f& position, const float scale, const Color color)
{
    strings.push_back(Text{ text, position, scale, color });
}

void TextRenderer::RenderText()
{
    for (const auto& string : strings)
    {
        this->shader->Use();
        this->shader->SetVec4("textColor", string.color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);

        float x = string.position.x();
        float y = string.position.y();

        std::string::const_iterator c;
        for (c = string.text.begin(); c != string.text.end(); ++c)
        {
            Character ch = characters[*c];

            float xpos = x + ch.bearing.x() * string.scale;
            float ypos = y + ((this->characters['H'].bearing.y() - ch.bearing.y()) * string.scale) / GAME_WINDOW_HEIGHT;

            float w = ch.size.x() * string.scale;
            float h = ch.size.y() * string.scale;

            float vertices[6][4] = { { xpos, ypos + h, 0.0f, 0.0f }, { xpos, ypos, 0.0f, 1.0f },
                                     { xpos + w, ypos, 1.0f, 1.0f }, { xpos, ypos + h, 0.0f, 0.0f },
                                     { xpos + w, ypos, 1.0f, 1.0f }, { xpos + w, ypos + h, 1.0f, 0.0f } };

            glBindTexture(GL_TEXTURE_2D, ch.textureID);

            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.advance >> 6) * string.scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
