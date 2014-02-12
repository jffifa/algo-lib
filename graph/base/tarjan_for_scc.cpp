/*
	Project: AkemiHomura's Standard Code Library [AHSCL]
	Author: [BUPT]AkemiHomura@PuellaMagi
	Category: Graph - Base
	Title: Tarjan for Strongly Connected Components
	Version: 0.103
	Date: 2011-9-4
	Remark: Tarjan算法求强联通分量
	Tested Problems: N/A
	Tag: Graph, Tarjan, Strongly Connected Components, SCC
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
//dfn为dfs时间戳，low为返祖标记，stk为栈，instk标记是否在栈内。
//blng为强联通分量标记。u所属强联通分量编号为blng[u]。分量编号从1开始。
int idx, top, scccnt;
int dfn[MAXN], low[MAXN], stk[MAXN], blng[MAXN];
bool instk[MAXN];

void dfs(int u)
{
	int v;
	dfn[u] = low[u] = ++idx;
	instk[u] = 1;
	stk[top++] = u;
	for (int i = fst[u]; i != -1; i = nxt[i])
	{
		v = e[i];
		if (!dfn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (instk[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		++scccnt;
		do
		{
			v = stk[--top];
			instk[v] = 0;
			blng[v] = scccnt;
		}
		while (v != u);
	}
}

void tarjan()
{
	top = scccnt = idx = 0;
	memset(dfn, 0, sizeof(dfn));
	for (int u = 1; u <= N; ++u)
		if (!dfn[u]) dfs(u); 
}
