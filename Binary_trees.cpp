   //*************************************************BINARY TREES*****
#include<iostream>
#include<queue>
using namespace std;
//1)Create a Binary Tree node class
template <typename T>
class BinaryTreeNode{
    public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    //constructor to initialize the binary search tree
    BinaryTreeNode(T data) {
        this->data=data;
        left=NULL;
        right=NULL;
    }

    //Destructor to delete the complete binary tree
    ~BinaryTreeNode(){
        delete left;
        delete right;
    }
};

//2)Function to take input of binary tree from the user levelwise
BinaryTreeNode<int>* takeinput(){
    int rootdata;
    cout<<"Enter root data: ";
    cin>>rootdata;
    if(rootdata==-1){
        return NULL;
    }
    BinaryTreeNode<int>* root=new BinaryTreeNode<int>(rootdata);
    queue<BinaryTreeNode<int>*> pendnodes;
    pendnodes.push(root);
    while(pendnodes.size()!=0){
        BinaryTreeNode<int>* curr=pendnodes.front();
        pendnodes.pop();
        int leftchilddata,rightchilddata;
        cout<<"Enter the left child of "<<curr->data<<": ";
        cin>>leftchilddata;
        if(leftchilddata!=-1){
            BinaryTreeNode<int>* leftchild=new BinaryTreeNode<int>(leftchilddata);
            curr->left=leftchild;
            pendnodes.push(leftchild);
        }
        cout<<"Enter the right child of "<<curr->data<<": ";
        cin>>rightchilddata;
        if(rightchilddata!=-1){
            BinaryTreeNode<int>* rightchild=new BinaryTreeNode<int>(rightchilddata);
            curr->right=rightchild;
            pendnodes.push(rightchild);
        } 
       /* if(leftchilddata==-1 || rightchilddata==-1){
            continue;
        } */ 
    }
    return root;
}

//3)Function to print the Binary Tree //in recurssive manner i.e,not levelwise
void PrintBinaryTree(BinaryTreeNode<int>* root){
    //Base case
    if(root==NULL) return;
    cout<<root->data<<": ";
    if(root->left!=NULL) cout<<'L'<<root->left->data<<',';
    if(root->right!=NULL) cout<<'R'<<root->right->data;
    cout<<endl;
    PrintBinaryTree(root->left);
    PrintBinaryTree(root->right);
}

//Function to print Binary Tree levelwise (use queue)
void PrintBinaryTreeLevelWise(BinaryTreeNode<int>* root){
    if(root==NULL){
        return;
    }
    
    queue<BinaryTreeNode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        BinaryTreeNode<int>* curr=pendingnodes.front();
        pendingnodes.pop();
        cout<<curr->data<<": ";
        if(curr->left!=NULL){
            pendingnodes.push(curr->left);
            cout<<'L'<<curr->left->data<<',';
        }
        if(curr->right!=NULL){
            pendingnodes.push(curr->right);
            cout<<'R'<<curr->right->data;
        }
        cout<<endl;    
    }
    return;
}

//Function to count the numer of nodes in the Binatry Tree
int countnodes(BinaryTreeNode<int>* root){
    if(root==NULL){
        return 0;
    }
    return 1+countnodes(root->left) + countnodes(root->right);
}

/*Find a node
Given a Binary Tree and an integer x, check if node with data x is present in the input binary tree or not. Return true or false.
*/
bool isXpresent(BinaryTreeNode<int>* root,int x){
    if(root==nullptr) return false;
    if(root->data == x){
        return true;
    }
    return (isXpresent(root->left, x) || isXpresent(root->right, x));
}

//Function to find the height of the binary tree
int height(BinaryTreeNode<int>* root){
    if(root==NULL) return 0;
    return 1+max(height(root->left),height(root->right));
}

//Mirror the given binary tree. That is, right child of every nodes
//should become left and left should become right.
BinaryTreeNode<int>* Mirrortree(BinaryTreeNode<int>* root){
    if(root==NULL) return NULL;
    if(root->left!=NULL && root->right!=NULL){
        Mirrortree(root->left);
        Mirrortree(root->right); 
        BinaryTreeNode<int>* temp=root->left;
        root->left=root->right;
        root->right=temp;  
    }
    else if(root->left==NULL){
        Mirrortree(root->right);
        root->left=root->right;
        root->right=NULL;
    }
    else if(root->right==NULL){
        root->right=root->left;
        root->left=NULL;
    }
    return root;
}

//Function for inorder printing i.e,(left->root, root, right->root)
void inorderprint(BinaryTreeNode<int>* root){
    if(root==NULL) return;
    inorderprint(root->left);
    cout<<root->data<<" ";
    inorderprint(root->right);
}

/*Preorder Binary Tree
Given a binary tree, print the preorder traversal of given tree.
Pre-order traversal is: Root LeftChild RightChild*/
void preorderprint(BinaryTreeNode<int>* root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    preorderprint(root->left);
    preorderprint(root->right);
}

/*Postorder Binary Tree
Given a binary tree, print the postorder traversal of given tree.
Post-order traversal is: LeftChild RightChild Root
*/
void postorderprint(BinaryTreeNode<int>* root){
    if(root==NULL) return;
    postorderprint(root->left);
    postorderprint(root->right);
    cout<<root->data<<" ";
}

//Build tree helper function
BinaryTreeNode<int>* BuildTreeHelper(int *in,int* pre,int inS,int inE,int preS,int preE){
    if(inS>inE){
        return NULL;
    }
    int rootdata;
    rootdata=pre[preS];
    int rootindex=-1;
    for(int i=inS;i<=inE;i++){
        if(in[i]==rootdata){
            rootindex=i;
            break;
        }
    }
    int linS=inS;
    int linE=rootindex-1;
    int lpreS=preS+1;
    int lpreE=lpreS+linE-linS;
    int rinS=rootindex+1;
    int rinE=inE;
    int rpreS=lpreE+1;
    int rpreE=preE;
    BinaryTreeNode<int>* root=new BinaryTreeNode<int>(rootdata);
    root->left=BuildTreeHelper(in,pre,linS,linE,lpreS,lpreE);
    root->right=BuildTreeHelper(in,pre,rinS,rinE,rpreS,rpreE);
    return root;
}

//Given the inorder and the preorder.we need to build the binary tree and return the root
BinaryTreeNode<int>* Buildtree(int* in, int* pre, int n){
    return BuildTreeHelper(in,pre,0,n-1,0,n-1);
}

//Another process
//Build a binary tree from postorder and inorder. We need to build the tree and return the root
BinaryTreeNode<int>* buildtreefrompostandinorder(int* pos,int possize,int* in,int insize){
//Base case
    if(pos==NULL || in==NULL || possize==0 || possize!=insize){
        return NULL;
    }

    int rootdata=pos[possize-1];
    int leftcount=0,rightcount;
    while(leftcount<insize && in[leftcount]!=rootdata){
        leftcount++;
    }
    rightcount=insize-leftcount-1;
    BinaryTreeNode<int>* root=new BinaryTreeNode<int>(rootdata);
    root->left=buildtreefrompostandinorder(pos,leftcount,in,leftcount);
    root->right=buildtreefrompostandinorder(pos+leftcount,rightcount,in+leftcount+1,rightcount);
    return root;
}

//Function to find both the height and the diameter
//USE INBUILT PAIR FUNCTION
pair<int,int> findheightdiameter(BinaryTreeNode<int>* root){
    pair<int,int> p;
    if(root==NULL){
        p.first=0;
        p.second=0;
        return p;
    }
    int height=0,diameter=0;
    int leftheight = findheightdiameter(root->left).first;
    int rightheight= findheightdiameter(root->right).first;
    height= 1+max(leftheight,rightheight);
    diameter= max(leftheight+rightheight, max(findheightdiameter(root->left).second,findheightdiameter(root->right).second));
    p.first=height;
    p.second=diameter;
    return p;
}

//Function to find the maximum and minimum in the binary tree
pair<int,int> findminmax(BinaryTreeNode<int>* root){
    pair<int,int> p;
    if(root==NULL){
        p.first=INT_MAX;
        p.second=INT_MIN;
        return p;
    }
    p.first=root->data;
    p.second=root->data;
    pair<int,int> leftminmax=findminmax(root->left);
    pair<int,int> rightminmax=findminmax(root->right);
    p.first=min(p.first,min(leftminmax.first,rightminmax.first));
    p.second=max(p.second,max(leftminmax.second,rightminmax.second));
    return p;
}

//Function to find the sum of all the nodes in the Binary Tree
int findsum(BinaryTreeNode<int>* root){
    if(root==NULL){
        return NULL;
    }
    int sum=root->data;
    return sum+findsum(root->left)+findsum(root->right);

}

//Function to check if the tree is balanced
pair<int,bool> isbalanced(BinaryTreeNode<int>* &root){
    pair<int,bool> ans;
    if(root==NULL){
        ans.first=0;
        ans.second=true;
        return ans;
    }
    int height=0;
    bool checkbalanced=true;
    int leftheight=isbalanced(root->left).first;
    int rightheight=isbalanced(root->right).first;
    height=1+max(leftheight,rightheight);
    if(isbalanced(root->left).second==true && isbalanced(root->right).second==true){
        if(abs(leftheight-rightheight)<=1){
            checkbalanced=true;
        }
        else checkbalanced=false;
    }
    else if(isbalanced(root->left).second==false || isbalanced(root->right).second==false){
        checkbalanced=false;
    }
    ans.first=height;
    ans.second=checkbalanced;
    return ans;

/*
    ans.first=1+ max(left.first,right.first);
    if(left.second=='FALSE' || right.second=='FALSE'){
        ans.second='FALSE';
        return ans;
    }
    else if(left.second=='TRUE' && right.second=='TRUE'){
        if(abs(left.first-right.first)<=1){
           ans.second='TRUE';
        }
    }
    return ans;
    */
}

//Driver function
int main(){
    /*
    BinaryTreeNode<int>* root=new BinaryTreeNode<int>(1);
    BinaryTreeNode<int>* node1=new BinaryTreeNode<int>(2);
    BinaryTreeNode<int>* node2=new BinaryTreeNode<int>(3);
    root->left=node1;
    root->right=node2;
    */
   
    BinaryTreeNode<int>* root=takeinput();
    PrintBinaryTreeLevelWise(root);
    //cout<<countnodes(root)<<endl;
    //cout<<isXpresent(root,4)<<endl;
     //cout<<height(root)<<endl;
    /*
    BinaryTreeNode<int>* mirtree=Mirrortree(root);
    PrintBinaryTreeLevelWise(mirtree);
    */
   /*
    inorderprint(root);
    cout<<endl;
    postorderprint(root);
   To build a tree from inorder and preorder
   */
 /*
    int in[]={4,2,5,1,8,6,9,3,7};
    int post[]={4,5,2,8,9,6,7,3,1};
    BinaryTreeNode<int>* root =buildtreefrompostandinorder(post,9,in,9);
    PrintBinaryTreeLevelWise(root);
 */

/*
   cout<<endl;
   pair<int,int> p=findheightdiameter(root);
   cout<<"Height:"<<p.first<<" Diameter:"<<p.second<<endl;
 */
/*
   pair<int,int> p=findminmax(root);
   cout<<"Minimum:"<<p.first<<" Maximum:"<<p.second<<endl;*/
  // cout<<findsum(root)<<endl;
  pair<int,bool> ans=isbalanced(root);
  cout<<ans.first<<" "<<ans.second;
   
   delete root;
}
