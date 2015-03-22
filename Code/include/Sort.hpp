#ifndef SORT_HPP
#define SORT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Portee.hpp"
#include "SortVisuel.hpp"

class Sort : public sf::Drawable
{
    public:
        Sort();
        Sort(unsigned short sortIndex, unsigned char coutPA, unsigned char coutPM, unsigned char coutPW, sf::Time tempsIncantation, sf::Time cooldown, SortVisuel sortVisuel, std::vector<sf::Texture> const& textures);

        void restartElapsedTime();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    private:
        unsigned short m_sortIndex;
        sf::Sprite m_spriteSort;
        unsigned char m_coutPA;
        unsigned char m_coutPM;
        unsigned char m_coutPW;
        sf::Time m_tempsIncantation;
        sf::Time m_cooldown;
        sf::Clock m_elapsedTime;
        SortVisuel m_sortVisuel;
};

sf::Packet& operator <<(sf::Packet& packet, Sort const& sortLance);
sf::Packet& operator >>(sf::Packet& packet, Sort& sortLance);

#endif // SORT_HPP
