#include <QCoreApplication>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    auto args = QCoreApplication::arguments();
    for (auto& arg : args) {
        qInfo() << arg;
    }
}