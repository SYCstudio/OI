#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Treap
{
public:
    int key,ran;
    int size;
    Treap * ch[2];
    Treap(int k)
    {
        key=k;
        ran=rand();
        ch[0]=ch[1]=NULL;
        size=1;
    }
    int compare(int k)
    {
        if (k==key)
            return -1;
        return k<key?0:1;
    }
    void maintain()
    {
        size=1;
        if (ch[0]!=NULL)
            size+=ch[0]->size;
        if (ch[1]!=NULL)
            size+=ch[1]->size;
    }
};

const int inf=2147483647;

int n;

void Rotate(Treap* &T,int f);//0代表左旋，1代表右旋
void Insert(Treap* &T,int value);
int Find(Treap * T,int value);
int Find_k(Treap * T,int value);
void print(Treap *T);

int main()
{
    Treap* root=NULL;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        char ch;
        int x;
        cin>>ch>>x;
        if (ch=='I')
        {
            //cout<<"x "<<x<<endl;
            Insert(root,x);
        }
        else
        {
            //cout<<Find(root,x)<<"aa"<<endl;
            cout<<Find_k(root,x)<<endl;
        }
        //cout<<i<<":"<<endl;
        //print(root);
        //cout<<endl;
    }
}

void Rotate(Treap* &T,int f)
{
    Treap* son=T->ch[f^1];//左旋处理的是右子树，而右旋处理的是左子树
    T->ch[f^1]=son->ch[f];
    son->ch[f]=T;
    T->maintain();
    son->maintain();
    T=son;
}

void Insert(Treap* &T,int value)
{
    if (T==NULL)
        T=new Treap(value);
    else
    {
        int f=value<(T->key) ? 0 :1;
        //cout<<value<<' '<<f<<' '<<(T->ch[0]==NULL)<<(T->ch[1]==NULL)<<endl;
        Insert(T->ch[f],value);
        if ((T->ch[f]->ran)>(T->ran))
            Rotate(T,f^1);//如果是右子树则左旋，如果是左子树则右旋
    }
    T->maintain();
}

int Find(Treap * T,int value)
{
    while (T!=NULL)
    {
        //cout<<"Find_In"<<endl;
        int f=T->compare(value);
        if (f==-1)
            return 1;
        T=T->ch[f];
    }
    return 0;
}

int Find_k(Treap * T,int value)
{
    //cout<<"In"<<endl;
    //cout<<T->ch[0]<<' '<<T->ch[1]<<endl;
    //int Ans=T->key;
    //cout<<"Init_Ans:"<<Ans<<endl;
    int Ans=-inf;
    while (T!=NULL)
    {
        //cout<<"Find_k :"<<T->key<<endl;
        //cout<<value<<' '<<T->key<<endl;
        if (T->key<=value)
            Ans=max(Ans,T->key);
        int f=T->compare(value);
        if (f==-1) return value;
        T=T->ch[f];
        //Ans=T->key;
    }
    return Ans;
}

void Delete(Treap* &T,int value)
{
    int f=T->compare(value);
    if (f==-1)
    {
        Treap* &T2=T;//因为后面要修改T指向，所以先用一个T2存下指针
        if (T->ch[0]==NULL)
        {
            T=T->ch[1];
            delete T2;
            T2=NULL;
        }
        else
            if (T->ch[1]==NULL)
        {
            T=T->ch[0];
            delete T2;
            T2=NULL;
        }
        else
        {
            int f2=T->ch[0]->ran > T->ch[1]->ran ? 1:0;
            Rotate(T,f2);
            Delete(T->ch[f2],value);
        }
    }
    else Delete(T->ch[f],value);
    if (T!=NULL)
        T->maintain();
}

void print(Treap *T)
{
    if (T==NULL)
        return;
    cout<<T->key<<'(';
    print(T->ch[0]);
    cout<<',';
    print(T->ch[1]);
    cout<<')';
    return;
}