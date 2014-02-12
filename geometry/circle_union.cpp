#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

int sgn(double d) {
	if (fabs(d)<EPS) return 0;
	return d>0?1:-1;
}

struct sp {
	double x, y;
	double pa;
	int cnt;
	sp() {}
	sp(double a, double b): x(a), y(b) {}
	sp(double a, double b, double c, int d): x(a), y(b), pa(c), cnt(d) {}
	bool operator<(const sp &rhs) const {
		/* 需要处理单点的情况时
		if (sgn(pa-rhs.pa)==0) return cnt>rhs.cnt;
		*/
		return pa<rhs.pa;
	}
	void read() {scanf("%lf%lf", &x, &y);}
	void write() {printf("%lf %lf\n", x, y);}
};

sp operator+(const sp &u, const sp &v) {
	return sp(u.x+v.x, u.y+v.y);
}

sp operator-(const sp &u, const sp &v) {
	return sp(u.x-v.x, u.y-v.y);
}

double det(const sp &u, const sp &v) {
	return u.x*v.y-v.x*u.y;
}

double dir(const sp &p, const sp &u, const sp &v) {
	return det(u-p, v-p);
}

double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

//计算两圆交点
//输入圆心坐标和半径
//返回两圆是否相交(相切不算)
//如果相交，交点返回在a和b(从a到b为u的交弧)
bool cirint(const sp &u, double ru, const sp &v, double rv, sp &a, sp &b) {
	double d = dis(u, v);
	/* 需要处理单点的情况时 覆盖的情况在这里不统计
	if (sgn(d-(ru+rv))>0 || sgn(d-fabs(ru-rv))<=0) return 0;
	*/
	if (sgn(d-(ru+rv))>=0 || sgn(d-fabs(ru-rv))<=0) return 0;
	sp c = u-v;
	double ca, sa, cb, sb, csum, ssum;

	ca = c.x/d, sa = c.y/d;
	cb = (rv*rv+d*d-ru*ru)/(2*rv*d), sb = sqrt(1-cb*cb);
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

sp e[222];
int cover[111];

//求圆并
//输入点数N，圆心数组p，半径数组r，答案数组s
//s[i]表示被至少i个圆覆盖的面积(最普通的圆并就是s[1])
void circle_union(int N, sp p[], double r[], double s[]) {
	int i, j, k;
	memset(cover, 0, sizeof cover);
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j) {
			double rd = r[i]-r[j];
			//覆盖的情况在这里统计
			if (i!=j && sgn(rd)>0 && sgn(dis(p[i], p[j])-rd)<=0)
				cover[j]++;
		}
	for (i = 0; i < N; ++i) {
		int ecnt = 0;
		e[ecnt++] = sp(p[i].x-r[i], p[i].y, -PI, 1);
		e[ecnt++] = sp(p[i].x-r[i], p[i].y, PI, -1);
		for (j = 0; j < N; ++j) {
			if (j==i) continue;
			if (cirint(p[i], r[i], p[j], r[j], a, b)) {
				e[ecnt++] = sp(a.x, a.y, atan2(a.y-p[i].y, a.x-p[i].x), 1);
				e[ecnt++] = sp(b.x, b.y, atan2(b.y-p[i].y, b.x-p[i].x), -1);
				if (sgn(e[ecnt-2].pa-e[ecnt-1].pa)>0) {
					e[0].cnt++;
					e[1].cnt--;
				}
			}
		}
		sort(e, e+ecnt);
		int cnt = e[0].cnt;
		for (j = 1; j < ecnt; ++j) {
			double pad = e[j].pa-e[j-1].pa;
			s[cover[i]+cnt] += (det(e[j-1], e[j])+r[i]*r[i]*(pad-sin(pad)))/2;
			cnt += e[j].cnt;
		}
	}
}
