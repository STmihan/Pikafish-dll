#include "papi/paip.h"

int main()
{
    PAIP_init();
    PAIP_run("go depth 10");
    PAIP_shutdown();
}
