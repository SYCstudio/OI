#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const ld alpha=0.8;
const int inf=2147483647;

class Scapegoat
{
public:
	int size,key,rsize;
	bool del;
};

int n;
int nodecnt,root;
Scapegoat S[maxN];
int top,St[maxN];
int dbcnt=0,DBin[maxN];

void Insert(int now,int key);
void MainTain();
int Kth(int now,int k);
int Rebuild(int now);

int main(){
	Init();int n,mn,plus=0,sum=0;scanf("%d%d",&n,&mn);
	while (n--){
		char ipt;int key;scanf(" %c%d",&ipt,&key);
		if (ipt=='I'){
			if (key<mn) continue;key-=plus;
			Insert(root,key);MainTain();
		}
	}
}
