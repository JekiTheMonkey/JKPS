#include "../Headers/Application.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60);

Application::Application(Settings& settings)
: mTextures()
, mFonts()
, mSettings(settings)
, mCalculation()
, mKeyPressingManager()
, mStatistics(mWindow)
, mButtons(mWindow)
, mWindow(sf::VideoMode
                        ( Settings::Distance * Settings::KeyAmount
                        + Settings::DefaultButtonTextureSize.x * Settings::KeyAmount
                        + Settings::SpaceBetweenButtonsAndStatistics
                        + Settings::StatisticsTextCharacterSize * 9
                        , Settings::Distance * 2
                        + Settings::DefaultButtonTextureSize.y )
                    , "KPS"
                    , sf::Style::None)
{
	mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(60);

    mFonts.load(Fonts::Main, "../KPSFont.ttf");
    mTextures.load(Textures::KeyButton, "../KPSButtonTexture.png");
    // mTextures.get(Textures::KeyButton).setSmooth(true); Does it change anything?

    mStatistics.loadFonts(mFonts);
    mStatistics.setFonts();
    mButtons.loadTextures(mTextures.get(Textures::KeyButton));

    mButtons.setupTexture();
    mButtons.setupAnimation();

    mSettings.setWindowReference(mWindow);
    mSettings.setChangeabilityPosition();
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
        }

        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    int i = 0;
    mKeyPressingManager.readClickedKeys(mSettings.isChangeable());
    while (mWindow.pollEvent(event))
    {
        if (mWindow.hasFocus())
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    mSettings.changeChangeability();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                &&  sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Save config
                    mWindow.close();
                }
            }

            if (mSettings.isChangeable())
            {
                mSettings.handleEvent(event);
                handleEvent(event);
                mSettings.setChangeabilityPosition();
                mStatistics.handleEvent(event);
                mButtons.handleEvent(event);
                mKeyPressingManager.handleEvent(event);
            }
        }
    }
    
    if (!mSettings.isChangeable())
    {
        mCalculation.handleInput(mKeyPressingManager, Settings::Keys);
        mStatistics.handleInput(mKeyPressingManager);
        mButtons.handleInput(mKeyPressingManager.mNeedToBeReleased);
    }
}

void Application::update(sf::Time dt)
{
    mCalculation.update();
    mStatistics.update
                    ( mCalculation.getKeyPerSecond()
                    , mCalculation.getBeatsPerMinute()
                    , mKeyPressingManager.mClickedKeys
                    , mSettings.isChangeable() );
    mButtons.update(mKeyPressingManager.mNeedToBeReleased);
    mKeyPressingManager.clear();
}

void Application::render()
{
    mWindow.clear();
    mButtons.draw();
    mStatistics.draw();
    mSettings.draw();
    mWindow.display();
}

void Application::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == Settings::KeyToIncrease
        || event.key.code == Settings::KeyToDecrease)
        {
            mWindow.setSize(sf::Vector2u
                            ( Settings::Distance * Settings::KeyAmount
                            + Settings::DefaultButtonTextureSize.x * Settings::KeyAmount
                            + Settings::SpaceBetweenButtonsAndStatistics
                            + Settings::StatisticsTextCharacterSize * 9
                            , Settings::Distance * 2
                            + Settings::DefaultButtonTextureSize.y ));

            mWindow.setView(sf::View(sf::FloatRect
                            ( 0, 0
                            , mWindow.getSize().x
                            , mWindow.getSize().y )));
        }
    }
}