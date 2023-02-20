#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;

void print(int x, int y, int z)
{
    std::cout << x << y << z << std::endl;
}

int main(int argc, char *argv[])
{
    asio::io_context io_context;

    asio::ip::tcp::acceptor acceptor(io_context);
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 8080);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    asio::ip::tcp::socket socket(io_context);

    acceptor.async_accept(socket,
                          std::bind(
                              [](asio::ip::tcp::socket *socket) -> void {
                                  std::string buff{"hello"};
                                  socket->write_some(asio::buffer(buff));
                                  std::cout << buff;

                                  buff.resize(1024);
                                  socket->read_some(asio::buffer(buff));
                                  std::cout << buff;
                              },
                              &socket));

    io_context.run();
}
