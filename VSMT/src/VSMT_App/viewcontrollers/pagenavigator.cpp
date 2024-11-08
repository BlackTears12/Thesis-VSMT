#include "pagenavigator.hpp"

namespace qml::viewcontrollers
{

void PageNavigator::showClientOverviewPage(client_id id)
{
    if(id != currentContext) {
        currentContext = id;
        emit clientContextChanged(id);
    }
    emit clientOverviewPageRequested();
}

PageNavigator::PageNavigator(QObject *parent)
    : QObject{parent}
{
    QObject::connect(this,&PageNavigator::requestDisconnect,this,[this](){
        emit clientDisconnectRequested(currentContext);
    });
}

int PageNavigator::clientContext() const
{
    return currentContext;
}

}
