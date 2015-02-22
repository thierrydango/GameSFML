#ifndef VECTOR_FUNCTIONS_HPP
#define VECTOR_FUNCTIONS_HPP

#include <cmath>
#include <SFML/System/Vector3.hpp>

template <class T>
sf::Vector3<T> makeVector(sf::Vector3<T> const& from, sf::Vector3<T> const& to)
{
    return to - from;
}

template <class T>
double dotProduct(sf::Vector3<T> const& v1, sf::Vector3<T> const& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <class T>
double norm2(sf::Vector3<T> const& vecteur)
{
    return dotProduct(vecteur, vecteur);
}

template <class T>
double norm(sf::Vector3<T> const& vecteur)
{
    return sqrt(norm2(vecteur));
}

template <class T>
void normalize(sf::Vector3<T>& vecteur)
{
    vecteur /= norm(vecteur);
}

template <class T>
sf::Vector3<T> crossProduct(sf::Vector3<T> const& v1, sf::Vector3<T> const& v2)
{
    return sf::Vector3<T>{
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

#endif // VECTOR_FUNCTIONS_HPP
