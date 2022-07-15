//Function to implement the binary tree and tell whether two nodes are cousins or not

/*Given the binary Tree and two nodes say ‘p’ and ‘q’. Determine whether the two nodes
 are cousins of each other or not. Two nodes are said to be cousins of each other if 
 they are at same level of the Binary Tree and have different parents.Do it in O(n).
*/
#include<bits/stdc++.h>
using namespace std;
//Create a class template for BinaryTreeNode;
template <typename T>
class Btnode{
    public:
    T data;
    Btnode<T>* left;
    Btnode<T>* right;
    //create a constructor to initialize the values
    Btnode(T data){
        this->data=data;
        this->left=NULL;
        this->right=NULL;
    } 
    //create a destructor
    ~Btnode(){
        delete left;
        delete right;
    }
};

//Function to take input and create a binary tree and return the root
Btnode<int>* takeinput(){
    int rootdata;
    cout<<"Enter the root data: ";
    cin>>rootdata;
    if(rootdata==-1) return NULL;
    Btnode<int>* root=new Btnode<int>(rootdata);
    queue<Btnode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        Btnode<int>* curr=pendingnodes.front();
        pendingnodes.pop();
        cout<<"Enter the left child of "<<curr->data<<": ";
        int leftchild;
        cin>>leftchild;
        if(leftchild!=-1){
            Btnode<int>* leftchildnode=new Btnode<int>(leftchild);
            pendingnodes.push(leftchildnode);
            curr->left=leftchildnode;
        }
        cout<<"Enter the right child of "<<curr->data<<": ";
        int rightchild;
        cin>>rightchild;
        if(rightchild!=-1){
            Btnode<int>* rightchildnode=new Btnode<int>(rightchild);
            pendingnodes.push(rightchildnode);
            curr->right=rightchildnode;
        }
    }
    delete pendingnodes;
    return root;
}

//Function to print the binary tree level wise
void printBtlevelwise(Btnode<int>* &root){
    if(root ==NULL) return;
    queue<Btnode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        Btnode<int>* curr=pendingnodes.front();
        pendingnodes.pop();
        cout<<curr->data<<":";
        if(curr->left){
            pendingnodes.push(curr->left);
            cout<<'L'<<curr->left->data;
        }
        if(curr->right){
            pendingnodes.push(curr->right);
            cout<<",R"<<curr->right->data;
        }
        delete pendingnodes;
        cout<<"\n";
    }
    return;
}

//Function to find the depth of a node in the Binary tree
int depthBtnode(Btnode<int>* &root, int node){
    if(root==NULL) return -1;
    if(root->data==node) return 0;
    int left=depthBtnode(root->left,node);
    if(left!=-1){
        return 1+left;
    }
    else{
        int right=depthBtnode(root->right,node);
        if(right!=-1){
            return 1+right;
        }
        else return -1;
    }
}

//Function to determine whether two nodes are siblings or not
bool issibling(Btnode<int>* root,int a,int b){
    if(root==NULL) return false;
    if(root->left!=NULL && root->right!=NULL){
        if(root->left->data==a && root->right->data==b){
            return true;
        }
        else if(root->left->data==b && root->right->data==a){
            return true;
        }
        else{
            return (issibling(root->left,a,b) || issibling(root->right,a,b));
        }
    }
    else if(root->left!=NULL){
            return issibling(root->left,a,b);
    }
    else  return issibling(root->right,a,b);
}

//Function to find if the two nodes are cousins are not
bool iscousin(Btnode<int>* &root,int a,int b){
    if(root==NULL) return false;
    return (depthBtnode(root,a)==depthBtnode(root,b) && !issibling(root,a,b));
}

int main(){
    Btnode<int>* root=takeinput();
    printBtlevelwise(root);
    cout<<iscousin(root,3,2);
    return 0;
    delete root;
}
