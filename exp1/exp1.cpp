#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct node
{
    int value;
    double weight;
};
void Print(node *A, int len)
{
    int i;
    for(i = 1; i <= len; i++)
        cout<<A[i].value<<' ';
    cout<<endl;
    for(i = 1; i <= len; i++)
        cout<<A[i].weight<<' ';
    cout<<endl;
}

int Partition(node *A, int p, int r)
{
    int i = p-1, j;
    for(j = p; j < r; j++)
    {
        if(A[j].value <= A[r].value)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}
node Select(node *A, int p, int r, int i);
node Insert(node *A, int start, int end, int k)
{
    int i, j;
    for(i = 2; i <= end; i++)
    {
        node t = A[i];
        for(j = i; j >= start; j--)
        {
            if(j == start)
                A[j] = t;
            else if(A[j-1].value > t.value)
                A[j] = A[j-1];
            else
            {
                A[j] = t;
                break;
            }
        }
    }
    return A[start+k-1];
}

node Find(node *A, int p, int r)
{
    int i, j = 0;
    int start, end, len = r - p + 1;
    node *B = new node[len/5+1];
    for(i = 1; i <= len; i++)
    {
        if(i % 5 == 1)
            start = i+p-1;
        if(i % 5 == 0 || i == len)
        {
            j++;
            end = i+p-1;
            //对每一组从start到end进行插入排序，并返回中值,如果是最后一组，组中元素个数可能少于5
            node ret = Insert(A, start, end, (end-start)/2+1);
            //把每一组的中值挑出来形成一个新的数组
            B[j] = ret;    
        }
    }
    //对这个数组以递归调用Select()的方式寻找中值
    node ret = Select(B, 1, j, (j+1)/2);
    //delete []B;
    return ret;
}
//以f为主元的划分
int Partition2(node *A, int p, int r, node f)
{
    int i;
    //找到f的位置并让它与A[r]交换
    for(i = p; i < r; i++)
    {
        if(A[i].value == f.value)
        {
            swap(A[i], A[r]);
            break;
        }
    }
    return Partition(A, p, r);
}
//寻找数组A[p..r]中的第i大的元素，i是从1开始计数，不是从p开始
node Select(node *A, int p, int r, int i)
{
    //如果数组中只有一个元素，则直接返回
    if(p == r)
        return A[p];
    //根据文中的算法，找到中值的中值
    node f = Find(A, p, r);
    int q = Partition2(A, p, r, f);
    //转换为中值在在数组A[p..r]中的位置
    int k = q - p + 1;
    //与所寻找的元素相比较
    if(i == k)
        return A[q];
    else if(i < k)
        return Select(A, p, q-1, i);
    else
        //如果主元是数组中的某个元素，后面一半要这样写
        return Select(A, q+1, r, i-k);
        //但是如果主元不是数组中的个某个元素，后面一半要改成Select(A, q, r, i-k+1)
}
//寻找数组A[p..r]中的第i大的元素，i是从1开始计数，不是从p开始
node Select2(node *A, int p, int r, double i)
{
    //如果数组中只有一个元素，则直接返回
    if(p == r)
        return A[p];
    //根据文中的算法，找到中值的中值
    node f = Find(A, p, r);
    //以这个中值为主元的划分，返回中值在整个数组A[1..len]的位置
    //因为主元是数组中的某个元素，划分好是这样的，A[p..q-1] <= f < A[q+1..r]
    int q = Partition2(A, p, r, f);
    //转换为中值在在数组A[p..r]中的位置
    int k = q - p + 1;
    //与所寻找的元素相比较
    double w = 0;
    for(int j = p; j <= k; j++)
        w += A[j].weight;
    if(w-A[k].weight < i && w >= i)
        return A[q];
    else if(w-A[k].weight >= i)
        return Select2(A, p, q-1, i);
    else
        //如果主元是数组中的某个元素，后面一半要这样写
        return Select2(A, q+1, r, i-w);
        //但是如果主元不是数组中的个某个元素，后面一半要改成Select(A, q, r, i-k+1)
}
int main()
{
	srand((int)time(0));
    int n, sum = 0, i;
    cin>>n;
    node *A = new node[n+1];
    int *B = new int[n+1];
    //生成随机数据
    for(i = 1; i <= n; i++)
    {
        A[i].value = rand() % 100;
        do{B[i] = rand() % 100;}while(B[i]==0);
        sum = sum + B[i];
    }
    //将权值规格化
    for(i = 1; i <= n; i++)
        A[i].weight = (double)B[i]/sum;
    //打印生成的数据
    Print(A, n);
    //求带权中位数
    cout<<Select2(A, 1, n, 0.5).value<<endl;
    return 0;
}