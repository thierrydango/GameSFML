#include <iostream>
#include "Sort.hpp"

Sort::Sort() :
    m_degatsBase{1u}
{

}

Sort::Sort(unsigned short sortIndex, unsigned char coutPA, unsigned char coutPM, unsigned char coutPW, sf::Time tempsIncantation, sf::Time cooldown, unsigned short porteeMin, unsigned short longueurTrajectoire, unsigned short textureIndex, unsigned short rayon, unsigned int degatsBase, std::vector<sf::Texture> const& textures) :
    m_sortIndex{sortIndex},
    m_coutPA{coutPA},
    m_coutPM{coutPM},
    m_coutPW{coutPW},
    m_tempsIncantation{tempsIncantation},
    m_cooldown{cooldown},
    m_porteeMin{porteeMin},
    m_longueurTrajectoire{longueurTrajectoire},
    m_textureIndex{textureIndex},
    m_rayon{rayon},
    m_degatsBase{degatsBase}
{
    m_spriteSort.setTexture(textures[m_sortIndex]);
    m_spriteSort.setScale(0.5f,0.5f);
}

void Sort::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_spriteSort);
}
