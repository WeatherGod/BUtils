#ifndef _FLOCK_UTLY_C
#define _FLOCK_UTLY_C
using namespace std;

/*! \file FlockUtly.C
 *  \ingroup FlockUtly
 *
*/

#include <fstream>

#include <ext/stdio_filebuf.h>          // for the fd() member function of the stdio_filebuf class (it gives the file descriptor number)
#include <unistd.h>                     // for fcntl()
#include <fcntl.h>                      // for fcntl()
#include <cctype>			// for off_t
#include <sys/types.h>                  // for ftruncate()

#include "FlockUtly.h"

// To turn off file locking through this utility, just compile with -D _NO_FILELOCK

int TruncateFile(fstream &FileStream, const off_t NewLength)
/* It is assumed that the file is not locked down by someone else.
   If it has an advisory lock, this code does not check for that and
   it will go ahead and truncate the file.
*/
{
	/* This retrives the system's file descriptor
           number.  This number seems valid, even
           if two processes in separate systems access
           the same file.
	*/
        const int FileDescriptNum = ((__gnu_cxx::stdio_filebuf<char>*) FileStream.rdbuf())->fd();
        return(ftruncate(FileDescriptNum, NewLength));
}

int FileLockControl(fstream &FileStream, const short LockType)
/* Different kinds of locks are F_RDLCK, F_WRLCK, and F_UNLCK
   This function will wait for the lock to be applied.
   So when this function exits with a return value of 0,
   then it should be ok to go ahead in the stream.
*/
{
#ifndef _NO_FILELOCK_
        struct flock FileLock;
        FileLock.l_type = LockType;
        FileLock.l_whence = SEEK_SET;   // How to interpreate the offset number from l_start.
        FileLock.l_start = 0;           // Zero offset.  If l_whence is set to SEEK_SET, then this means beginning of file
        FileLock.l_len = 0;             // Lock this much.  If set to zero, then that means to lock to the end of file, regardless of filesize

	/* This retrives the system's file descriptor
           number.  This number seems valid, even
           if two processes in separate systems access
           the same file.
        */
        const int FileDescriptNum = ((__gnu_cxx::stdio_filebuf<char>*) FileStream.rdbuf())->fd();
        return(fcntl(FileDescriptNum, F_SETLKW, &FileLock));
        // sets the file lock.  If another process already has a write lock
        // on this file, then it will wait until it is finished.
        // The waiting issue hasn't been fully tested, but I am pretty sure it
        // is ok.  If another process ends prematurely, without unlocking,
        // the file is automatically unlocked anyway.  This is an Advisory lock
        // only!  So, another process that does NOT check for this lock can
        // still go ahead and access the file at the same time.
#else
        // Do nothing to the file in terms of locking and unlocking...
        return(0);
#endif
}


#endif
