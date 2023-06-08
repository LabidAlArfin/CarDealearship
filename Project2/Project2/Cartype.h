#include<iostream>
#include<fstream>
#include<vector>
#include"Car.h"

//will this code run so far... no idea but mostly not XD

using namespace std;

int limit_days;

class LuxuryCar :public Car {
private:
    string model;// parse brand and model 
    int days_booked;
    bool isBooked;
    ifstream inputFile;

public:
    // Default constructor
    LuxuryCar() : Car(),
        model(""),
        days_booked(0),
        isBooked(false),
        inputFile("CarInfo.txt") {}

    // Parameterized constructor
    LuxuryCar(int id, const string& brand, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, const string& model, int days_booked, bool isBooked)
        : Car(id, brand, type, makeDate, rentDate, returnDate, mileage, pricing),
        model(model),
        days_booked(days_booked),
        isBooked(isBooked),
        inputFile("CarInfo.txt") {}


    float calculatePricing() override {
        float pricing = 0.0;

        float pricing = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return pricing;
        }

        string line;
        bool found = false;
        vector<string> columns;
        while (getline(inputFile, line)) {
            // Skip the header line
            if (line.find("Name") != string::npos) {
                continue;
            }

            // Split the line into columns
           
            size_t pos = 0;
            while (pos != string::npos) {
                size_t nextPos = line.find('\t', pos);
                if (nextPos != string::npos) {
                    columns.push_back(line.substr(pos, nextPos - pos));
                    pos = nextPos + 1;
                }
                else {
                    columns.push_back(line.substr(pos));
                    pos = nextPos;
                }
            }

            // Check the conditions for reading from the file
            string carType = columns[1];
            string availabilityStr = columns[5];
            if (carType == "Luxury" && (isBooked == false || availabilityStr == "1")) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No matching car found in the input file." << endl;
            return pricing;
        }

        float rentPrice = stof(columns[4]);
        pricing = rentPrice;

        return pricing;

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

        inputFile.close();
        return pricing;
    }

    float calculateMileage() override {
        float milesPassed = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return milesPassed;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            if (line.find(model) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Car model not found in the input file." << endl;
            return milesPassed;
        }

        float rentPrice = 0.0;
        inputFile.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore the preceding columns
        inputFile >> milesPassed;
       
        if (isBooked) {
            milesPassed += 400;
        }  
        return milesPassed;
    }

    //gotta make one but to lazy to make it 
    bool isSelected() {
        
    }
};



class EconomicCar :public Car {
private:
    string model;// parse brand and model 
    int days_booked;
    bool isBooked;
    ifstream inputFile;

public:
    // Default constructor
    EconomicCar() : Car(),
        model(""),
        days_booked(0),
        isBooked(false),
        inputFile("CarInfo.txt") {}

    // Parameterized constructor
    EconomicCar(int id, const string& brand, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, const string& model, int days_booked, bool isBooked)
        : Car(id, brand, type, makeDate, rentDate, returnDate, mileage, pricing),
        model(model),
        days_booked(days_booked),
        isBooked(isBooked),
        inputFile("CarInfo.txt") {}

    float calculatePricing() override {
        float pricing = 0.0;

        float pricing = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return pricing;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            // Skip the header line
            if (line.find("Name") != string::npos) {
                continue;
            }

            // Split the line into columns
            vector<string> columns;
            size_t pos = 0;
            while (pos != string::npos) {
                size_t nextPos = line.find('\t', pos);
                if (nextPos != string::npos) {
                    columns.push_back(line.substr(pos, nextPos - pos));
                    pos = nextPos + 1;
                }
                else {
                    columns.push_back(line.substr(pos));
                    pos = nextPos;
                }
            }

            // Check the conditions for reading from the file
            string carType = columns[1];
            string availabilityStr = columns[5];
            if (carType == "Economic" && (isBooked == false || availabilityStr == "1")) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No matching car found in the input file." << endl;
            return pricing;
        }

        float rentPrice = stof(columns[4]);
        pricing = rentPrice;


        limit_days = 7; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                pricing *= 7; //adds pricing for 2 days
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing = rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        inputFile.close();
        return pricing;
    }

    float calculateMileage() override {
        float milesPassed = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return milesPassed;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            if (line.find(model) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Car model not found in the input file." << endl;
            return milesPassed;
        }

        float rentPrice = 0.0;
        inputFile.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore the preceding columns
        inputFile >> milesPassed;

        if (isBooked) {
            milesPassed += 700;
        }
        return milesPassed;
    }


};

class SportsCar :public Car {
private:
    string model;// parse brand and model 
    int days_booked;
    bool isBooked;
    ifstream inputFile;

public:
    // Default constructor
    SportsCar() : Car(),
        model(""),
        days_booked(0),
        isBooked(false),
        inputFile("CarInfo.txt") {}

    // Parameterized constructor
    SportsCar(int id, const string& brand, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, const string& model, int days_booked, bool isBooked)
        : Car(id, brand, type, makeDate, rentDate, returnDate, mileage, pricing),
        model(model),
        days_booked(days_booked),
        isBooked(isBooked),
        inputFile("CarInfo.txt") {}

    float calculatePricing() override {
        float pricing = 0.0;

        float pricing = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return pricing;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            // Skip the header line
            if (line.find("Name") != string::npos) {
                continue;
            }

            // Split the line into columns
            vector<string> columns;
            size_t pos = 0;
            while (pos != string::npos) {
                size_t nextPos = line.find('\t', pos);
                if (nextPos != string::npos) {
                    columns.push_back(line.substr(pos, nextPos - pos));
                    pos = nextPos + 1;
                }
                else {
                    columns.push_back(line.substr(pos));
                    pos = nextPos;
                }
            }

            // Check the conditions for reading from the file
            string carType = columns[1];
            string availabilityStr = columns[5];
            if (carType == "Sports" && (isBooked == false || availabilityStr == "1")) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No matching car found in the input file." << endl;
            return pricing;
        }

        float rentPrice = stof(columns[4]); 
        pricing = rentPrice;

       

        limit_days = 1; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                for (int i = 0; i <= limit_days; i++) // still wrong needs some more adjustments, maybe a while loop or something 
                {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing += rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        inputFile.close();
        return pricing;
    }

    float calculateMileage() override {
        float milesPassed = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return milesPassed;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            if (line.find(model) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Car model not found in the input file." << endl;
            return milesPassed;
        }

        float rentPrice = 0.0;
        inputFile.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore the preceding columns
        inputFile >> milesPassed;

        if (isBooked) {
            milesPassed += 100;
        }
        return milesPassed;
    }

};

class Van :public Car {
private:
    string model;// parse brand and model 
    int days_booked;
    bool isBooked;
    ifstream inputFile;

public:
    // Default constructor
    Van() : Car(),
        model(""),
        days_booked(0),
        isBooked(false),
        inputFile("CarInfo.txt") {}

    // Parameterized constructor
    Van(int id, const string& brand, const string& type, const Date& makeDate, const Date& rentDate,
        const Date& returnDate, float mileage, float pricing, const string& model, int days_booked, bool isBooked)
        : Car(id, brand, type, makeDate, rentDate, returnDate, mileage, pricing),
        model(model),
        days_booked(days_booked),
        isBooked(isBooked),
        inputFile("CarInfo.txt") {}

    float calculatePricing() override {
        float pricing = 0.0;

        float pricing = 0.0;

        float pricing = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return pricing;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            // Skip the header line
            if (line.find("Name") != string::npos) {
                continue;
            }

            // Split the line into columns
            vector<string> columns;
            size_t pos = 0;
            while (pos != string::npos) {
                size_t nextPos = line.find('\t', pos);
                if (nextPos != string::npos) {
                    columns.push_back(line.substr(pos, nextPos - pos));
                    pos = nextPos + 1;
                }
                else {
                    columns.push_back(line.substr(pos));
                    pos = nextPos;
                }
            }

            // Check the conditions for reading from the file
            string carType = columns[1];
            string availabilityStr = columns[5];
            if (carType == "Van" && (isBooked == false || availabilityStr == "1")) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No matching car found in the input file." << endl;
            return pricing;
        }

        float rentPrice = stof(columns[4]);
        pricing = rentPrice;

        limit_days = 10; // sets the limits of days
        double pricing = rentPrice; // initially setting pricing 
        if (days_booked > limit_days) {

            while (days_booked > 0) {
                pricing *= 10; //adds pricing for 2 days
                for (int i = 0; i <= limit_days; i++) {
                    rentPrice += rentPrice * 0.05; // calculates new rentPrice
                    pricing = rentPrice; //sets the new pricing of the car
                }
                days_booked -= limit_days; //keeps decrementing till 0;
            }
        }

        inputFile.close();
        return pricing;
    }

    float calculateMileage() override {
        float milesPassed = 0.0;

        if (!inputFile.is_open()) {
            cout << "Failed to open the input file." << endl;
            return milesPassed;
        }

        string line;
        bool found = false;
        while (getline(inputFile, line)) {
            if (line.find(model) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Car model not found in the input file." << endl;
            return milesPassed;
        }

        float rentPrice = 0.0;
        inputFile.ignore(numeric_limits<streamsize>::max(), '\t'); // Ignore the preceding columns
        inputFile >> milesPassed;

        if (isBooked) {
            milesPassed += 1500;
        }
        return milesPassed;
    }

};
