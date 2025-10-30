#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node (int n) {
        value = n;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertionRec (Node * r, int n) {
    if (r == nullptr) {
        return new Node (n);
    }
    if (r->value == n) {
        return r;
    }
    if (n> r->value) {
        r->right = insertionRec(r->right, n);
    } else if ( n< r->value) {
        r->left = insertionRec(r->left, n);
    }
    return r;
}

Node* searchRec (Node* r, int n) {
    if (r == nullptr) {
        return nullptr;
    } if (r->value == n) {
        return r;
    }
    if (n> r->value) {
        return searchRec(r->right,n);
    } else if (n< r->value) {
        return searchRec(r->left,n);
    }
    return r;
}

bool search (Node*radice, int n) {
    Node* r= radice;
    while (r!= nullptr) {
        if (r->value == n) {
            return true;
        }
        if(n> r->value) {
            r = r->right;
        } else {
            r = r->left;
        }
    }
    return false;
}

bool insertion (Node* radice, int n) {
    Node* cur = radice;
    Node* prec = nullptr;
    while (cur!= nullptr) {
        if(cur->value == n) {
            return false;
        }
        if(n> cur->value) {
            if (cur->right == nullptr) {
                cur->right = new Node(n);
                return true;
            } else {
                cur=cur->right;
            }
        } if (n< cur->value) {
            if (cur->left == nullptr) {
                cur->left = new Node (n);
                return true;
            } else {
                cur = cur->left;
            }
        }
    }
    return false;
}

int main () {
    Node* root= new Node (17);
    root = insertionRec(root, 23);
    root = insertionRec(root, 12);
    if (insertion (root, 21)) cout <<"node insert\n";
    if (insertion (root, 27)) cout << "node insert\n";
    if (searchRec(root, 27) == nullptr) {
        cout << "node not found\n";
    } else {
        cout << "node found\n";
    }
    if (searchRec(root, 8) == nullptr) {
        cout << "node not found\n";
    } else {
        cout << "node found\n";
    }
    if (search(root, 12)) {
        cout << "node found\n";
    }
    return 0;
}