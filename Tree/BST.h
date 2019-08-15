// 二分搜索树的局限性:
// 如果是顺序插入的话, 二分搜索书退化成了链表, O(n)
// 解决方法: 红黑树, Splay 树, VAL树, 2-3树
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template<typename Key, typename Value>
class BST{
private:
    struct Node{
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key key, Value value){
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }

        Node(Node* node){
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    Node* root;
    int count;

public:
    BST(){
        root = NULL;
        count = 0;
    }

    ~BST(){
        destroy(root);
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    void insert(Key key, Value value){
        root = insert(root, key, value);
    }

    bool contain(Key key){
        return contain(root, key);
    }

    // search的返回值不好是Node*, 因为Node是private的, 所有的返回值为Node*的函数都是private的, 如果返回Node的话, 用户还要去了解Node
    // 如果返回值是Value的话, 在使用之前得调用contain, 因为Value不能为空
    Value* search(Key key){
        return search(root, key);
    }

    void preOrder(){
        preOrder(root);
    }

    void inOrder(){
        inOrder(root);
    }

    void postOrder(){
        postOrder(root);
    }

    void levelOrder(){
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* node = q.front();
            q.pop();

            cout<<node->key<<endl;

            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
    }

    Key minimum(){
        assert(count != 0);

        Node* minNode = minimum(root);
        return minNode->key;
    }

    Key maximum(){
        assert(count != 0);
        
        Node* maxNode = maximum(root);
        return maxNode->key;
    }
    
    // 
    void removeMin(){
        if(root)
            root = removeMin(root);
    }

    void removeMax(){
        if(root)
            root = removeMax(root);
    }

    void remove(Key key){
        root = remove(root, key);
    }
private:
    // 以node为根
    Node* insert(Node* node, Key key, Value value){
        if(node == NULL){
            count++;
            return new Node(key, value);
        }
        if(key < node->key)
            node->left = insert(node->left, key, value);
        else if(key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value;
        return node;
    }

    // 以node为根, 查看是否包含键值为key的节点
    bool contain(Node* node, Key key){
        if(node == NULL)
            return false;

        if(key < node->key)
            return contain(node->left, key);
        else if(key > node->key)
            return contain(node->right, key);
        else // key == node->key
            return true;
    }

    // 以node为根
    Value* search(Node* node, Key key){
        if(node == NULL)
            return NULL;

        if(key < node->key)
            return search(node->left, key);
        else if(key > node->key)
            return search(node->right, key);
        else // key == node->key
            return &node->value;
    }

    void preOrder(Node* node){
        if(node != NULL){
            cout<<node->key<<endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node* node){
        if(node != NULL){
            preOrder(node->left);
            cout<<node->key<<endl;
            preOrder(node->right);
        }
    }

    void postOrder(Node* node){
        if(node != NULL){
            preOrder(node->left);
            preOrder(node->right);
            cout<<node->key<<endl;
        }
    }

    void destroy(Node* node){
        if(node != NULL){
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    Node* minimum(Node* node){
        if(node->left == NULL) // 没有左孩子的节点就是最小的了
            return node;

        return minimum(node->left);
    }
    
    Node* maximum(Node* node){
        if(node->right == NULL)
            return node;

        return maximum(node->right);
    }

    Node* removeMin(Node* node){
        if(node->left == NULL){
            Node* rightNode = node->right; // 在返回之前要删除, 所以要暂存一下
            delete node;
            count--;
            return rightNode;
        }
        node->left = removeMin(node->left);
        return node; // 
    }

    Node* removeMax(Node* node){
        if(node->right == NULL){
            Node* leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }
        node->right = removeMax(node->right);
        return node;
    }

    // O(logn) Hubbard delection
    Node* remove(Node* node, Key key){
        if(node == NULL)
            return NULL;
        if(key > node->key){
            node->right = remove(node->right, key);
            return node;
        }
        else if(key < node->key){
            node->left = remove(node->left, key);
            return node;
        }
        else{ // key == node->key
            if(node->left == NULL){
                Node* rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }
            if(node->right == NULL){
                Node* leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }
            // node->left != NULL && node->right != NULL;
            // 用右子树的最小值代替要删除的节点, 右子树的最小既大于要删除的节点的左子树, 又小于要删除的节点的右子树(不包括拿来替代的那个)
            Node* successor = new Node(minimum(node->right)); // 删除最小后successor后无效了, 所以要复制一份
            count++;
            successor->right = removeMin(node->right); // 里面有count--
            successor->left = node->left;

            delete node;
            count--;

            return successor;
        } 
    }
};
