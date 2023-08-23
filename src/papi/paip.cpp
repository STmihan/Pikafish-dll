#if !defined(NN_NINTENDO_SDK)
#include "paip.h"

#if !defined(NN_NINTENDO_SDK)
#include <filesystem>
#endif
#include <iostream>
#include <sstream>
#include <string>

#include "../bitboard.h"
#include "../position.h"
#include "../search.h"
#include "../thread.h"
#include "../uci.h"
#include "../output/output.h"


void PAIP::init()
{
    Stockfish::Output::init();
    Stockfish::Output::output(Stockfish::engine_info());
    auto argv = new char* [1];
#if !defined(NN_NINTENDO_SDK)
    std::string path = std::filesystem::current_path().string();
    argv[0] = path.data();
#else
    argv[0] = "";
#endif


    Stockfish::CommandLine::init(1, argv);
    Stockfish::UCI::init(Stockfish::Options);
    Stockfish::Tune::init();
    Stockfish::Bitboards::init();
    Stockfish::Position::init();
    Stockfish::Threads.set(size_t(Stockfish::Options["Threads"]));
    Stockfish::Search::clear(); // After threads are up
    Stockfish::Eval::NNUE::init();
}

void PAIP::run(const char* command)
{
    std::vector<std::string> tokens;
    std::istringstream iss(command);

    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(tokens));

    std::vector<const char*> argv;
    argv.push_back("");
    argv.reserve(tokens.size());
    for (const auto& token : tokens)
        argv.push_back(token.c_str());

    Stockfish::UCI::run(argv.size(), const_cast<char**>(argv.data()));
}

void PAIP::shutdown()
{
    Stockfish::Threads.set(0);
    Stockfish::Output::shutdown();
}

void PAIP::set_output_callback(void (*on_output_callback)(const char*))
{
    Stockfish::Output::set_output_callback(on_output_callback);
}


extern "C" {
PIKAFISH_API void PAIP_init()
{
    PAIP::init();
}

PIKAFISH_API void PAIP_run(const char* command)
{
    PAIP::run(command);
}

PIKAFISH_API void PAIP_shutdown()
{
    PAIP::shutdown();
}

PIKAFISH_API void PAIP_set_output_callback(void (*on_output_callback)(const char*))
{
    PAIP::set_output_callback(on_output_callback);
}
}
#endif
