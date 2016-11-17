#include "networking.hpp"


networking::networking()
{
    //ctor
    if(socket.bind(port) != sf::Socket::Done){
        //error
        cout << "Failed to bind port 54000" << endl;
    }

}

networking::networking(string ip)
{


}

networking::~networking()
{
    //dtor
}
