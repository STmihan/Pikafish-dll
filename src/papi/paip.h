#pragma once

#ifdef PIKAFISH_EXPORTS
#define PIKAFISH_API __declspec(dllexport)
#else
#define PIKAFISH_API __declspec(dllimport)
#endif

namespace PAIP
{
    void init();
    void run(const char* command);
    void shutdown();
};

extern "C" {
    PIKAFISH_API void PAIP_init();
    PIKAFISH_API void PAIP_run(const char* command);
    PIKAFISH_API void PAIP_shutdown();
}
