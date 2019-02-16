#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=6;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,K;
int Mp[maxN][maxM+10],Ans[maxN][maxM+10],P[10];
int now,F[2][3001],Seq[2][3001],scnt[2],tim,Tim[3001],Pos[3001];
vector<pair<int,int> > V[maxN];
vector<int> Sv,Match[3000];

void Plus(int S,int key);
bool match_check(int S1,int S2);
void Trans1(int i,int j);
void Trans2(int i,int j);

int main(){
	P[0]=1;for (int i=1;i<10;i++) P[i]=P[i-1]*3;
	scanf("%d%d%d",&n,&m,&K);for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Mp[i][j]=1;
	for (int i=1;i<=K;i++){
		int x,y;scanf("%d%d",&x,&y);
		Mp[x][y]=0;
	}
	now=0;F[now][1]=1;scnt[now]=1;Seq[now][1]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			now^=1;tim++;scnt[now]=0;
			Trans1(i,j);
			if (j==m){
				for (int l=1;l<=scnt[now];l++)
					if (Seq[now][l]%3==0) V[i].push_back(make_pair(Seq[now][l],F[now][l]));
				//if (V[i].size()) sort(V[i].begin(),V[i].end());
			}
		}
	sort(Sv.begin(),Sv.end());
	for (int i=0,sz=Sv.size();i<sz;i++){
		//for (int j=1;j<=m;j++) cout<<Sv[i]/P[j]%3;cout<<endl;
		for (int j=0;j<sz;j++)
			if (match_check(Sv[i],Sv[j])) Match[Sv[i]].push_back(Sv[j]);
		/*
		for (int j=0,ssz=Match[Sv[i]].size();j<ssz;j++)
		{
			for (int k=1;k<=m;k++) cout<<Sv[i]/P[k]%3;cout<<endl;
			for (int k=1;k<=m;k++) cout<<Match[Sv[i]][j]/P[k]%3;cout<<endl;
			cout<<endl;
		}
		//*/
	}
	now=0;mem(F,0);mem(scnt,0);mem(Seq,0);
	F[now][1]=1;scnt[now]=1;Seq[now][1]=0;
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--){
			now^=1;++tim;scnt[now]=0;
			Trans2(i,j);
			if (j==1){
				for (int k=0,sz1=V[i-1].size();k<sz1;k++)
					for (int l=0,sz2=Match[V[i-1][k].first].size();l<sz2;l++)
						if (Tim[Match[V[i-1][k].first][l]]==tim)
							for (int p=1;p<=m;p++)
								if (V[i-1][k].first/P[p]%3) (Ans[i-1][p]+=1ll*F[now][Pos[Match[V[i-1][k].first][l]]]*V[i-1][k].second%Mod)%=Mod;
			}
		}
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",Ans[x][y]);
	}
	return 0;
}

void Plus(int S,int key){
	if ((Tim[S]==0)&&(S%3==0)) Sv.push_back(S);
	if (Tim[S]!=tim) Pos[Seq[now][++scnt[now]]=S]=scnt[now],Tim[S]=tim;
	F[now][Pos[S]]=(F[now][Pos[S]]+key)%Mod;return;
}

bool match_check(int S1,int S2){
	for (int i=1;i<=m;i++) if ((S1/P[i]%3==0)^(S2/P[i]%3==0)) return 0;
	if (S1==0) return 1;
	int c1[10],c2[10],st1[10],st2[10],top1=0,top2=0,cnt=0,vis[10],x=1,tot=0;mem(vis,0);
	for (int i=1;i<=m;i++)
		if (S1/P[i]%3!=0){
			++cnt;
			if (S1/P[i]%3==1) st1[++top1]=cnt;
			else c1[st1[top1]]=cnt,c1[cnt]=st1[top1],--top1;
			if (S2/P[i]%3==1) st2[++top2]=cnt;
			else c2[st2[top2]]=cnt,c2[cnt]=st2[top2],--top2;
		}
	//for (int i=1;i<=m;i++) cout<<S1/P[i]%3;cout<<" ";for (int i=1;i<=cnt;i++) cout<<c1[i];cout<<endl;
	//for (int i=1;i<=m;i++) cout<<S2/P[i]%3;cout<<" ";for (int i=1;i<=cnt;i++) cout<<c2[i];cout<<endl;
	while (vis[x]==0){
		vis[x]=1;x=c1[c2[x]];tot+=2;
	}
	return tot==cnt;
}

void Trans1(int i,int j){
	for (int l=1;l<=scnt[now^1];l++){
		int S=Seq[now^1][l],x=S%3,y=S/P[j]%3,key=F[now^1][l];F[now^1][l]=0;
		if (S==3000) continue;
		if (Mp[i][j]==0){
			if ((x==0)&&(y==0)) Plus(S,key);
			continue;
		}
		if (x==0){
			if (y==0){
				Plus(S,key);
				if (Mp[i+1][j]&&Mp[i][j+1]) Plus(S+P[j]+2,key);
			}
			if (y==1){
				if (Mp[i][j+1]) Plus(S-P[j]+1,key);
				if (Mp[i+1][j]) Plus(S,key);
			}
			if (y==2){
				if (Mp[i][j+1]) Plus(S-P[j]*2+2,key);
				if (Mp[i+1][j]) Plus(S,key);
			}
		}
		if (x==1){
			if (y==0){
				if (Mp[i][j+1]) Plus(S,key);
				if (Mp[i+1][j]) Plus(S-1+P[j],key);
			}
			if (y==1){
				int cnt=0,p=j+1;
				while ((p<=m)&&((cnt)||(S/P[p]%3!=2))){
					if (S/P[p]%3==1) ++cnt;
					if (S/P[p]%3==2) --cnt;
					++p;
				}
				if (p<=m) Plus(S-1-P[j]-P[p],key);
			}
			if (y==2){
				/*
				bool flag=1;
				for (int l=1;(l<=m)&&(flag);l++)
					if ((l!=j)&&(S/P[l]%3!=0)) flag=0;
				if (flag) Plus(3000,key);
				//*/
			}
		}
		if (x==2){
			if (y==0){
				if (Mp[i][j+1]) Plus(S,key);
				if (Mp[i+1][j]) Plus(S-2+P[j]*2,key);
			}
			if (y==1) Plus(S-2-P[j],key);
			if (y==2){
				int cnt=0,p=j-1;
				while ((p>=1)&&((cnt)||(S/P[p]%3!=1))){
					if (S/P[p]%3==1) --cnt;
					if (S/P[p]%3==2) ++cnt;
					--p;
				}
				if (p>=1) Plus(S-2-P[j]*2+P[p],key);
			}
		}
	}
	return;
}

void Trans2(int i,int j){
	for (int l=1;l<=scnt[now^1];l++){
		int S=Seq[now^1][l],x=S%3,y=S/P[j]%3,key=F[now^1][l];F[now^1][l]=0;
		if (Mp[i][j]==0){
			if ((x==0)&&(y==0)) Plus(S,key);
			continue;
		}
		if (x==0){
			if (y==0){
				Plus(S,key);
				if (Mp[i-1][j]&&Mp[i][j-1]) Plus(S+1+P[j]*2,key);
			}
			if (y==1){
				if (Mp[i-1][j]) Plus(S,key);
				if (Mp[i][j-1]) Plus(S-P[j]+1,key);
			}
			if (y==2){
				if (Mp[i-1][j]) Plus(S,key);
				if (Mp[i][j-1]) Plus(S-P[j]*2+2,key);
			}
		}
		if (x==1){
			if (y==0){
				if (Mp[i-1][j]) Plus(S-1+P[j],key);
				if (Mp[i][j-1]) Plus(S,key);
			}
			if (y==1){
				int cnt=0,p=j+1;
				while ((p<=m)&&((cnt)||(S/P[p]%3!=2))){
					if (S/P[p]%3==1) ++cnt;
					if (S/P[p]%3==2) --cnt;
					++p;
				}
				if (p<=m) Plus(S-1-P[j]-P[p],key);
			}
			if (y==2) Plus(S-1-P[j]*2,key);
		}
		if (x==2){
			if (y==0){
				if (Mp[i-1][j]) Plus(S-2+P[j]*2,key);
				if (Mp[i][j-1]) Plus(S,key);
			}
			if (y==1);
			if (y==2){
				int cnt=0,p=j-1;
				while ((p>=1)&&(cnt||(S/P[p]%3!=1))){
					if (S/P[p]%3==1) --cnt;
					if (S/P[p]%3==2) ++cnt;
					--p;
				}
				if (p>=1) Plus(S-2-P[j]*2+P[p],key);
			}
		}
	}
	return;
}
