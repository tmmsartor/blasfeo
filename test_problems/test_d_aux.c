/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS For Embedded Optimization.                                                      *
* Copyright (C) 2016-2017 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* HPMPC is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPMPC is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPMPC; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, giaf (at) dtu.dk                                                       *
*                          gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/



#if defined(TESTING_MODE)



// standard
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
// BLASFEO
#include "../include/blasfeo_common.h"
#include "../include/blasfeo_d_aux_ext_dep.h"
#include "../include/blasfeo_d_aux.h"
#include "../include/blasfeo_i_aux_ext_dep.h"
#include "../include/blasfeo_v_aux_ext_dep.h"
#include "../include/blasfeo_d_kernel.h"
#include "../include/blasfeo_d_blas.h"
// reference BLASFEO for testing
#include "../include/blasfeo_d_aux_ref.h"
#include "../include/blasfeo_d_aux_ext_dep_ref.h"

#define STR(x) #x
#define SHOW_DEFINE(x) printf("%s=%s\n", #x, STR(x));

#include "test_d_common.h"
#include "test_x_common.c"



int main()
	{

#ifndef LA
	#error LA undefined
#endif

#ifndef TARGET
	#error TARGET undefined
#endif

#ifndef PRECISION
	#error PRECISION undefined
#endif


SHOW_DEFINE(LA)
SHOW_DEFINE(TARGET)
SHOW_DEFINE(PRECISION)


	int ii, jj;

	int n = 21;
	int p_n = 15;
	int N = 10;

	//
	// matrices in column-major format
	//
	double *A;
	// standard column major allocation (malloc)
	d_zeros(&A, n, n);
	for(ii=0; ii<n*n; ii++) A[ii] = ii;

	double *B;
	// standard column major allocation (malloc)
	d_zeros(&B, n, n);
	for(ii=0; ii<n*n; ii++) B[ii] = 2*ii;

	// standard column major allocation (malloc)
	double *C;
	d_zeros(&C, n, n);

	/* -------- instantiate blasfeo_dmat */

	// compute memory size
	int size_dmat = 2*blasfeo_memsize_dmat(n, n);
	int size_dmat_ref = 2*blasfeo_memsize_dmat_ref(n, n);
	// inizilize void pointer
	void *memory_dmat;
	void *memory_dmat_ref;

	// initialize pointer
	// memory allocation
	v_zeros_align(&memory_dmat, size_dmat);
	v_zeros_align(&memory_dmat_ref, size_dmat_ref);

	// get point to dmat
	char *ptr_memory_dmat = (char *) memory_dmat;
	char *ptr_memory_dmat_ref = (char *) memory_dmat_ref;

	// instantiate blasfeo_dmat
	struct blasfeo_dmat sA;
	blasfeo_create_dmat(n, n, &sA, ptr_memory_dmat);
	ptr_memory_dmat += sA.memsize;
	blasfeo_pack_dmat(n, n, A, n, &sA, 0, 0);

	struct blasfeo_dmat sB;
	blasfeo_create_dmat(n, n, &sB, ptr_memory_dmat);
	ptr_memory_dmat += sB.memsize;
	blasfeo_pack_dmat(n, n, B, n, &sB, 0, 0);

	// Testing comparison
	// reference matrices, column major

	struct blasfeo_dmat_ref rA;
	blasfeo_create_dmat_ref(n, n, &rA, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += rA.memsize;
	blasfeo_pack_dmat_ref(n, n, A, n, &rA, 0, 0);

	struct blasfeo_dmat_ref rB;
	blasfeo_create_dmat_ref(n, n, &rB, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += sB.memsize;
	blasfeo_pack_dmat_ref(n, n, B, n, &rB, 0, 0);


	// -------- Print matrices

	printf("\nPrint dmat HP A:\n\n");
	blasfeo_print_dmat(p_n, p_n, &sA, 0, 0);

	printf("\nPrint dmat REF A:\n\n");
	blasfeo_print_dmat_ref(p_n, p_n, &rA, 0, 0);

	printf("\nPrint dmat HP B:\n\n");
	blasfeo_print_dmat(p_n, p_n, &sB, 0, 0);

	printf("\nPrint dmat REF B:\n\n");
	blasfeo_print_dmat_ref(p_n, p_n, &rB, 0, 0);

	printf("\n\n----------- TEST Copy&Scale\n\n");

	double alpha;
	alpha = 1.5;
	int ret, ni, mi;
	ni = 12;
	mi = 10;

	printf("Compute different combinations of submatrix offsets\n\n");

	// loop over A offset
	for (ii = 0; ii < 8; ii++)
		{

		// ---- Scale
		//
		printf("Scale A[%d:%d,%d:%d] by %f\n",
						ii,ni, 0,mi,    alpha);

		blasfeo_dgesc(     ni, mi, alpha, &sA, ii, 0);
		blasfeo_dgesc_ref(ni, mi, alpha, &rA, ii, 0);

		/* printf("value 0,1: %f", MATEL_LIBSTR(&sA, 0,1)); */
		/* printf("PS:%d", PS); */

		assert(dgecmp_libstr(n, n, &sA, &rA, &sA, &rA, 1));

		// loop over B offset
		for (jj = 0; jj < 8; jj++)
			{

			// ---- Copy&Scale
			//

			printf("Copy-Scale A[%d:%d,%d:%d] by %f in B[%d:%d,%d:%d]\n",
							     ii,ni, 0,mi,    alpha,  jj,ni, 0,mi);

			// HP submatrix copy&scale
			blasfeo_dgecpsc(ni, mi, alpha, &sA, ii, 0, &sB, jj, 0);
			// REF submatrix copy&scale
			blasfeo_dgecpsc_ref(ni, mi, alpha, &rA, ii, 0, &rB, jj, 0);
			// check against blas with blasfeo REF
			assert(dgecmp_libstr(n, n, &sB, &rB, &sA, &rA, 1));

			// ---- Copy
			//
			printf("Copy A[%d:%d,%d:%d] in B[%d:%d,%d:%d]\n",
							ii,ni, 0,mi,     jj,ni, 0,mi);

			blasfeo_dgecp(     ni, mi, &sA, ii, 0, &sB, jj, 0);
			blasfeo_dgecp_ref(ni, mi, &rA, ii, 0, &rB, jj, 0);
			assert(dgecmp_libstr(n, n, &sB, &rB, &sA, &rA, 1));

			printf("\n");
			}

		printf("\n");
		}

	printf("\n----------- END TEST Copy&Scale\n");

	printf("\n----------- TEST SUCCEEDED\n\n");

	SHOW_DEFINE(LA)
	SHOW_DEFINE(TARGET)
	SHOW_DEFINE(PRECISION)

	printf("\n\n");

	return 0;

	}



#else



#include <stdio.h>

int main()
	{
	printf("\n\n Recompile BLASFEO with TESTING_MODE=1 to run this test.\n\n");
	return 0;
	}



#endif
