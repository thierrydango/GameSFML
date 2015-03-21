#ifndef SORT_HPP
#define SORT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Portee.hpp"

class Sort
{
    public:
        Sort();
        Sort(std::string const& path, sf::Vector3f const& pos);

//    private:
        sf::Sprite m_spriteSort;
        sf::Texture m_textureSort;
        sf::Vector2f m_dimensions;
        float m_rayon;
        float m_degatsBase;
        sf::Vector3f m_position;
};

#endif // SORT_HPP
