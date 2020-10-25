//设有一个长度为L的钢条，在钢条上标有n个位置点（p1,p2,…,pn）。
//现在需要按钢条上标注的位置将钢条切割为n+1段，假定每次切割所需要的代价与所切割的钢条长度成正比。
//请编写一个算法，能够确定一个切割方案，使切割的总代价最小。
//1.最优子结构
//2.递归关系
//3.计算最优值
//4.构造最优解
//将切钢条过程反过来，求由短条合并为长条需要的代价

//每根钢条的长度sticks
//然后dp[i][j]表示sticks[i]..sticks[j]合并需要的最小代价
//dp[i][j]=sum(sticks[i]..sticks[j])+min(dp[i][k]+dp[k+1][j])其中k从i到j-1
#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
using namespace std;

int minCost(vector<int>& sticks,vector<int>& res,vector<vector<int> >& dp,vector<int>& sum) {
    int m = sticks.size();
    // dp[i][j]表示sticks[i..j]合并需要的最小代价
    for (int i = 0; i < m; i++) {
      dp[i][i] = 0;
      sum[i + 1] = sum[i] + sticks[i];//sum保存着所有可能的短条组合的长度
    }
    for (int count = 1; count <= m; ++count) {//第一层循环，count记录着从i到j的区间的长度
      for (int i = 0; i + count < m; ++i) {
        int j = i + count;
        for (int k = i; k < j; ++k) {//遍历k在i到j区间内的所有可能，求出最小的dp[i][k]+dp[k+1][j]
          //if(dp[i][j]>dp[i][k]+dp[k+1][j])res.push_back(k);
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
          //min(dp[i][k]+dp[k+1][j])
        }
        dp[i][j] += sum[j + 1] - sum[i];
      }
    }
    /*for(int k=0;k<m-1;k++){
      //cout<<sum[m]<<endl;
      //if(dp[0][m - 1] == dp[0][1]+dp[2][m-1]+sum[m]){cout<<"yes";}
      int temp;
      if(dp[0][m - 1] == dp[0][k]+dp[k+1][m-1]+sum[m]){res.push_back(k);}
    }
    /*for(int i=0;i<dp[0].size();i++){
      for(int j=0;j<dp.size();j++){
        cout<<dp[i][j]<<endl;
      }
    }*/
    return dp[0][m - 1];
  }
void backtrace(vector<vector<int> >& dp,vector<int>& sticks,vector<int>& res, int i,int j){
    int m = sticks.size();int sumlength=0;
    int flag=i;
    //cout<<dp[2][3]+dp[4][4];
    // dp[i][j]表示sticks[i..j]合并需要的最小代价//cout<<k<<endl;
    /*for(int i=0;i<dp[0].size();i++){
      for(int j=0;j<dp.size();j++){
        cout<<dp[i][j]<<endl;
      }
    }*/
    //if(j<=i)return;
    //cout<<i<<j;
    int temp;int k;
    //res.push_back(0);
    if(j<i)return;
    if(j==i){
      res.push_back(i);return;
    }
    if(j-i==1){
      res.push_back(i);return;
    }
    for(;i<=j;i++){
      sumlength+=sticks[i];
    }
    i=flag;//重制标志位
    //cout<<sumlength;//sumlength=7;
    for(k=i;k<j;k++){
      //cout<<"hello";
      temp=dp[i][k]+dp[k+1][j]+sumlength;//cout<<temp<<dp[i][j];
      if(dp[i][j] == temp){
        res.push_back(k);break;
        }
    }
    sumlength=0;temp=0;flag=0;//标志位重制
    backtrace(dp,sticks,res,i,k);
    backtrace(dp,sticks,res,k+1,j);
    return;
}


int main(){
    int L;
    freopen("exp2_in.txt","r",stdin);freopen("exp2_out.txt","w",stdout);
    while(cin>>L){
      int num;vector<int> sticks;vector<int> res;int n;
      cin>>n;int m=n+1;vector<int> input(m+1,0);int i;
      //cout<<"input the sticks:0->end"<<endl;
      for(i=1;i<m;i++){
        cin>>input[i];
      }
      input[i]=L;
      sort(input.begin(),input.end());
      /*for(int i=0;i<input.size();i++){
        cout<<input[i]<<endl;
      }*/
      for(int j=0;j<m;j++){
        sticks.push_back(input[j+1]-input[j]);
      }
      /*for(int i=0;i<sticks.size();i++){
        cout<<sticks[i]<<endl;
      }*/
      vector<vector<int> > dp(m, vector<int>(m, numeric_limits<int>::max()));vector<int> sum(m + 1, 0);
      cout<<minCost(sticks,res,dp,sum)<<endl;
    }
    //cout<<dp[2][3]<<dp[4][4]<<dp[2][4];
    //backtrace(dp,sticks,res,0,m-1);
    
    /*for(int i=0;i<dp[0].size();i++){
      for(int j=0;j<dp.size();j++){
        cout<<dp[i][j]<<endl;
      }
    }*/
   /* cout<<"res: "<<res.size()<<endl;
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }*/
    //fclose(stdin);
    //fclose(stdout);
    fclose(stdin);
    fclose(stdout);
    return 0;
}