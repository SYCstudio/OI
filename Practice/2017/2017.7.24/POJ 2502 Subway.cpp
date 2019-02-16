#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
#include<cmath>
using namespace std;

const int maxN=300;
const int maxM=maxN*maxN;
const double v1=10000.0/60.0;
const double v2=40000.0/60.0;
const int inf=2147483647;

class Pos
{
public:
	int x,y;
};

int n,m;
class Graph
{
private:
	int cnt;
	int Head[maxN];
	int Next[maxM];
	int V[maxM];
	double W[maxM];
	bool instack[maxN];
	stack<int> S;
public:
	double Dist[maxN];
	void init()
	{
		cnt=0;
		memset(Head,-1,sizeof(Head));
		memset(Next,-1,sizeof(Next));
	}
	void Add_Edge(int u,int v,double w)
	{
		cnt++;
		Next[cnt]=Head[u];
		V[cnt]=v;
		W[cnt]=w;
		Head[u]=cnt;
	}
	void spfa(int s)
	{
		memset(Dist,127,sizeof(Dist));
		memset(instack,0,sizeof(instack));
		Dist[s]=0;
		instack[s]=1;
		S.push(s);
		do
		{
			int u=S.top();
			S.pop();
			instack[u]=0;
			for (int i=Head[u];i!=-1;i=Next[i])
			{
				if (Dist[V[i]]>Dist[u]+W[i])
				{
					Dist[V[i]]=Dist[u]+W[i];
					if (instack[V[i]]==0)
					{
						instack[V[i]]=1;
						S.push(V[i]);
					}
				}
			}
		}
		while (!S.empty());
	}
	void OutEdge()
	{
		for (int i=1;i<=n;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
			{
				cout<<i<<"->"<<V[j]<<' '<<W[j]<<endl;
			}
			cout<<endl;
		}
	}
};

Pos P[maxN];
Graph G;

int read();
inline double Dist(Pos A,Pos B);
istream &operator >> (istream &is,Pos &p)
{
	is>>p.x>>p.y;
	return is;
}

int main()
{
	cin>>P[1]>>P[2];
	G.init();
	n=2;
	while (cin>>P[n+1])
	{
		n++;
		int now=n;
		Pos input;
		for (int i=1;i<=n;i++)
		{
			double dist=Dist(P[n],P[i])/v1;
			G.Add_Edge(n,i,dist);
			G.Add_Edge(i,n,dist);
		}
		while (cin>>input)
		{
			if (input.x==-1)
				break;
			n++;
			P[n]=input;
			double dist=Dist(P[n],P[n-1])/v2;
			G.Add_Edge(n,n-1,dist);
			G.Add_Edge(n-1,n,dist);
			for (int i=1;i<=n;i++)
			{
				//cout<<"Link:"<<i<<' '<<n<<endl;
				double dist2=Dist(P[n],P[i])/v1;
				G.Add_Edge(n,i,dist2);
				G.Add_Edge(i,n,dist2);
			}
		}
	}
	//G.OutEdge();
	G.spfa(1);
	printf("%.0f\n",G.Dist[2]);
	return 0;
}

int read()
{
	int x=0;
	int k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-'))
	    ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}

inline double Dist(Pos A,Pos B)
{
	return sqrt((double)((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)));
}
