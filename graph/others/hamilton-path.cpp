const int MAX = 500;
int N, M;
bool g[MAX][MAX];
int nxt[MAX];
bool vis[MAX];
int path[MAX];

//求hamilton路
//必须保证路存在，比如Bondy-Chvatal定理：若任意u,v有deg(u)+deg(v)>=N，则hamilton路一定存在
//特例为dirac定理
//n为点数，g为邻接矩阵，path为输出路径
void dirac(int n, bool g[][MAX], int path[]) {
	memset(nxt, 255, sizeof(nxt));
	memset(vis, 0, sizeof(vis));

	int i, j, k;
	int s = 0, t;
	for(t = 1; !g[s][t]; t++);
	
	nxt[s] = t;
	nxt[t] = s;
	vis[s] = vis[t] = 1;
	
	for(int num = 2; num != n; ) {
		while(1) {
			bool ok = 1;
			for(i = 0; i < n; i++) {
				if (vis[i])	continue;
				if (g[i][s]) {
					vis[i] = 1; nxt[i] = s; s = i; ok = 0; num++;
				} else if(g[t][i]) {
					vis[i] = 1; nxt[t] = i; t = i; ok = 0; num++;
				}
			}
			if (ok) break;
		}
		nxt[t] = s;	//fix the circut!
		if (!g[s][t]) {
			int tgt = -1;
			int prev = s, next;
			for(i = nxt[s]; nxt[i] != t; i = next) {
				//i and nxt[i]
				next = nxt[i];
				nxt[i] = prev;
				prev = i;
				if(g[s][next] && g[t][i]) {
					tgt = i;
					break;
				}
			}
			//assert(tgt!=-1);
			nxt[s] = next;
			nxt[t] = tgt;
			s = tgt;
		}
		//now s->t is a circut
		if (num == n) break;
		bool flag = 1;
		for (i = 0; i < n && flag; i ++) {
			if (vis[i]) continue;
			j = s;
			do {
				if(g[i][j]) {
					t = j;
					s = nxt[j];
					flag = 0;
					break;
				}
			} while ((j=nxt[j])!=s);
		}
	}
	//保存结果:
	int len = 0;
	i = s;
	do {
		path[len++] = i;
	} while((i=nxt[i])!=s);
	//assert(len==n);
}
