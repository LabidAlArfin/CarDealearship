#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include"Car.h"

//will this code run so far... no idea but mostly not XD

using namespace std;

int limit_days;

class LuxuryCar :public Car {
private:
    int days_booked;
    bool isAvailable;
    vector<LuxuryCar> cars;


public:
    // Default constructor
    LuxuryCar()
        : Car(), days_booked(0), isAvailable(true) {}

    // Parameterized constructor
    LuxuryCar(int& id, const string& name, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, int days_booked, bool isAvailable)
        : Car(id, name, type, makeDate, rentDate, returnDate, mileage, pricing),
        days_booked(days_booked),
        isAvailable(isAvailable) {
    }


    static vector<LuxuryCar> readFile() {
        vector<LuxuryCar> cars;
        ifstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file." << endl;
            return cars;
        }

        string line;
        getline(file, line);  // Read the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string brand, type, year, mileage, price, available, id;

            ss  >> brand >> type >> year >> mileage >> price >> available >> id;

            int idVal = stoi(id);
            string model = brand.substr(brand.find('-') + 1); // Parse model from brand
            brand = brand.substr(0, brand.find('-')); // Parse brand from brand

            int yearVal = stoi(year);
            float mileageVal = stof(mileage);
            float priceVal = stof(price);
            bool isAvailable = (available == "1");

            Date makeDate(1, 1, yearVal); // Assume make date is 1/1/{year}
            Date rentDate(2, 6, 2023); // Default rent date
            Date returnDate(2, 6, 2023); // Default return date

            LuxuryCar car(idVal, brand, type, makeDate, rentDate, returnDate, mileageVal, priceVal, 0, isAvailable);
            cars.push_back(car);
        }

        return cars;
    }

    void printFile() {
        ofstream outputFile("LuxuryCars.txt");

        if (outputFile.is_open()) {
            // Print header
            outputFile << "Name\t\t\tType\tYear\tTotal Mileage\tRent Price\tAvailable\tID\n";

            // Print car information
            for (int i = 0; i < cars.size(); i++) {
                outputFile << cars[i].getBrand() << "\t" << cars[i].getType() << "\t"
                    << cars[i].getYear() << "\t" << cars[i].getMileage() << "\t\t"
                    << cars[i].getPrice() << "\t\t" << cars[i].isAvailable << "\t\t"
                    << cars[i].getID() << "\n";
            }

            outputFile.close();
            std::cout << "Luxury cars information printed to file: LuxuryCars.txt" << std::endl;
        }
        else {
            std::cout << "Unable to open the file for printing." << std::endl;
        }
    }

    
    //findCar()

    int FindCarUsingName(const string& name) {

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getBrand() == name && cars[i].getType() == "Luxury") {
                return i; // Return the index of the car if found
            }
        }
        return -1; // Return -1 if the car is not found
    }

    int FindCarByID(const int& id) {
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getType() == "Luxury") {
                if (cars[i].getID() == id) {
                    return i; // Return the index of the car if found
                }
            }
        }
        return -1; // Return -1 if the car is not found
    }

    float calculatePricing(int index) override {
        float pricing = 0.0;


        //create a find function
        float rentPrice = cars[index].getPrice();
        pricing = rentPrice;


        //int extraDays = days_booked - 2; // Calculate the number of extra days beyond the initial 2 days
        //if (extraDays > 0) {
        //    float increment = rentPrice * 0.05; // 5% increment
        //    int weeksPassed = extraDays / 7;
        //    int daysWithinWeek = extraDays % 7;

        //    // Calculate pricing for the initial 2 days
        //    pricing += 2 * rentPrice;

        //    // Calculate pricing for the additional days
        //    pricing += 2 * increment; // Pricing for the 3rd and 4th days

        //    // Calculate pricing for the additional weeks
        //    for (int i = 0; i < weeksPassed; i++) {
        //        pricing += 2 * increment * pow(1.05, i + 1);
        //    }

        //    // Calculate pricing for the remaining days within the last week
        //    pricing += daysWithinWeek * increment * pow(1.05, weeksPassed + 1);
        //}
        //else {
        //    // Calculate pricing for the initial 2 days
        //    pricing = 2 * rentPrice;
        //}

        limit_days = 2; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                pricing *= 2; //adds pricing for 2 days
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing = rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        if (days_booked > 14) { cout << "Why is it so loong!" << endl; }

        return pricing;
    }

    float calculateMileage(int index) override {
        float milesPassed = 0.0;


        float rentPrice = 0.0;
        //will change after testing
        float milesPassed = cars[index].getMileage();
        if (isAvailable == 0) {
            milesPassed += 400;
        }  
        UpdateCarAvailability(index);
        return milesPassed;
    }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable;  }

    //gotta make one but to lazy to make it 
    void UpdateCarAvailability(int index) {
        cars[index].setAvailability(false); // Set the availability of the car to false (0)

        // Update the CarInfo.txt file
        ofstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file for updating car availability." << endl;
            return;
        }

        // Write the header line
        file << "Brand\tType\tYear\tMileage\tPrice\tAvailable\tID" << endl;

        // Write the updated car information to the file
        for (int i = 0; i < cars.size(); i++) {
            file << cars[i].getBrand() << "\t";
            file << cars[i].getType() << "\t";
            file << cars[i].getYear() << "\t";
            file << cars[i].getMileage() << "\t";
            file << cars[i].getPrice() << "\t";
            file << (cars[i].isAvailable ? "1" : "0") << "\t";
            file << cars[i].getID() << endl;
        }

        file.close();
    }
};



class EconomicCar :public Car {
private:
    int days_booked;
    bool isAvailable;
    vector<EconomicCar> cars;


public:
    // Default constructor
    EconomicCar()
        : Car(), days_booked(0), isAvailable(true) {}

    // Parameterized constructor
    EconomicCar(int& id, const string& name, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, int days_booked, bool isAvailable)
        : Car(id, name, type, makeDate, rentDate, returnDate, mileage, pricing),
        days_booked(days_booked),
        isAvailable(isAvailable) {
    }


    static vector<EconomicCar> readFile() {
        vector<EconomicCar> cars;
        ifstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file." << endl;
            return cars;
        }

        string line;
        getline(file, line);  // Read the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string brand, type, year, mileage, price, available, id;

            ss >> brand >> type >> year >> mileage >> price >> available >> id;

            int idVal = stoi(id);
            string model = brand.substr(brand.find('-') + 1); // Parse model from brand
            brand = brand.substr(0, brand.find('-')); // Parse brand from brand

            int yearVal = stoi(year);
            float mileageVal = stof(mileage);
            float priceVal = stof(price);
            bool isAvailable = (available == "1");

            Date makeDate(1, 1, yearVal); // Assume make date is 1/1/{year}
            Date rentDate(2, 6, 2023); // Default rent date
            Date returnDate(2, 6, 2023); // Default return date

            EconomicCar car(idVal, brand, type, makeDate, rentDate, returnDate, mileageVal, priceVal, 0, isAvailable);
            cars.push_back(car);
        }

        return cars;
    }


    //findCar()

    int FindCarUsingName(const string& name) {

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getBrand() == name && cars[i].getType() == "Economic") {
                return i; // Return the index of the car if found
            }
        }
        return -1; // Return -1 if the car is not found
    }

    int FindCarByID(const int& id) {
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getType() == "Economic") {
                if (cars[i].getID() == id) {
                    return i; // Return the index of the car if found
                }
            }
        }
        return -1; // Return -1 if the car is not found
    }

    float calculatePricing(int index) override {
        float pricing = 0.0;


        //create a find function
        float rentPrice = cars[index].getPrice();
        pricing = rentPrice;


        limit_days = 7; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                pricing *= 7; //adds pricing for 7 days
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing = rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        if (days_booked > 30) { cout << "Why is it so loong!" << endl; }

        return pricing;
    }

    float calculateMileage(int index) override {
        float milesPassed = 0.0;


        float rentPrice = 0.0;
        //will change after testing
        float milesPassed = cars[index].getMileage();
        if (isAvailable == 0) {
            milesPassed += 1000;
        }
        UpdateCarAvailability(index);
        return milesPassed;
    }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }

    //gotta make one but to lazy to make it 
    void UpdateCarAvailability(int index) {
        cars[index].setAvailability(false); // Set the availability of the car to false (0)

        // Update the CarInfo.txt file
        ofstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file for updating car availability." << endl;
            return;
        }

        // Write the header line
        file << "Brand\tType\tYear\tMileage\tPrice\tAvailable\tID" << endl;

        // Write the updated car information to the file
        for (int i = 0; i < cars.size(); i++) {
            file << cars[i].getBrand() << "\t";
            file << cars[i].getType() << "\t";
            file << cars[i].getYear() << "\t";
            file << cars[i].getMileage() << "\t";
            file << cars[i].getPrice() << "\t";
            file << (cars[i].isAvailable ? "1" : "0") << "\t";
            file << cars[i].getID() << endl;
        }

        file.close();
    }


};

class SportsCar :public Car {
private:
    int days_booked;
    bool isAvailable;
    vector<EconomicCar> cars;


public:
    // Default constructor
    SportsCar()
        : Car(), days_booked(0), isAvailable(true) {}

    // Parameterized constructor
    SportsCar(int& id, const string& name, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, int days_booked, bool isAvailable)
        : Car(id, name, type, makeDate, rentDate, returnDate, mileage, pricing),
        days_booked(days_booked),
        isAvailable(isAvailable) {
    }


    static vector<SportsCar> readFile() {
        vector<SportsCar> cars;
        ifstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file." << endl;
            return cars;
        }

        string line;
        getline(file, line);  // Read the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string brand, type, year, mileage, price, available, id;

            ss >> brand >> type >> year >> mileage >> price >> available >> id;

            int idVal = stoi(id);
            string model = brand.substr(brand.find('-') + 1); // Parse model from brand
            brand = brand.substr(0, brand.find('-')); // Parse brand from brand

            int yearVal = stoi(year);
            float mileageVal = stof(mileage);
            float priceVal = stof(price);
            bool isAvailable = (available == "1");

            Date makeDate(1, 1, yearVal); // Assume make date is 1/1/{year}
            Date rentDate(2, 6, 2023); // Default rent date
            Date returnDate(2, 6, 2023); // Default return date

            SportsCar car(idVal, brand, type, makeDate, rentDate, returnDate, mileageVal, priceVal, 0, isAvailable);
            cars.push_back(car);
        }

        return cars;
    }


    //findCar()

    int FindCarUsingName(const string& name) {

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getBrand() == name && cars[i].getType() == "Sport") {
                return i; // Return the index of the car if found
            }
        }
        return -1; // Return -1 if the car is not found
    }

    int FindCarByID(const int& id) {
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getType() == "Sport") {
                if (cars[i].getID() == id) {
                    return i; // Return the index of the car if found
                }
            }
        }
        return -1; // Return -1 if the car is not found
    }

    float calculatePricing(int index) override {
        float pricing = 0.0;


        //create a find function
        float rentPrice = cars[index].getPrice();
        pricing = rentPrice;


        limit_days = 1; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
               
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing += rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        if (days_booked > 4) { cout << "Why is it sooo loong!" << endl; }

        return pricing;
    }

    float calculateMileage(int index) override {
        float milesPassed = 0.0;


        float rentPrice = 0.0;
        //will change after testing
        float milesPassed = cars[index].getMileage();
        if (isAvailable == 0) {
            milesPassed += 300;
        }
        UpdateCarAvailability(index);
        return milesPassed;
    }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }

    //gotta make one but to lazy to make it 
    void UpdateCarAvailability(int index) {
        cars[index].setAvailability(false); // Set the availability of the car to false (0)

        // Update the CarInfo.txt file
        ofstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file for updating car availability." << endl;
            return;
        }

        // Write the header line
        file << "Brand\tType\tYear\tMileage\tPrice\tAvailable\tID" << endl;

        // Write the updated car information to the file
        for (int i = 0; i < cars.size(); i++) {
            file << cars[i].getBrand() << "\t";
            file << cars[i].getType() << "\t";
            file << cars[i].getYear() << "\t";
            file << cars[i].getMileage() << "\t";
            file << cars[i].getPrice() << "\t";
            file << (cars[i].isAvailable ? "1" : "0") << "\t";
            file << cars[i].getID() << endl;
        }

        file.close();
    }

};

class Van :public Car {
private:
    int days_booked;
    bool isAvailable;
    vector<EconomicCar> cars;


public:
    // Default constructor
    Van()
        : Car(), days_booked(0), isAvailable(true) {}

    // Parameterized constructor
    Van(int& id, const string& name, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, int days_booked, bool isAvailable)
        : Car(id, name, type, makeDate, rentDate, returnDate, mileage, pricing),
        days_booked(days_booked),
        isAvailable(isAvailable) {
    }


    static vector<Van> readFile() {
        vector<Van> cars;
        ifstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file." << endl;
            return cars;
        }

        string line;
        getline(file, line);  // Read the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string brand, type, year, mileage, price, available, id;

            ss >> brand >> type >> year >> mileage >> price >> available >> id;

            int idVal = stoi(id);
            string model = brand.substr(brand.find('-') + 1); // Parse model from brand
            brand = brand.substr(0, brand.find('-')); // Parse brand from brand

            int yearVal = stoi(year);
            float mileageVal = stof(mileage);
            float priceVal = stof(price);
            bool isAvailable = (available == "1");

            Date makeDate(1, 1, yearVal); // Assume make date is 1/1/{year}
            Date rentDate(2, 6, 2023); // Default rent date
            Date returnDate(2, 6, 2023); // Default return date

            Van car(idVal, brand, type, makeDate, rentDate, returnDate, mileageVal, priceVal, 0, isAvailable);
            cars.push_back(car);
        }

        return cars;
    }


    //findCar()

    int FindCarUsingName(const string& name) {

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getBrand() == name && cars[i].getType() == "Van") {
                return i; // Return the index of the car if found and checks type is Van
            }
        }
        return -1; // Return -1 if the car is not found
    }

    int FindCarByID(const int& id) {
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].getType() == "Van") {
                if (cars[i].getID() == id) {
                    return i; // Return the index of the car if found
                }
            }
        }
        return -1; // Return -1 if the car is not found
    }

    float calculatePricing(int index) override {
        float pricing = 0.0;


        //create a find function
        float rentPrice = cars[index].getPrice();
        pricing = rentPrice;


        limit_days = 10; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                pricing *= 10;
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing = rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        if (days_booked > 45) { cout << "Why is it sooo loong!" << endl; }

        return pricing;
    }

    float calculateMileage(int index) override {
        float milesPassed = 0.0;


        float rentPrice = 0.0;
        //will change after testing
        float milesPassed = cars[index].getMileage();
        if (isAvailable == 0) {
            milesPassed += 1500;
        }
        UpdateCarAvailability(index);
        return milesPassed;
    }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }

    //gotta make one but to lazy to make it 
    void UpdateCarAvailability(int index) {
        cars[index].setAvailability(false); // Set the availability of the car to false (0)

        // Update the CarInfo.txt file
        ofstream file("CarInfo.txt");
        if (!file) {
            cout << "Failed to open the file for updating car availability." << endl;
            return;
        }

        // Write the header line
        file << "Brand\tType\tYear\tMileage\tPrice\tAvailable\tID" << endl;

        // Write the updated car information to the file
        for (int i = 0; i < cars.size(); i++) {
            file << cars[i].getBrand() << "\t";
            file << cars[i].getType() << "\t";
            file << cars[i].getYear() << "\t";
            file << cars[i].getMileage() << "\t";
            file << cars[i].getPrice() << "\t";
            file << (cars[i].isAvailable ? "1" : "0") << "\t";
            file << cars[i].getID() << endl;
        }

        file.close();
    }

};
