#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int maxsize=200;
const int inf=2147483647;
 
long long A,B,n;
long long F[maxsize];
long long Num[maxsize];
bool vis[maxsize]={0};
 
int main()
{
    //freopen("sequenceb.in","r",stdin);
    //freopen("sequenceb.out","w",stdout);
 
    memset(F,-1,sizeof(F));
    memset(Num,-1,sizeof(Num));
 
    cin>>A>>B>>n;
 
    if ((n==1)||(n==2))
    {
        cout<<1<<endl;
        //fclose(stdin);
        //fclose(stdout);
        return 0;
    }
 
    /*F[1]=F[2]=1;
    for (int i=3;i<=n;i++)
        F[i]=(F[i-1]*A+F[i-2]*B)%7;
    cout<<F[n]<<endl;*/
 
    int a=1,b=1;
    F[1]=F[2]=1;
    vis[11]=1;
    Num[11]=1;
    int i=3;
 
    do
    {
        F[i]=(A*F[i-1]+B*F[i-2])%7;
        a=b;
        b=F[i];
        if (i==n)
        {
            cout<<F[i]<<endl;
            fclose(stdin);
            fclose(stdout);
            return 0;
        }
        if (vis[a*10+b]==1)
        {
            break;
        }
        vis[a*10+b]=1;
        Num[a*10+b]=i-1;
        i++;
        //cout<<a*10+b<<endl;
    }
    while (1);
 
    /*for (int j=0;j<=100;j++)
        if (Num[j]!=-1)
        {
            cout<<j<<' '<<Num[j]<<endl;
        }
    cout<<endl;
    cout<<"iab"<<i<<' '<<a<<' '<<b<<endl;*/
    i=i-2;
 
    n=n-Num[a*10+b]+1;
    //cout<<Num[a*10+b]<<' '<<n<<endl;
    n=n%(i-Num[a*10+b]+1);
    if (n==0)
        n=i;
    //cout<<n<<endl;
 
    cout<<F[n]<<endl;
 
    fclose(stdin);
    fclose(stdout);
    return 0;
}
