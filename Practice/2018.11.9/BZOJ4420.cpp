#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30010;
const int maxNum=700000;
const int inf=2147483647;

int n,D;
int Ten[10];
int stacnt,sta[maxN];
int F[2][maxN][6];
char Input[maxN];
map<int,int> ats;
pair<int,int> Rc[maxNum][6];

void dfs(int now,int key);
bool check(int key);
pair<int,int> calc(int key,int pos);
void Max(int &x,int y);

int main(){
	Ten[0]=1;for (int i=1;i<10;i++) Ten[i]=Ten[i-1]*10;
	scanf("%d%d",&n,&D);scanf("%s",Input+1);
	dfs(1,0);mem(F,128);F[0][1][0]=0;int Ans=-inf;mem(Rc,-1);
	//for (int i=1;i<=stacnt;i++) printf("%04d\n",sta[i]);
	for (int i=0;i<D;i++){
		int now=i&1;mem(F[now^1],128);
		for (int j=1;j<=stacnt;j++)
			for (int k=0;k<=5;k++)
				if (F[now][j][k]>=0)
					for (int p=0;p<n;p++)
						if (sta[j]/Ten[p]%10==0){
							pair<int,int> R=calc(sta[j]+(Input[i+1]-'0')*Ten[p],p);
							Max(F[now^1][R.first][k],F[now][j][k]+R.second);
							/*
							if (k!=0){
								for (int pp=0;pp<n;pp++)
									if (sta[R.first]/Ten[pp]%10==0) {
										pair<int,int> RR=calc(sta[R.first]+k*Ten[pp],pp);
										Max(F[now^1][RR.first][0],F[now][j][k]+R.second+RR.second);
									}
							}
							//*/
							if (k==0) Max(F[now^1][j][Input[i+1]-'0'],F[now][j][k]);
						}
		for (int j=1;j<=stacnt;j++)
			for (int k=1;k<=5;k++)
				if (F[now^1][j][k]>=0)
					for (int p=0;p<n;p++)
						if (sta[j]/Ten[p]%10==0){
							pair<int,int> R=calc(sta[j]+k*Ten[p],p);
							Max(F[now^1][R.first][0],F[now^1][j][k]+R.second);
						}
		for (int j=1;j<=stacnt;j++) for (int k=0;k<=5;k++) Max(Ans,F[now^1][j][k]);
	}
	for (int j=1;j<=stacnt;j++) for (int k=0;k<=5;k++) Max(Ans,F[D&1][j][k]);
	printf("%d\n",Ans);return 0;
}

void dfs(int now,int key){
	if (now==n+1){
		if (check(key)) ats[sta[++stacnt]=key]=stacnt;
		return;
	}
	for (int i=0;i<=5;i++) dfs(now+1,key*10+i);
	return;
}

bool check(int key){
	int lst=0;
	for (int i=0;i<n;i++){
		if ((lst!=0)&&(key%10!=0)&&(lst==key%10)) return 0;
		lst=key%10;key/=10;
	}
	return 1;
}

pair<int,int> calc(int key,int pos){
	if (Rc[key][pos].first!=-1) return Rc[key][pos];
	int ret=0,kk=key;//key=sta[key];
	while (check(key)==0){
		int l=pos,r=pos,level=key/Ten[pos]%10;
		while ((l>0)&&(key/Ten[l-1]%10==level)) --l;
		while ((r<n-1)&&(key/Ten[r+1]%10==level)) ++r;
		if (l==r) break;
		for (int i=l;i<=r;i++) key=key-level*Ten[i];
		ret=ret+(r-l+1)*(1<<level);++level;
		if (level<=5) key+=level*Ten[pos];
	}
	return Rc[kk][pos]=make_pair(ats[key],ret);
}

void Max(int &x,int y){
	if (y>x) x=y;return;
}
