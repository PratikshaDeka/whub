/*
 * File.h
 *
 * File descriptor management
 *
 *
 * Copyright (C) 2021 Amit Kumar (amitkriit@gmail.com)
 * This program is part of the Wanhive IoT Platform.
 * Check the COPYING file for the license.
 *
 */

#ifndef WH_BASE_UNIX_FILE_H_
#define WH_BASE_UNIX_FILE_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace wanhive {
/**
 * File descriptor management
 */
class File {
public:
	/**
	 * Default constructor: creates an empty object.
	 */
	File() noexcept;
	/**
	 * Constructor: associates a file descriptor.
	 * @param fd file descriptor's value
	 */
	File(int fd) noexcept;
	/**
	 * Constructor: opens a file.
	 * @param path file's pathname
	 * @param flags operation flags
	 */
	File(const char *path, int flags);
	/**
	 * COnstructor: opens or creates a file.
	 * @param path file's pathname
	 * @param flags operation flags
	 * @param mode file mode bitmap
	 */
	File(const char *path, int flags, mode_t mode);
	/**
	 * Constructor: opens a file.
	 * @param dirfd base path's descriptor
	 * @param path relative or absolute pathname
	 * @param flags operation flags
	 */
	File(int dirfd, const char *path, int flags);
	/**
	 * Constructor: opens or creates a file.
	 * @param dirfd base path's descriptor
	 * @param path relative or absolute pathname
	 * @param flags operation flags
	 * @param mode file mode bitmap
	 */
	File(int dirfd, const char *path, int flags, mode_t mode);
	/**
	 * Destructor: automatically closes the associated file descriptor.
	 */
	~File();
	//-----------------------------------------------------------------
	/**
	 * Returns the associated file descriptor.
	 * @return file descriptor's value
	 */
	int get() const noexcept;
	/**
	 * Sets a file descriptor after closing the existing one.
	 * @param fd new file descriptor's value
	 */
	void set(int fd) noexcept;
	/**
	 * Releases and returns the associated file descriptor.
	 * @return file descriptor's value
	 */
	int release() noexcept;
	//-----------------------------------------------------------------
	/**
	 * Wrapper for close(2): closes the file descriptor.
	 * @return true on success, false on system error
	 */
	bool close() noexcept;
	/**
	 * Wrapper for open(2): opens a file
	 * @param path file's pathname
	 * @param flags operation flags
	 */
	void open(const char *path, int flags);
	/**
	 * Wrapper for open(2): opens or creates a file.
	 * @param path file's pathname
	 * @param flags operation flags
	 * @param mode file mode bitmap
	 */
	void open(const char *path, int flags, mode_t mode);
	/**
	 * Wrapper for openat(2): opens a file.
	 * @param dirfd base path's descriptor
	 * @param path relative or absolute pathname
	 * @param flags operation flags
	 */
	void open(int dirfd, const char *path, int flags);
	/**
	 * Wrapper for openat(2): opens or creates a file.
	 * @param dirfd base path's descriptor
	 * @param path relative or absolute pathname
	 * @param flags operation flags
	 * @param mode file mode bitmap
	 */
	void open(int dirfd, const char *path, int flags, mode_t mode);
	//-----------------------------------------------------------------
	/**
	 * Wrapper for flock(2): applies an advisory lock.
	 * @param shared true for shared lock, false for exclusive lock
	 * @param block true for blocking operation, false for non-blocking
	 * @return true on success, false on temporary error (the operation was
	 * prohibited or interrupted).
	 */
	bool lock(bool shared, bool block);
	/**
	 * Wrapper for flock(2): removes an advisory lock.
	 */
	void unlock();
	//-----------------------------------------------------------------
	/**
	 * Wrapper for dup(2): duplicates the associated file descriptor.
	 * @return new file descriptor
	 */
	int duplicate();
	/**
	 * Wrapper for dup3(2) [fallback: dup2(2)]: duplicates the associated file
	 * descriptor.
	 * @param newfd suggested value for the new file descriptor
	 * @param flags operation flags for dup3(2)
	 * @return new file descriptor
	 */
	int duplicate(int newfd, int flags = 0);
private:
	int fd;
};

} /* namespace wanhive */

#endif /* WH_BASE_UNIX_FILE_H_ */
