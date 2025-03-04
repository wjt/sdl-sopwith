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
//
//        swobject -      SW object allocation and deallocation
//

#include "sw.h"
#include "swmain.h"
#include "swobject.h"

OBJECTS *allocobj(void)
{
	OBJECTS *ob;

	if (!objfree) {
		return NULL;
	}

	ob = objfree;
	objfree = ob->ob_next;

	ob->ob_next = NULL;
	ob->ob_prev = objbot;

	if (objbot) {
		objbot->ob_next = ob;
	} else {
		objtop = ob;
	}

	ob->ob_sound = NULL;
	ob->ob_drwflg = 0;
	ob->ob_onmap = false;

	objbot = ob;

	return ob;
}

void deallobj(OBJECTS * obp)
{
	OBJECTS *ob=obp;
	OBJECTS *obb = ob->ob_prev;

	if (obb) {
		obb->ob_next = ob->ob_next;
	} else {
		objtop = ob->ob_next;
	}

	obb = ob->ob_next;

	if (obb) {
		obb->ob_prev = ob->ob_prev;
	} else {
		objbot = ob->ob_prev;
	}

	ob->ob_next = 0;
	if (delbot) {
		delbot->ob_next = ob;
	} else {
		deltop = ob;
	}

	delbot = ob;
}

void movexy(OBJECTS * ob, int *x, int *y)
{
	unsigned int pos = 0;
	//long vel;
//      pos = (((long) (ob->ob_x)) << 16) + ob->ob_lx;
//      vel = (((long) (ob->ob_dx)) << 16) + ob->ob_ldx;

	// Adding this to avoid range errors -- Jesse
	if (pos >= ((currgame->gm_max_x - 10) << 16)) {
		pos = (currgame->gm_max_x - 10) << 16;
	}
	if (pos < 0) {
		pos = 0;
	}

	pos = (ob->ob_x + ob->ob_dx) << 16;
	pos += ob->ob_lx + ob->ob_ldx;
	ob->ob_x = (unsigned short) (pos >> 16) & 0xffff;
	ob->ob_lx = (unsigned short) pos & 0xffff;
	*x = ob->ob_x;
	pos = (ob->ob_y + ob->ob_dy) << 16;
	pos += ob->ob_ly + ob->ob_ldy;
	ob->ob_y = (unsigned short) (pos >> 16) & 0xffff;
	ob->ob_ly = (unsigned short) pos & 0xffff;
	*y = ob->ob_y;
}

void setdxdy(OBJECTS * obj, int dx, int dy)
{
	obj->ob_dx = (dx >> 8);
	obj->ob_ldx = (dx << 8) & 0xffff;
	obj->ob_dy = (dy >> 8);
	obj->ob_ldy = (dy << 8) & 0xffff;
}

//
// 2003-02-14: Code was checked into version control; no further entries
// will be added to this log.
//
// sdh 14/2/2003: change license header to GPL
// sdh 21/10/2001: rearranged headers, added cvs tags
// sdh 21/10/2001: reformatted with indent. adjusted some code by hand
//                 to make more readable
// sdh 19/10/2001: removed externs (now in headers)
// sdh 18/10/2001: converted all functions to ANSI-style arguments
//
//
// 87-03-09        Microsoft compiler.
// 84-10-31        Atari
// 84-06-12        PCjr Speed-up
// 84-02-07        Development
//
