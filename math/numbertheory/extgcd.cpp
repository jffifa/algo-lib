/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Math - Number Theory
	Title: Extended Euclid
	Version: 0.314
	Date: 2010-11-7
	Remark: Given d = GCD(a, b), Calculate x, y that satisfy d = ax + by
	Tested Problems: N/A
	Tag: Extended Euclid, GCD
	Special Thanks: Amber
*/
/*
	Input:
		a, b
	Output:
		d = GCD(a, b), x, y
*/

#include <cstdio>
#include <cstring>
using namespace std;

int a, b, d, x, y;

int extgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1; y = 0;
		return a;
	}
	int res = extgcd(b, a%b, x, y);
	int t = x; x = y; y = t-a/b*y;
	return res;
}
