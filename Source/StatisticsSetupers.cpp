#include "../Headers/Statistics.hpp"

void Statistics::setupText(ID id)
{
    mTexts.build(id);
    mTexts.get(id).setCharacterSize(Settings::StatisticsTextCharacterSize);
    mTexts.get(id).setFillColor(Settings::StatisticsTextColor);
    mTexts.get(id).setPosition(sf::Vector2f
                                ( mWindow.getSize().x 
                                + Settings::SpaceBetweenButtonsAndStatistics 
                                - Settings::StatisticsTextCharacterSize * 9.f
                                , Settings::Distance 
                                + Settings::StatisticsTextCharacterSize * id ));
}

void Statistics::setupTextVector()
{
    mKeyCountersText.resize(Settings::KeyAmount);
    for (size_t i = 0; i < Settings::KeyAmount; ++i)
    {
        mKeyCountersText[i].setCharacterSize(Settings::KeyCountersTextCharacterSize);
        mKeyCountersText[i].setFillColor(Settings::KeyCountersTextColor);

        setupTextPosition(i);
    }
}

void Statistics::setupTextPosition(int index)
{
    mKeyCountersText[index].setOrigin(sf::Vector2f
                                (mKeyCountersText[index].getLocalBounds().width  / 2.f
                                , mKeyCountersText[index].getLocalBounds().height / 1.2f));

    mKeyCountersText[index].setPosition(sf::Vector2f
                                (Settings::Distance * (index + 1) 
                                + Settings::DefaultButtonTextureSize.x / 2.f * (index * 2 + 1)
                                , Settings::Distance + Settings::DefaultButtonTextureSize.y / 2.f));
}

void Statistics::setupLong(ID id)
{
    mLongs.build(id);
    mLongs.get(id) = 0;
}

void Statistics::setupLongVector()
{
    mKeyCounters.resize(Settings::KeyAmount);
    for (auto& element : mKeyCounters)
        element = 0;
}

void Statistics::setupLongVector(std::size_t index)
{
    mKeyCounters.resize(Settings::KeyAmount);
    mKeyCounters[index] = 0;
}

void Statistics::setupString(ID id, const std::string& name)
{
    mStrings.build(id);
    mStrings.get(id) = name;
}

void Statistics::setupStringVector()
{
    for (size_t i = 0; i < Settings::KeyAmount; ++i)
    {
        mKeyCountersText[i].setString(std::to_string(mKeyCounters[i]));
    }
}