#include <iostream>
using namespace std;
struct TreeNode {
    int infor;
    TreeNode* LP, *RP;
};
TreeNode* createTreeNode(int data) {
    TreeNode* newTreeNode = new TreeNode;
    newTreeNode ->infor = data;
    newTreeNode->LP = NULL;
    newTreeNode -> RP = NULL;
    return newTreeNode;
}
struct QueueNode {
    TreeNode * treeNode;
    QueueNode* next;
};
struct Queue {
    QueueNode *front;
    QueueNode *rear;
};
void initQueue(Queue& q) {
    q.front = NULL;
    q.rear = NULL;
}
void enQueue(Queue& q, TreeNode * treeNode) {
    QueueNode * newNode = new QueueNode;
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q.front == NULL) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}
TreeNode* deQueue(Queue &q) {
    if (q.front == NULL) return NULL;
    QueueNode *temp = q.front;
    q.front = q.front ->next;
    TreeNode* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}
void builTreeFromArray(TreeNode*& root, int arr[], int size) {
    if (size == 0) return;
    TreeNode *newNode = createTreeNode(arr[0]);
    root = newNode;
    Queue q;
    initQueue(q);
    enQueue(q,root);
    int i = 1;
    while (i < size) {
        TreeNode* current = deQueue(q);
        if (i < size) {
            current->LP = createTreeNode(arr[i]);
            i++;
            enQueue(q,current->LP);
        }
        if (i < size) {
            current->RP = createTreeNode(arr[i]);
            i++;
            enQueue(q,current->RP);
        }
    }
}
void hienThi(TreeNode *node) {
    if (node != NULL) {
        printf("%d ",node->infor);
        hienThi(node->LP);
        hienThi(node->RP);
    }
}
int tinhTong(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->infor + tinhTong(node->LP) + tinhTong(node->RP);
}
TreeNode* searchTreeNode(TreeNode * root ,int data) {
    if (root == NULL) {
        return NULL;
    }
    if (root -> infor == data) return root;
    TreeNode* temp = searchTreeNode(root->LP,data);
    if (temp != NULL) {
        return temp;
    }
    return searchTreeNode(root->RP, data);
}
int tinhChieuCao(TreeNode* node) {
    if (node == NULL) {
        return -1;
    }
    int leftHeight = tinhChieuCao(node->LP);
    int rightHeight = tinhChieuCao(node->RP);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
int main() {
    TreeNode * root = NULL;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    builTreeFromArray(root,a,10);
    hienThi(root);
    cout << endl << tinhTong(root);
    cout << endl << tinhChieuCao(root);
    return 0;
}
