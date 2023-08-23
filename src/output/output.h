#pragma once
#include <string>

namespace Stockfish
{
    namespace Output
    {
        inline void(*on_output) (const char*);
        void init();
        void output(const std::string& output);
        void set_output_callback(void (*on_output) (const char*));
        void shutdown();
    }
}
