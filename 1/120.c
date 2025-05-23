int MinimumTotal(int **triangle, int triangleSize, int *triangleColSize) 
{
    int *dp = (int *)malloc(sizeof(*dp) * triangleSize);
    if (dp == NULL) {
        return 0;
    }

    // 初始化dp数组为三角形最后一行的值
    for (int i = 0; i < triangleSize; i++) {
        dp[i] = triangle[triangleSize - 1][i];
    }

    // 从倒数第二行开始向上计算 
    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            // 当前节点的最小路径和等于它下面两个节点中较小的那个加上当前值
            dp[j] = (dp[j] < dp[j + 1] ? dp[j] : dp[j + 1]) + triangle[i][j];
        }
    }

    int result = dp[0];
    free(dp);
    dp = NULL;
    return result;
}
