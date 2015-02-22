#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Personnage.hpp"

int main()
{
    sf::RenderWindow window;
    sf::View view;
    unsigned int longueurFenetre = 800;
    unsigned int largeurFenetre = 600;
    view.setSize(sf::Vector2f(longueurFenetre,largeurFenetre));

    // Création du personnage
    sf::Sprite spritePerso;
    sf::Texture texturePerso;
    Personnage perso(spritePerso,texturePerso);
    sf::Vector2u anim(0, 1);

    if (!texturePerso.loadFromFile("../graphics/sprites/SpriteIop01.png"))
    {
        std::cout << "Erreur au chargement de SpriteIop01.png" << std::endl;
    }

    spritePerso.setTexture(texturePerso);

    // Créer une fenêtre en lui donnant une taille et un nom
    window.create(sf::VideoMode(longueurFenetre ,largeurFenetre), "Tutoriel SFML");

    // Spécifier la position du bord haut gauche de la fenêtre
    window.setPosition(sf::Vector2i(0,0));

    // Modifier la taille de la fenêtre
    window.setSize(sf::Vector2u(longueurFenetre,largeurFenetre));

    // Limiter le nombre d'images par seconde
    window.setFramerateLimit(60);

    std::cout << "Lancement du jeu" << std::endl;

    // Creation et initialisation des éléments
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(100u,200u,50u));
    circle.setRadius(50.0f);
    circle.setPosition(300,300);
    circle.setOutlineColor(sf::Color(0u,0u,0u));
    circle.setOutlineThickness(7u);

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(255u,20u,40u));
    rect.setSize(sf::Vector2f(200,60));
    rect.setPosition(350,350);
    rect.setRotation(0);
    rect.setOutlineColor(sf::Color(0u,0u,0u));
    rect.setOutlineThickness(7u);
    rect.setOrigin(-48,30);

    sf::RectangleShape bordHorizontal;
    bordHorizontal.setFillColor(sf::Color(50u,50u,50u));
    bordHorizontal.setSize(sf::Vector2f(2000,650));
    bordHorizontal.setPosition(-800,-600);

    sf::RectangleShape bordVertical;
    bordVertical.setFillColor(sf::Color(50u,50u,50u));
    bordVertical.setSize(sf::Vector2f(850,2000));
    bordVertical.setPosition(-800,-600);

    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, sf::Vector2f(300,300));
    convex.setPoint(1, sf::Vector2f(450,320));
    convex.setPoint(2, sf::Vector2f(420,390));
    convex.setPoint(3, sf::Vector2f(350,440));
    convex.setPoint(4, sf::Vector2f(280,420));
    convex.setFillColor(sf::Color::Cyan);
    convex.setOutlineColor(sf::Color(0u,0u,0u));
    convex.setOutlineThickness(7u);

    unsigned int angle = 0u;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        // Deplacement du personnage
        perso.networkOrientedNextStep();

        // Gestion de la vue
        view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));

        //std::cout << "Position du perso : " << perso.getX() << "," << perso.getY() << std::endl;

        spritePerso.setPosition(perso.getPosition());
        spritePerso.setTextureRect(sf::IntRect(perso.getFrameNumber()*26,perso.getAnimationNumber()*59,26,59));

        angle = (angle+1)%360;
        rect.setRotation(angle);

        convex.move(1u,0u);

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // C'est ici qu'on dessine tout
        window.draw(circle);
        window.draw(rect);
        window.draw(bordHorizontal);
        window.draw(bordVertical);
        window.draw(convex);


        window.draw(spritePerso);

        window.display();
    }

    return 0;
}
