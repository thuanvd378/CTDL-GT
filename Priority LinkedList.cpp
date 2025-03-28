#include <iostream>
using namespace std;

struct Element {
    int value;
    int priority;
};

struct Queue {
    Element* arr;
    int front;
    int rear;
    int size;
};

void initQueue(Queue& qe, int s) {
    qe.size = s;
    qe.arr = new Element[s];
    qe.front = -1;
    qe.rear = -1;
}

int isEmpty(Queue qe) {
    return qe.front == -1;
}

int isFull(Queue qe) {
    return (qe.rear + 1) % qe.size == qe.front;
}

void enQueue(Queue& qe, int value, int priority) {
    if (isFull(qe)) {
        cout << "Hang doi day, khong the them phan tu." << endl;
        return;
    }
    Element newElement = {value, priority};
    if (isEmpty(qe)) {
        qe.front = 0;
        qe.rear = 0;
        qe.arr[0] = newElement;
    } else {
        int i = qe.rear;
        while (i != qe.front - 1 && qe.arr[(i + qe.size - 1) % qe.size].priority > priority) {
            qe.arr[(i + 1) % qe.size] = qe.arr[i];
            i = (i + qe.size - 1) % qe.size;
        }
        int pos = (i + 1) % qe.size;
        qe.arr[pos] = newElement;
        if (pos == (qe.rear + 1) % qe.size) {
            qe.rear = (qe.rear + 1) % qe.size;
        }
    }
}

void deQueue(Queue& qe) {
    if (isEmpty(qe)) {
        cout << "Hang doi rong, khong the lay phan tu." << endl;
        return;
    }
    if (qe.front == qe.rear) {
        qe.front = -1;
        qe.rear = -1;
    } else {
        qe.front = (qe.front + 1) % qe.size;
    }
}

void hienThi(Queue qe) {
    if (isEmpty(qe)) {
        cout << "Hang doi rong." << endl;
        return;
    }
    cout << "Cac phan tu trong hang doi: ";
    int i = qe.front;
    while (true) {
        cout << "(" << qe.arr[i].value << ", " << qe.arr[i].priority << ")\t";
        if (i == qe.rear) break;
        i = (i + 1) % qe.size;
    }
    cout << endl;
}

void giaiPhong(Queue& qe) {
    delete[] qe.arr;
    qe.arr = nullptr;
    qe.front = -1;
    qe.rear = -1;
    qe.size = 0;
}

int main() {
    Queue pq;
    initQueue(pq, 5);

    enQueue(pq, 10, 3);
    enQueue(pq, 20, 1);
    enQueue(pq, 30, 2);
    enQueue(pq, 40, 4);
    hienThi(pq);

    deQueue(pq);
    hienThi(pq);

    enQueue(pq, 50, 2);
    hienThi(pq);

    giaiPhong(pq);

    return 0;
}
