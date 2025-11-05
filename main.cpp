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

bool noSonRemover (Node* dad, Node* nRm) {
    if (dad->right == nRm) {
        dad->right = nullptr;
        delete nRm;
        return true;
    } else if (dad->left == nRm) {
        dad->left = nullptr;
        delete nRm;
        return true;
    }
    return false;
}

bool oneSonRemover (Node* dad, Node* son) {
    if(dad->right == son) {
        if (son->right == nullptr) {
            dad->right = son->left;
            delete son;
            return true;
        } else {
            dad->right = son->right;
            delete son;
            return true;
        }
    } else {
        if (son->left == nullptr) {
            dad->left = son->right;
            delete son;
            return true;
        } else {
            dad->left = son->left;
            delete son;
            return true;
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


bool twoSonRemover (Node* toRemove) {
    Node* succ = findNext(toRemove);
    Node* dad =findDadOfNext(toRemove, succ);
    dad->left=succ->right;
    toRemove->value = succ->value;
    delete succ;
    return true;
}

bool removeNode (Node* root, int n) {
    Node* nToRemove = searchRec(root, n);
    if (nToRemove == nullptr) return false;
    Node* dadNode = searchDadRec(root, n);
    if (nToRemove->left == nullptr && nToRemove->right == nullptr) {
        return noSonRemover(dadNode, nToRemove);
    }
    if ((nToRemove->left ==nullptr && nToRemove->right != nullptr) || ((nToRemove->right ==nullptr && nToRemove->left != nullptr))) {
        return oneSonRemover(dadNode, nToRemove);
    }
    return twoSonRemover(nToRemove);
}


int main () {
    Node* root= new Node (17);
    root = insertionRec(root, 24);
    root = insertionRec(root, 12);
    insertion (root, 21);
    insertion (root, 30);
    root = insertionRec(root,11);
    root = insertionRec(root,6);
    root = insertionRec(root,4);
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
    if (!removeNode(root, 24)) cout << "node NOT found!!\n";
    inOrderPrint(root);
    return 0;
}
