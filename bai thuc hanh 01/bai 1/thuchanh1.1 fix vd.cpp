#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}

double phuong_tien::tinh_phi() const {
    // gia tien tung loai xe
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;

    for (int h = 0; h < tg_do; ++h) {
        if (h < 2)
            tong += gia * (cao_diem ? 1.30 : 0.95);
        else
            tong += gia * 0.90; // giam gia ve sau
    }

    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void hien_thi_loai(string loai) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), co1(false), co2(false), co3(false) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), co1(false), co2(false), co3(false) {}

int bai_xe::lay_ma() const {
    return ma_bai;
}

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;

    if (cap >= 1 && !co1) {
        pt1 = v;
        co1 = true;
        return true;
    }

    if (cap >= 2 && !co2) {
        pt2 = v;
        co2 = true;
        return true;
    }

    if (cap >= 3 && !co3) {
        pt3 = v;
        co3 = true;
        return true;
    }

    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt1 = pt2;
            if (co3) {
                pt2 = pt3;
                co3 = false;
            }
            else co2 = false;
        }
        else co1 = false;

        return true;
    }

    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) {
            pt2 = pt3;
            co3 = false;
        }
        else co2 = false;

        return true;
    }

    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        return true;
    }

    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe) return true;

    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = co1 + co2 + co3;

    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";

    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;

    if (co1 && pt1.lay_loai_xe() == loai) {
        ++dem;
        tong += pt1.tinh_phi();
    }

    if (co2 && pt2.lay_loai_xe() == loai) {
        ++dem;
        tong += pt2.tinh_phi();
    }

    if (co3 && pt3.lay_loai_xe() == loai) {
        ++dem;
        tong += pt3.tinh_phi();
    }

    return dem > 0;
}

void bai_xe::hien_thi_loai(string loai) const {
    if (co1 && pt1.lay_loai_xe() == loai)
        pt1.hien_thi();

    if (co2 && pt2.lay_loai_xe() == loai)
        pt2.hien_thi();

    if (co3 && pt3.lay_loai_xe() == loai)
        pt3.hien_thi();
}

// menu quan ly chinh cua chuong trinh
class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : co1(false), co2(false), co3(false) {}

void SystemInterface::runMenu() {
    int chon;

    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1: {
            int ma;
            char kt;

            cout << "Ma bai: ";
            cin >> ma;
            cout << "Kich thuoc (S/M/L): ";
            cin >> kt;

            kt = toupper(kt);

            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le!\n";
                break;
            }

            if ((co1 && bai1.lay_ma() == ma) ||
                (co2 && bai2.lay_ma() == ma) ||
                (co3 && bai3.lay_ma() == ma)) {
                cout << "Ma bai da ton tai!\n";
                break;
            }

            if (!co1) {
                bai1 = bai_xe(ma, kt);
                co1 = true;
            }
            else if (!co2) {
                bai2 = bai_xe(ma, kt);
                co2 = true;
            }
            else if (!co3) {
                bai3 = bai_xe(ma, kt);
                co3 = true;
            }
            else {
                cout << "Da du 3 bai xe!\n";
                break;
            }

            cout << "Da tao bai " << ma << "\n";
            break;
        }

        case 2: {
            int ma, gio, tg, maBai;
            string loai;

            cout << "Ma xe: ";
            cin >> ma;

            if ((co1 && bai1.chua(ma)) ||
                (co2 && bai2.chua(ma)) ||
                (co3 && bai3.chua(ma))) {
                cout << "Ma xe da ton tai!\n";
                break;
            }

            cout << "Loai (Car/Motorcycle/Bicycle): ";
            cin >> loai;

            cout << "Gio vao (0-23): ";
            cin >> gio;

            cout << "Thoi luong (1-23): ";
            cin >> tg;

            if (gio < 0 || gio > 23 || tg < 1 || tg > 23) {
                cout << "Thong tin khong hop le!\n";
                break;
            }

            phuong_tien v(ma, loai, gio, tg);

            if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle") {
                cout << "Loai xe khong hop le!\n";
                break;
            }

            cout << "Nhap ma bai muon them xe: ";
            cin >> maBai;

            bool ok = false;

            if (co1 && bai1.lay_ma() == maBai)
                ok = bai1.them(v);
            else if (co2 && bai2.lay_ma() == maBai)
                ok = bai2.them(v);
            else if (co3 && bai3.lay_ma() == maBai)
                ok = bai3.them(v);
            else {
                cout << "Khong tim thay bai xe!\n";
                break;
            }

            if (ok)
                cout << "Da them xe thanh công! Phi: $"
                     << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else
                cout << "Bai xe da day!\n";

            break;
        }

        case 3: {
            int ma;

            cout << "Ma bai can xoa: ";
            cin >> ma;

            if (co1 && bai1.lay_ma() == ma) {
                if (co2) {
                    bai1 = bai2;
                    if (co3) {
                        bai2 = bai3;
                        co3 = false;
                    }
                    else co2 = false;
                }
                else co1 = false;

                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co2 && bai2.lay_ma() == ma) {
                if (co3) {
                    bai2 = bai3;
                    co3 = false;
                }
                else co2 = false;

                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co3 && bai3.lay_ma() == ma) {
                co3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else {
                cout << "Khong tim thay bai xe!\n";
            }

            break;
        }

        case 4: {
            int ma;

            cout << "Ma xe can lay ra: ";
            cin >> ma;

            bool ok = false;

            if (co1 && !ok) ok = bai1.xoa(ma);
            if (co2 && !ok) ok = bai2.xoa(ma);
            if (co3 && !ok) ok = bai3.xoa(ma);

            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");

            break;
        }

        case 5: {
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();

            break;
        }

        case 6: {
            int ma;

            cout << "Ma bai: ";
            cin >> ma;

            if (co1 && bai1.lay_ma() == ma)
                bai1.hien_thi();
            else if (co2 && bai2.lay_ma() == ma)
                bai2.hien_thi();
            else if (co3 && bai3.lay_ma() == ma)
                bai3.hien_thi();
            else
                cout << "Khong tim thay bai xe!\n";

            break;
        }

        case 7: {
            string loai;
            int dem;
            double tong;
            bool tim_thay = false;

            cout << "Loai xe: ";
            cin >> loai;

            if (co1 && bai1.co_loai(loai, dem, tong)) {
                cout << "Bai " << bai1.lay_ma() << ":\n";
                bai1.hien_thi_loai(loai);
                tim_thay = true;
            }

            if (co2 && bai2.co_loai(loai, dem, tong)) {
                cout << "Bai " << bai2.lay_ma() << ":\n";
                bai2.hien_thi_loai(loai);
                tim_thay = true;
            }

            if (co3 && bai3.co_loai(loai, dem, tong)) {
                cout << "Bai " << bai3.lay_ma() << ":\n";
                bai3.hien_thi_loai(loai);
                tim_thay = true;
            }

            if (!tim_thay)
                cout << "Khong tim thay xe!\n";

            break;
        }

        case 8: {
            int dem;
            double tong;
            int dem_car = 0, dem_moto = 0, dem_bike = 0;
            double tien_car = 0, tien_moto = 0, tien_bike = 0;

            cout << "\n===== BAO CAO THEO TUNG BAI =====\n";

            if (co1) {
                cout << "\nBai " << bai1.lay_ma() << ":\n";

                bai1.co_loai("Car", dem, tong);
                cout << "Car: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_car += dem;
                tien_car += tong;

                bai1.co_loai("Motorcycle", dem, tong);
                cout << "Motorcycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_moto += dem;
                tien_moto += tong;

                bai1.co_loai("Bicycle", dem, tong);
                cout << "Bicycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_bike += dem;
                tien_bike += tong;
            }

            if (co2) {
                cout << "\nBai " << bai2.lay_ma() << ":\n";

                bai2.co_loai("Car", dem, tong);
                cout << "Car: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_car += dem;
                tien_car += tong;

                bai2.co_loai("Motorcycle", dem, tong);
                cout << "Motorcycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_moto += dem;
                tien_moto += tong;

                bai2.co_loai("Bicycle", dem, tong);
                cout << "Bicycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_bike += dem;
                tien_bike += tong;
            }

            if (co3) {
                cout << "\nBai " << bai3.lay_ma() << ":\n";

                bai3.co_loai("Car", dem, tong);
                cout << "Car: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_car += dem;
                tien_car += tong;

                bai3.co_loai("Motorcycle", dem, tong);
                cout << "Motorcycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_moto += dem;
                tien_moto += tong;

                bai3.co_loai("Bicycle", dem, tong);
                cout << "Bicycle: " << dem << " xe | TB: $" << (dem > 0 ? tong / dem : 0) << "\n";
                dem_bike += dem;
                tien_bike += tong;
            }

            cout << "\n===== TRUNG BINH TOAN HE THONG =====\n";

            cout << "Car: ";
            if (dem_car == 0) cout << "Khong co xe\n";
            else cout << dem_car << " xe | TB: $" << fixed << setprecision(2) << tien_car / dem_car << "\n";

            cout << "Motorcycle: ";
            if (dem_moto == 0) cout << "Khong co xe\n";
            else cout << dem_moto << " xe | TB: $" << fixed << setprecision(2) << tien_moto / dem_moto << "\n";

            cout << "Bicycle: ";
            if (dem_bike == 0) cout << "Khong co xe\n";
            else cout << dem_bike << " xe | TB: $" << fixed << setprecision(2) << tien_bike / dem_bike << "\n";

            break;
        }

        case 9:
            cout << "Thoat chuong trinh!\n";
            return;

        default:
            cout << "Lua chon khong hop le!\n";
        }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
