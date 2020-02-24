#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;
const string clientLog = "Client: ";
const int PortNumber    = 55000;

int main()
{
   /*
    Create a client socket
    Headers: #include <sys/types.h>  #include <sys/socket.h>
    */
   int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (-1 == clientSocket)
    {
        cerr<<clientLog+"Failed to create a client socket"<<endl;
        return 1;
    }

    /*
        Create a sockaddr_in structure object to connect to server
TODO:   "127.0.0.1" -   ?
    */
   sockaddr_in clientSockAdd;
   clientSockAdd.sin_family = AF_INET;
   clientSockAdd.sin_port = htons(PortNumber);
   inet_pton(AF_INET, "127.0.0.1", &clientSockAdd.sin_addr);

    /*
        Connect to server
        Headers: #include <sys/types.h>  #include <sys/socket.h>
    */
   int ret = connect(clientSocket,(sockaddr*)&clientSockAdd, sizeof(clientSockAdd));
   if(-1 == ret){
        cerr<<clientLog+"Failed to connect to server"<<endl;
        return 2;
   }

    char buffer[1024];
    string clientInput;

    do{
        cout << "$ ";
        getline(cin, clientInput);

        //send a message to server
        //Headers: #include <sys/types.h> #include <sys/socket.h>
        int retSend = send(clientSocket, clientInput.c_str(), clientInput.size()+1, 0);
        if(-1 == retSend){
            cerr<<clientLog+"Failed to send message to server."<<endl;
        }

        //Receive a response from server
        int SizeOfResponseRecvFromServer = recv(clientSocket, buffer, 1024, 0);
        if (-1 == SizeOfResponseRecvFromServer)
        {
            cerr << clientLog+"There was an error getting response from server"<<endl;
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(buffer, SizeOfResponseRecvFromServer) << endl;
        }
    }while(1);

    close(clientSocket);

    return 0;
}