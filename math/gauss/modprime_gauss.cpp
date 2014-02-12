//模质数高斯消元
//求解模线性方程组AX=B(modulo mod)
int gauss(int N, int M, int a[][MAX], int mod) {
	int i, j, r, c, pvt, maxp;
	for (r=0, c=0; r<N && c<M; ++r, ++c) {
		for (i = r; i < N; ++i)
			if (a[i][c]) maxp = a[pvt=i][c];
		if (maxp == 0) {
			--r;
			continue;
		}
		if (pvt != r)
			for (j = r; j <= M; ++j) swap(a[r][j], a[pvt][j]);
		for (j = c+1; j <= M; ++j) {
			a[r][j] = (a[r][j]*pow(maxp, mod-2))%mod;
			for (i = r+1; i < N; ++i) {
				a[i][j] = (a[i][j]-a[i][c]*a[r][j])%mod;
				if (a[i][j] < 0) a[i][j] += mod;
			}
		}
	}
	for (i = r; i < N; ++i)
		if (a[i][M]) return -1;
	if (r < M) return M-r;
	for (i = M-1; i >= 0; --i) {
		for (j = i+1; j < M; ++j)
			a[i][M] = (a[i][M]-a[j][M]*a[i][j])%mod;
		if (a[i][M] < 0) a[i][M] += mod;
	}
	return 0;
}
