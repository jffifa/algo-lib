#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

//扩展中国剩余定理
//处理模线性方程组x=a[i](mod m[i])

int gcd(int a, int b) {
	return b?gcd(b, a%b):a;
}

int extgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1; y = 0;
		return a;
	}
	int res = extgcd(b, a%b, x, y);
	int t = x; x = y; y = t-a/b*y;
	return res;
}

//求a对m的乘法逆元
//不存在返回0
int inv(int a, int m) {
	int x, y;
	if (extgcd(a, m, x, y) != 1) return 0;
	return (x%m+m)%m;
}

//合并两个方程
//x=a1(mod m1)
//x=a2(mod m2)
//返回是否有解
bool merge(int m1, int a1, int m2, int a2, int &m, int &a) {
	int t1=m1, t2=m2;
	a = (a2-a1)%m2; if (a<0) a+=m2;
	int g = gcd(m1, m2);
	if (a%g) return 0;
	a /= g; m1 /= g; m2 /= g;
	a = a*inv(m1, m2)%m2*t1+a1;
	m = t1*t2/g;
	a %= m;
	return 1;
}
