#include <iostream>
#include "Personnage.hpp"
#include "VectorFunctions.hpp"

Personnage::Personnage() :
    m_position{0.0f, 0.0f, 0.0f},
    m_projection{0.0f, 0.0f, 0.0f}
{

}

Personnage::Personnage(std::string const& path) :
    m_spritePerso{},
    m_texturePerso{},
    m_dimensions{26u, 59u},
    m_frameNumber{0},
    m_animationNumber{0},
    m_position{200.0f, 480.0f, 0.0f},
    m_vitesse{5.0f},
    m_rayon{15.0f},
    m_direction{0u},
    m_projection{0.0f, 0.0f, 0.0f},
    m_state{},
    m_level{1u},
    m_xpTotale{0},
    m_xpPourUp{120},
    m_xpDonnee{10},
    m_money{50},
    m_moneyDonnee{10},
    m_pvMax{55u},
    m_pvActuels{55u},
    m_puissance{0u},
    m_resistance{0u}
{
    m_tempsDepuisDebutAnimation.restart();
    m_texturePerso.loadFromFile(path);
    m_spritePerso.setTexture(m_texturePerso);
}

sf::Vector2f Personnage::getPosition()
{
    return sf::Vector2f(m_position.x, m_position.y);
}

sf::Vector2f Personnage::getDimensions()
{
    return m_dimensions;
}

sf::Vector2f Personnage::getOrigin()
{
    return sf::Vector2f(m_position.x, m_position.y) - m_dimensions/2.0f;
}

unsigned int Personnage::getDirection()
{
    return m_direction;
}

unsigned int Personnage::getFrameNumber()
{
    return m_frameNumber;
}

unsigned int Personnage::getAnimationNumber()
{
    return m_animationNumber;
}

float Personnage::getX()
{
    return m_position.x;
}

float Personnage::getY()
{
    return m_position.y;
}

float Personnage::getZ()
{
    return m_position.z;
}

State Personnage::getState()
{
    return m_state;
}

sf::Sprite& Personnage::getSpritePerso()
{
    return m_spritePerso;
}

void Personnage::setX(float x)
{
    m_position.x = x;
}

void Personnage::setY(float y)
{
    m_position.y = y;
}

void Personnage::setZ(float z)
{
    m_position.z = z;
}

void Personnage::setState(State s)
{
    m_state = s;
}

void Personnage::startClock()
{
    m_tempsDepuisDebutAnimation.restart();
}

bool Personnage::manageEvent(sf::Event const& event, sf::Packet& packet)
{
    if ((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased))
    {
        State currentState = m_state;

        switch (event.key.code)
        {
            case sf::Keyboard::Right:
                m_state.m_movingRight = (event.type == sf::Event::KeyPressed);
                break;

            case sf::Keyboard::Up:
                m_state.m_movingUp    = (event.type == sf::Event::KeyPressed);
                break;

            case sf::Keyboard::Left:
                m_state.m_movingLeft  = (event.type == sf::Event::KeyPressed);
                break;

            case sf::Keyboard::Down:
                m_state.m_movingDown  = (event.type == sf::Event::KeyPressed);
                break;

            default:
                break;
        }

        if (m_state != currentState)
        {
            // On duplique 4 fois chaque booléen de sorte que ça rentre sur 16 bits
            //
            // DROITE    HAUT      GAUCHE    BAS
            // 0 1 0 0   1 1 0 0   0 1 0 1   0 0 1 0
            unsigned char packetType = 1;
            unsigned short newState = ((32768+16384+8192+4096)*m_state.m_movingRight + (2048+1024+512+256)*m_state.m_movingUp + (128+64+32+16)*m_state.m_movingLeft + (8+4+2+1)*m_state.m_movingDown);
            short posX = static_cast<short>(std::round(m_position.x));
            short posY = static_cast<short>(std::round(m_position.y));
            packet << packetType << newState << posX << posY;
            return true;
        }
    }
    return false;
}

void Personnage::networkOrientedNextStep()
{
    //Gestion du clavier
    sf::Vector3f nextMove;
    bool moving = true;

    if (m_state.m_movingUp)
    {
        nextMove += sf::Vector3f(0.0f, -1.0f, 0.0f);
    }

    if (m_state.m_movingDown)
    {
        nextMove += sf::Vector3f(0.0f, 1.0f, 0.0f);
    }

    if (m_state.m_movingRight)
    {
        nextMove += sf::Vector3f(1.0f, 0.0f, 0.0f);
    }

    if (m_state.m_movingLeft)
    {
        nextMove += sf::Vector3f(-1.0f, 0.0f, 0.0f);
    }

    if (nextMove.x > 0 && nextMove.y == 0)
    {
        m_direction = 0;
        m_animationNumber = 0;
    }

    if (nextMove.x > 0 && nextMove.y < 0)
    {
        m_direction = 4;
        m_animationNumber = 1;
    }

    if (nextMove.x == 0 && nextMove.y < 0)
    {
        m_direction = 8;
        m_animationNumber = 2;
    }

    if (nextMove.x < 0 && nextMove.y < 0)
    {
        m_direction = 12;
        m_animationNumber = 3;
    }

    if (nextMove.x < 0 && nextMove.y == 0)
    {
        m_direction = 16;
        m_animationNumber = 4;
    }

    if (nextMove.x < 0 && nextMove.y > 0)
    {
        m_direction = 20;
        m_animationNumber = 5;
    }

    if (nextMove.x == 0 && nextMove.y > 0)
    {
        m_direction = 24;
        m_animationNumber = 6;
    }

    if (nextMove.x > 0 && nextMove.y > 0)
    {
        m_direction = 28;
        m_animationNumber = 7;
    }

    if (nextMove.x == 0 && nextMove.y == 0)
    {
        m_frameNumber = 3;
        moving = false;
        m_tempsDepuisDebutAnimation.restart();
    }

    if (moving && m_vitesse * m_tempsDepuisDebutAnimation.getElapsedTime() > sf::milliseconds(315.0))
    {
        m_frameNumber++;
        if (m_frameNumber > 3)
            m_frameNumber = 0;
        m_tempsDepuisDebutAnimation.restart();
    }

    //nextMove /= nextMove.norm(); passé en commentaire car ne compile pas
    float normeDuDeplacement = std::sqrt(nextMove.x * nextMove.x + nextMove.y * nextMove.y + nextMove.z * nextMove.z);
    if (normeDuDeplacement > 0)
    {
        nextMove *= std::round(m_vitesse/normeDuDeplacement);
        sf::Vector3f nextPosition = m_position + nextMove;
        if (pow(nextPosition.x/640 - 1,2) + pow(nextPosition.y/480 - 1,2) < 1)
            m_position += nextMove;
        else
        {
            if (nextPosition.x >= 640 && nextPosition.y <= 500)
            {
                m_position += sf::Vector3f(-3.0f,3.0f,0.0f);
            }
            else if (nextPosition.x < 640 && nextPosition.y <= 500)
            {
                m_position += sf::Vector3f(3.0f,3.0f,0.0f);
            }
            else if (nextPosition.x < 640 && nextPosition.y > 500)
            {
                m_position += sf::Vector3f(3.0f,-3.0f,0.0f);
            }
            else if (nextPosition.x >= 640 && nextPosition.y > 500)
            {
                m_position += sf::Vector3f(-3.0f,-3.0f,0.0f);
            }
        }
    }
}

void Personnage::nextStep()
{
    //Gestion du clavier
    sf::Vector3f nextMove;
    bool moving = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        nextMove += sf::Vector3f(0.0f, -1.0f, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        nextMove += sf::Vector3f(0.0f, 1.0f, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        nextMove += sf::Vector3f(1.0f, 0.0f, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        nextMove += sf::Vector3f(-1.0f, 0.0f, 0.0f);
    }

    if (nextMove.x > 0 && nextMove.y == 0)
    {
        m_direction = 0;
        m_animationNumber = 0;
    }

    if (nextMove.x > 0 && nextMove.y < 0)
    {
        m_direction = 4;
        m_animationNumber = 1;
    }

    if (nextMove.x == 0 && nextMove.y < 0)
    {
        m_direction = 8;
        m_animationNumber = 2;
    }

    if (nextMove.x < 0 && nextMove.y < 0)
    {
        m_direction = 12;
        m_animationNumber = 3;
    }

    if (nextMove.x < 0 && nextMove.y == 0)
    {
        m_direction = 16;
        m_animationNumber = 4;
    }

    if (nextMove.x < 0 && nextMove.y > 0)
    {
        m_direction = 20;
        m_animationNumber = 5;
    }

    if (nextMove.x == 0 && nextMove.y > 0)
    {
        m_direction = 24;
        m_animationNumber = 6;
    }

    if (nextMove.x > 0 && nextMove.y > 0)
    {
        m_direction = 28;
        m_animationNumber = 7;
    }

    if (nextMove.x == 0 && nextMove.y == 0)
    {
        m_frameNumber = 3;
        moving = false;
        m_tempsDepuisDebutAnimation.restart();
    }

    if (moving && m_vitesse * m_tempsDepuisDebutAnimation.getElapsedTime() > sf::milliseconds(315.0))
    {
        m_frameNumber++;
        if (m_frameNumber > 3)
            m_frameNumber = 0;
        m_tempsDepuisDebutAnimation.restart();
    }

    //nextMove /= nextMove.norm(); passé en commentaire car ne compile pas
    float normeDuDeplacement = std::sqrt(nextMove.x * nextMove.x + nextMove.y * nextMove.y + nextMove.z * nextMove.z);
    if (normeDuDeplacement > 0)
    {
        nextMove *= std::round(m_vitesse/normeDuDeplacement);
        m_position += nextMove;
    }
}

void Personnage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_spritePerso);
}
