#ifndef TEXTVISUEL_HPP
#define TEXTVISUEL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class TextVisuel : public sf::Drawable
{
    public:
        TextVisuel();
        TextVisuel(sf::Text text, sf::Time dureeDevie = sf::milliseconds(900), float direction=3.1416f/2.0f, float vitesse=4.0f, float acceleration=-2.0f);
        void nextStep();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // private:
        sf::Text m_text;
        sf::Time m_dureeDeVie;
        sf::Clock m_clock;
        float m_direction;
        float m_vitesse;
        float m_acceleration;
};

#endif // TEXTVISUEL_HPP
