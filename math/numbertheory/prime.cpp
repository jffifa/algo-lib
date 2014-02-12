#include <cmath>

const int PSIZE = 100000;

int p[PSIZE], pcnt=0;

/*
//判断素数
bool prime(int n) {
	if ((n!=2&&!(n%2))||(n!=3&&!(n%3))||(n!=5&&!(n%5))||(n!=7&&!(n%7)))
		return 0;
	for (int i = 0; p[i]*p[i]<=n; ++i)
		if (n%p[i]==0) return 0;
	return n>1;
}

//初始化素数表
void initprime() {
	p[pcnt++] = 2;
	for (int i = 3; i <= 500000; ++i)
		if (prime(i)) p[pcnt++] = i;
}

//分解质因数
//f存放质因数，nf存放对应质因数个数
//返回不同质因数个数
int pf(int n, int *f, int *nf) {
	int cnt = 0;
	int n2 = (int)sqrt((double)n);
	for (int i = 0; n>1 && p[i]<=n2; ++i)
		if (n%p[i]==0) {
			for (nf[cnt]=0; n%p[i]==0; n/=p[i]) ++nf[cnt];
			f[cnt++] = p[i];
		}
	if (n > 1) {
		nf[cnt] = 1;
		f[cnt++] = n;
	}
	return cnt;
}
*/
//线性时间筛素数
const int MAX = 500050;
int minf[MAX];//存放x的最小质因数
void initprime() {
	for (int i = 2; i < MAX; ++i) {
		if (!minf[i]) {
			minf[i] = i;
			p[pcnt++] = i;
		}
		for (int j = 0; j < pcnt && p[j]*i < MAX; ++j) {
			minf[p[j]*i] = p[j];
			if (i%p[j]==0) break;
		}
	}
}

//分解质因数(限于MAX)
//f存放质因数，nf存放对应质因数个数
//返回不同质因数个数
int pf(int n, int *f, int *nf) {
	int cnt = 0;
	f[cnt] = 0;
	while (n > 1) {
		int now = minf[n];
		n /= now;
		if (now == f[cnt]) ++nf[cnt];
		else {
			f[cnt++] = now;
			nf[cnt] = 1;
		}
	}
	return cnt;
}
/*
//求欧拉函数phi
//注意：需要的话，可以在initprime里预处理出
int phi(int n) {
	int q = n/minf[n];
	if (q % minf[n]) return phi(q)*minf[n];
	else return phi(q)*(minf[n]-1);
}
const int MAX = 500050;
int minf[MAX];//存放x的最小质因数
int phi[MAX];//存放欧拉函数
void initprime() {
	for (int i = 2; i < MAX; ++i) {
		if (!minf[i]) {
			p[pcnt++] = i;
			phi[i] = i-1;
		}
		for (int j = 0; j < pcnt && p[j]*i < MAX; ++j) {
			minf[p[j]*i] = p[j];
			if (i%p[j])
				phi[p[j]*i] = phi[i]*(p[j]-1);
			else {
				phi[p[j]*i] = phi[i]*p[j];
				break;
			}
		}
	}
}
*/
