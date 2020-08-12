#include "NetworkUtils.h"

//UDP UTILS

UDPConnection::UDPConnection()
{
    ServerUDP = NULL;
    ClientUDP = NULL;
    UDPServerIP.host = NULL;
    UDPServerIP.port = NULL;
    udpPacket = NULL;
    sendPacket = NULL;
}

void UDPConnection::InitServerUDP()
{
    ServerUDP = SDLNet_UDP_Open(SERVER_PORT);
    if (ServerUDP == NULL)
    {
        std::cout << "SERVER UDP FAILED TO OPEN\n";
    }
    udpPacket = SDLNet_AllocPacket(MAX_PACKET_SIZE);
}

void UDPConnection::BindServerUDP()
{
}

void UDPConnection::ServerRecvUDP()
{

    int recv = SDLNet_UDP_Recv(ServerUDP, udpPacket);
    if (recv > 0)
    {
        std::cout << "Received UDP Data from: " << SDLNet_ResolveIP(&udpPacket->address) << " Port: " << SDLNet_Read16(&udpPacket->address.port) << "\n";
        //Resolves to port 10753, I believe i may be writing wrong.
        udpPacket->data[udpPacket->maxlen - 1] = 0;
        std::cout << "Data: " << udpPacket->data << "\n";
    }
}

void UDPConnection::InitClientUDP()
{
    ClientUDP = SDLNet_UDP_Open(CLIENT_PORT);
    if (ClientUDP == NULL)
    {
        std::cout << "CLIENT UDP ERROR" << std::endl;
    }

    sendPacket = SDLNet_AllocPacket(MAX_PACKET_SIZE);
    if (SDLNet_ResolveHost(&UDPServerIP, LOCAL_HOST.c_str(), SERVER_PORT))
    {
        std::cout << "Failed to resolve host UDP\n";
    }

    sendPacket->address.host = UDPServerIP.host;
    sendPacket->address.port = UDPServerIP.port;
}

void UDPConnection::SendUDP(const char message[])
{
    
    strcpy((char*)sendPacket->data, message);
    sendPacket->len = strlen(message);
    SDLNet_UDP_Send(ClientUDP, -1, sendPacket);
}

void UDPConnection::ClientClose()
{
}

UDPConnection::~UDPConnection()
{
    /*UDPsocket ServerUDP;
    UDPsocket ClientUDP;
    IPaddress UDPServerIP;
    const int MAX_PACKET_SIZE = 1024;
    UDPpacket* udpPacket;
    UDPpacket* sendPacket;*/

    SDLNet_UDP_Close(ServerUDP);
    SDLNet_UDP_Close(ClientUDP);
    SDLNet_FreePacket(udpPacket);
    SDLNet_FreePacket(sendPacket);
}

//TCP UTILS

TCPConnection::TCPConnection()
{
    ServerTCP = NULL;
    HostToClientTCP = NULL;
    ClientTCP = NULL;
    ServerIp.host = NULL;
    ServerIp.port = NULL;
    ClientIp.host = NULL;
    ClientIp.port = NULL;
    TCPSocketSet = NULL;
}

void TCPConnection::InitServerTCP()
{
    //SERVER ONLY RESOLVES PORT
    int resolve = SDLNet_ResolveHost(&ServerIp, NULL, SERVER_PORT);
    std::cout << "Resolve: " << resolve << "\n";
    if (resolve == -1)
    {
        std::cout << "ERROR RESOLVING SERVER HOST\n";
        return;
    }

    ServerTCP = SDLNet_TCP_Open(&ServerIp);
    if (!ServerTCP)
    {
        std::cout << "FAILURE TO OPEN SERVER TCP: " << SDLNet_GetError() << "\n";
        return;
    }

    std::cout << "TCP LISTEN ON: " << ServerIp.port << std::endl;
    TCPSocketSet = SDLNet_AllocSocketSet(MAX_CLIENTS + 1);

    SDLNet_TCP_AddSocket(TCPSocketSet, ServerTCP);
}

void TCPConnection::ServerAcceptTCP()
{
    //Rewrite to accept any new Connections.

    HostToClientTCP = SDLNet_TCP_Accept(ServerTCP);
    if (HostToClientTCP == NULL)
    {
        std::cout << "Failed to Accept Connection: " << SDLNet_GetError() << std::endl;
    }
    else
    {
        std::cout << "Accepted Connection\n";
        SDLNet_TCP_AddSocket(TCPSocketSet, HostToClientTCP);
    }

}

void TCPConnection::ServerRecvTCP()
{
    //TODO: More error handling
    int ready = SDLNet_CheckSockets(TCPSocketSet, 0);
    
    if (ready > 0)
    {
        
        if (SDLNet_SocketReady(HostToClientTCP))//(SDLNet_SocketReady(ServerTCP))
        {
            //ServerAcceptTCP();
            const int MAXLEN = 256;
            char data[MAXLEN] = { 0 };

            int dataReceived = SDLNet_TCP_Recv(HostToClientTCP, data, MAXLEN);
            data[dataReceived] = 0;

            std::cout << "Received Data: " << data << "\n";
            
        }
    }
}

void TCPConnection::ServerSendTCP()
{
    const char message[] = "TCP RECEIVED SERVER->Client";
    SDLNet_TCP_Send(HostToClientTCP, message, strlen(message));
}

void TCPConnection::InitClientTCP()
{
    if (SDLNet_ResolveHost(&ClientIp, LOCAL_HOST.c_str(), SERVER_PORT))
    {
        std::cout << "Failed to Resolve Client Host\n";
    }

    ClientTCP = SDLNet_TCP_Open(&ClientIp);
    if (ClientTCP == NULL)
    {
        std::cout << "Failed to Open TCP Client Socket\n";
    }

    TCPClientSet = SDLNet_AllocSocketSet(1); //alloc for server.

    SDLNet_TCP_AddSocket(TCPClientSet, ClientTCP);

}

void TCPConnection::ClientSendTCP(const char message[])
{
    //sizeof will not work here. Compiler will grab the size of a char* which is 4
    //instead of the appropriate string length.
    SDLNet_TCP_Send(ClientTCP, message, strlen(message)); //strlen, not sure if I should use strlen +1
}


void TCPConnection::ClientRecvTCP()
{

    int ready;
    ready = SDLNet_CheckSockets(TCPClientSet, 0);
    if (ready)
    {
        if (SDLNet_SocketReady(ClientTCP))
        {
            const int MAXLEN = 256;
            char data[MAXLEN] = { 0 };

            int dataReceived = SDLNet_TCP_Recv(ClientTCP, data, MAXLEN);
            data[dataReceived] = 0;

            std::cout << "Received Data: " << data << "\n";
        }
        
    }
}

bool TCPConnection::ClientOk()
{
    return (HostToClientTCP != NULL);
}

TCPConnection::~TCPConnection()
{
    /*TCPsocket ServerTCP;
	TCPsocket HostToClientTCP;
	TCPsocket ClientTCP; //in code HostToClient is ClientTCP rewrite
	IPaddress ServerIp;
	IPaddress ClientIp;
	SDLNet_SocketSet TCPSocketSet;*/

    SDLNet_TCP_DelSocket(TCPSocketSet, ServerTCP);
    SDLNet_FreeSocketSet(TCPSocketSet);
    SDLNet_TCP_DelSocket(TCPClientSet, ClientTCP);
    SDLNet_FreeSocketSet(TCPClientSet);
    SDLNet_TCP_Close(ServerTCP);
    SDLNet_TCP_Close(HostToClientTCP);
    SDLNet_TCP_Close(ClientTCP);
    
}
