#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node* parent;
    Node* left;
    Node* right;

    Node(int x)
    {
        this->value = x;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BST
{
public:
    Node* root;
    BST(int x = 0)
    {
        root = new Node(x);
    }

    ~BST()
    {
        this->root = treeFree(this->root);
    }

    /* 모든 노드의 메모리 해제 */
    Node* treeFree(Node* root)
    {
        if (root != nullptr)
        {
            root->left = treeFree(root->left);
            root->right = treeFree(root->right);
            // printf("delete : %d\n", root->value);
            delete root;
            return root = nullptr;
        }
        else
        {
            return nullptr;
        }
    }

    /* 전위 순회: root -> left -> right */
    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            printf("%d ", root->value);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    /* 중위 순회: left -> root -> right */
    void inOrder(Node* root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            printf("%d ", root->value);
            inOrder(root->right);
        }
    }

    /* 후위 순회: left -> right -> root */
    void postOrder(Node* root)
    {
        if (root != nullptr)
        {
            postOrder(root->left);
            postOrder(root->right);
            printf("%d ", root->value);
        }
    }

    /* treeSearch */
    Node* treeSearch(Node* root, const int target)
    {
        if (root != nullptr)
        {
            if (root->value == target)
            {
                return root;
            }
            if (root->value < target)
            {
                return this->treeSearch(root->right, target);
            }
            else
            {
                return this->treeSearch(root->left, target);
            }
        }
        else
        {
            return nullptr;
        }
    }

    /* treeInsert */
    Node* treeInsert(Node* root, int value)
    {
        if (root->value < value)
        {
            if (root->right != nullptr)
            {
                root->right = treeInsert(root->right, value);
                return root;
            }
            else
            {
                Node* newChild = new Node(value);
                root->right = newChild;
                newChild->parent = root;
                return root;
            }
        }
        else
        {
            if (root->left != nullptr)
            {
                root->left = treeInsert(root->left, value);
                return root;
            }
            else
            {
                Node* newChild = new Node(value);
                root->left = newChild;
                newChild->parent = root;
                return root;
            }
        }
    }

    /* delete Node */
    Node* deleteNode(Node* target)
    {
        //case 1 : target is a leaf node
        if (target->left == nullptr && target->right == nullptr)
        {
            delete target;
            target = nullptr;
            return target;
        }

        //case 2-1 : target has a right child
        else if (target->left == nullptr && target->right != nullptr)
        {
            Node* rightChild = target->right;
            delete target;
            return rightChild;
        }

        //case 2-2 : target has a left child
        else if (target->left != nullptr && target->right == nullptr)
        {
            Node* leftChild = target->left;
            delete target;
            return leftChild;
        }

        //case 3 : target has two children
        else
        {
            Node* replaceChild = target->right;
            while (replaceChild->left != nullptr)
            {
                replaceChild = replaceChild->left;
            }

            target->value = replaceChild->value;

            // there are below two cases to handle
            if (target->right == replaceChild)
            {
                target->right = replaceChild->right;
            }
            else
            {
                replaceChild->parent->left = replaceChild->right;
            }

            delete replaceChild;
            return target;
        }
    }

    /* delete operation */
    void treeDelete(Node* target, Node* parent)
    {
        if (this->root == target)
        {
            root = deleteNode(target);
        }
        else
        {
            if (parent->left == target)
            {
                parent->left = deleteNode(target);
            }
            else
            {
                parent->right = deleteNode(target);
            }
        }
    }
};

int main()
{

    BST* bst = new BST(5);
    int arr[] = { 10, 4, 2, 9, 3, 7, 8, 6, 1, 0, 11 };
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n; i++)
    {
        bst->root = bst->treeInsert(bst->root, arr[i]);
    }

    //bst->treeDelete(bst->root, nullptr);

    bst->preOrder(bst->root);
    putchar('\n');

    bst->inOrder(bst->root);
    putchar('\n');

    bst->postOrder(bst->root);
    putchar('\n');

    Node* target = bst->treeSearch(bst->root, 5);
    if (target != nullptr)
    {
        printf("search result : %d\n", target->value);
    }
    else
    {
        printf("존재하지 않는 키 값입니다\n");
    }

    delete bst;
    bst = nullptr;
    return 0;
}