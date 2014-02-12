#include <algorithm>
using namespace std;

const int MAX = 0x3fffffff;
const int MAXE = 10000;
const int MAXV = 1000;

struct se {
	int v, c;
	int n;
	se() {}
	se(int p, int q, int r): v(p), c(q), n(r) {}
}e[MAXE];
int fst[MAXV];

int V, M, E, s, t;
int h[MAXV], gap[MAXV];

void init() {
	memset(fst, -1, sizeof(fst));
	memset(gap, 0, sizeof(gap));
	memset(h, 0, sizeof(h));
	E = 0;
}

void ae(int u, int v, int c) {
	e[E] = se(v, c, fst[u]);
	fst[u] = E++;
	e[E] = se(u, 0, fst[v]);
	fst[v] = E++;
}

int sap(int u, int f) {
	if (u==t) return f;
	int i, minh=V, rf=f, cf;
	for (i = fst[u]; i != -1; i = e[i].n)
		if (e[i].c && h[e[i].v]+1==h[u])
		{
			cf = sap(e[i].v, min(e[i].c, rf));
			e[i].c -= cf; e[i^1].c += cf;
			rf -= cf;
			if (h[s]==V || !rf) return f-rf;
		}
	for (i = fst[u]; i != -1; i = e[i].n)
		if (e[i].c) minh = min(minh, h[e[i].v]);
	if (!--gap[h[u]]) h[s] = V;
	else ++gap[h[u]=minh+1];
	return f-rf;
}

int maxflow() {
	int res = 0;
	gap[0] = V;
	while (h[s] < V) res += sap(s, MAX);
	return res;
}
