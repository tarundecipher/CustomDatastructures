#include <bits/stdc++.h>
#define ll long long int
using namespace std;

class OperationStrategy
{
public:
    virtual int operate(int a, int b) = 0;
};

class MaxOperation : public OperationStrategy
{
public:
    int operate(int a, int b)
    {
        return max(a, b);
    }
};

class MinOperation : public OperationStrategy
{
public:
    int operate(int a, int b)
    {
        return min(a, b);
    }
};

class sparseTable
{

    int table[(int)1e3 + 5][26];
    OperationStrategy *op;

public:
    sparseTable(OperationStrategy *op)
    {
        this->op = op;
    }
    void createTable(int arr[], int n)
    {

        for (int i = 0; i < n; i++)
        {
            table[i][0] = arr[i];
        }

        for (int k = 1; k < 26; k++)
        {
            for (int i = 0; i + (1 << k) <= n; i++)
            {
                table[i][k] = this->op->operate(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int getmin(int l, int r)
    {
        int len = log2(r - l + 1);
        int ans = this->op->operate(table[l][len], table[r - (1 << len) + 1][len]);
        return ans;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    sparseTable sp1(new MinOperation());
    int arr[4] = {1, 2, 3, 4};
    sp1.createTable(arr, 4);
    cout << sp1.getmin(1, 3) << endl;
}