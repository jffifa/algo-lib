/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Graph - Base
	Title: Tarjan for BiConnected Components
	Version: 0.103
	Date: 2011-9-4
	Remark: Tarjan算法求双联通分量
	Tested Problems: HDU4005
	Tag: Graph, Tarjan, BiConnected Components, SCC
	Special Thanks: Amber, eucho@PuellaMagi, mabodx@PuellaMagi
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//最大点数
const int MAXN = 10001;
//最大边数
const int MAXM = 100001;

//输入图（边表），N个点，M条边。点编号从1到N。
int N, M, fst[MAXN], nxt[MAXM], e[MAXM];

inline void addedge(int u, int v)
{
	nxt[M] = fst[u];
	fst[u] = M;
	e[M++] = v;
}

void init()
{
	M = 0;
	memset(fst, 255, sizeof(fst));
}

//Tarjan算法
//输入为上面的图。
//dfn为dfs时间戳，low为返祖标记。
//blng为双联通分量标记。u所属双联通分量编号为blng[u]。分量编号从1开始。
int cnt, bcccnt;
int dfn[MAXN], low[MAXN], blng[MAXN];
//标记边是否被访问过。
bool vis[MAXM];
//标记桥边的编号，从0开始。
int brdgcnt, brdgcnt[MAXM];

void dfs(int u)
{
	int v;
	dfn[u] = low[u] = cnt++;
	for (int i = fst[u]; i != -1; i = nxt[i])
	{
		if (vis[i]) continue;
		vis[i] = vis[i^1] = 1;
		v = e[i];
		if (dfn[v] != -1)
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else
			low[u] = min(low[u], dfn[v]);
	}
}

void sch(int u)
{
	int i, v;
	for (i = fst[u]; i != -1; i = nxt[i])
	{
		v = e[i];
		if (!blng[v])
		{
			if (low[v] > dfn[u])
			{
				blng[v] = ++bcccnt;
				brdg[brdgcnt++] = i;
			}
			else
				blng[v] = blng[u];
			sch(v);
		}
	}
}

void tarjan()
{
	int u;
	brdgcnt = bcccnt = idx = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(vis, 0, sizeof(vis));
	for (u = 1; u <= N; ++u)
		if (!dfn[u]) dfs(u);
	memset(blng, 0, sizeof(blng));
	for (u = 1; u <= N; ++u)
		if (!blng[u])
		{
			blng[u] = ++bcccnt;
			sch(u);
		}
}

//求割点
void dfs(int u, int p)
{
	int v;
	dfn[u] = low[u] = cnt++;
	for (int i = 0; i < g[u].size(); ++i)
	{
		v = g[u][i];
		if (v==p) continue;
		if (!dfn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
			if (p!=-1 && dfn[u]<=low[v]) cut[u] = 1;
		}
		else
			low[u] = min(low[u], dfn[v]);
	}
}

