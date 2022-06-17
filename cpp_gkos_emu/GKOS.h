#pragma once

#include <map>
#include <optional>

#define KEY_1 'T'
#define KEY_2 'S'
#define KEY_3 'R'
#define KEY_4 'I'
#define KEY_5 'E'
#define KEY_6 'N'

namespace GKOS {

	enum GKOS_Mode {
		LETTER,
		SHIFTD,
		NUMBER,
		ONENUM
	};

	class GKOS {
		bool increasing = true;

		char state = 0;

		GKOS_Mode mode = GKOS_Mode::LETTER;

	public:
		std::optional<char> scanKeys( );

		void poll_loop( );

	};

	extern std::map<char, char> keymap_letter;

};