/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Minimum Spanning Tree
	Title: Kruskal
	Version: 0.314
	Date: 2011/2/11
	Remark: ID of vertice from 1
	Tested Problems: N/A
	Tag: MST, Kruskal
	Special Thanks: Amber
*/
/*
	Input:
		Number of vertexes, Adjacency List of edges.
	Output:
		Minimum cost.
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxV = 1000;
const int MaxE = 2500000;

struct SDisjointSet
{
	int P[MaxV+1], Rank[MaxV+1];
	
	SDisjointSet()
	{
		for (int i = 1; i <= MaxV; ++i)
		{
			P[i] = i;
			Rank[i] = 0;
		}
	}

	int FindSet(int v)
	{
		if (P[v] != v)
			P[v] = FindSet(P[v]);
		return P[v];
	}

	//return if u, v in the same set
	bool Union(int u, int v)
	{
		int Ru = FindSet(u);
		int Rv = FindSet(v);
		if (Ru != Rv)
		{
			if (Rank[Ru] < Rank[Rv])
				P[Ru] = Rv;
			else
			{
				P[Rv] = Ru;
				if (Rank[Ru] == Rank[Rv]) ++Rank[Ru];
			}
			return 0;
		}
		else
			return 1;
	}
};

struct SAdj
{
	int v, dis;
	SAdj() {}
	SAdj(int V, int D): v(V), dis(D) {}
};

struct SEdge
{
	int u, v, dis;
	SEdge() {}
	SEdge(int U, int V, int D): u(U), v(V), dis(D) {}
	friend bool operator < (const SEdge &E1, const SEdge &E2)
	{return E1.dis < E2.dis;}
};

//ID of V start from 1
//return the minimum weight of the MST or -1 if cannot form a connected graph
int Kruskal(int VNum, vector<SAdj> Adj[])
{
	int Ans = 0, SafeENum = 0;
	vector<SEdge> E;
	//vector<SEdge> SafeE;
	SDisjointSet V;

	for (int v = 1; v <= VNum; ++v)
		for (int i = 0; i < Adj[v].size(); ++i)
			E.push_back(SEdge(v, Adj[v][i].v, Adj[v][i].dis));
	sort(E.begin(), E.end());

	for (int i = 0; i < E.size(); ++i)
	{
		if (V.FindSet(E[i].u) != V.FindSet(E[i].v))
		{
			V.Union(E[i].u, E[i].v);
			Ans += E[i].dis;
			//SafeE.push_back(E[i]);
			++SafeENum;
		}
		if (SafeENum == VNum-1) break;
	}
	if (SafeENum == VNum-1) return Ans;
	else return -1;
}
