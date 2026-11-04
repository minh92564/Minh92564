#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
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
        parkingDuration = 0;
        parkingFee = 0;
    }

    Vehicle(int id, string loai, int gio, int tg) {
        vehicleID = id;

        for (int i = 0; i < loai.length(); i++) {
            loai[i] = toupper(loai[i]);
        }

        if (loai == "CAR")
            vehicleType = "Car";
        else if (loai == "MOTORCYCLE")
            vehicleType = "Motorcycle";
        else if (loai == "BICYCLE")
            vehicleType = "Bicycle";
        else
            vehicleType = "";

        entryTime = gio;
        parkingDuration = tg;
        parkingFee = calculateFee();
    }

    int GetVehicleID() const {
        return vehicleID;
    }

    string GetVehicleType() const {
        return vehicleType;
    }

    double calculateFee() const {
        double donGia = 0;

        if (vehicleType == "Car")
            donGia = 6;
        else if (vehicleType == "Motorcycle")
            donGia = 4;
        else if (vehicleType == "Bicycle")
            donGia = 2;

        double phi = 0;

        bool caoDiem = (entryTime >= 6 && entryTime < 10) ||
                       (entryTime >= 15 && entryTime < 19);

        for (int i = 1; i <= parkingDuration; i++) {
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

    void display() const {
        cout << "Ma xe: " << vehicleID << endl;
        cout << "Loai xe: " << vehicleType << endl;
        cout << "Gio vao: " << entryTime << endl;
        cout << "Thoi gian do: " << parkingDuration << endl;
        cout << "Phi do xe: " << parkingFee << endl;
    }
};
class ParkingLot {
private:
    int parkID;
    char size;

    static const int MAX_VEHICLES = 3;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

public:
    ParkingLot() {
        parkID = 0;
        size = 'S';
        currentVehicleCount = 0;
    }

    ParkingLot(int id, char kt) {
        parkID = id;
        size = kt;
        currentVehicleCount = 0;
    }

    int GetParkID() const {
        return parkID;
    }
int main(){
	
}

