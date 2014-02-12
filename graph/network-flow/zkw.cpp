//可用于负权（无负圈）图
template<int maxp,int maxl>//start with ID zero
struct CostFlow{
   struct EDGE{
      int ID,nxt,cost,flow;
   }e[maxl];
   int ST[maxp],dis[maxp],vis[maxp],st,ed;
   int pay,maxflow,cas,nflow,el;
   void addedge(int s,int t,int u,int c){
      e[el].cost=c;
      e[el].flow=u;
      e[el].ID=t;
      e[el].nxt=ST[s];
      ST[s]=el++;
   }
   void build(int s,int t,int u,int c){
      addedge(s,t,u,c);
      addedge(t,s,0,-c);
   }
   void init(int n){
      nflow=n;
      el=maxflow=pay=0;
      cas++;
      memset(ST,-1,sizeof(int)*(n+1));
      memset(dis,0,sizeof(int)*(n+1));
   }
   int aug(int no,int x){
      int T,d;
      if(no==ed){pay+=x*dis[st];maxflow+=x;return x;}
      vis[no]=cas;
      for(T=ST[no];T!=-1;T=e[T].nxt)
         if(e[T].flow>0&&vis[e[T].ID]<cas&&dis[e[T].ID]+e[T].cost==dis[no]){
            d=aug(e[T].ID,min(x,e[T].flow));
            if(d>0){e[T].flow-=d;e[T^1].flow+=d;return d;}
         }
      return 0;
   }
   bool modlabel(){
      int d=INT_MAX,i,j;
      for(i=0;i<nflow;i++)if(vis[i]==cas)
         for(j=ST[i];j!=-1;j=e[j].nxt)
            if(e[j].flow>0&&vis[e[j].ID]<cas&&(e[j].cost-dis[i]+dis[e[j].ID]<d))
               d=e[j].cost-dis[i]+dis[e[j].ID];
      if(d==INT_MAX)return true;
      for(i=0;i<nflow;i++)if(vis[i]==cas){
         vis[i]=cas-1;
         dis[i]+=d;
      }
      return false;
   }
   void spfa(){
      queue<int>Q;
      cas++;
      int i,T;
      for(i=0;i<nflow;i++)dis[i]=INT_MAX;
      dis[st]=0;vis[st]=cas;
      for(Q.push(st);Q.empty()==false;){
         i=Q.front();Q.pop();
         vis[i]=cas-1;
         for(T=ST[i];T!=-1;T=e[T].nxt)if(e[T].flow>0&&dis[e[T].ID]>dis[i]+e[T].cost){
            dis[e[T].ID]=dis[i]+e[T].cost;
            if(vis[e[T].ID]<cas){vis[e[T].ID]=cas;Q.push(e[T].ID);}
         }
      }
      for(i=0;i<nflow;i++)dis[i]=dis[ed]-dis[i];
      cas++;
   }
   void work(int s,int e,bool neg){
      st=s;
      ed=e;
      if(neg)spfa();
      while(true){
         while(aug(st,INT_MAX)>0)cas++;
         if(modlabel())break;
      }
   }
};
CostFlow<4500,500000>CF;
