int *path;
int pathTop;
int **ans;
int ansTop;

// 将used中元素都设置为0 
void Initialize(int *used, int usedLength) 
{
    for (int i = 0; i < usedLength; i++) {
        used[i] = 0;
    }
}

// 将path中元素拷贝到ans中
void CopyPath() 
{
    int *tempPath = (int *)malloc(sizeof(*tempPath) * pathTop);
    if (tempPath == NULL) {
        return; // 错误处理
    }
    
    for (int i = 0; i < pathTop; i++) {
        tempPath[i] = path[i];
    }
    ans[ansTop++] = tempPath;
}

void BackTracking(int *nums, int numsSize, int *used) 
{
    if (pathTop == numsSize) {
        CopyPath();
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i]) {
            continue;
        }
        
        used[i] = 1;
        path[pathTop++] = nums[i];
        BackTracking(nums, numsSize, used);
        pathTop--;
        used[i] = 0;
    }
}

int **Permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    path = (int *)malloc(sizeof(*path) * numsSize);
    ans = (int **)malloc(sizeof(*ans) * 1000);
    int *used = (int *)malloc(sizeof(*used) * numsSize);
    
    if (path == NULL || ans == NULL || used == NULL) {
        *returnSize = 0;
        return NULL; // 错误处理
    }

    // 将used数组中元素都置0 
    Initialize(used, numsSize);
    ansTop = pathTop = 0;

    BackTracking(nums, numsSize, used);

    // 设置返回的数组长度
    *returnSize = ansTop;
    *returnColumnSizes = (int *)malloc(sizeof(**returnColumnSizes) * ansTop);
    if (*returnColumnSizes == NULL) {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < ansTop; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }
    
    return ans;
}
