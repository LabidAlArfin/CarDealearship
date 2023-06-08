#include"Cartype.h"
#include"Car.h"

using namespace std;

int main() {
    vector<LuxuryCar> cars = LuxuryCar::readFile();

    // Display the cars to the user
    for (int i = 0; i < cars.size(); i++) {
        cout << "Car ID: " << cars[i].getID() << endl;
        cout << "Brand: " << cars[i].getBrand() << endl;
        cout << "Type: " << cars[i].getType() << endl;
        cout << "Make Date: " << cars[i].getMakeDate().day << "/" << cars[i].getMakeDate().month << "/" << cars[i].getMakeDate().year << endl;
        cout << "Rent Date: " << cars[i].getRentDate().day << "/" << cars[i].getRentDate().month << "/" << cars[i].getRentDate().year << endl;
        cout << "Return Date: " << cars[i].getReturnDate().day << "/" << cars[i].getReturnDate().month << "/" << cars[i].getReturnDate().year << endl;
        cout << "Mileage: " << cars[i].calculateMileage() << endl;
        cout << "Pricing: " << cars[i].calculatePricing() << endl;
        cout << "Available: " << (cars[i].isAvailable ? "Yes" : "No") << endl;
        cout << endl;
    }

    // Prompt the user to choose a car
    cout << "Enter the ID or Brand of the car you want to choose: ";
    string input;
    getline(cin, input);

    int index = -1;

    // Check if the user input is a number (car ID)
    if (isdigit(input[0])) {
        int carID = stoi(input);
        index = FindCarByID(carID);
    }
    else {
        index = FindCarUsingName(input);
    }

    if (index != -1) {
        // Car found, perform actions
        LuxuryCar& chosenCar = cars[index];
        // Perform actions with the chosen car
        // ...
    }
    else {
        // Car not found
        cout << "Car not found." << endl;
    }

    return 0;
}

