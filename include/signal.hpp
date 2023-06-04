#pragma once

#include <map>
#include <csignal>

typedef void (*die_handler_func)(int);

namespace Signal {

	enum type: int {
		TERM = SIGTERM,
		ALRM = SIGALRM,
		HUP = SIGHUP,
		INT = SIGINT,
		PIPE = SIGPIPE,
		QUIT = SIGQUIT,
		USR1 = SIGUSR1,
		USR2 = SIGUSR2,
		UNK = -1
	};

	static inline const std::map<Signal::type, bool> default_sig_actions {
		{ static_cast<Signal::type>(SIGTERM), true },
		{ static_cast<Signal::type>(SIGALRM), false },
		{ static_cast<Signal::type>(SIGHUP), false },
		{ static_cast<Signal::type>(SIGINT), true },
		{ static_cast<Signal::type>(SIGPIPE), false },
		{ static_cast<Signal::type>(SIGQUIT), false },
		{ static_cast<Signal::type>(SIGUSR1), false },
		{ static_cast<Signal::type>(SIGUSR2), false },
	};

	const bool register_handler(const die_handler_func die_handler,
		const std::map<Signal::type, bool> &sig_actions = Signal::default_sig_actions);
	const bool unregister_handler(void);
	const bool is_registered(void);
	const std::string string(const int sig);

	namespace _private {

		extern bool sig_registered;

	};

};
