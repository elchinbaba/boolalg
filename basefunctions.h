#ifndef BASE_H_
#define BASE_H_

bool NOT(bool); //!
bool OR(bool, bool); //+
bool AND(bool, bool); //*
bool IMP(bool, bool);
bool XOR(bool, bool);
bool EKV(bool, bool);

bool NOT(bool A)
{
	if (A == true) return false;
	if (A == false) return true;
}

bool OR(bool A, bool B)
{
	if (A == false && B == false) return false;
	else return true;
}

bool AND(bool A, bool B)
{
	if (A == true && B == true) return true;
	else return false;
}

bool IMP(bool A, bool B)
{
	if (A == true && B == false) return false; //return OR(NOT(A),B)
	else return true;
}

bool XOR(bool A, bool B)
{
	return AND(OR(A, B), OR(NOT(A), NOT(B)));
}

bool EKV(bool A, bool B)
{
	return OR(AND(A, B), AND(NOT(A), NOT(B)));
}

#endif