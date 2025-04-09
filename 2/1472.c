typedef struct {
    char **history;    /* 历史记录数组 */
    int capacity;      /* 数组容量 */
    int current;       /* 当前位置 */
    int size;          /* 实际大小 */
} BrowserHistory;

BrowserHistory* browserHistoryCreate(char *homepage)
{
    BrowserHistory *obj = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    if (obj == NULL) {
        return NULL;
    }

    obj->history = (char**)malloc(10 * sizeof(char*));
    if (obj->history == NULL) {
        free(obj);
        return NULL;
    }

    obj->history[0] = (char*)malloc((strlen(homepage) + 1) * sizeof(char));
    if (obj->history[0] == NULL) {
        free(obj->history);
        free(obj);
        return NULL;
    }
    strcpy(obj->history[0], homepage);

    obj->capacity = 10;
    obj->current = 0;
    obj->size = 1;

    return obj;
}

void browserHistoryVisit(BrowserHistory* obj, char * url)
{
    /* 清除前进历史 */
    for (int i = obj->current + 1; i < obj->size; i++) {
        free(obj->history[i]);
    }
    obj->size = obj->current + 1;

    /* 检查扩容 */
    if (obj->size >= obj->capacity) {
        obj->capacity *= 2;
        char **newHistory = (char**)realloc(obj->history, obj->capacity * sizeof(char*));
        if (newHistory == NULL) {
            return;
        }
        obj->history = newHistory;
    }

    /* 添加新URL */
    obj->history[obj->size] = (char*)malloc((strlen(url) + 1) * sizeof(char));
    if (obj->history[obj->size] == NULL) {
        return;
    }
    strcpy(obj->history[obj->size], url);

    obj->current = obj->size;
    obj->size++;
}

char * browserHistoryBack(BrowserHistory* obj, int steps)
{
    obj->current = (obj->current - steps) > 0 ? (obj->current - steps) : 0;
    return obj->history[obj->current];
}

char * browserHistoryForward(BrowserHistory* obj, int steps)
{
    obj->current = (obj->current + steps) < (obj->size - 1) ? (obj->current + steps) : (obj->size - 1);
    return obj->history[obj->current];
}

void browserHistoryFree(BrowserHistory* obj)
{
    for (int i = 0; i < obj->size; i++) {
        free(obj->history[i]);
    }
    free(obj->history);
    free(obj);
}
