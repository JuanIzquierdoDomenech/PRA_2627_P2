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
        ListLinked<TableEntry<V>>* table;

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
                table[pos].remove(idx);
                table[pos].insert(idx, TableEntry<V>(key, value));
            } else {
                table[pos].append(TableEntry<V>(key, value));
                n++;
            }
        }

        V search(std::string key) override {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx == -1) {
                throw std::runtime_error("Clave no encontrada: " + key);
            }
            return table[pos].get(idx).value;
        }

        V remove(std::string key) override {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            if (idx == -1) {
                throw std::runtime_error("Clave no encontrada: " + key);
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
                throw std::runtime_error("Clave no encontrada: " + key);
            }
            return table[pos].get(idx).value;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            for (int i = 0; i < th.max; i++) {
                int sz = th.table[i].size();
                out << "[" << i << "]: ";
                for (int j = 0; j < sz; j++) {
                    out << th.table[i].get(j);
                    if (j < sz - 1) {
                        out << ", ";
                    }
                }
                out << std::endl;
            }
            return out;
        }
};

#endif
