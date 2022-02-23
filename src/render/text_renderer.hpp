#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <map>

#include "glad.h"

#include "render/global.h"

#include "render/utility/buffers.h"
#include "render/utility/shader.hpp"

struct Character
{
    unsigned int textureID;
    Vector2i     size;
    Vector2i     bearing;
    unsigned int advance;
};

struct Text
{

    Text(const uint64_t     vehicleId,
         const std::string& text,
         const Vector2f&    position,
         const float        scale,
         const Color        color)
        : vehicleId{ vehicleId }
        , text{ text }
        , position{ position }
        , scale{ scale }
        , color{ color }
    {
    }

    uint64_t    vehicleId{ 0 };
    std::string text{};
    Vector2f    position{ 0.0f, 0.0f };
    float       scale{ 1.0f };
    Color       color{ WHITE_COLOR };
};

class TextRenderer
{

    static constexpr size_t TEXT_VERTEX_BUFFER_SIZE{ 8388608 /* 8 MB */ };

public:
    TextRenderer();

    void Load(const std::string& font, unsigned int fontSize);

    void ChangeText(const uint64_t vehicleId, const std::string& text)
    {
        const auto it = std::find_if(this->strings.begin(),
                                     this->strings.end(),
                                     [&](const Text& string) { return string.vehicleId == vehicleId; });
        if (it != this->strings.end())
        {
            it->text = text;
        }
    }

    void AddText(const uint64_t     vehicleId,
                 const std::string& text,
                 const Vector2f&    position,
                 const float        scale,
                 const Color        color = Color(WHITE_COLOR));

    void RenderText();

private:
    unsigned int VAO, VBO;

    std::map<char, Character> characters;

    std::unique_ptr<Shader> shader;

    std::vector<Text> strings;
};

#endif // TEXTRENDERER_HPP
