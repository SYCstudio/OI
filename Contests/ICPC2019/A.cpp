#include<bits/stdc++.h>
using namespace std;

const int maxN=505000;

class Data{
public:
    int p,h,id;
};

int n;
set<pair<int,int> > Sa,Sb;
Data A[maxN],B[maxN];
pair<int,int> Ans[maxN];

bool pcmp(Data A,Data B);
void EXIT();
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&A[i].p),A[i].id=i;
    for (int i=1;i<=n;i++) scanf("%d",&A[i].h);
    for (int i=1;i<=n;i++) scanf("%d",&B[i].p),B[i].id=i;
    for (int i=1;i<=n;i++) scanf("%d",&B[i].h);
    sort(&A[1],&A[n+1],pcmp);sort(&B[1],&B[n+1],pcmp);
    //for (int i=1;i<=n;i++) cout<<"("<<A[i].p<<" "<<A[i].h<<") ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<"("<<B[i].p<<" "<<B[i].h<<") ";cout<<endl;
    for (int i=1,p1=0,p2=0;i<=n;){
	set<pair<int,int> >::iterator it,p;
	while (p1+1<=n&&A[p1+1].p==A[i].p) ++p1,Sa.insert(make_pair(A[p1].h,A[p1].id));
	while (p2+1<=n&&B[p2+1].p==B[i].p) ++p2,Sb.insert(make_pair(B[p2].h,B[p2].id));
	//cout<<p1<<" "<<p2<<endl;
	if (p1<=p2){
	    for (p=Sa.begin();p!=Sa.end();p++){
		it=Sb.upper_bound(make_pair((*p).first,0));
		if (it==Sb.begin()) EXIT();
		--it;
		Ans[i++]=make_pair((*p).second,(*it).second);
		Sb.erase(it);
	    }
	    Sa.clear();
	}
	else{
	    for (p=Sb.begin();p!=Sb.end();p++){
		it=Sa.upper_bound(make_pair((*p).first,n+1));
		if (it==Sa.end()) EXIT();
		Ans[i++]=make_pair((*it).second,(*p).second);
		Sa.erase(it);
	    }
	    Sb.clear();
	}
    }
    for (int i=1;i<=n;i++) printf("%d ",Ans[i].first);printf("\n");
    for (int i=1;i<=n;i++) printf("%d ",Ans[i].second);printf("\n");
    return 0;
}
bool pcmp(Data A,Data B){
    return A.p<B.p;
}
void EXIT(){
    puts("impossible");exit(0);
}
