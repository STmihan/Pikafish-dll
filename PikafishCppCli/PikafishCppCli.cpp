#include "papi/paip.h"

int main(int argc, char* argv[])
{
    PAIP::init();
    PAIP::run("go depth 10");
    PAIP::shutdown();
    
    return 0;
}
