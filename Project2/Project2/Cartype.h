#include<iostream>
#include"Car.h"
using namespace std;

class LuxuryCar :public Car{
private:

public:
    float calculatePricing() override {
        // Calculate pricing logic specific to Sedan cars
        float pricing = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return pricing;
    }

    float calculateMileage() override {
        // Calculate mileage logic specific to Sedan cars
        float milesPassed = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return milesPassed;
    }

};

class EconomicCar :public Car {
private:

public:
    float calculatePricing() override {
        // Calculate pricing logic specific to Sedan cars
        float pricing = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return pricing;
    }

    float calculateMileage() override {
        // Calculate mileage logic specific to Sedan cars
        float milesPassed = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return milesPassed;
    }


};

class SportsCar :public Car {
private:

public:
    float calculatePricing() override {
        // Calculate pricing logic specific to Sedan cars
        float pricing = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return pricing;
    }

    float calculateMileage() override {
        // Calculate mileage logic specific to Sedan cars
        float milesPassed = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return milesPassed;
    }

};

class Van :public Car {
private:

public:
    float calculatePricing() override {
        // Calculate pricing logic specific to Sedan cars
        float pricing = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return pricing;
    }

    float calculateMileage() override {
        // Calculate mileage logic specific to Sedan cars
        float milesPassed = 0.0;
        // Custom calculation formula for Sedan cars
        // ...
        return milesPassed;
    }

};