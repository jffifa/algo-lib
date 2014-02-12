/*
	Project: Biribiri Standard Code Library [BSCL]
	Author: [BUPT]Biribiri
	Category: Graph - Shortest Path - Single-Source Shortest Path
	Title: Dijkstra
	Version: 0.314
	Date: 2010-9-28
	Remark: Vertex ID from 1.
	Tested Problems: N/A
	Tag: Dijkstra, single-source shortest path
	Special Thanks: Amber
*/
/*
	Input:
		Adjacent List
	Output:
		Dis[v] and Prev[v]
*/

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MaxV = 1000;
const int MaxE = 100000;
const int Inf = 0x3fffffff;

//AdjList
struct SAdj
{
	int v, d;
	SAdj() {}
	SAdj(int V, int D): v(V), d(D) {}
};

inline void AddEdge(vector<SAdj> Edge[], int u, int v, int d)
{Edge[u].push_back(SAdj(v, d));}

//The Minimum Heap
template <class T>
//The operator < must be overloaded for class T
struct SHeap
{
//Data
	//The source array.
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

	//x is the index of the source array
	void Insert(int x)
	{
		Map[++Size] = x;
		Rise(Size);
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

void Dijkstra(int V, int E, vector<SAdj> Edge[], int Src, int Dis[])
{
	int Prev[MaxV+1];
	for (int v = 1; v <= V; ++v)
	{
		Dis[v] = Inf;
		Prev[v] = 0;
	}
	Dis[Src] = 0;
	SHeap<int> Heap(Dis, V);
	int u, v, d;
	while (Heap.Size)
	{
		u = Heap.Delete(1);
		for (int e = 0; e < Edge[u].size(); ++e)
		{
			v = Edge[u][e].v; d = Edge[u][e].d;
			//RELAX(u, v, d)
			if (Dis[v] > Dis[u]+d)
			{
				Prev[v] = u;
				Dis[v] = Dis[u]+d;
				Heap.Rise(Heap.InvMap[v]);
			}
		}
	}
}
