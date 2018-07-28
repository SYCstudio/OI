#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010000;
const int maxAlpha=26;
const int inf=2147483647;

class SAM
{
public:
	int son[maxAlpha],fa,len;
};

class SplayData
{
public:
	int ch[2],fa,cnt,lz,rev;
};

int n,last=1,nodecnt=1,St[maxN];
char Input[maxN],Opt[20];
SAM T[maxN];
SplayData S[maxN];

void GetRealstr(char *s,int mask);
void Insert(int c);
bool Isroot(int x);
void Rotate(int x);
void PushDown(int x);
void Add(int x,int c);
void Revse(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Link(int u,int v);
void Cut(int u,int v);

void OutpSAM();
void OutpLCT();

int main()
{
	int Q;
	scanf("%d",&Q);
	scanf("%s",Input);
	int len=strlen(Input);
	for (int i=0;i<len;i++){
		Insert(Input[i]-'A');
		//OutpSAM();OutpLCT();
	}
	

	int mask=0;
	while (Q--){
		scanf("%s",Opt);
		if (Opt[0]=='A'){
			scanf("%s",Input);GetRealstr(Input,mask);
			len=strlen(Input);
			for (int i=0;i<len;i++) Insert(Input[i]-'A');
			//OutpSAM();OutpLCT();
		}
		if (Opt[0]=='Q'){
			scanf("%s",Input);GetRealstr(Input,mask);
			len=strlen(Input);
			int now=1;
			for (int i=0;i<len;i++){
				if (T[now].son[Input[i]-'A']==0){
					now=0;break;
				}
				now=T[now].son[Input[i]-'A'];
				//cout<<i<<" "<<now<<endl;
			}
			if (now==0) printf("0\n");
			else{
				Makeroot(1);Access(now);Splay(now);
				printf("%d\n",S[now].cnt);mask^=S[now].cnt;
			}
		}
	}
	
	return 0;			
}

void GetRealstr(char *s,int mask){
	//return;//////////////////////////////////////////////////////
	int l=strlen(s);
	for (int i=0;i<l;i++){
		mask=(mask*131+i)%l;
		swap(s[i],s[mask]);
	}
	return;
}

void Insert(int c){
	int np=++nodecnt,p=last;last=nodecnt;
	T[np].len=T[p].len+1;
	while ((p!=0)&&(T[p].son[c]==0)) T[p].son[c]=np,p=T[p].fa;
	if (p==0) T[np].fa=1,Link(1,np);
	else{
		int q=T[p].son[c];
		if (T[q].len==T[p].len+1) T[np].fa=q,Link(q,np);
		else{
			int nq=++nodecnt;T[nq]=T[q];T[nq].len=T[p].len+1;
			Makeroot(q);Splay(q);S[nq].cnt=S[q].cnt;S[nq].fa=S[q].fa;
			Cut(T[q].fa,q);Link(q,nq);Link(np,nq);Link(nq,T[nq].fa);
			T[q].fa=T[np].fa=nq;
			while ((p!=0)&&(T[p].son[c]==q)) T[p].son[c]=nq,p=T[p].fa;
		}
	}
	//OutpLCT();
	//cout<<"Insert over"<<endl;
	Makeroot(1);Access(last);Splay(1);Add(1,1);
	return;
}

bool Isroot(int x){
	if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
	return 1;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;S[y].fa=x;
	return;
}

void PushDown(int x){
	if (S[x].lz){
		if (S[x].ch[0]) Add(S[x].ch[0],S[x].lz);
		if (S[x].ch[1]) Add(S[x].ch[1],S[x].lz);
		S[x].lz=0;
	}
	if (S[x].rev){
		if (S[x].ch[0]) Revse(S[x].ch[0]);
		if (S[x].ch[1]) Revse(S[x].ch[1]);
		S[x].rev=0;
	}
	return;
}
void Add(int x,int c){
	//cout<<"Add:"<<x<<" "<<c<<endl;
	S[x].cnt+=c;S[x].lz+=c;
	return;
}

void Revse(int x){
	S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	return;
}

void Splay(int x){
	//cout<<"Splay:"<<x<<endl;
	int now=x,top=1;St[top]=x;
	while (Isroot(now)==0) now=St[++top]=S[now].fa;
	while (top) PushDown(St[top--]);
	//cout<<"PushDown ok"<<endl;
	while (Isroot(x)==0){
		int y=S[x].fa,z=S[y].fa;
		//cout<<x<<" "<<y<<" "<<z<<endl;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	//cout<<"Splay over"<<endl;
	return;
}

void Access(int x){
	//cout<<"Access:"<<x<<endl;
	int lastx=0;
	while (x){
		Splay(x);S[x].ch[1]=lastx;lastx=x;
		x=S[x].fa;
	}
	//cout<<"Access over"<<endl;
	return;
}

void Makeroot(int x){
	//cout<<"Makeroot:"<<x<<endl;
	Access(x);Splay(x);Revse(x);//cout<<"Makeroot over"<<endl;
	return;
}

int Findroot(int x){
	Access(x);Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Link(int u,int v){
	//cout<<"Link:"<<u<<" "<<v<<endl;
	if (Findroot(u)==Findroot(v)) return;
	//cout<<"f"<<endl;
	Makeroot(u);S[u].fa=v;return;
}

void Cut(int u,int v){
	//cout<<"Cut:"<<u<<" "<<v<<endl;
	Makeroot(u);Access(v);Splay(v);
	S[v].ch[0]=S[u].fa=0;
	return;
}

void OutpSAM(){
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (T[i].son[j]) cout<<i<<"->"<<T[i].son[j]<<" ["<<(char)('A'+j)<<"]"<<endl;
	for (int i=1;i<=nodecnt;i++) cout<<T[i].fa<<" ";cout<<endl;
	cout<<endl;return;
}

void OutpLCT(){
	for (int i=1;i<=nodecnt;i++) for (int j=1;j<=nodecnt;j++) PushDown(j);
	printf("id fa ls rs cnt lz rev\n");
	for (int i=1;i<=nodecnt;i++)
		printf("%2d%3d%3d%3d%4d%3d%4d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].cnt,S[i].lz,S[i].rev);
	cout<<endl;
	return;
}
	
/*
2
A
QUERY B
ADD BBABBBBAAB

10
AABAA
Q AA
Q A
Q AB
A ACCA
Q AA
Q A
Q B
Q AAC
Q C
Q CA
//*/
