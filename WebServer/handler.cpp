#include "stdafx.h"
#include "handler.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;


Handler::Handler(utility::string_t url) : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&Handler::handle_get, this, std::placeholders::_1));
}

//
// A GET of the dealer resource produces a list of existing tables.
//
void Handler::handle_get(http_request message)
{
    ucout <<"Handle get: "<< message.to_string() << endl;

	auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

	for(std::vector<utility::string_t>::iterator itr = paths.begin();itr != paths.end(); itr++){
        cout << *itr <<endl;
    }

    if (paths.empty())
    {
        message.reply(status_codes::OK, "{1:Namaste World!!!}");
        return;
    }

	message.reply(status_codes::OK, "{1:!!!Namaste World!!!!}");
	return;
};


