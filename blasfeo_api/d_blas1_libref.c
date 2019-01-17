/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS For Embedded Optimization.                                                      *
* Copyright (C) 2016-2018 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* This program is free software: you can redistribute it and/or modify                            *
* it under the terms of the GNU General Public License as published by                            *
* the Free Software Foundation, either version 3 of the License, or                               *
* (at your option) any later version                                                              *.
*                                                                                                 *
* This program is distributed in the hope that it will be useful,                                 *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                   *
* GNU General Public License for more details.                                                    *
*                                                                                                 *
* You should have received a copy of the GNU General Public License                               *
* along with this program.  If not, see <https://www.gnu.org/licenses/>.                          *
*                                                                                                 *
* The authors designate this particular file as subject to the "Classpath" exception              *
* as provided by the authors in the LICENSE file that accompained this code.                      *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FABS fabs
#define SQRT sqrt

#include "../include/blasfeo_common.h"
#include "../include/blasfeo_d_kernel.h"



#define REAL double

#define STRMAT blasfeo_dmat_ref
#define STRVEC blasfeo_dvec_ref

#define AXPY_LIBSTR blasfeo_daxpy_ref
#define AXPBY_LIBSTR blasfeo_daxpby_ref
#define VECMUL_LIBSTR blasfeo_dvecmul_ref
#define VECMULACC_LIBSTR blasfeo_dvecmulacc_ref
#define VECMULDOT_LIBSTR blasfeo_dvecmuldot_ref
#define DOT_LIBSTR blasfeo_ddot_ref
#define ROTG_LIBSTR blasfeo_drotg_ref
#define COLROT_LIBSTR blasfeo_dcolrot_ref
#define ROWROT_LIBSTR blasfeo_drowrot_ref

#include "x_blas1_lib.c"
