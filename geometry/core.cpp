/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Geometry
	Title: Core
	Version: 0.314
	Date: 2011-5-1
	Remark: Find a core of a simple polygon poly
	Tested Problems: POJ3130
	Tag: geometry, core
	Special Thanks: Amber
*/
/*
	Input:
		The size of the polygon N, the polygon poly (points in counterclockwise order)
	Output:
		Output: if there exists a core of polygon poly return true while make point P a core, otherwise false
*/

#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

inline int sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1: -1;
}

struct sp {
	double x, y;
	int id;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

struct ss {
	sp a, b;
	ss() {}
	ss(sp u, sp v): a(u), b(v) {}
};

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

char lineintp(const ss &u, const ss &v, sp &p) {
	double a1, b1, c1, a2, b2, c2;
	a1 = u.b.y - u.a.y;
	b1 = u.a.x - u.b.x;
	c1 = det(u.b, u.a);
	a2 = v.b.y - v.a.y;
	b2 = v.a.x - v.b.x;
	c2 = det(v.b, v.a);
	if (sgn(a1*b2-b1*a2)==0)
		if (sgn(det(u.a-v.a, u.a-v.b))==0) return 0;
		else return 1;
	else {
		double t = a2*b1-a1*b2;
		p.x = (b2*c1-b1*c2)/t;
		p.y = (a1*c2-a2*c1)/t;
		return 2;
	}
}

bool core(int N, sp poly[], sp &p) {
	bool found;
	poly[N] = poly[0];
	for (int i = 0; i < N; ++i) {
		for (int j = i+1; j < N; ++j) {
			if (lineintp(ss(poly[i], poly[i+1]), ss(poly[j], poly[j+1]), p) == 2) {
				found = 1;
				for (int k = 0; k < N; ++k)
					if (sgn(dir(poly[k], poly[k+1], p)) == -1) {found = 0; break;}
				if (found) return 1;
			}
		}
	}
	return 0;
}
