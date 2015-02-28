#include <iostream>
#include <bitset>
#include <math.h>

#include "State.hpp"

State::State()
{
    m_movingRight = false;
    m_movingUp    = false;
    m_movingLeft  = false;
    m_movingDown  = false;
}

State::State(unsigned short s)
{
    std::bitset<16> b;
    unsigned short k = 1;
    // Traduction de l'unsigned short en bitset
    for (size_t i = 1; i < b.size(); i++)
    {
        if (s%(2*k) == k)
        {
            b.set(i);
            s -= k;
        }
        k *= 2;
    }

    m_movingDown  = (b[0] +b[1] +b[2] +b[3]  > 2);
    m_movingLeft  = (b[4] +b[5] +b[6] +b[7]  > 2);
    m_movingUp    = (b[8] +b[9] +b[10]+b[11] > 2);
    m_movingRight = (b[12]+b[13]+b[14]+b[15] > 2);
}

State& State::operator=(State const& s)
{
    this->m_movingRight = s.m_movingRight;
    this->m_movingUp    = s.m_movingUp;
    this->m_movingLeft  = s.m_movingLeft;
    this->m_movingDown  = s.m_movingDown;
    return *this;
}

bool operator==(State const& l, State const& r)
{
    return ((l.m_movingRight == r.m_movingRight) &&
            (l.m_movingUp    == r.m_movingUp   ) &&
            (l.m_movingLeft  == r.m_movingLeft ) &&
            (l.m_movingDown  == r.m_movingDown ));
}

bool operator!=(State const& l, State const& r)
{
    return ((l.m_movingRight != r.m_movingRight) || (l.m_movingUp != r.m_movingUp) || (l.m_movingLeft != r.m_movingLeft) || (l.m_movingDown != r.m_movingDown));
}

std::ostream& operator<<(std::ostream& stream, State const& s)
{
    stream << "[ ";
    if (s.m_movingRight)
        stream << "Right ";
    if (s.m_movingUp)
        stream << "Up ";
    if (s.m_movingLeft)
        stream << "Left ";
    if (s.m_movingDown)
        stream << "Down ";
    stream << "]";

    return stream;
}
