#include <iostream>
#include <algorithm>
using namespace std;

// An AVL tree node
class Node
{
public:
    Node(int x = 0) : key(x) {}

    int key;
    int height;
    Node *left;
    Node *right;
};

// A utility function to get the
// height of the tree
int height(Node *N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}

/* allocates a new node */
Node *newNode(int key)
{
    Node *node = new Node(key);
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;

    return (node);
}

// A utility function to right
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == nullptr)
    {
        return 0;
    }
    else
    {
        return height(N->left) - height(N->right);
    }
}

// Recursive function to insert a key
Node *insert(Node *node, int key)
{
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)
    {
        return (newNode(key));
    }

    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
    {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key)
    {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int key)
{
    //STEP 1: Perform standard BST delete
    if (root == nullptr)
    {
        return root;
    }

    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            Node *temp = root->left ? root->left : root->right;

            //case1 : no child
            if (temp == nullptr)
            {
                delete root;
                root = nullptr;
            }
            //case2 : a child
            else
            {
                *root = *temp; //copy content
                delete temp;
                temp = nullptr;
            }
        }
        else
        {
            Node *temp = minValueNode(root->right); //minimum value node from right subtree.
            root->key = temp->key; //copy key to root
            root->right = deleteNode(root->right, temp->key); //delete minum value node
        }
    }

    if (root == nullptr)
    {
        return root;
    }

    // STEP2 : Update height of the current node
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP3 : Get the balance factor of this node
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *freeNodes(Node *root)
{
    if (root != nullptr)
    {
        root->left = freeNodes(root->left);
        root->right = freeNodes(root->right);
        delete root;
        return root = nullptr;
    }
    else
    {
        return nullptr;
    }
}

// A utility function to print preorder
void preOrder(Node *root)
{
    if (root != nullptr)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = nullptr;
    int arr[] = {9, 5, 10, 0, 6, 11, -1, 1, 2};
    int n = sizeof(arr) / sizeof(int);

    for (int i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }

    preOrder(root);
    root = deleteNode(root, 10);

    putchar('\n');
    preOrder(root);

    root = freeNodes(root);
    return 0;
}