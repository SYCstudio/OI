#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxL=110;
const ull base=13;
const int inf=2147483647;

int n,m,L;
char str[maxN][maxL];
ull Hash[maxN],Base[maxN];
int Cnt[maxN];
multiset<ull> Ms;

int main(){
	Base[0]=1;for (int i=1;i<maxN;i++) Base[i]=Base[i-1]*base;
	scanf("%d%d%d",&n,&L,&m);
	for (int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=L;j++) Hash[i]=Hash[i]*base+(ull)(str[j]-'a');
		Ms.insert(Hash[i]);
	}

	while (m--){
		int p1,w1,p2,w2;scanf("%d%d%d%d",&p1,&w1,&p2,&w2);
		Ms.erase(Ms.find(Hash[p1]));Ms.erase(Ms.find(Hash[p2]));
		Hash[p1]-=str[p1][w1]*Base[L-w1];
		Hash[p2]-=str[p2][w2]*Base[L-w2];
		swap(str[p1][w1],str[p2][w2]);
		Hash[p1]+=str[p1][w1]*Base[L-w1];
		Hash[p2]+=str[p2][w2]*Base[L-w2];
		Ms.insert(Hash[p1]);Ms.insert(Hash[p2]);
	}
}
