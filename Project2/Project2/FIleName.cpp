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
        cout << "Make Date: " << cars[i].getMake().day << "/" << cars[i].getMake().month << "/" << cars[i].getMake().year << endl;
        cout << "Rent Date: " << cars[i].getRentD().day << "/" << cars[i].getRentD().month << "/" << cars[i].getRentD().year << endl;
        cout << "Return Date: " << cars[i].getReturnD().day << "/" << cars[i].getReturnD().month << "/" << cars[i].getReturnD().year << endl;
        cout << "Mileage: " << cars[i].calculateMileage(i) << endl;
        cout << "Pricing: " << cars[i].calculatePricing(i) << endl;
        cout << "Available: " << (cars[i].getAvailability() ? "Yes" : "No") << endl;
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
        index = cars[0].FindCarByID(carID);
    }
    else {
        index = cars[0].FindCarUsingName(input);
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
