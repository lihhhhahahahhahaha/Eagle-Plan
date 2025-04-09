int MaxScore(int *cardPoints, int cardPointsSize, int k) 
{
    if (cardPoints == NULL || cardPointsSize == 0 || k <= 0) {
        return 0;
    }

    /* 计算前k个元素的总和作为初始窗口 */
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += cardPoints[i];
    }
    
    int maxSum = windowSum;
    
    /* 如果k等于数组大小，直接返回总和 */
    if (k == cardPointsSize) {
        return maxSum;
    }

    /* 滑动窗口，从两端取卡片 */
    int left = k - 1;
    int right = cardPointsSize - 1;
    
    for (int i = 0; i < k; i++) {
        /* 减去最左边的卡片，加上最右边的卡片 */
        windowSum = windowSum - cardPoints[left] + cardPoints[right];
        
        /* 更新最大值 */
        if (windowSum > maxSum) {
            maxSum = windowSum;
        }
        
        left--;
        right--;
    }
    return maxSum;
}
