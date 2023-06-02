#include <iostream>

#include "common.hpp"
//#include "constants.hpp"
#include "logger.hpp"
#include "signal.hpp"
//#include "ubus.hpp"

static bool running = true;

static void die_handler(int signum) {

	logger::info << "die signal received" << std::endl;
	running = false;
}

int main(const int argc, const char **argv) {

	logger::output_level[logger::type::info] = true;
	logger::output_level[logger::type::error] = true;
	logger::output_level[logger::type::verbose] = true;
	logger::output_level[logger::type::vverbose] = true;
	logger::output_level[logger::type::debug] = true;

	std::cout << "signal handler test" << std::endl;

	Signal::register_handler(die_handler);

	std::cout << "exit with CTRL-C" << std::endl;

	while (running);

	logger::verbose << "program exits" << std::endl;

	return 0;
}
