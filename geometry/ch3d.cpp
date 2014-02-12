#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 1111;
const double EPS = 1e-8;

inline int sgn(double d) {
	if (fabs(d) < EPS) return 0;
	return d>0 ? 1: -1;
}

struct sp {
	double x, y, z;
	sp() {}
	sp(double a, double b, double c): x(a), y(b), z(c) {}
	bool read() {return scanf("%lf%lf%lf", &x, &y, &z)==3;}
};

sp operator-(const sp &u, const sp &v) {
	return sp(u.x-v.x, u.y-v.y, u.z-v.z);
}

double dot(const sp &u, const sp &v) {
	return u.x*v.x+u.y*v.y+u.z*v.z;
}

sp det(const sp &u, const sp &v) {
	return sp(u.y*v.z-v.y*u.z,
			u.z*v.x-u.x*v.z,
			u.x*v.y-u.y*v.x);
}

sp dir(const sp &p, const sp &u, const sp &v) {
	return det(u-p, v-p);
}

double nrm(const sp &v) {
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
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

//四点共面(计算凸包有多少面时需要)
bool coplane(const sp &a, const sp &b, const sp &c, const sp &d) {
	return sgn(dot(det(c-a, b-a), d-a))==0;
}

//三维凸包的表面三角形
struct sf {
	int a, b, c;//三个顶点编号
	bool ok;//面是否最终是凸包上的面
	sf() {}
	sf(int p, int q, int r, bool b): a(p), b(q), c(r), ok(b) {}
};

struct sch3d {

	int N;//初始点数
	sp p[MAX];//初始点，注意：点顺序将被打乱！

	int cnt;//凸包所有表面三角形数
	sf f[MAX];//凸包所有表面三角形

	int to[MAX][MAX];//标记数组

	double dir(const sf &t, const sp &u) {
		return ::volume(p[t.a], p[t.b], p[t.c], u);
	}

	void deal(int t, int a, int b) {
		int fid = to[a][b];
		if (f[fid].ok) {
			if (dir(f[fid], p[t]) > EPS) dfs(t, fid);
			else {
				to[t][b] = to[a][t] = to[b][a] = cnt;
				f[cnt++] = sf(b, a, t, 1);
			}
		}
	}

	void dfs(int t, int cur) {
		f[cur].ok = 0;
		deal(t, f[cur].b, f[cur].a);
		deal(t, f[cur].c, f[cur].b);
		deal(t, f[cur].a, f[cur].c);
	}

	//构建三维凸包
	void ch() {
		cnt = 0;
		if (N < 4) return;

		int i, j, k;

		//保证前四个点不共面
		while (1) {
			random_shuffle(p, p+N);
			if (!::coplane(p[0], p[1], p[2], p[3])) break;
		}

		sf now;
		for (i = 0; i < 4; ++i) {
			now = sf(i+1&3, i+2&3, i+3&3, 1);
			if (dir(now, p[i]) > 0) swap(now.b, now.c);
			to[now.a][now.b] = to[now.b][now.c] = to[now.c][now.a] = cnt;
			f[cnt++] = now;
		}
		
		for (i = 4; i < N; ++i)
			for (j = 0; j < cnt; ++j)
				if (f[j].ok && dir(f[j], p[i])>EPS) {
					dfs(i, j);
					break;
				}

		int tmp = cnt;
		cnt = 0;
		for (i = 0; i < tmp; ++i)
			if (f[i].ok) f[cnt++] = f[i];
	}

	//表面积
	double area() {
		double res = 0;
		for (int i = 0; i < cnt; ++i)
			res += ::area(p[f[i].a], p[f[i].b], p[f[i].c]);
		return res/2;
	}

	//体积
	double volume() {
		sp o = sp(0, 0, 0);
		double res = 0;
		for (int i = 0; i < cnt; ++i)
			res += ::volume(o, p[f[i].a], p[f[i].b], p[f[i].c]);
		return fabs(res/6);
	}

	//三角形u,v共面
	bool same(int u, int v) {
		sp a = p[f[u].a], b = p[f[u].b], c = p[f[u].c];
		return ::coplane(a, b, c, p[f[v].a]) &&
			::coplane(a, b, c, p[f[v].b]) &&
			::coplane(a, b, c, p[f[v].c]);
	}
	//凸包面数
	int facecnt() {
		int res = 0;
		for (int i = 0; i < cnt; ++i) {
			bool t = 1;
			for (int j = 0; j < i; ++j) {
				if (same(i, j)) {
					t = 0;
					break;
				}
			}
			res += t;
		}
		return res;
	}
}ch3d;
