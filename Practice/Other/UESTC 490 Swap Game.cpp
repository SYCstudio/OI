#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=400020;
const int inf=2147483647;

ll n;
ll A[maxN];
char str[maxN];

int main()
{
    int TT;
    cin>>TT;
    for (int ti=1;ti<=TT;ti++)
    {
        scanf("%s",str);
        n=strlen(str);
        for (int i=0;i<n;i++)
            if (str[i]=='R')
                A[i+1]=1;
            else
                A[i+1]=0;
        ll invcnt=0;//�������
        ll tmp1=0;//���R�ĸ������ұ�B�ĸ���������������ԣ�
        ll tmp2=0;
        ll mid=n>>1;//�м��λ�ã�ͬʱҲ��Ԫ�ظ�����һ��
        //����ڳ�ʼmid��ߵ������ƺ��ұߵ������Ƶĳ�ֵtmp
        for (int i=1;i<=mid;i++)
            if (A[i]==1)
                tmp1++;
            else
                invcnt+=tmp1;
        for (int i=mid+1;i<=n;i++)
            if (A[i]==0)
                tmp2++;
            else
                invcnt+=tmp2;
        ll Ans=invcnt;//Ans�ĳ�ֵ����������������������������Ϊȫ�����м俿Ҳ��һ�ַ���
        //����涨RΪ1��BΪ1
        for (int i=1;i<=n;i++)//�൱�������һ���һ������
        {
            int i2=(i+mid-1)%n+1;//i����ԭ�������ߵ�һ����Ҫ�����ұߣ�i2����ԭ�ұ�����ߵ�һ����Ҫ�������
            if (A[i]==1)
            {
                if (A[i2]==0)//������invcnt���Ϸŵ�����ȥ���²�������������������Ҫ�ж�һ���ұ߻������ȥ���Ǹ����Ƿ�����һ������ԣ����ǣ���Ҫ��ȥһ
                {
                    invcnt+=tmp2-1;
                }
                else
                    invcnt+=tmp2;
                //�ټ�ȥ��������ߺ���ʧ���������
                invcnt-=mid-tmp1;//tmp1����ߵ�R������ômid-tmp1������ߵ�B��
            }
            if (A[i2]==0)
            {
                if (A[i]==1)//������һ��������Ҫinvcnt���ϰ�һ��B�ŵ�ǰ��ȥ���������γɵ����������
                            //��ʱ��Ҫ�ж�����Ƴ�ȥ���Ƿ���R��
                {
                    invcnt+=tmp1-1;
                }
                else
                    invcnt+=tmp1;
                //�ټ�ȥ�ұ���ʧ���������
                invcnt-=(n-mid-tmp2);//ע��������n-mid����Ϊn����ż���������������ʱ�����߲�һ��
            }
            if (A[i]==1)
                tmp1--;
            else
                tmp2++;
            if (A[i2]==0)
                tmp2--;
            else
                tmp1++;
            Ans=min(Ans,invcnt);
        }
        //printf("Case #%d: %d\n",ti,Ans);
        cout<<Ans<<endl;
    }
    return 0;
}
