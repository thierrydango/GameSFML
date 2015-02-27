#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <csignal>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Personnage.hpp"
#include "formes.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {

    // Lecture de l'éventuel paramètre pour être serveur
    if (argc > 2)
    {
        std::cout << "To be the server, good use is : ./main s" << std::endl;
        return -1;
    }

    bool isServer = false;
    if (argc == 2)
    {
        if (*argv[1] == 's')
        {
            isServer = true;
        }
    }

    if (isServer)
    {
        std::cout << "You are the server" << std::endl;
    }
    else
    {
        std::cout << "You are a client" << std::endl;
    }

    sf::IpAddress IPADDRESS = sf::IpAddress::getLocalAddress();
    const unsigned short PORT = 5000;
    sf::TcpSocket socket;
    sf::Mutex globalMutex;

    if (isServer)
    {
        sf::TcpListener listener;
        std::cout << "Waiting for a client..." << std::endl;
        listener.listen(PORT);
        if (listener.accept(socket) == sf::Socket::Done)
        {
            std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
        }
        else
        {
            std::cout << "Port already in use, please wait and retry" << std::endl;
            return 0;
        }
    }

    if (!isServer)
    {
        if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
        {
            std::cout << "Connexion successed" << std::endl;
        }
        else
        {
            std::cout << "Erreur de connection au serveur" << std::endl;
            return -1;
        }
    }
    }

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
    window.create(sf::VideoMode(longueurFenetre ,largeurFenetre), "SFML Tutorial");

    // Spécifier la position du bord haut gauche de la fenêtre
    window.setPosition(sf::Vector2i(0,0));

    // Modifier la taille de la fenêtre
    window.setSize(sf::Vector2u(longueurFenetre,largeurFenetre));

    // Limiter le nombre d'images par seconde
    window.setFramerateLimit(60);

    std::cout << "Game launching" << std::endl;

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

    sf::ConvexShape cooldown;

    float angle = 0.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            perso.manageEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        // Gestion de la vue
        view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));

        //std::cout << "Position du perso : " << perso.getX() << "," << perso.getY() << std::endl;

        spritePerso.setPosition(perso.getPosition());
        spritePerso.setTextureRect(sf::IntRect(perso.getFrameNumber()*26,perso.getAnimationNumber()*59,26,59));

        // Changer la couleur du perso
        spritePerso.setColor(sf::Color(255, 255, 255));

        angle = (angle+0.01);
        if (angle >= 1)
            angle = 0;
        rect.setRotation(angle*360);

        std::cout << angle << std::endl;
        cooldown = cooldownShape(sf::Vector2f(150,150), 45, angle, sf::Color(0,0,255,128));
        convex.move(1u,0u);

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // Deplacement du personnage
        perso.networkOrientedNextStep();

        // C'est ici qu'on dessine tout
        window.draw(circle);
        window.draw(rect);
        window.draw(bordHorizontal);
        window.draw(bordVertical);
        window.draw(convex);
        window.draw(cooldown);


        window.draw(spritePerso);

        window.display();
    }

    return 0;
}
