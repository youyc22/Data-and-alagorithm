//很难崩的一道题，我目前的方法也很难崩，不想说什么
#include "stdio.h"
#include "vector"
#include "algorithm"
#include "cstdlib"
#include "cmath"
#pragma warning(disable:4996)

int main()
{
    int n = 0, m = 0, r = 0, nn = 0, rr = 0;
    long double out = 0, varx = 0, x = 0, y = 0, c = 0;
    scanf("%d %d", &n, &m);
    std::vector<std::pair <long double, long double> > data;
    for (int i = 0; i < n; i++)
    {
        scanf("%Lf %Lf", &x, &y);
        data.push_back(std::make_pair(x, y));
    }
    nn = n;
    if (n >= 100)
    {
        c = 5.0E-2;
    }
    else
    {
        c = 1.0E-4;
    }
    for (int i = 0; i < nn - 1; i++)
    {
        for (int j = i + 1; j < nn; )
        {
            if (fabs(data[i].first - data[j].first) <= c && fabs(data[i].second - data[j].second) <= c)
            {
                data.erase(data.begin() + j);
                nn--;
            }
            else
            {
                j++;
            }
        }
    }
    r = data.size() - 1;
    std::vector<long double> t(r + 1);
    for (int i = 0; i < r + 1; i++)
    {
        t[i] = data[i].second;
    }
    for (int i = 1; i < r + 1; i++)
    {
        for (int j = r; j >= i; j--)
        {
            t[j] = (t[j] - t[j - 1]) / (data[j].first - data[j - i].first);
        }
    }
    for (int i = r; i >= 0; i--)
    {
        if (fabs(t[i]) >= 1.0E-4)
        {
            rr = i;
            break;
        }
    }
    printf("%d\n", rr);
    for (int i = 0; i < m; i++)
    {
        scanf("%Lf", &varx);
        out = t[r];
        for (int i = r; i > 0; i--)
        {
            out *= (varx - data[i - 1].first);
            out += t[i - 1];
        }
        printf("%.6Lf\n", out);
    }
    return 0;
}
