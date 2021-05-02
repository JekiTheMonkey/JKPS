#include "../Headers/Background.hpp"

Background::Background(sf::RenderWindow& window)
: mWindow(window)
{ 
    mBackgroundSprite.setColor(Settings::BackgroundColor);
}

void Background::handleEvent(sf::Event event)
{
    scaleTexture();
}

void Background::draw()
{
    mWindow.draw(mBackgroundSprite);
}

void Background::loadTextures(TextureHolder& textureHolder)
{
    mBackgroundSprite.setTexture(textureHolder.get(Textures::Background));
}

void Background::scaleTexture()
{
    mBackgroundSprite.scale((float) mWindow.getSize().x
                                    / (mBackgroundSprite.getTexture()->getSize().x
                                    * mBackgroundSprite.getScale().x),
                            (float) mWindow.getSize().y
                                    / (mBackgroundSprite.getTexture()->getSize().y
                                    * mBackgroundSprite.getScale().y));
}