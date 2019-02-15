#include"xylophone.h"
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
const int maxN=5010;
void find_permutation(int n,int *ans){
	ans[1]=1;if (n==1) return;
	int a=query(1,2),mn=1;ans[2]=ans[1]+a;mn=min(mn,ans[2]);
	for (int i=3;i<=n;i++){
		int r1=max(ans[i-2],ans[i-1])-min(ans[i-2],ans[i-1]),r2=query(i-1,i),r3=query(i-2,i);
		if (ans[i-2]<ans[i-1]){
			if (r1+r2==r3) ans[i]=ans[i-1]+r2;
			else ans[i]=ans[i-1]-r2;
		}
		else{
			if (r1+r2==r3) ans[i]=ans[i-1]-r2;
			else ans[i]=ans[i-1]+r2;
		}
		mn=min(mn,ans[i]);
	}
	int p1,p2;
	for (int i=1;i<=n;i++){
		ans[i]=ans[i]+1-mn;
		if (ans[i]==1) p1=i;
		if (ans[i]==n) p2=i;
	}
	if (p1>p2) for (int i=1;i<=n;i++) ans[i]=n-ans[i]+1;
	return;
}
