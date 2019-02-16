#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=180;
const int inf=2147483647;

int P,Q,R;
char Input[maxN];
int Bp[maxN][maxN][maxN],Bc[maxN][maxN][maxN];
int Len[maxN][maxN][maxN],Lf[maxN],Rf[maxN],St[maxN];

int G(int i,int j1,int k1,int j2,int k2);
int Calc(int X,int Y,int Z);

int main(){
	scanf("%d%d%d",&P,&Q,&R);swap(P,Q);
	for (int i=1;i<=P;i++)
		for (int j=1;j<=Q;j++){
			scanf("%s",Input+1);
			for (int k=1;k<=R;k++) Bp[i][j][k]=(Input[k]=='N');
		}

	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) for (int k=1;k<=R;k++) Bc[i][j][k]=Bp[i][j][k];
	int Ans=Calc(P,Q,R);
	mem(Bc,0);
	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) for (int k=1;k<=R;k++) Bc[j][i][k]=Bp[i][j][k];
	Ans=max(Ans,Calc(Q,P,R));
	mem(Bc,0);
	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) for (int k=1;k<=R;k++) Bc[k][i][j]=Bp[i][j][k];
	Ans=max(Ans,Calc(R,P,Q));
	printf("%lld\n",4ll*Ans);
	return 0;
}

int G(int i,int j1,int k1,int j2,int k2){
	return Bc[i][j2][k2]-Bc[i][j2][k1-1]-Bc[i][j1-1][k2]+Bc[i][j1-1][k1-1];
}

int Calc(int X,int Y,int Z){
	/*
	cout<<X<<" "<<Y<<" "<<Z<<endl<<"Mat:"<<endl;
	for (int i=1;i<=X;i++){
		for (int j=1;j<=Y;j++){
			for (int k=1;k<=Z;k++) cout<<Bc[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	//*/
	int ret=0;mem(Len,0);
	for (int i=1;i<=X;i++)
		for (int j=1;j<=Y;j++)
			for (int k=1;k<=Z;k++)
				Bc[i][j][k]=Bc[i][j][k]+Bc[i][j-1][k]+Bc[i][j][k-1]-Bc[i][j-1][k-1];
	/*
	cout<<"After sum:"<<endl;
	for (int i=1;i<=X;i++){
		for (int j=1;j<=Y;j++){
			for (int k=1;k<=Z;k++) cout<<Bc[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	//*/
	for (int i=1;i<=X;i++)
		for (int j=1;j<=Y;j++){
			int p=1;
			for (int k=1;k<=Z;k++){
				p=max(0,p-1);
				while (G(i,j,k,j+p,k+p)==(p+1)*(p+1)) ++p;
				Len[i][j][k]=p;
			}
		}
	/*
	cout<<"Len:"<<endl;
	for (int i=1;i<=X;i++){
		for (int j=1;j<=Y;j++){
			for (int k=1;k<=Z;k++) cout<<Len[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	//*/
	for (int j=1;j<=Y;j++)
		for (int k=1;k<=Z;k++){
			mem(Lf,0);mem(Rf,0);int top=0;St[0]=0;
			for (int i=1;i<=X;i++){
				while ((top)&&(Len[St[top]][j][k]>=Len[i][j][k])) top--;
				Lf[i]=St[top]+1;
				St[++top]=i;
			}
			top=0;St[0]=X+1;
			for (int i=X;i>=1;i--){
				while ((top)&&(Len[St[top]][j][k]>=Len[i][j][k])) top--;
				Rf[i]=St[top]-1;
				St[++top]=i;
			}
			for (int i=1;i<=X;i++) ret=max(ret,Len[i][j][k]*(Rf[i]-Lf[i]+1));
		}
	//cout<<"ret:"<<ret<<endl;
	return ret;
}
