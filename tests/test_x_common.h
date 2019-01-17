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
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../include/blasfeo_common.h"

#define STR(x) #x
#define SHOW_DEFINE(x) printf("%-16s= %s\n", #x, STR(x));

#ifndef LA
	#error LA undefined
#endif

#ifndef TARGET
	#error TARGET undefined
#endif

#ifndef PRECISION
	#error PRECISION undefined
#endif

#ifndef ROUTINE
	#error ROUTINE undefined
#endif

#define concatenate(var, post) var ## post
#define string(var) STR(var)

#define REF(fun) concatenate(fun, _ref)
#define BLASFEO(fun) concatenate(blasfeo_, fun)
#define BLAS(fun) concatenate(fun, _)

#ifndef VERBOSE
#define VERBOSE 0
#endif


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// Collection of macros  and functions inteded to be used to compute compare and check matrices

#if defined(LA_HIGH_PERFORMANCE)
// Panel major element extraction macro
#define MATEL_LIBSTR(sA,ai,aj) ((sA)->pA[((ai)-((ai)&(PS-1)))*(sA)->cn+(aj)*PS+((ai)&(PS-1))])
#define MATEL_LIB(sA,ai,aj) ((sA)->pA[(ai)+(aj)*(sA)->m])
#elif defined(LA_BLAS_WRAPPER) | defined(LA_REFERENCE)
#define MATEL_LIBSTR(sA,ai,aj) ((sA)->pA[(ai)+(aj)*(sA)->m])
#else
#error : wrong LA choice
#endif

// Column major element extraction macro
//
#define VECEL_LIBSTR(sa,ai) ((sa)->pa[ai])
#define VECEL_LIB(sa,ai) ((sa)->pa[ai])

struct RoutineArgs{
	// coefficients
	REAL alpha;
	REAL beta;

	int err_i;
	int err_j;

	// sizes
	int n;
	int m;
	int k;

	// offset
	int ai;
	int aj;

	int bi;
	int bj;

	int ci;
	int cj;

	int di;
	int dj;

	// indexes arrays
	int *sipiv;
	int *ripiv;
	int *cipiv;

	// matrices
	struct STRMAT *sA;
	struct STRMAT *sA_po;
	struct STRMAT *sB;
	struct STRMAT *sC;
	struct STRMAT *sD;

	struct STRMAT_REF *rA;
	struct STRMAT_REF *rA_po;
	struct STRMAT_REF *rB;
	struct STRMAT_REF *rC;
	struct STRMAT_REF *rD;

	struct STRMAT_REF *cA;
	struct STRMAT_REF *cA_po;
	struct STRMAT_REF *cB;
	struct STRMAT_REF *cC;
	struct STRMAT_REF *cD;

	void * work;

	// blas_api
	char ta;
	char tb;
	char uplo;
};

struct TestArgs{

	// sub-mastrix offset, sweep start
	int ai0;
	int bi0;
	int di0;
	int xj0;

	// sub-mastrix offset, sweep lenght
	int ais;
	int bis;
	int dis;
	int xjs;

	// sub-matrix dimensions, sweep start
	int ni0;
	int nj0;
	int nk0;

	// sub-matrix dimensions, sweep lenght
	int nis;
	int njs;
	int nks;

	int alphas;
	int betas;

	REAL alpha_l[6];
	REAL beta_l[6];

	// blas_api parameters
	int tas;
	int tbs;
	int uplos;

	const char* ta_l[2];
	const char* tb_l[2];
	const char* uplos_l[2];

	// statistics
	int total_calls;
};

void initialize_args(struct RoutineArgs * args);
void set_test_args(struct TestArgs * targs);
int compute_total_calls(struct TestArgs * targs);
void call_routines(struct RoutineArgs *args);
void print_routine(struct RoutineArgs *args);
void print_routine_matrices(struct RoutineArgs *args);

void print_xmat_debug(
	int m, int n, struct STRMAT_REF *sA,
	int ai, int aj, int err_i, int err_j, int ERR);

void blasfeo_print_xmat_debug(
	int m, int n, struct STRMAT *sA,
	int ai, int aj, int err_i, int err_j, int ERR);

int GECMP_LIBSTR(
	int n, int m, int bi, int bj, struct STRMAT *sC,
	struct STRMAT_REF *rC, int* err_i, int* err_j, int debug);

int GECMP_BLASAPI(
	int n, int m, int bi, int bj, struct STRMAT_REF *cC,
	struct STRMAT_REF *rC, int* err_i, int* err_j, int debug);


// template base on routine class
#include string(ROUTINE_CLASS_C)
