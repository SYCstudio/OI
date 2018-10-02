#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iomanip>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(Arr,size,x) (lower_bound(&Arr[1],&Arr[size+1],x)-Arr)

const int maxN=2010;
const int maxNode=maxN*20;
const int maxM=maxNode*4;
const int inf=2147483647;

class Point
{
public:
	int x,y,id;
};

int n,Sx,Sy,Tx,Ty,S,T;
int A[maxN],B[maxN],C[maxN],D[maxN];
int nx,Nx[maxNode],ny,Ny[maxNode];
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM],W[maxM];
int stu[maxN][maxN],Id[maxN][maxN],pcnt;
Point P[maxNode];
bool Exi[maxN],inq[maxNode];
int Dist[maxNode];
queue<int> Q;

void Go(int x,int y,int dx,int dy);
bool cmpx(Point P1,Point P2);
bool cmpy(Point P1,Point P2);
void Add_Edge(int u,int v,int w);
void Spfa();

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		nx=ny=edgecnt=0;mem(Nx,0);mem(Ny,0);mem(stu,0);mem(Id,0);mem(Head,-1);mem(Exi,0);
		scanf("%d%d%d%d",&Sx,&Sy,&Tx,&Ty);
		Nx[++nx]=Sx;Nx[++nx]=Tx;Ny[++ny]=Sy,Ny[++ny]=Ty;
		scanf("%d",&n);
		bool flag=1;
		for (int i=1;i<=n;i++){
			scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);Exi[i]=1;
			if (A[i]>C[i]) swap(A[i],C[i]);
			if (B[i]>D[i]) swap(B[i],D[i]);
			if ((A[i]<Sx)&&(C[i]>Sx)&&(B[i]<Sy)&&(D[i]>Sy)) flag=0;
			if ((A[i]<Tx)&&(C[i]>Tx)&&(B[i]<Ty)&&(D[i]>Ty)) flag=0;
			Nx[++nx]=A[i];Nx[++nx]=C[i];Ny[++ny]=B[i];Ny[++ny]=D[i];
		}
		if (flag==0){
			printf("No Path\n");continue;
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (i!=j)
					if ((A[j]<=A[i])&&(B[j]<=B[i])&&(C[j]>=C[i])&&(D[j]>=D[i])){
						Exi[i]=0;break;
					}
		sort(&Nx[1],&Nx[nx+1]);nx=unique(&Nx[1],&Nx[nx+1])-Nx-1;
		sort(&Ny[1],&Ny[ny+1]);ny=unique(&Ny[1],&Ny[ny+1])-Ny-1;
		
		cout<<"Nx:";for (int i=1;i<=nx;i++) cout<<Nx[i]<<" ";cout<<endl;
		cout<<"Ny:";for (int i=1;i<=ny;i++) cout<<Ny[i]<<" ";cout<<endl;
		
		Sx=Find(Nx,nx,Sx);Sy=Find(Ny,ny,Sy);Tx=Find(Nx,nx,Tx);Ty=Find(Ny,ny,Ty);
		for (int i=1;i<=n;i++) A[i]=Find(Nx,nx,A[i]),B[i]=Find(Ny,ny,B[i]),C[i]=Find(Nx,nx,C[i]),D[i]=Find(Ny,ny,D[i]);

		cout<<Sx<<" "<<Sy<<" "<<Tx<<" "<<Ty<<endl;
		for (int i=1;i<=n;i++) cout<<"("<<A[i]<<","<<B[i]<<") ("<<C[i]<<","<<D[i]<<")"<<endl;
		
		for (int i=1;i<=n;i++){
			if (Exi[i]==0) continue;
			for (int j=A[i];j<=C[i];j++) stu[j][B[i]]=1,stu[j][D[i]]=2;
			for (int j=B[i];j<=D[i];j++) stu[A[i]][j]=1,stu[C[i]][j]=2;
			stu[A[i]][B[i]]=stu[A[i]][D[i]]=stu[C[i]][B[i]]=stu[C[i]][D[i]]=-1;
		}
		stu[Sx][Sy]=stu[Tx][Ty]=-1;
		for (int i=1;i<=nx;i++){
			for (int j=1;j<=ny;j++)
				cout<<setw(4)<<stu[i][j];
			cout<<endl;
		}
		for (int i=1;i<=n;i++){
			if (Exi[i]==0) continue;
			Go(A[i],B[i],-1,0);Go(A[i],B[i],0,-1);Go(A[i],D[i],-1,0);Go(A[i],D[i],0,1);
			Go(C[i],B[i],1,0);Go(C[i],B[i],0,-1);Go(C[i],D[i],1,0);Go(C[i],D[i],0,1);
			Id[A[i]][B[i]]=Id[A[i]][D[i]]=Id[C[i]][B[i]]=Id[C[i]][D[i]]=1;
		}
		Id[Sx][Sy]=Id[Tx][Ty]=1;

		cout<<endl;
		for (int i=1;i<=nx;i++){
			for (int j=1;j<=ny;j++)
				cout<<setw(4)<<Id[i][j];
			cout<<endl;
		}
		
		for (int i=1;i<=nx;i++)
			for (int j=1;j<=ny;j++){
				if (Id[i][j]) P[++pcnt]=((Point){i,j,pcnt});
				if ((i==Sx)&&(j==Sy)) S=pcnt;
				if ((i==Tx)&&(j==Ty)) T=pcnt;
			}
		sort(&P[1],&P[pcnt+1],cmpx);
		for (int i=1,j;i<=pcnt;i=j){
			j=i+1;
			while (P[j].x==P[i].x){
				if ((stu[P[j-1].x][P[j-1].y]==-1)||(stu[P[j].x][P[j].y]==-1)||((stu[P[j-1].x][P[j-1].y]==2)&&(stu[P[j].x][P[j].y]==1)))
					Add_Edge(P[j-1].id,P[j].id,abs(Ny[P[j].y]-Ny[P[j-1].y]));
				j++;
			}
		}
		sort(&P[1],&P[pcnt+1],cmpy);
		for (int i=1,j;i<=pcnt;i=j){
			j=i+1;
			while (P[j].y==P[i].y){
				if ((stu[P[j-1].x][P[j-1].y]==-1)||(stu[P[j].x][P[j].y]==-1)||((stu[P[j-1].x][P[j-1].y]==2)&&(stu[P[j].x][P[j].y]==1)))
					Add_Edge(P[j-1].id,P[j].id,abs(Nx[P[j].x]-Nx[P[j-1].x]));
				j++;
			}
		}
		Spfa();
		if (Dist[T]==inf) printf("No Path\n");
		else printf("%d\n",Dist[T]);
	}
	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

void Go(int x,int y,int dx,int dy){
	x+=dx;y+=dy;
	while (stu[x][y]==0){
		if ((x<1)||(y<1)||(x>nx)||(y>ny)) return;
		x+=dx;y+=dy;
	}
	Id[x][y]=1;return;
}

bool cmpx(Point P1,Point P2){
	if (P1.x!=P2.x) return P1.x<P2.x;
	return P1.y<P2.y;
}

bool cmpy(Point P1,Point P2){
	if (P1.y!=P2.y) return P1.y<P2.y;
	return P1.x<P2.x;
}

void Spfa(){
	for (int i=1;i<=pcnt;i++) Dist[i]=inf;
	Dist[S]=0;inq[S]=1;Q.push(S);
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]>Dist[u]+W[i]){
				Dist[V[i]]=Dist[u]+W[i];
				if (inq[V[i]]==0){
					Q.push(V[i]);inq[V[i]]=1;
				}
			}
		inq[u]=0;
	}
	return;
}
