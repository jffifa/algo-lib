/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Minimum Circle Cover
	Version: 0.103
	Date: 2011-5-3
	Remark: Given a point set P, find the circle with minimum radius that covers all the points in P
	Tested Problems: N/A
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/

#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

inline char sgn(double d) {
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

double nrmsqr(const sp &v)
{return v.x*v.x+v.y*v.y;}

double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

bool concylic(const sp &p1, const sp &p2, const sp &p3, sp &c, double r) {
	if (sgn(dir(p1, p2, p3))==0) return 0;
	double t1 = nrmsqr(p1)-nrmsqr(p2);
	double t2 = nrmsqr(p1)-nrmsqr(p3);
	double t3 = 2*(p1.x-p2.x)*(p1.y-p3.y)-2*(p1.x-p3.x)*(p1.y-p2.y);
	c.x = ((p1.y-p3.y)*t1-(p1.y-p2.y)*t2)/t3;
	c.y = -((p1.x-p3.x)*t1-(p1.x-p2.x)*t2)/t3;
	r = dis(c, p1);
	return 1;
}

//mcc:minimum circle cover
//最小圆覆盖
//输入点集大小N，点集p
//返回覆盖所有点的最小圆的圆心c，半径r
void mcc(int N, sp p[], sp &c, double &r) {
	random_shuffle(p, p+N);
	c = p[0]; r = 0;
	for (int i = 1; i < N; ++i)
	if (sgn(dis(p[i],c)-r)>0) {
		c = p[i]; r = 0;
		for (int j = 0; j < i; ++j)
		if (sgn(dis(p[j], c)-r)>0) {
			c.x = (p[i].x+p[j].x)/2;
			c.y = (p[i].y+p[j].y)/2;
			r = dis(p[j], c);
			for (int k = 0; k < j; ++k)
			if (sgn(dis(p[k], c)-r)>0) {
				concylic(p[i], p[j], p[k], c, r);
				r = dis(p[i], c);
			}
		}
	}
}
