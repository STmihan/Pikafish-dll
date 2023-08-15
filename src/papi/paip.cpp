#include "paip.h"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

#include "../bitboard.h"
#include "../position.h"
#include "../search.h"
#include "../thread.h"
#include "../uci.h"


void PAIP::init()
{
    std::cout << Stockfish::engine_info() << std::endl;

    std::string path = std::filesystem::current_path().string();
    auto argv = new char*[1];
    argv[0] = path.data();

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
}


void PAIP_init()
{
    PAIP::init();
}

void PAIP_run(const char* command)
{
    PAIP::run(command);
}

void PAIP_shutdown()
{
    PAIP::shutdown();
}
