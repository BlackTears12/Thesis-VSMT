#include "controller.hpp"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<common::client_id>("common::client_id");
    qRegisterMetaType<shared_ptr<metrics::RuntimeMetric>>("shared_ptr<metrics::RuntimeMetric>");
    qRegisterMetaType<shared_ptr<vsock::Message>>("std::shared_ptr<Message>");
    Controller cont;
    cont.startExecution();

    return a.exec();
}
