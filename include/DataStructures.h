#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__
#include <string.h>
#define min(x, y)  ((x) < (y) ? (x) : (y))
#define max(x, y)  ((x) > (y) ? (x) : (y))

template <typename T> class List {
private:
    class Node {
    private:
        bool owned = true;
    public:
        T* value = nullptr;
        Node* next = nullptr;
        Node* prev = nullptr;
        explicit Node(T* value, bool copy = true) : owned{copy} {
            if (copy)
                this->value = new T{ *value};
            else {
                this->value = value;
            }
        }
        ~Node() {
            if (owned) delete value;
        }
        T* getValue() {
            return value;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void push(T* value, bool owned = false) {
        Node* node = new Node(value, !owned);
        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    void popFirst() {
        if (head != nullptr) {
            Node* node = head;
            head = head->next;
            if (tail == node)
                tail = head;
            delete node;
        }
    }
    void popLast() {
        if (tail != nullptr) {
            Node* node = tail;
            tail = tail->prev;
            if (head == node)
                head = nullptr;
            delete node;
        }
    }
    Node* getFirst() {
        return head;
    }
    ~List() {
        delete head;
    }

};
bool safe_string_compare(char* a, char* b);
#endif //__DATA_STRUCTURES_H__