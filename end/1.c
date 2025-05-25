long long minCuttingCost(int n, int m, int k) {
    /* 如果不需要切割 */
    if (n <= k && m <= k) {
        return 0;
    }
    /* 如果需要切割一段 */
    if (n <= k) {
        return (long long)(m - k) * k;
    }
    if (m <= k) {
        return (long long)(n - k) * k;
    }
    return -1;
}
