#include <iostream>

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node *z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node *y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node *y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void printTree(Node *node, int depth) {
        if (node != nullptr) {
            printTree(node->right, depth + 1);
            for (int i = 0; i < depth; i++) {
                std::cout << "    ";
            }
            std::cout << node->data << "(" << (node->color == RED ? "Red" : "Black") << ")" << std::endl;
            printTree(node->left, depth + 1);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(int data) {
        Node *z = new Node(data);
        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        insertFixup(z);
    }

    void LeftRotate() {
        if (root != nullptr) {
            leftRotate(root);
        }
    }

    void RightRotate() {
        if (root != nullptr) {
            rightRotate(root);
        }
    }

    void PrintTree() {
        printTree(root, 0);
    }
};

int main() {
    int N;
    std::cin >> N;

    RedBlackTree rbTree;

    for (int i = 0; i < N; ++i) {
        int value;
        std::cin >> value;
        rbTree.Insert(value);
    }

    std::cout << "Red-Black Tree:" << std::endl;
    rbTree.PrintTree();

    std::cout << "\nAfter Left Rotation:" << std::endl;
    rbTree.LeftRotate();
    rbTree.PrintTree();

    std::cout << "\nAfter Right Rotation:" << std::endl;
    rbTree.RightRotate();
    rbTree.PrintTree();

    return 0;
}
