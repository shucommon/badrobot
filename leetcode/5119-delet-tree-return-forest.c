/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
输入：root = [1,2,3,4,5,6,7], to_delete = [3,5]
输出：[[1,2,null,4],[6],[7]]
*/

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

void update(int *to_delete, int to_deleteSize, int index)
{
    int j = 0;
    for(int i = 0; i < to_deleteSize; i++)
        if(i != index)
           to_delete[j++] = to_delete[i];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize){
    int rs = 0;
    struct TreeNode ** rt = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * (2 * to_deleteSize + 1));
    if(root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    for(int i = 0; i < to_deleteSize; i++) {
        if(to_delete[i] == root->val) {
            if(root->left == NULL && root->right == NULL) {
                *returnSize = 0;
                return NULL;
            }
            struct TreeNode *tmp; 
            int tmp_rs;
            update(to_delete, to_deleteSize, i);
            if(root->left != NULL) {
                tmp = delNodes(root->left, to_delete, to_deleteSize - 1, &tmp_rs);
                for(int j = 0; j < tmp_rs; j++)
                    rt[rs++] = tmp[j]; 
            }
            if(root->right != NULL) {
                tmp = delNodes(root->right, to_delete, to_deleteSize - 1, &tmp_rs);
                for(int j = 0; j < tmp_rs; j++)
                    rt[rs++] = tmp[j]; 
            }
        }
    }
}
