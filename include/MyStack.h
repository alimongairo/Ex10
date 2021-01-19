// Copyright 2021 by idpas
#ifndef INCLUDE_MYSTACK_H_
#define INCLUDE_MYSTACK_H_

template <typename T>

class MyStack {
 private:
    unsigned int size;
    unsigned int head = 0;
    T* value;

 public:
    explicit MyStack(unsigned int new_size) {
        size = new_size;
        value = new T[size];
    }

    MyStack(const MyStack& tmp) {
        size = tmp.size;
        head = tmp.head;
        value = new T[size];
        for (unsigned int i = 0; i < head; ++i)
            value[i] = tmp.value[i];
    }

    ~MyStack() {
        delete value;
    }

    T get() const {
        return value[head - 1];
    }

    T pop() {
        head--;
        return value[head];
    }

    void push(T num) {
        value[head] = num;
        head++;
    }

    bool isFull() const {
        if (head == size)
            return true;
        else
            return false;
    }

    bool isEmpty() const {
        if (head == 0)
            return true;
        else
            return false;
    }
};

#endif  // INCLUDE_MYSTACK_H_
