#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define ParaBuffer(Buffer,Row,Col) (*(Buffer + (Row) * (SizeSrc + 1) + (Col)))

/***********************************************************************************
***********************************************************************************/
static int ParalimitRow(double* Para, int SizeSrc, int Row)
{
	int i;
	double Max, Min, Temp;
	for (Max = fabs(ParaBuffer(Para, Row, 0)), Min = Max, i = SizeSrc; i; i--)
	{
		Temp = fabs(ParaBuffer(Para, Row, i));
		if (Max < Temp)
			Max = Temp;
		if (Min > Temp)
			Min = Temp;
	}
	Max = (Max + Min) * 0.000005;
	for (i = SizeSrc; i >= 0; i--)
		ParaBuffer(Para, Row, i) /= Max;
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int Paralimit(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParalimitRow(Para, SizeSrc, i))
			return -1;
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int ParaPreDealA(double* Para, int SizeSrc, int Size)
{
	int i, j;
	for (Size -= 1, i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i, j) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, j) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, SizeSrc) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, Size) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int ParaDealA(double* Para, int SizeSrc)
{
	int i;
	for (i = SizeSrc; i; i--)
		if (ParaPreDealA(Para, SizeSrc, i))
			return -1;
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int ParaPreDealB(double* Para, int SizeSrc, int OffSet)
{
	int i, j;
	for (i = OffSet + 1; i < SizeSrc; i++)
	{
		for (j = OffSet + 1; j <= i; j++)
			ParaBuffer(Para, i, j) *= ParaBuffer(Para, OffSet, OffSet);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, OffSet, OffSet) - ParaBuffer(Para, i, OffSet) * ParaBuffer(Para, OffSet, SizeSrc);
		ParaBuffer(Para, i, OffSet) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int ParaDealB(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParaPreDealB(Para, SizeSrc, i))
			return -1;
	for (i = 0; i < SizeSrc; i++)
	{
		if (ParaBuffer(Para, i, i))
		{
			ParaBuffer(Para, i, SizeSrc) /= ParaBuffer(Para, i, i);
			ParaBuffer(Para, i, i) = 1.0;
		}
	}
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int ParaDeal(double* Para, int SizeSrc)
{
	
	Paralimit(Para, SizeSrc);
	
	if (ParaDealA(Para, SizeSrc))
		return -1;
	
	if (ParaDealB(Para, SizeSrc))
		return -1;
	return 0;
}
/***********************************************************************************
***********************************************************************************/
static int GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc)
{
	int i, j;
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, 0, i) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, 0, i) += pow(*(X + j), 2 * (SizeSrc - 1) - i);
	for (i = 1; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc - 1) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc - 1) += pow(*(X + j), SizeSrc - 1 - i);
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc) += (*(Y + j)) * pow(*(X + j), SizeSrc - 1 - i);
	for (i = 1; i < SizeSrc; i++)
		for (j = 0; j < SizeSrc - 1; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i - 1, j + 1);
	return 0;
}
        /// \brief 多项式拟合，拟合y=a1*xn +a2*x(n-1)+.....+an*x+ a(n+1)
        /// \param BufferX X值缓冲数组   
        /// \param BufferY Y值缓冲数组  
        /// \param Amount X（Y）数组长度
        /// \param SizeSrc 拟合后的参数个数（阶数+1）
        /// \param ParaResK 拟合后的参数存储地址，数组按阶数降序排列如上式的a1、a2、.......an、a(n+1)
int polyfit(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK)
{
	double* ParaK = (double*)malloc(SizeSrc * (SizeSrc + 1) * sizeof(double));
	GetParaBuffer(ParaK, BufferX, BufferY, Amount, SizeSrc);
	ParaDeal(ParaK, SizeSrc);
	for (Amount = 0; Amount < SizeSrc; Amount++, ParaResK++)
		*ParaResK = ParaBuffer(ParaK, Amount, SizeSrc);
	free(ParaK);
	return 0;
}