/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Shortest Path - Single-Source Shortest Path
	Title: Bellman-Ford
	Version: 0.314
	Date: 2011/2/22
	Remark: ID of vertex from 1
	Tested Problems: N/A
	Tag: Bellman-Ford, single-source shortest path
	Special Thanks: Amber
*/
/*
	Input:
		
	Output:
		
*/

#include <vector>
using namespace std;

const int MaxV = 100;
const int INF = 0x3fffffff;

struct SAdj
{
	int v, dis;
	SAdj() {}
	SAdj(int V, int D): v(V), dis(D) {}
};

bool BellmanFord(int V, vector<SAdj> Adj[], int Src, int Dis[])
{
	int Prev[MaxV+1];
	for (int v = 1; v <= V; ++v)
	{
		Dis[v] = INF;
		Prev[v] = 0;
	}
	Dis[Src] = 0;
	int u, v, d;
	for (int i = 1; i < V; ++i)
		for (u = 1; u <= V; ++u)
			for (int j = 0; j < Adj[u].size(); ++j)
			{
				v = Adj[u][j].v; d = Adj[u][j].dis;
				//RELAX(u, v, d)
				if (Dis[v] > Dis[u]+d)
				{
					Prev[v] = u;
					Dis[v] = Dis[u]+d;
				}
			}
	for (int u = 1; u <= V; ++u)
		for (int i = 0; i < Adj[u].size(); ++i)
		{
			v = Adj[u][i].v; d = Adj[u][i].dis;
			if (Dis[v] > Dis[u]+d)
				return 0;
		}
	return 1;
}
