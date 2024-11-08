#include "controller.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

int Controller::exec(int &argc, char **argv)
{
    QApplication a(argc, argv);
    view = std::make_unique<MainWindow>();
    QObject::connect(view.get(),&MainWindow::requestAppConfig,this,&Controller::getAppConfig);
    QObject::connect(view.get(),&MainWindow::connectToClient,this,&Controller::handleConnection);
    QObject::connect(view.get(),&MainWindow::appConfigChanged,this,[this](const model::AppConfig &conf){
        this->model.setConfiguration(conf);
    });
    QObject::connect(this,&Controller::runtimeMetricReceived,view.get(),&MainWindow::onRuntimeMetricReceived);
    std::thread* mythr = new std::thread(&Controller::simulate,this);
    view->show();    
    return a.exec();
}

void Controller::handleConnection(comm::client_id_t id)
{
    ///if a dispatcher is already connected
    if(clients.count(id)){
        view->connectionResolved(clients[id]->getConnection());
        return;
    }

    try{
        auto client = std::make_unique<ClientDispatcher>(model.getClientConfig(id));
        setupClient(client);
        clients.emplace(id,std::move(client));
    }
    catch(vsock::ConnectionError &e){
        view->connectionResolved({
            .id = id,
            .state = Connection::Error,
        });
        std::cerr << "unable to connect to client: " << id << std::endl;
        std::cerr << e.error << std::endl;
    }
    catch(model::UnknownClientException &e){
        view->connectionResolved({
            .id = id,
            .state = Connection::Error,
        });
        std::cerr << "unknown client: " << id << std::endl;
    }
}

void Controller::requestRuntimeMetric(comm::client_id_t id)
{
    auto& client = getDispatcher(id);
    client->requestRuntimeMetric();
}

void Controller::requestSystemInfo(comm::client_id_t id)
{
    emit systemInfoReceived(id,model.getSystemInfo(id));
}

void Controller::getAppConfig()
{
    view->provideAppConfig(model.getConfiguration());
}

void Controller::setupClient(unique_ptr<ClientDispatcher> &client)
{
    QObject::connect(client.get(),&ClientDispatcher::connectionResolved,this,[this](Connection conn){
        emit view->connectionResolved(conn);
        this->model.setClientInfo(conn.id,conn.system);
    });

    QObject::connect(client.get(),&ClientDispatcher::clientUnresponsive,this,[this,&client](){
        emit this->clientUnresponsive(client->getId());
    });

    QObject::connect(client.get(),&ClientDispatcher::runtimeMetricReceived,this,[this,&client](shared_ptr<metrics::RuntimeMetric> metric){
        emit this->runtimeMetricReceived(client->getId(),metric);
    });
}

unique_ptr<ClientDispatcher> &Controller::getDispatcher(comm::client_id_t id)
{
    auto iter = clients.find(id);
    if(iter == clients.end())
        throw UnknownClientException();
    return iter->second;
}

#include <QRandomGenerator>
#include <unistd.h>

void Controller::simulate()
{
    QRandomGenerator rand;
    while(true){
        vector<metrics::ProcessInfo> pinfo;
        double psum = 0;
        metrics::memoryunit_t memsum;
        for(int i = 0;i < 10;i++){
            double proc = (float)1000000000/rand.generate();
            metrics::memoryunit_t mem = rand.generate();
            pinfo.emplace_back(i,metrics::ProcessInfo::Running,proc,metrics::MemoryInfo{mem,rand.generate()},"sys_demo","");
            psum += proc;
            memsum += mem;
        }

        auto metric = std::make_shared<metrics::RuntimeMetric>(psum,metrics::MemoryInfo{memsum,100000000},pinfo);
        emit this->runtimeMetricReceived(0,metric);
        sleep(10);
    }
}
