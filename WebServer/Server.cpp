#include "stdafx.h"
#include "handler.h"
/************************************************/

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<Handler> g_httpHandler;

void on_initialize(const string_t& address){
	
	uri_builder uri(address);
	uri.append_path(U("get"));

	auto addr = uri.to_uri().to_string();
	//Create a handler object here who will server all requests.
	g_httpHandler = std::unique_ptr<Handler>(new Handler(addr));
	g_httpHandler->open().wait();
	
	ucout << utility::string_t(U("Listening for requests at: "))<<addr<<std::endl;

}

void on_shutdown(){

	g_httpHandler->close().wait();
	return;
}



int main(int argc, char* argv[]){
	//Set a port number where server listen
	utility::string_t port = U("34568");
	if (argc == 2){
		port = argv[1];
	}
	//Set a address where server will run.e.g localhost, IPaddress
	utility::string_t address = U("http://localhost:");
	address.append(port);
	//Initialize your server
	on_initialize(address);

/* 	for(int i=0; i<100; i++){ 
		std::cout<<"This is for test"<<std::endl;
		sleep(1);} */

	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);
	//Close server
	on_shutdown();
	return 0;
}
