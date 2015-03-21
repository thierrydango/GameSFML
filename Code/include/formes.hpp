#ifndef FORMES_HPP
#define FORMES_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

sf::RectangleShape defineRectangle(int posX, int posY, unsigned int longueur, unsigned int largeur, int origX = 0, int origY = 0, sf::Color fillColor = sf::Color::Red, unsigned int outlineThickness = 0, sf::Color outlineColor = sf::Color::Black, int initialAngle = 0);

sf::CircleShape defineCircle(int posX, int posY, unsigned int rayon, sf::Color fillColor = sf::Color::Blue, unsigned int outlineThickness = 0, sf::Color outlineColor = sf::Color::Black);

sf::ConvexShape cooldownShape(sf::Vector2f center, unsigned int demiCoteCarre, float proportion, sf::Color fillColor);

sf::ConvexShape healthBarre(float proportion);

sf::ConvexShape regenCircle(float proportion, float radius, bool isFull);

#endif // FORMES_HPP
