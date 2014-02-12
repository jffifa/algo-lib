/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Geometry Base Header
	Version: 0.103
	Date: 2011-5-3
	Remark: Structure definations and base functions
	Tested Problems: N/A
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/

#ifndef GEOMETRY_BASE_H
#define GEOMETRY_BASE_H

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/***<常量表****/
const int MAXN = 1000;
const double INF = 1e9;
const double EPS = 1e-8;
const double PI = acos(-1.0);
/****常量表>***/

/***<浮点函数****/
inline int sgn(double d)
{
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1: -1;
}

inline double min(double a, double b)
{return a<b ? a : b;}

inline double max(double a, double b)
{return a>b ? a : b;}
/****浮点函数>***/

/*******<平面几何********/

/***<点/向量定义与运算****/
struct sp {
	double x, y;
	double d, a;
	int id;
	sp() {}
	sp(double xx, double yy): x(xx), y(yy) {}
	bool read() {return scanf("%lf%lf", &x, &y)==2;}
	void write() {printf("%f %f\n", x, y);}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

inline sp operator+ (const sp &u, const sp &v)
{return sp(u.x+v.x, u.y+v.y);}

inline sp operator* (double d, const sp &v)
{return sp(v.x*d, v.y*d);}

inline bool operator== (const sp &u, const sp &v)
{return sgn(u.x-v.x)==0 && sgn(u.y-v.y)==0;}

inline bool operator!= (const sp &u, const sp &v)
{return !(u == v);}

const sp ORIGIN = sp(0, 0);
/****点/向量定义与运算>***/

/***<线段/直线定义****/
struct ss {
	sp a, b;
	ss() {}
	ss(sp u, sp v): a(u), b(v) {}
};
/****线段/直线定义>***/

/***<点与线基本函数****/
//向量范数平方
double nrmsqr(const sp &v)
{return v.x*v.x + v.y*v.y;}

//点积
double dot(const sp &u, const sp &v)
{return u.x*v.x + u.y*v.y;}

//叉积
double det(const sp &u, const sp &v)
{return u.x*v.y - v.x*u.y;}

//(u-p)x(v-p)
//等于0表示3点共线
//大于0表示pv在pu的逆时针，小于0表示pv在pu的顺时针
double dir(const sp &p, const sp &u, const sp &v)
{return det(u-p, v-p);}

//两点距离
double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

//两点距离平方，针对精度问题
double dissqr(const sp &u, const sp &v)
{return nrmsqr(v-u);}

//点到直线距离
double disptoline(const sp &p, const ss &s)
{return fabs(det(p-s.a, s.b-s.a))/dis(s.b, s.a);}

//点到直线最近点
sp ptoline(const sp &p, const ss &s) {
	sp v = s.b-s.a;
	double t = (dot(p, v)-dot(s.a, v))/dot(v, v);
	return s.a+t*v;
}

//点到线段最近点
sp ptoseg(const sp &p, const ss &s) {
	sp v = s.b-s.a, res;
	double t = (dot(p, v)-dot(s.a, v))/dot(v, v);
	if (sgn(t)>=0 && sgn(t-1)<=0)
		res = s.a+(t*v);
	else
		res = dis(p, s.a)<dis(p, s.b) ? s.a : s.b;
	return res;
}

//点到线段距离
double disptoseg(const sp &p, const ss &s)
{return dis(p, ptoseg(p, s));}

//线段到线段最短距离
double dissegtoseg(const ss &u, const ss &v) {
	double res = INF;
	res = min(res, disptoseg(u.a, v));
	res = min(res, disptoseg(u.b, v));
	res = min(res, disptoseg(v.a, u));
	res = min(res, disptoseg(v.b, u));
	return res;
}

//p相对p0极角
double pa(const sp &p, const sp &p0 = ORIGIN)
{return atan2(p.y-p0.y, p.x-p0.x);}

//向量u到v的到角
double da(const sp &u, const sp &v) {
	double res = acos(dot(v, u)/sqrt(dot(u, u)*dot(v, v)));
	return det(u, v)>0?res:-res;
}

//向量u-p到v-p的到角
double da(const sp &p, const sp &u, const sp &v) {
	return da(u-p, v-p);
}

//将点p绕点p0旋转a弧度
sp rotate(const sp &p, double a, const sp &p0 = ORIGIN) {
	sp res = p0, v = p-p0;
	double c = cos(a), s = sin(a);
	res.x += v.x*c-v.y*s;
	res.y += v.x*s+v.y*c;
	return res;
}

//判三点共线
bool coline(const sp &p0, const sp &p1, const sp &p2)
{return sgn(dir(p0, p1, p2))==0;}	

//点p是否在直线s上
bool online(const sp &p, const ss &s)
{return coline(p, s.a, s.b);}

//点p是否在线段s上
bool onseg(const sp &p, const ss &s)
{return online(p, s) && (s.a.x-p.x)*(s.b.x-p.x)<EPS && (s.a.y-p.y)*(s.b.y-p.y)<EPS;}

//判两点在线段同侧，点在线段上返回0
bool sameside(const sp &u, const sp &v, const ss &s)
{return dir(s.b, s.a, u)*dir(s.b, s.a, v)>EPS;}

//判两点在线段异侧，点在线段上返回0
bool oppositeside(const sp &u, const sp &v, const ss &s)
{return dir(s.b, s.a, u)*dir(s.b, s.a, v)<-EPS;}

//直线u和v是否相交
bool lineint(const ss &u, const ss &v)
{return sgn(det(u.b-u.a, v.b-v.a))!=0;}

//线段u和v是否相交（包括端点）
bool segint(const ss &u, const ss &v) {
	if (!coline(u.a, u.b, v.a) || !coline(u.a, u.b, v.b))
		return !sameside(u.a, u.b, v) && !sameside(v.a, v.b, u);
	else
		return onseg(u.a, v) || onseg(u.b, v) || onseg(v.a, u) || onseg(v.b, u);
}

//计算两直线交点，结果赋予p
//返回值: 0 共线, 1 平行, 2 相交
char lineintp(const ss &u, const ss &v, sp &p) {
	double a1, b1, c1, a2, b2, c2;
	a1 = u.b.y - u.a.y;
	b1 = u.a.x - u.b.x;
	c1 = det(u.b, u.a);
	a2 = v.b.y - v.a.y;
	b2 = v.a.x - v.b.x;
	c2 = det(v.b, v.a);
	//判断是否共线或平行，确定相交时可以去掉
	if (sgn(a1*b2-b1*a2)==0)
		//There may be some mistakes
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
/****点与线基本函数>***/

/***<面积****/
//三角形三个点有向面积
double area(const sp &a, const sp &b, const sp &c)
{return dir(a, b, c)/2;}
//三角形三条边面积
double area(double p, double q, double r) {
	double s = (p+q+r)/2;
	return sqrt(s*(s-p)*(s-q)*(s-r));
}

//多边形面积
double area(int N, sp poly[]) {
	double res = 0;
	if (N < 3) return 0;
	for (int i = 0; i < N; ++i)
		res += det(poly[i], poly[(i+1)%N]);
	return res/2;
}
/****面积>***/

/***<圆****/
//直线和圆的交点
//不相交返回0
//a为靠近s.a的交点，b为靠近s.b的交点
bool linecirint(const sp &c, double r, const ss &s, sp &a, sp &b) {
	if (sgn(disptoline(c, s)-r)>0) return 0;
	sp v = s.b-s.a;
	sp t = s.a+(dot(p, v)-dot(s.a, v))/dot(v, v)*v;
	double d = sqrt(r*r-disptoline(c, s)*disptoline(c, s));
	a = t-d/dis(s.b, s.a)*v;
	b = t+d/dis(s.b, s.a)*v;
	return 1;
}

//求点到圆的切点
//求出后可直接求切线
//点在圆内返回0，圆上返回1与点本身，否则返回2与两个切点
char tgp(const sp &c, double r, const sp &p, sp &u, sp &v) {
	char cv = sgn(dis(p, c)-r);
	if (cv < 0) return 0;
	if (cv == 0) {u = p; return 1;}
	double a = pa(p, c);
	double da = acos(r/dis(p, c));
	u.x = c.x+r*cos(a+da); u.y = c.y+r*sin(a+da);
	v.x = c.x+r*cos(a-da); v.y = c.y+r*sin(a-da);
	return 2;
}

//两圆外公切线
//输入两圆心和半径
//返回两直线s和t
//s和t的a对应u上切点，b对应v上切点
void cotgl(const sp &u, double ru, const sp &v, double rv, ss &s, ss &t) {
	double dr = ru-rv;
	double d = dis(u, v);
	double a = acos(dr/d);
	sp dv = v-u;
	s.a = u+ru/d*rotate(dv, a); s.b = v+rv/d*rotate(dv, a);
	t.a = u+ru/d*rotate(dv, -a); t.b = v+rv/d*rotate(dv, -a);
}

//两圆内公切线
//输入两圆心和半径
//返回两直线s和t
//s和t的a对应u上切点，b对应v上切点
void citgl(const sp &u, double ru, const sp &v, double rv, ss &s, ss &t) {
	double dr = ru+rv;
	double d = dis(u, v);
	double a = acos(dr/d);
	sp dv = v-u;
	s.a = u+ru/d*rotate(dv, a); s.b = v+rv/d*rotate(dv, a-PI);
	t.a = u+ru/d*rotate(dv, -a); t.b = v+rv/d*rotate(dv, PI-a);
}

//求三点共圆
//共圆返回true，并返回圆心，半径，否则返回false
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

//两圆交点
//返回两圆是否相交（相切不算）
//交点返回在a和b中
bool cirint(const sp &u, double ru, const sp &v, double rv, sp &a, sp &b) {
	double d = dis(u, v);
	if (sgn(d-(ru+rv))>=0 || sgn(d-fabs(ru-rv))<=0) return 0;
	sp c = u-v;
	double ca, sa, cb, sb, csum, ssum;

	ca = c.x/d, sa = c.y/d;
	cb = (rv*rv+d*d-ru*ru)/2/rv/d, sb = sqrt(1-cb*cb);
	csum = ca*cb-sa*sb;
	ssum = sa*cb+sb*ca;
	a = sp(rv*csum, rv*ssum);
	a = a+v;

	sb = -sb;
	csum = ca*cb-sa*sb;
	ssum = sa*cb+sb*ca;
	b = sp(rv*csum, rv*ssum);
	b = b+v;

	return 1;
}
/****圆>***/

/***<多边形****/
//多边形p是否以逆时针顺序给出
bool ccw(int N, sp p[]) {
	double cnt = 0;
	for (int i = 0; i < N; ++i)
		cnt += dir(p[i], p[(i+1)%N], ORIGIN);
	return sgn(cnt) > 0;
}

//点p是否在凸多边形c内
//输入：N为凸多边形点数，c为凸多边形，p为点。c中的点必须按逆时针序给出。
//输出：返回1表示（严格）在内部，0表示不在内部。
bool inside(int N, sp c[], sp p) {
	int l=1, r=N-1, m;
	while (l < r)
	{
		m = l+r>>1;
		if (sgn(dir(c[0], c[m], p)) <= 0)
			r = m;
		else
			l = m+1;
	}
	if (r==1 || sgn(dir(c[0], c[N-1], p))>=0 || sgn(dir(c[r], c[r-1], p))>=0) return 0;
	return 1;
}

//多边形切割
//将N个点的多边形p（逆时针输入）按直线s切割，留下side方向的部分
//剩下的部分返回在q(逆时针），返回q的点数
//可用于半平面交和多边形交
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
/****多边形>***/

//Scan Line

//Ring Scan Line
//return how many points in the half plane left to the line determined by P[Origin](origin) and P[j]
//NOT include points on the radial (P[Origin], P[st]),
//BUT may include points on the reverse radial (st from P[Origin], and the reverse direction), it depends
//ptmp is a copy of point set P
inline bool cmp(const sp &u, const sp &v)
{return u.a < v.a;}
void ringscan(int N, sp p[], int origin, int cnt[]) {
	sp ptmp[MAXN];
	for (int i = 0; i < N; ++i)
	{
		ptmp[i] = p[i];
		ptmp[i].id = i;
	}
	swap(ptmp[origin], ptmp[N-1]);
	for (int i = 0; i < N-1; ++i)
		ptmp[i].a = atan2(ptmp[i].y-ptmp[N-1].y, ptmp[i].x-ptmp[N-1].x);
	sort(ptmp, ptmp+N-1, cmp);
	//NOT include points in the reverse radial
	for (int st = 0, ed = 0; st < N-1; ++st)
	{
		if (ed == st) ed++;
		while ((ed<st+N-1) && (sgn(dir(ptmp[N-1], ptmp[st], ptmp[ed%(N-1)]))>0)) ed++;
		cnt[st] = ed-1-st;
	}
	//include points in the reverse radial
	/*
	for (int st = 0, ed = 0; st < N-1; ++st)
	{
		while ((ed<st+N-1) && (sgn(dir(ptmp[N-1], ptmp[st], ptmp[ed%(N-1)]))>=0)) ed++;
		cnt[st] = ed-1-st;
	}
	*/
}

#endif
