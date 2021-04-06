#ifndef DEFINE_H_
#define DEFINE_H_

bool*** defineBOOL(int, int, int);
bool** defineBOOL(int, int);
bool* defineBOOL(int);
int*** defineINT(int, int, int);
int** defineINT(int, int);
int* defineINT(int);
void deleteBOOL(bool***, int, int);
void deleteBOOL(bool**, int);
void deleteBOOL(bool*);
bool** reverseBOOL(bool**, int, int);

bool** reverseBOOL(bool **arr, int n, int k)
{
	bool **revarr = defineBOOL(k, n);
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			revarr[i][j] = arr[j][i];
		}
	}
	return revarr;
}

bool*** defineBOOL(int n, int k, int l)
{
	bool ***arr = new bool **[n];
	for (int i = 0; i < n; i++) arr[i] = defineBOOL(k, l);
	return arr;
}

bool** defineBOOL(int n, int k)
{
	bool **arr = new bool*[n];
	for (int i = 0; i < n; i++) arr[i] = defineBOOL(k);
	return arr;
}

bool* defineBOOL(int n)
{
	bool *A = new bool[n];
	return A;
}

int*** defineINT(int n, int k, int l)
{
	int ***arr = new int **[n];
	for (int i = 0; i < n; i++) arr[i] = defineINT(k, l);
	return arr;
}

int** defineINT(int n, int k)
{
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) arr[i] = defineINT(k);
	return arr;
}

int* defineINT(int n)
{
	int *arr = new int[n];
	return arr;
}

void deleteBOOL(bool*** arr, int n, int k)
{
	for (int i = 0; i < n; i++)	deleteBOOL(arr[i], k);
	delete[] arr;
}

void deleteBOOL(bool** arr, int k)
{
	for (int i = 0; i < k; ++i)	deleteBOOL(arr[i]);
	arr = NULL;
	delete[] arr;
}

void deleteBOOL(bool* A)
{
	A = NULL;
	delete[] A;
}

#endif