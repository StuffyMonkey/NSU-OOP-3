#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class Container {
    private:
        // base class for storing data in container
        class Cell {
            public:
            T data;
            Cell* next = nullptr;
            Cell* prev = nullptr;

            Cell(T const& data) : data(data) {}
        };

        class Iterator {
            public:
                Iterator(Cell* init) : ptr(init) {}

                // Prefix increment
                Iterator& operator++() {
                    ptr = ptr->next;
                    return *this;
                }

                Iterator& operator--() {
                    ptr = ptr->prev;
                    return *this;
                }

                // Postfix increment
                Iterator operator++(int) {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                Iterator operator--(int) {
                    Iterator tmp = *this;
                    --(*this);
                    return tmp;
                }

                bool operator==(const Iterator& other) {
                    return ptr == other.ptr;
                };

                bool operator!=(const Iterator& other) {
                    return ptr != other.ptr;
                };

                T& operator*() const {
                    return ptr->data;
                }

                T* operator->() const {
                    return &ptr->data;
                }

            private:
                Cell* ptr;
        };

    public:
        Container(const std::initializer_list<T>& iterable) {
            for(auto it = iterable.begin(); it != iterable.end(); it++) {
                addLast((*it));
            }
        }

        Container() = default;

        void addLast(const T& data) {
            Cell* newCell = new Cell(data);
            len++;

            if (tail == nullptr) {
                tail = newCell;
                head = tail;
                return;
            }
            else {
                Cell* tmp = tail;
                tail = newCell;
                tail->prev = tmp;
                tmp->next = tail;
                return;
            }

        }

        void addFirst(const T& data) {
            Cell* newCell = new Cell(data);
            len++;

            if (head == nullptr) {
                head = newCell;
                tail = head;
                return;
            }
            else {
                Cell* tmp = head;
                head = newCell;
                head->next = tmp;
                tmp->prev = head;
                return;
            }
        }

        Iterator begin() {
            return Iterator(head);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        void removeFirst() {
            if (isEmpty())
                throw std::out_of_range("Attempt to remove element from empty container");

            Cell* tmp = head;
            head = tmp->next;
            if (head != nullptr)
                head->prev = nullptr;
            else
                tail = nullptr;
            free(tmp);
            len--;
        }

        T& getFirst() {
            if (! isEmpty())
                return head->data;
            else
                throw std::out_of_range("Attempt to get element from empty container");
        }

        T& getLast() {
            if (! isEmpty())
                return tail->data;
            else
                throw std::out_of_range("Attempt to get element from empty container");
        }

        

        bool isEmpty() {
            return (len == 0);
        }

        int getLen() {
            return len;
        }

        void removeLast() {
            if (isEmpty())
                throw std::out_of_range("Attempt to remove element from empty container");

            Cell* tmp = tail;
            tail = tmp->prev;
            if (tail != nullptr)
                tail->next = nullptr;
            else
                head = nullptr;
            free(tmp);
            len--;
        }

        void reverseContainer() {
            Cell* tmp = head;
            while (tmp != nullptr) {
                Cell* swap = tmp->next;
                tmp->next = tmp->prev;
                tmp->prev = swap;
                tmp = swap;
            }
            tmp = head;
            head = tail;
            tail = tmp;
        }

        void freeContainer() {
            while (! isEmpty()) {
                removeFirst();
            }
        }

        ~Container() {
            freeContainer();
        }

        // manual cleaning
        void clear() { 
            freeContainer(); 
        }

    private:
        int len = 0;
        Cell* head = nullptr;
        Cell* tail = nullptr;
};

