typedef struct {
    int difficulty;
    int profit;
} Job;

int cmp(const void *a, const void *b)
{
    return ((Job *)a)->difficulty - ((Job *)b)->difficulty;
}

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize)
{
    Job *jobs = (Job *)malloc(difficultySize * sizeof(Job));
    if (NULL == jobs) {
        return -1;
    }
    for (int i = 0; i < difficultySize; i++) {
        jobs[i].difficulty = difficulty[i];
        jobs[i].profit = profit[i];
    }

    qsort(jobs, difficultySize, sizeof(Job), cmp);

    int *maxProfit = (int *)malloc(difficultySize * sizeof(int));
    if (maxProfit == NULL) {
        return -1;
    }
    maxProfit[0] = jobs[0].profit;
    for (int i = 1; i < difficultySize; i++) {
        maxProfit[i] = (jobs[i].profit > maxProfit[i - 1]) ? jobs[i].profit : maxProfit[i - 1];
    }

    int res = 0;
    for (int i = 0; i < workerSize; i++) {
        int ability = worker[i];
        int left = 0, right = difficultySize - 1, best = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (jobs[mid].difficulty <= ability) {
                best = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (best != -1) {
            res += maxProfit[best];
        }
    }

    free(jobs);
    free(maxProfit);
    return res;
}
