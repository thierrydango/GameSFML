#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "State.hpp"

class Personnage
{
    public:
        Personnage(sf::Sprite, sf::Texture);

        sf::Vector2f getPosition();
        unsigned int getDirection();
        unsigned int getFrameNumber();
        unsigned int getAnimationNumber();
        unsigned int getX();
        unsigned int getY();
        unsigned int getZ();

        void startClock();

        void manageEvent(sf::Event const& event);
        void networkOrientedNextStep();
        void nextStep();

    private:
        /* Apparence du personnage */
        sf::Sprite m_spritePerso;
        sf::Texture m_texturePerso;
        unsigned int m_frameNumber;
        unsigned int m_animationNumber;
        sf::Clock m_tempsDepuisDebutAnimation;

        /* Positionnement du personnage */
        // Positions x, y et z du personnage
        sf::Vector3f m_position;
        // Vitesse de déplacement de base
        float m_vitesse;
        // Rayon du personnage
        float m_rayon;
        // Direction du personnage
        unsigned int m_direction;
        // Vecteur de projection
        sf::Vector3f m_projection;
        // Current moving state
        State m_state;

        /* Leveling du personnage */
        // Niveau du personnage
        unsigned int m_level;
        // Expérience totale
        std::uint64_t m_xpTotale;
        // Expérience pour up
        std::uint64_t m_xpPourUp;
        // Expérience donnée si vaincu
        std::uint64_t m_xpDonnee;

        /* Argent et objets du personnage */
        // Argent possédé
        std::uint64_t m_money;
        // Argent donné si vaincu
        std::uint64_t m_moneyDonnee;

        /* Stats du perso */
        // Points de vie maximum du personnage
        unsigned int m_pvMax;
        // Points de vie actuels du personnage
        unsigned int m_pvActuels;
        // Degats = Degats de l'attaque * (100 + m_puissance de la cible - m_resistance de soi) / 100
        // Puissance du personnage
        unsigned int m_puissance;
        // Resistance du personnage
        unsigned int m_resistance;

        bool m_movingRight;
        bool m_movingUp;
        bool m_movingLeft;
        bool m_movingDown;
};

#endif // PERSONNAGE_HPP
