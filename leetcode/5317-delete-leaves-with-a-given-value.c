/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
    1 <= target <= 1000
    每一棵树最多有 3000 个节点。
    每一个节点值的范围是 [1, 1000] 。
*/

struct TreeNode* removeLeafNodes(struct TreeNode* root, int target){
    if(root->left == NULL && root->right == NULL && root->val == target) {
        free(root);
        return NULL;
    }
    if(root->left != NULL)
        root->left = removeLeafNodes(root->left, target);
    if(root->right != NULL)
        root->right = removeLeafNodes(root->right, target);
    if(root->left == NULL && root->right == NULL && root->val == target) {
        free(root);
        return NULL;
    }

    return root;
}

