#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict() {
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict() {
            delete tree;
        }

        void insert(std::string key, V value) override {
            try {
                tree->insert(TableEntry<V>(key, value));
            } catch (std::runtime_error &e) {
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
        }

        V search(std::string key) override {
            try {
                return tree->search(TableEntry<V>(key)).value;
            } catch (std::runtime_error &e) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
        }

        V remove(std::string key) override {
            try {
                TableEntry<V> entry = tree->search(TableEntry<V>(key));
                tree->remove(TableEntry<V>(key));
                return entry.value;
            } catch (std::runtime_error &e) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
        }

        int entries() override {
            return tree->size();
        }

        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bsd) {
            out << *(bsd.tree);
            return out;
        }
};

#endif
