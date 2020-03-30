#include "stdafx.h"

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class Handler
{
public:
    Handler() {}
    Handler(utility::string_t url);

    pplx::task<void> open() { return m_listener.open(); }
    pplx::task<void> close() { return m_listener.close(); }

private:
    void handle_get(http_request message);
    void handle_put(http_request message);
    void handle_post(http_request message);
    void handle_delete(http_request message);

    http_listener m_listener;
};

