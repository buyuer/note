#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

#include <iostream>

class SimpleHttpServer : public QTcpServer
{
    Q_OBJECT
  public:
    explicit SimpleHttpServer(QObject *parent = nullptr) : QTcpServer(parent)
    {
        listen(QHostAddress::Any, 8080);
    }

  protected slots:
    void incomingConnection(qintptr socketDescriptor) override
    {
        socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, &QTcpSocket::readyRead, this,
                &SimpleHttpServer::readyRead);
        connect(socket, &QTcpSocket::disconnected, socket,
                &SimpleHttpServer::deleteLater);
    }

    void readyRead()
    {
        QTextStream response(socket);
        response.setAutoDetectUnicode(true);
        response << "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html"
                    "charset =\"utf-8\"\r\n"
                    "\r\n"
                    "<h1>Hello, World!</h1>\n";
        socket->close();
    }

  private:
    QTcpSocket *socket{};
};

#include "tcp_server.moc"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    SimpleHttpServer server;

    return app.exec();
}