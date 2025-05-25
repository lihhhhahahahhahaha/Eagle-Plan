/* 第三题没做对，但还是把代码写在这里吧 */
#define MAX_N 160
int maxProfit(int n, int* present, int presentSize, int* future, int futureSize, int** hierarchy, int hierarchySize, int* hierarchyColSize, int budget) { // 这是题目
    int *parent = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }
    for (int i = 0; i < hierarchySize; i++) {
        int u = hierarchy[i][0];
        int v = hierarchy[i][1];
        parent[v] = u;
    }
    int *cost = (int *)malloc((n + 1) * sizeof(int));
    if (NULL == cost) {return -1;}
    int *profit = (int *)malloc((n + 1) * sizeof(int));
    if (NULL == cost) {return -1;}
    for(int i = 1; i <= n; i++) {
        if (parent[i] != -1) {
            cost[i] = present[i - 1] / 2;
        } else {
            cost[i] = present[i - 1];
        }
        profit[i] = future[i - 1] - cost[i];
    }
    int *dp = (int *)malloc((budget + 1) * sizeof(int));
    if (NULL == dp) {return -1;}
    memset(dp, 0, (budget + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        for (int j = budget; j >= cost[i]; j--) {
            if (dp[j - cost[i]] + profit[i] > dp[j]) {
                dp[j] = dp[j - cost[i]] + profit[i];
            }
        }
    }
    int maxProfit = dp[budget];
    free(parent);
    free(cost);
    free(profit);
    free(dp);
    return maxProfit;
}
