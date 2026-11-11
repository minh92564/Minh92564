
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int nhapSoNguyen(string thongBao) {
    int n;

    while (true) {
        cout << thongBao;
        cin >> n;

        if (cin.fail()) {
            cout << "Du lieu khong hop le! Nhap lai.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return n;
        }
    }
}

string chuanHoaLoai(string loai) {
    for (int i = 0; i < (int)loai.length(); i++) {
        loai[i] = toupper(loai[i]);
    }

    if (loai == "CAR") return "Car";
    if (loai == "MOTORCYCLE") return "Motorcycle";
    if (loai == "BICYCLE") return "Bicycle";

    return "";
}

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle();
    Vehicle(int id, string type, int time, int duration);

    int getVehicleID() const;
    string getVehicleType() const;
    int getEntryTime() const;
    int getParkingDuration() const;
    double getParkingFee() const;

    void setVehicleID(int id);
    void setVehicleType(string type);
    void setEntryTime(int time);
    void setParkingDuration(int duration);

    double calculateFee() const;
    void display() const;
};

Vehicle::Vehicle()
    : vehicleID(0), vehicleType(""), entryTime(0),
      parkingDuration(0), parkingFee(0) {}

Vehicle::Vehicle(int id, string type, int time, int duration)
    : vehicleID(id), vehicleType(chuanHoaLoai(type)),
      entryTime(time), parkingDuration(duration), parkingFee(0) {
    parkingFee = calculateFee();
}

int Vehicle::getVehicleID() const {
    return vehicleID;
}

string Vehicle::getVehicleType() const {
    return vehicleType;
}

int Vehicle::getEntryTime() const {
    return entryTime;
}

int Vehicle::getParkingDuration() const {
    return parkingDuration;
}

double Vehicle::getParkingFee() const {
    return parkingFee;
}

void Vehicle::setVehicleID(int id) {
    vehicleID = id;
}

void Vehicle::setVehicleType(string type) {
    vehicleType = chuanHoaLoai(type);
    parkingFee = calculateFee();
}

void Vehicle::setEntryTime(int time) {
    entryTime = time;
    parkingFee = calculateFee();
}

void Vehicle::setParkingDuration(int duration) {
    parkingDuration = duration;
    parkingFee = calculateFee();
}

double Vehicle::calculateFee() const {
    double gia = (vehicleType == "Car") ? 6.0 :
                 (vehicleType == "Motorcycle") ? 4.0 : 2.0;

    bool cao_diem = (entryTime >= 6 && entryTime <= 9) ||
                    (entryTime >= 15 && entryTime <= 18);

    double tong = 0;

    for (int h = 0; h < parkingDuration; h++) {
        if (h < 2)
            tong += gia * (cao_diem ? 1.30 : 0.95);
        else
            tong += gia * 0.90;
    }

    return tong;
}

void Vehicle::display() const {
    cout << "  ID: " << vehicleID
         << " | " << vehicleType
         << " | " << entryTime << "h"
         << " | " << parkingDuration << "h"
         << " | Phi: $" << fixed << setprecision(2)
         << parkingFee << "\n";
}

class ParkingLot {
private:
    int parkID;
    char size;
    static const int MAX_VEHICLES = 3;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

public:
    ParkingLot();
    ParkingLot(int id, char s);

    int getParkID() const;
    char getSize() const;
    int getCurrentVehicleCount() const;

    bool isFull() const;
    bool addVehicle(const Vehicle& v);
    bool removeVehicle(int vID);
    int findVehicleIndex(int vID) const;

    void displayLotInfo() const;
    void displayVehiclesByType(string type) const;
    void getTypeStats(string type, int& dem, double& tong) const;
};

ParkingLot::ParkingLot()
    : parkID(0), size('S'), currentVehicleCount(0) {}

ParkingLot::ParkingLot(int id, char s)
    : parkID(id), size(s), currentVehicleCount(0) {}

int ParkingLot::getParkID() const {
    return parkID;
}

char ParkingLot::getSize() const {
    return size;
}

int ParkingLot::getCurrentVehicleCount() const {
    return currentVehicleCount;
}

bool ParkingLot::isFull() const {
    int cap = (size == 'S') ? 1 : (size == 'M') ? 2 : 3;

    return currentVehicleCount >= cap;
}

bool ParkingLot::addVehicle(const Vehicle& v) {
    if (isFull())
        return false;

    vehicles[currentVehicleCount] = v;
    currentVehicleCount++;

    return true;
}

int ParkingLot::findVehicleIndex(int vID) const {
    for (int i = 0; i < currentVehicleCount; i++) {
        if (vehicles[i].getVehicleID() == vID)
            return i;
    }

    return -1;
}

bool ParkingLot::removeVehicle(int vID) {
    int index = findVehicleIndex(vID);

    if (index == -1)
        return false;

    for (int i = index; i < currentVehicleCount - 1; i++) {
        vehicles[i] = vehicles[i + 1];
    }

    currentVehicleCount--;

    return true;
}

void ParkingLot::displayLotInfo() const {
    cout << "Bai " << parkID << " [" << size << "] "
         << currentVehicleCount << "/"
         << ((size == 'S') ? 1 : (size == 'M') ? 2 : 3)
         << " xe\n";

    for (int i = 0; i < currentVehicleCount; i++) {
        vehicles[i].display();
    }
}

void ParkingLot::displayVehiclesByType(string type) const {
    for (int i = 0; i < currentVehicleCount; i++) {
        if (vehicles[i].getVehicleType() == type)
            vehicles[i].display();
    }
}

void ParkingLot::getTypeStats(string type, int& dem, double& tong) const {
    dem = 0;
    tong = 0;

    for (int i = 0; i < currentVehicleCount; i++) {
        if (vehicles[i].getVehicleType() == type) {
            dem++;
            tong += vehicles[i].getParkingFee();
        }
    }
}

class SystemInterface {
private:
    static const int MAX_LOTS = 10;
    ParkingLot parkingLots[MAX_LOTS];
    int currentLotCount;

    bool isParkIDExists(int pID) const;
    bool isVehicleIDExists(int vID) const;
    int generateRandomID() const;
    void displayReportForType(string type) const;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : currentLotCount(0) {}

bool SystemInterface::isParkIDExists(int pID) const {
    for (int i = 0; i < currentLotCount; i++) {
        if (parkingLots[i].getParkID() == pID)
            return true;
    }

    return false;
}

bool SystemInterface::isVehicleIDExists(int vID) const {
    for (int i = 0; i < currentLotCount; i++) {
        if (parkingLots[i].findVehicleIndex(vID) != -1)
            return true;
    }

    return false;
}

int SystemInterface::generateRandomID() const {
    return rand() % 90000 + 10000;
}

void SystemInterface::displayReportForType(string type) const {
    int dem;
    double tong;
    int demTong = 0;
    double tongTien = 0;

    cout << "\n" << type << ":\n";

    for (int i = 0; i < currentLotCount; i++) {
        parkingLots[i].getTypeStats(type, dem, tong);

        cout << "Bai " << parkingLots[i].getParkID()
             << ": " << dem << " xe | TB: $";

        if (dem > 0)
            cout << fixed << setprecision(2) << tong / dem;
        else
            cout << "0.00";

        cout << "\n";

        demTong += dem;
        tongTien += tong;
    }

    cout << "Toan he thong: ";

    if (demTong == 0)
        cout << "Khong co xe\n";
    else
        cout << demTong << " xe | TB: $"
             << fixed << setprecision(2)
             << tongTien / demTong << "\n";
}

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

        chon = nhapSoNguyen("Chon: ");

        switch (chon) {
        case 1: {
            if (currentLotCount >= MAX_LOTS) {
                cout << "Da du 10 bai xe!\n";
                break;
            }

            int ma = nhapSoNguyen("Ma bai: ");

            if (isParkIDExists(ma)) {
                cout << "Ma bai da ton tai! Tu dong tao ma moi.\n";

                do {
                    ma = generateRandomID();
                } while (isParkIDExists(ma));
            }

            char kt;
            cout << "Kich thuoc (S/M/L): ";
            cin >> kt;
            kt = toupper(kt);

            while (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le! Nhap lai: ";
                cin >> kt;
                kt = toupper(kt);
            }

            parkingLots[currentLotCount] = ParkingLot(ma, kt);
            currentLotCount++;

            cout << "Da tao bai " << ma << "\n";
            break;
        }

        case 2: {
            int ma = nhapSoNguyen("Ma xe: ");

            if (isVehicleIDExists(ma)) {
                cout << "Ma xe da ton tai! Tu dong tao ma moi.\n";

                do {
                    ma = generateRandomID();
                } while (isVehicleIDExists(ma));
            }

            string loai;
            cout << "Loai (Car/Motorcycle/Bicycle): ";
            cin >> loai;
            loai = chuanHoaLoai(loai);

            while (loai == "") {
                cout << "Loai xe khong hop le! Nhap lai: ";
                cin >> loai;
                loai = chuanHoaLoai(loai);
            }

            int gio = nhapSoNguyen("Gio vao (0-23): ");

            while (gio < 0 || gio > 23) {
                cout << "Gio khong hop le! Nhap lai: ";
                gio = nhapSoNguyen("");
            }

            int tg = nhapSoNguyen("Thoi luong (1-23): ");

            while (tg < 1 || tg > 23) {
                cout << "Thoi luong khong hop le! Nhap lai: ";
                tg = nhapSoNguyen("");
            }

            Vehicle v(ma, loai, gio, tg);
            bool ok = false;

            for (int i = 0; i < currentLotCount; i++) {
                if (parkingLots[i].addVehicle(v)) {
                    cout << "Da them xe " << ma
                         << " vao bai " << parkingLots[i].getParkID()
                         << " | Phi: $" << fixed << setprecision(2)
                         << v.calculateFee() << "\n";

                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Tat ca bai da day hoac chua co bai xe!\n";

            break;
        }

        case 3: {
            int ma = nhapSoNguyen("Ma bai can xoa: ");
            int index = -1;

            for (int i = 0; i < currentLotCount; i++) {
                if (parkingLots[i].getParkID() == ma) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                cout << "Khong tim thay bai xe!\n";
                break;
            }

            for (int i = index; i < currentLotCount - 1; i++) {
                parkingLots[i] = parkingLots[i + 1];
            }

            currentLotCount--;

            cout << "Da xoa bai " << ma << "\n";
            break;
        }

        case 4: {
            int ma = nhapSoNguyen("Ma xe can lay ra: ");
            bool ok = false;

            for (int i = 0; i < currentLotCount; i++) {
                if (parkingLots[i].removeVehicle(ma)) {
                    cout << "Da lay xe ra khoi bai "
                         << parkingLots[i].getParkID() << "\n";
                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Khong tim thay xe!\n";

            break;
        }

        case 5: {
            for (int i = 0; i < currentLotCount; i++) {
                parkingLots[i].displayLotInfo();
            }

            break;
        }

        case 6: {
            int ma = nhapSoNguyen("Ma bai: ");
            bool ok = false;

            for (int i = 0; i < currentLotCount; i++) {
                if (parkingLots[i].getParkID() == ma) {
                    parkingLots[i].displayLotInfo();
                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Khong tim thay bai xe!\n";

            break;
        }

        case 7: {
            string loai;

            cout << "Loai xe: ";
            cin >> loai;
            loai = chuanHoaLoai(loai);

            if (loai == "") {
                cout << "Loai xe khong hop le!\n";
                break;
            }

            bool timThay = false;

            for (int i = 0; i < currentLotCount; i++) {
                int dem;
                double tong;

                parkingLots[i].getTypeStats(loai, dem, tong);

                if (dem > 0) {
                    cout << "\nBai " << parkingLots[i].getParkID() << ":\n";
                    parkingLots[i].displayVehiclesByType(loai);
                    timThay = true;
                }
            }

            if (!timThay)
                cout << "Khong tim thay xe!\n";

            break;
        }

        case 8: {
            cout << "\n===== BAO CAO PHI TRUNG BINH =====\n";

            displayReportForType("Car");
            displayReportForType("Motorcycle");
            displayReportForType("Bicycle");

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
    srand(time(0));

    SystemInterface sys;
    sys.runMenu();

    return 0;
}

