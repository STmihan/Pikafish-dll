#include <iostream>

#include "papi/paip.h"

void on_output(const char* output)
{
    std::cout << output << " (from C++)" << std::endl;
}

int main()
{
    PAIP_init();
    PAIP_set_output_callback(on_output);
    PAIP_run("go depth 10");
    PAIP_shutdown();
}
