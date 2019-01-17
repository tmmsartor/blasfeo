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

#ifdef __cplusplus
extern "C" {
#endif



// headers to reference BLAS and LAPACK routines employed in BLASFEO WR

// level 1
void scopy_(int *m, float *x, int *incx, float *y, int *incy);
void saxpy_(int *m, float *alpha, float *x, int *incx, float *y, int *incy);
void sscal_(int *m, float *alpha, float *x, int *incx);
void srot_(int *m, float *x, int *incx, float *y, int *incy, float *c, float *s);
void srotg_(float *a, float *b, float *c, float *s);

// level 2
void sgemv_(char *ta, int *m, int *n, float *alpha, float *A, int *lda, float *x, int *incx, float *beta, float *y, int *incy);
void ssymv_(char *uplo, int *m, float *alpha, float *A, int *lda, float *x, int *incx, float *beta, float *y, int *incy);
void strmv_(char *uplo, char *trans, char *diag, int *n, float *A, int *lda, float *x, int *incx);
void strsv_(char *uplo, char *trans, char *diag, int *n, float *A, int *lda, float *x, int *incx);
void sger_(int *m, int *n, float *alpha, float *x, int *incx, float *y, int *incy, float *A, int *lda);

// level 3
void sgemm_(char *ta, char *tb, int *m, int *n, int *k, float *alpha, float *A, int *lda, float *B, int *ldb, float *beta, float *C, int *ldc);
void ssyrk_(char *uplo, char *trans, int *n, int *k, float *alpha, float *A, int *lda, float *beta, float *C, int *ldc);
void strmm_(char *side, char *uplo, char *transa, char *diag, int *m, int *n, float *alpha, float *A, int *lda, float *B, int *ldb);
void strsm_(char *side, char *uplo, char *transa, char *diag, int *m, int *n, float *alpha, float *A, int *lda, float *B, int *ldb);

// lapack
void spotrf_(char *uplo, int *m, float *A, int *lda, int *info);
void sgetrf_(int *m, int *n, float *A, int *lda, int *ipiv, int *info);
void sgeqrf_(int *m, int *n, float *A, int *lda, float *tau, float *work, int *lwork, int *info);
void sgeqr2_(int *m, int *n, float *A, int *lda, float *tau, float *work, int *info);
void sgelqf_(int *m, int *n, float *A, int *lda, float *tau, float *work, int *lwork, int *info);



#ifdef __cplusplus
}
#endif
