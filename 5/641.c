typedef struct {
    int *deque;
    int front, back;
    int size;
} MyCircularDeque;


MyCircularDeque *myCircularDequeCreate(int k)
{
    MyCircularDeque *obj = (MyCircularDeque *)malloc(sizeof(MyCircularDeque));
    if (NULL == obj) {
      return NULL;
    }
    obj->size = k + 1;
    obj->deque = (int *)malloc(sizeof(int) * obj->size);
    if (NULL == obj->deque) {
      return NULL;
    }
    obj->front = 0;
    obj->back = 0;
    return obj;
}

bool myCircularDequeInsertFront(MyCircularDeque *obj, int value)
{
    if ((obj->back + 1) % obj->size == obj->front) {
      return false;
    }
    obj->front = (obj->front - 1 + obj->size) % obj->size;
    obj->deque[obj->front] = value;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque *obj, int value)
{
    if ((obj->back + 1) % obj->size == obj->front) {
      return false;
    }
    obj->deque[obj->back] = value;
    obj->back = (obj->back + 1) % obj->size;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque *obj)
{
    if (obj->back == obj->front) {
      return false;
    }
    obj->front = (obj->front + 1) % obj->size;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque *obj) 
{
    if (obj->back == obj->front) {
      return false;
    }
    obj->back = (obj->back - 1 + obj->size) % obj->size;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque *obj)
{
    if (obj->back == obj->front) {
      return -1;
    }
    return obj->deque[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque *obj)
{
    if (obj->back == obj->front) {
      return -1;
    }
    return obj->deque[(obj->back - 1 + obj->size) % obj->size];
}

bool myCircularDequeIsEmpty(MyCircularDeque *obj)
{
    if (obj->back == obj->front) {
      return true;
    }
    return false;
}

bool myCircularDequeIsFull(MyCircularDeque *obj)
{
    if ((obj->back + 1) % obj->size == obj->front) {
      return true;
    }
    return false;
}

void myCircularDequeFree(MyCircularDeque *obj)
{
    free(obj->deque);
    free(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 
 * bool param_3 = myCircularDequeDeleteFront(obj);
 
 * bool param_4 = myCircularDequeDeleteLast(obj);
 
 * int param_5 = myCircularDequeGetFront(obj);
 
 * int param_6 = myCircularDequeGetRear(obj);
 
 * bool param_7 = myCircularDequeIsEmpty(obj);
 
 * bool param_8 = myCircularDequeIsFull(obj);
 
 * myCircularDequeFree(obj);
*/
