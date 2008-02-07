#ifndef _FLOCK_UTLY_H
#define _FLOCK_UTLY_H

#include <fstream>
#include <cctype>	// for off_t

/*! \defgrooup FlockUtly File Locking Utility
 *  \brief Provides a file-locking mechanism.
 *
 *  This module isn't very clear-cut.  It also contains a useful
 *  file system handling function.  The file locking control is
 *  strictly advisory and possibly only works for Linux filesystems.
 *
 *  @{
*/

/*! \file FlockUtly.h
 *
*/

int TruncateFile(fstream &FileStream, const off_t NewLength = 0);
int FileLockControl(fstream &FileStream, const short LockType);

/*  @} */	// end of FlockUtly group

#endif
