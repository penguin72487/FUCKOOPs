#include "UIComponent.hpp"
#include "Button.hpp"


class MainMenu : public UIComponent {
private:
    enum class Show {
        Picture,
        ILLUSTRATE,
        DEVELOPER
    };
    sf::Text title;
    Button illustrateButton, settingButton, startGameButton, exitGameButton, developerButton;
    sf::Texture pic;
    sf::Sprite picture;
    Show show = Show::Picture;
    sf::Text illustrateText;
    sf::Text developerText;

public:
    MainMenu(sf::RenderWindow& window);
    Screen render() override;
};
