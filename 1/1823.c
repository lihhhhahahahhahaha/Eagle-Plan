int FindTheWinner(int n, int k) {
    int x = 0;
    for (int i = 2; i <= n; ++i) {
        x = (x + k) % i;
    }
    return x + 1;
}
