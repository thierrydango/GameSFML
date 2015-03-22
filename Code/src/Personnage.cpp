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
    m_resistance{0u},
    m_PAmax{6},
    m_PMmax{3},
    m_PWmax{6},
    m_PA{6},
    m_PM{3},
    m_PW{6},
    m_regenPV{0.0f},
    m_regenPA{0.0f},
    m_regenPM{0.0f},
    m_regenPW{0.0f},
    m_speedRegenPV{0.01f},
    m_speedRegenPA{0.01f},
    m_speedRegenPM{0.005f},
    m_speedRegenPW{0.001f},
    m_tempsIncantation{sf::milliseconds(0)}
{
    m_tempsDepuisDebutAnimation.restart();
    m_texturePerso.loadFromFile(path);
    m_spritePerso.setTexture(m_texturePerso);
    m_tempsIncante.restart();
}

sf::Vector2f Personnage::getOrigin()
{
    return sf::Vector2f(m_position.x, m_position.y)- m_dimensions/2.0f;
}

void Personnage::startClock()
{
    m_tempsDepuisDebutAnimation.restart();
}

bool Personnage::manageEvent(sf::Event const& event, sf::Packet& packet, std::vector<Sort> & sortsIcons, std::vector<std::pair<sf::Clock, Sort>>& sortsAttente)
{
    // Traitement des évènements de type Flèches directionnelles
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

    // Traitement des évènements de type Lancement de sort
    if (event.type == sf::Event::KeyReleased && m_tempsIncante.getElapsedTime() >= m_tempsIncantation)
    {
        bool keySort = false;
        Sort sortLance;
        unsigned short indexSortLance = 0;

        switch (event.key.code)
        {
            case sf::Keyboard::A:
                keySort = true;
                indexSortLance = 0;
                break;

            case sf::Keyboard::Z:
                keySort = true;
                indexSortLance = 1;
                break;

            case sf::Keyboard::E:
                keySort = true;
                indexSortLance = 2;
                break;

            case sf::Keyboard::R:
                keySort = true;
                indexSortLance = 3;
                break;

            case sf::Keyboard::T:
                keySort = true;
                indexSortLance = 4;
                break;

            case sf::Keyboard::Y:
                keySort = true;
                indexSortLance = 5;
                break;

            case sf::Keyboard::U:
                keySort = true;
                indexSortLance = 6;
                break;

            case sf::Keyboard::I:
                keySort = true;
                indexSortLance = 7;
                break;

            case sf::Keyboard::O:
                keySort = true;
                indexSortLance = 8;
                break;

            case sf::Keyboard::P:
                keySort = true;
                indexSortLance = 9;
                break;

            default:
                break;
        }

        if (keySort)
        {
            sortLance = sortsIcons[indexSortLance];
            SortVisuel sortVisuelLance = sortLance.m_sortVisuel;
            unsigned char coutPA{sortLance.m_coutPA};
            unsigned char coutPM{sortLance.m_coutPM};
            unsigned char coutPW{sortLance.m_coutPW};
            sf::Time tempsIncantation{sortLance.m_tempsIncantation};
            sf::Time cooldown{sortLance.m_cooldown};
            sf::Time elapsedTime{sortLance.m_elapsedTime.getElapsedTime()};

            if (elapsedTime >= cooldown && m_PA >= coutPA && m_PM >= coutPM && m_PW >= coutPW)
            {
                // Le packet sera de la forme :
                // (2, Xperso, Yperso, tempsIncanta, porteeMin, longuTraj, textureIdx, rayon, degats)
                sortsIcons[indexSortLance].restartElapsedTime();
                m_PA -= coutPA;
                m_PM -= coutPM;
                m_PW -= coutPW;
                unsigned char packetType = 2;
                packet << packetType << sortLance;
                sortsAttente.push_back(std::make_pair(sf::Clock(),sortLance));
                m_tempsIncantation = tempsIncantation;
                m_tempsIncante.restart();
                return true;
            }
        }
    }

    return false;
}

void Personnage::regenStep()
{
    if (m_PA < m_PAmax)
    {
        m_regenPA += m_speedRegenPA;
        while (m_regenPA >= 1 && m_PA < m_PAmax)
        {
            m_PA++;
            m_regenPA--;
        }
    }
    else
    {
        m_regenPA = 0;
    }

    if (m_PM < m_PMmax && m_state == State{0})
    {
        m_regenPM += m_speedRegenPM;
        while (m_regenPM >= 1 && m_PM < m_PMmax)
        {
            m_PM++;
            m_regenPM--;
        }
    }
    else
    {
        if (m_PM >= m_PMmax)
            m_regenPM = 0;
    }

    if (m_PW < m_PWmax)
    {
        m_regenPW += m_speedRegenPW;
        while (m_regenPW >= 1 && m_PW < m_PWmax)
        {
            m_PW++;
            m_regenPW--;
        }
    }
    else
    {
        m_regenPW = 0;
    }

    if (m_pvActuels < m_pvMax)
    {
        m_regenPV += m_speedRegenPV;
        while (m_regenPV >= 1 && m_pvActuels < m_pvMax)
        {
            m_pvActuels++;
            m_regenPV--;
        }
    }
    else
    {
        m_regenPV = 0;
    }
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
            while (pow(nextPosition.x/640 - 1,2) + pow(nextPosition.y/480 - 1,2) >= 1)
            {
                sf::Vector3f recul = nextPosition - sf::Vector3f{640.0f,480.0f,0.0f};
                recul = recul/std::sqrt(recul.x*recul.x + recul.y*recul.y + recul.z*recul.z);
                nextPosition = nextPosition - recul;
            }
            m_position = nextPosition;
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
