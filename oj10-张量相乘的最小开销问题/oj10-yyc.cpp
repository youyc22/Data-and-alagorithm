#include"iostream"
#include"vector"
#pragma warning(disable : 4996)
int main()
{
    int n = 0, K = 0;
    std::vector<std::vector<unsigned int>> tensor;
    scanf("%d%d", &n, &K);
    std::vector<std::vector<unsigned int>> all_price(n, std::vector<unsigned int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        std::vector<unsigned int> temp;
        for (int j = 0; j < K; j++)
        {
            unsigned int t;
            scanf("%u", &t);
            temp.push_back(t);
        }
        tensor.push_back(temp);
    }
    for (int length = 2; length <= n; length++)
    {
        for (int i = 0; i <= n - length; i++)
        {
            int j = i + length - 1;
            all_price[i][j] = INT64_MAX;
            unsigned int max = 1;
            for (int p = 0; p < K - 2; p++)
            {
                for (int q = i; q <= j; q++)
                {
                    if (tensor[q][p] > 1)
                    {
                        max *= tensor[q][p];
                        break;
                    }
                }
            }
            unsigned int temp1=max * tensor[i][K - 2] *tensor[j][K - 1];
            for (int k = i; k < j; k++)
            {
                unsigned int temp =temp1 * tensor[k + 1][K - 2] + all_price[i][k] + all_price[k + 1][j];
                if (temp < all_price[i][j])
                {
                    all_price[i][j] = temp;
                }
            }
        }
    }
    printf("%u", all_price[0][n - 1]);
    return 0;
}
