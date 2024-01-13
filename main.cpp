#include <iostream>

#include "common.hpp"
#include "logger.hpp"
#include "signal.hpp"

static bool running = true;

static void die_handler(int signum) {

	logger::info << Signal::string(signum) << " signal received" << std::endl;
	running = false;
}

int main(const int argc, const char **argv) {

	logger::loglevel(logger::debug);

	std::cout << "signal handler test" << std::endl;

	Signal::register_handler(die_handler);

	std::cout << "exit with CTRL-C" << std::endl;

	while (running);

	logger::verbose << "program exits" << std::endl;

	return 0;
}
