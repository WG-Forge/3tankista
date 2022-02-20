#include "render/text_renderer.hpp"

#include "game/game_configuration.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <iostream>

TextRenderer::TextRenderer()
    : shader(nullptr)
{
    this->shader =
        std::make_unique<Shader>("shaders/text.vert", "shaders/text.frag");

    this->shader->SetInt("text", 0);

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

    // Сначала очищаем ранее загруженные символы
    this->characters.clear();

    // Затем инициализируем и загружаем библиотеку FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // все функции в случае ошибки возвращают
                               // значение, отличное от 0
    {
        std::cout << "ERRPR::FREETYPE: Could not init FreeType Library"
                  << std::endl
                  << std::flush;
    }

    // Загружаем шрифта в качестве face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl
                  << std::flush;
    }

    // Устанавливаем размер загружаемых глифов
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // Отключаем ограничение на выравнивание байтов
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Предварительно загружаем/компилируем символы шрифта и сохраняем их
    for (GLubyte c = 0; c < 255; ++c)
    {
        // Хагрузка символа глифа
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl
                      << std::flush;
            continue;
        }

        // Генерация текстуры
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

        // Установка параметров текстур
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Теперь сохраняем символы для их дальнейшего использования
        Character character = {
            texture,
            Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    //Когда закончили, освобождаем ресурсы FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::AddText(const std::string& text,
                           const Vector2f&    position,
                           const float        scale,
                           const Color        color)
{
    strings.push_back(Text{ text, position, scale, color });
}

void TextRenderer::RenderText()
{
    // Активируем соответсвтующее состание рендера

    for (const auto& string : strings)
    {
        this->shader->Use();
        this->shader->SetVec4("textColor", string.color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);

        float x = string.position.x();
        float y = string.position.y();

        //Цикл по всем символам
        std::string::const_iterator c;
        for (c = string.text.begin(); c != string.text.end(); ++c)
        {
            Character ch = characters[*c];

            float xpos =
                x + (ch.bearing.x() * string.scale) / GAME_WINDOW_WIDTH;
            float ypos =
                y + ((this->characters['H'].bearing.y() - ch.bearing.y()) *
                     string.scale) /
                        GAME_WINDOW_HEIGHT;

            float w = (ch.size.x() * string.scale) / GAME_WINDOW_WIDTH;
            float h = (ch.size.y() * string.scale) / GAME_WINDOW_HEIGHT;

            // Обновляем VBO для каждого символа
            float vertices[6][4] = { { xpos, ypos + h, 0.0f, 0.0f },
                                     { xpos, ypos, 0.0f, 1.0f },
                                     { xpos + w, ypos, 1.0f, 1.0f },
                                     { xpos, ypos + h, 0.0f, 0.0f },
                                     { xpos + w, ypos, 1.0f, 1.0f },
                                     { xpos + w, ypos + h, 1.0f, 0.0f } };

            // Рендерим на прямоугольник текстуру глифа
            glBindTexture(GL_TEXTURE_2D, ch.textureID);

            // Обновляем содержимое памяти VBO
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER,
                            0,
                            sizeof(vertices),
                            vertices); // обязательно используйте функцию
            // glBufferSubData(), а не glBufferData()
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Рендерим прямоугольник
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Теперь смещаем курсор к следующему глифу
            x += ((ch.advance >> 6) * string.scale) /
                 GAME_WINDOW_WIDTH; // битовый сдвиг на 6, чтобы получить
                                    // значение в пикселях (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
