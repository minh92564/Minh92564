
#include <iostream>
#include <string>
using namespace std;

class KH {
private:
    string hoten;
    int sdt;
    string diachi;

public:
    KH();
    KH(string ht, int sdt1, string dc);
    void nhap();
    void in();
};

KH::KH() {
    hoten = "";
    sdt = 0;
    diachi = "";
}

KH::KH(string ht, int sdt1, string dc) {
    hoten = ht;
    sdt = sdt1;
    diachi = dc;
}

void KH::nhap() {
    cout << "Nhap ho ten KH: ";
    getline(cin, hoten);

    cout << "Nhap SDT: ";
    cin >> sdt;
    cin.ignore(1000, '\n');

    cout << "Nhap dia chi: ";
    getline(cin, diachi);
}

void KH::in() {
    cout << "Ho ten: " << hoten << endl;
    cout << "SDT: " << sdt << endl;
    cout << "Dia chi: " << diachi << endl;
}

class ChuCH {
private:
    string hoten;
    int sdt;
    string diachi;
    string tencuahang;
    string MST;
public:
    ChuCH();
    ChuCH(string ht, int sdt1, string dc, string tenCH, string mst);
    void nhap();
    void in();
};
ChuCH::ChuCH() {
    hoten = "";
    sdt = 0;
    diachi = "";
    tencuahang = "";
    MST = "";
}
ChuCH::ChuCH(string ht, int sdt1, string dc, string tenCH, string mst) {
    hoten = ht;
    sdt = sdt1;
    diachi = dc;
    tencuahang = tenCH;
    MST = mst;
}
void ChuCH::nhap() {
    cout << "Nhap ho ten chu cua hang: ";
    getline(cin, hoten);
    cout << "Nhap SDT: ";
    cin >> sdt;
    cin.ignore(1000, '\n');
    cout << "Nhap dia chi: ";
    getline(cin, diachi);
    cout << "Nhap ten cua hang: ";
    getline(cin, tencuahang);
    cout << "Nhap ma so thue: ";
    getline(cin, MST);
}
void ChuCH::in() {
    cout << "Ho ten: " << hoten << endl;
    cout << "SDT: " << sdt << endl;
    cout << "Dia chi: " << diachi << endl;
    cout << "Ten cua hang: " << tencuahang << endl;
    cout << "Ma so thue: " << MST << endl;
}
class MH {
private:
    string tenMH;
    int SL;
    int dongia;
    string donvitinh;
    
public:
    MH();
    MH(string ten, int sl, int dg, string dvt);
    void nhap();
    void in();
    float thanhtien() {
        return dongia * SL;}
    /*string getTenMH(){
    	return tenMH;
	}*/
	friend class HD;    
};
MH::MH() {
    tenMH = "";
    SL = 0;
    dongia = 0;
    donvitinh = "";
}
MH::MH(string ten, int sl, int dg, string dvt) {
    tenMH = ten;
    SL = sl;
    dongia = dg;
    donvitinh = dvt;
}
void MH::nhap() {
    cout << "Nhap ten mat hang: ";
    getline(cin, tenMH);
    cout << "Nhap so luong: ";
    cin >> SL;
    cout << "Nhap don gia: ";
    cin >> dongia;
    cin.ignore(1000, '\n');
    cout << "Nhap don vi tinh: ";
    getline(cin, donvitinh);
}
void MH::in() {
    cout << "Ten Mat Hang: " << tenMH << endl;
    cout << "So luong: " << SL << endl;
    cout << "Don gia: " << dongia << endl;
    cout << "Don vi tinh: " << donvitinh << endl;
    cout << "Thanh tien: " << thanhtien() << endl;
}
class HD {
private:
    ChuCH x;
    KH y;
    int somathang;
    MH *a;
public:
    HD();
    HD(int sl);
    ~HD();
    void nhap();
    float tongtien();
    /*void Sapxeptheoten();*/
    void Sapxep();
    void in();
};
HD::HD() {
    somathang = 0;
    a = NULL;
}
HD::HD(int sl) {
    somathang = sl;
    a = new MH[somathang];
}
HD::~HD() {
    delete[] a;
}
void HD::nhap() {
    cout << "\nNhap thong tin chu cua hang:\n";
    x.nhap();
    cout << "\nNhap thong tin khach hang:\n";
    y.nhap();
    cout << "\nNhap so luong mat hang: ";
    cin >> somathang;
    cin.ignore(1000, '\n');
    if (somathang < 0) {
        somathang = 0;
    }

    delete[] a;
    a = new MH[somathang];

    for (int i = 0; i < somathang; i++) {
        cout << "\nNhap thong tin mat hang thu " << i + 1 << ":\n";
        a[i].nhap();
    }
}
float HD::tongtien() {
    float tong = 0;
    for (int i = 0; i < somathang; i++) {
        tong += a[i].thanhtien();
    }
    return tong;
}
/*void HD::Sapxeptheoten(){
	for (int i = 0; i < somathang - 1; i++) {
        for (int j = i + 1; j < somathang; j++) {
            if (a[i].getTenMH() > a[j].getTenMH()) {
                MH temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
*/
void HD::Sapxep(){
	for (int i = 0; i < somathang - 1; i++) {
        for (int j = i + 1; j < somathang; j++) {
            if (a[i].tenMH > a[j].tenMH) {
                MH temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
void HD::in() {
    cout << "\nThong tin chu cua hang:\n";
    x.in();
    cout << "\nThong tin khach hang:\n";
    y.in();
    cout << "\nThong tin cac mat hang:\n";
    for (int i = 0; i < somathang; i++) {
        cout << "\nMat hang thu " << i + 1 << ":\n";
        a[i].in();
    }
    cout << "\nSo luong mat hang: " << somathang << endl;
    cout << "Tong tien hoa don: " << tongtien() << endl;
}

int main() {
    HD hd;

    hd.nhap();
    hd.in();
    /*hd.Sapxeptheoten();*/
    hd.Sapxep();
    hd.in();

    return 0;
}

