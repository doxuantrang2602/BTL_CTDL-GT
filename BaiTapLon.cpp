#include <bits/stdc++.h>
#define se second
#define fi first
#define endl '\n'

using namespace std;

// Cap phat cho 1 node
// Kiem tra rong 
// Size
// insertFirst
// insertLast
// insertMiddle
// Xoa dau
// Xoa cuoi
// Xoa giua
// in 1 node
// in toan bo node
// Cac thuat toan sap xep, tim kiem,...

class KhachHang{
	private:	
		string name, sdt;
		int ma;
	public:
		friend istream &operator >> (istream& in,KhachHang& x){
			cout << "Nhap ma khach hang: "; in >> x.ma;
			cout << "Nhap ho ten: "; fflush(stdin); getline(in,x.name);
			cout << "Nhap sdt: "; fflush(stdin); getline(in, x.sdt);
			return in;
		}
		string getName(){
			return name;
		}
		string getSdt(){
			return sdt;
		}
		int getMa(){
			return ma;
		}	
		void nhapHoten(){
			cout << "Nhap ho ten: ";
			fflush(stdin); getline(cin,name);
		}
		void nhapSdt(){
			cout << "Nhap sdt: ";
			fflush(stdin); getline(cin,sdt);
		}
};

struct KH{
	KhachHang s;
	KH *prev;
	KH *next;
};

typedef struct KH* kh;

// cap phat dong cho 1 node
kh makeNode(KhachHang x){	// O(1)
	kh tmp = new KH();
	tmp->s = x;
	tmp->prev = NULL;
	tmp->next = NULL;
	return tmp;
}
// Kiem tra rong
bool empty(kh a){ // O(1)
	return a == NULL;
}

int Size(kh a){ // O(n)
	int cnt =0;
	while(a != NULL){
		++cnt;
		a=a->next;
	}
	return cnt;
}

// Them 1 phan tu vao dau dslk
void insertFirst(kh *head,KhachHang s){ //O(1)
	kh tmp = makeNode(s);
	tmp->next =(*head);
	if(*head != NULL){
		(*head)->prev = tmp;
	}
	*head = tmp;
}
// Them phan tu vao cuoi dslk
void insertLast(kh *head,KhachHang s){ // O(n)
	kh newNode = makeNode(s); //cap phat cho newNode
	if(*head ==NULL){ // head tro den NULL thi newNode = head
		*head = newNode;
		return;
	}
	kh temp = *head;
	while(temp->next!=NULL){
		temp=temp->next;		
	}
	temp->next = newNode;
	newNode->prev = temp;
}
// Them phan tu vao giua dslk
void insertMiddle(kh *head, int k,KhachHang s){ //O(n)
	int n = Size(*head);
	if(k<0 || k >n+1){
		return;
	}
	if(k == 1){
		insertFirst(head,s);
		return;
	}
	else if(k>n){
		insertLast(head,s);
		return;
	}
	kh tmp = *head;
	for(int i=1;i<=k-1;i++){
		tmp= tmp->next;
	}
	kh newNode = makeNode(s);
	newNode->next=tmp;
	tmp->prev->next = newNode;
	tmp->prev = newNode->prev;
	tmp->prev = newNode;
}
void deleteFirst(kh &head) //O(1)
{
	if(head == NULL) return;
	head = head->next;
	head->prev =NULL;
}

void deleteLast(kh &head){ // O(n)
	if(head == NULL) return;
	kh tmp;
	for(tmp=head; tmp!=NULL;tmp=tmp->next){
		if(tmp->next == NULL){
			kh tmp1 = tmp->prev;
			tmp1->next = NULL;
			tmp->prev = NULL;
		}
	}
}

void deleteMiddle(kh &head,kh p) // O(1)
{
	kh temp = p->prev;
	kh temp1 = p->next;
	temp->next = temp1;
	temp1->prev = temp;
}

void in(KhachHang s){ // O(1)
	cout << "*****************************\n";
	cout << "| Ma khach hang: " << s.getMa() <<endl;
	cout << "| Ho ten: " << s.getName() << endl;
	cout << "| So dien thoat: " << s.getSdt() << endl;
	cout << "*****************************\n";
}

void inds(kh a){ // O(n)
	cout << "Danh sach khach hang: \n";
	while(a != NULL){	
		in(a->s);
		a=a->next;		
	}
	cout << endl;
}

void editKhachHang(kh &head){ // O(1)
	string edit_name;
	string edit_sdt;
	while(1){
		cout << "	----------------Edit_MENU---------------" << endl;
		cout << "		1. Sua ho ten Khach hang \n";
		cout << "		2. Sua so dien thoai khach hang \n";
		cout << "		3. Hoan thanh! \n";
		cout << "	Ban muon sua gi? Hay nhap lua chon nao: ";	
		int c;
		cin >> c;
		if(c==1){
			head->s.nhapHoten();
		}
		else if(c == 2){
			head->s.nhapSdt();
		}
		else if(c == 3){
			cout << "Da sua xong khach hang ma " << head->s.getMa();
			break;
		}
		else{
			cout << "Lua chon sai ! Hay nhap lai" << endl;
		}
	}		
}

void swap(KhachHang &x,KhachHang &y)
{
	KhachHang tg;
	tg = x;
	x = y;
	y = tg;
}

void Sapxep(kh head)
{	
	kh temp = head;
	kh temp1 = head;
	cout << "Da sap xep khach hang theo ma !" << endl;
	while(temp->next!=NULL)
		{
			temp1=temp->next;
			while(temp1!=NULL)
			{
			if(temp->s.getMa() > temp1->s.getMa())
				{
					 swap(temp->s,temp1->s);
				}
				temp1=temp1->next;
			}
			temp = temp->next;
		}
}

void TimKiem(kh &head){ // O(n^2)
	cout << "*Nhap ma khach hang can tim: ";
	int ma_nhap;
	cin >> ma_nhap;
	kh a=head;
	int k=0;
	for(a=head;a!=NULL;a=a->next){
		if(ma_nhap == a->s.getMa() ){
			k++;			
			cout << "	Da tim thay khach hang ma " << a->s.getMa() <<" !" << endl;;
			cout << "	-------------Search_Menu------------" << endl;
			cout << "		1. Xoa khach hang vua nhap" << endl;
			cout << "		2. Sua thong tin ho ten, sdt khach hang" << endl;
			cout << "	Hay nhap lua chon cua ban: ";
			int b; cin >> b;
			cout << endl;
			if(b==1){
				if(a == NULL) return;
				else if(a == head){
					deleteFirst(head);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;	
					return;
				}
				else if(a->prev!=NULL && a->next == NULL)
				{
					deleteLast(a);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;
				 } 
				else if(a->prev!=NULL && a->next !=NULL)
				{
					deleteMiddle(head,a);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;									
				}
			}			 	
			else if(b == 2){
				editKhachHang(a);
				break;
			}
		}	
		
	}
	cout << endl;
	if(k==0)	
		cout << "Khong tim thay khach hang can tim! " << endl;
}

int main(){
	kh head = NULL;
	cout << "--------------------------------------" << endl;
	cout << "| Ho va ten: DO XUAN TRANG - IT5*K62 |" << endl;
	cout << "| Ma sinh vien: 211240555            |" << endl;
	cout << "| Bai tap lon: Chu de 17             |" << endl;
	cout << "-------------------------------------- " << endl;
	cout << endl;
	while(1){
		cout << "-------------------MENU------------------ \n";
		cout << "| 1.Them khach hang vao dau danh sach   | \n";
		cout << "| 2.Them khach hang vao cuoi danh sach  | \n";
		cout << "| 3.Them khach hang vao giua danh sach  | \n";
		cout << "| 4.Duyet danh sach khach hang          | \n";
		cout << "| 5.Tim kiem khach hang theo ma         | \n";
		cout << "| 6.Sap xep khach hang theo ma tang dan | \n";
		cout << "| 0.Thoat!                              | \n";
		cout << "----------------------------------------- \n";
		cout << "Nhap lua chon: ";
		int lc; cin >> lc;
		cout << endl;
		if(lc == 1){
			KhachHang x;
			cin >> x;
			insertFirst(&head,x);
			cout << "Ban co muon insertFirst (Y or N)? : ";
			string s; getline(cin,s);
			string s1 = "Y";
			string s2 = "N";
			cout << endl;
			while(s == s1){
				KhachHang x;
				cin >> x;
				insertFirst(&head,x);
				cout << "Ban van muon inserFirst(Y or N)? : "; getline(cin,s);
				cout << endl;
			}
			cout << endl;
			while(s == s2){
				cout << "Ket thuc !\n";
			    break;
			}
		}
		else if(lc == 2){
			KhachHang x;
			cin >> x;
			insertLast(&head,x);
			cout << "Ban co muon insertLast(Y or N): ";
			string s; getline(cin,s);
			cout << endl;
			string s1 = "Y";
			string s2 = "N";
			while(s == s1){
				KhachHang x;
				cin >> x;
				insertLast(&head,x);
				cout << "Ban van muon insertLast(Y or N)? : "; getline(cin,s);
				cout << endl;
			}
			while(s == s2){
				cout << "Ket thuc !\n";
			    break;
			}
		}
		else if(lc == 3){			
			int k; 
			cout << "Nhap vi tri can chen: ";
			cin >> k;
			string s; 
			string s1 = "Y";
			string s2 = "N";
			int n = Size(head);
			if(k<0 || k >n+1){
				cout << "Vi tri chen khong hop le ! \n" << endl;
			}
			else{
				KhachHang x;
				cin >> x;
				insertMiddle(&head,k,x);			
				cout << "Ban co muon insertMiddle(Y or N): ";
				getline(cin,s);				
				cout << endl;
				while(s == s1){	
					int k;			 
					cout << "Nhap vi tri can chen: ";
					cin >> k;
					if(k<0 || k >n+1){
						cout << "Vi tri chen khong hop le ! \n";
						break;
					}
					else{
						KhachHang x;
						cin >> x;
						insertMiddle(&head,k,x);
						cout << "Ban van muon insertMiddle(Y or N)?: ";
						getline(cin,s);
						cout << endl;
					}	
				}
				while(s == s2){
					cout << "Ket thuc !\n";
			    	break;
				}	
			}
		}
		else if(lc == 4){
			inds(head);
		}
		else if(lc == 5){
			TimKiem(head);
		}
		else if(lc == 6){
			Sapxep(head);
		}
		else if(lc == 0){
			break;
		}
		else{
			cout << "Hay nhap lai lua chon !" << endl;
		}
	}
	return 0;
}