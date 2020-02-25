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
        AF_INET     -   The AF_INET address family is the address family for IPv4.
        AF_INET6    -   The AF_INET6 address family is the address family for IPv6.
        SOCK_STREAM -   for TCP Socket 
        SOCK_DGRAM  -   UDP socket
        Headers     -   #include <sys/types.h>  #include <sys/socket.h>
     */
    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == serverSocket){
        cerr<< ServerLog + "Failed to create socket.";
        return 1;
    }

    /*
        Bind the ip address and port to a socket.
        sockaddr_in     -   The SOCKADDR_IN structure specifies a transport address and port for the AF_INET address family.  
        sockaddr_in6    -   The SOCKADDR_IN6 structure specifies a transport address and port for the AF_INET6 address family 
        htons()         -   The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian)
        inet_pton()     -   convert IPv4 and IPv6 addresses from text to binary form.
        "0.0.0.0"       -   all IPv4 addresses on the local machine.
    */
    sockaddr_in serverSocketAdd;
    serverSocketAdd.sin_family = AF_INET;
    serverSocketAdd.sin_port = htons(PortNumber);
    inet_pton(AF_INET, "0.0.0.0", &serverSocketAdd.sin_addr);

    bind(serverSocket, (sockaddr*)&serverSocketAdd, sizeof(serverSocketAdd));

    /*
        Tell the socket to start listening
        SOMAXCONN - ?
    */
    listen(serverSocket, SOMAXCONN);

    /*
        Waiting for client connections
        Header - ?
    */
   sockaddr_in clientSocketAdd;
   socklen_t clientSocketLen = sizeof(clientSocketAdd);

   int clientSocket = accept(serverSocket, (sockaddr*)&clientSocketAdd, &clientSocketLen);

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

    // Close serverSocket socket
    close(serverSocket);
    /*Close client socket*/
    close(clientSocket);
    return 0;
}