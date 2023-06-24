#ifndef _WAVIO_H_
#define _WAvIO_H_

#include "audio.h"

Audio read_wav(char* file_name, char* has_err, char** err_msg);

#endif