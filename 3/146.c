typedef struct DLinkedNode {
    int key;
    int value;
    struct DLinkedNode* prev;
    struct DLinkedNode* next;
} DLinkedNode;

typedef struct HashItem {
    int key;
    DLinkedNode *node;
    struct HashItem *next;
} HashItem;

typedef struct {
    int capacity;
    int size;
    DLinkedNode *head;
    DLinkedNode *tail;
    HashItem **hashTable;
} LRUCache;

DLinkedNode *createNode(int key, int value)
{
    DLinkedNode *node = (DLinkedNode *)malloc(sizeof(DLinkedNode));
    if (NULL == node) {
        return NULL;
    }
    node->key = key;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

unsigned int hash(int key, unsigned int size)
{
    return (unsigned int)key % size;
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    
    cache->head = createNode(-1, -1);
    cache->tail = createNode(-1, -1);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    
    cache->hashTable = (HashItem **)calloc(capacity * 2, sizeof(HashItem *));
    if (cache->hashTable == NULL) {
        return NULL;
    }
    return cache;
}

void moveToHead(LRUCache *cache, DLinkedNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

void removeTail(LRUCache *cache)
{
    DLinkedNode* node = cache->tail->prev;
    node->prev->next = cache->tail;
    cache->tail->prev = node->prev;
    
    unsigned int index = hash(node->key, cache->capacity * 2);
    HashItem *curr = cache->hashTable[index];
    HashItem *prev = NULL;
    
    while (curr) {
        if (curr->key == node->key) {
            if (prev) {
                prev->next = curr->next;
            } else {
                cache->hashTable[index] = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    free(node);
    cache->size--;
}

int lRUCacheGet(LRUCache *cache, int key)
{
    unsigned int index = hash(key, cache->capacity * 2);
    HashItem *item = cache->hashTable[index];
    
    while (item) {
        if (item->key == key) {
            moveToHead(cache, item->node);
            return item->node->value;
        }
        item = item->next;
    }
    return -1;
}

void lRUCachePut(LRUCache *cache, int key, int value)
{
    unsigned int index = hash(key, cache->capacity * 2);
    HashItem *item = cache->hashTable[index];
    
    while (item) {
        if (item->key == key) {
            item->node->value = value;
            moveToHead(cache, item->node);
            return;
        }
        item = item->next;
    }
    
    DLinkedNode *newNode = createNode(key, value);
    
    HashItem *newItem = (HashItem *)malloc(sizeof(HashItem));
    newItem->key = key;
    newItem->node = newNode;
    newItem->next = cache->hashTable[index];
    cache->hashTable[index] = newItem;
    
    newNode->next = cache->head->next;
    newNode->prev = cache->head;
    cache->head->next->prev = newNode;
    cache->head->next = newNode;
    cache->size++;
    
    if (cache->size > cache->capacity) {
        removeTail(cache);
    }
}

void lRUCacheFree(LRUCache *cache)
{
    DLinkedNode *curr = cache->head->next;
    while (curr != cache->tail) {
        DLinkedNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(cache->head);
    free(cache->tail);
    
    for (int i = 0; i < cache->capacity * 2; i++) {
        HashItem *item = cache->hashTable[i];
        while (item) {
            HashItem *temp = item;
            item = item->next;
            free(temp);
        }
    }
    free(cache->hashTable);   
    free(cache);
}
