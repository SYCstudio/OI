#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxT=1010000;
const int maxAlpha=20;
const int inf=2147483647;

int n;
int nodecnt=1,root=1;
int son[maxT][maxAlpha],cnt[maxT];
vector<int> Tim[maxT];
char Input[maxN];

void Insert(char *str,int key,int t);
int Query(char *str,int key);

int main(){
	scanf("%d",&n);
	int lstans=0;
	for (int ni=1;ni<=n;ni++){
		int opt;scanf("%d %s",&opt,Input+1);
		if (opt==1) Insert(Input,1,ni);
		else if (opt==2) Insert(Input,-1,ni);
		else{
			ll a,b,c;scanf("%lld%lld%lld",&a,&b,&c);
			int key=(a*abs(lstans)+b)%c;
			printf("%d\n",lstans=Query(Input,key));
		}
	}
	return 0;
}

void Insert(char *str,int key,int t){
	int len=strlen(str+1),now=1;
	for (int i=1;i<=len;i++){
		int c=str[i]-'a';
		if (son[now][c]==0){
			son[now][c]=++nodecnt;
			Tim[nodecnt].push_back(t);
		}
		now=son[now][c];cnt[now]+=key;
		if (cnt[now]>Tim[now].size()) Tim[now].push_back(t);
	}
	//cout<<"I:"<<(str+1)<<" "<<now<<" "<<cnt[now]<<endl;
	return;
}

int Query(char *str,int key){
	int len=strlen(str+1),now=1;
	for (int i=1;i<=len;i++){
		int c=str[i]-'a';
		if (son[now][c]==0) return -1;
		now=son[now][c];
	}
	//cout<<"Q:"<<(str+1)<<" "<<now<<" key:"<<key<<endl;
	if (Tim[now].size()-1<key) return -1;
	return Tim[now][key];
}
