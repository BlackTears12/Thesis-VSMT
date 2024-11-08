#include "application.hpp"
#include "metatypes.hpp"

using namespace core;

int main(int argc, char *argv[])
{
    Application::Init(argc,argv);
    return Application::Instance().startExecution();
}
