#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 32;

//高斯消元
//异或（模2）线性方程组AX=B："+"等价于"^"，"*"等价于"&"。
//输入：方程个数（A行数）N，变量个数（A列数）M，增广（只有0和1）矩阵a=[A|B]。
//输出：返回值：-1为无解，大于0为无穷解并返回自由变量个数。0为唯一解，解返回在a[i][M]中。
int gauss(int N, int M, char a[][MAXN])
{
	int i, j, r, c, pvt;
	//将增广矩阵化为行阶梯阵
	//r为当前处理行，c为当前处理列
	//终止时，形成行阶梯阵，有r<=c
	for (r=0, c=0; r<N && c<M; ++r, ++c)
	{
		//选主元，pvt标记绝对值最大的行
		for (pvt = r; pvt < N; ++pvt)
			if (a[pvt][c]) break;
		//若当前列当前行以下全部是0，则当前行不变，处理下一列
		if (pvt == N)
		{
			r--;
			continue;
		}
		//与r行交换
		if (pvt != r)
			for (j = r; j <= M; ++j) swap(a[r][j], a[pvt][j]);
		//开始消元
		for (i = r+1; i < N; ++i)
		if (a[i][c])
			for (j = c; j <= M; ++j)
				a[i][j] ^= a[r][j];
	}
	//无解的情况：增广阵存在[0,0,0,...,x(x!=0)]的行
	for (i = r; i < N; ++i)
		if (a[i][M]) return -1;
	//无穷解的情况：在M*(M+1)的增广阵中存在[0,0,0,...,0]这样的行
	//出现的行数即自由变量的个数
	if (r < M)
	{
		/*
		
		*/
		return M - r;
	}
	//唯一解的情况：在M*(M+1)的增广阵中形成严格上三角阵
	for (i = M-1; i >= 0; --i)
		for (j = i+1; j < M; ++j)
			a[i][M] ^= a[j][M]&a[i][j];
	return 0;
}
