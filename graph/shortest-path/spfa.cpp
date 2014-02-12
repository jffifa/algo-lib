/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Shortest Path - Single-Source Shortest Path
	Title: Shortest Path Faster Algorithm
	Version: 0.314
	Date: 2011/2/23
	Remark: with Small Label First method, ID of vertex from 1
	Tested Problems: N/A
	Tag: SPFA, SLF
	Special Thanks: Amber
*/
/*
	Input:
		
	Output:
		
*/

#include <vector>
#include <deque>
using namespace std;

const int MaxV = 100;
const int INF = 0x3fffffff;

struct SAdj
{
	int v, dis;
	SAdj() {}
	SAdj(int V, int D): v(V), dis(D) {}
};

bool SPFA(int V, vector<SAdj> Adj[], int Src, int Dis[])
{
	int Prev[MaxV+1], Time[MaxV+1];
	char InQ[MaxV+1];
	deque<int> Q;
	for (int v = 1; v <= V; ++v)
	{
		Dis[v] = INF;
		Time[v] = InQ[v] = Prev[v] = 0;
	}
	Dis[Src] = 0;
	Time[Src] = InQ[Src] = 1;
	Q.push_back(Src);
	int u, v, d;
	while (!Q.empty())
	{
		u = Q.front();
		Q.pop_front();
		InQ[u] = 0;
		for (int i = 0; i < Adj[u].size(); ++i)
		{
			v = Adj[u][i].v; d = Adj[u][i].dis;
			if (Dis[v] > Dis[u]+d)
			{
				Dis[v] = Dis[u]+d;
				Prev[v] = u;
				if (!InQ[v])
				{
					//SLF优化，仅当确定有解（无负环）时可用
					if (!Q.empty() && Dis[v]<Dis[Q.front()]) Q.push_front(v);
					else Q.push_back(v);
					InQ[v] = 1;
					++Time[v];
					if (Time[v] > V) return 0;
				}
			}
		}
	}
	return 1;
}
