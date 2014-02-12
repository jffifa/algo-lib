#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

struct sp {
	double x, y;
	sp () {}
	sp (double xx, double yy): x(xx), y(yy) {}
};

inline sp operator- (const sp &u, const sp &v)
{return sp(u.x-v.x, u.y-v.y);}

double nrmsqr(const sp &v)
{return v.x*v.x + v.y*v.y;}

double dis(const sp &u, const sp &v) {
	double dx = u.x-v.x;
	double dy = u.y-v.y;
	return sqrt(dx*dx+dy*dy);
}

double fermatpoint(int N, sp p[]) {
	sp u, v;
	double step = 0;
	u.x = u.y = 0;
	for (int i = 0; i < N; ++i)
	{
		u.x += p[i].x;
		u.y += p[i].y;
	}
	step = u.x+u.y;
	u.x /= N;
	u.y /= N;
	double now, best = 0;
	for (int i = 0; i < N; ++i)
		best += dis(u, p[i]);
	while (step > EPS)
	{
		for (int i = -2; i <= 2; ++i)
			for (int j = -2; j <= 2; ++j)
			{
				v.x = u.x+step*i;
				v.y = u.y+step*j;
				now = 0;
				for (int k = 0; k < N; ++k)
					now += dis(v, p[i]);
				if (now < best)
				{
					best = now;
					u = v;
				}
			}
		//影响ac,wa,tle...
		step /= 1.1;
	}
	return best;
}

