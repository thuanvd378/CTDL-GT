#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>// xử lý chữ in hoa , thường
#include<windows.h>
#include<string.h>
#include <time.h>
#define MAX_NAME 100
#define MAX_PHONE 100
#define MAX_CCCD 100
#define MAX_DATE 100
#define MAX_SERVICE 100
#define MAX_USER 100
#define MAX_PASSWORD 100
//===========================================================BACKEND===========================================================
//Hàm bổ trợ
char* layThoiGian() {
    static char date[11]; // Định dạng dd/mm/yyyy (10 ký tự + 1 ký tự null)
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);

    sprintf(date, "%02d/%02d/%04d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    return date;
}
void sleep_fake(int n) {
    for (int i = 1;i <= n;i++) {
        for(long long j = 1;j <= 2000000000;j++) {
            //DELAY TIME
        }
    }
}
void eraseLines(int count) {// xóa count dòng
    if (count > 0) {
        printf("\x1b[2k");// xóa dòng hiện tại
        for (int i = 1; i < count; i++) {
            printf("\x1b[1A"); // Di chuyển con trỏ lên một dòng
            printf("\x1b[2K"); // Xóa nội dung trên dòng
        }
        printf("\r");
    }
}
int convert(char *s){ // biến chuỗi số thành số nguyên
    int result = 0;
    for(int i = 0; i < strlen(s); i++){
        result = result*10+((int)s[i]-48);
    }
    return result;
}
void UPCASE(char *s) // biến thành chuỗi in hoa
{
    for (size_t i = 0; s[i] != '\0'; ++i)
        s[i] = (char)toupper((unsigned char)s[i]);
}
//====================DỊCH VỤ====================
struct Node {
    int   maDichVu;
    char  tenDichVu[MAX_SERVICE];  /* lưu cả chuỗi tên */
    double giaTien;
    struct Node *next;
};

typedef Node* PNode;
typedef Node* DanhSachDV;

void initListDV(DanhSachDV &list)        { list = NULL; }
int isEmpty(DanhSachDV  list)         { return list == NULL; }

void themDV(DanhSachDV &list, int id, const char *name, double price)
{
    PNode q = (PNode)malloc(sizeof(Node));
    q->maDichVu = id;

    strncpy(q->tenDichVu, name, MAX_SERVICE);
    q->tenDichVu[MAX_SERVICE - 1] = '\0';

    q->giaTien = price;

    q->next = list;
    list    = q;
}

PNode timKiemDV(DanhSachDV list, int k)
{
    for (PNode p = list; p != NULL; p = p->next)
        if (p->maDichVu == k) return p;
    return NULL;
}

PNode timKiemDVTen(DanhSachDV list, const char *keyword)
{
    if (list == NULL || keyword == NULL) return NULL;
    char keyUp[MAX_SERVICE];
    strncpy(keyUp, keyword, MAX_SERVICE);
    keyUp[MAX_SERVICE-1] = '\0';
    UPCASE(keyUp);
    for (PNode p = list; p != NULL; p = p->next)
    {
        char nameUp[MAX_SERVICE];
        strncpy(nameUp, p->tenDichVu, MAX_SERVICE);
        nameUp[MAX_SERVICE-1] = '\0';
        UPCASE(nameUp);

        if (strstr(nameUp, keyUp) != NULL)
            return p;
    }
    return NULL;
}

void suaDV(PNode q, const char *name, double price)
{
    if (q == NULL) return;

    strncpy(q->tenDichVu, name, MAX_SERVICE);
    q->tenDichVu[MAX_SERVICE - 1] = '\0';
    q->giaTien = price;
}

void xoaDV(DanhSachDV &list, PNode p)
{
    if (isEmpty(list) || p == NULL) return;

    if (p == list)
        list = list->next;
    else {
        PNode prev = list;
        while (prev && prev->next != p) prev = prev->next;
        if (!prev) return;
        prev->next = p->next;
    }
    free(p);
}

void hienThiDV(DanhSachDV list)
{
    printf("--------------------------------------------------\n");
    for (PNode p = list; p != NULL; p = p->next)
        printf("Ma: %-5d | Ten: %-25s | Gia: %.0lf VND\n",
               p->maDichVu, p->tenDichVu, p->giaTien);
    printf("--------------------------------------------------\n");
}
//====================BỆNH NHÂN====================
//1. Định nghĩa danh sách liên kết đơn và hàng đợi
struct NodeBN {
    int   STT;                                 // số thứ tự
    char  tenBenhNhan[MAX_NAME];               // tên bệnh nhân (chuỗi)
    int   tuoiBenhNhan;
    char  SDT[MAX_PHONE];                      // số điện thoại
    char  CCCD[MAX_CCCD];                      // căn cước
    char  tinhTrangBenh[MAX_NAME];             // mô tả bệnh
    char  lichKham[MAX_DATE];                  // ngày khám (dd/mm/yyyy)
    int   BHYT;                                // 1:có, 0:không
    Node *dichVu;                            // dịch vụ đã chọn
    struct NodeBN *next;                       // node kế tiếp
};
typedef NodeBN* TNode;
typedef NodeBN* DanhSachBN;
struct QueueBN {
    TNode front;
    TNode rear;
};
//2. Hàng đợi cho bệnh nhân
void initQueue(QueueBN& q) {
    q.front = q.rear = NULL;
}
bool isQueueEmpty(QueueBN q) {
    return (q.front == NULL);
}
void enqueueBN(QueueBN& q, TNode newBN) {
    newBN->next = NULL;
    if (isQueueEmpty(q)) {
        q.front = q.rear = newBN;
    } else {
        q.rear->next = newBN;
        q.rear = newBN;
    }
}
TNode dequeueBN(QueueBN& q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }
    TNode temp = q.front;
    q.front = q.front->next;
    if (q.front == NULL) {
        q.rear = NULL;
    }
    temp->next = NULL;
    return temp;
}
TNode peekQueue(const QueueBN &q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }
    return q.front;
}
QueueBN hangDoi;
//3. Danh sách liên kết đơn cho bệnh nhân
void initListBN(DanhSachBN& list) {
    list = NULL;
}
int isEmpty(DanhSachBN list) {
    return (list == NULL);
}
void themBN(DanhSachBN &list,
            int   STT2,
            const char *tenBenhNhan2,
            int   tuoiBenhNhan2,
            const char *SDT2,
            const char *CCCD2,
            const char *tinhTrangBenh2,
            const char *lichKham2,
            int   BHYT2,
            Node *dichVu2)
{
    TNode q = (TNode)malloc(sizeof(NodeBN));

    q->STT          = STT2;
    strncpy(q->tenBenhNhan, tenBenhNhan2, MAX_NAME);
    q->tenBenhNhan[MAX_NAME-1] = '\0';

    q->tuoiBenhNhan = tuoiBenhNhan2;

    strncpy(q->SDT,  SDT2,  MAX_PHONE);
    q->SDT[MAX_PHONE-1] = '\0';

    strncpy(q->CCCD, CCCD2, MAX_CCCD);
    q->CCCD[MAX_CCCD-1] = '\0';

    strncpy(q->tinhTrangBenh, tinhTrangBenh2, MAX_NAME);
    q->tinhTrangBenh[MAX_NAME-1] = '\0';

    strncpy(q->lichKham, lichKham2, MAX_DATE);
    q->lichKham[MAX_DATE-1] = '\0';

    q->BHYT  = BHYT2;
    q->dichVu = dichVu2;
    q->next = list;
    list    = q;
    enqueueBN(hangDoi, q);
}
TNode timKiemBNTen(DanhSachBN list, const char *name)
{
    char key[MAX_NAME];
    strncpy(key, name, MAX_NAME);
    key[MAX_NAME-1] = '\0';
    UPCASE(key);

    for (TNode p = list; p; p = p->next) {
        char tmp[MAX_NAME];
        strncpy(tmp, p->tenBenhNhan, MAX_NAME);
        tmp[MAX_NAME-1] = '\0';
        UPCASE(tmp);

        if (strcmp(tmp, key) == 0)
            return p;
    }
    return NULL;
}
TNode timKiemBNSDT(DanhSachBN list, const char *SDTtemp)
{
    for (TNode ptr = list; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->SDT, SDTtemp) == 0)
            return ptr;
    return NULL;
}
void suaBN(DanhSachBN &list,
           TNode       q,
           int         STT2,
           const char *tenBenhNhan2,
           int         tuoiBenhNhan2,
           const char *SDT2,
           const char *CCCD2,
           const char *tinhTrangBenh2,
           const char *lichKham2,
           int         BHYT2,
           Node     *dichVu2)
{
    if (isEmpty(list) || q == NULL)  return;

    q->STT = STT2;

    strncpy(q->tenBenhNhan, tenBenhNhan2, MAX_NAME);
    q->tenBenhNhan[MAX_NAME - 1] = '\0';

    q->tuoiBenhNhan = tuoiBenhNhan2;

    strncpy(q->SDT, SDT2, MAX_PHONE);
    q->SDT[MAX_PHONE - 1] = '\0';

    strncpy(q->CCCD, CCCD2, MAX_CCCD);
    q->CCCD[MAX_CCCD - 1] = '\0';

    strncpy(q->tinhTrangBenh, tinhTrangBenh2, MAX_NAME);
    q->tinhTrangBenh[MAX_NAME - 1] = '\0';

    strncpy(q->lichKham, lichKham2, MAX_DATE);
    q->lichKham[MAX_DATE - 1] = '\0';

    q->BHYT   = BHYT2;
    q->dichVu = dichVu2;
}
void xoaBN(DanhSachBN& list, NodeBN* p) {
    if (isEmpty(list)) {
        return;
    }
    if (p == NULL) {
        return;
    }

    if (p == list) {
        list = list->next;
        delete p;
        return;
    }
    NodeBN* prev = list;
    while (prev != NULL && prev->next != p) {
        prev = prev->next;
    }

    if (prev == NULL) {
        return;
    }
    prev->next = p->next;
    delete p;
}
void hienThiMotBN(DanhSachBN& list, TNode q) {
    printf("--------------------------------------------------\n");
    if (isEmpty(list) || q == NULL)  printf("Danh sach rong\n");
    printf("STT : %d\n",q->STT);
    printf("Ten benh nhan : %s\n",q->tenBenhNhan);
    printf("Tuoi benh nhan : %d\n",q->tuoiBenhNhan);
    printf("SDT : %s\n",q->SDT);
    printf("CCCD : %s\n",q->CCCD);
    printf("Tinh trang benh : %s\n",q->tinhTrangBenh);
    printf("Lich kham : %s\n",q->lichKham);
    printf("Dich vu : %s\n",q->dichVu->tenDichVu);
    if (q->BHYT) printf("BHYT : Co\n");
    else printf("BHYT : Khong\n");
    printf("--------------------------------------------------\n");
}
void hienThiBN(DanhSachBN& list) {
    for (TNode q = list; q != NULL; q = q->next) {
        printf("--------------------------------------------------\n");
        if (isEmpty(list) || q == NULL){
            printf("Danh sach rong\n");
            return;
        }
        printf("STT : %d\n",q->STT);
        printf("Ten benh nhan : %s\n",q->tenBenhNhan);
        printf("Tuoi benh nhan : %d\n",q->tuoiBenhNhan);
        printf("SDT : %s\n",q->SDT);
        printf("CCCD : %s\n",q->CCCD);
        printf("Tinh trang benh : %s\n",q->tinhTrangBenh);
        printf("Lich kham : %s\n",q->lichKham);
        printf("Dich vu : %s\n",q->dichVu->tenDichVu);
        if (q->BHYT) printf("BHYT : Co\n");
        else printf("BHYT : Khong\n");
        printf("--------------------------------------------------\n");
    }
}
//====================HÓA ĐƠN====================
struct QueueHD {
    TNode front;
    TNode rear;
};
void initQueueHD(QueueHD& q) {
    q.front = q.rear = NULL;
}
bool isQueueHDEmpty(QueueHD q) {
    return (q.front == NULL);
}
void enqueueHD(QueueHD& q, TNode newHD) {
    newHD->next = NULL;
    if (isQueueHDEmpty(q)) {
        q.front = q.rear = newHD;
    } else {
        q.rear->next = newHD;
        q.rear = newHD;
    }
}
TNode dequeueHD(QueueHD& q) {
    if (isQueueHDEmpty(q)) {
        return NULL;
    }
    TNode temp = q.front;
    q.front = q.front->next;
    if (q.front == NULL) {
        q.rear = NULL;
    }
    temp->next = NULL; // tách khỏi hàng đợi
    return temp;
}
TNode peekQueueHD(const QueueHD &q) {
    if (isQueueHDEmpty(q)) {
        return NULL;
    }
    return q.front;
}
void hienThiHD(DanhSachBN& list, TNode q) {
    if (isEmpty(list) || q == NULL)  {
        printf("Khong co hoa don nao !\n");
        return;
    }
    printf("--------------------------------------------------\n");
    printf("STT : %d\n",q->STT);
    printf("Ten benh nhan : %s\n",q->tenBenhNhan);
    printf("Tuoi benh nhan : %d\n",q->tuoiBenhNhan);
    printf("SDT : %s\n",q->SDT);
    printf("CCCD : %s\n",q->CCCD);
    printf("Tinh trang benh : %s\n",q->tinhTrangBenh);
    printf("Lich kham : %s\n",q->lichKham);
    printf("Dich vu : %s\n",q->dichVu->tenDichVu);
    if (q->BHYT) printf("BHYT : Co\n");
    else printf("BHYT : Khong\n");
    printf("--------------------------------------------------\n");
    printf("Gia dich vu : %lf VND\n", q->dichVu->giaTien);
    if (q->BHYT) printf("Chiet khau BHYT : 50%% \n");
    printf("--------------------------------------------------\n");
    printf("TONG : %lf VND \n", (q->dichVu->giaTien) / ( q->BHYT ? 2.0 : 1.0 ));
}
QueueHD hangDoiHoaDon;
//===========================================================BACKEND===========================================================



//===========================================================FRONTEND==========================================================
void MENU(DanhSachBN& list, DanhSachDV& list2);
void quanLyBN(DanhSachBN& list, DanhSachDV& list2);
void quanLyDichVu(DanhSachBN& list, DanhSachDV& list2);
//===================Quản lý bệnh nhân===================
PNode chonDV(DanhSachDV list) {
    system("cls");
    int k;
    printf("================== CHON DICH VU ==================\n");
    printf("Danh sach dich vu : \n");
    if (isEmpty(list)) printf("Danh sach rong ! \n");
    else hienThiDV(list);
    printf("==================================================\n");
    printf("Vui long nhap ma dich vu : ");
    scanf("%d",&k);
    if (timKiemDV(list,k) != NULL) {
        return timKiemDV(list,k);
    } else {
        system("cls");

        printf("Nhap sai ma, vui long nhap lai");
        sleep_fake(2);
        return chonDV(list);
    }
}
void taoBN(DanhSachBN &list, DanhSachDV &list2)
{
    system("cls");
    printf("================= TAO BENH NHAN =================\n");
    if (isEmpty(list2)) {
        printf("Danh sach dich vu rong, khong the tao benh nhan ! \n");
        sleep_fake(2);
        quanLyBN(list,list2);
        return;
    }
    static int autoSTT = 1;
    int  STT2 = autoSTT++;
    char tenBenhNhan2[MAX_NAME];
    int  tuoiBenhNhan2;
    char SDT2[MAX_PHONE];
    char CCCD2[MAX_CCCD];
    char tinhTrangBenh2[MAX_NAME];
    int  BHYT2;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    printf("Ten benh nhan la : ");
    fgets(tenBenhNhan2, sizeof(tenBenhNhan2), stdin);
    tenBenhNhan2[strcspn(tenBenhNhan2, "\n")] = '\0';

    printf("Nhap tuoi benh nhan: ");
    scanf("%d", &tuoiBenhNhan2); getchar();

    printf("Nhap so dien thoai: ");
    fgets(SDT2, sizeof(SDT2), stdin);
    SDT2[strcspn(SDT2, "\n")] = '\0';

    printf("Nhap CCCD: ");
    fgets(CCCD2, sizeof(CCCD2), stdin);
    CCCD2[strcspn(CCCD2, "\n")] = '\0';

    printf("Trang thai cua benh nhan: ");
    fgets(tinhTrangBenh2, sizeof(tinhTrangBenh2), stdin);
    tinhTrangBenh2[strcspn(tinhTrangBenh2, "\n")] = '\0';

    printf("Co bao hiem y te ko (1 co 0 khong): ");
    scanf("%d", &BHYT2); getchar();
    themBN(list, STT2, tenBenhNhan2, tuoiBenhNhan2,
           SDT2, CCCD2, tinhTrangBenh2,
           layThoiGian(), BHYT2, chonDV(list2));
    system("cls");
    printf("\n>>> Them benh nhan thanh cong!\n");
    sleep_fake(2);
    system("cls");
    MENU(list,list2);
}
void xoaBN(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= XOA BENH NHAN =================\n");
    if (isEmpty(list)) {
        printf("Danh sach rong!\n");
        sleep_fake(2);
        quanLyBN(list,list2);
    }
    char sdt[MAX_PHONE];
    printf("Nhap SDT benh nhan can xoa: ");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    fgets(sdt, sizeof(sdt), stdin);
    sdt[strcspn(sdt, "\n")] = '\0';

    TNode p = timKiemBNSDT(list, sdt);
    if (!p) {
        printf("Khong tim thay benh nhan co SDT nay!\n");
        sleep_fake(2);
        return;
    }
    hienThiMotBN(list, p);
    printf("Ban co chac muon xoa benh nhan nay? (y/n): ");
    char confirm[8];
    fgets(confirm, sizeof(confirm), stdin);
    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        xoaBN(list, p);
        printf("\n>>> Da xoa benh nhan thanh cong!\n");
    } else {
        printf("\n>>> Da huy thao tac xoa!\n");
    }
    sleep_fake(2);
    MENU(list,list2);
}
void khamBN(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= KHAM BENH NHAN =================\n");
    printf("--------------- BENH NHAN DEN LUOT ---------------\n");
    hienThiMotBN(list,peekQueue(hangDoi));
    printf("--------------------------------------------------\n");
    int k;
    printf("Kham benh nhan khong ? ([0] la khong, [1] la co) : ");
    scanf("%d",&k);
    switch(k) {
        case 0:
            quanLyBN(list,list2);
        case 1:
            enqueueHD(hangDoiHoaDon,dequeueBN(hangDoi));
            system("cls");
            printf("\n>>> Da kham benh nhan, xin moi benh nhan tiep theo!\n");
            sleep_fake(2);
            quanLyBN(list,list2);
        default :
        system("cls");
        printf("Vui long nhap lai !");
        sleep_fake(2);
        khamBN(list,list2);
        break;
    }
}
void suaThongTinBN(DanhSachBN &list, DanhSachDV &list2)
{
    system("cls");
    printf("================= SUA BENH NHAN =================\n");

    if (isEmpty(list)) {
        printf("Danh sach rong!");
        sleep_fake(2);
        quanLyBN(list,list2);
        return;
    }
    char sdtKey[MAX_PHONE];
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {} // clear stdin
    printf("Nhap SDT benh nhan can sua: ");
    fgets(sdtKey, sizeof(sdtKey), stdin);
    sdtKey[strcspn(sdtKey, "\n")] = '\0';
    TNode p = timKiemBNSDT(list, sdtKey);
    if (!p) {
        printf("Khong tim thay benh nhan !\n");
        sleep_fake(2);
        quanLyBN(list, list2);
        return;
    }

    printf("=== SUA THONG TIN === (bo qua = giu nguyen)\n");
    char buf[128];
    char newTen[MAX_NAME];      strncpy(newTen, p->tenBenhNhan, MAX_NAME);
    int  newTuoi    = p->tuoiBenhNhan;
    char newSDT[MAX_PHONE];     strncpy(newSDT, p->SDT, MAX_PHONE);
    char newCCCD[MAX_CCCD];     strncpy(newCCCD, p->CCCD, MAX_CCCD);
    char newTinhTrang[MAX_NAME];strncpy(newTinhTrang, p->tinhTrangBenh, MAX_NAME);
    int  newBHYT    = p->BHYT;
    Node *newDV     = p->dichVu;

    printf("Ten [%s]: ", p->tenBenhNhan);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') { buf[strcspn(buf, "\n")] = '\0'; strncpy(newTen, buf, MAX_NAME); }
    printf("Tuoi [%d]: ", p->tuoiBenhNhan);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n')   newTuoi = atoi(buf);// chuyểnn chuỗi thành số nguyên
    printf("SDT [%s]: ", p->SDT);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') { buf[strcspn(buf, "\n")] = '\0'; strncpy(newSDT, buf, MAX_PHONE); newSDT[MAX_PHONE-1] = '\0';}
    printf("CCCD [%s]: ", p->CCCD);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') { buf[strcspn(buf, "\n")] = '\0'; strncpy(newCCCD, buf, MAX_CCCD); }
    printf("Tinh trang [%s]: ", p->tinhTrangBenh);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') { buf[strcspn(buf, "\n")] = '\0'; strncpy(newTinhTrang, buf, MAX_NAME); }
    printf("BHYT (1/0) [%d]: ", p->BHYT);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n')   newBHYT = atoi(buf);
    printf("Muon doi dich vu? (y/n): ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] == 'y' || buf[0] == 'Y')
        newDV = chonDV(list2);
    suaBN(list,
          p,
          p->STT,
          newTen,
          newTuoi,
          newSDT,
          newCCCD,
          newTinhTrang,
          p->lichKham,
          newBHYT,
          newDV);
    system("cls");
    printf(">>> Da cap nhat.\n");
    sleep_fake(2);
    quanLyBN(list,list2);
}

void timKiemBN(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= TIM KIEM BENH NHAN =================\n");
    if (isEmpty(list)) {
        printf("Danh sach rong!");
        sleep_fake(2);
        quanLyBN(list,list2);
    }
    int k,t;
    printf("Tim theo ten [0], tim theo so dien thoai [1] : ");
    scanf("%d", &k);
    getchar();
    printf("\n");
    switch(k) {
        case 0:
            char name[MAX_NAME];
            printf("Nhap ten benh nhan can tim kiem: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            getchar();
            printf("===========================================\n ");
            printf("Danh sach benh nhan can tim: \n");
            hienThiMotBN(list, timKiemBNTen(list,name));
            printf("===========================================\n ");
            printf("Go bat ky nut nao de quay lai : ");
            scanf("%d", &t);
            getchar();
            sleep_fake(1);
            quanLyBN(list,list2);
            break;
        case 1:
            char sdt[MAX_PHONE];
            printf("Nhap SDT benh nhan can tim kiem: ");
            fgets(sdt, sizeof(sdt), stdin);
            sdt[strcspn(sdt, "\n")] = '\0';
            printf("===========================================\n ");
            printf("Danh sach benh nhan can tim: \n");
            hienThiMotBN(list, timKiemBNSDT(list,sdt));
            printf("===========================================\n ");
            printf("Go bat ky nut nao de quay lai : ");
            scanf("%d", &t);
            getchar();
            sleep_fake(1);
            quanLyBN(list,list2);
            break;
        default :
        system("cls");
        printf("Vui long nhap lai !");
        sleep_fake(2);
        timKiemBN(list,list2);
        break;
    }
}
void thongKeBN(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    int k;
    printf("================= THONG KE BENH NHAN =================\n");
    hienThiBN(list);
    printf("======================================================\n");
    printf("Go bat ky nut nao de quay lai : ");
    scanf("%d", &k);
    getchar();
    sleep_fake(1);
    quanLyBN(list,list2);
}

void quanLyBN(DanhSachBN& list, DanhSachDV& list2) {
    int k;
    system("cls");
    printf("=============== QUAN LY BENH NHAN ===============\n");
    printf("1. Tao benh nhan moi\n");
    printf("2. Xoa benh nhan\n");
    printf("3. Kham benh nhan\n");
    printf("4. Sua thong tin benh nhan\n");
    printf("5. Tim kiem benh nhan\n");
    printf("6. Thong ke benh nhan\n");
    printf("7. Quay lai\n");
    printf("==================================================\n");
    printf("Vui long chon thao tac : ");
    scanf("%d",&k);
    switch(k) {
    case 1:
        taoBN(list, list2);
        break;
    case 2 :
        xoaBN(list,list2);
        break;
    case 3 :
        khamBN(list,list2);
        break;
    case 4 :
        suaThongTinBN(list,list2);
        break;
    case 5 :
        timKiemBN(list,list2);
        break;
    case 6:
        thongKeBN(list,list2);
        break;
    case 7:
        system("cls");
        MENU(list,list2);
        break;
    default :
        system("cls");
        printf("Vui long nhap lai !");
        sleep_fake(2);
        quanLyBN(list,list2);
        break;
    }
}
//====================Quản lý dịch vụ====================
void taoDV(DanhSachBN& list, DanhSachDV& list2) {
    system("cls");
    printf("================= TAO DICH VU =================\n");

    static int autoSTT = 1;
    int  STT2 = autoSTT++;
    char tenDichVu2[MAX_NAME];
    double  giaDichVu2;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    printf("Ten dich vu la : ");
    fgets(tenDichVu2, sizeof(tenDichVu2), stdin);
    tenDichVu2[strcspn(tenDichVu2, "\n")] = '\0';

    printf("Nhap gia dich vu : ");
    scanf("%lf", &giaDichVu2); getchar();

    themDV(list2, STT2, tenDichVu2, giaDichVu2);
    system("cls");

    printf("\n>>> Them dich vu thanh cong!\n");
    sleep_fake(2);
    system("cls");
    MENU(list,list2);
}
void xoaDV(DanhSachBN& list, DanhSachDV& list2) {
    system("cls");
    printf("================= XOA DICH VU =================\n");
    if (isEmpty(list2)) {
        printf("Danh sach dich vu rong!\n");
        sleep_fake(2);
        return;
    }
    hienThiDV(list2);
    int ma;
    printf("Nhap ma dich vu can xoa: ");
    scanf("%d", &ma); getchar();

    PNode p = timKiemDV(list2, ma);
    if (!p) {
        printf("Khong tim thay dich vu co ma nay!\n");
        sleep_fake(2);
        return;
    }

    for (TNode q = list; q != NULL; q = q->next) {
        if (q->dichVu && q->dichVu->maDichVu == ma) {
            printf("Khong the xoa! Co benh nhan dang su dung dich vu nay.\n");
            sleep_fake(2);
            return;
        }
    }
    printf("Ban co chac muon xoa dich vu nay? (y/n): ");
    char confirm[8];
    fgets(confirm, sizeof(confirm), stdin);
    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        system("cls");
        printf("\n>>> Da xoa dich vu!\n");
    } else {
        printf("\n>>> Da huy thao tac xoa.\n");
    }
    sleep_fake(2);
    quanLyDichVu(list, list2);
}
void suaDV(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= SUA DICH VU =================\n");
    if (isEmpty(list2)) {
        printf("Danh sach dich vu rong!\n");
        sleep_fake(2);
        return;
    }
    hienThiDV(list2);
    int ma;
    printf("Nhap ma dich vu can sua: ");
    scanf("%d", &ma); getchar();

    PNode p = timKiemDV(list2, ma);
    if (!p) {
        printf("Khong tim thay dich vu co ma nay!\n");
        sleep_fake(2);
        return;
    }
    printf("=== SUA THONG TIN === (bo qua = giu nguyen)\n");
    char buf[128];

    char   newTen[MAX_NAME];  strncpy(newTen, p->tenDichVu, MAX_NAME);
    double newGia            = p->giaTien;

    printf("Ten dich vu [%s]: ", p->tenDichVu);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strncpy(newTen, buf, MAX_NAME);
    }

    printf("Gia tien [%.0lf]: ", p->giaTien);
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n')
        newGia = atof(buf);
    suaDV(p, newTen, newGia);
    system("cls");
    printf(">>> Da cap nhat dich vu!\n");
    sleep_fake(2);
    quanLyDichVu(list, list2);
}
void timKiemDV(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= TIM KIEM DICH VU =================\n");
    if (isEmpty(list2)) {
        printf("Danh sach dich vu rong!\n");
        sleep_fake(2);
        return;
    }
    int k;
    printf("Tim theo ma [1] hay theo ten [2]: ");
    scanf("%d", &k); getchar();
    if (k == 1) {
        int ma;
        printf("Nhap ma dich vu: ");
        scanf("%d", &ma); getchar();
        PNode p = timKiemDV(list2, ma);
        if (p) {
            printf("Ket qua tim kiem:\n");
            printf("Ma: %-5d | Ten: %-25s | Gia: %.0lf VND\n", p->maDichVu, p->tenDichVu, p->giaTien);
        } else {
            printf("Khong tim thay dich vu co ma nay!\n");
        }
    } else if (k == 2) {
        char ten[MAX_NAME];
        printf("Nhap ten dich vu: ");
        fgets(ten, sizeof(ten), stdin);
        ten[strcspn(ten, "\n")] = '\0';
        PNode p = timKiemDVTen(list2, ten);
        if (p) {
            printf("Ket qua tim kiem:\n");
            printf("Ma: %-5d | Ten: %-25s | Gia: %.0lf VND\n", p->maDichVu, p->tenDichVu, p->giaTien);
        } else {
            printf("Khong tim thay dich vu co ma nay!\n");
        }
    } else {
        printf("Lua chon khong hop le!\n");
    }
    printf("\nNhan phim bat ky de quay lai...");
    getchar();
    quanLyDichVu(list, list2);
}
void danhSachDV(DanhSachBN &list, DanhSachDV &list2) {
    system("cls");
    printf("================= DANH SACH DICH VU =================\n");
    if (isEmpty(list2)) {
        printf("Danh sach dich vu rong!\n");
    } else {
        hienThiDV(list2);
    }
    int k;
    printf("\nNhan phim bat ky de quay lai...");
    scanf("%d", &k);
    getchar();
    quanLyDichVu(list, list2);
}

void quanLyDichVu(DanhSachBN& list, DanhSachDV& list2) {
    int k;
    system("cls");
    printf("================ QUAN LY DICH VU =================\n");
    printf("1. Tao dich vu moi\n");
    printf("2. Xoa dich vu\n");
    printf("3. Sua dich vu\n");
    printf("4. Tim kiem dich vu\n");
    printf("5. Danh sach dich vu\n");
    printf("6. Quay lai\n");
    printf("==================================================\n");
    printf("Vui long chon thao tac : ");
    scanf("%d",&k);
    switch(k) {
    case 1:
        taoDV(list,list2);
        break;
    case 2 :
        xoaDV(list, list2);
        break;
    case 3 :
        suaDV(list, list2);
        break;
    case 4 :
        timKiemDV(list, list2);
        break;
    case 5:
        danhSachDV(list, list2);
        break;
    case 6:
        system("cls");
        MENU(list,list2);
        break;
    default :
        system("cls");
        printf("Vui long nhap lai !");
        sleep_fake(2);
        quanLyDichVu(list,list2);
        break;
    }
}
//=====================Xuất hóa đơn======================
void xuatHoaDon(DanhSachBN& list, DanhSachDV& list2) {
    int k;
    system("cls");
    printf("======= HOA DON HIEN TAI =======\n");
    hienThiHD(list,peekQueueHD(hangDoiHoaDon));
    printf("================================\n");
    printf("Ban co muon xuat hoa don tren ? ([0] la khong, [1] la co) \n");
    scanf("%d",&k);
    switch(k) {
        case 0:
            sleep_fake(1);
            MENU(list,list2);
            break;
        case 1:
            dequeueHD(hangDoiHoaDon);
            printf("\n>>> Xuat hoa don thanh cong!\n");
            sleep_fake(2);
            MENU(list,list2);
            break;
        default :
        system("cls");
        printf("Vui long nhap lai !");
        sleep_fake(2);
        xuatHoaDon(list,list2);
        break;

    }
}
//==================Chương trình chính==================
void MENU(DanhSachBN& list, DanhSachDV& list2) {
    int k;
    system("cls");
    printf("==== CHUONG TRINH QUAN LY PHONG KHAM ====\n");
    printf("1. Quan ly benh nhan\n");
    printf("2. Quan ly dich vu\n");
    printf("3. Xuat hoa don\n");
    printf("4. Thoat chuong trinh \n");
    printf("==================================================\n");
    printf("Vui long chon thao tac : ");
    scanf("%d",&k);
    switch(k) {
    case 1:
        quanLyBN(list,list2);
        break;
    case 2 :
        quanLyDichVu(list,list2);
        break;
    case 3 :
        xuatHoaDon(list,list2);
        break;
    case 4 :
        system("cls");
        printf("XIN CHAO VA HEN GAP LAI  !");
        sleep_fake(2);
        exit(0);
        break;
    default :
        eraseLines(2);
        printf("Vui long nhap lai !");
        sleep_fake(2);
        MENU(list,list2);
        break;
    }
}

inline int DangNhap() {
    char USER[MAX_USER];
    char PASSWORD[MAX_PASSWORD];

    printf("============== DANG NHAP ==============\n");
    printf("Ten dang nhap : ");
    fgets(USER, sizeof(USER), stdin);
    USER[strcspn(USER, "\n")] = '\0';

    printf("Mat khau : ");
    fgets(PASSWORD, sizeof(PASSWORD), stdin);
    PASSWORD[strcspn(PASSWORD, "\n")] = '\0';
    printf("=======================================\n");

    if (strcmp(USER, "admin") == 0 && strcmp(PASSWORD, "admin") == 0) {
        printf("DANG NHAP THANH CONG !\n");
        sleep_fake(2);
        return 1;
    } else {
        printf("TEN DANG NHAP HOAC MAT KHAU SAI !\n");
        sleep_fake(2);
        return 0;
    }
}
int main() {
    if (!DangNhap()) return 0;
    DanhSachBN list;
    DanhSachDV list2;
    initListBN(list);
    initListDV(list2);
    initQueue(hangDoi);
    initQueueHD(hangDoiHoaDon);
    MENU(list,list2);
}
