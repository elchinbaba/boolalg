#include<iostream>
#include"define.h"
#include"basefunctions.h"
#include"necessaryfunc+.h"

using namespace std;

struct imp
{
	int INT;
	bool BOOL;
};

struct imps
{
	int N;
	imp *arrIMP;
	void allocate()
	{
		arrIMP = new imp[N];
	}
};

struct impps
{
	int M;
	imps *hi;
	void allocate()
	{
		hi = new imps[M];
	}
};

struct INTS
{
	int min;
	int howmuch;
};

#ifndef NORMALFORMS_H_
#define NORMALFORMS_H_

impps* implicants(bool*, int);
impps* implicants(bool(*F)(bool*, int), int n);
impps* prime_implicants(impps*);
impps* MDNF(bool*, int);
impps* MDNF(bool(*F)(bool*, int), int);
impps* ADNF(bool*, int);
impps* ADNF(bool(*F)(bool*, int), int);
void showMADNF(impps*);
bool** PDNF(bool(*F)(bool*, int), int, int);
bool* PDNF(bool(*F)(bool*, int), int);
bool** PDNF(bool*, int, int);
bool* PDNF(bool*, int);
void showPDNF(bool**, int, int);
void showPDNF(bool*, int);
bool** PCNF(bool(*F)(bool*, int), int, int);
bool* PCNF(bool(*F)(bool*, int), int);
bool** PCNF(bool*, int, int);
bool* PCNF(bool*, int);
void showPCNF(bool**, int, int);
void showPCNF(bool*, int);


bool isthere(imps*, impps*);
void addit(imps, impps*, int);

bool u(bool*, bool*, bool*, int, int);
bool v(bool, bool);

void writethere(int, bool);

bool ispartof(imps, bool*);

INTS* minimum(bool**, int, int);



bool u(bool *a, bool *A, int *imp, int N, int k)
{
	bool g = v(a[0], A[imp[0] - 1]);
	for (int i = 1; i < k; i++)
	{
		g = AND(g, v(a[i], A[imp[i] - 1]));
	}
	return g;
}

bool v(bool a, bool A)
{
	if (a) return A;
	if (!a) return NOT(A);
}

void writethere(int INT, bool BOOL)
{
	if (!BOOL) cout << "!";
	cout << "x_" << INT;
}

bool isthere(imps *obje, impps *obj)
{
	bool A;
	for (int i = 0; i < obj->M; i++)
	{
		A = false;
		if (obje->N == obj->hi[i].N)
		{
			A = true;
			for (int j = 0; j < obje->N; j++)
			{
				if (obje->arrIMP[j].INT != obj->hi[i].arrIMP[j].INT || obje->arrIMP[j].BOOL != obj->hi[i].arrIMP[j].BOOL)
				{
					A = false;
					break;
				}
			}
		}
		if (A) return true;
	}
	return false;
}

void addit(imps obje, impps *object, int m)
{
	object->hi[m].N = obje.N;
	object->hi[m].allocate();
	for (int i = 0; i < object->hi[m].N; i++)
	{
		object->hi[m].arrIMP[i] = obje.arrIMP[i];
	}
}

bool ispartof(imps adnf, bool *rpdnf)
{
	for (int k = 0; k < adnf.N; k++)
	{
		if (rpdnf[adnf.arrIMP[k].INT - 1] != adnf.arrIMP[k].BOOL) return false;
	}
	return true;
}

INTS* minimum(bool **arr, int n, int k)
{
	INTS *ans = new INTS;
	int min_c = 0;
	for (int i = 0; i < n; i++)
	{
		min_c += arr[i][0];
	}
	int tmp;
	for (int j = 1; j < k; j++)
	{
		tmp = 0;
		for (int i = 0; i < n; i++)
		{
			tmp += arr[i][j];
		}
		if (tmp < min_c) min_c = tmp;
	}
	ans->min = min_c;
	ans->howmuch = 0;
	for (int j = 0; j < k; j++)
	{
		tmp = 0;
		for (int i = 0; i < n; i++)
		{
			tmp += arr[i][j];
		}
		if (tmp == min_c) ans->howmuch++;
	}
	return ans;
}


impps* implicants(bool *B, int n)
{
	impps *hello = new impps;
	int ***imp = new int**[n];
	int C = 1;
	int j, r;
	for (int i = 0; i < n; i++)
	{
		C *= (float(n) - i) / (i + 1);
		imp[i] = defineINT(C, i + 1);
		j = 0;
		while (j < C)
		{
			for (int k = 0; k < i + 1; k++) imp[i][j][k] = k + 1;
			j++;
		}
		j = 1;
		while (j < C)
		{
			r = 0;
			while (imp[i][j - 1][i - r] == n - r && i != r)
			{
				r++;
			}
			if (r != 0)
			{
				for (int k = j; k < C; k++)
				{
					imp[i][k][i - r]++;
				}
				for (int k = i - r + 1; k < i + 1; k++)
				{
					imp[i][j][k] = imp[i][j][k - 1] + 1;
				}
				j++;
				continue;
			}
			if (imp[i][j - 1][i] <= n)
			{
				imp[i][j][i] = imp[i][j - 1][i] + 1;
				j++;
				continue;
			}
		}
	}

	/*for (int i = 0; i < n; i++)
	{
	C *= (float(n) - i) / (i + 1);
	for (j = 0; j < C; j++)
	{
	for (int k = 0; k < i + 1; k++)
	{
	cout << imp[i][j][k] << " ";
	}
	cout << "  ";
	}
	cout << endl;
	}*/

	int l, o, m, num;
	bool *a, g;
	bool *A;

	A = defineBOOL(n);
	hello->M = 0;
	for (int i = 0; i < n; i++)
	{
		a = defineBOOL(i + 1);
		C *= (float(n) - i) / (i + 1);
		for (j = 0; j < C; j++)
		{
			for (int k = 0; k < i + 1; k++) a[k] = false;
			for (int k = 0; k < n; k++) A[k] = false;
			
			/*o = 0;
			while (o < pow(2, n))
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
				if (!g) break;
				o++;
			}*/
			for (o = 0; o < pow(2, n); o++)
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
				if (!g) break;
			}
			/*o = 0;
			while (o <= pow(2, n))
			{
				g = IMP(u(a, A, imp[i][j], n, i + 1), f(A, n));
				if (!g) break;
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				o++;
			}*/
			if (o == pow(2, n))
			{
				hello->M++;
				/*for (int h = 0; h < i + 1; h++)
				{
				cout << "x_" << imp[i][j][h] << " ";
				}
				cout << endl;
				for (int h = 0; h < i + 1; h++)
				{
				cout << a[h] << " ";
				}
				cout << "= a" << endl;*/
			}

			for (l = 1; l < pow(2, i + 1); l++)
			{
				num = l, m = i + 1 - 1;
				while (num != 0)
				{
					a[m] = num % 2;
					num /= 2;
					m--;
				}

				for (int k = 0; k < n; k++) A[k] = false;
				/*o = 0;
				while (o < pow(2, n))
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
					if (!g) break;
					o++;
				}*/
				for (o = 0; o < pow(2, n); o++)
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
					if (!g) break;
				}
				/*o = 0;
				while (o <= pow(2, n))
				{
					g = IMP(u(a, A, imp[i][j], n, i + 1), f(A, n));
					if (!g) break;
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					o++;
				}*/

				if (o == pow(2, n))
				{
					hello->M++;
					/*for (int h = 0; h < i + 1; h++)
					{
					cout << "x_" << imp[i][j][h] << " ";
					}
					cout << endl;
					for (int h = 0; h < i + 1; h++)
					{
					cout << a[h] << " ";
					}
					cout << "= a" << endl;*/
				}
			}
		}
	}

	hello->allocate();

	A = defineBOOL(n);
	hello->M = 0;
	for (int i = 0; i < n; i++)
	{
		a = defineBOOL(i + 1);
		C *= (float(n) - i) / (i + 1);
		for (j = 0; j < C; j++)
		{
			for (int k = 0; k < i + 1; k++) a[k] = false;
			for (int k = 0; k < n; k++) A[k] = false;
			
			/*o = 0;
			while (o < pow(2, n))
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
				if (!g) break;
				o++;
			}*/
			for (o = 0; o < pow(2, n); o++)
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
				if (!g) break;
			}
			/*o = 0;
			while (o <= pow(2, n))
			{
				g = IMP(u(a, A, imp[i][j], n, i + 1), f(A, n));
				if (!g) break;
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				o++;
			}*/
			if (o == pow(2, n))
			{
				hello->hi[hello->M].N = i + 1;
				hello->hi[hello->M].allocate();
				for (int h = 0; h < hello->hi[hello->M].N; h++)
				{
					hello->hi[hello->M].arrIMP[h].INT = imp[i][j][h];
					hello->hi[hello->M].arrIMP[h].BOOL = a[h];
				}
				hello->M++;
			}

			for (l = 1; l < pow(2, i + 1); l++)
			{
				num = l, m = i + 1 - 1;
				while (num != 0)
				{
					a[m] = num % 2;
					num /= 2;
					m--;
				}

				for (int k = 0; k < n; k++) A[k] = false;

				/*o = 0;
				while (o < pow(2, n))
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
					if (!g) break;
					o++;
				}*/
				for (o = 0; o < pow(2, n); o++)
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), B[o]);
					if (!g) break;
				}
				/*o = 0;
				while (o <= pow(2, n))
				{
					g = IMP(u(a, A, imp[i][j], n, i + 1), f(A, n));
					if (!g) break;
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					o++;
				}*/

				if (o == pow(2, n))
				{
					hello->hi[hello->M].N = i + 1;
					hello->hi[hello->M].allocate();
					for (int h = 0; h < hello->hi[hello->M].N; h++)
					{
						hello->hi[hello->M].arrIMP[h].INT = imp[i][j][h];
						hello->hi[hello->M].arrIMP[h].BOOL = a[h];
					}
					hello->M++;
				}
			}
		}
	}
	return hello;
}

impps* implicants(bool(*F)(bool*, int), int n)
{
	impps *hello = new impps;
	int ***imp = new int**[n];
	int C = 1;
	int j, r;
	for (int i = 0; i < n; i++)
	{
		C *= (float(n) - i) / (i + 1);
		imp[i] = defineINT(C, i + 1);
		j = 0;
		while (j < C)
		{
			for (int k = 0; k < i + 1; k++) imp[i][j][k] = k + 1;
			j++;
		}
		j = 1;
		while (j < C)
		{
			r = 0;
			while (imp[i][j - 1][i - r] == n - r && i != r)
			{
				r++;
			}
			if (r != 0)
			{
				for (int k = j; k < C; k++)
				{
					imp[i][k][i - r]++;
				}
				for (int k = i - r + 1; k < i + 1; k++)
				{
					imp[i][j][k] = imp[i][j][k - 1] + 1;
				}
				j++;
				continue;
			}
			if (imp[i][j - 1][i] <= n)
			{
				imp[i][j][i] = imp[i][j - 1][i] + 1;
				j++;
				continue;
			}
		}
	}
	
	/*for (int i = 0; i < n; i++)
	{
		C *= (float(n) - i) / (i + 1);
		for (j = 0; j < C; j++)
		{
			for (int k = 0; k < i + 1; k++)
			{
				cout << imp[i][j][k] << " ";
			}
			cout << "  ";
		}
		cout << endl;
	}*/

	int l, o, m, num;
	bool *a, g;
	bool *A;

	A = defineBOOL(n);
	hello->M = 0;
	for (int i = 0; i < n; i++)
	{
		a = defineBOOL(i + 1);
		C *= (float(n) - i) / (i + 1);
		for (j = 0; j < C; j++)
		{
			for (int k = 0; k < i + 1; k++) a[k] = false;
			for (int k = 0; k < n; k++) A[k] = false;
			for (o = 0; o < pow(2, n); o++)
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), F(A, n));
				if (!g) break;
			}
			if (o == pow(2, n))
			{
				hello->M++;
				/*for (int h = 0; h < i + 1; h++)
				{
					cout << "x_" << imp[i][j][h] << " ";
				}
				cout << endl;
				for (int h = 0; h < i + 1; h++)
				{
					cout << a[h] << " ";
				}
				cout << "= a" << endl;*/
			}

			for (l = 1; l < pow(2, i + 1); l++)
			{
				num = l, m = i + 1 - 1;
				while (num != 0)
				{
					a[m] = num % 2;
					num /= 2;
					m--;
				}

				for (int k = 0; k < n; k++) A[k] = false;
				for (o = 0; o < pow(2, n); o++)
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), F(A, n));
					if (!g) break;
				}

				if (o == pow(2, n))
				{
					hello->M++;
					/*for (int h = 0; h < i + 1; h++)
					{
						cout << "x_" << imp[i][j][h] << " ";
					}
					cout << endl;
					for (int h = 0; h < i + 1; h++)
					{
						cout << a[h] << " ";
					}
					cout << "= a" << endl;*/
				}
			}
		}
	}

	hello->allocate();

	A = defineBOOL(n);
	hello->M = 0;
	for (int i = 0; i < n; i++)
	{
		a = defineBOOL(i + 1);
		C *= (float(n) - i) / (i + 1);
		for (j = 0; j < C; j++)
		{
			for (int k = 0; k < i + 1; k++) a[k] = false;
			for (int k = 0; k < n; k++) A[k] = false;
			for (o = 0; o < pow(2, n); o++)
			{
				num = o, m = n - 1;
				while (num != 0)
				{
					A[m] = num % 2;
					num /= 2;
					m--;
				}
				g = IMP(u(a, A, imp[i][j], n, i + 1), F(A, n));
				if (!g) break;
			}
			if (o == pow(2, n))
			{
				hello->hi[hello->M].N = i + 1;
				hello->hi[hello->M].allocate();
				for (int h = 0; h < hello->hi[hello->M].N; h++)
				{
					hello->hi[hello->M].arrIMP[h].INT = imp[i][j][h];
					hello->hi[hello->M].arrIMP[h].BOOL = a[h];
				}
				hello->M++;
			}

			for (l = 1; l < pow(2, i + 1); l++)
			{
				num = l, m = i + 1 - 1;
				while (num != 0)
				{
					a[m] = num % 2;
					num /= 2;
					m--;
				}

				for (int k = 0; k < n; k++) A[k] = false;
				for (o = 0; o < pow(2, n); o++)
				{
					num = o, m = n - 1;
					while (num != 0)
					{
						A[m] = num % 2;
						num /= 2;
						m--;
					}
					g = IMP(u(a, A, imp[i][j], n, i + 1), F(A, n));
					if (!g) break;
				}

				if (o == pow(2, n))
				{
					hello->hi[hello->M].N = i + 1;
					hello->hi[hello->M].allocate();
					for (int h = 0; h < hello->hi[hello->M].N; h++)
					{
						hello->hi[hello->M].arrIMP[h].INT = imp[i][j][h];
						hello->hi[hello->M].arrIMP[h].BOOL = a[h];
					}
					hello->M++;
				}
			}
		}
	}
	return hello;
}

impps* prime_implicants(impps *obj)
{
	impps *object = new impps;
	imps *obje = new imps;
	int n, C, ***impp=new int**[1];
	int k, r, o;
	bool q;

	object->M = 0;
	for (int i = 0; i < obj->M; i++)
	{
		q = true;
		n = obj->hi[i].N - 1;
		if (n > 0)
		{
			impp = new int**[n];
			C = 1;
			for (int j = 0; j < n; j++)
			{
				C *= (float(n) + 1 - j) / (j + 1);
				impp[j] = defineINT(C, j + 1);
				k = 0;
				while (k < C)
				{
					for (int l = 0; l < j + 1; l++) impp[j][k][l] = l + 1;
					k++;
				}
				k = 1;
				while (k < C)
				{
					r = 0;
					while (impp[j][k - 1][j - r] == n + 1 - r && j != r)
					{
						r++;
					}
					if (r != 0)
					{
						for (int l = k; l < C; l++)
						{
							impp[j][l][j - r]++;
						}
						for (int l = j - r + 1; l < j + 1; l++)
						{
							impp[j][k][l] = impp[j][k][l - 1] + 1;
						}
						k++;
						continue;
					}
					if (impp[j][k - 1][j] <= n + 1)
					{
						impp[j][k][j] = impp[j][k - 1][j] + 1;
						k++;
						continue;
					}
				}
			}
			
			C = 1;
			for (int j = 0; (j < n) && q; j++)
			{
				obje->N = j + 1;
				obje->allocate();
				C *= (float(n) + 1 - j) / (j + 1);
				for (int k = 0; (k < C) && q; k++)
				{
					for (int l = 0; l < j + 1; l++)
					{
						//obje->arrIMP[l].INT = obj->hi[i].arrIMP[impp[j][k][l] - 1].INT;
						//obje->arrIMP[l].BOOL = obj->hi[i].arrIMP[impp[j][k][l] - 1].BOOL;
						obje->arrIMP[l] = obj->hi[i].arrIMP[impp[j][k][l] - 1];
					}
					if (isthere(obje, obj))
					{
						q = false;
					}
				}
			}
			
		}
		if (q)
		{
			object->M++;
		}
	}

	object->allocate();

	object->M = 0;
	for (int i = 0; i < obj->M; i++)
	{
		q = true;
		n = obj->hi[i].N - 1;
		if (n > 0)
		{
			impp = new int**[n];
			C = 1;
			for (int j = 0; j < n; j++)
			{
				C *= (float(n) + 1 - j) / (j + 1);
				impp[j] = defineINT(C, j + 1);
				k = 0;
				while (k < C)
				{
					for (int l = 0; l < j + 1; l++) impp[j][k][l] = l + 1;
					k++;
				}
				k = 1;
				while (k < C)
				{
					r = 0;
					while (impp[j][k - 1][j - r] == n + 1 - r && j != r)
					{
						r++;
					}
					if (r != 0)
					{
						for (int l = k; l < C; l++)
						{
							impp[j][l][j - r]++;
						}
						for (int l = j - r + 1; l < j + 1; l++)
						{
							impp[j][k][l] = impp[j][k][l - 1] + 1;
						}
						k++;
						continue;
					}
					if (impp[j][k - 1][j] <= n + 1)
					{
						impp[j][k][j] = impp[j][k - 1][j] + 1;
						k++;
						continue;
					}
				}
			}
			
			C = 1;
			for (int j = 0; (j < n) && q; j++)
			{
				obje->N = j + 1;
				obje->allocate();
				C *= (float(n) + 1 - j) / (j + 1);
				for (k = 0; (k < C) && q; k++)
				{
					for (int l = 0; l < j + 1; l++)
					{
						//obje->arrIMP[l].INT = obj->hi[i].arrIMP[impp[j][k][l] - 1].INT;
						//obje->arrIMP[l].BOOL = obj->hi[i].arrIMP[impp[j][k][l] - 1].BOOL;
						obje->arrIMP[l] = obj->hi[i].arrIMP[impp[j][k][l] - 1];
					}
					if (isthere(obje, obj))
					{
						q = false;
					}
				}
			}
		}
		if (q)
		{
			addit(obj->hi[i], object, object->M);
			object->M++;
		}
	}
	return object;
}

void showMADNF(impps* adnf)
{
	cout << "Shortened Disjunctive Normal Form:" << endl;
	for (int i = 0; i < adnf->M; i++)
	{
		for (int j = 0; j < adnf->hi[i].N; j++)
		{
			writethere(adnf->hi[i].arrIMP[j].INT, adnf->hi[i].arrIMP[j].BOOL);
			if (j != adnf->hi[i].N - 1) cout << "*";
		}
		if (i != adnf->M - 1) cout << " v ";
	}
	cout << endl;
}

impps* ADNF(bool *B, int N)
{
	impps *abbreviated = new impps;
	abbreviated = prime_implicants(implicants(B, N));
	return abbreviated;
}

impps* ADNF(bool(*F)(bool*, int), int n)
{
	impps *abbreviated = new impps;
	abbreviated = prime_implicants(implicants(F, n));
	return abbreviated;
}

impps* MDNF(bool *B, int N)
{
	impps *mdnf = new impps;
	impps *adnf = ADNF(B, N);
	int k = howmuchtrue(B, N);
	if (k > 1)
	{
		INTS *min_column;
		bool **pdnf = PDNF(B, N, k);
		/*for (int i = 0; i < n; i++)
		{
		for (int j = 0; j < k; j++)
		{
		cout << pdnf[i][j] << " ";
		}
		cout << endl;
		}*/
		bool **rpdnf = reverseBOOL(pdnf, N, k);
		/*for (int i = 0; i < k; i++)
		{
		for (int j = 0; j < n; j++)
		{
		cout << rpdnf[i][j] << " ";
		}
		cout << endl;
		}*/
		bool **matris = defineBOOL(adnf->M, k);
		for (int i = 0; i < adnf->M; i++)
		{
			for (int j = 0; j < k; j++)
			{
				matris[i][j] = ispartof(adnf->hi[i], rpdnf[j]);
			}
		}

		min_column = minimum(matris, adnf->M, k);

		mdnf->M = min_column->howmuch;
		mdnf->allocate();

		int min_tmp;
		min_column->howmuch = 0;
		for (int j = 0; j < k; j++)
		{
			min_tmp = 0;
			for (int i = 0; i < adnf->M; i++)
			{
				min_tmp += matris[i][j];
			}
			if (min_tmp == min_column->min)
			{
				for (int i = 0; i < adnf->M; i++)
				{
					if (matris[i][j] && !isthere(&(adnf->hi[i]), mdnf))
					{
						addit(adnf->hi[i], mdnf, min_column->howmuch);
						min_column->howmuch++;
					}
				}
			}
		}
		mdnf->M = min_column->howmuch;
	}
	else if (k == 1)
	{
		mdnf = adnf;
	}
	return mdnf;
}

impps* MDNF(bool(*F)(bool*, int), int n)
{
	impps *mdnf = new impps;
	impps *adnf = ADNF(F, n);
	int k = howmuchtrue(F, n);
	if (k > 1)
	{
		INTS *min_column;
		bool **pdnf = PDNF(F, n, k);
		/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				cout << pdnf[i][j] << " ";
			}
			cout << endl;
		}*/
		bool **rpdnf = reverseBOOL(pdnf, n, k);
		/*for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << rpdnf[i][j] << " ";
			}
			cout << endl;
		}*/
		bool **matris = defineBOOL(adnf->M, k);
		for (int i = 0; i < adnf->M; i++)
		{
			for (int j = 0; j < k; j++)
			{
				matris[i][j] = ispartof(adnf->hi[i], rpdnf[j]);
			}
		}

		min_column = minimum(matris, adnf->M, k);

		mdnf->M = min_column->howmuch;
		mdnf->allocate();

		int min_tmp;
		min_column->howmuch = 0;
		for (int j = 0; j < k; j++)
		{
			min_tmp = 0;
			for (int i = 0; i < adnf->M; i++)
			{
				min_tmp += matris[i][j];
			}
			if (min_tmp == min_column->min)
			{
				for (int i = 0; i < adnf->M; i++)
				{
					if (matris[i][j] && !isthere(&(adnf->hi[i]), mdnf))
					{
						addit(adnf->hi[i], mdnf, min_column->howmuch);
						min_column->howmuch++;
					}
				}
			}
		}
		mdnf->M = min_column->howmuch;
	}
	else if (k == 1)
	{
		mdnf = adnf;
	}
	return mdnf;
}

void showPDNF(bool **litera, int n, int k)
{
	cout << "Perfect Disjunctive Normal Form:" << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			writethere(j + 1, litera[j][i]);
			if (j != n - 1) cout << "*";
		}
		if (i != k - 1) cout << " v ";
	}
	cout << endl;
}

void showPDNF(bool *litera, int n)
{
	cout << "Perfect Disjunctive Normal Form:" << endl;
	for (int i = 0; i < n; i++)
	{
		writethere(i + 1, litera[i]);
		if (i != n - 1) cout << "*";
	}
	cout << endl;
}

bool* PDNF(bool(*F)(bool*, int), int n)
{
	bool *A = defineBOOL(n);
	bool *litera = defineBOOL(n);

	for (int i = 0; i < n; i++) A[i] = false;
	if (F(A, n))
		for (int i = 0; i < n; i++) litera[i] = A[i];
	int j, num;
	for (int i = 1; i < pow(2, n); i++)
	{
		num = i; j = n - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (F(A, n))
			for (j = 0; j < n; j++) litera[j] = A[j];
	}
	return litera;
}

bool** PDNF(bool(*F)(bool*, int), int n, int k)
{
	bool *A = defineBOOL(n);
	bool **litera = defineBOOL(n, k);

	int K = 0;
	for (int i = 0; i < n; i++) A[i] = false;
	if (F(A, n))
	{
		for (int i = 0; i < n; i++) litera[i][K] = A[i];
		K++;
	}

	int j, num;
	for (int i = 1; i < pow(2, n); i++)
	{
		num = i; j = n - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (F(A, n))
		{
			for (j = 0; j < n; j++) litera[j][K] = A[j];
			K++;
		}
	}
	//deleteBOOL(A);
	return litera;
}

bool* PDNF(bool *B, int n)
{
	bool *A = defineBOOL(n);
	bool *litera = defineBOOL(n);

	for (int i = 0; i < n; i++) A[i] = false;
	if (B[0])
		for (int i = 0; i < n; i++) litera[i] = A[i];
	int j, num;
	for (int i = 1; i < pow(2, n); i++)
	{
		num = i; j = n - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (B[i])
			for (j = 0; j < n; j++) litera[j] = A[j];
	}
	return litera;
}

bool** PDNF(bool *B, int n, int k)
{
	bool *A = defineBOOL(n);
	bool **litera = defineBOOL(n, k);

	int K = 0;
	for (int i = 0; i < n; i++) A[i] = false;
	if (B[0])
	{
		for (int i = 0; i < n; i++) litera[i][K] = A[i];
		K++;
	}

	int j, num;
	for (int i = 1; i < pow(2, n); i++)
	{
		num = i; j = n - 1;
		while (num != 0)
		{
			A[j] = num % 2;
			num /= 2;
			j--;
		}
		if (B[i])
		{
			for (j = 0; j < n; j++) litera[j][K] = A[j];
			K++;
		}
	}
	//deleteBOOL(A);
	return litera;
}

void showPCNF(bool **xlitera, int n, int k)
{
	cout << "Perfect Conjunctive Normal Form:" << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (xlitera[j][i]) cout << "!"; //!writethere(j+1,xlitera[j][i])
			cout << "x_" << j + 1;
			if (j != n - 1) cout << "+";
		}
		if (i != k - 1) cout << " ^ ";
	}
	cout << endl;
}

void showPCNF(bool *xlitera, int n)
{
	cout << "Perfect Conjunctive Normal Form:" << endl;
	for (int i = 0; i < n; i++)
	{
		if (xlitera[i]) cout << "!"; //!writethere(i+1,xlitera[i])
		cout << "x_" << i + 1;
		if (i != n - 1) cout << "+";
	}
	cout << endl;
}

bool* PCNF(bool(*F)(bool*, int), int n)
{
	bool *A = defineBOOL(n);
	bool *xlitera = defineBOOL(n);

	for (int i = 0; i < n; i++) A[i] = false;
	if (!F(A, n))
		for (int i = 0; i < n; i++) xlitera[i] = A[i];
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
		if (!F(A, n))
			for (j = 0; j < n; j++) xlitera[j] = A[j];
	}
	return xlitera;
}

bool** PCNF(bool(*F)(bool*, int), int n, int l)
{
	bool *A = defineBOOL(n);
	bool **xlitera = defineBOOL(n, l);

	int L = 0;
	for (int i = 0; i < n; i++) A[i] = false;
	if (!F(A, n))
	{
		for (int i = 0; i < n; i++) xlitera[i][L] = A[i];
		L++;
	}

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
		if (!F(A, n))
		{
			for (j = 0; j < n; j++) xlitera[j][L] = A[j];
			L++;
		}
	}
	//deleteBOOL(A);
	return xlitera;
}

bool* PCNF(bool *B, int n)
{
	bool *A = defineBOOL(n);
	bool *xlitera = defineBOOL(n);

	for (int i = 0; i < n; i++) A[i] = false;
	if (!B[0])
		for (int i = 0; i < n; i++) xlitera[i] = A[i];
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
		if (!B[i])
			for (j = 0; j < n; j++) xlitera[j] = A[j];
	}
	return xlitera;
}

bool** PCNF(bool *B, int n, int l)
{
	bool *A = defineBOOL(n);
	bool **xlitera = defineBOOL(n, l);

	int K = 0;
	for (int i = 0; i < n; i++) A[i] = false;
	if (!B[0])
	{
		for (int i = 0; i < n; i++) xlitera[i][K] = A[i];
		K++;
	}

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
		if (!B[i])
		{
			for (j = 0; j < n; j++) xlitera[j][K] = A[j];
			K++;
		}
	}
	//deleteBOOL(A);
	return xlitera;
}

#endif