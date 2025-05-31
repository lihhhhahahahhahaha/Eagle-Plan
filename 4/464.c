#define MAX_STATE (1 << 21)
char memo[MAX_STATE];

bool canWinHelper(int maxChoosable, int remaining, int used)
{
    if (memo[used] != 0) {
        return memo[used] == 1;
    }
    for (int i = 1; i <= maxChoosable; i++)
    {
        int mask = 1 << i;
        if ((used & mask) == 0) {
            if (i >= remaining || !canWinHelper(maxChoosable, remaining - i, used | mask)) {
                memo[used] = 1;
                return true;
            }
        }
    }
    memo[used] = 2;
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (desiredTotal <= 0) {
        return true;
    }
    if (maxChoosableInteger >= 21) {
        return false;
    } 
    if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
        return false;
    }
    memset(memo, 0, sizeof(memo));
    return canWinHelper(maxChoosableInteger, desiredTotal, 0);
}
