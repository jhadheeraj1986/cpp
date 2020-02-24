#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
using namespace std;

const string ServerLog  = "Server: ";
const int PortNumber    = 55000;
int main()
{
    /*  
        Lets create  a socket
        AF_INET     -   IPV4(for Internet Protocol v4 addresses)    Ref: https://docs.microsoft.com/en-us/windows-hardware/drivers/network/af-inet
        SOCK_STREAM -   for TCP Socket 
        SOCK_DGRAM  -   UDP socket
     */
    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == serverSocket){
        cerr<< ServerLog + "Failed to create socket.";
        return 1;
    }

    /*
        Bind the ip address and port to a socket.
TODO:   sockaddr_*      -   ?
TODO:   sockaddr_in     -   ?
TODO:   sockaddr_in6    -   ?
TODO:   htons()         -   ?
TODO:   inet_pton()     -   ?
TODO:   "0.0.0.0"       -   ?
    */
    sockaddr_in serverSocketAdd;
    serverSocketAdd.sin_family = AF_INET;
    serverSocketAdd.sin_port = htons(PortNumber);
    inet_pton(AF_INET, "0.0.0.0", &serverSocketAdd.sin_addr);

    bind(serverSocket, (sockaddr*)&serverSocketAdd, sizeof(serverSocketAdd));

    /*
        Tell Winsock the socket is for listening
        SOMAXCONN - ?
    */
    listen(serverSocket, SOMAXCONN);

    /*
        Waiting for client connections
        Header - ?
    */
   sockaddr_in clientSockerAdd;
   socklen_t clientSockerLen = sizeof(clientSockerAdd);

   int clientSocket = accept(serverSocket, (sockaddr*)&clientSockerAdd, &clientSockerLen);

   // Close serverSocket socket
    close(serverSocket);

    /*
        Receive message from client and sent it back to client as it is.
    */
   char buffer[1024];
   
   while(1){
       memset(buffer, 0, 1024);

        //Headers required: #include <sys/types.h> #include <sys/socket.h>
       int SizeOfMsgRecvFromClient = recv(clientSocket, buffer, 1024, 0);
       if(-1 == SizeOfMsgRecvFromClient){
           cerr<<ServerLog + "Some error while receiving from client"<<endl;
       }
       else{
           if(0 == SizeOfMsgRecvFromClient){
               cout << ServerLog + "Client disconnected. retry..." << endl;
           }
           else{
                cout << string(buffer, 0, SizeOfMsgRecvFromClient) << endl;
                // message back to client
                int SizeOfMsgSentToClient = send(clientSocket, buffer, SizeOfMsgRecvFromClient + 1, 0);
                if(-1 == SizeOfMsgSentToClient){
                    cerr<<ServerLog + "Some error while sending message to client"<<endl;
                }
           }
       }
   }
   /*Close client socket*/
    close(clientSocket);
    return 0;
}