#pragma once

#include "ecs.h"

class TextureComponent : public ecs::Component<TextureComponent>
{
    using TextureID = unsigned int;

public:
    TextureComponent() = default;
    TextureComponent(const std::string& textureFileName);

    virtual ~TextureComponent() = default;

public:
    void Apply();
    void Misapply();

    inline auto&       GetTextureFileName() { return this->textureFileName; }
    inline const auto& GetTextureFileName() const { return this->textureFileName; }

    inline auto&       GetTextureID() { return this->textureId; }
    inline const auto& GetTextureID() const { return this->textureId; }

    void SetTextureFileName(const std::string& textureFileName)
    {
        this->textureFileName = textureFileName;
        this->Initialize();
    }

private:
    void SetTextureID(const TextureID) = delete;

private:
    void Initialize();

private:
    std::string textureFileName;

    TextureID textureId;
};
