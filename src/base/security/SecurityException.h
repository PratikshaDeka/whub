/*
 * SecurityException.h
 *
 * Exceptions and errors generated during cryptographic operations
 *
 *
 * Copyright (C) 2018 Amit Kumar (amitkriit@gmail.com)
 * This program is part of the Wanhive IoT Platform.
 * Check the COPYING file for the license.
 *
 */

#ifndef WH_BASE_SECURITY_SECURITYEXCEPTION_H_
#define WH_BASE_SECURITY_SECURITYEXCEPTION_H_
#include "../common/BaseException.h"

namespace wanhive {
/**
 * Exceptions generated by the cryptographic library
 */
class SecurityException: public BaseException {
public:
	SecurityException() noexcept;
	~SecurityException();
	const char* what() const noexcept override;
	int errorCode() const noexcept override;
private:
	unsigned long error;
	char buffer[256]; //Recommended size: at least 256 bytes
};

} /* namespace wanhive */

#endif /* WH_BASE_SECURITY_SECURITYEXCEPTION_H_ */
