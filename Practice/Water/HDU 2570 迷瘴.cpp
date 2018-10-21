#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxsize=1000;
const int inf=2147483647;

double P[maxsize];

int main()
{
    int n,W,V;
    int C;
    cin>>C;
    while (C--)
    {
        int i;
        cin>>n>>V>>W;
        for (i=0;i<n;i++)
            cin>>P[i];
        sort(P,P+n);
        double sum=0.0;
        for (i=0;i<n;i++)
        {
            if (i*sum+P[i]*0.01>(i+1)*W*0.01)
                break;
            sum=(i*sum+P[i]*0.01)/(double)(i+1);
        }
        printf("%d %.2f\n",i*V,sum);
    }
    return 0;
}
