#ifndef METRICS_H
#define METRICS_H

#include <vector>
#include <variant>
#include <memory>
#include <cstdint>
#include <string>

namespace metrics
{

using std::string;
using std::vector;
using std::unique_ptr;

using metricid_t = uint8_t;
using memoryunit_t = uint32_t;

/* Static info on the os cannot change in runtime */
struct SystemInfo
{
    SystemInfo(uint8_t core_n,uint64_t ram):
        cores(core_n),totalRam(ram) {}

    SystemInfo():
        cores(1),totalRam(1) {}

    uint64_t totalRam;
    uint8_t cores;
    string os;

    /* Defines the first byte of this metric */
    const static uint8_t IdByte = 1;
};

/* Info on memory in kb-s */

struct MemoryInfo
{
    MemoryInfo(uint64_t u,uint64_t a):
        used(u),available(a) {}
    uint64_t used;
    uint64_t available;
};

/* Info on a single process */
struct ProcessInfo
{
    enum Status
    {
        Running,Sleeping,Waiting,Zombie,Stopped,Dead,Idle
    };

    ProcessInfo(uint16_t p,Status stat,double proc,MemoryInfo mem,string exec,string arg):
        pid(p),status(stat),processorUsage(proc),memoryUsage(mem),executable(exec),args(arg) {}

    uint16_t pid;
    Status status;
    double processorUsage;
    MemoryInfo memoryUsage;
    string executable;
    string args;
};

/* Info on a single thread */
struct ThreadInfo
{
    ThreadInfo(uint16_t id,double proc,ProcessInfo::Status stat):
        tid(id),processorUsage(proc),status(stat){}
    uint16_t tid;
    double processorUsage;
    ProcessInfo::Status status;
};

/* Info on the os runtime at a given moment */
struct RuntimeMetric
{
    RuntimeMetric(double procL,MemoryInfo mem,vector<ProcessInfo> proc):
        processorLoad(procL),memory(mem),processes(proc){}

    double processorLoad;
    MemoryInfo memory;
    vector<ProcessInfo> processes;

    /* Defines the first byte of this metric */
    const static uint8_t IdByte = 2;
};

/* Wrapper around the variant type of RuntimeMetric and SystemInfo */
struct Metric
{
    typedef std::variant<unique_ptr<RuntimeMetric>,unique_ptr<SystemInfo>> ResponseData;
    enum Type
    {
        SystemInfoRequest = metrics::SystemInfo::IdByte,
        RuntimeMetricRequest = metrics::RuntimeMetric::IdByte,
        Corrupt
    };
public:
    explicit Metric(unique_ptr<metrics::RuntimeMetric> metric,metricid_t id);
    explicit Metric(unique_ptr<metrics::SystemInfo> sysinfo,metricid_t id);
    explicit Metric(void* nullp,metricid_t id_): type(Corrupt),id(id_) {}

    /* Moves the contained data casted to RuntimeMetric ptr*/
    unique_ptr<metrics::RuntimeMetric> moveDataAsMetric() { return std::move(std::get<unique_ptr<metrics::RuntimeMetric>>(data)); }

    /* Moves the contained data casted to SystemInfo ptr*/
    unique_ptr<metrics::SystemInfo> moveDataAsSysInfo() { return std::move(std::get<unique_ptr<metrics::SystemInfo>>(data)); }

    Type getType() const { return type; }
    metricid_t getId() const { return id; }
private:
    /*
     * type has to be initialized before data
    */    
    Type type;
    ResponseData data;
    metricid_t id;
};

}

#endif // METRICS_H
