#include <iostream>
using namespace std;
/*
Hãy cài đặt cây nhị phân tìm kiếm, các khóa trên cây là các số nguyên với các thao tác (hàm):
khởi tạo cây rỗng
bổ sung phần tử vào cây
xóa phần tử khỏi cây
tìm kiếm phần tử trên cây
tính tổng giá trị các khóa trên cây
đếm tổng số lượng các nút trên cây
hiển thị giá trị tất cả các khóa trên cây.
Viết chương trình chính sử dụng cây trên
*/
struct  Node {
	int  key;
	Node* LP, * RP;
};

void initialBST (Node*& Root){
	Root = NULL;
}
// tim kiem phan tu x tren cay
Node* searchBST(Node* Root, int  x) {
	if (Root == NULL)  return  NULL;
	if (x == Root->key) return  Root;
	else   if (x < Root->key)  return  searchBST(Root->LP, x);
	else  return  searchBST(Root->RP, x);
}

//bo sung phan tu vao cay
void  insertBST(Node*& Root, int  x) {
	Node*  Q;
	if (Root == NULL) {		//khi cây rỗng
		Q = new Node; 		//tạo ra đỉnh mới
		Q->key = x;
		Q->LP = Q->RP = NULL;
		Root = Q;
	}
	else {
		if (x < Root->key)  insertBST(Root->LP, x);
		else if (x > Root->key)  insertBST(Root->RP, x);
		else return;
	}
}

//Xoa mot nut va sap lai cay
void  deleteNode(Node*& P) {	//Xóa nút P & sắp lại cây
	Node* Q;
	Node* R;
	if (P->LP == NULL) {	//Xóa nút chỉ có cây con phải
		Q = P;
		P = P->RP;
	}
	else	if (P->RP == NULL) 	//Xóa nút chỉ có cây con trái
	{
		Q = P;
		P = P->LP;
	}
	else {		 	//Xóa nút có 2 cây con
		Q = P->LP;
		if (Q->RP == NULL) {
			P->key = Q->key;
			P->LP = Q->LP;
		}
		else {
			do {		//Dùng R để lưu parent của Q
				R = Q;
				Q = Q->RP;
			} while (Q->RP != NULL);
			P->key = Q->key; 	//Lấy giá trị ở Q đưa lên
			R->RP = Q->LP;	//Chuyển con của Q lên vị trí Q
		}
	}
	delete  Q;			//Xoá Q
}

// Xoa nut tren cay
void  deleteBST(Node*& Root, int  x) {
	if (Root != NULL) {
		if (x < Root->key)  deleteBST(Root->LP, x);
		else  if (x > Root->key)  deleteBST(Root->RP, x);
		else  deleteNode(Root);		//Xoá gốc của cây
	}
}

//tinh tong khoa tren cay - duyet cay theo thu tu sau
int  sumBST(Node* Root) {

	if (Root == NULL) return 0;
	int sumLeftBST = sumBST(Root->LP);
	int sumRightBST = sumBST(Root->RP);
	return sumLeftBST + sumRightBST + Root->key;
	//return sumBST(Root->LP) + Root->key + sumBST(Root->RP);
}


//Dem so phan tu tren cay - Duyet cay theo thu tu giua
int countTree(Node* Root) {
	if (Root == NULL)
		return 0;
	else
		return countTree(Root->LP) + 1 + countTree(Root->RP);
}

//Hien thi cac nut tren cay - duyet cay theo thu tu truoc
void  displayBST(Node* Root) {
	if (Root == NULL) return;
	cout << Root->key << "\t";
	displayBST(Root->LP);
	displayBST(Root->RP);
	}

//check cay nhi phan suy bien lech trai
bool checkLeftDegenerateBTree(Node* Root)
{
	// check if node is NULL or is a leaf node
	if (Root == NULL || (Root->LP == NULL &&
		Root->RP == NULL))
		return true;

	// check if node has two children if
	// yes, return false
	if (Root->LP && Root->RP)
		return false;
	else if (Root->LP)
		return checkLeftDegenerateBTree(Root->LP);
	return false;
}

//check cay nhi phan suy bien lech phai
bool checkRightDegenerateBTree(Node* Root)
{
	// check if node is NULL or is a leaf node
	if (Root == NULL || (Root->LP == NULL &&
		Root->RP == NULL))
		return true;

	// check if node has two children if
	// yes, return false
	if (Root->LP && Root->RP)
		return false;
	else if (Root->RP)
		return checkRightDegenerateBTree(Root->RP);
	return false;
}

int main()
{
	Node* Root;
	initialBST(Root);
	insertBST(Root, 10);
	insertBST(Root, 18);
	insertBST(Root, 21);
	//insertBST(Root, 6);
	//insertBST(Root, 8);
	displayBST(Root);
	cout << "\n" << sumBST(Root) << "\n";
	cout << "\n" << countTree(Root) << "\n";
	cout << "\n" << checkRightDegenerateBTree(Root);
	//deleteBST(Root, 6);
	//displayBST(Root);
}
