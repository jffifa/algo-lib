#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 111;
const double EPS = 1e-8;

inline int sgn(double d) {
	if (fabs(d)<EPS) return 0;
	return d>0?1:-1;
}

//高斯消元
//浮点线性方程组AX=B
//输入：方程个数（A行数）N，变量个数（A列数）M，增广矩阵a=[A|B]。
//输出：返回值：-1为无解，大于0为无穷解并返回自由变量个数。0为唯一解，解返回在a[i][M]中。
//注意：做某些概率题(eg HDU 4418)时，如果从起点走不到某个状态，应强制将解赋为INF(a[i][i]=1, a[i][j]=0, a[i][M]=INF)。否则可能因为这些与答案无关的状态使得解向量不存在。
int gauss(int N, int M, double a[][MAXN]) {
	int i, j, r, c, pvt;
	double maxp;
	//将增广矩阵化为行阶梯阵
	//r为当前处理行，c为当前处理列
	//终止时，形成行阶梯阵，有r<=c
	for (r=0, c=0; r<N && c<M; ++r, ++c)
	{
		//选主元，maxp标记绝对值最大主元，pvt标记主元所在行
		for (maxp=0, i=r; i < N; ++i)
			if (fabs(a[i][c])>fabs(maxp)) maxp = a[pvt=i][c];
		//若当前列当前行以下全部是0，则当前行不变，处理下一列
		if (sgn(maxp)==0)
		{
			r--;
			continue;
		}
		//与r行交换
		if (pvt != r)
			for (j = r; j <= M; ++j) swap(a[r][j], a[pvt][j]);
		//开始消元
		for (j = c+1; j <= M; ++j)
		{
			a[r][j] /= maxp;//第r行以a[r][c]归一化
			for (i = r+1; i < N; ++i)
				a[i][j] -= a[i][c]*a[r][j];
		}
	}
	//无解的情况，增广阵存在[0,0,...,x(x!=0)]的行
	for (i = r; i < N; ++i)
		if (sgn(a[i][M])) return -1;
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
			a[i][M] -= a[j][M]*a[i][j];
	return 0;
}

//高斯消元求解逆矩阵
//输入：方阵阶数N，方阵a。
//输出：返回值：0为逆不存在，1为存在；逆矩阵返回在b中。
bool inv(int N, double a[][MAXN], double b[][MAXN])
{
	int i, j, r, c, pvt;
	double k, maxp;
	//将单位矩阵写入b
	for (r = 0; r < N; ++r)
		for (c = 0; c < N; ++c)
			b[r][c] = r==c?1:0;
	//将a化为行阶梯阵，同时对b施以同样的初等行变换
	//r为当前处理行/列
	for (r = 0; r < N; ++r)
	{
		//选主元，maxp标记绝对值最大主元，pvt标记主元所在行
		for (maxp=0, i=r; i < N; ++i)
			if (fabs(a[i][r])>fabs(maxp)) maxp = a[pvt=i][r];
		//若当前列当前行以下全部是0，则无逆矩阵，直接跳出
		if (fabs(maxp) < EPS) return 0;
		//与r行交换
		if (pvt != r)
			for (j = 0; j < N; ++j)
			{
				swap(a[r][j], a[pvt][j]);
				swap(b[r][j], b[pvt][j]);
			}
		//开始消元
		for (j = 0; j < N; ++j)
		{
			a[r][j] /= maxp;//第r行以a[r][r]归一化
			b[r][j] /= maxp;
		}
		for (i = r+1; i < N; ++i)
		{
			k = a[i][r];
			for (j = 0; j < N; ++j)
			{
				a[i][j] -= k*a[r][j];
				b[i][j] -= k*b[r][j];
			}
		}
	}
	//将a化为单位矩阵，同时对b施以同样的初等行变换
	//r为当前处理行
	for (r = 0; r < N; ++r)
	{
		for (i = r+1; i < N; ++i)
		{
			if (fabs(a[r][i]) < EPS) continue;
			maxp = a[r][i];
			for (j = 0; j < N; ++j)
			{
				a[r][j] -= maxp*a[i][j];
				b[r][j] -= maxp*b[i][j];
			}
		}
	}
	return 1;
}
