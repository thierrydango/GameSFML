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
#include "SortVisuel.hpp"

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

    // Création des menus
    sf::Sprite spriteHealthBar;
    sf::Sprite spriteXpBar;
    sf::Texture textureHealthBar;
    sf::Texture textureXpBar;

    // Initialiser les menus
    if (!textureHealthBar.loadFromFile("graphics/bars/healthBar.png"))
    {
        std::cout << "Error when loading the healthBar" << std::endl;
        return -1;
    }
    spriteHealthBar.setTexture(textureHealthBar);
    spriteHealthBar.setScale(sf::Vector2f{0.5f,0.5f});

    if (!textureXpBar.loadFromFile("graphics/bars/xpBar.png"))
    {
        std::cout << "Error when loading the xpBar" << std::endl;
        return -1;
    }
    spriteXpBar.setTexture(textureXpBar);
    spriteXpBar.setScale(sf::Vector2f{0.5f,0.5f});

    // Initialiser un vecteur de textures à charger
    unsigned int nbTexturesSorts = 2;
    std::vector<sf::Texture> texturesSorts;
    for (unsigned int i = 0; i < nbTexturesSorts; i++)
    {
        sf::Texture textureSort;
        std::string pathToSort = "graphics/sprites/Sorts/Sort" + std::to_string(i) + ".png";
        if (!textureSort.loadFromFile(pathToSort))
        {
            std::cout << "Error when loading the texture of Sort" << i << ".png" << std::endl;
            if (!textureSort.loadFromFile("graphics/sprites/Sorts/Sort0.png"))
            {
                std::cout << "Le sprite de secours n'a pas pu être chargé non plus..." << std::endl;
                return -1;
            }
        }
        texturesSorts.push_back(textureSort);
    }

    // Initialiser un vecteur de sorts à afficher
    std::vector<SortVisuel> sortsVisuels;

    sortsVisuels.push_back({sf::Vector3f{1000.0f, 600.0f, 0.0f}, 1, texturesSorts});
    sortsVisuels.push_back({sf::Vector3f{700.0f, 400.0f, 0.0f}, 1, texturesSorts});

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

    // Creation de la barre de vie
    sf::ConvexShape cooldown;
    sf::ConvexShape barreVie;
    sf::Font font;
    sf::Text ratioVie;
    sf::Text lvlText;
    sf::Text pseudoText;

    sf::Packet packet;

    if (!font.loadFromFile("graphics/font/sao.otf"))
    {
        std::cout << "Error when loading the font sao.otf" << std::endl;
    }
    ratioVie.setFont(font);
    ratioVie.setCharacterSize(24);
    ratioVie.setColor(sf::Color::White);

    lvlText.setFont(font);
    lvlText.setCharacterSize(24);
    lvlText.setColor(sf::Color::White);
    lvlText.setString("LV."+std::to_string(perso.m_level));

    pseudoText.setFont(font);
    pseudoText.setCharacterSize(24);
    pseudoText.setColor(sf::Color::White);
    pseudoText.setString("Pseudo");

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
                    other.m_state = stateOther;
                    std::cout << "Received : " << other.m_state << std::endl;
                    other.m_position.x = x;
                    other.m_position.y = y;
                    break;

            }
        }

        window.clear(sf::Color::White);

        // Gestion de la vue
        view.setCenter(perso.getOrigin());

        // Positionnement du personnage
        perso.m_spritePerso.setPosition(perso.getOrigin());
        other.m_spritePerso.setPosition(other.getOrigin());

        // Choix du bon sprite de la fiche de sprite
        perso.m_spritePerso.setTextureRect(sf::IntRect(perso.m_frameNumber*26,perso.m_animationNumber*59,26,59));
        other.m_spritePerso.setTextureRect(sf::IntRect(other.m_frameNumber*26,other.m_animationNumber*59,26,59));

        // Changer la couleur du perso
        // perso.getSpritePerso().setColor(sf::Color(255, 255, 255));
        // other.getSpritePerso().setColor(sf::Color(255, 100, 100));

        // Positionnement du menu
        spriteHealthBar.setPosition(perso.getOrigin() - sf::Vector2f{390.0f,290.0f});
        spriteXpBar.setPosition(perso.getOrigin() - sf::Vector2f{130.0f,252.0f});
        ratioVie.setPosition(perso.getOrigin() - sf::Vector2f{125.0f, 252.0f});
        lvlText.setPosition(perso.getOrigin() - sf::Vector2f{20.0f, 252.0f});
        pseudoText.setPosition(perso.getOrigin() - sf::Vector2f{359.0f, 279.0f});

        // Gestion du cooldown
        cooldown = cooldownShape(sf::Vector2f(150,150), 45, 0.625, sf::Color(0,0,255,128));

        barreVie = healthBarre(static_cast<float>(perso.m_pvActuels/perso.m_pvMax));
        ratioVie.setString(std::to_string(perso.m_pvActuels) + "/" + std::to_string(perso.m_pvMax));
        barreVie.setPosition(perso.getOrigin().x-299, perso.getOrigin().y-274);

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // Deplacement du personnage
        perso.networkOrientedNextStep();
        other.networkOrientedNextStep();

        // Deplacement des sorts
        for (unsigned int i = 0; i < sortsVisuels.size(); i++)
        {
            sortsVisuels[i].m_spriteSort.setPosition(sortsVisuels[i].getOrigin());
//            sortsVisuels[i].nextStep();
        }

        // C'est ici qu'on dessine tout
        window.draw(contour);
        window.draw(cooldown);
        window.draw(ellipse);
        window.draw(spriteHealthBar);
        window.draw(spriteXpBar);
        window.draw(barreVie);
        window.draw(ratioVie);
        window.draw(lvlText);
        window.draw(pseudoText);

        // Affichage des sorts
        for (unsigned int i = 0; i < sortsVisuels.size(); i++)
            window.draw(sortsVisuels[i]);

        window.draw(other);
        window.draw(perso);

        window.display();
    }

    return 0;
}
