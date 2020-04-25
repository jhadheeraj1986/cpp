/*!
 *  @file       Server.cpp
 *  @Project    Http Web Server implementation in cpp.
 *  @author     Dheeraj Jha
 *  @date       25/04/2020
 *  @license    MIT - (c) 2020 - Dheeraj Jha - jha.dheeraj1986@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. 
 */

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
	//uri.append_path(U("get"));

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

	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);
	//Close server
	on_shutdown();
	return 0;
}
