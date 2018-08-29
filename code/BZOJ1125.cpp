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
int Ans[maxN];
multiset<ull> Ms;

int main(){
	Base[0]=1;for (int i=1;i<maxN;i++) Base[i]=Base[i-1]*base;
	scanf("%d%d%d",&n,&L,&m);
	for (int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=L;j++) Hash[i]=Hash[i]*base+(ull)(str[i][j]-'a');
		Ms.insert(Hash[i]);
	}
	for (int i=1;i<=n;i++) Ans[i]=Ms.count(Hash[i]);
	//cout<<"Input over"<<endl;
	//for (int i=1;i<=n;i++) cout<<Hash[i]<<" ";cout<<endl;
	while (m--){
		int p1,w1,p2,w2;scanf("%d%d%d%d",&p1,&w1,&p2,&w2);
		Ms.erase(Ms.find(Hash[p1]));if (p1!=p2) Ms.erase(Ms.find(Hash[p2]));
		Hash[p1]-=(ull)(str[p1][w1]-'a')*Base[L-w1];
		Hash[p2]-=(ull)(str[p2][w2]-'a')*Base[L-w2];
		swap(str[p1][w1],str[p2][w2]);
		Hash[p1]+=(ull)(str[p1][w1]-'a')*Base[L-w1];
		Hash[p2]+=(ull)(str[p2][w2]-'a')*Base[L-w2];
		Ms.insert(Hash[p1]);if (p1!=p2) Ms.insert(Hash[p2]);
		for (int i=1;i<=n;i++) Ans[i]=max(Ans[i],(int)Ms.count(Hash[i]));
		//for (int i=1;i<=n;i++) cout<<Hash[i]<<" ";cout<<endl;
	}

	for (int i=1;i<=n;i++) printf("%d\n",Ans[i]);

	return 0;
}
