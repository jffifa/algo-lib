#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

inline int sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1: -1;
}

struct sp {
	double x, y;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

inline bool operator== (const sp &u, const sp &v)
{return sgn(u.x-v.x)==0 && sgn(u.y-v.y)==0;}

struct ss {
	sp a, b;
	ss() {}
	ss(sp u, sp v): a(u), b(v) {}
};

double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

bool coline(const sp &p0, const sp &p1, const sp &p2)
{return sgn(dir(p0, p1, p2))==0;}	

bool online(const sp &p, const ss &s)
{return coline(p, s.a, s.b);}

bool onseg(const sp &p, const ss &s)
{return online(p, s) && (s.a.x-p.x)*(s.b.x-p.x)<EPS && (s.a.y-p.y)*(s.b.y-p.y)<EPS;}

bool sameside(const sp &u, const sp &v, const ss &s)
{return dir(s.b, s.a, u)*dir(s.b, s.a, v)>EPS;}

bool segint(const ss &u, const ss &v) {
	if (!coline(u.a, u.b, v.a) || !coline(u.a, u.b, v.b))
		return !sameside(u.a, u.b, v) && !sameside(v.a, v.b, u);
	else
		return onseg(u.a, v) || onseg(u.b, v) || onseg(v.a, u) || onseg(v.b, u);
}

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
	else
	{
		double t = a2*b1-a1*b2;
		p.x = (b2*c1-b1*c2)/t;
		p.y = (a1*c2-a2*c1)/t;
		return 2;
	}
}

int polycut(int N, sp p[], const ss &s, const sp &side, sp q[]) {
	sp pp[111];
	int M = 0, res = 0, i;
	for (i = 0; i < N; ++i) {
		if (sameside(p[i], side, s))
			pp[M++] = p[i];
		if (!sameside(p[i], p[(i+1)%N], s)
			&& !(sgn(dir(s.b, p[i], s.a))==0
			&& sgn(dir(s.b, p[(i+1)%N], s.a))==0))
			lineintp(ss(p[i], p[(i+1)%N]), s, pp[M++]);
	}
	for (res = i = 0; i < M; ++i) {
		if (!i || sgn(pp[i].x-pp[i-1].x)!=0 || sgn(pp[i].y-pp[i-1].y)!=0)
			q[res++] = pp[i];
	}
	if (sgn(q[res-1].x-q[0].x)==0 && sgn(q[res-1].y-q[0].y)==0)
		res--;
	if (res < 3) res = 0;
	return res;
}

bool cmp(const sp &u, const sp &v) {
	if (sgn(u.y-v.y)==0) return u.x>v.x;
	return u.y>v.y;
}

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

//凸多边形交
//输入两个多边形p和q（逆时针）及相应点数N和M
//返回两个多边形的交于r，返回点数
//graham为可选步骤，最好做一下保证正确性
int polyint(int N, sp p[], int M, sp q[], sp r[]) {
	int i, j, k;
	sp t[111];
	for (i = 0; i < N; ++i)
		t[i] = p[i];
	int res = N;
	for (i = 0; i < M; ++i) {
		res = polycut(res, t, ss(q[i], q[(i+1)%M]), q[(i+2)%M], t);
		if (res==0) return 0;
	}
	res = graham(res, t, r);
	return res;
}

