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
    std::cout << "You are a client" << std::endl;

    sf::IpAddress IPADDRESS = sf::IpAddress::getLocalAddress();
    const unsigned short PORT = 6789;
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(IPADDRESS, PORT);

    if (status != sf::Socket::Done)
    {
        std::cout << "Error in socket.connect(" << IPADDRESS << ", " << PORT << ")" << std::endl;
        return -1;
    }

    std::cout << "Connection succeeded" << std::endl;

    socket.setBlocking(false);

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

    //Création du personnage de l'adversaire
    sf::Sprite spriteOther;
    sf::Texture textureOther;
    Personnage other(spritePerso,texturePerso);

    if (!texturePerso.loadFromFile("graphics/sprites/SpriteIop01.png"))
    {
        std::cout << "Erreur au chargement de SpriteIop01.png" << std::endl;
    }

    if (!textureOther.loadFromFile("graphics/sprites/SpriteIop01.png"))
    {
        std::cout << "Erreur au chargement de SpriteIop01.png" << std::endl;
    }

    spritePerso.setTexture(texturePerso);
    spriteOther.setTexture(textureOther);

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
    sf::RectangleShape bordHorizontal;
    bordHorizontal.setFillColor(sf::Color(50u,50u,50u));
    bordHorizontal.setSize(sf::Vector2f(2000,650));
    bordHorizontal.setPosition(-800,-600);

    sf::RectangleShape bordVertical;
    bordVertical.setFillColor(sf::Color(50u,50u,50u));
    bordVertical.setSize(sf::Vector2f(850,2000));
    bordVertical.setPosition(-800,-600);

    sf::ConvexShape cooldown;
    sf::Packet packet;

    while (window.isOpen())
    {
        packet.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (perso.manageEvent(event, packet))
            {
                socket.send(packet);
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Packet packetReceived;
        if (socket.receive(packetReceived) == sf::Socket::Done)
        {
            unsigned short direction;
            short x;
            short y;
            packetReceived >> direction >> x >> y;
            std::cout << "Received : " << x << " " << y << std::endl;
            State stateOther{direction};
            other.setState(stateOther);
            std::cout << "Received : " << other.getState() << std::endl;
            other.setX(x);
            other.setY(y);
        }

        window.clear(sf::Color::White);

        // Gestion de la vue
        view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));

        // Positionnement du personnage
        spritePerso.setPosition(perso.getPosition());
        spriteOther.setPosition(other.getPosition());

        // Choix du bon sprite de la fiche de sprite
        spritePerso.setTextureRect(sf::IntRect(perso.getFrameNumber()*26,perso.getAnimationNumber()*59,26,59));
        spriteOther.setTextureRect(sf::IntRect(other.getFrameNumber()*26,other.getAnimationNumber()*59,26,59));

        // Changer la couleur du perso
        spritePerso.setColor(sf::Color(255, 255, 255));
        spriteOther.setColor(sf::Color(255, 100, 100));

        cooldown = cooldownShape(sf::Vector2f(150,150), 45, 0.625, sf::Color(0,0,255,128));

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // Deplacement du personnage
        perso.networkOrientedNextStep();
        other.networkOrientedNextStep();

        // C'est ici qu'on dessine tout
        window.draw(bordHorizontal);
        window.draw(bordVertical);
        window.draw(cooldown);

        window.draw(spritePerso);
        window.draw(spriteOther);

        window.display();
    }

    return 0;
}
