#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using std::shared_ptr;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    model::AppConfig getConfig();
    void provideAppConfig(const model::AppConfig &config);
    void connectionResolved(const comm::Connection& connection);
public slots:
    void onRuntimeMetricReceived(comm::client_id_t id,shared_ptr<metrics::RuntimeMetric> metric);
signals:
    void requestAppConfig();
    void appConfigChanged(const model::AppConfig& config);
    void connectToClient(comm::client_id_t id);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
