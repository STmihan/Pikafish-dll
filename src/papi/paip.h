#pragma once

#if !defined(NN_NINTENDO_SDK)
#ifdef PIKAFISH_EXPORTS
#define PIKAFISH_API __declspec(dllexport)
#else
#define PIKAFISH_API __declspec(dllimport)
#endif
#include <sstream>

namespace PAIP
{
    void init();
    void run(const char* command);
    void shutdown();
    void set_output_callback(void (*on_output_callback) (const char*));
};

extern "C" {
    PIKAFISH_API void PAIP_init();
    PIKAFISH_API void PAIP_run(const char* command);
    PIKAFISH_API void PAIP_shutdown();
    PIKAFISH_API void PAIP_set_output_callback(void (*on_output_callback) (const char*));
}
#endif
