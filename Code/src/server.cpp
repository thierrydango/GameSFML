#include <iostream>
#include <thread>
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
    std::cout << "You are the server !" << std::endl;

    std::vector<SortVisuel> sortsVisuelsPerso;
    std::vector<SortVisuel> sortsVisuelsOther;

    std::vector<std::pair<sf::Clock, Sort>> sortsAttentePerso;
    std::vector<std::pair<sf::Clock, Sort>> sortsAttenteOther;

//    unsigned int nbMaxPlayers = 2;
//    unsigned int nbPlayers = 0;
//    sf::IpAddress IPADDRESS = sf::IpAddress::getLocalAddress();
    const unsigned short PORT = 6789;
    sf::TcpSocket socketPlayer1;
    sf::TcpSocket socketPlayer2;
    sf::Mutex globalMutex;
    sf::TcpListener listener;

    std::cout << "Waiting for player 1..." << std::endl;
    listener.listen(PORT);

    if (listener.accept(socketPlayer1) == sf::Socket::Done)
    {
        std::cout << "Player 1 connected: " << socketPlayer1.getRemoteAddress() << std::endl;
    }
    else
    {
        return -1;
    }

    std::cout << "Waiting for player 2..." << std::endl;

    if (listener.accept(socketPlayer2) == sf::Socket::Done)
    {
        std::cout << "Player 2 connected: " << socketPlayer2.getRemoteAddress() << std::endl;
    }
    else
    {
        return -1;
    }

    socketPlayer1.setBlocking(false);
    socketPlayer2.setBlocking(false);

    Personnage joueur1;
    Personnage joueur2;

    sf::SocketSelector selector;
    selector.add(socketPlayer1);
    selector.add(socketPlayer2);

    std::cout << "Both players are connected, the game starts now!" << std::endl;

    while (true)
    {
        if (selector.wait(sf::seconds(60)))
        {
            sf::Packet packet;
            if (selector.isReady(socketPlayer1))
            {
                socketPlayer1.receive(packet);
                socketPlayer2.send(packet);
                unsigned char packetType;
                packet >> packetType;

                switch (packetType)
                {
                    case 1:
                    {
                        unsigned short newState;
                        short x;
                        short y;
                        packet >> newState >> x >> y;
//                        std::cout << "Received " << newState << " " << x << " " << y << " from Player 1" << std::endl;
                        joueur1.m_position.x = x;
                        joueur1.m_position.y = y;
                        break;
                    }

                    case 2:
                    {
                        Sort sortLance;
                        packet >> sortLance;
//                        std::cout << "Received temps Incantation :" << sortLance.m_tempsIncantation.asMilliseconds() << std::endl;
//                        std::cout << "Received texture index :" << sortLance.m_sortVisuel.m_textureIndex << std::endl;
//                        std::cout << "Received rayon :" << sortLance.m_sortVisuel.m_rayon << std::endl;
//                        std::cout << "Received degats :" << sortLance.m_sortVisuel.m_degatsBase << std::endl;
//                        std::cout << "Received porteeMin :" << sortLance.m_sortVisuel.m_porteeMin << std::endl;
//                        std::cout << "Received longueurTrajectoire :" << sortLance.m_sortVisuel.m_longueurTrajectoire << std::endl;
//                        std::cout << "Received vitesse :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesse) << std::endl;
//                        std::cout << "Received acceleration :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_acceleration) << std::endl;
//                        std::cout << "Received angle :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_angle) << std::endl;
//                        std::cout << "Received vitesse rotation :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesseRotation) << std::endl;
//                        std::cout << "Received acceleration angulaire :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_accelerationAngulaire) << std::endl;
//                        std::cout << "Received duree de Vie :" << sortLance.m_sortVisuel.m_dureeDeVie.asMilliseconds() << std::endl;
                        sortsAttentePerso.push_back(std::make_pair(sf::Clock(),sortLance));
                        break;
                    }
                }
            }
            if (selector.isReady(socketPlayer2))
            {
                socketPlayer2.receive(packet);
                socketPlayer1.send(packet);
                unsigned char packetType;
                packet >> packetType;

                switch (packetType)
                {
                    case 1:
                    {
                        unsigned short newState;
                        short x;
                        short y;
                        packet >> newState >> x >> y;
                        std::cout << "Received " << newState << " " << x << " " << y << " from Player 2" << std::endl;
                        joueur2.m_position.x = x;
                        joueur2.m_position.y = y;
                        break;
                    }

                    case 2:
                    {
                        Sort sortLance;
                        packet >> sortLance;
//                        std::cout << "Received temps Incantation :" << sortLance.m_tempsIncantation.asMilliseconds() << std::endl;
//                        std::cout << "Received texture index :" << sortLance.m_sortVisuel.m_textureIndex << std::endl;
//                        std::cout << "Received rayon :" << sortLance.m_sortVisuel.m_rayon << std::endl;
//                        std::cout << "Received degats :" << sortLance.m_sortVisuel.m_degatsBase << std::endl;
//                        std::cout << "Received porteeMin :" << sortLance.m_sortVisuel.m_porteeMin << std::endl;
//                        std::cout << "Received longueurTrajectoire :" << sortLance.m_sortVisuel.m_longueurTrajectoire << std::endl;
//                        std::cout << "Received vitesse :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesse) << std::endl;
//                        std::cout << "Received acceleration :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_acceleration) << std::endl;
//                        std::cout << "Received angle :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_angle) << std::endl;
//                        std::cout << "Received vitesse rotation :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesseRotation) << std::endl;
//                        std::cout << "Received acceleration angulaire :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_accelerationAngulaire) << std::endl;
//                        std::cout << "Received duree de Vie :" << sortLance.m_sortVisuel.m_dureeDeVie.asMilliseconds() << std::endl;
                        sortsAttenteOther.push_back(std::make_pair(sf::Clock(),sortLance));
                        break;
                    }

                }
            }

            std::cout << "Passage apres le if else" << std::endl;

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
                    float theta = joueur1.m_direction*(3.1416f/16.0f) + static_cast<float>(sortAffiche.m_angle)*(3.1416f/128.0f);
                    sortAffiche.m_angleReel = theta*(128.0f/3.1416);
                    unsigned short porteeMinim = sortAffiche.m_porteeMin;
                    sortAffiche.m_position = joueur1.m_position + static_cast<float>(porteeMinim)*sf::Vector3f{std::cos(theta),-std::sin(theta), 0.0f};
                    sortAffiche.m_dureeVecue.restart();
                    sortsVisuelsPerso.push_back(sortAffiche);
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
                    //sortAffiche.m_spriteSort.setTexture(texturesSortsVisuels[1]);
                    sortAffiche.m_vitesseReelle = static_cast<float>(sortAffiche.m_vitesse)/10.0f;
                    sortAffiche.m_accelerationReelle = static_cast<float>(sortAffiche.m_acceleration)/10.0f;
                    sortAffiche.m_vitesseRotationReelle = static_cast<float>(sortAffiche.m_vitesseRotation)/10.0f;
                    sortAffiche.m_accelerationAngulaireReelle = static_cast<float>(sortAffiche.m_accelerationAngulaire)/10.0f;
                    float theta = joueur2.m_direction*(3.1416f/16.0f) + static_cast<float>(sortAffiche.m_angle)*(3.1416f/128.0f);
                    sortAffiche.m_angleReel = theta*(128.0f/3.1416);
                    unsigned short porteeMinim = sortAffiche.m_porteeMin;
                    sortAffiche.m_position = joueur2.m_position + static_cast<float>(porteeMinim)*sf::Vector3f{std::cos(theta),-std::sin(theta), 0.0f};
                    sortAffiche.m_dureeVecue.restart();
                    sortsVisuelsOther.push_back(sortAffiche);
                    sortsAttenteOther.erase(sortsAttenteOther.begin()+j);
                }
                else
                    j++;
            }

            // Gestion des collisions entre sorts et joueurs
            for (unsigned int i = 0; i < sortsVisuelsPerso.size(); i++)
            {
                SortVisuel sortVisu = sortsVisuelsPerso[i];
                std::cout << (std::sqrt((sortVisu.m_position.x-joueur2.m_position.x)*(sortVisu.m_position.x-joueur2.m_position.x)+(sortVisu.m_position.y-joueur2.m_position.y)*(sortVisu.m_position.y-joueur2.m_position.y)) < sortVisu.m_rayon) << std::endl;
                if (std::sqrt((sortVisu.m_position.x-joueur2.m_position.x)*(sortVisu.m_position.x-joueur2.m_position.x)+(sortVisu.m_position.y-joueur2.m_position.y)*(sortVisu.m_position.y-joueur2.m_position.y)) < sortVisu.m_rayon)
                {
                    std::cout << "TOUCHE" << std::endl;
                    sortsVisuelsPerso[i].m_distanceParcourue = sortsVisuelsPerso[i].m_longueurTrajectoire;
                    sf::Packet packetDegatsInfliges;
                    unsigned char packetType = 3;
                    unsigned short degatsInfliges = static_cast<float>(sortsVisuelsPerso[i].m_degatsBase) * (1.0f + static_cast<float>(joueur1.m_puissance)/100.0f);
                    packetDegatsInfliges << packetType << degatsInfliges;
                    socketPlayer2.send(packetDegatsInfliges);
                }
            }

            for (unsigned int i = 0; i < sortsVisuelsOther.size(); i++)
            {
                SortVisuel sortVisu = sortsVisuelsOther[i];
                std::cout << (std::sqrt((sortVisu.m_position.x-joueur1.m_position.x)*(sortVisu.m_position.x-joueur1.m_position.x)+(sortVisu.m_position.y-joueur1.m_position.y)*(sortVisu.m_position.y-joueur1.m_position.y)) < sortVisu.m_rayon) << std::endl;
                if (std::sqrt((sortVisu.m_position.x-joueur1.m_position.x)*(sortVisu.m_position.x-joueur1.m_position.x)+(sortVisu.m_position.y-joueur1.m_position.y)*(sortVisu.m_position.y-joueur1.m_position.y)) < sortVisu.m_rayon)
                {
                    std::cout << "TOUCHE" << std::endl;
                    sortsVisuelsOther[i].m_distanceParcourue = sortsVisuelsOther[i].m_longueurTrajectoire;
                    sf::Packet packetDegatsInfliges;
                    unsigned char packetType = 3;
                    unsigned short degatsInfliges = static_cast<float>(sortsVisuelsOther[i].m_degatsBase) * (1.0f + static_cast<float>(joueur2.m_puissance)/100.0f);
                    packetDegatsInfliges << packetType << degatsInfliges;
                    socketPlayer1.send(packetDegatsInfliges);
                }
            }

            // Retrait des sorts ayant fait leur temps ou dépassé leur distance à parcourir
            j = 0;
            while (j < sortsVisuelsPerso.size())
            {
                if (sortsVisuelsPerso[j].m_dureeVecue.getElapsedTime() >= sortsVisuelsPerso[j].m_dureeDeVie || sortsVisuelsPerso[j].m_distanceParcourue >= sortsVisuelsPerso[j].m_longueurTrajectoire)
                    sortsVisuelsPerso.erase(sortsVisuelsPerso.begin()+j);
                else
                    j++;
            }

            j = 0;
            while (j < sortsVisuelsOther.size())
            {
                if (sortsVisuelsOther[j].m_dureeVecue.getElapsedTime() >= sortsVisuelsOther[j].m_dureeDeVie || sortsVisuelsOther[j].m_distanceParcourue >= sortsVisuelsOther[j].m_longueurTrajectoire)
                    sortsVisuelsOther.erase(sortsVisuelsOther.begin()+j);
                else
                    j++;
            }

            // Déplacement des sorts
            for (unsigned int i = 0; i < sortsVisuelsPerso.size(); i++)
                sortsVisuelsPerso[i].nextStep();

            for (unsigned int i = 0; i < sortsVisuelsOther.size(); i++)
                sortsVisuelsOther[i].nextStep();
        }
        else
        {
            std::cout << "No reception during the last 60 seconds..." << std::endl;
        }

    }

}
