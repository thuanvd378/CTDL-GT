#include <iostream>
using namespace std;
struct Node {
    int infor;
    Node* next;
};
struct CircleLinkedList {
    Node* last;
};
void initCircleLinkedList(CircleLinkedList* cl) {
    cl->last = NULL;
}
void insertBegin(CircleLinkedList* cl, int data) {
    Node* newNode = new Node;
    newNode-> infor = data;
    if (cl->last == NULL) {
        cl->last = newNode;
        cl->last->next = newNode;
        return;
    }
    newNode->next = cl->last->next;
    cl->last->next = newNode;
}
void insertAfter(CircleLinkedList* cl, int data, Node* p) {
    Node* newNode = new Node;
    newNode->infor = data;
    if (cl->last == NULL) {
        return;
    }
    if (p == NULL) {
        return;
    }
    if (p == cl->last) {
        newNode->next = p;
        cl->last = newNode;
        cl->last->next = p;
        return;
    }
    newNode->next = p->next;
    p->next = newNode;
}
void hienThi(CircleLinkedList* cl) {
    if (cl->last == NULL) {
        cout << "\n ds rong";
        return;
    }
    Node* ptr = cl->last->next;
    while (ptr != cl->last) {
        cout << ptr->infor << "\t";
        ptr = ptr->next;
    }
    cout << cl->last->infor;
}
int main() {
    CircleLinkedList cl;
    initCircleLinkedList(&cl);
    insertBegin(&cl,11);
    insertBegin(&cl,22);
    insertBegin(&cl,33);
    insertBegin(&cl,44);
    insertBegin(&cl,55);
    hienThi(&cl);

}
