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
#include "Sort.hpp"

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

    unsigned int longueurFenetre = 800;
    unsigned int largeurFenetre = 600;
    sf::RenderWindow window{sf::VideoMode{longueurFenetre, largeurFenetre}, "SFML Tutorial", sf::Style::Close};
    sf::View view;
    view.setSize(sf::Vector2f(longueurFenetre,largeurFenetre));

    // Création du personnage
    sf::Sprite spritePerso;
    sf::Texture texturePerso;
    Personnage perso("graphics/sprites/SpriteIop01.png");
    sf::Vector2u anim(0, 1);

    //Création du personnage de l'adversaire
    sf::Sprite spriteOther;
    sf::Texture textureOther;
    Personnage other("graphics/sprites/SpriteIop01.png");

    // Initialiser un vecteur de sorts à afficher
    std::vector<Sort> sorts;

    // Spécifier la position du bord haut gauche de la fenêtre
    window.setPosition(sf::Vector2i(0,0));

    // Modifier la taille de la fenêtre
    window.setSize(sf::Vector2u(longueurFenetre,largeurFenetre));

    // Limiter le nombre d'images par seconde
    window.setFramerateLimit(60);

    std::cout << "Game launching" << std::endl;

    // Creation et initialisation des éléments
    sf::RectangleShape contour;
    contour.setFillColor(sf::Color(50u,50u,50u));
    contour.setSize(sf::Vector2f(3000,2000));
    contour.setPosition(-1000,-600);

    sf::CircleShape ellipse;
    ellipse.setFillColor(sf::Color(100u,100u,100u));
    ellipse.setPointCount(100);
    ellipse.setRadius(480);
    ellipse.setScale(1.33333,1.0);
    ellipse.setPosition(0,0);
    ellipse.move(0.0,20.0);

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
            unsigned char packetType;
            packetReceived >> packetType;

            switch (packetType)
            {
                case 1:
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
                    break;

            }
        }

        window.clear(sf::Color::White);

        // Gestion de la vue
        view.setCenter(perso.getOrigin());

        // Positionnement du personnage
        perso.getSpritePerso().setPosition(perso.getOrigin());
        other.getSpritePerso().setPosition(other.getOrigin());

        // Choix du bon sprite de la fiche de sprite
        perso.getSpritePerso().setTextureRect(sf::IntRect(perso.getFrameNumber()*26,perso.getAnimationNumber()*59,26,59));
        other.getSpritePerso().setTextureRect(sf::IntRect(other.getFrameNumber()*26,other.getAnimationNumber()*59,26,59));

        // Changer la couleur du perso
        // perso.getSpritePerso().setColor(sf::Color(255, 255, 255));
        // other.getSpritePerso().setColor(sf::Color(255, 100, 100));

        // Gestion du cooldown
        cooldown = cooldownShape(sf::Vector2f(150,150), 45, 0.625, sf::Color(0,0,255,128));

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // Deplacement du personnage
        perso.networkOrientedNextStep();
        other.networkOrientedNextStep();

        // C'est ici qu'on dessine tout
        window.draw(contour);
        window.draw(cooldown);
        window.draw(ellipse);

        window.draw(perso);
        window.draw(other);

        window.display();
    }

    return 0;
}
