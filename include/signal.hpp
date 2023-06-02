#pragma once

#include <map>

typedef void (*die_handler_func)(int);

namespace Signal {

	enum type: uint8_t {
		TERM = 0,
		ALRM = 1,
		HUP = 2,
		INT = 3,
		PIPE = 4,
		QUIT = 5,
		USR1 = 6,
		USR2 = 7
	};

	static inline const std::map<Signal::type, bool> default_sig_actions {
		{ static_cast<Signal::type>(0), true },
		{ static_cast<Signal::type>(1), false },
		{ static_cast<Signal::type>(2), false },
		{ static_cast<Signal::type>(3), true },
		{ static_cast<Signal::type>(4), false },
		{ static_cast<Signal::type>(5), false },
		{ static_cast<Signal::type>(6), false },
		{ static_cast<Signal::type>(7), false },
	};

	const bool register_handler(const die_handler_func die_handler,
		const std::map<Signal::type, bool> &sig_actions = Signal::default_sig_actions);
	const bool unregister_handler(void);
	const bool is_registered(void);

	namespace _private {

		extern bool sig_registered;

	};

};
