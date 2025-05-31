int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int findPairs(int *nums, int numsSize, int k)
{
    if (k < 0 || numsSize < 2) return 0;
    
    qsort(nums, numsSize, sizeof(int), compare);
    
    int count = 0;
    int left = 0, right = 1;
    
    while (left < numsSize && right < numsSize) {
        if (left > 0 && nums[left] == nums[left-1]) {
            left++;
            continue;
        }

        if (right <= left) {
            right = left + 1;
            continue;
        }
        
        int diff = nums[right] - nums[left];
        
        if (diff == k) {
            count++;
            left++;
            right++;
        } else if (diff < k) {
            right++;
        } else {
            left++;
        }
    }
    
    return count;
}
