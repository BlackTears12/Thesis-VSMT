#include "controller.h"

Q_DECLARE_METATYPE(comm::client_id_t);
Q_DECLARE_METATYPE(shared_ptr<metrics::RuntimeMetric>);


int main(int argc, char *argv[])
{
    qRegisterMetaType<comm::client_id_t>("comm::client_id_t");
    qRegisterMetaType<shared_ptr<metrics::RuntimeMetric>>("shared_ptr<metrics::RuntimeMetric>");
    Controller controller;
    controller.exec(argc,argv);
}
