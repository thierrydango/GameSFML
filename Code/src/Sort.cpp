#include <iostream>
#include "Sort.hpp"

Sort::Sort() :
    m_degatsBase{1.0f},
    m_position{0.0f, 0.0f, 0.0f}
{

}

Sort::Sort(std::string const& path, sf::Vector3f const& pos) :
    m_spriteSort{},
    m_textureSort{},
    m_dimensions{32u,32u},
    m_rayon{16},
    m_degatsBase{5}
{
    m_position = pos;
}

