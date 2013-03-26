/*
   File name: fem_e022.c
   Date:      Tue Mar 26 11:40:43 CET 2013
   Author:    Jiri Brozovsky

   Copyright (C) 2013  Jiri Brozovsky

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   in a file called COPYING along with this program; if not, write to
   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
   02239, USA.

	FEM Solver - Element 022 (2D link contact element)
*/

#include "fem_elem.h"

extern tVector u;
extern int e003_res_p_loc(long ePos, long point, double *x, double *y, double *z);

int e022_geom_matrix(long ePos, long Mode, double L, tMatrix *K_s) { return(AF_OK); }
int e022_stiff(long ePos, long Mode, tMatrix *K_e, tVector *F_e, tVector *Fr_e) { return(AF_OK); }
int e022_mass(long ePos, tMatrix *M_e) { return(AF_OK); }
int e022_volume(long ePos, double *val) { return(AF_OK); }
long e022_rvals(long ePos) { return(4); }
int e022_eload(long ePos, long mode, tVector *F_e) { return(AF_OK); }


int e022_res_p_loc(long ePos, long point, double *x, double *y, double *z)
{
	double x1,x2,y1,y2 ;
  x1 = femGetNCoordPosX(femGetENodePos(ePos,0));
  y1 = femGetNCoordPosY(femGetENodePos(ePos,0));
  x2 = femGetNCoordPosX(femGetENodePos(ePos,1));
  y2 = femGetNCoordPosY(femGetENodePos(ePos,1));

  switch (point)
  {
	  case 1:
	     *x = x1 ;
	     *y = y1 ;
			 break ;
	  case 2:
	     *x = x2 ;
	     *y = y2 ;
			 break ;
	  default:
	     *x = 0.5*(x1+x2) ;
	     *y = 0.5*(y1+y2) ;
			 break ;
	}


	*z = 0 ;

	return(AF_OK);
}

int addElem_022(void)
{
	int rv = AF_OK;
	static long type    = 1 ;
	static long dim     = 1 ;
	static long nodes   = 2 ;
	static long dofs    = 2 ;
	static long ndof[2] = {U_X,U_Y} ;
	static long rs      = 2 ;
	static long real[2]  = {RS_FRICT,RS_PAIR_ID} ;
	static long rs_rp    = 0 ;
	static long *real_rp = NULL ;
	static long res      = 0 ;
	static long *nres    = NULL ;
	static long res_rp   = 2 ;
	static long nres_rp[2] = {RES_FX,RES_FY} ;

	if (type != femAddElem(type)) {return(AF_ERR_VAL);}
	Elem[type].dim = dim ;
	Elem[type].nodes = nodes ;
	Elem[type].dofs = dofs ;
	Elem[type].ndof = ndof ;
	Elem[type].rs = rs ;
	Elem[type].real = real ;
	Elem[type].rs_rp = rs_rp ;
	Elem[type].real_rp = real_rp ;
	Elem[type].res = res ;
	Elem[type].nres = nres ;
	Elem[type].res_rp = res_rp ;
	Elem[type].nres_rp = nres_rp ;

	Elem[type].stiff = e022_stiff;
	Elem[type].mass  = e022_mass;
	Elem[type].rvals = e022_rvals;
	Elem[type].eload = e022_eload;
	Elem[type].res_p_loc = e003_res_p_loc;
	Elem[type].res_node = e000_res_node;
	Elem[type].volume = e022_volume;
	Elem[type].therm = e000_therm;
	return(rv);
}

/* end of fem_e022.c */
