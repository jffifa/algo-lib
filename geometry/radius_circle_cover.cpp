/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Radius Circle Cover
	Version: 0.103
	Date: 2011-8-17
	Remark: Given a point set P, find a circle with a given radius R that covers the most points in P
	Tested Problems: Ural1332
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);

inline int sgn(double d) {
	if (fabs(d)<EPS) return 0;
	return d>0?1:-1;
}

struct sp {
	double x, y;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
	void read() {scanf("%lf%lf", &x, &y);}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}


double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

double pa(const sp &p, const sp &p0)
{return atan2(p.y-p0.y, p.x-p0.x);}

struct sarc {
	double a;
	char cnt;
	sarc() {}
	sarc(double aa, int cc): a(aa), cnt(cc) {}
};
bool operator< (const sarc &a1, const sarc &a2) {
	//if (sgn(a1.a-a2.a)==0) return a1.cnt>a2.cnt;
	return a1.a<a2.a;
}

//给定半径圆覆盖
//输入点集大小N，点集p，给定半径r
//返回能覆盖最多点的点数及圆心c
int rcc(int N, sp p[], double r, sp &c) {
	if (sgn(r)<0) return 0;
	c = p[0];
	if (sgn(r)==0) return 1;
	sarc arc[1000];
	int arccnt, swpcnt, res = 1;
	double d, a, da, as, ae;
	for (int i = 0; i < N; ++i) {
		swpcnt = arccnt = 0;
		for (int j = 0; j < N; ++j) {
			if (i==j) continue;
			d = dis(p[i], p[j]);
			if (sgn(d-r-r)>0) continue;
			a = pa(p[j], p[i]);
			da = acos(d/(2*r));
			if (sgn(da)==0) {
				arc[arccnt++] = sarc(a, 1);
				arc[arccnt++] = sarc(a, -1);
				continue;
			}
			as = a-da;
			ae = a+da;
			if (sgn(as+PI)<0) as += 2*PI;
			if (sgn(ae-PI)>0) ae += 2*PI;
			if (sgn(as-ae)>0) {
				arc[arccnt++] = sarc(as, 1);
				arc[arccnt++] = sarc(PI, -1);
				arc[arccnt++] = sarc(-PI, 1);
				arc[arccnt++] = sarc(ae, -1);
			}
			else {
				arc[arccnt++] = sarc(as, 1);
				arc[arccnt++] = sarc(ae, -1);
			}
		}
		sort(arc, arc+arccnt);
		for (int j = 0; j < arccnt; ++j) {
			swpcnt += arc[j].cnt;
			if (swpcnt+1 > res) {
				res = swpcnt+1;
				c.x = p[i].x+r*cos(arc[j].a);
				c.y = p[i].y+r*sin(arc[j].a);
			}
		}
	}
	return res;
}
