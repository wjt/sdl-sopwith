//
// Copyright(C) 1984-2000 David L. Clark
// Copyright(C) 2001-2005 Simon Howard
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version. This program is distributed in the hope that
// it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//

#ifndef __SWASYNIO_H__
#define __SWASYNIO_H__

typedef enum { ASYN_LISTEN, ASYN_CONNECT } asynmode_t;

extern asynmode_t asynmode;
extern char asynhost[128];

extern void asynput(int movekey);
extern char *asynclos(void);
extern void init1asy(void);
extern void init2asy(void);
extern void asynupdate(void);

#endif

