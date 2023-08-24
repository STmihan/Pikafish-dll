#include <iostream>
#include <string>

#include "papi/papi.h"

void on_output(const char* output)
{
    std::cout << output << " (from C++)" << std::endl;
}

int main(int argc, char* argv[])
{
    PAIP_init();
    PAIP_run("go depth 10");
    PAIP_shutdown();
    return 0;
}
