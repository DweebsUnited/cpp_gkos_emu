#include "GKOS.h"
#include "Windows.h"

std::optional<char> GKOS::GKOS::scanKeys( ) {

	char curr = 0;

	curr |= ( 0x8000 & GetAsyncKeyState( KEY_1 ) ) >> 15;
	curr |= ( 0x8000 & GetAsyncKeyState( KEY_2 ) ) >> 14;
	curr |= ( 0x8000 & GetAsyncKeyState( KEY_3 ) ) >> 13;
	curr |= ( 0x8000 & GetAsyncKeyState( KEY_4 ) ) >> 12;
	curr |= ( 0x8000 & GetAsyncKeyState( KEY_5 ) ) >> 11;
	curr |= ( 0x8000 & GetAsyncKeyState( KEY_6 ) ) >> 10;

	char ret = 0;

	// What to do if up and down at the same?
	// Ignore? Unsafe, but okay for prototype...
	// Remove all ups, emit char, add back downs?

	// If increasing
	if( this->increasing ) {
		// If bits now unset, mark decreasing and emit char

		if( curr < this->state ) {

			ret = this->state;

			this->increasing = false;

		}

	} else {

		// Decreasing

		// If bits now set, mark increasing
		if( curr > this->state || curr == 0 ) {

			this->increasing = true;

		}

	}

	this->state = curr;

	// If we should return, look it up
	if( ret > 0 ) {
		
		auto c = keymap_letter.find( ret );
		
		// If we find one, return it
		if( c != keymap_letter.end( ) ) {

			return std::optional( c->second );
		
		} else {
			
			// Return an X if we don't know the char
			return std::optional( 'X' );
		
		}

	} else {

		return std::nullopt;

	}

};

void GKOS::GKOS::poll_loop( ) {

	while( 1 ) {
		
		std::optional<char> c = this->scanKeys( );
		if( c.has_value( ) ) {

			printf( "%c", *c );

		}

		// Sleep 10ms
		Sleep( 10 );

	}

};

std::map<char, char> GKOS::keymap_letter( {
	{ 0b000001, 't' },
	{ 0b000010, 'a' },
	{ 0b000100, 'o' },
	{ 0b100000, 'i' },
	{ 0b010000, 'e' },
	{ 0b001000, 'n' },

	{ 0b110000, 's' },
	{ 0b110001, 'v' },
	{ 0b110010, 'k' },
	{ 0b110100, 'j' },

	{ 0b011000, 'h' },
	{ 0b011001, 'g' },
	{ 0b011010, 'p' },
	{ 0b011100, 'f' },

	{ 0b000011, 'r' },
	{ 0b100011, 'y' },
	{ 0b010011, 'b' },
	{ 0b001011, 'w' },

	{ 0b000110, 'l' },
	{ 0b100110, 'm' },
	{ 0b010110, 'u' },
	{ 0b001110, 'c' },

	{ 0b101000, 'd' },
	{ 0b101001, 'x' },
	{ 0b101010, 'z' },
	{ 0b101100, 'q' },

	{ 0b000101, 'ü' },
	{ 0b100101, 'ö' },
	{ 0b010101, 'ä' },
	{ 0b001101, 'ß' },

	// Special characters and missing punctuation

	// Whitespace
	{ 0b010010, ' ' },
	{ 0b110011, '\n'},
	{ 0b011110, '\t'} } );