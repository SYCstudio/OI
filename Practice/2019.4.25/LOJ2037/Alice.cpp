#include "Alicelib.h"
#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
static const int maxN=1024;
static const int BIT=10;
static vector<pair<int,int> > E;

void Alice(int N,int M,int A[],int B[]){
    for (int i=0;i<M;i++) E.pb(mp(A[i],B[i]));
    for (int i=0;i<N;i++){
	E.pb(mp(i,N+BIT));
	for (int j=0;j<BIT;j++)
	    if (i&(1<<j)) E.pb(mp(i,N+j));
    }
    for (int i=1;i<BIT;i++) E.pb(mp(N+i-1,N+i));
    for (int i=2;i+1<BIT;i++) E.pb(mp(N,N+i));
    for (int i=0;i<BIT;i++) E.pb(mp(N+i,N+BIT)),E.pb(mp(N+i,N+BIT+1));

    InitG(N+BIT+2,(int)(E.size()));
    for (int i=0,sz=E.size();i<sz;i++) MakeG(i,E[i].ft,E[i].sd);
    return;
}

