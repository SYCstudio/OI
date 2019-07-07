#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=1010000;

int n,m;
int A[maxN],B[maxN],Nxt[maxN],Rka[maxN];
int BIT[maxN];
int num,Num[maxN];
vector<int> Ans;

void Plus(int p,int key,int up);
int Sum(int p);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
	int pos;scanf("%d",&pos);A[pos]=i;
    }
    for (int i=1;i<=m;i++) scanf("%d",&B[i]),Num[i]=B[i];
    sort(&Num[1],&Num[m+1]);num=unique(&Num[1],&Num[m+1])-Num-1;

    memset(BIT,0,sizeof(BIT));
    for (int i=1;i<=n;i++) Plus(A[i],1,n),Rka[i]=Sum(A[i]);
    
    memset(BIT,0,sizeof(BIT));
    Nxt[0]=Nxt[1]=0;
    for (int i=2,j=0,lst=2;i<=n;i++){
	while (j&&Sum(A[i])+1!=Rka[j+1]){
	    int nj=Nxt[j];
	    while (lst<i-nj) Plus(A[lst],-1,n),++lst;
	    j=nj;
	}
	if (Sum(A[i])+1==Rka[j+1]) ++j;
	Nxt[i]=j;Plus(A[i],1,n);
    }

    //for (int i=1;i<=n;i++) cout<<Nxt[i]<<" ";cout<<endl;
    for (int i=1;i<=m;i++) B[i]=lower_bound(&Num[1],&Num[num+1],B[i])-Num;
    //for (int i=1;i<=m;i++) cout<<B[i]<<" ";cout<<endl;

    memset(BIT,0,sizeof(BIT));
    
    for (int i=1,j=0,lst=1;i<=m;i++){
	while (j&&Sum(B[i])+1!=Rka[j+1]){
	    int nj=Nxt[j];
	    while (lst<i-nj) Plus(B[lst++],-1,num);
	    j=nj;
	}
	//cout<<"check:"<<Sum(B[i])<<"+1 "<<Rka[j+1]<<" "<<j<<endl;
	if (Sum(B[i])+1==Rka[j+1]) ++j;
	//cout<<i<<" "<<j<<" "<<lst<<endl;
	if (j==n){
	    Ans.pb(i-n+1);int nj=Nxt[j];
	    while (lst<i-nj+1) Plus(B[lst],-1,num),++lst;
	    j=nj;
	}
	Plus(B[i],1,num);
    }
    printf("%d\n",(int)Ans.size());
    for (int i=0;i<Ans.size();i++) printf("%d ",Ans[i]);puts("");
    return 0;
}
void Plus(int p,int key,int up){
    while (p<=up){
	BIT[p]+=key;p+=(p)&(-p);
    }
    return;
}
int Sum(int p){
    int ret=0;
    while (p){
	ret+=BIT[p];p-=(p)&(-p);
    }
    return ret;
}
