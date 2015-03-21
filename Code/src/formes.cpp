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

sf::ConvexShape healthBarre(float proportion)
{
    sf::ConvexShape convex;
    convex.setFillColor(sf::Color{0,255,0,128});
    convex.setPointCount(4);
    convex.setPoint(0, sf::Vector2f{0.0f,0.0f});
    sf::Vector2f secondPoint{312.0f*proportion, 0.0f};
    convex.setPoint(1, secondPoint);

    if (proportion < 158.0f/312.0f)
    {
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(0.0f, 21.0f);
        convex.setPoint(2, thirdPoint);
        convex.setPoint(3, sf::Vector2f{0.0f, 21.0f});
    }

    else if (proportion >= 158.0f/312.0f && proportion <= 163.0f/312.0f)
    {
        convex.setPointCount(5);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(0.0f, 21.0f-9*(proportion*312-158)/5);
        convex.setPoint(2, thirdPoint);
        convex.setPoint(3, sf::Vector2f{157.0f, 21.0f});
        convex.setPoint(4, sf::Vector2f{0.0f, 21.0f});
    }

    else if (proportion > 158.0f/312.0f && proportion <= 305.0f/312.0f)
    {
        convex.setPointCount(6);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(0.0f, 12.0f);
        convex.setPoint(2, thirdPoint);
        convex.setPoint(3, sf::Vector2f{162.0f, 12.0f});
        convex.setPoint(4, sf::Vector2f{157.0f, 21.0f});
        convex.setPoint(5, sf::Vector2f{0.0f, 21.0f});
    }

    else
    {
        convex.setPointCount(7);
        sf::Vector2f thirdPoint = secondPoint + sf::Vector2f(0.0f, 12.0f-12*(proportion*312-305)/7);
        convex.setPoint(2, thirdPoint);
        convex.setPoint(3, sf::Vector2f{305.0f, 12.0f});
        convex.setPoint(4, sf::Vector2f{162.0f, 12.0f});
        convex.setPoint(5, sf::Vector2f{157.0f, 21.0f});
        convex.setPoint(6, sf::Vector2f{0.0f, 21.0f});
    }

    convex.setOutlineThickness(1);
    convex.setOutlineColor(sf::Color::Black);

    return convex;
}

sf::ConvexShape regenCircle(float proportion, float radius)
{
    sf::ConvexShape convex;
    unsigned int nbPtsOnCircle = std::round(100*proportion);
    convex.setPointCount(1+nbPtsOnCircle);
    convex.setPoint(0, sf::Vector2f{0.0f,0.0f});
    float pi = 3.1416;

    for (unsigned int i = 0; i < nbPtsOnCircle; i++)
    {
        float theta = (pi/50)*i + pi/2;
        float xCircle = radius*cos(theta);
        float yCircle = -radius*sin(theta);
        convex.setPoint(i+1, sf::Vector2f{xCircle,yCircle});
    }

    return convex;
}
