#ifndef NETWORKING_H
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <iostream>
#define NETWORKING_H
using namespace std;

class networking
{
    public:
        networking();
        networking(string Ip);
        virtual ~networking();
    protected:
        sf::IpAddress getReipientIP();
        void setReipientIP(string Ip);

    private:
        sf::IpAddress player2Ip;
        sf::UdpSocket socket;
        unsigned short port = 54000;

};

#endif // NETWORKING_H
