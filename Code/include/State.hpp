#ifndef STATE_HPP
#define STATE_HPP

#include <istream>

class State
{
    public:
        State();
        State(unsigned short s);

        bool m_movingRight;
        bool m_movingUp;
        bool m_movingLeft;
        bool m_movingDown;
        State& operator=(State const& s);

    private:
};


bool operator==(State const& l, State const& r);

bool operator!=(State const& l, State const& r);

std::ostream& operator<<(std::ostream& stream, State const& s);

#endif // STATE_HPP
