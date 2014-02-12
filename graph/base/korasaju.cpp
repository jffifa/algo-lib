/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Base
	Title: Korasaju
	Version: 0.314
	Date: 2011/2/21
	Remark: ID of Vertex from 1
	Tested Problems: POJ1236
	Tag: Korasaju, strongly connected components, SCC
	Special Thanks: Amber
*/
/*
	Input:
		Adjacent list and reverse adjacent list of the graph
	Output:
		If u, v in the same SCC, then SCC[u] == SCC[v] == the identifier of the SCC
*/

#include <vector>
#include <cstring>
using namespace std;

const int MaxN = 101;

char Vis[MaxN];
int Cnt, Ord[MaxN], SCC[MaxN], SCCCnt;
vector<int> Adj[MaxN], RAdj[MaxN];

void DFS(int u)
{
	Vis[u] = 1;
	for (int i = 0; i < Adj[u].size(); ++i)
		if (!Vis[Adj[u][i]]) DFS(Adj[u][i]);
	Ord[++Cnt] = u;
}

void RDFS(int u)
{
	Vis[u] = 1;
	SCC[u] = SCCCnt;
	for (int i = 0; i < RAdj[u].size(); ++i)
		if (!Vis[RAdj[u][i]]) RDFS(RAdj[u][i]);
}

void Korasaju()
{
	Cnt = 0;
	memset(Vis, 0, sizeof(Vis));
	for (int u = 1; u <= N; ++u)
		if (!Vis[u]) DFS(u);
	SCCCnt = 0;
	memset(Vis, 0, sizeof(Vis));
	for (int i = N; i >= 1; --i)
		if (!Vis[Ord[i]]) {++SCCCnt; RDFS(Ord[i]);}
}
