#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#define N 5
using namespace std;

struct node
{
	int value;
	double weight;
};

const int VALUE_MAX = 100;
//node INDEX[N] = { {1,0.6},{2,0.1},{5,0.1},{3,0.1},{4,0.1} };

void Print(node *A, int len)
{
	int i;
	for (i = 0; i < len; i++)
		cout << A[i].value << '\t';
	cout << endl;
	for (i = 0; i < len; i++)
		cout << A[i].weight << '\t';
	cout << endl;
}

//返回选定的pivot中值
int Partition(node *A, int begin, int end)
{
	int less = begin - 1, i;
	int pivotIndex = begin + rand() % (end - begin + 1);
	for (i = begin; i <= end; i++)
	{
		if (A[i].value < A[pivotIndex].value)
		{
			less++;
			swap(A[less], A[i]);
		}
	}
	swap(A[less + 1], A[pivotIndex]);
	return less + 1;
}

double getSumWeight(node*A, int begin, int end) {
	double sum = 0;
	for (int i = begin; i <= end; i++) {
		sum += A[i].weight;
	}
	return sum;
}

//
int selectWeightedMedian(node* index, int begin, int end) {
	if (begin == end)
		return index[begin].value;
	/*if (end - begin == 1) {
		if (index[begin].weight == index[end].weight)
			return (index[begin].value + index[end].value) / 2;
		if (index[begin].weight > index[end].weight)
			return index[begin].value;
		else
			return index[end].value;
	}*/
	int midIndex = Partition(index, begin, end);
	double leftWeight = getSumWeight(index, begin, midIndex - 1);
	double rightWeight = getSumWeight(index, midIndex + 1, end);
	if (leftWeight <= 0.5&&rightWeight <= 0.5)
		return index[midIndex].value;
	else
		if (leftWeight > rightWeight) {
			index[midIndex].weight += rightWeight;
			return selectWeightedMedian(index, begin, midIndex);
		}
		else {
			index[midIndex].weight += leftWeight;
			return selectWeightedMedian(index, midIndex, end);
		}
}

int main(void) {
	srand((int)time(0));
	cout << setprecision(3);
	int length, sum = 0;
	cout << "length";
	cin >> length;
	node *index = new node[length + 1];
	int * weights = new int[length + 1];
	//生成随机数据
	for (int i = 0; i < length; i++)
	{
		index[i].value = rand() % VALUE_MAX;
		do { weights[i] = rand() % VALUE_MAX; } while (weights[i] == 0);
		sum = sum + weights[i];
	}
	//将权值规格化
	for (int i = 0; i < length; i++)
		index[i].weight = (double)weights[i] / sum;
	//打印生成的数据
	Print(index, length);
	cout << "mid is" << selectWeightedMedian(index, 0, length ) << endl;
	return 0;
}
