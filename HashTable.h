#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2627_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        mutable ListLinked<TableEntry<V>>* table;

        int h(std::string key) {
            int sum = 0;
            for (int i = 0; i < (int) key.size(); i++) {
                sum += int(key.at(i));
            }
            return sum % max;
        }

    public:
        HashTable(int size) {
            max = size;
            n = 0;
            table = new ListLinked<TableEntry<V>>[size];
        }

        ~HashTable() {
            delete[] table;
        }

        void insert(std::string key, V value) override {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx != -1) {
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
            table[pos].prepend(TableEntry<V>(key, value));
            n++;
        }

        V search(std::string key) override {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx == -1) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
            return table[pos].get(idx).value;
        }

        V remove(std::string key) override {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx == -1) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
            TableEntry<V> entry = table[pos].remove(idx);
            n--;
            return entry.value;
        }

        int entries() override {
            return n;
        }

        int capacity() {
            return max;
        }

        V operator[](std::string key) {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx == -1) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
            return table[pos].get(idx).value;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
            out << "==============" << std::endl;
            for (int i = 0; i < th.max; i++) {
                out << "== Cubeta " << i << " ==" << std::endl;
                int sz = th.table[i].size();
                if (sz == 0) {
                    out << "List => []" << std::endl;
                } else {
                    out << "List => [" << std::endl;
                    for (int j = 0; j < sz; j++) {
                        out << "  " << th.table[i].get(j) << std::endl;
                    }
                    out << "]" << std::endl;
                }
            }
            out << "==============";
            return out;
        }
};

#endif