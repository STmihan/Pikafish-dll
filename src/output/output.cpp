#include "output.h"

#include <iostream>
#include <string>

void Stockfish::Output::init()
{
    on_output = nullptr;
}

void Stockfish::Output::output(const std::string& output)
{
    std::cout << output << std::endl;
    if (on_output)
        on_output(output.c_str());
}

void Stockfish::Output::set_output_callback(void (*on_output_callback) (const char*))
{
    on_output = on_output_callback;
}

void Stockfish::Output::shutdown()
{
    on_output = nullptr;
}
