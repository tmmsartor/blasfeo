/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS For Embedded Optimization.                                                      *
* Copyright (C) 2016-2017 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* BLASFEO is free software; you can redistribute it and/or                                        *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* BLASFEO is distributed in the hope that it will be useful,                                      *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with BLASFEO; if not, write to the Free Software                                  *
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

// BLASFEO routines
#include "../include/blasfeo_common.h"
#include "../include/blasfeo_d_blas.h"
#include "../include/blasfeo_d_kernel.h"

// External dependencies
#include "../include/blasfeo_d_aux_ext_dep.h"
#include "../include/blasfeo_i_aux_ext_dep.h"
#include "../include/blasfeo_v_aux_ext_dep.h"

// BLASFEO LA:REFERENCE routines
#include "../include/blasfeo_d_blas3_ref.h"
#include "../include/blasfeo_d_aux_ref.h"
#include "../include/blasfeo_d_aux_ext_dep_ref.h"

#define STR(x) #x
#define SHOW_DEFINE(x) printf("%s=%s\n", #x, STR(x));

#include "test_d_common.h"
#include "test_x_common.c"



#ifndef LA
	#error LA undefined
#endif

#ifndef TARGET
	#error TARGET undefined
#endif

#ifndef PRECISION
	#error PRECISION undefined
#endif

int main()
	{

	SHOW_DEFINE(LA)
	SHOW_DEFINE(TARGET)
	SHOW_DEFINE(PRECISION)

	int ii, jj, kk;
	int n = 60;
	int p_n = 15;

	/* matrices in column-major format */
	printf("Allocate C matrices\n");

	double *A, *B, *C, *D;
	// standard column major allocation (malloc)
	d_zeros(&A, n, n);
	d_zeros(&B, n, n);
	d_zeros(&C, n, n);
	d_zeros(&D, n, n);


	for(ii=0; ii<n*n; ii++) A[ii] = ii;
	for(ii=0; ii<n*n; ii++) B[ii] = 2*ii;
	for(ii=0; ii<n*n; ii++) C[ii] = 0.5*ii;


	/* instantiate blasfeo_dmat */

	printf("Allocate HP matrices\n");

	// compute memory size
	int size_dmat = 4*blasfeo_memsize_dmat(n, n);

	// initialize void pointer
	void *memory_dmat;

	// memory allocation
	v_zeros_align(&memory_dmat, size_dmat);

	// cast memory pointer
	char *ptr_memory_dmat = (char *) memory_dmat;

	// instantiate blasfeo_dmat
	struct blasfeo_dmat sA;
	struct blasfeo_dmat sB;
	struct blasfeo_dmat sC;
	struct blasfeo_dmat sD;

	blasfeo_create_dmat(n, n, &sA, ptr_memory_dmat);
	ptr_memory_dmat += sA.memsize;
	blasfeo_pack_dmat(n, n, A, n, &sA, 0, 0);

	blasfeo_create_dmat(n, n, &sB, ptr_memory_dmat);
	ptr_memory_dmat += sB.memsize;
	blasfeo_pack_dmat(n, n, B, n, &sB, 0, 0);

	blasfeo_create_dmat(n, n, &sC, ptr_memory_dmat);
	ptr_memory_dmat += sC.memsize;
	blasfeo_pack_dmat(n, n, C, n, &sC, 0, 0);

	blasfeo_create_dmat(n, n, &sD, ptr_memory_dmat);
	ptr_memory_dmat += sD.memsize;
	blasfeo_pack_dmat(n, n, D, n, &sD, 0, 0);

	printf("Allocate REF matrices\n");

	// Testing comparison
	// reference matrices, column major
	int size_dmat_ref = 4*blasfeo_memsize_dmat_ref(n, n);
	void *memory_dmat_ref;
	v_zeros_align(&memory_dmat_ref, size_dmat_ref);
	char *ptr_memory_dmat_ref = (char *) memory_dmat_ref;

	struct blasfeo_dmat_ref rA;
	blasfeo_create_dmat_ref(n, n, &rA, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += rA.memsize;
	blasfeo_pack_dmat_ref(n, n, A, n, &rA, 0, 0);

	struct blasfeo_dmat_ref rB;
	blasfeo_create_dmat_ref(n, n, &rB, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += sB.memsize;
	blasfeo_pack_dmat_ref(n, n, B, n, &rB, 0, 0);

	struct blasfeo_dmat_ref rC;
	blasfeo_create_dmat_ref(n, n, &rC, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += sC.memsize;
	blasfeo_pack_dmat_ref(n, n, C, n, &rC, 0, 0);

	struct blasfeo_dmat_ref rD;
	blasfeo_create_dmat_ref(n, n, &rD, ptr_memory_dmat_ref);
	ptr_memory_dmat_ref += sD.memsize;
	blasfeo_pack_dmat_ref(n, n, D, n, &rD, 0, 0);


	// -------- Print matrices

	/* printf("\nPrint dmat HP A:\n\n"); */
	/* blasfeo_print_dmat(p_n, p_n, &sA, 0, 0); */

	/* printf("\nPrint dmat REF A:\n\n"); */
	/* blasfeo_print_dmat_ref(p_n, p_n, &rA, 0, 0); */

	/* printf("\nPrint dmat HP B:\n\n"); */
	/* blasfeo_print_dmat(p_n, p_n, &sB, 0, 0); */

	/* printf("\nPrint dmat REF B:\n\n"); */
	/* blasfeo_print_dmat_ref(p_n, p_n, &rB, 0, 0); */

	printf("\n\n----------- TEST gemm\n\n");

	int ret, ni, nj, nk, total_calls, bad_calls;

	int ii0 = 0;
	int jj0 = 0;
	int iis = 8;
	int jjs = 8;

	int ni0 = 0;
	int nj0 = 0;
	int nk0 = 32;
	int nis = 30;
	int njs = 30;
	int nks = 1;

	double alphas[6] = {0.0, 0.0001, 0.02, 1.0, 400.0, 50000.0};
	double betas[6] = {0.0, 0.0001, 0.02, 1.0, 400.0, 50000.0};

	total_calls = nis*njs*iis*jjs;
	bad_calls = 0;

	// loop over alphas/betas
	for (kk = 0; kk < 1; kk++)
		{
		double alpha = alphas[1];
		double beta = betas[1];

		// loop over row matrix dimension
		for (ni = nj0; ni < ni0+nis; ni++)
			{

			// loop over column matrix dimension
			for (nj = nj0; nj < nj0+njs; nj++)
				{

				// loop over column matrix dimension
				for (nk = nk0; nk < nk0+nks; nk++)
					{
					// loop over row offset
					for (ii = ii0; ii < ii0+iis; ii++)
						{

						// loop over column offset
						for (jj = jj0; jj < jj0+jjs; jj++)
							{


							// gemm_nn D <- alpha*A*B + beta*C
							blasfeo_dgemm_nn(ni, nj, nk, alpha, &sA, ii, jj, &sB, ii, jj, beta, &sC, ii, jj, &sD, ii, jj);
							blasfeo_dgemm_nn_ref(ni, nj, nk, alpha, &rA, ii, jj, &rB, ii, jj, beta, &rC, ii, jj, &rD, ii, jj);

							/* assert(dgecmp_libstr(ni, nj, &sD, &rD, &sA, &rA)); */
							int res = dgecmp_libstr(ni, nj, &sD, &rD, &sA, &rA, 0);
							if (!res)
								{
								bad_calls += 1;
								printf(
									"Mismatch at D[%d:%d,%d:%d] =  %f*A[%d:%d,%d:%d]*B[%d:%d,%d:%d] + %f*C[%d:%d,%d:%d]\n",
									ii, ni, jj, nj,
									alpha, ii, ni, jj, nk,
									ii, nk, jj, nj,
									beta, ii, ni, jj, nj);
								}
							else
								{
								printf(
									"Correct at D[%d:%d,%d:%d] =  %f*A[%d:%d,%d:%d]*B[%d:%d,%d:%d] + %f*C[%d:%d,%d:%d]\n",
									ii, ni, jj, nj,
									alpha, ii, ni, jj, nk,
									ii, nk, jj, nj,
									beta, ii, ni, jj, nj);
								}
							}
						}
					}
				}
			}
		printf("\n");
		}

	printf("\n----------- END TEST gemm\n");

	if (!bad_calls)
		{
			printf("\n----------- TEST SUCCEEDED\n\n");
		}
	else
		{
			printf("\n----------- TEST FAILED, %d/%d bad_calls\n\n", bad_calls, total_calls);
		}

	SHOW_DEFINE(LA)
	SHOW_DEFINE(TARGET)
	SHOW_DEFINE(PRECISION)

	d_free(A);
	d_free(B);
	d_free(C);
	d_free(D);

	blasfeo_free_dmat(&sA);
	blasfeo_free_dmat(&sB);
	blasfeo_free_dmat(&sC);
	blasfeo_free_dmat(&sD);

	blasfeo_free_dmat_ref(&rA);
	blasfeo_free_dmat_ref(&rB);
	blasfeo_free_dmat_ref(&rC);
	blasfeo_free_dmat_ref(&rD);

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
