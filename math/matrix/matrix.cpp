/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Bary Center 
	Version: 0.103
	Date: 2011-9-19
	Remark: Structure definations and base functions
	Tested Problems: N/A
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/
#include <cstdio>
#include <cstring>

typedef long long LL;

const int SIZE = 5;
const LL MOD = 2;

struct sm
{
	LL m[SIZE][SIZE];
	sm() {memset(m, 0, sizeof(m));}
	void eye() {for (int i = 0; i < SIZE; ++i) m[i][i] = 1;}
};

//res=a*b
sm operator*(const sm &a, const sm &b)
{
	sm res;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			for (int k = 0; k < SIZE; ++k)
				res.m[i][j] = (res.m[i][j]+a.m[i][k]*b.m[k][j]) % MOD;
	return res;
}

//res=a+b;
sm operator+(const sm &a, const sm &b)
{
	sm res;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			res.m[i][j] = (a.m[i][j]+b.m[i][j]) % MOD;
	return res;
}

//res=a^p
sm operator^(sm a, int p)
{
	sm res;
	res.eye();
	for (; p; p >>= 1)
	{
		if (p & 1)
			res = res * a;
		a = a * a;
	}
	return res;
}

/*已废弃
//res=a^1+a^2+...+a^p
sm sum(const sm &a, int p)//Sum=A^1+A^2+...+A^x
{
	if (p == 1)
		return a;
	if (p & 1)
		return (a^p)+(sum(a, p-1));
	else
		return (sum(a, p>>1))*((a^(p>>1))+sm().eye());
}
*/
