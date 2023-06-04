#include "logger.hpp"
#include "signal.hpp"

bool Signal::_private::sig_registered = false;

const bool Signal::register_handler(const die_handler_func die_handler, const std::map<Signal::type, bool> &sig_actions) {

	if ( Signal::_private::sig_registered ) {

		logger::error << "signal handler already registered" << std::endl;
		return false;
	}

	Signal::_private::sig_registered = true;

	logger::debug << "registering signal handlers" << std::endl;

	struct sigaction exit_action, ignore_action;

	exit_action.sa_handler = die_handler;
	sigemptyset(&exit_action.sa_mask);
	exit_action.sa_flags = 0;

	ignore_action.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action.sa_mask);
	ignore_action.sa_flags = 0;

	std::map<Signal::type, bool> new_actions(Signal::default_sig_actions);

	for ( auto const& [key, val] : sig_actions)
		new_actions[key] = val;

	sigaction(SIGTERM, new_actions.at(Signal::type::TERM) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGALRM, new_actions.at(Signal::type::ALRM) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGHUP, new_actions.at(Signal::type::HUP) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGINT, new_actions.at(Signal::type::INT) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGPIPE, new_actions.at(Signal::type::PIPE) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGQUIT, new_actions.at(Signal::type::QUIT) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGUSR1, new_actions.at(Signal::type::USR1) ? &exit_action : &ignore_action, NULL);
	sigaction(SIGUSR2, new_actions.at(Signal::type::USR2) ? &exit_action : &ignore_action, NULL);

	return true;
}

const bool Signal::unregister_handler(void) {

	if ( !Signal::_private::sig_registered ) {

		logger::error << "signal handler not registered" << std::endl;
		return false;
	}

	struct sigaction def_action;

	def_action.sa_handler = SIG_DFL;
	sigemptyset(&def_action.sa_mask);
	def_action.sa_flags = 0;

	sigaction(SIGTERM, &def_action, NULL);
	sigaction(SIGALRM, &def_action, NULL);
	sigaction(SIGHUP, &def_action, NULL);
	sigaction(SIGINT, &def_action, NULL);
	sigaction(SIGPIPE, &def_action, NULL);
	sigaction(SIGQUIT, &def_action, NULL);
	sigaction(SIGUSR1, &def_action, NULL);
	sigaction(SIGUSR2, &def_action, NULL);

	Signal::_private::sig_registered = false;
	return true;
}

const bool Signal::is_registered(void) {

	return Signal::_private::sig_registered;
}

const std::string Signal::string(const int sig) {

	switch (sig) {
		case SIGTERM: return "SIGTERM";
		case SIGALRM: return "SIGALRM";
		case SIGHUP: return "SIGHUP";
		case SIGINT: return "SIGINT";
		case SIGPIPE: return "SIGPIPE";
		case SIGQUIT: return "SIGQUIT";
		case SIGUSR1: return "SIGUSR1";
		case SIGUSR2: return "SIGUSR2";
		default: return "(unsupported signal type)";
	}

}
