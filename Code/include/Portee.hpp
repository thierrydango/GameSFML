#ifndef PORTEE_HPP
#define PORTEE_HPP

class Portee
{
    public:
        Portee();
        Portee(unsigned short porteeMin, unsigned short porteeMax);

        unsigned short m_porteeMin;
        unsigned short m_porteeMax;
};

#endif // PORTEE_HPP
