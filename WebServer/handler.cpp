/*!
 *  @file       handler.cpp
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

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;


Handler::Handler(utility::string_t url) : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&Handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&Handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&Handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&Handler::handle_delete, this, std::placeholders::_1));
}

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


