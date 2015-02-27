#ifndef STATE_HPP
#define STATE_HPP

class State
{
    public:
        State();

        bool m_movingRight;
        bool m_movingUp;
        bool m_movingLeft;
        bool m_movingDown;

    private:
};

bool operator==(State const& l, State const& r);

bool operator!=(State const& l, State const& r);

#endif // STATE_HPP
