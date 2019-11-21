/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct {
    struct TreeNode *root;
} FindElements;

void go_through(struct TreeNode * root) {
    if(root == NULL)
        return;
    if(root->left != NULL) {
        root->left->val = root->val * 2 + 1;
        go_through(root->left);
    }
    if(root->right != NULL) {
        root->right->val = root->val * 2 + 2;
        go_through(root->right);
    }
}

FindElements* findElementsCreate(struct TreeNode* root) {
    root->val = 0;
    go_through(root);
    FindElements *obj = (FindElements *)malloc(sizeof(FindElements));
    obj->root = root;
    return obj;
}

bool find(struct TreeNode *root, int target)
{
    if(root == NULL)
        return false;
    if(root->left != NULL) {
        if(root->left->val == target)
            return true;
        if(find(root->left, target))
            return true;
    }
    if(root->right != NULL) {
        if(root->right->val == target)
            return true;
        if(find(root->right, target))
            return true;
    }
    return false;
}

bool findElementsFind(FindElements* obj, int target) {
    return find(obj->root, target);
}

void findElementsFree(FindElements* obj) {
    free(obj->root);
    free(obj);
}

/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);
 
 * findElementsFree(obj);
*/
