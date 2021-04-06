#include<cmath>

struct jeqa_const
{
	bool a;
	int n, *index;
	void allocate()
	{
		index = defineINT(n);
	}
};

struct jeqa
{
	int M;
	jeqa_const *c;
	void allocate()
	{
		c = new jeqa_const[M];
	}
};

struct cons
{
	bool ans;
	int index;
};

#ifndef JEQALKIN_H_
#define JEQALKIN_H_

jeqa* defineC(bool(*F)(bool*, int), int);
jeqa* derivative(jeqa*, int);
jeqa* derivative(jeqa*, int*, int);

//int init(jeqa_const, jeqa_const);

int findit(jeqa*, int, jeqa_const*);

int findit(jeqa*, int, int*, int);

cons consist(int, int*, int);

void showJeqa(jeqa*);

int convert(bool*, int);


int findit(jeqa *je, int M, jeqa_const *obje)
{
	int j;
	for (int i = 1; i < M; i++)
	{
		if (je->c[i].n == obje->n)
		{
			for (j = 0; j < obje->n; j++)
			{
				if (je->c[i].index[j] != obje->index[j]) break;
			}
			if (j == obje->n)
			{
				return i;
			}
		}
	}
}

int findit(jeqa *je, int M, int *im, int N)
{
	int j;
	for (int i = 1; i < M; i++)
	{
		if (je->c[i].n == N)
		{
			for (j = 0; j < N; j++)
			{
				if (je->c[i].index[j] != im[j]) break;
			}
			if (j == N)
			{
				return i;
			}
		}
	}
}

cons consist(int k, int *A, int n)
{
	cons resp;
	for (int i = 0; i < n; i++)
	{
		if (k == A[i])
		{
			resp.ans = true;
			resp.index = i;
			return resp;
		}
	}
	resp.ans = false;
	resp.index = -1;
	return resp;
}

void showJeqa(jeqa *jeqalkin)
{
	cout << "Zhegalkin polynomial:" << endl;
	for (int i = 1; i < jeqalkin->M; i++)
	{
		if (jeqalkin->c[i].a)
		{
			for (int j = 0; j < jeqalkin->c[i].n; j++)
			{
				cout << "x_" << jeqalkin->c[i].index[j];
			}
			cout << "+";
		}
	}
	cout << jeqalkin->c[0].a;
	cout << endl;
}

int convert(bool *A, int n)
{
	int sum_2 = 0;
	for (int i = 0; i < n; i++)
	{
		sum_2 += A[i] * pow(2, n - i - 1);
	}
	return sum_2;
}

jeqa* JEQA(bool *B, int n)
{
	jeqa *jeq = new jeqa;
	int M = pow(2, n);
	jeq->M = M;
	jeq->allocate();

	bool *A = defineBOOL(n);

	jeq->c[0].n = 1;
	jeq->c[0].allocate();
	jeq->c[0].index[0] = 0;
	jeq->c[0].a = B[0];

	int ***imp = new int**[n], ***impp;
	int C, c, P;
	int j, k, r, t = 1, m;
	int q, index;
	C = 1; c = 1;
	jeqa_const *obje = new jeqa_const;
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

		c += C;

		while (t < c)
		{
			jeq->c[t].n = i + 1;
			jeq->c[t].allocate();
			for (int h = 0; h < n; h++)
			{
				A[h] = false;
			}
			for (int h = 0; h < jeq->c[t].n; h++)
			{
				jeq->c[t].index[h] = imp[i][C - (c - t)][h];
				A[jeq->c[t].index[h] - 1] = true;
			}
			index = convert(A, n);
			jeq->c[t].a = XOR(jeq->c[0].a, B[index]);

			m = jeq->c[t].n - 1;
			impp = new int**[m];
			P = 1;
			for (j = 0; j < m; j++)
			{
				P *= (float(m) + 1 - j) / (j + 1);
				impp[j] = defineINT(P, j + 1);
				k = 0;
				while (k < P)
				{
					for (int l = 0; l < j + 1; l++) impp[j][k][l] = l + 1;
					k++;
				}
				k = 1;
				while (k < P)
				{
					r = 0;
					while (impp[j][k - 1][j - r] == m + 1 - r && j != r)
					{
						r++;
					}
					if (r != 0)
					{
						for (int l = k; l < P; l++)
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
					if (impp[j][k - 1][j] <= m + 1)
					{
						impp[j][k][j] = impp[j][k - 1][j] + 1;
						k++;
						continue;
					}
				}
			}

			P = 1;
			for (j = 0; j < m; j++)
			{
				obje->n = j + 1;
				obje->allocate();
				P *= (float(m) + 1 - j) / (j + 1);
				for (int k = 0; k < P; k++)
				{
					for (int l = 0; l < j + 1; l++)
					{
						obje->index[l] = jeq->c[t].index[imp[j][k][l] - 1];
					}
					//if (init(obje, jeq->c[t]))
					q = findit(jeq, t, obje);
					jeq->c[t].a = XOR(jeq->c[t].a, jeq->c[q].a);
				}
			}
			t++;
		}
	}
	return jeq;
}

jeqa* JEQA(bool(*F)(bool*, int), int n)
{
	jeqa *jeq = new jeqa;
	int M = pow(2, n);
	jeq->M = M;
	jeq->allocate();

	bool *A = defineBOOL(n);
	for (int i = 0; i < n; i++) A[i] = false;

	jeq->c[0].n = 1;
	jeq->c[0].allocate();
	jeq->c[0].index[0] = 0;
	jeq->c[0].a = F(A, n);

	int ***imp = new int**[n], ***impp;
	int C, c, P;
	int j, k, r, t = 1, m;
	int q;
	C = 1; c = 1;
	jeqa_const *obje = new jeqa_const;
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

		c += C;

		while (t < c)
		{
			jeq->c[t].n = i + 1;
			jeq->c[t].allocate();
			for (int h = 0; h < n; h++)
			{
				A[h] = false;
			}
			for (int h = 0; h < jeq->c[t].n; h++)
			{
				jeq->c[t].index[h] = imp[i][C - (c - t)][h];
				A[jeq->c[t].index[h] - 1] = true;
			}
			/*for (int h = 0; h < n; h++)
			{
				cout<<A[h];
			}
			cout << endl;*/
			jeq->c[t].a = XOR(jeq->c[0].a, F(A, n));

			m = jeq->c[t].n - 1;
			impp = new int**[m];
			P = 1;
			for (j = 0; j < m; j++)
			{
				P *= (float(m) + 1 - j) / (j + 1);
				impp[j] = defineINT(P, j + 1);
				k = 0;
				while (k < P)
				{
					for (int l = 0; l < j + 1; l++) impp[j][k][l] = l + 1;
					k++;
				}
				k = 1;
				while (k < P)
				{
					r = 0;
					while (impp[j][k - 1][j - r] == m + 1 - r && j != r)
					{
						r++;
					}
					if (r != 0)
					{
						for (int l = k; l < P; l++)
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
					if (impp[j][k - 1][j] <= m + 1)
					{
						impp[j][k][j] = impp[j][k - 1][j] + 1;
						k++;
						continue;
					}
				}
			}

			P = 1;
			for (j = 0; j < m; j++)
			{
				obje->n = j + 1;
				obje->allocate();
				P *= (float(m) + 1 - j) / (j + 1);
				for (int k = 0; k < P; k++)
				{
					for (int l = 0; l < j + 1; l++)
					{
						obje->index[l] = jeq->c[t].index[imp[j][k][l]-1];
					}
					//if (init(obje, jeq->c[t]))
					q = findit(jeq, t, obje);
					jeq->c[t].a = XOR(jeq->c[t].a, jeq->c[q].a);
				}
			}
			t++;
		}

	}
	return jeq;
}

jeqa* derivative(jeqa *jeqalkin, int k)
{
	jeqa answer;
	answer.M = jeqalkin->M;
	answer.allocate();
	for (int i = 0; i < jeqalkin->M; i++)
	{
		answer.c[i].a = jeqalkin->c[i].a;
		jeqalkin->c[i].a = false;
	}
	int *exm, m;
	int index, q;
	cons some;
	for (int i = 0; i < jeqalkin->M; i++)
	{
		some = consist(k, jeqalkin->c[i].index, jeqalkin->c[i].n);
		if (some.ans && answer.c[i].a)
		{
			index = some.index;
			m = jeqalkin->c[i].n - 1;
			if (m > 0)
			{
				exm = defineINT(m);
				for (int j = 0; j < m; j++)
				{
					if (j < index) exm[j] = jeqalkin->c[i].index[j];
					else exm[j] = jeqalkin->c[i].index[j + 1];
				}
				q = findit(jeqalkin, jeqalkin->M, exm, m);
				jeqalkin->c[q].a = true;
			}
		}
	}
	if(answer.c[k].a) jeqalkin->c[0].a = true;
	return jeqalkin;
}

jeqa* derivative(jeqa *jeqalkin, int *C, int m)
{
	for (int i = 0; i < m; i++)
	{
		jeqalkin = derivative(jeqalkin, C[i]);
	}
	return jeqalkin;
}

#endif
