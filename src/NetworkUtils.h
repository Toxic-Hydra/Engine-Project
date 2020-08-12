//
// Created by ivanl on 2020/7/11
//

#pragma once
#include "EngineConstants.h"
#include <iostream>
#include <SDL_net.h>

//Reminder handle deallocs
class UDPConnection
{
private:
    UDPsocket ServerUDP;
    UDPsocket ClientUDP;
    IPaddress UDPServerIP;
    const int MAX_PACKET_SIZE = 1024;
    UDPpacket* udpPacket;
    UDPpacket* sendPacket;

public:
    //Constructors
    UDPConnection();
    //UDP
    void InitServerUDP();
    void BindServerUDP();
    void ServerRecvUDP();
    //server->client send

    void InitClientUDP();
    void SendUDP(const char message[]);
    void ClientClose();
    //server->client receive

    ~UDPConnection();

};

class TCPConnection
{
private:
	TCPsocket ServerTCP;
	TCPsocket HostToClientTCP;
	TCPsocket ClientTCP; 
	IPaddress ServerIp;
	IPaddress ClientIp;
	SDLNet_SocketSet TCPSocketSet;
    SDLNet_SocketSet TCPClientSet;

public:
    //CONSTRUCTORS
    TCPConnection();
    //TCP
    void InitServerTCP();
    void ServerAcceptTCP();
    void ServerRecvTCP();
    void ServerSendTCP();
    //server send
    void InitClientTCP();
    void ClientSendTCP(const char message[]);
    bool ClientOk();
    void ClientRecvTCP();
    //client recv

    ~TCPConnection();
};
