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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#if defined(LA_BLAS_WRAPPER)
#if defined(REF_BLAS_BLIS)
#include "d_blas_64.h"
#elif defined(REF_BLAS_MKL)
#include "mkl.h"
#else
#include "d_blas.h"
#endif
#endif

#include "../include/blasfeo_common.h"
#include "../include/blasfeo_d_aux.h"



#define REAL double

#define STRMAT blasfeo_dmat
#define STRVEC blasfeo_dvec

#define GELQF_PD_DA_LIBSTR blasfeo_dgelqf_pd_da
#define GELQF_PD_LA_LIBSTR blasfeo_dgelqf_pd_la
#define GELQF_PD_LLA_LIBSTR blasfeo_dgelqf_pd_lla
#define GELQF_PD_LIBSTR blasfeo_dgelqf_pd
#define GELQF_LIBSTR blasfeo_dgelqf
#define GELQF_WORK_SIZE_LIBSTR blasfeo_dgelqf_worksize
#define GEQRF_LIBSTR blasfeo_dgeqrf
#define GEQRF_WORK_SIZE_LIBSTR blasfeo_dgeqrf_worksize
#define GETF2_NOPIVOT dgetf2_nopivot
#define GETRF_NOPIVOT_LIBSTR blasfeo_dgetrf_nopivot
#define GETRF_LIBSTR blasfeo_dgetrf_rowpivot
#define POTRF_L_LIBSTR blasfeo_dpotrf_l
#define POTRF_L_MN_LIBSTR blasfeo_dpotrf_l_mn
#define PSTRF_L_LIBSTR dpstrf_l_libstr
#define SYRK_POTRF_LN_LIBSTR blasfeo_dsyrk_dpotrf_ln

#define COPY dcopy_
#define GELQF dgelqf_
#define GEMM dgemm_
#define GER dger_
#define GEQRF dgeqrf_
#define GEQR2 dgeqr2_
#define GETRF dgetrf_
#define POTRF dpotrf_
#define SCAL dscal_
#define SYRK dsyrk_
#define TRSM dtrsm_


#include "x_lapack_lib.c"
