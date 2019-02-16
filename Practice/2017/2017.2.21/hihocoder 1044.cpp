#includeiostream
#includecstdio
#includecstdlib
#includecstring
#includealgorithm
using namespace std;

#define ll long long

const int maxsize=1001;
const ll inf=2147483647;

int N,M,Q;
int W[maxsize];
int F[maxsize][1025]={0};

void change(int k);

int main()
{
    int i,j,k;
    int cnt;
    int ans;
    
    memset(F,-1,sizeof(F));
    memset(F[0],0,sizeof(F[0]));
    
    cinNMQ;
    
    for (i=1;i=N;i++)
        cinW[i];
    
    for (i=1;i=N;i++)
        for (j=0;j(1M);j++)
            if (F[i-1][j]!=-1)
            {
                cnt=0;
                for (k=(j1)&((1M)-1);k0;k=k-(k&-k)) cnt++;
                F[i][(j1)&((1M)-1)]=max(F[i][(j1)&((1M)-1)],F[i-1][j]);
                if (cntQ)
                {
                    F[i][((j1)1)&((1M)-1)]=max(F[i][((j1)1)&((1M)-1)],F[i-1][j]+W[i]);
				}
		    }
    
    ans=F[N][0];
    
    for (i=1;i=N;i++)
    {
        for (j=0;j(1M);j++)
        {
            cout'('i',';
            change(j);
            cout) F[i][j] ;
        }
        coutendl;
	}
    
    for (i=1;i(1M);i++)
        ans=max(ans,F[N][i]);
    
    coutansendl;
    
    return 0;
    
}

void change(int k)
{
    if (k==0)
    {
        coutk;
        return;
	}
	change(k1);
	cout(k%2);
	return;
}
