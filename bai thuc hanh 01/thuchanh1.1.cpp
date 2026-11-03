#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien() {
        ma_xe = 0;
        loai_xe = "";
        gio_vao = 0;
        tg_do = 0;
    }

    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma;

        for (size_t i = 0; i < loai.length(); i++) {
            loai[i] = toupper(static_cast<unsigned char>(loai[i]));
        }

        if (loai == "CAR")
            loai_xe = "Car";
        else if (loai == "MOTORCYCLE")
            loai_xe = "Motorcycle";
        else if (loai == "BICYCLE")
            loai_xe = "Bicycle";
        else
            loai_xe = "";

        gio_vao = gio;
        tg_do = tg;
    }

    int lay_ma_xe() const {
        return ma_xe;
    }

    string lay_loai_xe() const {
        return loai_xe;
    }

    double tinh_phi() const {
        double donGia = 0;

        if (loai_xe == "Car")
            donGia = 6;
        else if (loai_xe == "Motorcycle")
            donGia = 4;
        else if (loai_xe == "Bicycle")
            donGia = 2;

        double phi = 0;

        bool caoDiem = false;

        if ((gio_vao >= 6 && gio_vao < 10) ||
            (gio_vao >= 15 && gio_vao < 19)) {
            caoDiem = true;
        }

        for (int i = 1; i <= tg_do; i++) {
            if (i <= 2) {
                if (caoDiem)
                    phi += donGia * 1.3;
                else
                    phi += donGia * 0.95;
            }
            else {
                phi += donGia * 0.9;
            }
        }

        return phi;
    }

    void hien_thi() const {
        cout << "Ma xe: " << ma_xe << endl;
        cout << "Loai xe: " << loai_xe << endl;
        cout << "Gio vao: " << gio_vao << endl;
        cout << "Thoi gian do: " << tg_do << " gio" << endl;
        cout << "Phi do xe: " << tinh_phi() << " VND" << endl;
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;

    phuong_tien pt1, pt2, pt3;

    bool co1, co2, co3;

public:
    bai_xe() {
        ma_bai = 0;
        kich_thuoc = 'S';
        co1 = false;
        co2 = false;
        co3 = false;
    }

    bai_xe(int ma, char kt) {
        ma_bai = ma;
        kich_thuoc = toupper(static_cast<unsigned char>(kt));
        co1 = false;
        co2 = false;
        co3 = false;
    }

    int lay_ma() const {
        return ma_bai;
    }

    bool them(phuong_tien v) {
        if (co1 && pt1.lay_ma_xe() == v.lay_ma_xe())
            return false;

        if (co2 && pt2.lay_ma_xe() == v.lay_ma_xe())
            return false;

        if (co3 && pt3.lay_ma_xe() == v.lay_ma_xe())
            return false;

        if (!co1) {
            pt1 = v;
            co1 = true;
            return true;
        }

        if (kich_thuoc >= 'M' && !co2) {
            pt2 = v;
            co2 = true;
            return true;
        }

        if (kich_thuoc == 'L' && !co3) {
            pt3 = v;
            co3 = true;
            return true;
        }

        return false;
    }

    bool xoa(int ma_xe) {
        if (co1 && pt1.lay_ma_xe() == ma_xe) {
            co1 = false;
            return true;
        }

        if (co2 && pt2.lay_ma_xe() == ma_xe) {
            co2 = false;
            return true;
        }

        if (co3 && pt3.lay_ma_xe() == ma_xe) {
            co3 = false;
            return true;
        }

        return false;
    }

    bool chua(int ma_xe) const {
        if (co1 && pt1.lay_ma_xe() == ma_xe)
            return true;

        if (co2 && pt2.lay_ma_xe() == ma_xe)
            return true;

        if (co3 && pt3.lay_ma_xe() == ma_xe)
            return true;

        return false;
    }

    void hien_thi() const {
        int dem = 0;

        if (co1) dem++;
        if (co2) dem++;
        if (co3) dem++;

        cout << "\nMa bai: " << ma_bai << endl;
        cout << "Kich thuoc: " << kich_thuoc << endl;
        cout << "So xe: " << dem << endl;

        if (co1) pt1.hien_thi();
        if (co2) pt2.hien_thi();
        if (co3) pt3.hien_thi();
    }

    bool co_loai(string loai, int& dem, double& tong) const {
        bool timThay = false;

        if (co1 && pt1.lay_loai_xe() == loai) {
            pt1.hien_thi();
            dem++;
            tong += pt1.tinh_phi();
            timThay = true;
        }

        if (co2 && pt2.lay_loai_xe() == loai) {
            pt2.hien_thi();
            dem++;
            tong += pt2.tinh_phi();
            timThay = true;
        }

        if (co3 && pt3.lay_loai_xe() == loai) {
            pt3.hien_thi();
            dem++;
            tong += pt3.tinh_phi();
            timThay = true;
        }

        return timThay;
    }
};

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;

    bool co1, co2, co3;

public:
    SystemInterface() {
        co1 = false;
        co2 = false;
        co3 = false;
    }

    void runMenu() {
        int chon;

        do {
            cout << "\n========== QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao bai do xe\n";
            cout << "2. Them xe vao bai\n";
            cout << "3. Xoa bai do xe\n";
            cout << "4. Lay xe ra khoi bai\n";
            cout << "5. Hien thi danh sach bai xe\n";
            cout << "6. Hien thi xe theo bai\n";
            cout << "7. Tim xe theo loai\n";
            cout << "8. Bao cao phi do xe trung binh\n";
            cout << "9. Thoat\n";
            cout << "Chon: ";
            cin >> chon;

            switch (chon) {
                case 1: {
                    int ma;
                    char kt;

                    cout << "Nhap ma bai: ";
                    cin >> ma;

                    cout << "Nhap kich thuoc (S/M/L): ";
                    cin >> kt;

                    kt = toupper(static_cast<unsigned char>(kt));

                    if (kt != 'S' && kt != 'M' && kt != 'L') {
                        cout << "Kich thuoc khong hop le!\n";
                    }
                    else if ((co1 && bai1.lay_ma() == ma) ||
                             (co2 && bai2.lay_ma() == ma) ||
                             (co3 && bai3.lay_ma() == ma)) {
                        cout << "Ma bai da ton tai!\n";
                    }
                    else if (!co1) {
                        bai1 = bai_xe(ma, kt);
                        co1 = true;
                        cout << "Tao bai thanh cong!\n";
                    }
                    else if (!co2) {
                        bai2 = bai_xe(ma, kt);
                        co2 = true;
                        cout << "Tao bai thanh cong!\n";
                    }
                    else if (!co3) {
                        bai3 = bai_xe(ma, kt);
                        co3 = true;
                        cout << "Tao bai thanh cong!\n";
                    }
                    else {
                        cout << "He thong da du 3 bai!\n";
                    }

                    break;
                }

                case 2: {
                    int ma, gio, tg;
                    string loai;

                    cout << "Nhap ma xe: ";
                    cin >> ma;

                    if ((co1 && bai1.chua(ma)) ||
                        (co2 && bai2.chua(ma)) ||
                        (co3 && bai3.chua(ma))) {
                        cout << "Ma xe da ton tai!\n";
                        break;
                    }

                    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
                    cin >> loai;

                    cout << "Nhap gio vao (0-23): ";
                    cin >> gio;

                    cout << "Nhap thoi gian do (1-23): ";
                    cin >> tg;

                    if (gio < 0 || gio > 23 || tg < 1 || tg > 23) {
                        cout << "Thong tin khong hop le!\n";
                        break;
                    }

                    phuong_tien v(ma, loai, gio, tg);

                    if (v.lay_loai_xe() == "") {
                        cout << "Loai xe khong hop le!\n";
                        break;
                    }

                    bool thanhCong = false;

                    if (co1 && bai1.them(v))
                        thanhCong = true;
                    else if (co2 && bai2.them(v))
                        thanhCong = true;
                    else if (co3 && bai3.them(v))
                        thanhCong = true;

                    if (thanhCong)
                        cout << "Them xe thanh cong!\n";
                    else
                        cout << "Khong con bai xe trong!\n";

                    break;
                }

                case 3: {
                    int ma;

                    cout << "Nhap ma bai can xoa: ";
                    cin >> ma;

                    if (co1 && bai1.lay_ma() == ma) {
                        bai1 = bai_xe();
                        co1 = false;
                        cout << "Da xoa bai!\n";
                    }
                    else if (co2 && bai2.lay_ma() == ma) {
                        bai2 = bai_xe();
                        co2 = false;
                        cout << "Da xoa bai!\n";
                    }
                    else if (co3 && bai3.lay_ma() == ma) {
                        bai3 = bai_xe();
                        co3 = false;
                        cout << "Da xoa bai!\n";
                    }
                    else {
                        cout << "Khong tim thay bai!\n";
                    }

                    break;
                }

                case 4: {
                    int ma;

                    cout << "Nhap ma xe can lay: ";
                    cin >> ma;

                    if ((co1 && bai1.xoa(ma)) ||
                        (co2 && bai2.xoa(ma)) ||
                        (co3 && bai3.xoa(ma))) {
                        cout << "Da lay xe ra!\n";
                    }
                    else {
                        cout << "Khong tim thay xe!\n";
                    }

                    break;
                }

                case 5: {
                    if (co1) bai1.hien_thi();
                    if (co2) bai2.hien_thi();
                    if (co3) bai3.hien_thi();

                    if (!co1 && !co2 && !co3)
                        cout << "Chua co bai xe!\n";

                    break;
                }

                case 6: {
                    int ma;

                    cout << "Nhap ma bai: ";
                    cin >> ma;

                    if (co1 && bai1.lay_ma() == ma)
                        bai1.hien_thi();
                    else if (co2 && bai2.lay_ma() == ma)
                        bai2.hien_thi();
                    else if (co3 && bai3.lay_ma() == ma)
                        bai3.hien_thi();
                    else
                        cout << "Khong tim thay bai!\n";

                    break;
                }

                case 7: {
                    string loai;

                    cout << "Nhap loai xe: ";
                    cin >> loai;

                    for (size_t i = 0; i < loai.length(); i++) {
                        loai[i] = toupper(static_cast<unsigned char>(loai[i]));
                    }

                    if (loai == "CAR")
                        loai = "Car";
                    else if (loai == "MOTORCYCLE")
                        loai = "Motorcycle";
                    else if (loai == "BICYCLE")
                        loai = "Bicycle";
                    else {
                        cout << "Loai xe khong hop le!\n";
                        break;
                    }

                    int dem = 0;
                    double tong = 0;

                    if (co1 && bai1.co_loai(loai, dem, tong))
                        cout << "Xe thuoc bai: " << bai1.lay_ma() << endl;

                    if (co2 && bai2.co_loai(loai, dem, tong))
                        cout << "Xe thuoc bai: " << bai2.lay_ma() << endl;

                    if (co3 && bai3.co_loai(loai, dem, tong))
                        cout << "Xe thuoc bai: " << bai3.lay_ma() << endl;

                    if (dem == 0)
                        cout << "Khong tim thay xe!\n";

                    break;
                }

                case 8: {
                    int demCar = 0, demMoto = 0, demBike = 0;
                    double tongCar = 0, tongMoto = 0, tongBike = 0;

                    cout << "\n===== BAO CAO THEO TUNG BAI =====\n";

                    if (co1) {
                        int c = 0, m = 0, b = 0;
                        double tc = 0, tm = 0, tb = 0;

                        cout << "\nBai " << bai1.lay_ma() << endl;

                        bai1.co_loai("Car", c, tc);
                        bai1.co_loai("Motorcycle", m, tm);
                        bai1.co_loai("Bicycle", b, tb);

                        cout << "Phi trung binh Car: " << (c > 0 ? tc / c : 0) << endl;
                        cout << "Phi trung binh Motorcycle: " << (m > 0 ? tm / m : 0) << endl;
                        cout << "Phi trung binh Bicycle: " << (b > 0 ? tb / b : 0) << endl;

                        demCar += c;
                        demMoto += m;
                        demBike += b;
                        tongCar += tc;
                        tongMoto += tm;
                        tongBike += tb;
                    }

                    if (co2) {
                        int c = 0, m = 0, b = 0;
                        double tc = 0, tm = 0, tb = 0;

                        cout << "\nBai " << bai2.lay_ma() << endl;

                        bai2.co_loai("Car", c, tc);
                        bai2.co_loai("Motorcycle", m, tm);
                        bai2.co_loai("Bicycle", b, tb);

                        cout << "Phi trung binh Car: " << (c > 0 ? tc / c : 0) << endl;
                        cout << "Phi trung binh Motorcycle: " << (m > 0 ? tm / m : 0) << endl;
                        cout << "Phi trung binh Bicycle: " << (b > 0 ? tb / b : 0) << endl;

                        demCar += c;
                        demMoto += m;
                        demBike += b;
                        tongCar += tc;
                        tongMoto += tm;
                        tongBike += tb;
                    }

                    if (co3) {
                        int c = 0, m = 0, b = 0;
                        double tc = 0, tm = 0, tb = 0;

                        cout << "\nBai " << bai3.lay_ma() << endl;

                        bai3.co_loai("Car", c, tc);
                        bai3.co_loai("Motorcycle", m, tm);
                        bai3.co_loai("Bicycle", b, tb);

                        cout << "Phi trung binh Car: " << (c > 0 ? tc / c : 0) << endl;
                        cout << "Phi trung binh Motorcycle: " << (m > 0 ? tm / m : 0) << endl;
                        cout << "Phi trung binh Bicycle: " << (b > 0 ? tb / b : 0) << endl;

                        demCar += c;
                        demMoto += m;
                        demBike += b;
                        tongCar += tc;
                        tongMoto += tm;
                        tongBike += tb;
                    }

                    cout << "\n===== BAO CAO TOAN HE THONG =====\n";

                    cout << "Phi trung binh Car: "
                         << (demCar > 0 ? tongCar / demCar : 0) << endl;

                    cout << "Phi trung binh Motorcycle: "
                         << (demMoto > 0 ? tongMoto / demMoto : 0) << endl;

                    cout << "Phi trung binh Bicycle: "
                         << (demBike > 0 ? tongBike / demBike : 0) << endl;

                    break;
                }

                case 9:
                    cout << "Thoat chuong trinh!\n";
                    break;

                default:
                    cout << "Lua chon khong hop le!\n";
                    break;
            }

        } while (chon != 9);
    }
};

int main() {
    SystemInterface app;
    app.runMenu();
    return 0;
}
