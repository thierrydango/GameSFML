#ifndef SORT_HPP
#define SORT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Portee.hpp"

class Sort : public sf::Drawable
{
    public:
        Sort();
        Sort(unsigned short sortIndex, unsigned char coutPA, unsigned char coutPM, unsigned char coutPW, sf::Time tempsIncantation, sf::Time cooldown, unsigned short porteeMin, unsigned short longueurTrajectoire, unsigned short textureIndex, unsigned short rayon, unsigned int m_degatsBase, std::vector<sf::Texture> const& textures);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    private:
        unsigned short m_sortIndex;
        sf::Sprite m_spriteSort;
        unsigned char m_coutPA;
        unsigned char m_coutPM;
        unsigned char m_coutPW;
        sf::Time m_tempsIncantation;
        sf::Time m_cooldown;
        unsigned short m_porteeMin;
        unsigned short m_longueurTrajectoire;
        unsigned short m_textureIndex;
        unsigned short m_rayon;
        unsigned int m_degatsBase;
};

#endif // SORT_HPP
