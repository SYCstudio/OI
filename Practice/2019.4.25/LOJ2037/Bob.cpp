#include "Boblib.h"
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
static const int maxN=1020;
static const int BIT=10;

static vector<int> E[maxN];
static int Mark[maxN],Id[maxN],scnt,BS[BIT+10];

void Bob(int V,int U,int C[],int D[]){
    for (int i=0;i<U;i++) E[C[i]].push_back(D[i]),E[D[i]].push_back(C[i]);
    int mrt=0;for (int i=0;i<V;i++) if (E[i].size()>E[mrt].size()) mrt=i;
    Mark[mrt]=-1;
    for (int i=0,sz=E[mrt].size();i<sz;i++) Mark[E[mrt][i]]=1;
    int id12=0;while (Mark[id12]) ++id12;

    pair<int,int> Seq[BIT+10];
    for (int i=0,sz=E[id12].size();i<sz;i++) Mark[E[id12][i]]=2,Seq[scnt++]=mp(0,E[id12][i]);
    for (int i=0;i<BIT;i++){
	int u=Seq[i].sd;
	for (int j=0,sz=E[u].size();j<sz;j++) if (Mark[E[u][j]]==2) ++Seq[i].ft;
    }
    int bitone=0;
    for (int i=1;i<BIT;i++) if (Seq[i].ft>Seq[bitone].ft) bitone=i;
    bitone=Seq[bitone].sd;
    for (int i=0,u=bitone,sz=E[u].size();i<sz;i++) if (Mark[E[u][i]]==2) Mark[E[u][i]]=3;

    BS[BIT]=-1;
    for (int i=0;i<BIT;i++) if (Mark[Seq[i].sd]==2&&Seq[i].sd!=bitone) BS[BIT-1]=Seq[i].sd;
    for (int i=BIT-1;i>=2;i--){
	int u=BS[i];
	for (int j=0,sz=E[u].size();j<sz;j++){
	    int v=E[u][j];
	    if (Mark[v]==3&&v!=bitone&&v!=BS[i+1]){
		BS[i-1]=v;break;
	    }
	}
    }
    BS[0]=bitone;

    for (int i=0;i<BIT;i++){
	int u=BS[i];
	for (int j=0,sz=E[u].size();j<sz;j++) if (Mark[E[u][j]]==1) Id[E[u][j]]|=(1<<i);
    }

    int mcnt=0;for (int i=0;i<U;i++) if (Mark[C[i]]==1&&Mark[D[i]]==1) ++mcnt;
    InitMap(V-BIT-2,mcnt);
    for (int i=0;i<U;i++) if (Mark[C[i]]==1&&Mark[D[i]]==1) MakeMap(Id[C[i]],Id[D[i]]);
    
    return;
}
