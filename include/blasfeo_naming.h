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


/*
 * ----------- Naming conventions
 *
 *  blasfeo_(precision)(data-type)(operation)[_(options)]
 *
 * 1)
 *    d(double)
 *    s(single)
 *
 * 2)
 *    ge  (general)
 *    tr  (triangular)
 *    vec (vector)
 *    row (row)
 *    col (column)
 *    dia (diagonal)
 *    sy  (symmetric)
 *    syrk (symmetric rank-k)
 *
 * 3)
 *    * blas
 *    mm (matrix-matrix multiplication)
 *    mv (matrix-vector multiplication)
 *    sm (solve matrix)
 *    sm (solve vector)
 *
 *    * aux
 *    se (set)
 *    cp (copy)
 *    sc (scale)
 *    ad (add)
 *    tr (transpose)
 *    in (insert)
 *    ex (extract)
 *    pe (premute)
 *    sw (swap)
 *
 *    * lapack
 *    lqf (LQ factorization)
 *    qrf (QR factorization)
 *    trf (LU factorization using partial pivoting with row interchanges)
 *
 * 4) options
 *    l         (lower)
 *    u         (upper)
 *    d         (diagonal)
 *    n         (non-trasposed)
 *    t         (trasposed)
 *    sp        (sparse)
 *    nopivot
 *    rowpivot
 *    worksize  (return worksize in bytes)
 */
