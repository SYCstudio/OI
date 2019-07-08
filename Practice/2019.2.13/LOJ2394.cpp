#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "Broken_device_lib.h"
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=150;
int vis[maxN],D[maxN];
void Anna(int n,long long X,int K,int P[])
{
	mem(vis,0);
	for (int i=0; i<K; i++) vis[P[i]]=1;
	for (int i=0; i<60; i++) D[i]=(X>>i)&1;
	//for (int i=0;i<60;i++) cout<<D[i]<<" ";cout<<endl;
	int j=0;
	for (int i=0; i<60; j+=3) {
		int c=vis[j]+vis[j+1]+vis[j+2];
		if (c==0) {
			if (!D[i]&&!D[i+1]) Set(j,0),Set(j+1,1),Set(j+2,0),i+=2;
			else if (!D[i]&&D[i+1]) Set(j,0),Set(j+1,1),Set(j+2,1),i+=2;
			else if (D[i]&&!D[i+1]) Set(j,1),Set(j+1,0),Set(j+2,1),i+=2;
			else Set(j,1),Set(j+1,1),Set(j+2,1),i+=2;
		} else if (c==1) {
			if (vis[j]) {
				if (D[i]) Set(j,0),Set(j+1,0),Set(j+2,1),i++;
				else if (!D[i]&&!D[i+1]) Set(j,0),Set(j+1,1),Set(j+2,0),i+=2;
				else Set(j,0),Set(j+1,1),Set(j+2,1),i+=2;
			} else if (vis[j+1]) {
				if (D[i]&&!D[i+1]) Set(j,1),Set(j+1,0),Set(j+2,1),i+=2;
				else if (!D[i]) Set(j,1),Set(j+1,0),Set(j+2,0),i++;
				else Set(j,0),Set(j+1,0),Set(j+2,1),i++;
			} else {
				if (!D[i]&&!D[i+1]) Set(j,0),Set(j+1,1),Set(j+2,0),i+=2;
				else if (!D[i]) Set(j,1),Set(j+1,0),Set(j+2,0),i++;
				else Set(j,1),Set(j+1,1),Set(j+2,0),i++;
			}
		} else {
			Set(j,0);
			Set(j+1,0);
			Set(j+2,0);
		}
	}
	while (j<n) Set(j++,0);
	return;
}
long long Bruno(int n,int S[])
{
	long long Ans=0;
	mem(D,0);
	for (int i=0,j=0; i<60&&j<n; j+=3) {
		int key=(S[j]<<2)|(S[j+1]<<1)|(S[j+2]);
		//cout<<key<<" ";
		if (key==1) D[i]=1,++i;
		if (key==2) i+=2;
		if (key==3) D[i+1]=1,i+=2;
		if (key==4) ++i;
		if (key==5) D[i]=1,i+=2;
		if (key==6) D[i]=1,++i;
		if (key==7) D[i]=D[i+1]=1,i+=2;
		//cout<<i<<endl;
	}//cout<<endl;
	for (int i=0; i<60; i++) if (D[i]) Ans|=1ll<<i;
	//for (int i=0;i<60;i++) cout<<D[i]<<" ";cout<<endl;
	return Ans;
}