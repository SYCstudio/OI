#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Mod=20130426;
const int inf=2147483647;

class SplayData
{
public:
	int key,mul,plus,idplus;
	int ch[2],fa,id;
	SplayData(){
		mul=1;plus=key=ch[0]=ch[1]=fa=id=idplus=0;return;
	}
	void init(){
		mul=1;plus=key=ch[0]=ch[1]=fa=id=idplus=0;return;
	}
};

int Q,root,nodecnt=0;
SplayData S[maxN];
int Pow[maxN];

int Build(int l,int r,int fa);
void Plus(int x,int key);
void Mul(int x,int key);
void Idplus(int x,int key);
void PushDown(int x);
void Rotate(int x);
void Splay(int x,int goal);
int Kth(int k);
int Calc(int x);

int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d",&Q);
	root=Build(-1,100010,0);
	char ipt[8];int l,r,v;
	while (Q--){
		//cout<<"Q is:"<<Q<<endl;
		scanf("%s",ipt);
		if ((ipt[0]=='m')&&(strlen(ipt)==3)){
			scanf("%d%d%d",&l,&r,&v);
			int L=Kth(l-1),R=Kth(r+1);
			Splay(L,0);Splay(R,L);
			Mul(S[R].ch[0],v);
		}
		if (ipt[0]=='a'){
			scanf("%d%d%d",&l,&r,&v);
			int L=Kth(l-1),R=Kth(r+1);
			//cout<<L<<" "<<R<<endl;
			Splay(L,0);Splay(R,L);
			Plus(S[R].ch[0],v);
		}
		if ((ipt[0]=='m')&&(strlen(ipt)==4)){
			scanf("%d%d",&l,&r);

			//cout<<"A"<<endl;
			int L=Kth(l-1),R=Kth(r+1),a=Kth(r),b=Kth(r+2);
			Splay(L,0);Splay(R,L);Idplus(S[R].ch[0],1);

			//cout<<"B"<<endl;
			Splay(a,0);Splay(b,a);int id=S[b].ch[0],key=S[id].key;
			S[id].init();S[b].ch[0]=0;

			//cout<<"C"<<endl;
			L=Kth(l-1);R=Kth(l+1);
			Splay(L,0);Splay(R,L);
			S[R].ch[0]=id;S[id].fa=R;S[id].id=l;
			
			L=Kth(r-1);R=Kth(r+1);
			Splay(L,0);Splay(R,L);
			Plus(S[R].ch[0],key);
		}
		if (ipt[0]=='q'){
			scanf("%d",&v);
			Pow[0]=1;for (int i=1;i<=100010;i++) Pow[i]=1ll*Pow[i-1]*v%Mod;
			printf("%d\n",Calc(root));
		}
		//Calc(root);
	}
	return 0;
}

int Build(int l,int r,int fa){
	int mid=(l+r)>>1;
	int now=++nodecnt;
	S[now].id=mid;S[now].fa=fa;
	//cout<<"Build:"<<l<<" "<<r<<endl;
	if (l==r) return now;
	if (l<mid) S[now].ch[0]=Build(l,mid-1,now);
	if (mid<r) S[now].ch[1]=Build(mid+1,r,now);
	return now;
}

void Plus(int x,int key){
	S[x].key=(S[x].key+key)%Mod;
	S[x].plus=(S[x].plus+key)%Mod;
	return;
}

void Mul(int x,int key){
	S[x].key=1ll*S[x].key*key%Mod;
	S[x].mul=1ll*S[x].mul*key%Mod;
	S[x].plus=1ll*S[x].plus*key%Mod;
	return;
}

void Idplus(int x,int key){
	S[x].id=S[x].id+key;
	S[x].idplus=S[x].idplus+key;
	return;
}

void PushDown(int x){
	if (S[x].mul!=1){
		if (S[x].ch[0]) Mul(S[x].ch[0],S[x].mul);
		if (S[x].ch[1]) Mul(S[x].ch[1],S[x].mul);
		S[x].mul=1;
	}
	if (S[x].plus){
		if (S[x].ch[0]) Plus(S[x].ch[0],S[x].plus);
		if (S[x].ch[1]) Plus(S[x].ch[1],S[x].plus);
		S[x].plus=0;
	}
	if (S[x].idplus){
		if (S[x].ch[0]) Idplus(S[x].ch[0],S[x].idplus);
		if (S[x].ch[1]) Idplus(S[x].ch[1],S[x].idplus);
		S[x].idplus=0;
	}
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;return;
}

int Stk[maxN];

void Splay(int x,int goal){
	//cout<<"Splay:"<<x<<" "<<goal<<endl;
	int now=x,top=1;Stk[top]=now=x;
	while (S[now].fa) Stk[++top]=now=S[now].fa;
	while (top) PushDown(Stk[top--]);
	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		//cout<<x<<" "<<y<<" "<<z<<endl;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	if (goal==0) root=x;
	return;
}

int Kth(int k){
	//cout<<"GetKth:"<<k<<endl;
	int now=root;
	while (1){
		//cout<<now<<" "<<S[now].id<<":"<<S[now].ch[0]<<" "<<S[now].ch[1]<<endl;
		PushDown(now);
		if (S[now].id==k){
			Splay(now,0);
			return now;
		}
		if (S[now].id<k) now=S[now].ch[1];
		else now=S[now].ch[0];
	}
}

int Calc(int x){
	//cout<<"Calc:"<<x<<endl;
	PushDown(x);
	int ret=1ll*S[x].key*Pow[S[x].id]%Mod;
	if (S[x].ch[0]) ret=(ret+Calc(S[x].ch[0]))%Mod;
	if (S[x].ch[1]) ret=(ret+Calc(S[x].ch[1]))%Mod;
	return ret;
}
