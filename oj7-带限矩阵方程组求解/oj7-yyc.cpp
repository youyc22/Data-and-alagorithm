#include "cstdio"
#include "vector"
#pragma warning(disable:4996)
int  main()
{
     int p = 0,n = 0,m = 0;
     scanf("%d %d %d",&p,&n,&m);
     if (p == 3)
     {
         std::vector<double> Z(n,0.0);
         std::vector<double> c(n,0.0);
         std::vector<double> b(n,0.0);
         std::vector<double> a(n,0.0);
         for(int i=0;i<n-1;i++)
         {
             scanf("%lf",&c[i]);
         }
         for(int i=0;i<n;i++)
         {
             scanf("%lf",&b[i]);
         }
         for(int i=0;i<n-1;i++)
         {
             scanf("%lf",&a[i]);
         }
         c[0] = c[0] / b[0];
         for (int i = 1; i < n - 1; i++) {
             b[i] = b[i] - a[i - 1] * c[i - 1];
             c[i] = c[i] / b[i];
         }
         b[n - 1] = b[n - 1] - a[n - 2] * c[n - 2];
         for (int i = 0; i < m; i++)
         {
             for (int j = 0; j < n; j++)
             {
                 scanf("%lf", &Z[j]);
             }
             std::vector<double> y(n, 0.0);
             y[0] = Z[0] / b[0];
             for (int i = 1; i < n; i++) {
                 y[i] = (Z[i] - a[i - 1] * y[i - 1]) / b[i];
             }
             for (int i = n - 2; i >= 0; --i) {
                 y[i] = y[i] - c[i] * y[i + 1];
             }
             for (int i = 0; i < n; i++)
             {
                 printf("%.4lf ", y[i]);
             }
             printf("\n");
         }
     }
     else if(p==5)
     {
         std::vector<double>Z(n,0.0);
         std::vector<double>e(n,0.0);
         std::vector<double>d(n,0.0);
         std::vector<double>c(n,0.0);
         std::vector<double>b(n,0.0);
         std::vector<double>a(n,0.0);
         std::vector<double>y(n,0.0);
         for(int i=0;i<n-2;i++)
         {
             scanf("%lf",&e[i]);
         }
         for(int i=0;i<n-1;i++)
         {
             scanf("%lf",&d[i]);
         }
         for(int i=0;i<n;i++)
         {
             scanf("%lf",&c[i]);
         }
         for(int i=0;i<n-1;i++)
         {
             scanf("%lf",&b[i+1]);
         }
         for(int i=0;i<n-2;i++)
         {
             scanf("%lf",&a[i+2]);
         }
         d[0] = d[0] / c[0];
         c[1] = c[1] - b[1] * d[0];
         for (int i = 2; i < n; i++)
         {
             e[i - 2] = e[i - 2] / c[i - 2];
             d[i - 1] = (d[i - 1] - b[i - 1] * e[i - 2]) / c[i - 1];
             b[i] = b[i] - a[i] * d[i - 2];
             c[i] = c[i] - a[i] * e[i - 2] - b[i] * d[i - 1];
         }
         for (int q = 0; q < m; q++)
         {
             for (int j = 0; j < n; j++)
             {
                 scanf("%lf", &Z[j]);
             }
             y[0] = Z[0] / c[0];
             y[1] = (Z[1] - b[1] * y[0]) / c[1];
             for (int i = 2; i < n; i++)
             {
                 y[i] = (Z[i] - a[i] * y[i - 2] - b[i] * y[i - 1]) / c[i];
             }
             y[n - 2] = y[n - 2] - d[n - 2] * y[n - 1];
             for (int i = n - 3; i >= 0; i--)
             {
                 y[i] = y[i] - e[i] * y[i + 2] - d[i] * y[i + 1];
             }
             for (int i = 0; i < n; i++)
             {
                 printf("%.4lf ", y[i]);
             }
             printf("\n");
         }
     }
    return 0;
}
