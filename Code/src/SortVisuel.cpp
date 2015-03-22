#include <iostream>
#include "SortVisuel.hpp"

SortVisuel::SortVisuel() :
    m_textureIndex{0},
    m_degatsBase{1u},
    m_position{0.0f, 0.0f, 0.0f}
{

}

SortVisuel::SortVisuel(sf::Vector3f const& pos, unsigned short textureIndex, std::vector<sf::Texture> const& textures, unsigned int puissance) :
    m_spriteSort{},
    m_textureIndex{textureIndex},
    m_dimensions{32u,32u},
    m_rayon{16},
    m_degatsBase{puissance}
{
    m_spriteSort.setTexture(textures[m_textureIndex]);
    m_position = pos;
}

sf::Vector2f SortVisuel::getOrigin()
{
    return sf::Vector2f(m_position.x, m_position.y) - m_dimensions/2.0f;
}

void SortVisuel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_spriteSort);
}
