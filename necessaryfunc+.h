#include<iostream>
#include<cmath>
#include"define.h"

using namespace std;

#ifndef NECESSARYFUNCs_H_
#define NECESSARYFUNCs_H_

bool isTau(bool(*F)(bool*, int), int);
bool isNOTTau(bool(*F)(bool*, int), int);
int howmuchtrue(bool(*F)(bool*, int), int);
int howmuchtrue(bool*, int);
int howmuchfalse(bool(*F)(bool*, int), int);
int howmuchfalse(bool*, int);
void showf(bool(*F)(bool*, int), int);

int howmuchtrue(bool(*F)(bool*, int), int N)
{
	int k = 0;
	bool *A = defineBOOL(N);
	for (int i = 0; i < N; i++) A[i] = false;
	if (F(A, N)) k++;

	int j, num;
	for (int i = 1; i < pow(2, N); i++)
	{
		num = i, j = N - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (F(A, N)) k++;
	}
	//deleteBOOL(A);
	return k;
}

int howmuchtrue(bool *B, int N)
{
	int k = 0;
	for (int i = 0; i < pow(2, N); i++)
	{
		if (B[i]) k++;
	}
	return k;
}

int howmuchfalse(bool(*F)(bool*, int), int N)
{
	int k = 0;
	bool *A = defineBOOL(N);
	for (int i = 0; i < N; i++) A[i] = false;
	if (!F(A, N)) k++;

	int j, num;
	for (int i = 1; i < pow(2, N); i++)
	{
		num = i, j = N - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (!F(A, N)) k++;
	}
	//deleteBOOL(A);
	return k;
}

int howmuchfalse(bool *B, int N)
{
	int k = 0;
	for (int i = 0; i < pow(2, N); i++)
	{
		if (!B[i]) k++;
	}
	return k;
}

bool isTau(bool(*F)(bool*, int), int N)
{
	bool *A = defineBOOL(N);
	for (int i = 0; i < N; i++) A[i] = false;
	if (!F(A, N))
	{
		//deleteBOOL(A);
		return false;
	}

	int j, num;
	for (int i = 1; i < pow(2, N); i++)
	{
		num = i, j = N - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (!F(A, N))
		{
			//deleteBOOL(A);
			return false;
		}
	}
	//deleteBOOL(A);
	return true;
}

bool isNOTTau(bool(*F)(bool*, int), int N)
{
	bool *A = defineBOOL(N);
	for (int i = 0; i < N; i++) A[i] = false;
	if (F(A, N))
	{
		//deleteBOOL(A);
		return false;
	}

	int j, num;
	for (int i = 1; i < pow(2, N); i++)
	{
		num = i, j = N - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (F(A, N))
		{
			//deleteBOOL(A);
			return false;
		}
	}
	//deleteBOOL(A);
	return true;
}

void showf(bool(*F)(bool*, int), int n)
{
	bool *A = defineBOOL(n);
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " ";
	}
	cout << "\t" << "f" << endl;
	for (int i = 0; i < n; i++)
	{
		A[i] = false;
		cout << A[i] << "  ";
	}
	cout << "\t" << F(A, n) << endl;

	int j, num;
	for (int i = 1; i < pow(2, n); i++)
	{
		num = i, j = n - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		for (j = 0; j < n; j++) cout << A[j] << "  ";
		cout << "\t" << F(A, n) << endl;
	}
	//deleteBOOL(A);
}

#endif

