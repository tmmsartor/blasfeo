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



#if defined(LA_REFERENCE) | defined(LA_BLAS_WRAPPER) | defined(TESTING_MODE)



// dgemm with A diagonal matrix (stored as strvec)
void GEMM_L_DIAG_LIBSTR(int m, int n, REAL alpha, struct STRVEC *sA, int ai, struct STRMAT *sB, int bi, int bj, REAL beta, struct STRMAT *sC, int ci, int cj, struct STRMAT *sD, int di, int dj)
	{
	if(m<=0 | n<=0)
		return;

	// invalidate stored inverse diagonal of result matrix
	sD->use_dA = 0;

	int ii, jj;
	int ldb = sB->m;
	int ldd = sD->m;
	REAL *dA = sA->pa + ai;
	REAL *pB = sB->pA + bi + bj*ldb;
	REAL *pD = sD->pA + di + dj*ldd;
	REAL a0, a1;
	if(beta==0.0)
		{
		ii = 0;
		for(; ii<m-1; ii+=2)
			{
			a0 = alpha * dA[ii+0];
			a1 = alpha * dA[ii+1];
			for(jj=0; jj<n; jj++)
				{
				pD[ii+0+ldd*jj] = a0 * pB[ii+0+ldb*jj];
				pD[ii+1+ldd*jj] = a1 * pB[ii+1+ldb*jj];
				}
			}
		for(; ii<m; ii++)
			{
			a0 = alpha * dA[ii];
			for(jj=0; jj<n; jj++)
				{
				pD[ii+0+ldd*jj] = a0 * pB[ii+0+ldb*jj];
				}
			}
		}
	else
		{
		int ldc = sC->m;
		REAL *pC = sC->pA + ci + cj*ldc;
		ii = 0;
		for(; ii<m-1; ii+=2)
			{
			a0 = alpha * dA[ii+0];
			a1 = alpha * dA[ii+1];
			for(jj=0; jj<n; jj++)
				{
				pD[ii+0+ldd*jj] = a0 * pB[ii+0+ldb*jj] + beta * pC[ii+0+ldc*jj];
				pD[ii+1+ldd*jj] = a1 * pB[ii+1+ldb*jj] + beta * pC[ii+1+ldc*jj];
				}
			}
		for(; ii<m; ii++)
			{
			a0 = alpha * dA[ii];
			for(jj=0; jj<n; jj++)
				{
				pD[ii+0+ldd*jj] = a0 * pB[ii+0+ldb*jj] + beta * pC[ii+0+ldc*jj];
				}
			}
		}
	return;
	}



// dgemm with B diagonal matrix (stored as strvec)
void GEMM_R_DIAG_LIBSTR(int m, int n, REAL alpha, struct STRMAT *sA, int ai, int aj, struct STRVEC *sB, int bi, REAL beta, struct STRMAT *sC, int ci, int cj, struct STRMAT *sD, int di, int dj)
	{
	if(m<=0 | n<=0)
		return;

	// invalidate stored inverse diagonal of result matrix
	sD->use_dA = 0;

	int ii, jj;
	int lda = sA->m;
	int ldd = sD->m;
	REAL *pA = sA->pA + ai + aj*lda;
	REAL *dB = sB->pa + bi;
	REAL *pD = sD->pA + di + dj*ldd;
	REAL a0, a1;
	if(beta==0.0)
		{
		jj = 0;
		for(; jj<n-1; jj+=2)
			{
			a0 = alpha * dB[jj+0];
			a1 = alpha * dB[jj+1];
			for(ii=0; ii<m; ii++)
				{
				pD[ii+ldd*(jj+0)] = a0 * pA[ii+lda*(jj+0)];
				pD[ii+ldd*(jj+1)] = a1 * pA[ii+lda*(jj+1)];
				}
			}
		for(; jj<n; jj++)
			{
			a0 = alpha * dB[jj+0];
			for(ii=0; ii<m; ii++)
				{
				pD[ii+ldd*(jj+0)] = a0 * pA[ii+lda*(jj+0)];
				}
			}
		}
	else
		{
		int ldc = sC->m;
		REAL *pC = sC->pA + ci + cj*ldc;
		jj = 0;
		for(; jj<n-1; jj+=2)
			{
			a0 = alpha * dB[jj+0];
			a1 = alpha * dB[jj+1];
			for(ii=0; ii<m; ii++)
				{
				pD[ii+ldd*(jj+0)] = a0 * pA[ii+lda*(jj+0)] + beta * pC[ii+ldc*(jj+0)];
				pD[ii+ldd*(jj+1)] = a1 * pA[ii+lda*(jj+1)] + beta * pC[ii+ldc*(jj+1)];
				}
			}
		for(; jj<n; jj++)
			{
			a0 = alpha * dB[jj+0];
			for(ii=0; ii<m; ii++)
				{
				pD[ii+ldd*(jj+0)] = a0 * pA[ii+lda*(jj+0)] + beta * pC[ii+ldc*(jj+0)];
				}
			}
		}
	return;
	}



#else

#error : wrong LA choice

#endif





