/*
 * Random.h
 *
 * Cryptographically secure pseudo random number generator
 *
 *
 * Copyright (C) 2018 Amit Kumar (amitkriit@gmail.com)
 * This program is part of the Wanhive IoT Platform.
 * Check the COPYING file for the license.
 *
 */

#ifndef WH_UTIL_RANDOM_H_
#define WH_UTIL_RANDOM_H_

namespace wanhive {
/**
 * Cryptographically secure PRNG
 */
class Random {
public:
	/**
	 * Default constructor: initializes the PRNG.
	 */
	Random() noexcept;
	/**
	 * Destructor
	 */
	~Random();

	/**
	 * Generates pseudo random bytes.
	 * @param buffer pointer to the output buffer
	 * @param count number of bytes to generate
	 */
	void bytes(void *buffer, unsigned int count);
};

} /* namespace wanhive */

#endif /* WH_UTIL_RANDOM_H_ */
