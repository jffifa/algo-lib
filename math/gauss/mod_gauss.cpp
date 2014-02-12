//模(可以非质数)高斯消元辗转相除法消成上阶梯阵
void gauss(int N, int M, int a[][MAXN], int mod) {
	int i, j, r, c;
	//将矩阵化为行阶梯阵
	//r为当前处理行，c为当前处理列
	//终止时，形成行阶梯阵，有r<=c
	for (r=0, c=0; r<N && c<M; ++r, ++c) {
		for (i = r+1; i < N; ++i)
			//a[r][c]和a[i][c]辗转相除
			while (a[i][c]) {
				int t = a[r][c]/a[i][c];
				for (j = c; j < M; ++j) {
					a[r][j] = (a[r][j]-t*a[i][j]%mod)%mod;
					swap(a[r][j], a[i][j]);
				}
			}
		if (!a[r][c]) r--;
	}
}

//模高斯消元(模可以非质数)求行列式
int det(int N, int a[][MAXN], int mod) {
	int ans = 1;
	int i, j, k;
	for (i = 0; i < N; ++i) {
		for (j = i+1; j < N; ++j)
			//a[r][c]和a[i][c]辗转相除
			while (a[i][j]) {
				int t = a[i][i]/a[i][j];
				for (k = i; k < N; ++k) {
					a[i][k] = (a[i][k]-t*a[j][k]%mod)%mod;
					swap(a[i][k], a[j][k]);
				}
				ans = -ans;
			}
		if (!a[i][i]) return 0;
		ans = ans*a[i][i]%mod;
	}
	return ans;
}
