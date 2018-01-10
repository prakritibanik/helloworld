# You have a binary tree. All you need to do is deep copy or clone the given tree. Remember deep copy or clone means any change in the given tree will not effect the copied tree.

Write both recursive and iterative version.

```c++
#include <iostream>
#include <string>
#include <stack>

using namespace std;

typedef struct Node {
    int val;
    struct Node * left;
    struct Node *right;
}Node;

void preorder(Node *root)
{
    if(root==NULL) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);    
}

Node* deepCopyRec(Node *root)
{
    if(root==NULL) return NULL;
    Node *node = new Node;
    node->val = root->val;
    node->left = deepCopyRec(root->left);
    node->right = deepCopyRec(root->right);
    return node;
}

Node* deepCopyIter(Node *root)
{
    if(root==NULL) return NULL;
    stack<Node*> src, copy;
    src.push(root);
    Node *node = new Node;
    node->val = root->val;
    node->left = node->right = NULL;
    Node *copyRoot = node;
    copy.push(node);
    while(!src.empty())
    {
        Node *top = src.top();
        src.pop();
        Node *ctop = copy.top();
        copy.pop();
        if(top->left)
        {
            Node *lnode = new Node;
            lnode->val = top->left->val;
            lnode->left = lnode->right = NULL;
            ctop->left = lnode;
            copy.push(lnode);
            src.push(top->left);
        }
        
         if(top->right)
        {
            Node *rnode = new Node;
            rnode->val = top->right->val;
            rnode->left = rnode->right = NULL;
            ctop->right = rnode;
            copy.push(rnode);
            src.push(top->right);
        }  
    }
        
    return copyRoot;
}

int main()
{
  Node *root = new Node;
  root->val = 1;
  Node *node1 = new Node;
  node1->val = 2;
  node1->left = NULL;
  Node *node2 = new Node;
  node2->val = 3;  
  node2->left = node2->right = NULL;
  root->left = node1;
  root->right = node2;
  Node *node3 = new Node;
  node3->val = 4;
  node3->left = node3->right = NULL;
  root->left->right = node3;
  
  preorder(root);
  
  Node *copy = deepCopyIter(root);
  cout << '\n';
  preorder(copy);
  
  Node *node4 = new Node;
  node4->val = 5;
  node4->left = node4->right = NULL;
  node1->left = node4;
  cout << '\n'; 
  preorder(root);
  cout << '\n';
  preorder(copy);  
  return 0;
  
}
```
