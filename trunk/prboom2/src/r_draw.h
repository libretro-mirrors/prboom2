/* Emacs style mode select   -*- C++ -*- 
 *-----------------------------------------------------------------------------
 *
 * $Id: r_draw.h,v 1.2 2000/05/09 21:45:39 proff_fs Exp $
 *
 *  PrBoom a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Colin Phipps (cph@lxdoom.linuxgames.com), 
 *  Jess Haas (JessH@lbjhs.net)
 *  and Florian Schulze (florian.proff.schulze@gmx.net)
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *      System specific interface stuff.
 *
 *-----------------------------------------------------------------------------*/

#ifndef __R_DRAW__
#define __R_DRAW__

#include "r_defs.h"

#ifdef __GNUG__
#pragma interface
#endif

extern const lighttable_t *dc_colormap;
extern int      dc_x;
extern int      dc_yl;
extern int      dc_yh;
extern fixed_t  dc_iscale;
extern fixed_t  dc_texturemid;
extern int      dc_texheight;    // killough

// first pixel in a column
extern const byte     *dc_source;         

// The span blitting interface.
// Hook in assembler or system specific BLT here.

#ifndef _MSC_VER

#ifndef I386
void R_DrawColumn(void);
void R_DrawTLColumn(void);      // drawing translucent textures // phares
#else
// CPhipps - core rendering high res ASM support
// For optimal speed at 320xy resolutions we continue to use the 
//  old hardcoded width asm funcs
// For other resolutions we use versions that uses SCREENWIDTH

// _Normal funcs assume SCREENWIDTH = 320
void R_DrawColumn_Normal(void);
void R_DrawTLColumn_Normal(void);

// _HighRes funcs use SCREENWIDTH var
void R_DrawColumn_HighRes(void);
void R_DrawTLColumn_HighRes(void);

// Pointers to the ones to use, held and set in i_video.c
extern void (*R_DrawColumn)(void);
extern void (*R_DrawTLColumn)(void);

#endif

#else // _MSC_VER
void (*R_DrawColumn)(void);
void (*R_DrawTLColumn)(void);

void R_DrawColumn_Normal(void);
void R_DrawTLColumn_Normal(void);

#define R_DrawColumn_HighRes R_DrawColumn_Normal
#define R_DrawTLColumn_HighRes R_DrawTLColumn_Normal
#endif // _MSC_VER

void R_DrawFuzzColumn(void);    // The Spectre/Invisibility effect.

// Draw with color translation tables, for player sprite rendering,
//  Green/Red/Blue/Indigo shirts.

void R_DrawTranslatedColumn(void);

void R_VideoErase(unsigned ofs, int count);

extern lighttable_t *ds_colormap;

extern int     ds_y;
extern int     ds_x1;
extern int     ds_x2;
extern fixed_t ds_xfrac;
extern fixed_t ds_yfrac;
extern fixed_t ds_xstep;
extern fixed_t ds_ystep;

// start of a 64*64 tile image
extern const byte *ds_source;              
extern byte playernumtotrans[MAXPLAYERS]; // CPhipps - what translation table for what player
extern const byte *translationtables;
extern const byte *dc_translation;

// Span blitting for rows, floor/ceiling. No Spectre effect needed.
void R_DrawSpan(void);

void R_InitBuffer(int width, int height);

// Initialize color translation tables, for player rendering etc.
void R_InitTranslationTables(void);

// Rendering function.
void R_FillBackScreen(void);

// If the view size is not full screen, draws a border around it.
void R_DrawViewBorder(void);

extern const byte *tranmap;         // translucency filter maps 256x256  // phares 
extern const byte *main_tranmap;    // killough 4/11/98

#endif
