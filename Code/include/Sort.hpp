#ifndef SORT_HPP
#define SORT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Sort : public sf::Drawable
{
    public:
        Sort();
        Sort(std::string const& path, sf::Vector3f const& pos);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite m_spriteSort;
        sf::Texture m_textureSort;
        sf::Vector2f m_dimensions;
        float m_rayon;
        float m_degatsBase;
        sf::Vector3f m_position;
};

#endif // SORT_HPP
