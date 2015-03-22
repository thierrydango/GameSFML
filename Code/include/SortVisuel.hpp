#ifndef SORTVISUEL_HPP
#define SORTVISUEL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class SortVisuel : public sf::Drawable
{
    public:
        SortVisuel();
        SortVisuel(sf::Vector3f const& pos, unsigned short textureIndex, std::vector<sf::Texture> const& textures, unsigned short rayon, unsigned int puissance, unsigned short porteeMin, unsigned short longueurTrajectoire, unsigned char vitesse, unsigned char acceleration, unsigned char angle, unsigned char vitesseRotation, unsigned char accelerationAngulaire, sf::Time dureeDeVie);

        sf::Vector2f getOrigin();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    private:
        sf::Sprite m_spriteSort;
        unsigned short m_textureIndex;
        sf::Vector2f m_dimensions;
        unsigned short m_rayon;
        unsigned int m_degatsBase;
        unsigned short m_porteeMin;
        sf::Vector3f m_position;
        unsigned short m_longueurTrajectoire;
        unsigned short m_distanceParcourue;
        unsigned char m_vitesse;
        unsigned char m_acceleration;

        // L'angle est entre 0 et 255 mappé entre 0 et 255/128pi
        unsigned char m_angle;
        unsigned char m_vitesseRotation;
        unsigned char m_accelerationAngulaire;
        sf::Time m_dureeDeVie;
        sf::Clock m_dureeVecue;
};

sf::Packet& operator <<(sf::Packet& packet, SortVisuel const& sortVisuel);
sf::Packet& operator >>(sf::Packet& packet, SortVisuel& sortVisuel);

#endif // SORTVISUEL_HPP
