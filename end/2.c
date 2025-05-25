bool IsConse(char a, char b)
{
    int dif = abs(a - b);
    return (dif == 1) || (dif == 25);
}
char* resultingString(char* s) { // 这是题目的定义
    int len = strlen(s);
    if (len < 2) {return s;}
    char *stack = (char *)malloc((len + 1) * sizeof(char));
    if (NULL == stack) {return NULL;}
    int top = -1;
    for (int i = 0; i < len; i++) {
        if (top >= 0 && IsConse(stack[top], s[i])) {
            top--;
        } else {
            top++;
            stack[top] = s[i];
        }
    }
    stack[top + 1] = '\0';
    char *result = (char *)malloc((top + 2) * sizeof(char));
    strcpy(result, stack);
    free(stack);
    return result;
}
