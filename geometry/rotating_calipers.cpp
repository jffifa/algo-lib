/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Geometry
	Title: Rotating Calipers
	Version: 0.314
	Date: 2011/2/6
	Remark: N/A
	Tested Problems: N/A
	Tag: geometry, rotating calipers
	Special Thanks: Amber
*/
/*
	Input:
		A convex hull by counterclockwise
	Output:
		The maximum distance of pairs of points
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-8;
const double PI = acos(-1.0);

inline char sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1 : -1;
}

struct sp {
	double x, y;
	double dis, ang;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
};

sp operator - (const sp &v1, const sp &v2)
{return sp(v1.x-v2.x, v1.y-v2.y);}

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

double rotatingcalipers(int N, sp poly[]) {
	poly[N] = poly[0];
	int p=0, q=1;
	double ans = 0;
	for (; p < N; ++p)
	{
		while (sgn(dir(poly[p], poly[p+1], poly[q+1])-dir(poly[p], poly[p+1], poly[q])) > 0)
			q = (q+1) % N;
		ans = max(ans, max(dis(poly[p], poly[q]), dis(poly[p+1], poly[q+1])));
	}
	return ans;
}

/*
begin
     p0:=pn;
     q:=NEXT[p];
     while (Area(p,NEXT[p],NEXT[q]) > Area(p,NEXT[p],q)) do
          q:=NEXT[q];
          q0:=q;
          while (q != p0) do
               begin
                    p:=NEXT[p];
                    Print(p,q);
                    while (Area(p,NEXT[p],NEXT[q]) > Area(p,NEXT[p],q) do
                         begin
                              q:=NEXT[q];
                              if ((p,q) != (q0,p0)) then Print(p,q)
                              else return
                         end;
                    if (Area(p,NEXT[p],NEXT[q]) = Area(p,NEXT[p],q)) then
                      if ((p,q) != (q0,p0)) then Print(p,NEXT[q])
                      else Print(NEXT[p],q)
               end
end.
*/
