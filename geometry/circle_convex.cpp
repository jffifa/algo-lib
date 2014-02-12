#include <cmath>

const double EPS = 1e-8;
const double PI = acos(-1.0);

inline int sgn(double x) {
	if (fabs(x)<EPS) return 0;
	return x>0?1:-1;
}

struct sp {
	double x, y;
	sp() {}
	sp(double a, double b): x(a), y(b) {}
	void read() {scanf("%lf%lf", &x, &y);}
};

struct ss {
	sp a, b;
	ss() {}
	ss(sp u, sp v): a(u), b(v) {}
};

sp operator-(const sp &u, const sp &v) {
	return sp(u.x-v.x, u.y-v.y);
}

sp operator+(const sp &u, const sp &v) {
	return sp(u.x+v.x, u.y+v.y);
}

sp operator*(double d, const sp &v) {
	return sp(d*v.x, d*v.y);
}

double det(const sp &u, const sp &v) {
	return u.x*v.y-v.x*u.y;
}

double dir(const sp &p, const sp &u, const sp &v) {
	return det(u-p, v-p);
}

double dot(const sp &u, const sp &v) {
	return u.x*v.x+u.y*v.y;
}

double da(const sp &u, const sp &v) {
	double res = acos(dot(v, u)/sqrt(dot(u, u)*dot(v, v)));
	return det(u, v)>0?res:-res;
}

double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

double disptoline(const sp &p, const ss &s) {
	return fabs(det(p-s.a, s.b-s.a))/dis(s.b, s.a);
}

bool inside(int N, sp c[], sp p) {
	int l=1, r=N-1, m;
	while (l < r) {
		m = l+r>>1;
		if (sgn(dir(c[0], c[m], p)) <= 0)
			r = m;
		else
			l = m+1;
	}
	if (r==1 || sgn(dir(c[0], c[N-1], p))>=0 || sgn(dir(c[r], c[r-1], p))>=0) return 0;
	return 1;
}

bool onseg(const sp &p, const ss &s) {
	return (s.a.x-p.x)*(s.b.x-p.x)<EPS && (s.a.y-p.y)*(s.b.y-p.y)<EPS;
}

bool linecirint(const sp &c, double r, const ss &s, sp &a, sp &b) {
	if (sgn(disptoline(c, s)-r)>0) return 0;
	sp v = s.b-s.a;
	sp t = s.a+(dot(c, v)-dot(s.a, v))/dot(v, v)*v;
	double d = sqrt(r*r-disptoline(c, s)*disptoline(c, s));
	a = t-d/dis(s.b, s.a)*v;
	b = t+d/dis(s.b, s.a)*v;
	return 1;
}

//圆和凸多边形交的面积
//输入凸多边形必须为逆时针
//p会改变！
double circleconvex(sp o, double r, int N, sp p[]) {
	int i;
	for (i = 0; i < N; ++i)
		p[i] = p[i]-o;
	o = sp(0, 0);
	p[N] = p[0];
	double res = 0;
	for (i = 0; i < N; ++i) {
		bool hmr = sgn(dis(p[i], o)-r)<=0;
		bool mdk = sgn(dis(p[i+1], o)-r)<=0;
		sp a, b;
		if (hmr && mdk) res += det(p[i], p[i+1]);
		else {
			bool x = linecirint(o, r, ss(p[i], p[i+1]), a, b);
			if (!hmr && !mdk) {
				if (x && onseg(a, ss(p[i], p[i+1]))) {
					res += r*r*da(p[i], a);
					res += det(a, b);
					res += r*r*da(b, p[i+1]);
				}
				else
					res += r*r*da(p[i], p[i+1]);
			}
			else if (hmr && !mdk) {
				res += det(p[i], b);
				res += r*r*da(b, p[i+1]);
			}
			else {
				res += det(a, p[i+1]);
				res += r*r*da(p[i], a);
			}
		}
	}
	return res/2;
}
