#include <iostream>
#include "Sort.hpp"

Sort::Sort() :
    m_sortIndex{0},
    m_coutPA{0},
    m_coutPM{0},
    m_coutPW{0},
    m_cooldown{sf::milliseconds(0)}
{

}

Sort::Sort(unsigned short sortIndex, unsigned char coutPA, unsigned char coutPM, unsigned char coutPW, sf::Time tempsIncantation, sf::Time cooldown, SortVisuel sortVisuel, std::vector<sf::Texture> const& textures) :
    m_sortIndex{sortIndex},
    m_coutPA{coutPA},
    m_coutPM{coutPM},
    m_coutPW{coutPW},
    m_tempsIncantation{tempsIncantation},
    m_cooldown{cooldown},
    m_elapsedTime{sf::Clock()},
    m_sortVisuel{sortVisuel}
{
    m_spriteSort.setTexture(textures[m_sortIndex]);
    m_spriteSort.setScale(0.5f,0.5f);
}

void Sort::restartElapsedTime()
{
    m_elapsedTime.restart();
}

void Sort::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_spriteSort);
}

sf::Packet& operator <<(sf::Packet& packet, Sort const& sortLance)
{
    return packet << sortLance.m_tempsIncantation.asMilliseconds() << sortLance.m_sortVisuel;
}

sf::Packet& operator >>(sf::Packet& packet, Sort& sortLance)
{
    sf::Int32 tempsIncan;
    packet >> tempsIncan >> sortLance.m_sortVisuel;
    sortLance.m_tempsIncantation = sf::milliseconds(tempsIncan);
    return packet;
}
