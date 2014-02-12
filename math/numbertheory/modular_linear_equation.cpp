/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Math - Number Theory
	Title: Modular Linear Equation
	Version: 0.314
	Date: 2010-11-7
	Remark: Calculate all the solutions of x that satisfy ax = b (mod n)
	Tested Problems: N/A
	Tag: Extended Euclid, GCD, Modular Linear Equation
	Special Thanks: Amber
*/
/*
	Input:
		a, b, n
	Output:
		x, each in a line
*/
/*
	Comment:
		The equation ax = b (mod n) has d (=GCD(a, n)) solutions (modulo n) iff GCD(a, n)|b,
		otherwise, it has no solution.

		The "Modular Linear Equation" is just a special case of "Modular Linear Equation System".
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int MaxSol = 10000;

int a, b, n, d, x, y, SolNum, Sol[MaxSol];

int ExtendedEuclid(int a, int b)
{
	if (!b)
	{
		x = 1; y = 0;
		return a;
	}
	int Ans = ExtendedEuclid(b, a%b);
	int Tmp = x;
	x = y; y = Tmp-a/b*y;
	return Ans;
}

bool ModularLinearEquationSolver(int a, int b, int n)//false means no solution
{
	d = ExtendedEuclid(a, n);
	if (b % d) return 0;
	Sol[0] = x*(b/d) % n;
	if (Sol[0] < 0) Sol[0] += n;
	for (int i = 0; i < d; ++i)
		Sol[i] = (Sol[0]+i*(n/d)) % n;
	return 1;
}

int main()
{
	scanf("%d%d%d", &a, &b, &n);
	if (ModularLinearEquationSolver(a, b, n))
	{
		for (int i = 0; i < d; ++i)
			printf("%d\n", Sol[i]);
	}
	else
		printf("No Solution.");
	return 0;
}
