#include "application.h"

#include <linux/sysfileparser.hpp>

int main(int argc, char *argv[])
{
    Applicaton app(argc,argv);
    return app.exec();
}
