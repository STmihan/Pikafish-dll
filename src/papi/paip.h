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
#else
#include <nn/nn_Log.h>
#include <string>
#include <vector>

#include "../bitboard.h"
#include "../position.h"
#include "../search.h"
#include "../thread.h"
#include "../uci.h"
#include "../output/output.h"

void tokenize(std::string const& str, const char* delim,
    std::vector<const char*>& out)
{
    char* token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(token);
        token = strtok(nullptr, delim);
    }
}

extern "C" inline void PAIP_init()
{
    NN_LOG("call PAIP_init()\n");

    Stockfish::Output::init();
    Stockfish::Output::output(Stockfish::engine_info());

    auto argv = new char* [1];
    argv[0] = "";
    Stockfish::CommandLine::init(1, argv);
    Stockfish::UCI::init(Stockfish::Options);
    Stockfish::Tune::init();
    Stockfish::Bitboards::init();
    Stockfish::Position::init();
    Stockfish::Threads.set(size_t(Stockfish::Options["Threads"]));
    Stockfish::Search::clear(); // After threads are up
    Stockfish::Eval::NNUE::init();
}

extern "C" inline void PAIP_run(const char* command)
{
    std::string comStr = std::string(command);
    std::string log = "call PAIP_run() with command: " + comStr + "\n";
	NN_LOG(log.c_str());

    std::vector<const char*> tokens;
    tokens.push_back("");
    tokenize(comStr, " ", tokens);
    const int size = tokens.size();
    char** data = new char* [size];
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = const_cast<char*>(tokens[i]);
    }

    Stockfish::UCI::run(size, data);
    delete[] data;
}

extern "C" inline void PAIP_shutdown()
{
    NN_LOG("call PAIP_shutdown()\n");
    Stockfish::Threads.set(0);
    Stockfish::Output::shutdown();
}

extern "C" inline void PAIP_set_output_callback(void (*on_output_callback)(const char*))
{
    NN_LOG("call PAIP_set_output_callback()\n");
    Stockfish::Output::set_output_callback(on_output_callback);
}
#endif
