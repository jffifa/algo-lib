/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]AkemiHomura
	Category: Geometry
	Title: Graham Scan
	Version: 0.314
	Date: 2011-1-31
	Remark: Find the the convex hull of point set P
	Tested Problems: POJ1113
	Tag: geometry, convex hull, Graham Scan
	Special Thanks: Amber
*/
/*
	Input:
		A set of points p[]
	Output:
		The convex hull ch[], and the number of the points in it
*/

#include <cmath>
#include <algorithm>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-8;
const double PI = acos(-1.0);

inline int sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1 : -1;
}

struct sp {
	double x, y;
	sp () {}
	sp (double xx, double yy): x(xx), y(yy) {}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

bool cmp(const sp &u, const sp &v) {
	if (sgn(u.y-v.y)==0) return u.x>v.x;
	return u.y>v.y;
}

//输入点数N，点集p，bool变量in表示是否包括三点共线中间点，默认为false，为true可能会退化
//返回凸包点数，凸包集ch
int graham(int N, sp p[], sp ch[], bool in = 0) {
	const double e = in ? EPS : -EPS;
	int i, j, k;
	if (N < 3)
	{
		for (i = 0; i < N; ++i)
			ch[i] = p[i];
		return N;
	}

	sort(p, p+N, cmp);
	ch[0] = p[0];
	ch[1] = p[1];
	for (i = j = 2; i < N; ch[j++]=p[i++])
		while (j>1 && dir(ch[j-1], ch[j-2], p[i])>e) --j;
	ch[k=j++] = p[N-2];
	for (i = N-3; i > 0; ch[j++]=p[i--])
		while (j>k && dir(ch[j-1], ch[j-2], p[i])>e) --j;
	while (j>k && dir(ch[j-1], ch[j-2], ch[0])>e) --j;
	return j;
}

