#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <map>

#include "glad.h"

#include "utility/matrix.hpp"

#include "render/utility/buffers.h"
#include "render/utility/shader.hpp"

// Информация о состоянии символа, загруженного с помощью библиотеки FreeType
struct Character
{
    unsigned int textureID; // ID текстуры глифа
    Vector2i     size;      // размер глифа
    Vector2i     bearing; // смещение от линии шрифта до верхнего левого угла глифа
    unsigned int
        advance; // горизонтальное смещение для перехода к следующему глифу
};

struct Text
{
    using Color = Vector4f;

    Text(const std::string& text,
         const Vector2f&    position,
         const float        scale,
         const Color        color)
        : text{ text }
        , position{ position }
        , scale{ scale }
        , color{ color }
    {
    }

    std::string text{};
    Vector2f    position{ 0.0f, 0.0f };
    float       scale{ 1.0f };
    Color       color{ 1.0f, 1.0f, 1.0f, 1.0f };
};

// Класс TextRenderer предназначен для рендеринга текста, отображаемого шрифтом,
// загруженным с помощью библиотеки FreeType. Загруженный шрифт обрабатывается и
// сохраняется для последующего рендеринга в виде списка символов
class TextRenderer
{
    using Color = Vector4f;

    static constexpr size_t TEXT_VERTEX_BUFFER_SIZE{ 8388608 /* 8 MB */ };

public:
    // Конструктор
    TextRenderer();

    // Список предварительно скопилированных символов из заданного шрифта
    void Load(const std::string& font, unsigned int fontSize);

    void AddText(const std::string& text,
                 const Vector2f&    position,
                 const float        scale,
                 const Color        color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    // Рендеринг строки текста с использованием предварительно скомпилированного
    // списка символов
    void RenderText();

private:
    // Состояние рендеринга
    unsigned int VAO, VBO;

    // список предварительно скомпилированных символов
    std::map<char, Character> characters;

    // Шейдер, используемый для рендеринга текста
    std::unique_ptr<Shader> shader;

    std::size_t stringCount{ 0 };

    std::vector<Text> strings;

    std::vector<Vector2f> vertexTexCoordData{};
    std::vector<Vector3f> vertexPosData{};
    std::vector<Vector4f> vertexColorData{};
};

#endif // TEXTRENDERER_HPP
