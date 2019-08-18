/*
给你一个二叉树的根节点 root。设根节点位于二叉树的第 1 层，而根节点的子节点位于第 2 层，依此类推。
请你找出层内元素之和 最大 的那几层（可能只有一层）的层号，并返回其中 最小 的那个
         1
      7    0
    7  -8 
输入：[1,7,0,7,-8,null,null]
输出：2
解释：
第 1 层各元素之和为 1，
第 2 层各元素之和为 7 + 0 = 7，
第 3 层各元素之和为 7 + -8 = -1，
所以我们返回第 2 层的层号，它的层内元素之和最大。

树中的节点数介于 1 和 10^4 之间
-10^5 <= node.val <= 10^5

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct list_bt {
    struct TreeNode *ele;
    struct list_bt *next;
} list;

int maxLevelSum(struct TreeNode* root){
    list *ls;
    if(root != NULL) {
        ls = (list *)malloc(sizeof(list));
        ls->ele = root;
        ls->next = NULL;
        //printf("%d c %c\n", ls->ele->data, ls->ele->c);
    } else
        return;

    list *p1 = ls;
    list *p2 = ls;
    int max = root->val, level = 1, lv = 1;
    int cnt1 = 0, cnt2 = 2, sum = 0; 
    while(p1 != NULL) {
        if(p1->ele->left != NULL) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->ele = p1->ele->left;
            p2 = p2->next;
            p2->next = NULL;
            //printf("%d c %c\n", p2->ele->data, p2->ele->c);
            sum += p2->ele->val;
            cnt1++;
        } else {
            cnt2--;
        }
        if(p1->ele->right != NULL) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->ele = p1->ele->right;
            p2 = p2->next;
            p2->next = NULL;
            //printf("%d c %c\n", p2->ele->data, p2->ele->c);
            sum += p2->ele->val;
            cnt1++;
        } else {
            cnt2--;
        }
        if(cnt1 == cnt2) {
            lv++;
            if(sum > max) {
                max = sum;
                level = lv;
            }
            sum = 0;
            cnt2 = cnt1 * 2;
            cnt1 = 0;
        }
        p1 = p1->next;
    }
    return level;
}

/*
// example
class Solution {
    int s[10005],n;
public:
    void dfs(TreeNode* root,int d)
    {
        if(!root)return;
        n=max(n,d);
        s[d]+=root->val;
        dfs(root->left,d+1);
        dfs(root->right,d+1);
    }
    int maxLevelSum(TreeNode* root) {
        memset(s,0,sizeof(s));
        n=0;
        dfs(root,1);
        int i,j;
        for(i=j=1;i<=n;i++)if(s[i]>s[j])j=i;
        return j;
    }
};
*/

int main()
{

    return 0;
}
