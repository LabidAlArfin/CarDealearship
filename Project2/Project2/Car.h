#include<iostream>
#include<string>
using namespace std;

struct Date {
	int day, month, year;
	Date(int d, int m, int y) : day(d), month(m), year(y) {};
};

class Car {
private:
	int id;
	string brand, type;
	Date makeDate, rentDate, returnDate;
	float milage, pricing;
public:
	//getters and setters;
	//setting is for admins only
	void setID(int id) { this->id = id; }
	void setBrand(string brand) { this->brand = brand; }
	void setType(string type) { this->type = type; }
	void setDate(Date make) { this->makeDate = make; }
	void setRentDate(Date rentDate) { this->rentDate = rentDate; }
	void setReturnDate(Date returnDate) { this->returnDate = returnDate; }

	//getting for the users only
	int getID() { return id; }
	string getBrand() { return brand; }
	string getType() { return type; }
	Date getMake() { return makeDate; }
	Date getRentD() { return rentDate; }
	Date getReturnD() { return returnDate; }

	virtual float calculatePricing() {
		// Calculate pricing logic based on make date, rent date, and return date
		// Replace the example logic with your own calculation formula
		float pricing = 0.0;
		int rentalPeriod = calculateDaysPassed(rentDate, returnDate);
		pricing = rentalPeriod * 50.0; // Example calculation: $50 per day
		return pricing;
	}

	// Virtual function to calculate the miles the car has passed
	virtual float calculateMileage() {
		// Calculate mileage logic based on the difference between the make date and return date
		// Replace the example logic with your own calculation formula
		float milesPassed = 0.0;
		int daysPassed = calculateDaysPassed(makeDate, returnDate);
		milesPassed = daysPassed * 50.0; // Example calculation: 50 miles per day
		return milesPassed;
	}

	//calculate days passed
	int calculateDaysPassed(Date startDate, Date endDate) {
		// Calculate the exact number of days between the start and end dates
		int daysPassed = 0;

		// Convert the dates to days since a reference date
		int startDays = startDate.day + getDaysInMonth(startDate.month, startDate.year) * startDate.month + 365 * startDate.year;
		int endDays = endDate.day + getDaysInMonth(endDate.month, endDate.year) * endDate.month + 365 * endDate.year;

		// Calculate the difference in days
		daysPassed = endDays - startDays;

		return daysPassed;
	}

	//calculate the number of days in each month... fast method.
	int getDaysInMonth(int month, int year) const {
		static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		// Adjust for leap years
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
			return 29;

		return daysInMonth[month - 1];
	}
};









