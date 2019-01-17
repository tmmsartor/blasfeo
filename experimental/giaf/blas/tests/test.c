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

#include "../include/blasfeo_d_blas.h"

#include "../../../../include/blasfeo_target.h"
#include "../../../../include/blasfeo_common.h"
#include "../../../../include/blasfeo_timing.h"
#include "../../../../include/blasfeo_d_aux.h"
#include "../../../../include/blasfeo_d_aux_ext_dep.h"
#include "../../../../include/blasfeo_d_kernel.h"


int main()
	{

	int n = 16;

	int ii;

	double *A = malloc(n*n*sizeof(double));
	for(ii=0; ii<n*n; ii++)
		A[ii] = ii;
	int lda = n;
//	d_print_mat(n, n, A, n);

	double *B = malloc(n*n*sizeof(double));
	for(ii=0; ii<n*n; ii++)
		B[ii] = 0;
	for(ii=0; ii<n; ii++)
		B[ii*(n+1)] = 1.0;
	int ldb = n;
//	d_print_mat(n, n, B, ldb);

	double *C = malloc(n*n*sizeof(double));
	for(ii=0; ii<n*n; ii++)
		C[ii] = -1;
	int ldc = n;
//	d_print_mat(n, n, C, ldc);

	double *D = malloc(n*n*sizeof(double));
	for(ii=0; ii<n*n; ii++)
		D[ii] = -1;
	int ldd = n;
//	d_print_mat(n, n, C, ldc);


	int bs = 4;

	struct blasfeo_dmat sA; blasfeo_allocate_dmat(n, n, &sA);
	blasfeo_pack_dmat(n, n, A, n, &sA, 0, 0);
	int sda = sA.cn;
	struct blasfeo_dmat sB; blasfeo_allocate_dmat(n, n, &sB);
	blasfeo_pack_dmat(n, n, B, n, &sB, 0, 0);
	int sdb = sB.cn;
	struct blasfeo_dmat sC; blasfeo_allocate_dmat(n, n, &sC);
	blasfeo_pack_dmat(n, n, C, n, &sC, 0, 0);
	int sdc = sC.cn;
	struct blasfeo_dmat sD; blasfeo_allocate_dmat(n, n, &sD);
	blasfeo_pack_dmat(n, n, D, n, &sD, 0, 0);
	int sdd = sD.cn;



	double alpha = 1.0;
	double beta = 1.0;

	char ta = 'n';
	char tb = 't';
	char uplo = 'l';
	int info = 0;

	int m0 = 7;
	int n0 = 7;
	int k0 = 7;


	// blas

	for(ii=0; ii<n*n; ii++) C[ii] = -1;

	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
//	dgemm_(&ta, &tb, &m0, &n0, &k0, &alpha, A, &n, A, &n, &beta, C, &n);
	dgemm_(&ta, &tb, &n, &n, &n, &alpha, A, &n, A, &n, &beta, C, &n);
	dpotrf_(&uplo, &m0, C, &n, &info);

	d_print_mat(n, n, C, ldc);
//	d_print_mat(n, n, D, ldd);


	// blasfeo blas

	for(ii=0; ii<n*n; ii++) C[ii] = -1;

	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
//	blasfeo_dgemm(&ta, &tb, &m0, &n0, &k0, &alpha, A, &n, A, &n, &beta, C, &n);
	blasfeo_dgemm(&ta, &tb, &n, &n, &n, &alpha, A, &n, A, &n, &beta, C, &n);
	blasfeo_dpotrf(&uplo, &m0, C, &n);

	d_print_mat(n, n, C, ldc);
//	d_print_mat(n, n, D, ldd);


	// free memory

	free(A);
	free(B);
	free(C);
	free(D);
	blasfeo_free_dmat(&sA);
	blasfeo_free_dmat(&sB);
	blasfeo_free_dmat(&sC);
	blasfeo_free_dmat(&sD);


	// return

	return 0;

	}
