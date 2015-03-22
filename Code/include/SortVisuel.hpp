#ifndef SORTVISUEL_HPP
#define SORTVISUEL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class SortVisuel : public sf::Drawable
{
    public:
        SortVisuel();
        SortVisuel(sf::Vector3f const& pos, unsigned short textureIndex, std::vector<sf::Texture> const& textures, unsigned int puissance);

        sf::Vector2f getOrigin();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    private:
        sf::Sprite m_spriteSort;
        unsigned short m_textureIndex;
        sf::Vector2f m_dimensions;
        unsigned short m_rayon;
        unsigned int m_degatsBase;
        sf::Vector3f m_position;
};

#endif // SORTVISUEL_HPP
