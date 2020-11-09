//给定1个1000行×20列的0-1矩阵，对于该矩阵的任意1列，其中值为1的元素的数量不超过10%。
//设有两个非空集合A和B，每个集合由矩阵的若干列组成。集合A和B互斥是指对于矩阵的任意一行，同时满足下列2个条件：
//1）若A中有一个或多个元素在这一行上的值是1，则B中的元素在这一行全部是0；
//2）若B中有一个或多个元素在这一行上的值是1，则A中的元素在这一行全部是0。
//请你设计一个算法，找出一对互斥集合A和B，使得A和B包含的列的总数最大。
#include<iostream>
//#include<set>
#include<queue>
//#include<cstdlib>
//#include<ctime>
//#include<cstdio>
//#include<fstream>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
using namespace std;
 
//const int NumOfL = 1000;   //列的数目
//const int NumOfHang = 20;   //行的数目
//const int n = 1000;          //1的数量
 
struct node
{
    int level;          //搜索的层数
    vector<int> A;   //集合A中的元素
    vector<int> B;
    int Res = 0;    //目前的解
    //node(){};
};
 
struct cmp
{
    bool operator()(node &n1,node &n2){
        return n1.Res < n2.Res;
    }
};

void mute(int k,vector<vector<int>> &martix,vector<vector<int>> &mutex){
    for(int i=0;i<20;i++){
        if(i==k)continue;int j;
        for(j=0;j<1000;j++){
            if(martix[j][k]==1&&martix[j][i]==1)break;//说明i,k两列互斥
        }
        if(j>=1000){
            mutex[k].push_back(i);
        }
    }
}
vector<int> vectors_intersection(vector<int> v1,vector<int> v2){
    vector<int > v;
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));
    return v;
}

node adjust(int k,node temp,int &bestres,vector<vector<int>> &mutex){
    node n=temp;
    n.A.push_back(k);
    if(n.A.size()==1)n.B=mutex[k];
    else {
        //vector<int> B;
        n.B = vectors_intersection(n.B,mutex[k]);
        //对n.B和mutex[k]求交集,赋给n.B
    }

    if(n.B.size()==0||n.A.size()+n.B.size()+20-n.level<bestres){
        n.Res=0;
    }
    else {
        n.Res=n.A.size()+n.B.size();
    }
    return n;
}


int main(){
    int n;cin>>n;
    //freopen("exp6_in.txt","r",stdin);
    //freopen("exp6_out.txt","w",stdout);
    while(n==10){
         vector<vector<int>> martix;vector<vector<int>> mutex(20,vector<int>());//初始化全部为-1
    vector<int> best_a;vector<int> best_b;
    int bestres=0;
    martix.resize(1000);
    for(int i=0;i<1000;i++){
        int n=0;
        //for(int j=0;j<)
        while(n<20){
            int in;
            cin>>in;martix[i].push_back(in);n++;
        }
    }
    cout<<"success input!"<<endl;
    for(int i=0;i<20;i++){
        mute(i,martix,mutex);
    }
    /*for(int i=0;i<mutex.size();i++){
        for(int j=0;j<mutex[i].size();j++){
            cout<<mutex[i][j]<<" ";
        }
        cout<<endl;
    }*/
    int num=0;
    priority_queue<node,vector<node>,cmp> q;//一个以结点的res为优先级的结点优先队列
    node s;s.level=0;
    q.push(s);q.push(adjust(0,s,bestres,mutex));
    node livenode = q.top();//选择当前的res优先级最高的结点为活结点
    int floor = livenode.level;
    //回溯部分
    while(!q.empty()){
        q.pop();
        node extendnode=adjust(floor,livenode,bestres,mutex);
        if(extendnode.Res>bestres){
            bestres=extendnode.Res;
            best_a=extendnode.A;
            best_b=extendnode.B;
        }
        int a=best_a.size()-best_b.size();
        int b=extendnode.A.size()-extendnode.B.size();
        if(extendnode.Res==bestres&&(abs(a)>abs(b))){
            bestres=extendnode.Res;
            best_a=extendnode.A;
            best_b=extendnode.B;
        }
        else if(extendnode.Res==bestres&&best_a.size()<extendnode.A.size()){
            bestres=extendnode.Res;
            best_a=extendnode.A;
            best_b=extendnode.B;
        }
        int sum_a=accumulate(best_a.begin(),best_a.end(),0);
        int sum_b=accumulate(extendnode.A.begin(),extendnode.A.end(),0);
        if(extendnode.Res==bestres&&sum_a>sum_b){
            bestres=extendnode.Res;
            best_a=extendnode.A;
            best_b=extendnode.B;
        }
        extendnode.level++;
        if(extendnode.level!=20){
            if(extendnode.Res!=0){
                q.push(extendnode);
                num++;
            }
            livenode.level++;
            q.push(livenode);
            num++;
        }
        livenode=q.top();
        floor = livenode.level;
    }
    //回溯结束
    cout<<"output is:"<<endl;
    for(int i=0;i<best_a.size();i++){
        cout<<best_a[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<best_b.size();i++){
        cout<<best_b[i]<<" ";
    }
    cout<<endl;
    n--;
    }
   
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}