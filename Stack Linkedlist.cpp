#include <iostream>
#include <string>
using namespace std;

struct Node {
    int info;
    Node* next;
};
typedef Node* PNode;
typedef Node* Stack;


void initStack(Stack& stack) {
    stack = NULL;
}


int isEmpty(Stack stack) {
    return (stack == NULL);
}

void push(Stack& stack, int k) {
    PNode q = new Node;
    q->info = k;
    q->next = stack;
    stack = q;
}

int pop(Stack& stack) {
    if (isEmpty(stack)) {
        cout << "ds rong" << endl;
        return -1;
    }
    PNode temp = stack;
    int value = temp->info;
    stack = stack->next;
    delete temp;
    return value;
}


int top(Stack stack) {
    if (isEmpty(stack)) {
        cout << "ds rong" << endl;
        return -1;
    }
    return stack->info;
}


void hienThi(Stack stack) {
    if (isEmpty(stack)) {
        cout << "ds rong" << endl;
        return;
    }
    cout << "Ngăn xếp: ";
    PNode ptr = stack;
    while (ptr != NULL) {
        cout << ptr->info << " ";
        ptr = ptr->next;
    }
    cout << endl;
}


int main() {
    Stack s;
    initStack(s);
    push(s, 11);
    push(s, 22);
    push(s, 33);
    push(s, 44);
    hienThi(s);

    cout << "Phần tử đỉnh: " << top(s) << endl;

    cout << "Pop: " << pop(s) << endl;
    hienThi(s);


    push(s, 55);
    hienThi(s);


    cout << "Pop: " << pop(s) << endl;
    cout << "Pop: " << pop(s) << endl;
    hienThi(s);

    return 0;
}
