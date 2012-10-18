#ifndef LOG_H
#define LOG_H

#include "utils.h"

// ==============================================================
#ifdef _DEBUG
#define log(x,...) printf(x,__VA_ARGS__)
#else // _DEBUG
#define log(x,...)
#endif // _DEBUG
// ==============================================================



#endif // LOG_H
