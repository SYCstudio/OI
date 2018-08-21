#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

namespace IO{
    const int maxn((1 << 21) + 1);

    char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf, *oT = obuf + maxn - 1, c, st[55];
    int f, tp;
    char Getc() {
        return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
    }

    void Flush() {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }

    void Putc(char x) {
        *oS++ = x;
        if (oS == oT) Flush();
    }
    
    template <class Int> void Input(Int &x) {
        for (f = 1, c = Getc(); c < '0' || c > '9'; c = Getc()) f = c == '-' ? -1 : 1;
        for (x = 0; c <= '9' && c >= '0'; c = Getc()) x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    
    template <class Int> void Print(Int x) {
        if (!x) Putc('0');
        if (x < 0) Putc('-'), x = -x;
        while (x) st[++tp] = x % 10 + '0', x /= 10;
        while (tp) Putc(st[tp--]);
    }

    void Getstr(char *s, int &l) {
        for (c = Getc(); c < 'a' || c > 'z'; c = Getc());
        for (l = 0; c <= 'z' && c >= 'a'; c = Getc()) s[l++] = c;
        s[l] = 0;
    }
    
    void Putstr(const char *s) {
        for (int i = 0, n = strlen(s); i < n; ++i) Putc(s[i]);
    }
}

//using namespace IO;

void Input(int &x){
	scanf("%d",&x);return;
}

const int maxN=4010;
const int inf=2147483647;

class Data
{
public:
	int key,cnt;
};

int n,K;
int W[maxN][maxN];
int Q[maxN];
Data Ans,F[maxN];

void Calc(int limit);
bool operator < (Data A,Data B);
bool operator <= (Data A,Data B);
bool operator > (Data A,Data B);
Data operator + (Data A,Data B);
Data operator + (Data A,int B);
int Lower(int u,int v);

int main(){
	Input(n);Input(K);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Input(W[i][j]);
	for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) W[i][j]+=W[i][j-1];

	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<W[i][j]<<" ";cout<<endl;
	}

	int L=-W[1][n],R=W[1][n],pos;
	do{
		int mid=(L+R)>>1;
		Calc(mid);
		if (Ans.cnt>=K) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);

	Calc(pos);cout<<"pos:"<<pos<<endl;
	printf("%d\n",Ans.key-K*pos);return 0;
}

void Calc(int limit){
	cout<<"Calc:"<<limit<<endl;
	F[0]=((Data){0,0});int L=1,R=1;Q[1]=0;
	for (int i=1;i<=n;i++){
		while ((L<R)&&(Lower(Q[L],Q[L+1])<=i)) L++;
		F[i]=F[Q[L]]+((Data){W[Q[L]+1][i]+limit,1});
		while ((L<=R)&&(Lower))
	}
	Ans=F[n];
	return;
}

bool operator < (Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.cnt<B.cnt;
}

bool operator >= (Data A,Data B){
	if (A.key!=B.key) return A.key>B.key;
	return A.cnt>=B.cnt;
}

bool operator > (Data A,Data B){
	if (A.key!=B.key) return A.key>B.key;
	return A.cnt>B.cnt;
}

Data operator + (Data A,Data B){
	return ((Data){A.key+B.key,A.cnt+B.cnt});
}

Data operator + (Data A,int B){
	return ((Data){A.key+B,A.cnt});
}

int Lower(int u,int v){
	if (F[u]+W[u+1][n]<F[v]+W[v+1][n]) return inf;
	int L=max(u,v),R=n,ret=inf;
	do{
		int mid=(L+R)>>1;
		if (F[u]+W[u+1][mid]>=F[v]+W[v+1][mid]) ret=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);
	return ret;
}
