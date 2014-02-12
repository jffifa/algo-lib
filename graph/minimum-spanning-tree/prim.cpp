/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Minimum Spanning Tree
	Title: Prim
	Version: 0.314
	Date: 2011/2/12
	Remark: ID of vertex from 1
	Tested Problems: N/A
	Tag: 
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

const int MaxV = 1001;
const int MaxE = 250000;
const int INF = 0x3fffffff;

//The Minimum Heap
template <class T>
//The operator < must be overloaded for class T
struct SHeap
{
//Data
	//The source array. Index start from 1.
	T *Arr;
	//HeapSize
	int Size;
	//The array "Map" contains the indexes of the source array, not the keys. Map[i]->Arr[Map[i]]
	int Map[MaxV+1];
	//The inverse map from the heap to the source array. Arr[i]->Heap[InvMap[i]]
	int InvMap[MaxV+1];

//Function
	inline void Swap(int a, int b)
	{int Tmp=Map[a]; Map[a]=Map[b]; Map[b]=Tmp; InvMap[Map[a]]=a; InvMap[Map[b]]=b;}

	SHeap() {}

	SHeap(T *a, int N)
	{
		Arr = a;
		Size = N;
		for (int i = 1; i <= Size; ++i)
		{
			Map[i] = i;
			InvMap[i] = i;
		}
		for (int i = Size>>1; i >= 1; --i)
			Sink(i);
	}

	void Sink(int i)
	{
		int L, R, Min;
		while (L = i<<1, R = (i<<1)+1, L <= Size)
		{
			Min = i;
			if (L<=Size && Arr[Map[L]]<Arr[Map[Min]])
				Min = L;
			if (R<=Size && Arr[Map[R]]<Arr[Map[Min]])
				Min = R;
			if (Min == i) break;
			Swap(i, Min);
			i = Min;
		}
	}

	void Rise(int i)
	{
		int P;
		while (i > 1)
		{
			P = i >> 1;
			if (Arr[Map[P]] < Arr[Map[i]]) break;
			Swap(i, P);
			i = P;
		}
	}

	//Return the index of the source array
	int Delete(int i)
	{
		int Ans = Map[i];
		Swap(i, Size--);
		Sink(i);
		//if i is a leaf node
		Rise(i);
		return Ans;
	}
};

struct SAdj
{
	int v, dis;
	SAdj() {}
	SAdj(int V, int D): v(V), dis(D) {}
};

//ID of V start from 1
//return the minimum weight of the MST or -1 if cannot form a connected graph
int Prim(int VNum, vector<SAdj> Adj[])
{
	int Ans = 0, SafeENum = 0, u, v, d;
	int Dis[MaxV+1], Prev[MaxV+1];
	for (int v = 1; v <= VNum; ++v)
	{
		Dis[v] = INF;
		Prev[v] = 0;
	}
	Dis[1] = 0;
	SHeap<int> Heap(Dis, VNum);
	while (Heap.Size)
	{
		u = Heap.Delete(1);
		if (Dis[u] == INF) return -1;
		Ans += Dis[u];
		for (int i = 0; i < Adj[u].size(); ++i)
		{
			v = Adj[u][i].v; d = Adj[u][i].dis;
			if (Heap.InvMap[v]<=Heap.Size && d<Dis[v])
			{
				Prev[v] = u;
				Dis[v] = d;
				Heap.Rise(Heap.InvMap[v]);
			}
		}
	}
	return Ans;
}
