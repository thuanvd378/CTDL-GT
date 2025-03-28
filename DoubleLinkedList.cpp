#include <iostream>
using namespace std;
struct Node {
    int infor;
    Node* next;
    Node* prev;
};
struct DLinkedList {
    Node* l;
    Node* r;
};
void initDLinkedList(DLinkedList& dl) {
    dl.l = NULL;
    dl.r = NULL;
}
int isEmpty(DLinkedList dl) {
    return (dl.l == NULL);
}
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->infor = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void insertBegin(DLinkedList& dl, int data) {
    Node* temp = createNode(data);
    if (isEmpty(dl)) {
        dl.l = temp;
        dl.r = temp;
        return;
    }
    temp->next = dl.l;
    dl.l->prev = temp;
    dl.l = temp;
}
void insertBefore(DLinkedList& dl, int data, Node* p) {
    Node* temp = createNode(data);
    if (isEmpty(dl)) {
        dl.l = temp;
        dl.r = temp;
        return;
    }
    if (p == NULL) {
        cout << "\n Phan tu p khong ton tai";
        return;
    }
    if (p == dl.l) { //Neu p la phan tu dau tien
        temp->next = p;
        p->prev = temp;
        dl.l = temp;
        return;
    }
    temp->next = p;
    temp->prev = p->prev;
    p->prev->next = temp;
    p->prev = temp;
}
void insertAfter(DLinkedList& dl, int data, Node*p) {
    Node* temp = createNode(data);
    if (isEmpty(dl)) {
        dl.l = temp;
        dl.r = temp;
        return;
    }
    if (p == NULL) {
        cout << "\n Phan tu p khong ton tai";
        return;
    }
    if (p == dl.r) {
        p->next = temp;
        temp->prev = p;
        dl.r = temp;
        return;
    }
    temp->next = p->next;
    temp->prev = p;
    p->next = temp;
    temp->next->prev = temp;
}
void deleteBegin(DLinkedList& dl) {
    if (isEmpty(dl)) {
        return;
    }
    Node* temp = dl.l;
    dl.l = temp->next;
    dl.l->prev = NULL;
    delete temp;
}
int deleteBegin2(DLinkedList& dl) {
    if (isEmpty(dl)) {
        return -1;
    }
    Node* temp = dl.l;
    int data = temp->infor;
    dl.l = temp->next;
    dl.l->prev = NULL;
    delete temp;
    return data;
}
void deleteCurrentNode(DLinkedList& dl, Node* p) {
    if(isEmpty(dl)) {
        return;
    }
    if (p == NULL) {
        return;
    }
    if (p == dl.l) {
        dl.l = p->next;
        dl.l->prev = NULL;
        delete p;
        return;
    }
    if (p == dl.r) {
        dl.r = p->prev;
        dl.r->next = NULL;
        delete p;
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}
Node *search(DLinkedList dl, int data) {
    if(isEmpty(dl)) {
        return NULL;
    }
    Node* ptr = dl.l;
    while (ptr != NULL && ptr->infor != data) {
        ptr = ptr->next;
    }
    return ptr;
}
void hienThi(DLinkedList dl) {
    if (isEmpty(dl)) {
        cout << "ds rong";
        return;
    }
    Node* ptr = dl.l;
    while(ptr != NULL) {
        cout << ptr->infor << "\t";
        ptr = ptr->next;
    }
    cout << endl;
}
int main() {
    DLinkedList dl;
    initDLinkedList(dl);
    insertBegin(dl,11);
    insertBegin(dl,22);
    insertBegin(dl,33);
    hienThi(dl);
    Node*temp = search(dl,22);
    insertBefore(dl,44,temp);
    hienThi(dl);
    insertAfter(dl,55,temp);
    hienThi(dl);
}
