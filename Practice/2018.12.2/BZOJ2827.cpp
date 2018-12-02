#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100;
const int inf=2147483647;

class Splay
{
public:
	int key,mx1,mx2,lz1,lz2;
	int ch[2],fa,size;
};

int n;
Splay S[maxN];
int X[maxN],Y[maxN],St[maxN];
map<pair<int,int>,int> Rt;

int Input();
void Insert(int id);
void Erase(int id);
bool cmp(int a,int b);
void Update(int x);
void PushDown(int x);
void GM(int x,int sz,int key);
void Rotate(int x);
void Splay(int &rt,int x,int goal);
int Prev(int &rt,int x);
int Next(int &rt,int x);
void dfs_pushdown(int x);
void outp(int now);

int main(){
	//freopen("in","r",stdin);
	n=Input();//scanf("%d",&n);
	for (int i=1;i<=n;i++){
		S[i].key=Input();X[i]=Input();Y[i]=Input();//scanf("%d%d%d",&S[i].key,&X[i],&Y[i]);
		S[i].size=1;Insert(i);
	}
	int TTT=Input();//scanf("%d",&TTT);
	while (TTT--){
		int v=Input(),x=Input(),y=Input();//scanf("%d%d%d",&v,&x,&y);
		Erase(v);X[v]=x;Y[v]=y;Insert(v);
        /*
		cout<<"T="<<TTT<<endl;
		for (map<pair<int,int>,int>::iterator it=Rt.begin();it!=Rt.end();it++)
			if ((*it).second){
				cout<<"("<<(*it).first.first<<","<<(*it).first.second<<")"<<endl;
				outp((*it).second);
			}
		//*/
		//outp(Rt[make_pair(X[89],Y[89])]);cout<<endl;
	}
	for (int i=1;i<=n;i++)
		if (Rt.count(make_pair(X[i],Y[i]))){
			dfs_pushdown(Rt[make_pair(X[i],Y[i])]);
			Rt.erase(make_pair(X[i],Y[i]));
		}
	for (int i=1;i<=n;i++) printf("%lld\n",1ll*S[i].mx1*S[i].mx2);
	return 0;
}

int Input(){
	int x=0,k=1;char ch=getchar();
	while ((!isdigit(ch))&&(ch!='-')) ch=getchar();
	if (ch=='-') k=-1,ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x*k;
}

void Insert(int id){
	//cout<<"Insert:"<<id<<endl;
	pair<int,int> p=make_pair(X[id],Y[id]);
	if (Rt.count(p)==0){
		Rt[p]=id;S[id].fa=S[id].ch[0]=S[id].ch[1]=0;
	}
	else{
		int now=Rt[p];
		do{
			PushDown(now);
			if (cmp(now,id)){
				if (S[now].ch[1]) now=S[now].ch[1];
				else{
					S[now].ch[1]=id;S[id].fa=now;Splay(Rt[p],id,0);
					break;
				}
			}
			else{
				if (S[now].ch[0]) now=S[now].ch[0];
				else{
					S[now].ch[0]=id;S[id].fa=now;Splay(Rt[p],id,0);
					break;
				}
			}
		}
		while (1);
		now=Rt[p];
		while (S[now].ch[1]) now=S[now].ch[1];
		Splay(Rt[p],now,0);GM(S[now].ch[0],S[now].size-1,S[now].key);
		//cout<<S[now].size-1<<" "<<S[now].key<<endl;
		int pre=Prev(Rt[p],now);Splay(Rt[p],pre,0);
		//cout<<"now:"<<now<<" pre:"<<pre<<" "<<S[pre].ch[1]<<" "<<S[pre].size<<" "<<S[pre].key<<endl;
		GM(S[pre].ch[1],S[pre].size-1,S[pre].key);
	}
	return;
}

void Erase(int id){
	//cout<<"Erase:"<<id<<endl;
	pair<int,int> p=make_pair(X[id],Y[id]);
	if (S[Rt[p]].size==1) Rt.erase(p);
	else{
		if (Prev(Rt[p],id)==-1){
			Splay(Rt[p],id,0);Rt[p]=S[id].ch[1];
			S[S[id].ch[1]].fa=0;S[id].ch[1]=0;
			Update(id);
		}
		else if (Next(Rt[p],id)==-1){
			Splay(Rt[p],id,0);Rt[p]=S[id].ch[0];
			S[S[id].ch[0]].fa=0;S[id].ch[0]=0;
			Update(id);
		}
		else{
			int pre=Prev(Rt[p],id),nxt=Next(Rt[p],id);
			//cout<<"Case3:"<<pre<<" "<<nxt<<endl;
			Splay(Rt[p],pre,0);Splay(Rt[p],nxt,pre);
			S[id].fa=0;S[nxt].ch[0]=0;Update(nxt);Update(pre);
			//outp(Rt[p]);
		}
	}
	return;
}

bool cmp(int a,int b){
	if (S[a].key!=S[b].key) return S[a].key<S[b].key;
	else return a<b;
}

void Update(int x){
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
	return;
}

void PushDown(int x){
	if ((S[x].lz1!=0)||(S[x].lz2!=0)){
		if (S[x].ch[0]) GM(S[x].ch[0],S[x].lz1,S[x].lz2);
		if (S[x].ch[1]) GM(S[x].ch[1],S[x].lz1,S[x].lz2);
		S[x].lz1=S[x].lz2=0;
	}
	return;
}

void GM(int x,int sz,int key){
	S[x].mx1=max(S[x].mx1,sz);S[x].lz1=max(S[x].lz1,sz);
	S[x].mx2=max(S[x].mx2,key);S[x].lz2=max(S[x].lz2,key);
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

void Splay(int &rt,int x,int goal){
	int top=0,now=x;//cout<<rt<<" "<<x<<" "<<goal<<" "<<S[x].fa<<endl;
	while (now) St[++top]=now,now=S[now].fa;
	for (int i=top;i>=1;i--) PushDown(St[i]);
	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	if (goal==0) rt=x;return;
}

int Prev(int &rt,int x){
	Splay(rt,x,0);if (S[x].ch[0]==0) return -1;
	int now=S[x].ch[0];while (S[now].ch[1]) now=S[now].ch[1];
	return now;
}

int Next(int &rt,int x){
	Splay(rt,x,0);if (S[x].ch[1]==0) return -1;
	int now=S[x].ch[1];while (S[now].ch[0]) now=S[now].ch[0];
	return now;
}

void dfs_pushdown(int x){
	PushDown(x);
	if (S[x].ch[0]) dfs_pushdown(S[x].ch[0]);
	if (S[x].ch[1]) dfs_pushdown(S[x].ch[1]);
	return;
}

void outp(int x){
	cout<<x<<" "<<S[x].ch[0]<<" "<<S[x].ch[1]<<" "<<S[x].fa<<" "<<S[x].key<<" "<<S[x].mx1<<" "<<S[x].mx2<<" "<<S[x].lz1<<" "<<S[x].lz2<<endl;
	if (S[x].ch[0]) outp(S[x].ch[0]);
	if (S[x].ch[1]) outp(S[x].ch[1]);
	return;
}
/*
5
1 1 1
3 1 2
4 4 4
2 0 1
2 2 3
5
1 1 2
2 4 4
2 4 3
3 0 1
5 0 1
//*/
