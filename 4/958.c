typedef struct TreeNode TreeNode; 
#define MAXCAPA 1000
bool isCompleteTree(struct TreeNode* root)
{
    if (root == NULL) return true;
    
    struct TreeNode **queue = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * MAXCAPA);
    int front = 0, rear = 0;
    queue[rear++] = root;
    bool seenNull = false;
    
    while (front < rear) {
        struct TreeNode *node = queue[front++];
        
        if (node == NULL) {
            seenNull = true;
        } else {
            if (seenNull) {
                free(queue);
                return false;
            }
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        }
    }
    
    free(queue);
    return true;
}
