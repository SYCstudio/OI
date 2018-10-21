#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxsize=20000;
const int inf=2147483647;

int Tot[maxsize]={6,2,5,5,4,5,6,3,7,6};

int main()
{
    int n;
    for (int i=10;i<=10000;i++)
        Tot[i]=Tot[i/10]+Tot[i%10];
    cin>>n;
    n=n-4;
    int Ans=0;
    for (int i=0;i<=999;i++)
        for (int j=0;j<=999;j++)
        {
            //cout<<i<<" "<<j<<endl;
            if (Tot[i]+Tot[j]+Tot[i+j]==n)
            {
                //cout<<i<<' '<<j<<endl;
                Ans++;
            }
        }
    cout<<Ans<<endl;
    return 0;
}
