#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int maxN=100001;
const int inf=2147483647;
 
int n;
int A[maxN];
int Solve[40]={0};
 
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>A[i];
    int Ans=0;
    for (int i=1;i<=n;i++)
    {
        int now_ans=1;
        for (int j=0,sum=1;j<=40;j++,sum=sum<<1)//取出最大值
            if (sum&A[i])
                now_ans=max(now_ans,Solve[j]+1);
        for (int j=0,sum=1;j<=40;j++,sum=sum<<1)//把所有在x上这一位是1的都更新成当前最大值+1
            if (sum&A[i])
                Solve[j]=max(Solve[j],now_ans);
        Ans=max(now_ans,Ans);//更新最后要输出的最大值
    }
    cout<<Ans<<endl;
    return 0;
}
