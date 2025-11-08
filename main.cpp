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

    /*~Node() {
        delete left;
        delete right;
    }*/
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


Node* searchDadRec (Node* r, int n) {
    if (r == nullptr) {
        return nullptr;
    } if (r->left->value == n || r->right->value == n) {
        return r;
    }
    if (n> r->value) {
        return searchDadRec(r->right,n);
    } else if (n< r->value) {
        return searchDadRec(r->left,n);
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

void preOrderPrint (Node* n) {
    if (n == nullptr) return;
    cout << n->value << "  ";
    preOrderPrint (n->left);
    preOrderPrint (n->right);
}

void inOrderPrint (Node* n) {
    if (n == nullptr) return;
    inOrderPrint (n->left);
    cout <<n->value << "  ";
    inOrderPrint (n->right);
}

void postOrderPrint (Node* n) {
    if (n == nullptr) return ;
    postOrderPrint(n->left);
    postOrderPrint(n->right);
    cout << n->value << "  ";
}

Node * noSonRemover (Node* root, Node* toRemove) {
    if(root == toRemove) {
        delete toRemove;
        return nullptr;
    } else {
        Node * dad = searchDadRec(root, toRemove->value);
        if (dad->right == toRemove) {
            dad->right = nullptr;
            delete toRemove;
            return root;
        } else if (dad->left == toRemove) {
            dad->left = nullptr;
            delete toRemove;
            return root;
        }
        return root;
    }
}

Node * oneSonRemover (Node* root, Node* toRemove) {
    if (root == toRemove) {
        if (root->left == nullptr) {
            root = root->right;
            delete toRemove;
        } else {
            root = root->left;
            delete toRemove;
        }
    } else {
        Node * dad = searchDadRec(root, toRemove->value);
         if(dad->right == toRemove) {
            if (toRemove->right == nullptr) {
                dad->right = toRemove->left;
                delete toRemove;
                return root;
            } else {
                dad->right = toRemove->right;
                delete toRemove;
                return root;
            }
        } else {
            if (toRemove->left == nullptr) {
                dad->left = toRemove->right;
                delete toRemove;
                return root;
            } else {
                dad->left = toRemove->left;
                delete toRemove;
                return root;
            }
        }
    }
}


Node * findNext (Node* subNodeRight) {
    while (subNodeRight->left != nullptr) {
        subNodeRight= subNodeRight->left;
    }
    return subNodeRight;
}

Node* findDadOfNext (Node*subNodeRight, Node*succ) {
    while (subNodeRight->left != succ) {
        subNodeRight= subNodeRight->left;
    }
    return subNodeRight;
}


Node* twoSonRemover (Node* root, Node* toRemove) {
    Node* succ = findNext(toRemove->right);
    int nSwap = succ->value;

    if (succ->left == nullptr && succ->right == nullptr) {
        root = noSonRemover(root, succ);
    } else {
        root = oneSonRemover(root, succ);
    }
    toRemove->value = nSwap;
    return root;
}

Node * removeNode (Node* root, int n) {
    Node* nToRemove = searchRec(root, n);
    if (nToRemove == nullptr) return root;
    if (nToRemove->left == nullptr && nToRemove->right == nullptr) {
        return noSonRemover(root, nToRemove);
    }
    if ((nToRemove->left ==nullptr && nToRemove->right != nullptr) || ((nToRemove->right ==nullptr && nToRemove->left != nullptr))) {
        return oneSonRemover(root, nToRemove);
    }
    return twoSonRemover(root, nToRemove);
}


int main () {
    Node* root= new Node (17);
    root = insertionRec(root, 24);
    root = insertionRec(root, 12);
    insertion (root, 21);
    insertion (root, 30);
    root = insertionRec(root,11);
    root = insertionRec(root,6);
    //root = insertionRec(root,4);
    root = insertionRec(root,7);
    root = insertionRec(root,19);
    root = insertionRec(root,22);
    root = insertionRec(root,26);
    root = insertionRec(root,50);
    /*if (searchRec(root, 27) == nullptr) {
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
    cout << endl << "PREORDER:  ";
    preOrderPrint(root);
    cout << endl << "INORDER:   ";
    inOrderPrint(root);
    cout << endl << "POSTORDER: ";
    postOrderPrint(root);*/
    root = removeNode(root, 24);
    inOrderPrint(root);
    return 0;
}
