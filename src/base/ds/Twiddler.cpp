/*
 * Twiddler.cpp
 *
 * Bit and byte manipulations
 *
 *
 * Copyright (C) 2018 Amit Kumar (amitkriit@gmail.com)
 * This program is part of the Wanhive IoT Platform.
 * Check the COPYING file for the license.
 *
 */

#include "Twiddler.h"
#include <cctype>
#include <cstring>

namespace wanhive {

const unsigned char Twiddler::bitCount_[256] = {
#define B2(n) n, n+1, n+1, n+2
#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
		B6(0), B6(1), B6(1), B6(2) };

//Position of the first set bit in Nth byte (first entry is invalid)
const unsigned char Twiddler::bitOrdinal_[256] = {
#define P0 8
#define P(n) (n-1)
#define P1 P(1)
#define P2 P(2), P1
#define P3 P(3), P1, P2
#define P4 P(4), P1, P2, P3
#define P5 P(5), P1, P2, P3, P4
#define P6 P(6), P1, P2, P3, P4, P5
#define P7 P(7), P1, P2, P3, P4, P5, P6
#define P8 P(8), P1, P2, P3, P4, P5, P6, P7
		P0, P1, P2, P3, P4, P5, P6, P7, P8 };

unsigned int Twiddler::max(unsigned int x, unsigned int y) noexcept {
	return x ^ ((x ^ y) & -(x < y));
}

unsigned int Twiddler::min(unsigned int x, unsigned int y) noexcept {
	return y ^ ((x ^ y) & -(x < y));
}

bool Twiddler::isPower2(unsigned int x) noexcept {
	return x && !(x & (x - 1));
}

unsigned int Twiddler::modPow2(unsigned int n, unsigned int s) noexcept {
	return n & (s - 1);
}

unsigned int Twiddler::modExp2(unsigned int n, unsigned int exp) noexcept {
	const unsigned int d = 1U << exp;
	return n & (d - 1);
}

void Twiddler::exchange(unsigned int &x, unsigned int &y) noexcept {
	(((x) == (y)) || (((x) ^= (y)), ((y) ^= (x)), ((x) ^= (y))));
}

unsigned int Twiddler::power2Floor(unsigned int x) noexcept {
	if (x == 0) {
		return 0; //Invalid value
	} else if (isPower2(x)) {
		return x;
	} else {
		unsigned int p = 1;
		unsigned int r = 1;

		while (p && p <= x) {
			r = p;
			p <<= 1;
		}

		return r;
	}
}

unsigned int Twiddler::power2Ceil(unsigned int x) noexcept {
	if (x == 0) {
		return 1;
	} else if (isPower2(x)) {
		return x;
	} else {
		unsigned int r = 1;
		while (r && r < x) {
			r <<= 1;
		}
		return r;
	}
}

unsigned long Twiddler::mix(unsigned long i) noexcept {
	i += ~(i << 15);
	i ^= (i >> 10);
	i += (i << 3);
	i ^= (i >> 6);
	i += ~(i << 11);
	i ^= (i >> 16);
	return i;
}

unsigned long long Twiddler::mix(unsigned long long l) noexcept {
	l += ~(l << 32);
	l ^= (l >> 22);
	l += ~(l << 13);
	l ^= (l >> 8);
	l += (l << 3);
	l ^= (l >> 15);
	l += ~(l << 27);
	l ^= (l >> 31);
	return l;
}

bool Twiddler::isBetween(unsigned int value, unsigned int from,
		unsigned int to) noexcept {
	if (from < to) {
		return (from < value && to > value);
	} else {
		return (from < value || to > value);
	}
}

bool Twiddler::isInRange(unsigned int value, unsigned int from,
		unsigned int to) noexcept {
	if (from <= to) {
		return (from <= value && to >= value);
	} else {
		return (from <= value || to >= value);
	}
}

uint32_t Twiddler::mask(uint32_t word, uint32_t bitmask, bool set) noexcept {
	//For superscalar CPUs
	return ((word & ~bitmask) | (-set & bitmask));
}

uint32_t Twiddler::set(uint32_t word, uint32_t bitmask) noexcept {
	return word | bitmask;
}

uint32_t Twiddler::clear(uint32_t word, uint32_t bitmask) noexcept {
	return word &= ~bitmask;
}

uint32_t Twiddler::test(uint32_t word, uint32_t bitmask) noexcept {
	return (word & bitmask);
}

uint32_t Twiddler::merge(uint32_t x, uint32_t y, uint32_t bitmask) noexcept {
	return x ^ ((x ^ y) & bitmask);
}

unsigned int Twiddler::mod8(unsigned int x) noexcept {
	return (x & 7);
}

unsigned int Twiddler::div8(unsigned int x) noexcept {
	return (x >> 3);
}

unsigned int Twiddler::mult8(unsigned int x) noexcept {
	return (x << 3);
}

unsigned int Twiddler::bitCount(unsigned char v) noexcept {
	return bitCount_[v];
}

unsigned int Twiddler::bitCount(uint32_t v) noexcept {
	uint8_t *p = (uint8_t*) &v;
	return bitCount(p[0]) + bitCount(p[1]) + bitCount(p[2]) + bitCount(p[3]);
}

unsigned int Twiddler::bitOrdinal(unsigned char v) noexcept {
	return bitOrdinal_[v];
}

unsigned int Twiddler::bitNSlots(unsigned int bits) noexcept {
	return ((bits + 7) >> 3);
}

unsigned int Twiddler::bitSlot(unsigned int index) noexcept {
	return div8(index);
}

unsigned char Twiddler::bitMask(unsigned int index) noexcept {
	return (1U << mod8(index));
}

void Twiddler::set(unsigned char *bitmap, unsigned int index) noexcept {
	bitmap[bitSlot(index)] |= bitMask(index);
}

void Twiddler::clear(unsigned char *bitmap, unsigned int index) noexcept {
	bitmap[bitSlot(index)] &= ~bitMask(index);
}

void Twiddler::toggle(unsigned char *bitmap, unsigned int index) noexcept {
	bitmap[bitSlot(index)] ^= bitMask(index);
}

bool Twiddler::test(const unsigned char *bitmap, unsigned int index) noexcept {
	return (bitmap[bitSlot(index)] & bitMask(index));
}

unsigned int Twiddler::align(unsigned int size, unsigned int alignment) noexcept {
	return ((size + alignment - 1) & ~(alignment - 1));
}

unsigned int Twiddler::ceiling(unsigned int n, unsigned int k) noexcept {
	return (n + k - 1) / k;
}

unsigned int Twiddler::toUpperCase(char *dest, const char *src) noexcept {
	unsigned int i = 0;
	for (; src[i]; ++i) {
		dest[i] = toupper(src[i]);
	}
	dest[i] = '\0';
	return i;
}

unsigned int Twiddler::toLowerCase(char *dest, const char *src) noexcept {
	unsigned int i = 0;
	for (; src[i]; ++i) {
		dest[i] = tolower(src[i]);
	}
	dest[i] = '\0';
	return i;
}

void Twiddler::xorString(unsigned char *dest, const unsigned char *s1,
		const unsigned char *s2, unsigned int length) noexcept {
	for (unsigned int i = 0; i < length; ++i) {
		dest[i] = s1[i] ^ s2[i];
	}
}

char* Twiddler::stripLast(char *s, char delimiter) noexcept {
	if (s) {
		char *last = strrchr(s, delimiter);
		if (last) {
			*last = '\0';
			return last;
		}
	}
	return nullptr;
}

char* Twiddler::removeWhitespace(char *s) noexcept {
	char *i = s;
	char *j = s;

	do {
		if (!isspace(*i)) {
			*(j++) = *i;
		}
	} while (*(i++));

	return s;
}

} /* namespace wanhive */
