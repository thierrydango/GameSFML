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

//auto waitForPlayer(unsigned short PORT, sf::TcpSocket& socket)
//{
//    sf::TcpListener listener;
//    std::cout << "Waiting for a client..." << std::endl;
//    listener.listen(PORT);
//
//    if (listener.accept(socket) == sf::Socket::Done)
//    {
//        std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
//        return socket.getRemoteAddress();
//    }
//    else
//    {
//        std::cout << "Passage dans le else de listener.accept(socket), port peut-être déjà utilisé" << std::endl;
//    }
//}

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

    std::cout << "Waiting for player 2..." << std::endl;

    if (listener.accept(socketPlayer2) == sf::Socket::Done)
    {
        std::cout << "Player 2 connected: " << socketPlayer2.getRemoteAddress() << std::endl;
    }



}
