#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;

const int maxN=300100*2;
const int inf=2147483647;

class Question
{
public:
	int pos,tim,id;
};

class Shop
{
public:
	int pos,tim,opt;
};

class ShopInput
{
public:
	int pos,kind,l,r;
};

class Heap
{
private
	priority_queue<int> Q,Del;
public:
	void MainTain(){
		while ((!Q.empty())&&(!Del.empty())&&(Q.top()==Del.top())) Q.pop(),Del.pop();
		return;
	}
	void push(int key){
		MainTain();
		Q.push(key);return;
	}
	void delete(int key){
		MainTain();Del.push(key);
		MainTain();return;
	}
	int top(){
		MainTain();
		if (Q.empty()) return inf;
		else return Q.top();
	}
};

int n,K,Q;
Question Qn[maxN];
Shop Sn[maxN];
ShopInput In[maxN];
int poscnt,P[maxN];
Heap H[maxN];

int main(){
	scanf("%d%d%d",&n,&K,&Q);
	for (int i=1;i<=n;i++) scanf("%d%d%d%d",&In[i].pos,&In[i].kind,&In[i].l,&In[i].r),P[++poscnt]=In[i].pos;
	for (int i=1;i<=Q;i++) scanf("%d%d",&Qn[i].pos,&Qn[i].tim),Qn[i].id=i;
	
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) In[i].pos=lower_bound(&Num[1],&Num[numcnt+1],In[i].pos)-Num;

	
