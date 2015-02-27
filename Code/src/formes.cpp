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

sf::ConvexShape cooldownShape(sf::Vector2f center, unsigned int demiCoteCarre, float proportion, sf::Color fillColor)
{
    sf::ConvexShape convex;
    convex.setFillColor(fillColor);
    convex.setPointCount(2);
    convex.setPoint(0, center);
    sf::Vector2f secondPoint = sf::Vector2f(center.x, center.y - demiCoteCarre);
    convex.setPoint(1, secondPoint);

    if (proportion >= 0.0f && proportion <= 0.125f)
    {
        convex.setPointCount(3);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(demiCoteCarre*8*proportion, 0.0f);
        convex.setPoint(2, thirdPoint);
    }

    else if (proportion > 0.125f && proportion <= 0.375f)
    {
        convex.setPointCount(4);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(demiCoteCarre, 0.0f);
        convex.setPoint(2, thirdPoint);
        sf::Vector2f forthPoint = thirdPoint + sf::Vector2f(0.0f, demiCoteCarre*8*(proportion - 0.125f));
        convex.setPoint(3, forthPoint);
    }

    else if (proportion > 0.375f && proportion <= 0.625f)
    {
        convex.setPointCount(5);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(demiCoteCarre, 0.0f);
        convex.setPoint(2, thirdPoint);
        sf::Vector2f forthPoint = thirdPoint + sf::Vector2f(0.0f, demiCoteCarre*2);
        convex.setPoint(3, forthPoint);
        sf::Vector2f fifthPoint = forthPoint - sf::Vector2f(demiCoteCarre*8*(proportion - 0.375f), 0.0f);
        convex.setPoint(4, fifthPoint);
    }

    else if (proportion > 0.625f && proportion <= 0.875f)
    {
        convex.setPointCount(6);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(demiCoteCarre, 0.0f);
        convex.setPoint(2, thirdPoint);
        sf::Vector2f forthPoint = thirdPoint + sf::Vector2f(0.0f, demiCoteCarre*2);
        convex.setPoint(3, forthPoint);
        sf::Vector2f fifthPoint = forthPoint - sf::Vector2f(demiCoteCarre*2, 0.0f);
        convex.setPoint(4, fifthPoint);
        sf::Vector2f sixthPoint = fifthPoint - sf::Vector2f(0.0f, demiCoteCarre*8*(proportion - 0.625f));
        convex.setPoint(5, sixthPoint);
    }

    else
    {
        convex.setPointCount(7);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(demiCoteCarre, 0.0f);
        convex.setPoint(2, thirdPoint);
        sf::Vector2f forthPoint = thirdPoint + sf::Vector2f(0.0f, demiCoteCarre*2);
        convex.setPoint(3, forthPoint);
        sf::Vector2f fifthPoint = forthPoint - sf::Vector2f(demiCoteCarre*2, 0.0f);
        convex.setPoint(4, fifthPoint);
        sf::Vector2f sixthPoint = fifthPoint - sf::Vector2f(0.0f, demiCoteCarre*2);
        convex.setPoint(5, sixthPoint);
        sf::Vector2f seventhPoint = sixthPoint + sf::Vector2f(demiCoteCarre*8*(proportion-0.875), 0.0f);
        convex.setPoint(6, seventhPoint);
    }

    return convex;
}
