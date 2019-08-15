#include "BST.h"

int main(){
    BST<int, char> bst = BST<int, char>();
    bst.insert(1, 'a');
    bst.insert(11, 'b');    
    bst.insert(5, 'c');
    bst.insert(9, 'c');
    bst.insert(7, 'c');
    bst.insert(100, 'c');
    // bst.inOrder();
    // bst.levelOrder();
    // bst.removeMin();
    // cout<<bst.minimum();
    cout<<bst.maximum()<<endl;
    bst.remove(100);
    cout<<bst.maximum()<<endl;
    cout<<bst.size()<<endl;
}