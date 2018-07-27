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



#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_n_4_gen_lib4(int kmax, double *alpha, double *A, double *x, double *beta, double *y, double *z, int k0, int k1)
	{

	const int bs = 4;

	int k;

	double
		x_0,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	for(; k<kmax-3; k+=4)
		{

		x_0 = x[0];

		y_0 += A[0+bs*0] * x_0;
		y_1 += A[1+bs*0] * x_0;
		y_2 += A[2+bs*0] * x_0;
		y_3 += A[3+bs*0] * x_0;
		
		x_0 = x[1];

		y_0 += A[0+bs*1] * x_0;
		y_1 += A[1+bs*1] * x_0;
		y_2 += A[2+bs*1] * x_0;
		y_3 += A[3+bs*1] * x_0;
		
		x_0 = x[2];

		y_0 += A[0+bs*2] * x_0;
		y_1 += A[1+bs*2] * x_0;
		y_2 += A[2+bs*2] * x_0;
		y_3 += A[3+bs*2] * x_0;
		
		x_0 = x[3];

		y_0 += A[0+bs*3] * x_0;
		y_1 += A[1+bs*3] * x_0;
		y_2 += A[2+bs*3] * x_0;
		y_3 += A[3+bs*3] * x_0;
		
		A += 4*bs;
		x += 4;

		}

	for(; k<kmax; k++)
		{

		x_0 = x[0];

		y_0 += A[0+bs*0] * x_0;
		y_1 += A[1+bs*0] * x_0;
		y_2 += A[2+bs*0] * x_0;
		y_3 += A[3+bs*0] * x_0;
		
		A += 1*bs;
		x += 1;

		}

	y_0 = alpha[0]*y_0 + beta[0]*y[0];
	y_1 = alpha[0]*y_1 + beta[0]*y[1];
	y_2 = alpha[0]*y_2 + beta[0]*y[2];
	y_3 = alpha[0]*y_3 + beta[0]*y[3];

	if(k0<=0 & k1>3)
		{
		z[0] = y_0;
		z[1] = y_1;
		z[2] = y_2;
		z[3] = y_3;
		}
	else
		{
		if(k0<=0 & k1>0) z[0] = y_0;
		if(k0<=1 & k1>1) z[1] = y_1;
		if(k0<=2 & k1>2) z[2] = y_2;
		if(k0<=3 & k1>3) z[3] = y_3;
		}

	}
#endif
	
	
	

#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_n_4_vs_lib4(int kmax, double *alpha, double *A, double *x, double *beta, double *y, double *z, int k1)
	{

	kernel_dgemv_n_4_gen_lib4(kmax, alpha, A, x, beta, y, z, 0, k1);

	}
#endif



#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_n_4_lib4(int kmax, double *alpha, double *A, double *x, double *beta, double *y, double *z)
	{

	kernel_dgemv_n_4_gen_lib4(kmax, alpha, A, x, beta, y, z, 0, 4);

	}
#endif



#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_t_4_gen_lib4(int kmax, double *alpha, int offA, double *A, int sda, double *x, double *beta, double *y, double *z, int km)
	{

	const int bs  = 4;
	
	int k, kend;
	
	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	if(offA!=0) // 1, 2, 3
		{
		kend = 4-offA<kmax ? 4-offA : kmax;
		for(; k<kend; k++)
			{
			
			x_0 = x[0];
		
			y_0 += A[0+bs*0] * x_0;
			y_1 += A[0+bs*1] * x_0;
			y_2 += A[0+bs*2] * x_0;
			y_3 += A[0+bs*3] * x_0;
		
			A += 1;
			x += 1;
			
			}
		A += bs*(sda-1);
		}
	for(; k<kmax-bs+1; k+=bs)
		{
		
		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];
		
		y_0 += A[0+bs*0] * x_0;
		y_1 += A[0+bs*1] * x_0;
		y_2 += A[0+bs*2] * x_0;
		y_3 += A[0+bs*3] * x_0;

		y_0 += A[1+bs*0] * x_1;
		y_1 += A[1+bs*1] * x_1;
		y_2 += A[1+bs*2] * x_1;
		y_3 += A[1+bs*3] * x_1;
		
		y_0 += A[2+bs*0] * x_2;
		y_1 += A[2+bs*1] * x_2;
		y_2 += A[2+bs*2] * x_2;
		y_3 += A[2+bs*3] * x_2;

		y_0 += A[3+bs*0] * x_3;
		y_1 += A[3+bs*1] * x_3;
		y_2 += A[3+bs*2] * x_3;
		y_3 += A[3+bs*3] * x_3;
		
		A += sda*bs;
		x += 4;

		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
	
		y_0 += A[0+bs*0] * x_0;
		y_1 += A[0+bs*1] * x_0;
		y_2 += A[0+bs*2] * x_0;
		y_3 += A[0+bs*3] * x_0;
	
		A += 1;
		x += 1;
		
		}

	y_0 = alpha[0]*y_0 + beta[0]*y[0];
	y_1 = alpha[0]*y_1 + beta[0]*y[1];
	y_2 = alpha[0]*y_2 + beta[0]*y[2];
	y_3 = alpha[0]*y_3 + beta[0]*y[3];

	if(km>=4)
		{
		z[0] = y_0;
		z[1] = y_1;
		z[2] = y_2;
		z[3] = y_3;
		}
	else
		{
		z[0] = y_0;
		if(km>=2)
			{
			z[1] = y_1;
			if(km>2)
				{
				z[2] = y_2;
				}
			}
		}

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_t_4_lib4(int kmax, double *alpha, double *A, int sda, double *x, double *beta, double *y, double *z)
	{

	kernel_dgemv_t_4_gen_lib4(kmax, alpha, 0, A, sda, x, beta, y, z, 4);

	}
#endif




#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dgemv_t_4_vs_lib4(int kmax, double *alpha, double *A, int sda, double *x, double *beta, double *y, double *z, int k1)
	{

	kernel_dgemv_t_4_gen_lib4(kmax, alpha, 0, A, sda, x, beta, y, z, k1);

	}
#endif




#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ln_inv_4_vs_lib4(int kmax, double *A, double *inv_diag_A, double *x, double *y, double *z, int km, int kn)
	{

	const int bs = 4;
	
	int k;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	for(; k<kmax-3; k+=4)
		{

		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[1+bs*0] * x_0;
		y_2 -= A[2+bs*0] * x_0;
		y_3 -= A[3+bs*0] * x_0;

		y_0 -= A[0+bs*1] * x_1;
		y_1 -= A[1+bs*1] * x_1;
		y_2 -= A[2+bs*1] * x_1;
		y_3 -= A[3+bs*1] * x_1;

		y_0 -= A[0+bs*2] * x_2;
		y_1 -= A[1+bs*2] * x_2;
		y_2 -= A[2+bs*2] * x_2;
		y_3 -= A[3+bs*2] * x_2;

		y_0 -= A[0+bs*3] * x_3;
		y_1 -= A[1+bs*3] * x_3;
		y_2 -= A[2+bs*3] * x_3;
		y_3 -= A[3+bs*3] * x_3;
		
		A += 4*bs;
		x += 4;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	double
		a_00, a_10, a_20, a_30,
		a_11, a_21, a_31;
	
	// a_00
	a_00 = inv_diag_A[0];
	a_10 = A[1+bs*0];
	a_20 = A[2+bs*0];
	a_30 = A[3+bs*0];
	y_0 *= a_00;
	z[0] = y_0;
	y_1 -= a_10 * y_0;
	y_2 -= a_20 * y_0;
	y_3 -= a_30 * y_0;

	if(kn==1)
		{
		if(km==1)
			return;
		y[1] = y_1;
		if(km==2)
			return;
		y[2] = y_2;
		if(km==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_11
	a_11 = inv_diag_A[1];
	a_21 = A[2+bs*1];
	a_31 = A[3+bs*1];
	y_1 *= a_11;	
	z[1] = y_1;
	y_2 -= a_21 * y_1;
	y_3 -= a_31 * y_1;

	if(kn==2)
		{
		if(km==2)
			return;
		y[2] = y_2;
		if(km==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_22
	a_00 = inv_diag_A[2];
	a_10 = A[3+bs*2];
	y_2 *= a_00;
	z[2] = y_2;
	y_3 -= a_10 * y_2;

	if(kn==3)
		{
		if(km==3)
			return;
		y[3] = y_3;

		return;
		}

	// a_33
	a_11 = inv_diag_A[3];
	y_3 *= a_11;	
	z[3] = y_3;

	}
#endif
	

	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ln_inv_4_lib4(int kmax, double *A, double *inv_diag_A, double *x, double *y, double *z)
	{

	kernel_dtrsv_ln_inv_4_vs_lib4(kmax, A, inv_diag_A, x, y, z, 4, 4);

	return;

	}
#endif
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ln_one_4_vs_lib4(int kmax, double *A, double *x, double *y, double *z, int km, int kn)
	{

	const int bs = 4;
	
	int k;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	for(; k<kmax-3; k+=4)
		{

		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[1+bs*0] * x_0;
		y_2 -= A[2+bs*0] * x_0;
		y_3 -= A[3+bs*0] * x_0;

		y_0 -= A[0+bs*1] * x_1;
		y_1 -= A[1+bs*1] * x_1;
		y_2 -= A[2+bs*1] * x_1;
		y_3 -= A[3+bs*1] * x_1;

		y_0 -= A[0+bs*2] * x_2;
		y_1 -= A[1+bs*2] * x_2;
		y_2 -= A[2+bs*2] * x_2;
		y_3 -= A[3+bs*2] * x_2;

		y_0 -= A[0+bs*3] * x_3;
		y_1 -= A[1+bs*3] * x_3;
		y_2 -= A[2+bs*3] * x_3;
		y_3 -= A[3+bs*3] * x_3;
		
		A += 4*bs;
		x += 4;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	double
		a_00, a_10, a_20, a_30,
		a_11, a_21, a_31;
	
	// a_00
//	a_00 = 1.0;
	a_10 = A[1+bs*0];
	a_20 = A[2+bs*0];
	a_30 = A[3+bs*0];
//	y_0 *= a_00;
	z[0] = y_0;
	y_1 -= a_10 * y_0;
	y_2 -= a_20 * y_0;
	y_3 -= a_30 * y_0;

	if(kn==1)
		{
		if(km==1)
			return;
		y[1] = y_1;
		if(km==2)
			return;
		y[2] = y_2;
		if(km==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_11
//	a_11 = 1.0;
	a_21 = A[2+bs*1];
	a_31 = A[3+bs*1];
//	y_1 *= a_11;	
	z[1] = y_1;
	y_2 -= a_21 * y_1;
	y_3 -= a_31 * y_1;

	if(kn==2)
		{
		if(km==2)
			return;
		y[2] = y_2;
		if(km==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_22
//	a_00 = 1.0;
	a_10 = A[3+bs*2];
//	y_2 *= a_00;
	z[2] = y_2;
	y_3 -= a_10 * y_2;

	if(kn==3)
		{
		if(km==3)
			return;
		y[3] = y_3;

		return;
		}

	// a_33
//	a_11 = 1.0;
//	y_3 *= a_11;	
	z[3] = y_3;

	}
#endif
	

	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ln_one_4_lib4(int kmax, double *A, double *x, double *y, double *z)
	{

	kernel_dtrsv_ln_one_4_vs_lib4(kmax, A, x, y, z, 4, 4);


	}
#endif
	
	
		
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_inv_4_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=4;
	A += 4 + (sda-1)*bs;
	x += 4;
	for(; k<kmax-3; k+=4)
		{
		
		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		y_3 -= A[0+bs*3] * x_0;

		y_0 -= A[1+bs*0] * x_1;
		y_1 -= A[1+bs*1] * x_1;
		y_2 -= A[1+bs*2] * x_1;
		y_3 -= A[1+bs*3] * x_1;
		
		y_0 -= A[2+bs*0] * x_2;
		y_1 -= A[2+bs*1] * x_2;
		y_2 -= A[2+bs*2] * x_2;
		y_3 -= A[2+bs*3] * x_2;

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;
		y_2 -= A[3+bs*2] * x_3;
		y_3 -= A[3+bs*3] * x_3;
		
		A += sda*bs;
		x += 4;

		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		y_3 -= A[0+bs*3] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}
	
	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	A = tA;
	x = tx;

	// bottom trinagle
	y_3 *= inv_diag_A[3];
	z[3] = y_3;

	y_2 -= A[3+bs*2] * y_3;
	y_2 *= inv_diag_A[2];
	z[2] = y_2;

	// square
	y_0 -= A[2+bs*0]*y_2 + A[3+bs*0]*y_3;
	y_1 -= A[2+bs*1]*y_2 + A[3+bs*1]*y_3;
		
	// top trinagle
	y_1 *= inv_diag_A[1];
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	y_0 *= inv_diag_A[0];
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_inv_3_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0;
	
	k = 3;
	if(kmax>4)
		{
		// clean up at the beginning
		x_3 = x[3];

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;
		y_2 -= A[3+bs*2] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_1 -= A[0+bs*1] * x_0;
			y_2 -= A[0+bs*2] * x_0;

			y_0 -= A[1+bs*0] * x_1;
			y_1 -= A[1+bs*1] * x_1;
			y_2 -= A[1+bs*2] * x_1;
			
			y_0 -= A[2+bs*0] * x_2;
			y_1 -= A[2+bs*1] * x_2;
			y_2 -= A[2+bs*2] * x_2;

			y_0 -= A[3+bs*0] * x_3;
			y_1 -= A[3+bs*1] * x_3;
			y_2 -= A[3+bs*2] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 3;
		x += 1;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;

	A = tA;
	x = tx;

	// bottom trinagle
	y_2 *= inv_diag_A[2];
	z[2] = y_2;

	// square
	y_0 -= A[2+bs*0]*y_2;
	y_1 -= A[2+bs*1]*y_2;
		
	// top trinagle
	y_1 *= inv_diag_A[1];
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	y_0 *= inv_diag_A[0];
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_inv_2_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0;
	
	k = 2;
	if(kmax>4)
		{
		// clean up at the beginning
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[2+bs*0] * x_2;
		y_1 -= A[2+bs*1] * x_2;

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_1 -= A[0+bs*1] * x_0;

			y_0 -= A[1+bs*0] * x_1;
			y_1 -= A[1+bs*1] * x_1;
			
			y_0 -= A[2+bs*0] * x_2;
			y_1 -= A[2+bs*1] * x_2;

			y_0 -= A[3+bs*0] * x_3;
			y_1 -= A[3+bs*1] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 2;
		x += 2;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;

	A = tA;
	x = tx;

	// top trinagle
	y_1 *= inv_diag_A[1];
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	y_0 *= inv_diag_A[0];
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_inv_1_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0;
	
	k = 1;
	if(kmax>4)
		{
		// clean up at the beginning
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[1+bs*0] * x_1;
		y_0 -= A[2+bs*0] * x_2;
		y_0 -= A[3+bs*0] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_0 -= A[1+bs*0] * x_1;
			y_0 -= A[2+bs*0] * x_2;
			y_0 -= A[3+bs*0] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 1;
		x += 1;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;

	A = tA;
	x = tx;

	// top trinagle
	y_0 *= inv_diag_A[0];
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_one_4_lib4(int kmax, double *A, int sda, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=4;
	A += 4 + (sda-1)*bs;
	x += 4;
	for(; k<kmax-3; k+=4)
		{
		
		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		y_3 -= A[0+bs*3] * x_0;

		y_0 -= A[1+bs*0] * x_1;
		y_1 -= A[1+bs*1] * x_1;
		y_2 -= A[1+bs*2] * x_1;
		y_3 -= A[1+bs*3] * x_1;
		
		y_0 -= A[2+bs*0] * x_2;
		y_1 -= A[2+bs*1] * x_2;
		y_2 -= A[2+bs*2] * x_2;
		y_3 -= A[2+bs*3] * x_2;

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;
		y_2 -= A[3+bs*2] * x_3;
		y_3 -= A[3+bs*3] * x_3;
		
		A += sda*bs;
		x += 4;

		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		y_3 -= A[0+bs*3] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}
	
	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	A = tA;
	x = tx;

	// bottom trinagle
	z[3] = y_3;

	y_2 -= A[3+bs*2] * y_3;
	z[2] = y_2;

	// square
	y_0 -= A[2+bs*0]*y_2 + A[3+bs*0]*y_3;
	y_1 -= A[2+bs*1]*y_2 + A[3+bs*1]*y_3;
		
	// top trinagle
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_one_3_lib4(int kmax, double *A, int sda, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0;
	
	k = 3;
	if(kmax>4)
		{
		// clean up at the beginning
		x_3 = x[3];

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;
		y_2 -= A[3+bs*2] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_1 -= A[0+bs*1] * x_0;
			y_2 -= A[0+bs*2] * x_0;

			y_0 -= A[1+bs*0] * x_1;
			y_1 -= A[1+bs*1] * x_1;
			y_2 -= A[1+bs*2] * x_1;
			
			y_0 -= A[2+bs*0] * x_2;
			y_1 -= A[2+bs*1] * x_2;
			y_2 -= A[2+bs*2] * x_2;

			y_0 -= A[3+bs*0] * x_3;
			y_1 -= A[3+bs*1] * x_3;
			y_2 -= A[3+bs*2] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 3;
		x += 1;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;

	A = tA;
	x = tx;

	// bottom trinagle
	z[2] = y_2;

	// square
	y_0 -= A[2+bs*0]*y_2;
	y_1 -= A[2+bs*1]*y_2;
		
	// top trinagle
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_one_2_lib4(int kmax, double *A, int sda, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0;
	
	k = 2;
	if(kmax>4)
		{
		// clean up at the beginning
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[2+bs*0] * x_2;
		y_1 -= A[2+bs*1] * x_2;

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_1 -= A[0+bs*1] * x_0;

			y_0 -= A[1+bs*0] * x_1;
			y_1 -= A[1+bs*1] * x_1;
			
			y_0 -= A[2+bs*0] * x_2;
			y_1 -= A[2+bs*1] * x_2;

			y_0 -= A[3+bs*0] * x_3;
			y_1 -= A[3+bs*1] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 2;
		x += 2;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;

	A = tA;
	x = tx;

	// top trinagle
	z[1] = y_1;

	y_0 -= A[1+bs*0] * y_1;
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_lt_one_1_lib4(int kmax, double *A, int sda, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0;
	
	k = 1;
	if(kmax>4)
		{
		// clean up at the beginning
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];

		y_0 -= A[1+bs*0] * x_1;
		y_0 -= A[2+bs*0] * x_2;
		y_0 -= A[3+bs*0] * x_3;

		k=4;
		A += 4 + (sda-1)*bs;
		x += 4;
		for(; k<kmax-3; k+=4)
			{
			
			x_0 = x[0];
			x_1 = x[1];
			x_2 = x[2];
			x_3 = x[3];
			
			y_0 -= A[0+bs*0] * x_0;
			y_0 -= A[1+bs*0] * x_1;
			y_0 -= A[2+bs*0] * x_2;
			y_0 -= A[3+bs*0] * x_3;
			
			A += sda*bs;
			x += 4;

			}
		}
	else
		{
		A += 1;
		x += 1;
		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];
		
		y_0 -= A[0+bs*0] * x_0;
		
		A += 1;//sda*bs;
		x += 1;

		}

	y_0 = y[0] + y_0;

	A = tA;
	x = tx;

	// top trinagle
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_un_inv_4_lib4(int kmax, double *A, double *inv_diag_A, double *x, double *y, double *z)
	{

	const int bs = 4;
	
	int
		k;
	
	double *tA, *tx;
	tA = A;
	tx = x;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=4;
	A += 4*bs;
	x += 4;
	for(; k<kmax-3; k+=4)
		{
		
		x_0 = x[0];

		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[1+bs*0] * x_0;
		y_2 -= A[2+bs*0] * x_0;
		y_3 -= A[3+bs*0] * x_0;
		
		x_0 = x[1];

		y_0 -= A[0+bs*1] * x_0;
		y_1 -= A[1+bs*1] * x_0;
		y_2 -= A[2+bs*1] * x_0;
		y_3 -= A[3+bs*1] * x_0;
		
		x_0 = x[2];

		y_0 -= A[0+bs*2] * x_0;
		y_1 -= A[1+bs*2] * x_0;
		y_2 -= A[2+bs*2] * x_0;
		y_3 -= A[3+bs*2] * x_0;
		
		x_0 = x[3];

		y_0 -= A[0+bs*3] * x_0;
		y_1 -= A[1+bs*3] * x_0;
		y_2 -= A[2+bs*3] * x_0;
		y_3 -= A[3+bs*3] * x_0;
		
		A += 4*bs;
		x += 4;

		}
	for(; k<kmax; k++)
		{
		
		x_0 = x[0];

		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[1+bs*0] * x_0;
		y_2 -= A[2+bs*0] * x_0;
		y_3 -= A[3+bs*0] * x_0;
		
		A += 1*bs;
		x += 1;

		}
	
	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	A = tA;
	x = tx;

	// bottom trinagle
	y_3 *= inv_diag_A[3];
	z[3] = y_3;

	y_2 -= A[2+bs*3] * y_3;
	y_2 *= inv_diag_A[2];
	z[2] = y_2;

	// square
	y_0 -= A[0+bs*2]*y_2 + A[0+bs*3]*y_3;
	y_1 -= A[1+bs*2]*y_2 + A[1+bs*3]*y_3;
		
	// top trinagle
	y_1 *= inv_diag_A[1];
	z[1] = y_1;

	y_0 -= A[0+bs*1] * y_1;
	y_0 *= inv_diag_A[0];
	z[0] = y_0;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ut_inv_4_vs_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z, int m1, int n1)
	{

	const int bs = 4;
	
	int
		k;
	
	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	for(; k<kmax-3; k+=4)
		{
		
		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];
		
		y_0 -= A[0+bs*0] * x_0;
		y_1 -= A[0+bs*1] * x_0;
		y_2 -= A[0+bs*2] * x_0;
		y_3 -= A[0+bs*3] * x_0;

		y_0 -= A[1+bs*0] * x_1;
		y_1 -= A[1+bs*1] * x_1;
		y_2 -= A[1+bs*2] * x_1;
		y_3 -= A[1+bs*3] * x_1;
		
		y_0 -= A[2+bs*0] * x_2;
		y_1 -= A[2+bs*1] * x_2;
		y_2 -= A[2+bs*2] * x_2;
		y_3 -= A[2+bs*3] * x_2;

		y_0 -= A[3+bs*0] * x_3;
		y_1 -= A[3+bs*1] * x_3;
		y_2 -= A[3+bs*2] * x_3;
		y_3 -= A[3+bs*3] * x_3;
		
		A += sda*bs;
		x += 4;

		}
	
	y_0 = y[0] + y_0;
	y_1 = y[1] + y_1;
	y_2 = y[2] + y_2;
	y_3 = y[3] + y_3;

	double
		a_00, a_10, a_20, a_30,
		a_11, a_21, a_31;
	
	// a_00
	a_00 = inv_diag_A[0];
	a_10 = A[0+bs*1];
	a_20 = A[0+bs*2];
	a_30 = A[0+bs*3];
	y_0 *= a_00;
	z[0] = y_0;
	y_1 -= a_10 * y_0;
	y_2 -= a_20 * y_0;
	y_3 -= a_30 * y_0;

	if(n1==1)
		{
		if(m1==1)
			return;
		y[1] = y_1;
		if(m1==2)
			return;
		y[2] = y_2;
		if(m1==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_11
	a_11 = inv_diag_A[1];
	a_21 = A[1+bs*2];
	a_31 = A[1+bs*3];
	y_1 *= a_11;	
	z[1] = y_1;
	y_2 -= a_21 * y_1;
	y_3 -= a_31 * y_1;

	if(n1==2)
		{
		if(m1==2)
			return;
		y[2] = y_2;
		if(m1==3)
			return;
		y[3] = y_3;
		return;
		}

	// a_22
	a_00 = inv_diag_A[2];
	a_10 = A[2+bs*3];
	y_2 *= a_00;
	z[2] = y_2;
	y_3 -= a_10 * y_2;

	if(n1==3)
		{
		if(m1==3)
			return;
		y[3] = y_3;

		return;
		}

	// a_33
	a_11 = inv_diag_A[3];
	y_3 *= a_11;	
	z[3] = y_3;

	return;

	}
#endif
	

	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_HASWELL) || defined(TARGET_X64_INTEL_SANDY_BRIDGE) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrsv_ut_inv_4_lib4(int kmax, double *A, int sda, double *inv_diag_A, double *x, double *y, double *z)
	{

	kernel_dtrsv_ut_inv_4_vs_lib4(kmax, A, sda, inv_diag_A, x, y, z, 4, 4);

	return;

	}
#endif



#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrmv_un_4_lib4(int kmax, double *A, double *x, double *z)
	{

	const int bs = 4;
	
	int k;

	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	x_0 = x[0];
	x_1 = x[1];
	x_2 = x[2];
	x_3 = x[3];

	y_0 += A[0+bs*0] * x_0;
/*	y_1 += A[1+bs*0] * x_0;*/
/*	y_2 += A[2+bs*0] * x_0;*/
/*	y_3 += A[3+bs*0] * x_0;*/

	y_0 += A[0+bs*1] * x_1;
	y_1 += A[1+bs*1] * x_1;
/*	y_2 += A[2+bs*1] * x_1;*/
/*	y_3 += A[3+bs*1] * x_1;*/

	y_0 += A[0+bs*2] * x_2;
	y_1 += A[1+bs*2] * x_2;
	y_2 += A[2+bs*2] * x_2;
/*	y_3 += A[3+bs*2] * x_2;*/

	y_0 += A[0+bs*3] * x_3;
	y_1 += A[1+bs*3] * x_3;
	y_2 += A[2+bs*3] * x_3;
	y_3 += A[3+bs*3] * x_3;
	
	A += 4*bs;
	x += 4;

	k=4;
	for(; k<kmax-3; k+=4)
		{

		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];

		y_0 += A[0+bs*0] * x_0;
		y_1 += A[1+bs*0] * x_0;
		y_2 += A[2+bs*0] * x_0;
		y_3 += A[3+bs*0] * x_0;

		y_0 += A[0+bs*1] * x_1;
		y_1 += A[1+bs*1] * x_1;
		y_2 += A[2+bs*1] * x_1;
		y_3 += A[3+bs*1] * x_1;

		y_0 += A[0+bs*2] * x_2;
		y_1 += A[1+bs*2] * x_2;
		y_2 += A[2+bs*2] * x_2;
		y_3 += A[3+bs*2] * x_2;

		y_0 += A[0+bs*3] * x_3;
		y_1 += A[1+bs*3] * x_3;
		y_2 += A[2+bs*3] * x_3;
		y_3 += A[3+bs*3] * x_3;
		
		A += 4*bs;
		x += 4;

		}

	for(; k<kmax; k++)
		{

		x_0 = x[0];

		y_0 += A[0+bs*0] * x_0;
		y_1 += A[1+bs*0] * x_0;
		y_2 += A[2+bs*0] * x_0;
		y_3 += A[3+bs*0] * x_0;
		
		A += 1*bs;
		x += 1;

		}

	z[0] = y_0;
	z[1] = y_1;
	z[2] = y_2;
	z[3] = y_3;

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrmv_ut_4_vs_lib4(int kmax, double *A, int sda, double *x, double *z, int km)
	{

	const int bs  = 4;
	
	int
		k;
	
	double
		x_0, x_1, x_2, x_3,
		y_0=0, y_1=0, y_2=0, y_3=0;
	
	k=0;
	for(; k<kmax-4; k+=4)
		{
		
		x_0 = x[0];
		x_1 = x[1];
		x_2 = x[2];
		x_3 = x[3];
		
		y_0 += A[0+bs*0] * x_0;
		y_1 += A[0+bs*1] * x_0;
		y_2 += A[0+bs*2] * x_0;
		y_3 += A[0+bs*3] * x_0;

		y_0 += A[1+bs*0] * x_1;
		y_1 += A[1+bs*1] * x_1;
		y_2 += A[1+bs*2] * x_1;
		y_3 += A[1+bs*3] * x_1;
		
		y_0 += A[2+bs*0] * x_2;
		y_1 += A[2+bs*1] * x_2;
		y_2 += A[2+bs*2] * x_2;
		y_3 += A[2+bs*3] * x_2;

		y_0 += A[3+bs*0] * x_3;
		y_1 += A[3+bs*1] * x_3;
		y_2 += A[3+bs*2] * x_3;
		y_3 += A[3+bs*3] * x_3;
		
		A += sda*bs;
		x += 4;

		}

	x_0 = x[0];
	x_1 = x[1];
	x_2 = x[2];
	x_3 = x[3];
	
	y_0 += A[0+bs*0] * x_0;
	y_1 += A[0+bs*1] * x_0;
	y_2 += A[0+bs*2] * x_0;
	y_3 += A[0+bs*3] * x_0;

/*	y_0 += A[1+bs*0] * x_1;*/
	y_1 += A[1+bs*1] * x_1;
	y_2 += A[1+bs*2] * x_1;
	y_3 += A[1+bs*3] * x_1;
	
/*	y_0 += A[2+bs*0] * x_2;*/
/*	y_1 += A[2+bs*1] * x_2;*/
	y_2 += A[2+bs*2] * x_2;
	y_3 += A[2+bs*3] * x_2;

/*	y_0 += A[3+bs*0] * x_3;*/
/*	y_1 += A[3+bs*1] * x_3;*/
/*	y_2 += A[3+bs*2] * x_3;*/
	y_3 += A[3+bs*3] * x_3;
	
//	A += sda*bs;
//	x += 4;

	// store_vs
	store:
	if(km>=4)
		{
		z[0] = y_0;
		z[1] = y_1;
		z[2] = y_2;
		z[3] = y_3;
		}
	else
		{
		z[0] = y_0;
		if(km>=2)
			{
			z[1] = y_1;
			if(km>2)
				{
				z[2] = y_2;
				}
			}
		}

	}
#endif
	
	
	
#if defined(TARGET_GENERIC) || defined(TARGET_X86_AMD_BARCELONA) || defined(TARGET_X86_AMD_JAGUAR) || defined(TARGET_X64_INTEL_CORE) || defined(TARGET_X64_AMD_BULLDOZER) || defined(TARGET_ARMV7A_ARM_CORTEX_A15) || defined(TARGET_ARMV8A_ARM_CORTEX_A57) || defined(TARGET_ARMV8A_ARM_CORTEX_A53)
void kernel_dtrmv_ut_4_lib4(int kmax, double *A, int sda, double *x, double *z)
	{
	
	kernel_dtrmv_ut_4_vs_lib4(kmax, A, sda, x, z, 4);

	}
#endif





