#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {

    private:
        int nelem;
        BSNode<T>* root;

        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("Element not found!");
            } else if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n;
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                return new BSNode<T>(e);
            } else if (e < n->elem) {
                n->left = insert(n->left, e);
            } else if (e > n->elem) {
                n->right = insert(n->right, e);
            } else {
                throw std::runtime_error("Element already exists!");
            }
            return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << *n << " ";
                print_inorder(out, n->right);
            }
        }

        T max(BSNode<T>* n) const {
            if (n->right == nullptr) {
                return n->elem;
            }
            return max(n->right);
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* aux = n->left;
                delete n;
                return aux;
            }
            n->right = remove_max(n->right);
            return n;
        }

        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Element not found!");
            } else if (e < n->elem) {
                n->left = remove(n->left, e);
            } else if (e > n->elem) {
                n->right = remove(n->right, e);
            } else {
                if (n->left == nullptr) {
                    BSNode<T>* aux = n->right;
                    delete n;
                    return aux;
                } else if (n->right == nullptr) {
                    BSNode<T>* aux = n->left;
                    delete n;
                    return aux;
                } else {
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                }
            }
            return n;
        }

        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        BSTree() {
            nelem = 0;
            root = nullptr;
        }

        ~BSTree() {
            delete_cascade(root);
        }

        int size() const {
            return nelem;
        }

        T search(T e) const {
            return search(root, e)->elem;
        }

        T operator[](T e) const {
            return search(e);
        }

        void insert(T e) {
            root = insert(root, e);
            nelem++;
        }

        void remove(T e) {
            root = remove(root, e);
            nelem--;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
};

#endif
