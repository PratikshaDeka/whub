/*
 * SystemException.h
 *
 * Exceptions and errors generated by system calls
 *
 *
 * Copyright (C) 2018 Amit Kumar (amitkriit@gmail.com)
 * This program is part of the Wanhive IoT Platform.
 * Check the COPYING file for the license.
 *
 */

#ifndef WH_BASE_UNIX_SYSTEMEXCEPTION_H_
#define WH_BASE_UNIX_SYSTEMEXCEPTION_H_
#include "../common/BaseException.h"

namespace wanhive {
/**
 * Exceptions generate by system calls
 */
class SystemException: public BaseException {
public:
	/**
	 * Default constructor: reads the current errno.
	 */
	SystemException() noexcept;
	/**
	 * Constructor: assigns an error code.
	 * @param type error code
	 */
	SystemException(int type) noexcept;
	/**
	 * Destructor
	 */
	~SystemException();
	const char* what() const noexcept override;
	int errorCode() const noexcept override;
private:
	static const char* getErrorMessage(int error, char *buffer,
			unsigned int size) noexcept;
private:
	int error;
	const char *errorMessage;
	char buffer[256]; //Should be sufficient
};

} /* namespace wanhive */

#endif /* WH_BASE_UNIX_SYSTEMEXCEPTION_H_ */
