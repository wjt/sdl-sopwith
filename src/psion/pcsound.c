// Emacs style mode select -*- C++ -*-
//---------------------------------------------------------------------------
//
// $Id$
//
// Copyright(C) 2001-2003 Simon Howard
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version. This program is distributed in the hope that
// it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
// the GNU General Public License for more details. You should have
// received a copy of the GNU General Public License along with this
// program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA.
//
//--------------------------------------------------------------------------
//
// Sound.
//
// todo: Psion speaker kernel driver
//	 /dev/dsp output
//
//---------------------------------------------------------------------------

#include <math.h>

#include "sw.h"
#include "swsound.h"

#define FREQ 22050
#define TIMER_FREQ 1193280

static int speaker_on = 0;
static float current_freq = 0xff;

// square wave function for sound generation

static inline float square_wave(float time)
{
	int l = (int) time;
	return time - l < 0.5 ? 1 : 0;
}

// callback function to generate sound

static void snd_callback(void *userdata, unsigned char *stream, int len)
{
	static int lasttime;
	static float lastfreq;
	int i;

	swsndupdate();

	// lasttime stores the time offset from the last call
	// we save the time so that the multiple time slices
	// all fit together smoothly

	// if we have changed frequency since last time, we need
	// to adjust lasttime to the new frequency

	lasttime *= lastfreq / current_freq;

	for (i = 0; i < len; ++i) {
		if (speaker_on) {
			stream[i] =
			    127 * square_wave(current_freq *
					      (i + lasttime));
		} else {
			stream[i] = 0;
		}
	}

	lasttime += len;
	lastfreq = current_freq;
}

//
// set the speaker tone
// f is the 'count' sent to the timer chip to specify the frequency
//

void Speaker_Output(unsigned short count)
{
	if (!count) {
		current_freq = 0;
		speaker_on = 0;
		return;
	}
	speaker_on = 1;
	current_freq = (TIMER_FREQ) / ((float) count * FREQ);
}

// turn speaker on

void Speaker_On()
{
	speaker_on = 1;
	if (!current_freq)	// sanity check
		current_freq = 255;
}

// turn sound off

void Speaker_Off()
{
	speaker_on = 0;
}

static int sound_initted = 0;

void Speaker_Shutdown()
{
	if (!sound_initted)
		return;


	sound_initted = 0;
}

// initialise sound

void Speaker_Init()
{
}

// this is identical to the BASIC SOUND function

void Speaker_Sound(int freq, int duration)
{
	int duration_clocks = duration * 1000 / 18.2;
	int endtime;

	// turn speaker on

	int count = TIMER_FREQ / freq;

	Speaker_Output(count);

	// turn speaker off

	Speaker_Off();
}

//-----------------------------------------------------------------------
// 
// $Log$
// Revision 1.1.1.1  2003/02/14 19:03:38  fraggle
// Initial Sourceforge CVS import
//
//
// sdh 14/2/2003: change license header to GPL
// sdh 10/11/2001: Gtk+ port
// sdh 21/10/2001: added cvs tags
//
//-----------------------------------------------------------------------
