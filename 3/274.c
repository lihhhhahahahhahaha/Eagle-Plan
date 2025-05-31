int partition(int *citations, int left, int right)
{
    int pivot = citations[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (citations[j] <= pivot) {
            i++;
            int temp = citations[i];
            citations[i] = citations[j];
            citations[j] = temp;
        }
    }
    int temp = citations[i+1];
    citations[i+1] = citations[right];
    citations[right] = temp;
    return i + 1;
}

void quickSort(int *citations, int left, int right)
{
    if (left < right) {
        int pi = partition(citations, left, right);
        quickSort(citations, left, pi - 1);
        quickSort(citations, pi + 1, right);
    }
}

int hIndex(int *citations, int citationsSize)
{
    quickSort(citations, 0, citationsSize - 1);
    int h = 0;
    for (int i = citationsSize - 1; i >= 0; i--) {
        if (citations[i] > h) {
            h++;
        } else {
            break;
        }
    }
    return h;
}
