#include "cpuloaddatamodel.hpp"
#include "application.hpp"

namespace datamodels
{

void CpuLoadDataModel::updateLoads(common::client_id id, double overallLoad, const vector<double> &coreLoads)
{
    auto &load = loadData[id];
    load->overallLoad.push(overallLoad);
    auto size = std::min(coreLoads.size(),(size_t)load->coreLoads.size());
    for(int i = 0;i < size;i++) {
        load->coreLoads[i]->push(coreLoads[i]);
    }

    if(id == context) {
        core::Application::Instance().getCpuRangeModel().setValue(overallLoad);
    }
}

void CpuLoadDataModel::setContext(common::client_id id)
{
    context = id;
    auto &load = loadData[id];
    core::Application::Instance().getCoreLoadProvider().setDataProviders(load->coreLoads);
    core::Application::Instance().getCpuGraphModel().setDataprovider(load->overallLoad);
}

void CpuLoadDataModel::append(common::client_id id, size_t coreSize)
{
    loadData.emplace(id,std::make_unique<CpuLoadData>(coreSize));
}

void CpuLoadDataModel::remove(common::client_id id)
{
    if(id == context) {
        setContext(common::ClientConfiguration::hostId());
    }
    loadData.erase(id);
}

}
