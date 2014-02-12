/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Matching - Bipartite Graph
	Title: Hungarian
	Version: 0.314
	Date: 2011-7-10
	Remark: Take adjacency matrix as input format. Start with vertex ID=1.
	Tested Problems: N/A
	Tag: Match, Bipartite Graph Matching
	Special Thanks: Amber
*/
/*
	Input:
		Two sets of vertexes S(with size N) and T(with size M)
	Output:
		The maximum match num
*/

#include <cstdio>
#include <cstring>
using namespace std;

//X to Y: 1 to 1 match
template <int MaxN>
struct SMatch
{
	//Size of vertex sets X and Y
	int N, M;
	//AdjList of set X
	vector<int> Adj[MaxN];
	//vertex i (in set Y) matches vertex MatchY[i] in set X
	int MatchY[MaxN];
	char VisY[MaxN];

	inline void Init(int _N, int _M)
	{
		memset(MatchY, 0, sizeof(MatchY));
		N = _N; M = _M;
		for (int u = 1; u <= N; ++u)
			adj[u].clear();
	}

	inline void AddEdge(int u, int v)
	{Adj[u].push_back(v);}

	bool DFS(int u)
	{
		int v;
		for (int i = 0; i < Adj[u].size(); ++i)
		{
			v = Adj[u][i];
			if (VisY[v]) continue;
			VisY[v] = 1;
			if (!MatchY[v] || DFS(MatchY[v]))
			{
				MatchY[v] = u;
				return 1;
			}
		}
		return 0;
	}

	int Hungarian()
	{
		int MatchNum = 0;
		for (int u = 1; u <= N; ++u)
		{
			memset(VisY, 0, sizeof(VisY));
			if (DFS(u)) ++MatchNum;
		}
		return MatchNum;
	}
};

//X to Y: multi to 1 match
template <int MaxN>
struct SMatch
{
	//Size of vertex sets X and Y
	int N, M;
	//AdjList of set X
	vector<int> Adj;
	//vertex i (in set Y) matches MatchY[i][0] vertexes (in set X): MatchY[i][j], 1 <= j <= MatchY[i][0]
	int MatchY[MaxN][MaxN];
	char VisY[MaxN];

	void Init(int _N, int _M)
	{
		memset(MatchY, 0, sizeof(MatchY));
		N = _N; M = _M;
		for (int u = 1; u <= N; ++u)
			adj[u].clear();
	}

	inline void AddEdge(int u, int v)
	{Adj[u].push_back(v);}

	bool DFS(int u)
	{
		int v;
		for (int i = 0; i < Adj[u].size(); ++i)
		{
			v = Adj[u][i];
			if (Vis[v]) continue;
			if (/*here you might set some restrictions to the MatchNum of vertex v in set Y*/)
			{
				MatchY[v][++MatchY[v][0]] = u;
				return 1;
			}
			else
			{
				for (int j = 1; j <= MatchY[v][0]; ++j)
					if (DFS(MatchY[v][j]))
					{
						MatchY[v][j] = u;
						return 1;
					}
			}
		}
		return 0;
	}

	int Hungarian()
	{
		int MatchNum = 0;
		for (int u = 1; u <= N; ++u)
		{
			memset(VisY, 0, sizeof(VisY));
			if (DFS(u)) ++MatchNum;
		}
		return MatchNum;
	}
};
