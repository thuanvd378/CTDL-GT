#include <iostream>
#include <string>
using namespace std;
struct Node {
    int info;
    Node* next;
};
typedef Node* PNode;
typedef Node* LinkedList;
void initList(LinkedList& list) {
    list = NULL;
}
int isEmpty(LinkedList list) {
    return (list == NULL);
}
void insertBegin(LinkedList& list, int k) {
    PNode q = new Node;
    q->info = k;
    q->next = list;
    list = q;
}
void sortLinkedList(LinkedList& list) {
    if (isEmpty(list)) {
        cout << "\n ds rong!";
        return;
    }
    PNode ptr = list;
    int temp;
    while (ptr != NULL) {
        PNode ptr1 = ptr->next;
        while (ptr1 != NULL) {
            if (ptr->info > ptr1->info) {
                temp = ptr->info;
                ptr->info = ptr1->info;
                ptr1->info = temp;
            }
            ptr1 = ptr1->next;
        }
        ptr = ptr->next;
    }
}
PNode search(LinkedList list, int k) {
    PNode ptr = list;
    while (ptr != NULL ) {
        if (ptr->info == k) {
            return ptr;
        } else
            ptr = ptr->next;
    }
    return NULL;
}
void insertAfter(LinkedList& list,int k, PNode p) {
    PNode q = new Node;
    q->info = k;
    if (isEmpty(list)) {
        list = q;
        q->next = NULL;
        return;
    }
    if (p == NULL) {
        return;
    }
    q->next = p->next;
    p->next = q;
}
void insertBefore1(LinkedList& list,int k, PNode p) {
    PNode q = new Node;
    q->info = k;
    if (isEmpty(list)) {
        list = q;
        q->next = NULL;
        return;
    }
    if (p == NULL) {
        return;
    }
    PNode ptr = list;
    while(ptr -> next != p) {
        ptr = ptr->next;
    }
    q->next = ptr->next;
    ptr->next = q;
}
void insertBefore2(LinkedList& list,int k, PNode p) {
    PNode q = new Node;
    q->info = k;
    if (isEmpty(list)) {
        list = q;
        q->next = NULL;
        return;
    }
    if (p == NULL) {
        return;
    }
    q->info = p->info;
    p->info = k;
    q->next = p->next;
    p->next = q;
}
void deleteBegin(LinkedList& list) {
    Node*temp = list;
    if (isEmpty(list)) {
        cout << "ds rong";
        return;
    }
    if (list->next == NULL) {
        list = NULL;
        delete temp;
        return;
    }
    list = list->next;
    delete temp;
}
int deleteBegin2(LinkedList& list) {
    Node*temp = list;
    int x = temp->info;
    if (isEmpty(list)) {
        cout << "ds rong";
        return -1;
    }
    if (list->next == NULL) {
        list = NULL;
        delete temp;
        return x;
    }
    list = list->next;
    delete temp;
    return x;
}
void deleteCurrent(LinkedList& list, Node* p) {
    if (isEmpty(list)) {
        cout << "\n ds rong";
        return;
    }
    if (p == NULL) {
        cout << "\n Khong ton tai phan tu can xoa";
        return;
    }

    if (p == list) {
        list = list->next;
        delete p;
        return;
    }

    Node* prev = list;
    while (prev != NULL && prev->next != p) {
        prev = prev->next;
    }

    if (prev == NULL) {
        cout << "\n Node p khong thuoc danh sach";
        return;
    }
    prev->next = p->next;
    delete p;
}
void deleteEnd(LinkedList& list) {
    if (isEmpty(list)) {
        cout << "\nDanh sach rong!";
        return;
    }

    if (list->next == NULL) {
        delete list;
        list = NULL;
        return;
    }

    Node* prev = list;
    Node* last = list->next;

    while (last->next != NULL) {
        prev = prev->next;
        last = last->next;
    }

    prev->next = NULL;
    delete last;
}
void tinhGiaTriTrungBinh(LinkedList list) {
    cout << endl;
    if (isEmpty(list)) {
        cout << "\n ds rong!";
        return;
    }
    int result = 0;
    int num = 0;
    PNode ptr = list;
    while (ptr != NULL) {
        result += ptr->info;
        num++;
        ptr = ptr->next;
    }
    cout << "Gia tri trung binh cua day : " << result / num;
}
LinkedList connectLinkedList(LinkedList l1, LinkedList l2) {
    if (isEmpty(l1) && isEmpty(l2)) {
        cout << "\n ds rong!";
        return NULL;
    }
    PNode ptr;
    ptr = l1;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr ->next = l2;
    return l1;
}
LinkedList connectLinkedListPosition(LinkedList l1, LinkedList l2, int t) {
    if (isEmpty(l1) && isEmpty(l2)) {
        cout << "\n ds rong!";
        return NULL;
    }
    if (t == 0) {
        return connectLinkedList(l2,l1);
    } else {
        PNode ptr,temp;
        ptr = l1;
        int i = 0;
        while (i != t-1) {
            ptr = ptr->next;
            i++;
        }
        temp = ptr->next;
        ptr ->next = l2;
        while(ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
        return l1;
    }
}
void hienThi(LinkedList list) {
    cout << "\nDanh sach gom: ";
    if (isEmpty(list)) {
        cout << "rong!";
        return;
    }
    PNode ptr = list;
    while (ptr != NULL) {
        cout << ptr->info << " ";
        ptr = ptr->next;
    }
}
int main() {
    LinkedList l;
    initList(l);
    insertBegin(l,11);
    insertBegin(l,22);
    insertBegin(l,33);
    insertBegin(l,44);
    PNode p = search(l,33);
    insertAfter(l,77,p);
    insertBefore2(l,88,p);
    deleteBegin(l);
    hienThi(l);
    tinhGiaTriTrungBinh(l);
    deleteCurrent(l,p);
    hienThi(l);
}
