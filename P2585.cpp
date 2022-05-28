#include<iostream>
#include<string>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;
string treeS;
struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int maxColor = 1;
    int minColor = 0;
    int totNode = 1;
    bool maxG = true;
    bool minG = false;
};
int main(){
    cin >> treeS;
    stack<TreeNode*> alg;
    //深度优先搜索
    stack<TreeNode*> stack;
    TreeNode* root = new TreeNode();
    alg.push(root);
    stack.push(root);
    for(int i =0;i<treeS.length();i++){
        TreeNode* node = stack.top();
        stack.pop();
        if(treeS[i]=='1'){
            TreeNode* left = new TreeNode();
            node->left = left;
            alg.push(left);
            stack.push(left);
        }else if(treeS[i]=='2'){
            TreeNode* left = new TreeNode();
            TreeNode* right = new TreeNode();
            node->left = left;
            node->right= right;
            stack.push(right);
            stack.push(left);
            alg.push(right);
            alg.push(left);
        }
    }
    int num = 0;
    while(!alg.empty()){
        TreeNode* node = alg.top();
        alg.pop();
        if(node->left==NULL){
            num = 0;
        }else if(node->right==NULL){
            if(node->left->maxG){
                node->maxG = false;
                node->maxColor = node->left->maxColor;
            }else{
                node->maxG = true;
                node->maxColor = node->left->maxColor+1;
            }
            node->minG = false;
            node->minColor = node->left->minColor;
            node->totNode = node->left->totNode+1;
        }else{
            //计算max值
            if(node->left->maxG&&node->right->maxG){
                node->maxG = false;
                node->maxColor = max(node->left->totNode-node->left->maxColor-node->left->minColor+node->right->maxColor,node->right->totNode-node->right->maxColor-node->right->minColor+node->left->maxColor);
            }else if(node->left->maxG||node->right->maxG){
                node->maxG = false;
                node->maxColor = node->left->maxColor + node->right->maxColor;
            }else{
                node->maxG = true;
                node->maxColor = node->left->maxColor + node->right->maxColor+1;
            }
            //计算min值
            if(node->left->minG&&node->right->minG){
                node->minG = false;
                node->minColor = min(node->left->totNode-node->left->maxColor-node->left->minColor+node->right->minColor,node->right->totNode-node->right->maxColor-node->right->minColor+node->left->minColor);
            }else if(node->left->minG||node->right->minG){
                node->minG = false;
                node->minColor = node->left->minColor + node->right->minColor;
            }else{
                node->minG = true;
                node->minColor = node->left->minColor + node->right->minColor+1;
            }
            node->totNode = node->left->totNode+node->right->totNode+1;
        }
    }
    cout << root->maxColor << " "<<root->minColor<<endl;
    system("pause");
    return 0;
}