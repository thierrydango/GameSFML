#include "Portee.hpp"

Portee::Portee() :
    m_porteeMin{0},
    m_porteeMax{100}
{

}

Portee::Portee(unsigned short porteeMin, unsigned short porteeMax) :
    m_porteeMin{porteeMin},
    m_porteeMax{porteeMax}
{

}
