/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    //TODO: Implement non-default constructor

  elevatorId = -1;
  targetFloor = -1;
  numPeopleToPickup = 0;
  totalSatisfaction = 0;
  isPass = false;
  isPickup = false;
  isSave = false;
  isQuit = false;

  
  if (commandString == "") {
    isPass = true;
  }

  if (!commandString.empty()) {
    if (commandString == "s" || commandString == "S") {
      isSave = true;
    } else if (commandString == "q" || commandString == "Q") {
      isQuit = true;
    }
  
    if (commandString.at(0) == 'e') {
      elevatorId = static_cast<int>(commandString.at(1)) - 48;
      if (commandString.at(2) == 'f') {
        targetFloor = static_cast<int>(commandString.at(3)) - 48;
      } else if (commandString.at(2) == 'p') {
        isPickup = true;
      }
    }
  
  }
    
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {

    if (isPassMove() || isQuitMove() || isSaveMove()) {
        return true;
    }


    if (isPickupMove() || (!isPassMove() && !isQuitMove() && !isSaveMove())) {

        if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS) {
            return false;
        }

        if (elevators[elevatorId].isServicing()) {
            return false;
        }

        if (!isPickupMove()) {

            if (targetFloor < 0 || targetFloor >= NUM_FLOORS) {
                return false;
            }

            if (targetFloor == elevators[elevatorId].getCurrentFloor()) {
                return false;
            }
        }
        return true;
    }

    return false;
}


    

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    //TODO: Implement setPeopleToPickup

    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int tempAngerLevel = 0;
    int floorDiff = 0;

    for (int i = 0; i < pickupList.length(); i++) {
      peopleToPickup[i] = static_cast<int>(pickupList.at(i)) - 48;
      numPeopleToPickup++;
      
      tempAngerLevel = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
      totalSatisfaction += (MAX_ANGER - tempAngerLevel);

      if (abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor) > floorDiff) {
        floorDiff = abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor);
        targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
      }

    }
  
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
