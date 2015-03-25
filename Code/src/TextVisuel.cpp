#include "TextVisuel.hpp"
#include <iostream>

TextVisuel::TextVisuel()
{

}

TextVisuel::TextVisuel(sf::Text text, sf::Time dureeDeVie, float direction, float vitesse, float acceleration) :
    m_text{text},
    m_dureeDeVie{dureeDeVie},
    m_direction{direction},
    m_vitesse{vitesse},
    m_acceleration{acceleration}
{

}

void TextVisuel::nextStep()
{
    sf::Color colorText = m_text.getColor();
    m_text.setColor(sf::Color(colorText.r, colorText.g, colorText.b, 255-255*(static_cast<float>(m_clock.getElapsedTime().asMilliseconds())/static_cast<float>(m_dureeDeVie.asMilliseconds()))));
    m_text.setPosition(m_text.getPosition().x + m_vitesse*cos(m_direction),m_text.getPosition().y - m_vitesse*sin(m_direction));
    m_vitesse += m_acceleration/10.0f;
}

void TextVisuel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text);
}
