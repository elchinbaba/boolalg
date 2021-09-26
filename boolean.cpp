#include<iostream>
#include<cmath>
#include<cstdlib>
#include"basefunctions.h"
#include"define.h"
#include"NF.h"
#include"f.h"
#include"necessaryfunc+.h"
#include"Jeqa.h"

using namespace std;

//Boolean algebra

int main()
{
	int n = 3;
	if (isTau(f, n)) cout << "f function is tautology.";
	else if (isNOTTau(f, n)) cout << "f function is contradiction.";
	else cout << "f function is logically contingent.";
	
	cout << endl << endl;

	if (!isNOTTau(f, n))
	{
		int k = howmuchtrue(f, n);
		if (k == 1)
		{
			bool *litera = PDNF(f, n);
			showPDNF(litera, n);
		}
		else if (k > 1)
		{
			bool **litera = PDNF(f, n, k);
			showPDNF(litera, n, k);
		}
		cout << endl;
		//deleteBOOL(litera, k);
	}

	if (!isTau(f, n))
	{
		int l = howmuchfalse(f, n);
		if (l == 1)
		{
			bool *xlitera = PCNF(f, n);
			showPCNF(xlitera, n);
		}
		else if (l > 1)
		{
			bool **xlitera = PCNF(f, n, l);
			showPCNF(xlitera, n, l);
		}
		cout << endl;
	}
	
	showMADNF(MDNF(f, n));

	bool *D = defineBOOL(pow(2, n));
	D[0] = 0;
	D[1] = 0;
	D[2] = 0;
	D[3] = 1;
	D[4] = 1;
	D[5] = 1;
	D[6] = 1;
	D[7] = 1;
	

	/*int l = howmuchfalse(D, n);
	bool **xlit = PCNF(D, n, l);
	showPCNF(xlit, n, l);*/

	cout << endl;

	showf(f, n);

	cout << endl;

	/*impps *salam = MDNF(f, n);
	showMADNF(salam);

	impps *saghol = MDNF(D, n);
	showMADNF(saghol);*/

	/*jeqa *salam = JEQA(f, n);
	showJeqa(salam);
	
	cout << endl;

	jeqa *saghol = JEQA(D, n);
	showJeqa(saghol);*/

	jeqa *salamm = JEQA(f, n);
	showJeqa(salamm);

	cout << endl << "derivative with respect to x_1:" << endl;

	showJeqa(derivative(salamm, 1));

	cout << endl << "derivative with respect to x_2:" << endl;

	salamm = JEQA(f, n);
	showJeqa(derivative(salamm, 2));

	cout << endl << "derivative with respect to x_3:" << endl;

	salamm = JEQA(f, n);
	showJeqa(derivative(salamm, 3));

	int *C = defineINT(2);
	C[0] = 1; C[1] = 3;
	salamm = JEQA(f, n);

	cout << endl << "derivative with respect to C:" << endl;
	showJeqa(derivative(salamm, C, 2));

	system("PAUSE");
	return 0;
}
