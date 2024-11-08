#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <linux/virtio_vsock.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>
#include <vector>
#include "gaugewidget.h"

using std::vector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

model::AppConfig MainWindow::getConfig()
{

}

void MainWindow::provideAppConfig(const model::AppConfig &config)
{

}

void MainWindow::connectionResolved(const comm::Connection &connection)
{
    std::cerr << "connection with client " << connection.id << " - " <<connection.state << std::endl;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onRuntimeMetricReceived(comm::client_id_t id,shared_ptr<metrics::RuntimeMetric> metric)
{
    std::cout << "Metric received: " << id << std::endl;
    std::cout << "Proc usage: " << metric->processorLoad << std::endl;
    std::cout << "Available memory:" << metric->memory.available << "\tUsed memory:" << metric->memory.used << std::endl;
    std::cout << "Processes:\n";
    for(auto& e: metric->processes){
        std::cout << "pid: " <<e.pid << "\t" << e.executable << " : " << e.args << "\tprocessor usage: " << e.processorUsage << "\tmemory usage: " << e.memoryUsage.used << std::endl;
    }
}
