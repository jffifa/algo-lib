/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Bary Center 
	Version: 0.103
	Date: 2011-8-24
	Remark: Structure definations and base functions
	Tested Problems: N/A
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/

#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-8;

inline int sgn(double d)
{
	if (fabs(d) < EPS) return 0;
	return d>0?1:-1;
}

struct sp {
	double x, y;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

inline sp operator+ (const sp &u, const sp &v)
{return sp(u.x+v.x, u.y+v.y);}

inline sp operator* (double d, const sp &v)
{return sp(v.x*d, v.x*d);}

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

//三角形重心
sp bc(const sp &a, const sp &b, const sp &c) {
	double x = (a.x+b.x+c.x)/3;
	double y = (a.y+b.y+c.y)/3;
	return sp(x, y);
}
	
//多边形重心
//输入点数N，点集p
//返回重心
sp bc(int N, sp p[]) {
	sp res = sp(0, 0), t;
	double t1 = 0, t2;
	for (int i = 0; i < N-1; ++i)
		if (sgn(t2=dir(p[0], p[i], p[i+1]))) {
			t = bc(p[0], p[i], p[i+1]);
			res = res+(t2*t);
			t1 += t2;
		}
	if (sgn(t1)) res = 1/t1*res;
	return res;
}
