#include "formes.hpp"

sf::RectangleShape defineRectangle(int posX, int posY, unsigned int longueur, unsigned int largeur, int origX, int origY, sf::Color fillColor, unsigned int outlineThickness, sf::Color outlineColor, int initialAngle)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(longueur,largeur));
    rect.setPosition(posX, posY);
    rect.setOrigin(origX, origY);
    rect.setRotation(initialAngle);
    rect.setFillColor(fillColor);
    rect.setOutlineThickness(outlineThickness);
    rect.setOutlineColor(outlineColor);

    return rect;
}

sf::CircleShape defineCircle(int posX, int posY, unsigned int rayon, sf::Color fillColor, unsigned int outlineThickness, sf::Color outlineColor)
{
    sf::CircleShape circle;
    circle.setRadius(rayon);
    circle.setPosition(posX, posY);
    circle.setFillColor(fillColor);
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);

    return circle;
}
