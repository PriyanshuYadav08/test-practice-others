#include <stdio.h>

int maximum(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int main()
{
    int C; // Capacity
    printf("Enter the maximum capacity :");
    scanf("%d", &C);
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    // Arrays to store the profit and Weight of each item
    int Weight[n];
    int Profit[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the profit and weight of the item %d:  ", i + 1);
        scanf("%d", &Profit[i]);
        scanf("%d", &Weight[i]);
    }

    // Create the table for using tabulation method of dynamic programming
    int table[n + 1][C + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= C; w++)
        {
            if (i == 0 || w == 0)
            {
                table[i][w] = 0;
            }
            else if (Weight[i] <= w)
            {
                table[i][w] = maximum(Profit[i] + table[i - 1][w - Weight[i]],
                                      table[i - 1][w]);
            }
            else
            {
                table[i][w] = table[i - 1][w];
            }
        }
    }

    printf("The maximum profit for the above items is: %d ", table[n][C]);
    return 0;
}