#include<bits/stdc++.h>
using namespace std;

int n;

int Query(int p);
int main(){
    scanf("%d",&n);
    if (n%4){
	puts("! -1");return 0;
    }
    int l=1,r=n/2,lkey=Query(l);
    while (l+1<r){
	int mid=(l+r)>>1;
	//cout<<"["<<l<<" "<<r<<"]"<<mid<<endl;
	int qk=Query(mid);
	if (1ll*qk*lkey>0) l=mid,lkey=qk;
	else r=mid-1;
    }
    Query(l);Query(r);
    return 0;
}
int Query(int p){
    printf("? %d\n? %d\n",p,p+n/2);fflush(stdout);
    int a,b;scanf("%d %d",&a,&b);
    if (a==b){
	printf("! %d\n",p);exit(0);
    }
    return b-a;
}
