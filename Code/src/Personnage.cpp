#include <iostream>
#include "Personnage.hpp"
#include "VectorFunctions.hpp"

Personnage::Personnage(sf::Sprite spritePerso, sf::Texture texturePerso)
{
    m_spritePerso = spritePerso;
    m_texturePerso = texturePerso;
    m_frameNumber = 0;
    m_animationNumber = 0;
    m_tempsDepuisDebutAnimation.restart();
    m_position = sf::Vector3f(50.0f, 50.0f, 0.0f);
    m_vitesse = 5.0f;
    m_rayon = 15.0f;
    m_direction = 0u;
    m_projection = sf::Vector3f(0.0f, 0.0f, 0.0f);
    m_level = 1u;
    m_xpTotale = 0;
    m_xpPourUp = 120;
    m_xpDonnee = 10;
    m_money = 50;
    m_moneyDonnee = 10;
    m_pvMax = 55u;
    m_pvActuels = 55u;
    m_puissance = 0u;
    m_resistance = 0u;

    m_movingRight = false;
    m_movingUp = false;
    m_movingLeft = false;
    m_movingDown = false;
}

sf::Vector2f Personnage::getPosition()
{
    return sf::Vector2f(m_position.x, m_position.y);
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

unsigned int Personnage::getX()
{
    return m_position.x;
}

unsigned int Personnage::getY()
{
    return m_position.y;
}

unsigned int Personnage::getZ()
{
    return m_position.z;
}

void Personnage::startClock()
{
    m_tempsDepuisDebutAnimation.restart();
}

void Personnage::networkOrientedNextStep()
{
    //Gestion du clavier
    sf::Vector3f nextMove;
    bool moving = true;

    if (!m_movingRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_movingRight = true;
    }

    if (!m_movingUp && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_movingUp = true;
    }

    if (!m_movingLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_movingLeft = true;
    }

    if (!m_movingDown && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_movingDown = true;
    }

    if (m_movingRight && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_movingRight = false;
    }

    if (m_movingUp && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_movingUp = false;
    }

    if (m_movingLeft && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_movingLeft = false;
    }

    if (m_movingDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_movingDown = false;
    }

    if (m_movingUp)
    {
        nextMove += sf::Vector3f(0.0f, -1.0f, 0.0f);
    }

    if (m_movingDown)
    {
        nextMove += sf::Vector3f(0.0f, 1.0f, 0.0f);
    }

    if (m_movingRight)
    {
        nextMove += sf::Vector3f(1.0f, 0.0f, 0.0f);
    }

    if (m_movingLeft)
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
