#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000<<1;
const int inf=2147483647;

int n;
int Len[maxN];
char str[maxN];
bool used[30];
vector<int> T[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		Len[i<<1]=x+1;
	}
	for (int i=1;i<n;i++){
		int x;scanf("%d",&x);
		Len[i<<1|1]=x+1;
	}
	Len[1]=1;Len[n<<1|1]=1;
	//for (int i=1;i<=n+n+1;i++) cout<<Len[i]<<" ";cout<<endl;
	for (int i=1;i<=n+n+1;i++) T[i+Len[i]].push_back(i-Len[i]);
	/*
	for (int i=2;i<=n+n;i=i+2){
		mem(used,0);
		for (int j=0,sz=T[i].size();j<sz;j++)
			used[str[T[i][j]]-'a']=1;
		str[i]='a';
		while (used[str[i]-'a']) ++str[i];
	}
	//*/
	
	int p=1,mx=1+Len[1];
	for (int i=2;i<=n+n;i++){
		//cout<<i<<" p:"<<p<<" mx:"<<mx<<endl;
		if (i&1){
			if (i+Len[i]>mx) mx=i+Len[i],p=i;
		}
		else {
			if (i>=mx){
				p=i;mx=i+Len[i];
				mem(used,0);
				for (int j=0,sz=T[i].size();j<sz;j++)
					used[str[T[i][j]]-'a']=1;
				str[i]='a';
				while (used[str[i]-'a']) ++str[i];
			}
			else str[i]=str[p*2-i];
			if (i+Len[i]>=mx) mx=i+Len[i],p=i;
		}
	}
	//*/
	//for (int i=1;i<=n+n;i++) printf("%d ",str[i]);printf("\n");
	for (int i=2;i<=n+n;i+=2) printf("%c",str[i]);printf("\n");
	return 0;
}
