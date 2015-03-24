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

    sf::Packet packetJ1;
    unsigned char designerJ1 = 7;
    packetJ1 << designerJ1;
    socketPlayer1.send(packetJ1);

    sf::Packet packetJ2;
    unsigned char designerJ2 = 8;
    packetJ2 << designerJ2;
    socketPlayer2.send(packetJ2);

    Personnage joueur1;
    Personnage joueur2;

    joueur1.m_position.x = 200.0f;
    joueur1.m_position.y = 480.0f;
    joueur2.m_position.x = 1080.0f;
    joueur2.m_position.y = 480.0f;

    sf::SocketSelector selector;
    selector.add(socketPlayer1);
    selector.add(socketPlayer2);

    sf::Clock cadence60;
    unsigned int numTour = 1;

    std::cout << "Both players are connected, the game starts now!" << std::endl;

    while (true)
    {
        sf::Packet packet1;
        if (socketPlayer1.receive(packet1) == sf::Socket::Done)
        {
            socketPlayer2.send(packet1);
            unsigned char packetType;
            packet1 >> packetType;

            switch (packetType)
            {
                case 1:
                {
                    unsigned short newState;
                    short x;
                    short y;
                    packet1 >> newState >> x >> y;
                    joueur1.m_position.x = x;
                    joueur1.m_position.y = y;
                    State stateJoueur1{newState};
                    joueur1.m_state = stateJoueur1;
                    break;
                }

                case 2:
                {
                    Sort sortLance;
                    packet1 >> sortLance;
                    sortsAttentePerso.push_back(std::make_pair(sf::Clock(),sortLance));
                    break;
                }
            }
        }
        sf::Packet packet2;
        if (socketPlayer2.receive(packet2) == sf::Socket::Done)
        {
            socketPlayer1.send(packet2);
            unsigned char packetType;
            packet2 >> packetType;

            switch (packetType)
            {
                case 1:
                {
                    unsigned short newState;
                    short x;
                    short y;
                    packet2 >> newState >> x >> y;
                    joueur2.m_position.x = x;
                    joueur2.m_position.y = y;
                    State stateJoueur2{newState};
                    joueur2.m_state = stateJoueur2;
                    break;
                }

                case 2:
                {
                    Sort sortLance;
                    packet2 >> sortLance;
                    sortsAttenteOther.push_back(std::make_pair(sf::Clock(),sortLance));
                    break;
                }

            }
        }

        // Instructions à effectuer 60 fois par seconde
        while (cadence60.getElapsedTime() > sf::microseconds(16667*numTour))
        {

            numTour++;

            joueur1.regenStep();
            joueur2.regenStep();

            joueur1.networkOrientedNextStep();
            joueur2.networkOrientedNextStep();

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
                if (std::sqrt((sortVisu.m_position.x-joueur2.m_position.x)*(sortVisu.m_position.x-joueur2.m_position.x)+(sortVisu.m_position.y-joueur2.m_position.y)*(sortVisu.m_position.y-joueur2.m_position.y)) < sortVisu.m_rayon+joueur2.m_rayon)
                {
                    std::cout << "TOUCHE" << std::endl;
                    sortsVisuelsPerso[i].m_distanceParcourue = sortsVisuelsPerso[i].m_longueurTrajectoire;
                    unsigned short degatsInfliges = static_cast<unsigned short>(std::round(static_cast<float>(sortsVisuelsPerso[i].m_degatsBase) * (1.0f + static_cast<float>(joueur1.m_puissance)/100.0f) - static_cast<float>(joueur2.m_resistance)/100.0f));
                    if (degatsInfliges < joueur2.m_pvActuels)
                    {
                        joueur2.m_pvActuels -= degatsInfliges;
                        sf::Packet packetDegatsInfliges;
                        sf::Packet packetDegatsInfligesOther;
                        unsigned char packetType = 3;
                        unsigned char packetTypeOther = 4;
                        packetDegatsInfliges << packetType << degatsInfliges;
                        packetDegatsInfligesOther << packetTypeOther << degatsInfliges;
                        socketPlayer2.send(packetDegatsInfliges);
                        socketPlayer1.send(packetDegatsInfligesOther);
                    }
                    else
                    {
                        joueur2.m_pvActuels = 0;
                        sf::Packet packetVictoire;
                        sf::Packet packetDefaite;
                        unsigned char packetType = 5;
                        unsigned char packetTypeOther = 6;
                        packetVictoire << packetType << degatsInfliges;
                        packetDefaite << packetTypeOther << degatsInfliges;
                        socketPlayer1.send(packetVictoire);
                        socketPlayer2.send(packetDefaite);
                    }
                }
            }

            for (unsigned int i = 0; i < sortsVisuelsOther.size(); i++)
            {
                SortVisuel sortVisu = sortsVisuelsOther[i];
                if (std::sqrt((sortVisu.m_position.x-joueur1.m_position.x)*(sortVisu.m_position.x-joueur1.m_position.x)+(sortVisu.m_position.y-joueur1.m_position.y)*(sortVisu.m_position.y-joueur1.m_position.y)) < sortVisu.m_rayon+joueur1.m_rayon)
                {
                    std::cout << "TOUCHE" << std::endl;
                    sortsVisuelsOther[i].m_distanceParcourue = sortsVisuelsOther[i].m_longueurTrajectoire;
                    unsigned short degatsInfliges = static_cast<unsigned short>(std::round(static_cast<float>(sortsVisuelsOther[i].m_degatsBase) * (1.0f + static_cast<float>(joueur2.m_puissance)/100.0f) - static_cast<float>(joueur1.m_resistance)/100.0f));
                    if (degatsInfliges < joueur1.m_pvActuels)
                    {
                        joueur1.m_pvActuels -= degatsInfliges;
                        sf::Packet packetDegatsInfliges;
                        sf::Packet packetDegatsInfligesOther;
                        unsigned char packetType = 3;
                        unsigned char packetTypeOther = 4;
                        packetDegatsInfliges << packetType << degatsInfliges;
                        packetDegatsInfligesOther << packetTypeOther << degatsInfliges;
                        socketPlayer1.send(packetDegatsInfliges);
                        std::cout << "Envoie d'information de douleur j1 à joueur 2" << std::endl;
                        socketPlayer2.send(packetDegatsInfligesOther);
                    }
                    else
                    {
                        joueur1.m_pvActuels = 0;
                        sf::Packet packetVictoire;
                        sf::Packet packetDefaite;
                        unsigned char packetType = 5;
                        unsigned char packetTypeOther = 6;
                        packetVictoire << packetType << degatsInfliges;
                        packetDefaite << packetTypeOther << degatsInfliges;
                        socketPlayer2.send(packetVictoire);
                        socketPlayer1.send(packetDefaite);
                    }
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
            //else
            //{
            //    std::cout << "No reception during the last 60 seconds..." << std::endl;
            //}
    }


}
