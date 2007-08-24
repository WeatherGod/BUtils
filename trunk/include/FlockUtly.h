#ifndef _FLOCK_UTLY_H
#define _FLOCK_UTLY_H

#include <fstream>


int TruncateFile(fstream &FileStream, const off_t NewLength = 0);
int FileLockControl(fstream &FileStream, const short LockType);

#endif
