/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string inputString) : Person() {
    //TODO: Implement non-default constructor
    int i = 0;
    int j = 0;
    if (inputString[1] != 'f'){
        i = inputString[0] - '0';
        j = inputString[1] - '0';
        turn = 10 * i + j;
        currentFloor = inputString[3] - '0';
        targetFloor = inputString[5] - '0';
        angerLevel = inputString[7] - '0';
    }else {
        turn = inputString[0] - '0';
        currentFloor = inputString[2] - '0';
        targetFloor = inputString[4] - '0';
        angerLevel = inputString[6] - '0';
    }
}

bool Person::tick(int currentTime) {
    //TODO: Implement tick
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0){
        angerLevel++;
    } if (angerLevel >= MAX_ANGER){
        return true;
    } else{
        return false;
    }
    //Returning false to prevent compilation error
}

void Person::print(ostream &outs) {
    //TODO: Implement print
    outs  << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel << endl;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {
    return currentFloor;
}

int Person::getTargetFloor() const {
    return targetFloor;
}

int Person::getAngerLevel() const {
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
