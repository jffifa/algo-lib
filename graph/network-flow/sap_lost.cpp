#include <algorithm>
using namespace std;
template<int maxp,int maxl>
struct SSap
{
	//edgelist
	//initially, for each edge(u, v), flow = c(u, v)
	//in the process, for each edge(u, v) flow = cf(u, v) (the residual capcity)
	struct edge
	{
		int v,flow,next;
	}e[maxl];

	//tot: number of edges
	//ST[u]: last index of vertex u in the edgelist
	//n: number of vertexes, m: number of edges, s: source, t: terminal
	int tot,ST[maxp],n,m,s,t;
	//h: the distance label (height function), gap: gap[h] means the number of vertexes of dislabel h
	int h[maxp],gap[maxp];
	
	inline void init(int _n)
	{
		n=_n;
		memset(ST,-1,sizeof(int)*n);
		memset(gap,0,sizeof(int)*n);
		memset(h,0,sizeof(int)*n);
		tot=0;
	}
	
	void addedge(int u,int v,int flow)
	{
		e[tot].v=v;
		e[tot].flow=flow;
		e[tot].next=ST[u];
		ST[u]=tot++;
	}
	
	void build(int u,int v,int flow)
	{
		addedge(u,v,flow);
		addedge(v,u,0);
	}
	
	inline int dfs(int pos, int cost)
	{
		if (pos==t) return cost;
		//what does lv mean?
		int i, mi=n-1, lv=cost, d;
		for(i=ST[pos]; i!=-1; i=e[i].next)
		{
			int v=e[i].v, fl=e[i].flow;
			if (fl > 0)
			{
				if(h[v]+1 == h[pos])
				{
					d=dfs(v,min(fl,lv));
					e[i].flow-=d;
					e[i^1].flow+=d;
					lv-=d;
					if(h[s]>=n)return cost-lv;
					if(!lv)break;
				}
				mi=min(mi,h[v]);
			}
		}
		//relabel
		if (lv==cost)
		{
			--gap[h[pos]];
			//gap[h[pos]]=0 means no augment path, so set h[s]=n and the algo will be halt at once
			if(!gap[h[pos]])h[s]=n;
			h[pos]=mi+1;
			++gap[h[pos]];
		}
		return cost-lv;
	}
	
	int sap(int st,int ed)
	{
		s=st;
		t=ed;
		gap[s]=n;
		int ret=0;
		while (h[s]<n) ret+=dfs(s,INT_MAX);
		return ret;
	}
};
SSap<30500,1000000>Sap;
