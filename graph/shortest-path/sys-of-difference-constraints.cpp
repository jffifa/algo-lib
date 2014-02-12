/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Shortest Path - Single-Source Shortest Path
	Title: System of Difference Constraints
	Version: 0.314
	Date: 2011/2/22
	Remark: ID of Solution Vector(or vertex) from 1
	Tested Problems: POJ2983
	Tag: System of Difference Constraints, SPFA
	Special Thanks: Amber
*/
/*
	Input:
		Number of variables N, Number of diff M, Diff vector E
	Output:
		If the system of diff constraints has solution
*/

#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 100;

//X[v]-X[u]<=dis
struct SEdge
{
	int u, v, dis;
	SEdge() {}
	SEdge(int U, int V, int D): u(U), v(V), dis(D) {}
};

//E(u,v,d):X[v]-X[u]<=d
//Bellman-Ford
bool DiffCon(int N, int M, SEdge E[])
{
	//Bellman-Ford specialized for the difference constraints, the source is vertex 0
	int Dis[MaxN+1] = {0};
	int u, v, d;
	for (int i = 1; i < N; ++i)
		for (int j = 0; j < M; ++j)
			Dis[E[j].v] = min(Dis[E[j].v], Dis[E[j].u]+E[j].dis);
	for (int i = 0; i < M; ++i)
		if (Dis[E[i].v] > Dis[E[i].u]+E[i].dis) return 0;
	return 1;
}

//E(u,v,d):X[v]-X[u]<=d
//SPFA WITHOUT SLF
bool DiffCon(int N, int M, SEdge E[])
{
	//SPFA specialized for the difference constraints, the source is vertex 0
	vector<SAdj> Adj[MaxN+1];
	for (int i = 0; i < M; ++i)
		Adj[E[i].u].push_back(SAdj(E[i].v, E[i].dis));
	int Dis[MaxN+1], Time[MaxN+1];
	char InQ[MaxN+1];
	deque<int> Q;
	memset(Dis, 0, sizeof(Dis));
	//In fact, here the number of vertex is N+1
	memset(Time, 0, sizeof(Time));
	memset(InQ, 1, sizeof(InQ));
	for (int u = 1; u <= N; ++u)
		Q.push_back(u);
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
				if (!InQ[v])
				{
					//NO SLF!!!
					Q.push_back(v);
					InQ[v] = 1;
					++Time[v];
					if (Time[v] > N) return 0;
				}
			}
		}
	}
	return 1;
}
