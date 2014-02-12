/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Geometry
	Title: Geometry Base 3d ver Header
	Version: 0.314
	Date: 2012-08-26
	Remark: Structure definations and base functions
	Tested Problems: N/A
	Tag: Geometry
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi, lxyxynt@UESTC_Kyouko, thomas0726@UESTC_Kyouko
*/

#ifndef GEOMETRY_BASE_3D_H
#define GEOMETRY_BASE_3D_H

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/***<常量表****/
const int MAXN = 1000;
const double INF = 1e10;
const double EPS = 1e-8;
const double PI = acos(-1.0);
/****常量表>***/

/***<浮点函数****/
inline int sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1: -1;
}

inline double min(double a, double b)
{return a<b ? a : b;}

inline double max(double a, double b)
{return a>b ? a : b;}

inline double sqr(double x) {
	return x*x;
}
/****浮点函数>***/

/***<点/向量定义与运算****/
struct sp {
	double x, y, z;
	sp() {}
	sp(double a, double b, double c): x(a), y(b), z(c) {}
	bool read() {return scanf("%lf%lf%lf", &x, &y, &z)==3;}
	void write() {printf("%f %f %f\n", x, y, z);}
};

sp operator-(const sp &u, const sp &v) {
	return sp(u.x-v.x, u.y-v.y, u.z-v.z);
}

sp operator+(const sp &u, const sp &v) {
	return sp(u.x+v.x, u.y+v.y, u.z+v.z);
}

//数乘
sp operator*(double d, const sp &v) {
	return sp(d*v.x, d*v.y, d*v.z);
}

//范数
double nrm(const sp &v) {
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

//范数平方
double nrmsqr(const sp &v) {
	return v.x*v.x+v.y*v.y+v.z*v.z;
}

//内积(点积)
double dot(const sp &u, const sp &v) {
	return u.x*v.x+u.y*v.y+u.z*v.z;
}

//外积(叉积)
sp det(const sp &u, const sp &v) {
	return sp(u.y*v.z-v.y*u.z,
			u.z*v.x-u.x*v.z,
			u.x*v.y-u.y*v.x);
}

//三角形有向面积*2
//(p, u, v)确定的右手系
sp dir(const sp &p, const sp &u, const sp &v) {
	return det(u-p, v-p);
}

//三角形面积*2
double area(const sp &a, const sp &b, const sp &c) {
	return nrm(dir(a, b, c));
}

//四面体有向体积*6
//正负代表p在(v-u, w-u)所确定右手系平面的方向
double volume(const sp &u, const sp &v, const sp &w, const sp &p) {
	return dot(dir(u, v, w), p-u);
}

const sp ORIGIN = sp(0, 0, 0);
/****点/向量定义与运算>***/

/***<线段/直线定义****/
struct ss
{
	sp a, b;
	ss() {}
	ss(sp u, sp v): a(u), b(v) {}
};
/****线段/直线定义>***/

/***<平面定义****/
struct splane {
	sp a, b, c;
	splane() {}
	splane(sp u, sp v, sp w): a(u), b(v), c(w) {}
};

//法向量
sp nv(const splane &s) {
	return det(s.a-s.b, s.b-s.c);
}

//ax+by+cz+d=0
struct splanef {
	double a, b, c, d;
	splanef() {}
	splanef(double p, double q, double r, double s): a(p), b(q), c(r), d(s) {}
	splanef(const splane &p) {
		sp m = det(p.b-p.a, p.c-p.a);
		a = m.x, b = m.y, c = m.z;
		d = -m.x*p.a.x-m.y*p.a.y-m.z*p.a.z;
	}
};
/****平面定义>***/

/***<点与线基本函数****/
//两点距离
double dis(const sp &u, const sp &v) {
	return sqrt(sqr(u.x-v.x)+sqr(u.y-v.y)+sqr(u.z-v.z));
}

//三点共线
bool coline(const sp &p1, const sp &p2, const sp &p3) {
	return nrmsqr(det(p1-p2,p2-p3))<EPS;
}

//四点共面
bool coplane(const sp &a, const sp &b, const sp &c, const sp &d) {
	return sgn(dot(det(c-a, b-a), d-a))==0;
}

//点在直线上
bool online(const sp &p, const ss &l) {
	return coline(p, l.a, l.b);
}

//点在线段上，包括端点
bool onseg(const sp &p, const ss &l) {
	return sgn(nrmsqr(det(p-l.a, p-l.b)))==0 &&
		(l.a.x-p.x)*(l.b.x-p.x)<EPS &&
		(l.a.y-p.y)*(l.b.y-p.y)<EPS &&
		(l.a.z-p.z)*(l.b.z-p.z)<EPS;
}

//点在线段上，不包括端点
bool onsegex(const sp &p, const ss &l) {
	return onseg(p, l) &&
		(sgn(p.x-l.a.x)||sgn(p.y-l.a.y)||sgn(p.z-l.a.z)) &&
		(sgn(p.x-l.b.x)||sgn(p.y-l.b.y)||sgn(p.z-l.b.z));
}

//点在空间三角形上，包括边界，三点共线无意义
bool onplane(const sp &p, const splane &s) {
	return sgn(nrm(det(s.a-s.b, s.a-s.c))-
			nrm(det(p-s.a, p-s.b))-
			nrm(det(p-s.b, p-s.c))-
			nrm(det(p-s.c, p-s.a)))==0;
}

//点在空间三角形上，不包括边界，三点共线无意义
bool onplaneex(const sp &p, const splane &s) {
	return onplane(p, s) &&
		nrmsqr(det(p-s.a, p-s.b))>EPS &&
		nrmsqr(det(p-s.b, p-s.c))>EPS &&
		nrmsqr(det(p-s.c, p-s.a))>EPS;
}

//两点在直线同侧，点在线段上返回0，不共面无意义
bool sameside(const sp &u, const sp &v, const ss &l) {
	return dot(det(l.a-l.b, p-l.b),det(l.a-l.b, q-l.b))>EPS;
}

//两点在直线异侧，点在线段上返回0，不共面无意义
bool oppositeside(const sp &u, const sp &v, const ss &l) {
	return dot(det(l.a-l.b, p-l.b),det(l.a-l.b, q-l.b))<-EPS;
}

//两点在平面同侧，点在平面上返回0
bool sameside(const sp &u, const sp &v, const splane &s) {
	return dot(nv(s), det(p-s.a))*dot(nv(s),det(q-s.a))>EPS;
}

//两点在平面同侧，点在平面上返回0
bool sameside(const sp &u, const sp &v, const splanef &s) {
	return (s.a*u.x+s.b*u.y+s.c*u.z+s.d)*(s.a*v.x+s.b*v.y+s.c*v.z+s.d)>EPS;
}

//判两点在平面异侧，点在平面上返回0
bool oppositeside(const sp &u, const sp &v, const splane &s) {
	return dot(nv(s), det(p-s.a))*dot(nv(s),det(q-s.a))<-EPS;
}

//判两点在平面异侧，点在平面上返回0
bool oppositeside(const sp &u, const sp &v, const splanef &s) {
	return (s.a*u.x+s.b*u.y+s.c*u.z+s.d)*(s.a*v.x+s.b*v.y+s.c*v.z+s.d)<-EPS;
}

//判两直线平行
bool parallel(const ss &u, const ss &v) {
	return nrmsqr(det(u.a-u.b, v.a-v.b))<EPS;
}

//判两平面平行
bool parallel(const splane &u, const splane &v) {
	return nrmsqr(det(nv(u), nv(v)))<EPS;
}

//点到直线距离(直线不可以退化)
double disptoline(const sp &p, const ss &l) {
	return nrm(det(p-l.a, l.b-l.a))/dis(l.a, l.b);
}

//点到直线最近点
sp ptoline(const sp &p, const ss &l) {
	sp ab = l.b-l.a;
	double t = -dot(p-l.a, ab)/nrmsqr(ab);
	ab = t*ab;
	return l.a-ab;
}

//点到线段距离
double disptoseg(const sp &p, const ss &l) {
	sp q = ptoline(p, l);
	if (onseg(q, l)) return dis(p, q);
	return min(dis(p, l.a), dis(p, l.b));
}

//点到线段最近点
sp ptoseg(const sp &p, const ss &l) {
	sp q = ptoline(p, l);
	if (onseg(q, l)) return q;
	return dis(p, l.a)<dis(p, l.b)?l.a:l.b;
}

//直线到直线最短距离
double dislinetoline(const ss &u, const ss &v) {
	sp n = det(u.a-u.b, v.a-v.b);
	if (nrmsqr(n)<EPS) //两直线平行
		return disptoline(u.a, v);
	else
		return fabs(dot(u.a-v.a, n))/nrm(n);
}

//直线到直线最近点对(需要保证直线不平行)
//返回p在u上，q在v上
void linetoline(const ss &u, const ss &v, sp &p, sp &q) {
	//assert(!parallel(u, v));
	sp ab = u.b-u.a, cd = v.b-v.a, ac = v.a-u.a;
	double r = (dot(ab, cd)*dot(ac, ab)-nrmsqr(ab)*dot(ac, cd)) /
		(nrmsqr(ab)*nrmsqr(cd)-sqr(dot(ab, cd)));
	q = v.a+(r*cd);
	p = ptoline(q, u);
}

//线段到线段最短距离
double dissegtoseg(const ss &u, const ss &v) {
	double res = INF;
	res = min(res, disptoseg(u.a, v));
	res = min(res, disptoseg(u.b, v));
	res = min(res, disptoseg(v.a, u));
	res = min(res, disptoseg(v.b, u));
	if (!parallel(u, v)) {
		sp p, q;
		linetoline(u, v, p, q);
		if (onseg(p, u) && onseg(q, v))
			res = min(res, dis(p, q));
	}
	return res;
}

#endif
