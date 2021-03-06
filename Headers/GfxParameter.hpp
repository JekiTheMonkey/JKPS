#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "ResourceIdentifiers.hpp"

#include <string>
#include <vector>
#include <memory>


class ParameterLine;

struct GfxParameter : public sf::Drawable, public sf::Transformable
{
    public:
        GfxParameter(const ParameterLine *parent, const std::string &str, unsigned n, sf::Vector2f rectSize = sf::Vector2f(70.f, 25.f));
        GfxParameter(const ParameterLine *parent, bool b);
        GfxParameter(const std::string &str, sf::Vector2f rectSize);
        GfxParameter(const ParameterLine *parent);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void setupValPos();
        bool contains(sf::Vector2f v2) const;
        sf::Vector2f getGlobalPosition() const;
        sf::FloatRect getGlobalBounds() const;

        void setInverseMark();
        void setRightTexture();

        static float getPosX();


    public:
        static const TextureHolder *mTextures;
        static const FontHolder *mFonts;

        const ParameterLine *mParent;

        sf::Sprite mSprite;
        sf::RectangleShape mRect;
        const static sf::Color defaultRectColor;
        const static sf::Color defaultAimedRectColor;
        const static sf::Color defaultSelectedRectColor;
        sf::Text mValText;
};