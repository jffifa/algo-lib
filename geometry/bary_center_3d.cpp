//以下均为质量均匀分布的情况(均分至面积/体积)
#include <cstdio>
#include <cmath>

struct sp {
	double x, y, z;
	sp() {}
	sp(double a, double b, double c): x(a), y(b), z(c) {}
	bool read() {return scanf("%lf%lf%lf", &x, &y, &z)==3;}
	void write() {printf("%f %f %f\n", x, y, z);}
};

//空间三角形重心(需保证三点不共线)
sp bc(const sp &a, const sp &b, const sp &c) {
	return sp(
		(a.x+b.x+c.x)/3,
		(a.y+b.y+c.y)/3,
		(a.z+b.z+c.z)/3
		);
}

//四面体重心(需保证四点不共面)
sp bc(const sp &a, const sp &b, const sp &c, const sp &d) {
	return sp(
		(a.x+b.x+c.x+d.x)/4,
		(a.y+b.y+c.y+d.y)/4,
		(a.z+b.z+c.z+d.z)/4
		);
}

//凸多面体重心
//HDU4273
//需要三维凸包模板
sp bc(int N, sp p[]) {
	ch3d.N = N;
	int i;
	for (i = 0; i < N; ++i)
		ch3d.p[i] = p[i];
	ch3d.ch();
	sp res = sp(0, 0, 0), t;
	double t1 = 0, t2;
	for (i = 0; i < ch3d.cnt; ++i)
		if (sgn(t2=ch3d.dir(ch3d.f[i], ch3d.p[0]))) {
			t = bc(ch3d.p[0], ch3d.p[ch3d.f[i].a], ch3d.p[ch3d.f[i].b], ch3d.p[ch3d.f[i].c]);
			res = res+t2*t;
			t1 += t2;
		}
	if (sgn(t1)) res = 1/t1*res;
	return res;
}
