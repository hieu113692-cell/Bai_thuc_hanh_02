#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
Node *tkMa(LList L, int id){
	Node *pp = L.pHead;
	while(pp != NULL && (pp->infor.ma_sv != id)){
		pp = pp->link;
	}
	return pp;
}
Node *tkTen(LList L, char ten[30]){
    Node *pp = L.pHead;
    while(pp != NULL && !strstr(pp->infor.ho_ten, ten)){
        pp = pp->link;
    }return pp;
}
void xoaMa(LList *L, int ma){
    if(emptyList(*L))return;
    Node *pp = L->pHead;
    Node *qq = NULL;
    while(pp != NULL && pp->infor.ma_sv != ma){
        qq = pp;
        pp = pp->link;
    }
    if(pp == NULL){
        printf("Khong tim thay sinh vien can xoa\n");
        return;
    }
    if(qq == NULL){
        L->pHead = pp->link;
        if(L->pHead == NULL) L->pTail = NULL;
    }
    else{
        qq->link = pp->link;
        if(pp == L->pTail) L->pTail = qq;
    }
    free(pp);
    L->spt--;
    printf("Da xoa thanh cong\n");
}
void xoaTen(LList *L, char ten[]){
    if(emptyList(*L)) return;
    Node *pp = L->pHead;
    Node *qq = NULL;
    int dem = 0;
    while(pp != NULL){
        if(strstr(pp->infor.ho_ten, ten) != NULL){
            dem++;
            Node *tg = pp;
            if(qq == NULL){
                L->pHead = pp->link;
                pp = L->pHead;
                if(L->pHead == NULL) L->pTail = NULL;
            }
            else{
                qq->link = pp->link;
                if(pp == L->pTail) L->pTail = qq;
                pp = pp->link;
            }
            free(tg);
            L->spt--;
        }
        else{
            qq = pp;
            pp = pp->link;
        }
    }
    if(dem > 0){
        printf("Da xoa thanh cong\n");
    }
    else{
        printf("Khong tim thay sinh vien nao de xoa\n");
    }
}
void sxep(Data *a, Data *b){
    Data tg = *a;
    *a = *b;
    *b = tg;
}
void sxepTen(LList *L){
    if(emptyList(*L)) return;
    for(Node *pp = L->pHead; pp != NULL; pp = pp->link){
        for(Node *qq = pp->link; qq != NULL; qq = qq->link){
            if(strcmp(pp->infor.ho_ten, qq->infor.ho_ten)>0){
                sxep(&(pp->infor), &(qq->infor));
            }
        }
    }
    printf("Da sap xep theo ten\n");
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
	char ten[30];
	Data x;
	initList(&L);
	do{
		printf("Chuong trinh lam viec voi DSLK don SV\n");
		printf("\n1: Them nut vao dau danh sach");
		printf("\n2: Them nut vao cuoi danh sach");
		printf("\n3: Them nut vao sau mot nut khac trong danh sach");
		printf("\n4: Xoa theo ma");
		printf("\n5: Xoa theo ten");
		printf("\n6: Tim kiem theo ma");
		printf("\n7: Tim kiem theo ten");
		printf("\n8: Sap xep danh sach theo ten");
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
			    printf("Nhap ma sinh vien can xoa: ");
			    scanf("%d", &ma);
			    xoaMa(&L, ma);
			    break;
			case 5:
			    printf("Nhap ten sinh vien can xoa: ");
			    scanf(" %[^\n]", ten);
			    xoaTen(&L, ten);
			    break;
			case 6:
				printf("\nNhap ma sinh vien can tim: ");
				scanf("%d", &ma);
				if(tkMa(L, ma) != NULL){
					printf("Tim thay sinh vien: ");
					in(tkMa(L, ma)->infor);
				}
				else{
					printf("Khong tim thay sinh vien\n");
				}
				break;
			case 7:
			    printf("Nhap sinh vien ca tim: ");
			    scanf(" %[^\n]", ten);
			    if(tkTen(L, ten) != NULL){
			        printf("Tim thay sinh vien: ");
			        in(tkTen(L, ten)->infor);
			    }
			    else{
			        printf("Khong tim thay sinh vien\n");
			    }
			    break;
			case 8:
			    sxepTen(&L);
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


