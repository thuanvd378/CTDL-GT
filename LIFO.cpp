#include <iostream>
using namespace std;
const int MAX = 70;
struct Book {
    int maSo;
    char tenSach[100];
    long donGia;
};
template <class T>
struct Stack {
    T data[MAX];
    int size;
};
template <class T>
void initStack(Stack<T> &S) {
    S.size = 0;
}
template <class T>
int isEmpty(Stack<T> &S) {
    return (S.size == 0);
}

template <class T>
int isFull(Stack<T> &S) {
    return (S.size == MAX);
}
template <class T>
void push(Stack<T> &S, T x) {
    if (isFull(S)) {
        printf("\n Ngan xep day");
        return;
    }
    S.data[S.size] = x;
    S.size++;
}

template <class T>
T pop(Stack<T> &S) {
    if (isEmpty(S)) {
        printf("\n Ngan xep rong");
    }
    S.size--;
    return S.data[S.size];
}

template <class T>
void hienThi(Stack<T> &S) {
    if (isEmpty(S)) {
        printf("\n Ngan xep rong");
        return;
    }
    for (int i = 0; i < S.size; i++) {
        cout << "Ma so: " << S.data[i].maSo << ", Ten sach: " << S.data[i].tenSach << ", Don gia: " << S.data[i].donGia << endl;
    }
}
template <class T>
long tinhDonGiaTrungBinh(Stack<T> &S) {
    if (isEmpty(S)) {
        cout << "\n Ngan xep rong, khong the tinh don gia trung binh." << endl;
        return 0;
    }
    long tongDonGia = 0;
    for (int i = 0; i < S.size; i++) {
        tongDonGia += S.data[i].donGia;
    }
    return tongDonGia / S.size;
}
template <class T>
void peek(Stack<T> &S) {
    return S.data[S.size-1];
}
int main() {
    Stack<Book> S;
    initStack(S);
    Book book1 = {1, "Lap Trinh C", 100000};
    Book book2 = {2, "Cau Truc Du Lieu", 150000};
    Book book3 = {3, "Giai Thuat", 200000};
    push(S, book1);
    push(S, book2);
    push(S, book3);
    hienThi(S);

    cout << "\nDon gia trung binh cua cac cuon sach: " << tinhDonGiaTrungBinh(S) << endl;

    return 0;
}
