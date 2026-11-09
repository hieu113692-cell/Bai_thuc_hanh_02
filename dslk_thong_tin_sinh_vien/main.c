#include<stdio.h>
#include<stdlib.h>
typedef struct{
	char ho_ten[30];
	int ma_sv;
	float d1, d2, d3;
}Data;
typedef struct tagNode{
	Data infor;
	struct tagNode *link;
}Node;
typedef struct{
	Node *pHead;
	Node *pTail;
	int spt;
}LList;

void initList(LList *L){
	L->pHead = NULL;
	L->pTail = NULL;
	L->spt = 0;
}

int emptyList(LList L){
	return (L.spt == 0);
}

void insert_Head(LList *L, Data x){
	Node *pp;
	pp = (Node*)malloc(sizeof(Node));
	if(pp ==NULL)return;
	pp->infor = x;
	pp->link = NULL;
	if(emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else{
		pp->link = L->pHead;
		L->pHead = pp;
	}
	L->spt++;
}
void insert_Tail(LList *L, Data x){
	Node *pp;
	pp = (Node*)malloc(sizeof(Node));
	if(pp == NULL)return;
	pp->infor = x;
	pp->link = NULL;
	if(emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else{
		L->pTail->link = pp;
		L->pTail = pp;
	}
	L->spt++;
}
void insert_Chen(LList *L, Data x, int ma){
	Node *p = L->pHead;
	while(p != NULL&& p->infor.ma_sv != ma){
		p=p->link;
	}
	if(p==NULL){
		printf("Khong tim thay sinh vien co ma vua nhap");
		return;
	}
	Node *pp = (Node*)malloc(sizeof(Node));
	pp->infor = x;
	pp->link =p->link;
	p->link = pp;
	if(p == L->pTail){
		L->pTail = pp;
	}
	L->spt++;
	printf("Da chen thanh cong\n");
}

void nhap(Data *x){
	printf("Nhap ma sinh vien: ");
	scanf("%d", &(x->ma_sv));
	if(x->ma_sv > 0){
		printf("Nhap ho ten: ");
		scanf(" %29[^\n]", x->ho_ten);
		printf("Nhap diem m1: ");
		scanf("%f", &(x->d1));
		printf("Nhap diem m2: ");
		scanf("%f", &(x->d2));
		printf("Nhap diem m3: ");
		scanf("%f", &(x->d3));
	}
}
Node *search(LList L, int id){
	Node *pp = L.pHead;
	while(pp != NULL && (pp->infor.ma_sv != id)){
		pp = pp->link;
	}
	return pp;
}
void in(Data x){
	printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f", x.ho_ten, x.ma_sv, x.d1, x.d2, x.d3);
}
void processList(LList L){
	Node *pp = L.pHead;
	while(pp != NULL){
		in(pp->infor);
		pp = pp->link;
	}
}

int main(){
	LList L;
	int kt=0, ma;
	Data x;
	initList(&L);
	do{
		printf("Chuong trinh lam viec voi DSLK don SV\n");
		printf("\n1: Them nut vao dau danh sach");
		printf("\n2: Them nut vao cuoi danh sach");
		printf("\n3: Them nut vao sau mot nut khac trong danh sach");
		printf("\n9: Duyet ds");
		printf("\n0: Thoat");
		printf("\nMoi ban chon: ");
		int chon;
		scanf("%d", &chon);
		switch(chon){
			case 1:
				nhap(&x);
				if(x.ma_sv > 0){
					insert_Head(&L, x);
				}
				break;
			case 2:
				nhap(&x);
				if(x.ma_sv > 0){
					insert_Tail(&L, x);
				}
				break;
			case 3:
				if(emptyList(L)){
					printf("\nDanh sach rong khong the chen");
					break;
				}
				printf("\nNhap ma sinh vien dung truoc: ");
				scanf("%d", &ma);
				printf("Nhap thong tin sinh vien can chen: ");
				nhap(&x);
				if(x.ma_sv > 0){
					insert_Chen(&L, x, ma);
					break;
				}
				break;
			case 4:
				printf("\nNhap ma sinh vien can tim: ");
				scanf("%d", &ma);
				if(search(L, ma) != NULL){
					printf("Tim thay sinh vien: ");
					in(search(L, ma)->infor);
				}
				else{
					printf("Khong tim thay sinh vien");
				}
				break;
			case 9:
				processList(L);
				break;
			case 0:
				kt = 1;
				break;
			default:
				printf("Lua chon khong hop le");
		}
	}while(kt == 0);
	return 0;
}
