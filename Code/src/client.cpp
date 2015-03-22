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

    // Création des icônes
    sf::Sprite spritePA;
    sf::Sprite spritePM;
    sf::Sprite spritePW;
    sf::Texture texturePA;
    sf::Texture texturePM;
    sf::Texture texturePW;

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

    // Initialiser les icones
    if (!texturePA.loadFromFile("graphics/icons/IconPA.png"))
    {
        std::cout << "Error when loading the IconPA" << std::endl;
        return -1;
    }
    spritePA.setTexture(texturePA);

    if (!texturePM.loadFromFile("graphics/icons/IconPM.png"))
    {
        std::cout << "Error when loading the IconPM" << std::endl;
        return -1;
    }
    spritePM.setTexture(texturePM);

    if (!texturePW.loadFromFile("graphics/icons/IconPW.png"))
    {
        std::cout << "Error when loading the IconPW" << std::endl;
        return -1;
    }
    spritePW.setTexture(texturePW);

    // Initialiser un vecteur de textures à charger
    unsigned int nbTexturesSortsVisuels = 5;
    std::vector<sf::Texture> texturesSortsVisuels;
    for (unsigned int i = 0; i < nbTexturesSortsVisuels; i++)
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
        texturesSortsVisuels.push_back(textureSort);
    }

    // Initialiser un vecteur de sorts à afficher
    std::vector<SortVisuel> sortsVisuels;

//    sortsVisuels.push_back({sf::Vector3f{1000.0f, 600.0f, 0.0f}, 1, texturesSortsVisuels, 16u, 5u, 0u, 400u, 3, 0, 0, 1, 0, sf::Time{sf::milliseconds(4000)}});
//    sortsVisuels.push_back({sf::Vector3f{500.0f, 400.0f, 0.0f}, 2, texturesSortsVisuels, 16u, 7u, 0u, 500u, 2, 1, 128, 0, 1, sf::Time{sf::milliseconds(6000)}});

    // Initialiser un vecteur de textures à charger
    unsigned int nbTexturesSortsIcons = 401;
    std::vector<sf::Texture> texturesSortsIcons;
    for (unsigned int i = 0; i < nbTexturesSortsIcons; i++)
    {
        sf::Texture textureSort;
        std::string pathToSort = "graphics/icons/IconSorts/IconSort" + std::to_string(i) + ".png";
        if (!textureSort.loadFromFile(pathToSort))
        {
            std::cout << "Error when loading the texture of Sort" << i << ".png" << std::endl;
            if (!textureSort.loadFromFile("graphics/icons/IconSorts/IconSort0.png"))
            {
                std::cout << "Le sprite de secours n'a pas pu être chargé non plus..." << std::endl;
                return -1;
            }
        }
        texturesSortsIcons.push_back(textureSort);
    }

    // Initialiser un vecteur de sorts à afficher
    std::vector<Sort> sortsIcons;

    SortVisuel sortVisuel1{sf::Vector3f{0.0f,0.0f,0.0f}, 1, texturesSortsVisuels, 16u, 5,    0u, 520, 30, 0, 0, 0, 0, sf::Time(sf::milliseconds(5000))};
    SortVisuel sortVisuel2{sf::Vector3f{0.0f,0.0f,0.0f}, 4, texturesSortsVisuels, 16u, 9,   60u, 800, 40, 2, 0, 10, 0, sf::Time(sf::milliseconds(6000))};
    SortVisuel sortVisuel3{sf::Vector3f{0.0f,0.0f,0.0f}, 2, texturesSortsVisuels, 16u, 12, 100u, 1320, 25, 1, 0, 0, 3, sf::Time(sf::milliseconds(8000))};
    SortVisuel sortVisuel4{sf::Vector3f{0.0f,0.0f,0.0f}, 3, texturesSortsVisuels, 16u, 10,   0u, 1400, 10, 2, 0, 5, 1, sf::Time(sf::milliseconds(8000))};

    sortsIcons.push_back({  7, 2, 0, 0, sf::Time{sf::milliseconds(200)},  sf::Time{sf::milliseconds(2000)}, sortVisuel1, texturesSortsIcons});
    sortsIcons.push_back({ 30, 3, 1, 0, sf::Time{sf::milliseconds(300)},  sf::Time{sf::milliseconds(5000)}, sortVisuel2, texturesSortsIcons});
    sortsIcons.push_back({  1, 4, 0, 1, sf::Time{sf::milliseconds(900)}, sf::Time{sf::milliseconds(8000)}, sortVisuel3, texturesSortsIcons});
    sortsIcons.push_back({187, 2, 1, 1, sf::Time{sf::milliseconds(500)}, sf::Time{sf::milliseconds(4000)}, sortVisuel4, texturesSortsIcons});

    // Initialiser deux vecteurs de sorts en attente de la fin de leurs temps d'incantation
    std::vector<std::pair<sf::Clock, Sort>> sortsAttentePerso;
    std::vector<std::pair<sf::Clock, Sort>> sortsAttenteOther;

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

    sf::CircleShape circlePA;
    circlePA.setFillColor(sf::Color(255,255,255,128));
    circlePA.setPointCount(100);
    circlePA.setRadius(16);
    circlePA.setOutlineThickness(1);
    circlePA.setOutlineColor(sf::Color::Black);

    sf::CircleShape circlePM;
    circlePM.setFillColor(sf::Color(255,255,255,128));
    circlePM.setPointCount(100);
    circlePM.setRadius(16);
    circlePM.setOutlineThickness(1);
    circlePM.setOutlineColor(sf::Color::Black);

    sf::CircleShape circlePW;
    circlePW.setFillColor(sf::Color(255,255,255,128));
    circlePW.setPointCount(100);
    circlePW.setRadius(16);
    circlePW.setOutlineThickness(1);
    circlePW.setOutlineColor(sf::Color::Black);

    sf::ConvexShape circleRegenPA = regenCircle(perso.m_regenPA, 16, (perso.m_PA == perso.m_PAmax));
    circleRegenPA.setFillColor(sf::Color(15,25,205,64));

    sf::ConvexShape circleRegenPM = regenCircle(perso.m_regenPM, 16, (perso.m_PM == perso.m_PMmax));
    circleRegenPM.setFillColor(sf::Color(15,205,25,64));

    sf::ConvexShape circleRegenPW = regenCircle(perso.m_regenPW, 16, (perso.m_PW == perso.m_PWmax));
    circleRegenPW.setFillColor(sf::Color(25,155,155,64));

    // Creation de la barre de vie
    std::vector<sf::ConvexShape> cooldowns;
    for (unsigned int i = 0; i < sortsIcons.size(); i++)
        cooldowns.push_back(sf::ConvexShape());
    sf::ConvexShape barreVie;
    sf::Font font;
    sf::Text ratioVie;
    sf::Text lvlText;
    sf::Text pseudoText;
    sf::Text PAText;
    sf::Text PMText;
    sf::Text PWText;

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

    PAText.setFont(font);
    PAText.setCharacterSize(18);
    PAText.setColor(sf::Color(5,45,235,248));

    PMText.setFont(font);
    PMText.setCharacterSize(18);
    PMText.setColor(sf::Color(15,145,95,248));

    PWText.setFont(font);
    PWText.setCharacterSize(18);
    PWText.setColor(sf::Color(85,225,255,248));

    while (window.isOpen())
    {
        packet.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (perso.manageEvent(event, packet, sortsIcons, sortsAttentePerso))
            {
                socket.send(packet);
                packet.clear();
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
                {
                    unsigned short direction;
                    short x;
                    short y;
                    packetReceived >> direction >> x >> y;
//                    std::cout << "Received : " << x << " " << y << std::endl;
                    State stateOther{direction};
                    other.m_state = stateOther;
//                    std::cout << "Received : " << other.m_state << std::endl;
                    other.m_position.x = x;
                    other.m_position.y = y;
                    break;
                }

                case 2:
                {
                    Sort sortLance;
                    packetReceived >> sortLance;
//                    std::cout << "Received temps Incantation :" << sortLance.m_tempsIncantation.asMilliseconds() << std::endl;
//                    std::cout << "Received texture index :" << sortLance.m_sortVisuel.m_textureIndex << std::endl;
//                    std::cout << "Received rayon :" << sortLance.m_sortVisuel.m_rayon << std::endl;
//                    std::cout << "Received degats :" << sortLance.m_sortVisuel.m_degatsBase << std::endl;
//                    std::cout << "Received porteeMin :" << sortLance.m_sortVisuel.m_porteeMin << std::endl;
//                    std::cout << "Received longueurTrajectoire :" << sortLance.m_sortVisuel.m_longueurTrajectoire << std::endl;
//                    std::cout << "Received vitesse :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesse) << std::endl;
//                    std::cout << "Received acceleration :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_acceleration) << std::endl;
//                    std::cout << "Received angle :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_angle) << std::endl;
//                    std::cout << "Received vitesse rotation :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesseRotation) << std::endl;
//                    std::cout << "Received acceleration angulaire :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_accelerationAngulaire) << std::endl;
//                    std::cout << "Received duree de Vie :" << sortLance.m_sortVisuel.m_dureeDeVie.asMilliseconds() << std::endl;
                    sortLance.m_sortVisuel.m_spriteSort.setTexture(texturesSortsVisuels[sortLance.m_sortVisuel.m_textureIndex]);
                    sortsAttenteOther.push_back(std::make_pair(sf::Clock(),sortLance));
                    break;
                }

                case 3:
                {
                    unsigned short degatsRecus;
                    packetReceived >> degatsRecus;
                    if (degatsRecus < perso.m_pvActuels)
                        perso.m_pvActuels -= degatsRecus;
                    else
                        perso.m_pvActuels = 0;
                }
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

        // Positionnement des cercles de PA, PM, PW et de régénération
        circlePA.setPosition(perso.getOrigin() - sf::Vector2f{334.0f,248.0f});
        circleRegenPA = regenCircle(perso.m_regenPA, 16, (perso.m_PA == perso.m_PAmax));
        circleRegenPA.setPosition(perso.getOrigin() - sf::Vector2f{318.0f,232.0f});
        circleRegenPA.setFillColor(sf::Color(15,25,205,128));
        circlePM.setPosition(perso.getOrigin() - sf::Vector2f{264.0f,248.0f});
        circleRegenPM = regenCircle(perso.m_regenPM, 16, (perso.m_PM == perso.m_PMmax));
        circleRegenPM.setPosition(perso.getOrigin() - sf::Vector2f{248.0f,232.0f});
        circleRegenPM.setFillColor(sf::Color(15,205,25,128));
        circlePW.setPosition(perso.getOrigin() - sf::Vector2f{194.0f,248.0f});
        circleRegenPW = regenCircle(perso.m_regenPW, 16, (perso.m_PW == perso.m_PWmax));
        circleRegenPW.setFillColor(sf::Color(25,155,155,128));
        circleRegenPW.setPosition(perso.getOrigin() - sf::Vector2f{178.0f,232.0f});

        // PA, PM, PW
        PAText.setString(std::to_string(perso.m_PA));
        PAText.setPosition(perso.getOrigin() - sf::Vector2f{330.0f,243.0f});
        PMText.setString(std::to_string(perso.m_PM));
        PMText.setPosition(perso.getOrigin() - sf::Vector2f{260.0f,243.0f});
        PWText.setString(std::to_string(perso.m_PW));
        PWText.setPosition(perso.getOrigin() - sf::Vector2f{190.0f,243.0f});

        // Positionnement des icônes
        spritePA.setPosition(perso.getOrigin() - sf::Vector2f{320.0f,240.0f});
        spritePM.setPosition(perso.getOrigin() - sf::Vector2f{250.0f,240.0f});
        spritePW.setPosition(perso.getOrigin() - sf::Vector2f{180.0f,240.0f});

        // Gestion des cooldowns
        for (unsigned int i = 0; i < sortsIcons.size(); i++)
        {
            float prop = static_cast<float>(sortsIcons[i].m_elapsedTime.getElapsedTime().asMilliseconds())/static_cast<float>(sortsIcons[i].m_cooldown.asMilliseconds());
            cooldowns[i] = cooldownShape(perso.getOrigin() - sf::Vector2f(376.0f,216.0f-32.0f*i), 16, std::min(prop,1.0f), sf::Color(0,0,255,128));
        }

        // Gestion des barres de vie
        barreVie = healthBarre((static_cast<float>(perso.m_pvActuels)+perso.m_regenPV)/static_cast<float>(perso.m_pvMax));
        ratioVie.setString(std::to_string(perso.m_pvActuels) + "/" + std::to_string(perso.m_pvMax));
        barreVie.setPosition(perso.getOrigin().x-299, perso.getOrigin().y-274);

        // Gestion des sorts en attente
        unsigned int j = 0;
        while (j < sortsAttentePerso.size())
        {

            if (sortsAttentePerso[j].first.getElapsedTime() >= sortsAttentePerso[j].second.m_tempsIncantation)
            {
                SortVisuel sortAffiche = sortsAttentePerso[j].second.m_sortVisuel;
                if (sortAffiche.m_vitesse < 128)
                    sortAffiche.m_vitesseReelle = static_cast<float>(sortAffiche.m_vitesse)/10.0f;
                else
                    sortAffiche.m_vitesseReelle = -static_cast<float>(sortAffiche.m_vitesse)/10.0f+12.8f;
                if (sortAffiche.m_acceleration < 128)
                    sortAffiche.m_accelerationReelle = static_cast<float>(sortAffiche.m_acceleration)/10.0f;
                else
                    sortAffiche.m_accelerationReelle = -static_cast<float>(sortAffiche.m_acceleration)/10.0f+12.8f;
                if (sortAffiche.m_vitesseRotation < 128)
                    sortAffiche.m_vitesseRotationReelle = static_cast<float>(sortAffiche.m_vitesseRotation)/10.0f;
                else
                    sortAffiche.m_vitesseRotationReelle = -static_cast<float>(sortAffiche.m_vitesseRotation)/10.0f+12.8f;
                if (sortAffiche.m_accelerationAngulaire < 128)
                    sortAffiche.m_accelerationAngulaireReelle = static_cast<float>(sortAffiche.m_accelerationAngulaire)/10.0f;
                else
                    sortAffiche.m_accelerationAngulaireReelle = -static_cast<float>(sortAffiche.m_accelerationAngulaire)/10.0f+12.8f;
                float theta = perso.m_direction*(3.1416f/16.0f) + static_cast<float>(sortAffiche.m_angle)*(3.1416f/128.0f);
                sortAffiche.m_angleReel = theta*(128.0f/3.1416);
                unsigned short porteeMinim = sortAffiche.m_porteeMin;
                sortAffiche.m_position = perso.m_position + static_cast<float>(porteeMinim)*sf::Vector3f{std::cos(theta),-std::sin(theta), 0.0f};
                sortAffiche.m_dureeVecue.restart();
                sortsVisuels.push_back(sortAffiche);
                sortsAttentePerso.erase(sortsAttentePerso.begin()+j);
            }
            else
                j++;
        }

        j = 0;
        while (j < sortsAttenteOther.size())
        {

            if (sortsAttenteOther[j].first.getElapsedTime() >= sortsAttenteOther[j].second.m_tempsIncantation)
            {
                SortVisuel sortAffiche = sortsAttenteOther[j].second.m_sortVisuel;
                sortAffiche.m_spriteSort.setOrigin(sortAffiche.m_rayon, sortAffiche.m_rayon);
                if (sortAffiche.m_vitesse < 128)
                    sortAffiche.m_vitesseReelle = static_cast<float>(sortAffiche.m_vitesse)/10.0f;
                else
                    sortAffiche.m_vitesseReelle = -static_cast<float>(sortAffiche.m_vitesse)/10.0f+12.8f;
                if (sortAffiche.m_acceleration < 128)
                    sortAffiche.m_accelerationReelle = static_cast<float>(sortAffiche.m_acceleration)/10.0f;
                else
                    sortAffiche.m_accelerationReelle = -static_cast<float>(sortAffiche.m_acceleration)/10.0f+12.8f;
                if (sortAffiche.m_vitesseRotation < 128)
                    sortAffiche.m_vitesseRotationReelle = static_cast<float>(sortAffiche.m_vitesseRotation)/10.0f;
                else
                    sortAffiche.m_vitesseRotationReelle = -static_cast<float>(sortAffiche.m_vitesseRotation)/10.0f+12.8f;
                if (sortAffiche.m_accelerationAngulaire < 128)
                    sortAffiche.m_accelerationAngulaireReelle = static_cast<float>(sortAffiche.m_accelerationAngulaire)/10.0f;
                else
                    sortAffiche.m_accelerationAngulaireReelle = -static_cast<float>(sortAffiche.m_accelerationAngulaire)/10.0f+12.8f;
                float theta = other.m_direction*(3.1416f/16.0f) + static_cast<float>(sortAffiche.m_angle)*(3.1416f/128.0f);
                sortAffiche.m_angleReel = theta*(128.0f/3.1416);
                unsigned short porteeMinim = sortAffiche.m_porteeMin;
                sortAffiche.m_position = other.m_position + static_cast<float>(porteeMinim)*sf::Vector3f{std::cos(theta),-std::sin(theta), 0.0f};
                sortAffiche.m_dureeVecue.restart();
                sortsVisuels.push_back(sortAffiche);
                sortsAttenteOther.erase(sortsAttenteOther.begin()+j);
            }
            else
                j++;
        }

        //view.setCenter(sf::Vector2f(perso.getX(),perso.getY()));
        window.setView(view);

        // Régénération du personnage
        perso.regenStep();

        // Retrait des sorts ayant fait leur temps ou dépassé leur distance à parcourir
        j = 0;
        while (j < sortsVisuels.size())
        {

            if (sortsVisuels[j].m_dureeVecue.getElapsedTime() >= sortsVisuels[j].m_dureeDeVie || sortsVisuels[j].m_distanceParcourue >= sortsVisuels[j].m_longueurTrajectoire)
                sortsVisuels.erase(sortsVisuels.begin()+j);
            else
                j++;
        }

        // Deplacement des sorts
        for (unsigned int i = 0; i < sortsVisuels.size(); i++)
        {
            sortsVisuels[i].m_spriteSort.setPosition(sortsVisuels[i].getOrigin());
            sortsVisuels[i].nextStep();
            sortsVisuels[i].m_spriteSort.setRotation(-static_cast<float>(sortsVisuels[i].m_angleReel)*(360.0f/256.0f));
        }

        for (unsigned int i = 0; i < sortsIcons.size(); i++)
        {
            sortsIcons[i].m_spriteSort.setPosition(perso.getOrigin() - sf::Vector2f{392.0f,232.0f-32.0f*i});
        }

        // Deplacement du personnage
        perso.networkOrientedNextStep();
        other.networkOrientedNextStep();

        // C'est ici qu'on dessine tout
        window.draw(contour);
        window.draw(ellipse);
        window.draw(spriteHealthBar);
        window.draw(spriteXpBar);
        window.draw(barreVie);
        window.draw(ratioVie);
        window.draw(lvlText);
        window.draw(circlePA);
        window.draw(circleRegenPA);
        window.draw(PAText);
        window.draw(circlePM);
        window.draw(circleRegenPM);
        window.draw(PMText);
        window.draw(circlePW);
        window.draw(circleRegenPW);
        window.draw(PWText);
        window.draw(spritePA);
        window.draw(spritePM);
        window.draw(spritePW);
        window.draw(pseudoText);

        // Affichage des sorts
        for (unsigned int i = 0; i < sortsVisuels.size(); i++)
            window.draw(sortsVisuels[i]);

        for (unsigned int i = 0; i < sortsIcons.size(); i++)
            window.draw(sortsIcons[i]);

        for (unsigned int i = 0; i < cooldowns.size(); i++)
            window.draw(cooldowns[i]);

        window.draw(other);
        window.draw(perso);

        window.display();
    }

    return 0;
}
