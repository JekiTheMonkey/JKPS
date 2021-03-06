#include "../Headers/KPSWindow.hpp"
#include "../Headers/Settings.hpp"
#include "../Headers/ResourceHolder.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/StringHelper.hpp"

#include <SFML/Window/Event.hpp>


static unsigned maxLen = 4U;

KPSWindow::KPSWindow(const FontHolder &fonts)
: mFonts(fonts)
{
    updateAssets();
    updateParameters();

    mKPSText.setString("KPS");
    mKPSNumber.setString("0");
    if (Settings::KPSWindowEnabledFromStart)
        openWindow();
}

void KPSWindow::handleOwnEvent()
{
    auto event = sf::Event();
    while (mWindow.pollEvent(event))
    { 
        if (event.type == sf::Event::KeyPressed)
        {
            const auto key = event.key;
            if (key.control && key.code == Settings::KeyExit)
                mWindow.close();
        }

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void KPSWindow::update()
{
    if (mWindow.isOpen())
    {
        auto str = std::string();
        const auto kps = Button::getKeysPerSecond();
        if (false)
            str = eraseDigitsOverHundredths(std::to_string(kps));
        else
            str = std::to_string(static_cast<unsigned>(kps));
        mKPSNumber.setString(str);

        mKPSNumber.setOrigin((mKPSNumber.getLocalBounds().left + 
            mKPSNumber.getLocalBounds().width) / 2.f, mKPSNumber.getLocalBounds().top);
    }
}

void KPSWindow::render()
{
    if (mWindow.isOpen())
    {
        auto textTransform = sf::Transform::Identity;
        auto numberTranform = sf::Transform::Identity;

        textTransform.translate((mWindow.getSize().x - mKPSText.getLocalBounds().width + 
            mKPSText.getLocalBounds().left) / 2.f, Settings::KPSWindowTopPadding);

        numberTranform.translate(mWindow.getSize().x / 2.f - mKPSNumber.getLocalBounds().left, 
            mKPSText.getLocalBounds().height + Settings::KPSWindowDistanceBetween + Settings::KPSWindowTopPadding);

        mWindow.clear(Settings::KPSBackgroundColor);

        mWindow.draw(mKPSText, textTransform);
        mWindow.draw(mKPSNumber, numberTranform);

        mWindow.display();
    }
}

void KPSWindow::updateParameters()
{
    mKPSText.setOrigin(mKPSText.getLocalBounds().left, mKPSText.getLocalBounds().top);
    mKPSNumber.setOrigin((mKPSNumber.getLocalBounds().left + mKPSNumber.getLocalBounds().width) / 2.f, 
        mKPSNumber.getLocalBounds().top);

    mKPSText.setCharacterSize(Settings::KPSTextSize);
    mKPSNumber.setCharacterSize(Settings::KPSNumberSize);

    mKPSText.setFillColor(Settings::KPSTextColor);
    mKPSNumber.setFillColor(Settings::KPSNumberColor);

    mWindow.setSize(sf::Vector2u(Settings::KPSWindowSize.x, Settings::KPSWindowSize.y));
    mWindow.setView(sf::View( { 0, 0, static_cast<float>(Settings::KPSWindowSize.x), static_cast<float>(Settings::KPSWindowSize.y) } ));
}   

void KPSWindow::updateAssets()
{
    mKPSText.setFont(mFonts.get(Fonts::KPSText));
    mKPSNumber.setFont(mFonts.get(Fonts::KPSNumber));
}

void KPSWindow::openWindow()
{
    sf::Uint32 style;
#ifdef _WIN32
    style = sf::Style::Close;
#elif linux
    style = sf::Style::Default;
#else
#error Unsupported compiler
#endif

    mWindow.create(sf::VideoMode(Settings::KPSWindowSize.x, 
        Settings::KPSWindowSize.y), "KPS Window", style);

#ifdef linux
    auto desktop = sf::VideoMode::getDesktopMode();
    mWindow.setPosition(sf::Vector2i(
        desktop.width / 1.5  - mWindow.getSize().x / 2, 
        desktop.height / 2 - mWindow.getSize().y / 2));
#endif
}

void KPSWindow::closeWindow()
{
    mWindow.close();
}

bool KPSWindow::isOpen() const
{
    return mWindow.isOpen();
}

bool KPSWindow::parameterIdMatches(LogicalParameter::ID id)
{
    return
        id == LogicalParameter::ID::KPSWndwSz ||
        id == LogicalParameter::ID::KPSWndwTxtChSz ||
        id == LogicalParameter::ID::KPSWndwNumChSz ||
        id == LogicalParameter::ID::KPSWndwBgClr ||
        id == LogicalParameter::ID::KPSWndwTxtClr ||
        id == LogicalParameter::ID::KPSWndwNumClr ||
        id == LogicalParameter::ID::KPSWndwTopPadding ||
        id == LogicalParameter::ID::KPSWndwDistBtw;
}