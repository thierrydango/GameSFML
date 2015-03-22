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

int main(int argc, char *argv[])
{
    std::cout << "You are the server !" << std::endl;

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
                        std::cout << "Received " << newState << " " << x << " " << y << " from Player 1" << std::endl;
                        break;
                    }

                    case 2:
                    {
                        Sort sortLance;
                        packet >> sortLance;
                        std::cout << "Received temps Incantation :" << sortLance.m_tempsIncantation.asMilliseconds() << std::endl;
                        std::cout << "Received texture index :" << sortLance.m_sortVisuel.m_textureIndex << std::endl;
                        std::cout << "Received rayon :" << sortLance.m_sortVisuel.m_rayon << std::endl;
                        std::cout << "Received degats :" << sortLance.m_sortVisuel.m_degatsBase << std::endl;
                        std::cout << "Received porteeMin :" << sortLance.m_sortVisuel.m_porteeMin << std::endl;
                        std::cout << "Received longueurTrajectoire :" << sortLance.m_sortVisuel.m_longueurTrajectoire << std::endl;
                        std::cout << "Received vitesse :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesse) << std::endl;
                        std::cout << "Received acceleration :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_acceleration) << std::endl;
                        std::cout << "Received angle :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_angle) << std::endl;
                        std::cout << "Received vitesse rotation :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesseRotation) << std::endl;
                        std::cout << "Received acceleration angulaire :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_accelerationAngulaire) << std::endl;
                        std::cout << "Received duree de Vie :" << sortLance.m_sortVisuel.m_dureeDeVie.asMilliseconds() << std::endl;

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
                        break;
                    }

                    case 2:
                    {
                        Sort sortLance;
                        packet >> sortLance;
                        std::cout << "Received temps Incantation :" << sortLance.m_tempsIncantation.asMilliseconds() << std::endl;
                        std::cout << "Received texture index :" << sortLance.m_sortVisuel.m_textureIndex << std::endl;
                        std::cout << "Received rayon :" << sortLance.m_sortVisuel.m_rayon << std::endl;
                        std::cout << "Received degats :" << sortLance.m_sortVisuel.m_degatsBase << std::endl;
                        std::cout << "Received porteeMin :" << sortLance.m_sortVisuel.m_porteeMin << std::endl;
                        std::cout << "Received longueurTrajectoire :" << sortLance.m_sortVisuel.m_longueurTrajectoire << std::endl;
                        std::cout << "Received vitesse :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesse) << std::endl;
                        std::cout << "Received acceleration :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_acceleration) << std::endl;
                        std::cout << "Received angle :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_angle) << std::endl;
                        std::cout << "Received vitesse rotation :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_vitesseRotation) << std::endl;
                        std::cout << "Received acceleration angulaire :" << static_cast<unsigned int>(sortLance.m_sortVisuel.m_accelerationAngulaire) << std::endl;
                        std::cout << "Received duree de Vie :" << sortLance.m_sortVisuel.m_dureeDeVie.asMilliseconds() << std::endl;

                        break;
                    }

                }
            }
        }
        else
        {
            std::cout << "No reception during the last 60 seconds..." << std::endl;
        }
    }

}
