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

// TODO remove
//
void strcp_l_lib(int m, float alpha, int offsetA, float *A, int sda, int offsetB, float *B, int sdb);
void sgead_lib(int m, int n, float alpha, int offsetA, float *A, int sda, int offsetB, float *B, int sdb);
void sgetr_lib(int m, int n, float alpha, int offsetA, float *pA, int sda, int offsetC, float *pC, int sdc);
void strtr_l_lib(int m, float alpha, int offsetA, float *pA, int sda, int offsetC, float *pC, int sdc);
void strtr_u_lib(int m, float alpha, int offsetA, float *pA, int sda, int offsetC, float *pC, int sdc);
void sdiareg_lib(int kmax, float reg, int offset, float *pD, int sdd);
void sdiain_sqrt_lib(int kmax, float *x, int offset, float *pD, int sdd);
void sdiaex_lib(int kmax, float alpha, int offset, float *pD, int sdd, float *x);
void sdiaad_lib(int kmax, float alpha, float *x, int offset, float *pD, int sdd);
void sdiain_libsp(int kmax, int *idx, float alpha, float *x, float *pD, int sdd);
void sdiaex_libsp(int kmax, int *idx, float alpha, float *pD, int sdd, float *x);
void sdiaad_libsp(int kmax, int *idx, float alpha, float *x, float *pD, int sdd);
void sdiaadin_libsp(int kmax, int *idx, float alpha, float *x, float *y, float *pD, int sdd);
void srowin_lib(int kmax, float alpha, float *x, float *pD);
void srowex_lib(int kmax, float alpha, float *pD, float *x);
void srowad_lib(int kmax, float alpha, float *x, float *pD);
void srowin_libsp(int kmax, float alpha, int *idx, float *x, float *pD);
void srowad_libsp(int kmax, int *idx, float alpha, float *x, float *pD);
void srowadin_libsp(int kmax, int *idx, float alpha, float *x, float *y, float *pD);
void srowsw_lib(int kmax, float *pA, float *pC);
void scolin_lib(int kmax, float *x, int offset, float *pD, int sdd);
void scolad_lib(int kmax, float alpha, float *x, int offset, float *pD, int sdd);
void scolin_libsp(int kmax, int *idx, float *x, float *pD, int sdd);
void scolad_libsp(int kmax, float alpha, int *idx, float *x, float *pD, int sdd);
void scolsw_lib(int kmax, int offsetA, float *pA, int sda, int offsetC, float *pC, int sdc);
void svecin_libsp(int kmax, int *idx, float *x, float *y);
void svecad_libsp(int kmax, int *idx, float alpha, float *x, float *y);
