
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle() {
        vehicleID = 0;
        vehicleType = "";
        entryTime = 0;
        parkingDuration = 1;
        parkingFee = 0;
    }

    Vehicle(int id, string type, int time, int duration) {
        vehicleID = id;
        vehicleType = type;
        entryTime = time;
        parkingDuration = duration;
        parkingFee = 0;
        calculateFee();
    }

    int getVehicleID() const {
        return vehicleID;
    }

    string getVehicleType() const {
        return vehicleType;
    }

    int getEntryTime() const {
        return entryTime;
    }

    int getParkingDuration() const {
        return parkingDuration;
    }

    double getParkingFee() const {
        return parkingFee;
    }

    void setVehicleID(int id) {
        vehicleID = id;
    }

    void setVehicleType(string type) {
        vehicleType = type;
    }

    void setEntryTime(int time) {
        entryTime = time;
    }

    void setParkingDuration(int duration) {
        parkingDuration = duration;
    }

    void calculateFee() {
        double rate = 0;

        string type = vehicleType;

        for (int i = 0; i < (int)type.length(); i++) {
            type[i] = toupper(type[i]);
        }

        if (type == "CAR") {
            rate = 6;
        }
        else if (type == "MOTORCYCLE") {
            rate = 4;
        }
        else if (type == "BICYCLE") {
            rate = 2;
        }

        double total = 0;

        for (int i = 0; i < parkingDuration; i++) {
            int hour = (entryTime + i) % 24;

            if ((hour >= 6 && hour < 9) ||
                (hour >= 15 && hour < 18)) {
                if (i < 2)
                    total += rate * 1.3;
                else
                    total += rate * 0.9;
            }
            else {
                if (i < 2)
                    total += rate * 0.95;
                else
                    total += rate * 0.9;
            }
        }

        parkingFee = total;
    }

    void display() const {
        cout << left
             << setw(12) << vehicleID
             << setw(15) << vehicleType
             << setw(12) << entryTime
             << setw(15) << parkingDuration
             << fixed << setprecision(2)
             << parkingFee << endl;
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    int capacity;
    int currentVehicleCount;
    Vehicle** vehicles;

    void resize(int newCapacity) {
        Vehicle** temp = new Vehicle*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            temp[i] = nullptr;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            temp[i] = vehicles[i];
        }

        delete[] vehicles;
        vehicles = nullptr;

        vehicles = temp;
        capacity = newCapacity;
    }

public:
    ParkingLot(int id = 0, char s = 'S') {
        parkID = id;
        size = toupper(s);

        if (size == 'S')
            capacity = 1;
        else if (size == 'M')
            capacity = 2;
        else
            capacity = 3;

        currentVehicleCount = 0;

        vehicles = new Vehicle*[capacity];

        for (int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }
    }

    ~ParkingLot() {
        for (int i = 0; i < currentVehicleCount; i++) {
            delete vehicles[i];
            vehicles[i] = nullptr;
        }

        delete[] vehicles;
        vehicles = nullptr;
    }

    ParkingLot(const ParkingLot& other) {
        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];

        for (int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            vehicles[i] = new Vehicle(*other.vehicles[i]);
        }
    }

    ParkingLot& operator=(const ParkingLot& other) {
        if (this != &other) {
            for (int i = 0; i < currentVehicleCount; i++) {
                delete vehicles[i];
                vehicles[i] = nullptr;
            }

            delete[] vehicles;
            vehicles = nullptr;

            parkID = other.parkID;
            size = other.size;
            capacity = other.capacity;
            currentVehicleCount = other.currentVehicleCount;

            vehicles = new Vehicle*[capacity];

            for (int i = 0; i < capacity; i++) {
                vehicles[i] = nullptr;
            }

            for (int i = 0; i < currentVehicleCount; i++) {
                vehicles[i] = new Vehicle(*other.vehicles[i]);
            }
        }

        return *this;
    }

    int getParkID() const {
        return parkID;
    }

    int getCurrentVehicleCount() const {
        return currentVehicleCount;
    }

    bool addVehicle(const Vehicle& v) {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i]->getVehicleID() == v.getVehicleID()) {
                cout << "Vehicle ID da ton tai!\n";
                return false;
            }
        }

        if (currentVehicleCount == capacity) {
            resize(capacity * 2);
        }

        vehicles[currentVehicleCount] = new Vehicle(v);
        currentVehicleCount++;

        cout << "Them xe thanh cong!\n";
        return true;
    }

    bool removeVehicle(int vID) {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i]->getVehicleID() == vID) {
                delete vehicles[i];
                vehicles[i] = nullptr;

                for (int j = i; j < currentVehicleCount - 1; j++) {
                    vehicles[j] = vehicles[j + 1];
                }

                currentVehicleCount--;
                vehicles[currentVehicleCount] = nullptr;

                cout << "Xoa xe thanh cong!\n";
                return true;
            }
        }

        return false;
    }

    bool hasVehicle(int id) const {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i]->getVehicleID() == id)
                return true;
        }

        return false;
    }

    void display() const {
        cout << "\nMa bai: " << parkID;
        cout << "\nKich thuoc: " << size;
        cout << "\nSuc chua hien tai: " << capacity;
        cout << "\nSo xe hien co: " << currentVehicleCount << endl;

        if (currentVehicleCount == 0) {
            cout << "Bai chua co xe!\n";
            return;
        }

        cout << left
             << setw(12) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(12) << "Gio vao"
             << setw(15) << "Thoi gian"
             << "Phi do xe\n";

        for (int i = 0; i < currentVehicleCount; i++) {
            vehicles[i]->display();
        }
    }

    void displayByType(string type) const {
        for (int i = 0; i < currentVehicleCount; i++) {
            string t = vehicles[i]->getVehicleType();

            for (int j = 0; j < (int)t.length(); j++) {
                t[j] = toupper(t[j]);
            }

            string search = type;

            for (int j = 0; j < (int)search.length(); j++) {
                search[j] = toupper(search[j]);
            }

            if (t == search) {
                vehicles[i]->display();
            }
        }
    }

    double averageFeeByType(string type) const {
        double sum = 0;
        int count = 0;

        for (int i = 0; i < currentVehicleCount; i++) {
            string t = vehicles[i]->getVehicleType();

            for (int j = 0; j < (int)t.length(); j++) {
                t[j] = toupper(t[j]);
            }

            string search = type;

            for (int j = 0; j < (int)search.length(); j++) {
                search[j] = toupper(search[j]);
            }

            if (t == search) {
                sum += vehicles[i]->getParkingFee();
                count++;
            }
        }

        if (count == 0)
            return -1;

        return sum / count;
    }
};

class SystemInterface {
private:
    int lotCapacity;
    int currentLotCount;
    ParkingLot** parkingLots;

    void resizeSystem(int newCapacity) {
        ParkingLot** temp = new ParkingLot*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            temp[i] = nullptr;
        }

        for (int i = 0; i < currentLotCount; i++) {
            temp[i] = parkingLots[i];
        }

        delete[] parkingLots;
        parkingLots = nullptr;

        parkingLots = temp;
        lotCapacity = newCapacity;
    }

    int findLot(int id) const {
        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i]->getParkID() == id)
                return i;
        }

        return -1;
    }

public:
    SystemInterface() {
        lotCapacity = 5;
        currentLotCount = 0;

        parkingLots = new ParkingLot*[lotCapacity];

        for (int i = 0; i < lotCapacity; i++) {
            parkingLots[i] = nullptr;
        }
    }

    ~SystemInterface() {
        for (int i = 0; i < currentLotCount; i++) {
            delete parkingLots[i];
            parkingLots[i] = nullptr;
        }

        delete[] parkingLots;
        parkingLots = nullptr;
    }

    SystemInterface(const SystemInterface& other) {
        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];

        for (int i = 0; i < lotCapacity; i++) {
            parkingLots[i] = nullptr;
        }

        for (int i = 0; i < currentLotCount; i++) {
            parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
        }
    }

    SystemInterface& operator=(const SystemInterface& other) {
        if (this != &other) {
            for (int i = 0; i < currentLotCount; i++) {
                delete parkingLots[i];
                parkingLots[i] = nullptr;
            }

            delete[] parkingLots;
            parkingLots = nullptr;

            lotCapacity = other.lotCapacity;
            currentLotCount = other.currentLotCount;

            parkingLots = new ParkingLot*[lotCapacity];

            for (int i = 0; i < lotCapacity; i++) {
                parkingLots[i] = nullptr;
            }

            for (int i = 0; i < currentLotCount; i++) {
                parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
            }
        }

        return *this;
    }

    void createLot() {
        int id;
        char s;

        cout << "Nhap ma bai: ";
        cin >> id;

        if (findLot(id) != -1) {
            cout << "Ma bai da ton tai!\n";
            return;
        }

        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> s;

        s = toupper(s);

        if (s != 'S' && s != 'M' && s != 'L') {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        if (currentLotCount == lotCapacity) {
            resizeSystem(lotCapacity * 2);
        }

        parkingLots[currentLotCount] = new ParkingLot(id, s);
        currentLotCount++;

        cout << "Tao bai do thanh cong!\n";
    }

    void addVehicleToLot() {
        int id;

        cout << "Nhap ma bai: ";
        cin >> id;

        int index = findLot(id);

        if (index == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        int vehicleID, time, duration;
        string type;

        cout << "Nhap ma xe: ";
        cin >> vehicleID;

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i]->hasVehicle(vehicleID)) {
                cout << "Ma xe da ton tai trong he thong!\n";
                return;
            }
        }

        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> type;

        for (int i = 0; i < (int)type.length(); i++) {
            type[i] = toupper(type[i]);
        }

        if (type != "CAR" && type != "MOTORCYCLE" && type != "BICYCLE") {
            cout << "Loai xe khong hop le!\n";
            return;
        }

        cout << "Nhap gio vao (0-23): ";
        cin >> time;

        cout << "Nhap thoi gian do (1-23): ";
        cin >> duration;

        if (time < 0 || time > 23 || duration < 1 || duration > 23) {
            cout << "Thong tin thoi gian khong hop le!\n";
            return;
        }

        Vehicle v(vehicleID, type, time, duration);
        parkingLots[index]->addVehicle(v);
    }

    void deleteLot() {
        int id;

        cout << "Nhap ma bai can xoa: ";
        cin >> id;

        int index = findLot(id);

        if (index == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        delete parkingLots[index];
        parkingLots[index] = nullptr;

        for (int i = index; i < currentLotCount - 1; i++) {
            parkingLots[i] = parkingLots[i + 1];
        }

        currentLotCount--;
        parkingLots[currentLotCount] = nullptr;

        cout << "Xoa bai do thanh cong!\n";
    }

    void removeVehicleFromLot() {
        int id, vehicleID;

        cout << "Nhap ma bai: ";
        cin >> id;

        int index = findLot(id);

        if (index == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        cout << "Nhap ma xe can xoa: ";
        cin >> vehicleID;

        if (!parkingLots[index]->removeVehicle(vehicleID)) {
            cout << "Khong tim thay xe!\n";
        }
    }

    void displayAllLots() const {
        if (currentLotCount == 0) {
            cout << "He thong chua co bai do!\n";
            return;
        }

        for (int i = 0; i < currentLotCount; i++) {
            cout << "\n========== BAI DO " << i + 1 << " ==========\n";
            parkingLots[i]->display();
        }
    }

    void displayOneLot() const {
        int id;

        cout << "Nhap ma bai: ";
        cin >> id;

        int index = findLot(id);

        if (index == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        parkingLots[index]->display();
    }

    void searchVehicleByType() const {
        string type;

        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> type;

        for (int i = 0; i < (int)type.length(); i++) {
            type[i] = toupper(type[i]);
        }

        if (type != "CAR" && type != "MOTORCYCLE" && type != "BICYCLE") {
            cout << "Loai xe khong hop le!\n";
            return;
        }

        cout << "\nDanh sach xe:\n";

        cout << left
             << setw(12) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(12) << "Gio vao"
             << setw(15) << "Thoi gian"
             << "Phi do xe\n";

        bool found = false;

        for (int i = 0; i < currentLotCount; i++) {
            int before = 0;

            for (int j = 0; j < currentLotCount; j++) {
                if (j != i) {
                    before += 0;
                }
            }

            parkingLots[i]->displayByType(type);
        }
    }

    void averageFeeReport() const {
        string types[3] = {"CAR", "MOTORCYCLE", "BICYCLE"};

        cout << "\n===== PHI DO XE TRUNG BINH =====\n";

        for (int i = 0; i < 3; i++) {
            double sum = 0;
            int count = 0;

            for (int j = 0; j < currentLotCount; j++) {
                double avg = parkingLots[j]->averageFeeByType(types[i]);

                if (avg >= 0) {
                    int vehicleCount = 0;

                    for (int k = 0; k < currentLotCount; k++) {
                        if (k == j) {
                            vehicleCount = 1;
                        }
                    }

                    sum += avg;
                    count += vehicleCount;
                }
            }

            if (count > 0) {
                cout << types[i] << ": "
                     << fixed << setprecision(2)
                     << sum / count << endl;
            }
            else {
                cout << types[i] << ": Chua co xe\n";
            }
        }
    }

    void runMenu() {
        int choice;

        do {
            cout << "\n========== QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot bai do xe\n";
            cout << "4. Lay xe ra khoi bai do\n";
            cout << "5. Hien thi tat ca bai do\n";
            cout << "6. Hien thi xe theo bai\n";
            cout << "7. Tim xe theo loai\n";
            cout << "8. Bao cao phi do xe trung binh\n";
            cout << "9. Thoat\n";
            cout << "Lua chon: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createLot();
                    break;
                case 2:
                    addVehicleToLot();
                    break;
                case 3:
                    deleteLot();
                    break;
                case 4:
                    removeVehicleFromLot();
                    break;
                case 5:
                    displayAllLots();
                    break;
                case 6:
                    displayOneLot();
                    break;
                case 7:
                    searchVehicleByType();
                    break;
                case 8:
                    averageFeeReport();
                    break;
                case 9:
                    cout << "Dang giai phong bo nho...\n";
                    cout << "Ket thuc chuong trinh!\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
            }

        } while (choice != 9);
    }
};

int main() {
    SystemInterface system;
    system.runMenu();

    return 0;
}

