#include <iostream>
#include "SortVisuel.hpp"

SortVisuel::SortVisuel() :
    m_textureIndex{0},
    m_degatsBase{1u},
    m_position{0.0f, 0.0f, 0.0f}
{

}

SortVisuel::SortVisuel(sf::Vector3f const& pos, unsigned short textureIndex, std::vector<sf::Texture> const& textures, unsigned short rayon, unsigned int puissance, unsigned short porteeMin, unsigned short longueurTrajectoire,unsigned char vitesse, unsigned char acceleration, unsigned char angle, unsigned char vitesseRotation, unsigned char accelerationAngulaire, sf::Time dureeDeVie) :
    m_spriteSort{},
    m_textureIndex{textureIndex},
    m_dimensions{2.0f*rayon, 2.0f*rayon},
    m_rayon{rayon},
    m_degatsBase{puissance},
    m_porteeMin{porteeMin},
    m_longueurTrajectoire{longueurTrajectoire},
    m_distanceParcourue{0.0f},
    m_vitesse{vitesse},
    m_acceleration{acceleration},
    m_angle{angle},
    m_vitesseRotation{vitesseRotation},
    m_accelerationAngulaire{accelerationAngulaire},
    m_dureeDeVie{dureeDeVie},
    m_dureeVecue{sf::Clock()}
{
    m_spriteSort.setTexture(textures[m_textureIndex]);
    m_spriteSort.setOrigin(rayon, rayon);
    m_position = pos;
}

sf::Vector2f SortVisuel::getOrigin()
{
    return sf::Vector2f(m_position.x, m_position.y); // - m_dimensions/2.0f;
}

void SortVisuel::nextStep()
{
    m_vitesseReelle += m_accelerationReelle/10.0f;
    m_vitesseRotationReelle += m_accelerationAngulaireReelle/10.0f;
    m_angleReel += m_vitesseRotationReelle;
    float theta = static_cast<float>(m_angleReel*(3.1416f/128.0f));
    m_position += static_cast<float>(m_vitesseReelle) * sf::Vector3f{std::cos(theta), -std::sin(theta), 0.0f};
    m_distanceParcourue += std::abs(m_vitesseReelle);
}

void SortVisuel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_spriteSort);
}

sf::Packet& operator <<(sf::Packet& packet, SortVisuel const& sortVisuel)
{
    return packet << sortVisuel.m_textureIndex << sortVisuel.m_rayon << sortVisuel.m_degatsBase << sortVisuel.m_porteeMin << sortVisuel.m_longueurTrajectoire << sortVisuel.m_vitesse << sortVisuel.m_acceleration << sortVisuel.m_angle << sortVisuel.m_vitesseRotation << sortVisuel.m_accelerationAngulaire << sortVisuel.m_dureeDeVie.asMilliseconds();
}

sf::Packet& operator >>(sf::Packet& packet, SortVisuel& sortVisuel)
{
    sf::Int32 dureeVie;
    packet >> sortVisuel.m_textureIndex >> sortVisuel.m_rayon >> sortVisuel.m_degatsBase >> sortVisuel.m_porteeMin >> sortVisuel.m_longueurTrajectoire >> sortVisuel.m_vitesse >> sortVisuel.m_acceleration >> sortVisuel.m_angle >> sortVisuel.m_vitesseRotation >> sortVisuel.m_accelerationAngulaire >> dureeVie;
    sortVisuel.m_dureeDeVie = sf::milliseconds(dureeVie);
    return packet;
}
