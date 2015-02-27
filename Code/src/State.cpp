#include <iostream>

#include "State.hpp"

State::State()
{
    m_movingRight = false;
    m_movingUp    = false;
    m_movingLeft  = false;
    m_movingDown  = false;
}

bool operator==(State const& l, State const& r)
{
    return ((l.m_movingRight == r.m_movingRight) && (l.m_movingUp == r.m_movingUp) && (l.m_movingLeft == r.m_movingLeft) && (l.m_movingDown == r.m_movingDown));
}

bool operator!=(State const& l, State const& r)
{
    return ((l.m_movingRight != r.m_movingRight) || (l.m_movingUp != r.m_movingUp) || (l.m_movingLeft != r.m_movingLeft) || (l.m_movingDown != l.m_movingDown));
}
