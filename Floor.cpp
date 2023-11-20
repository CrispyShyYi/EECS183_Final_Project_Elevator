/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Floor.h"
#include <algorithm>

using namespace std;

int Floor::tick(int currentTime) {
    int count = 0;
    int idx[MAX_PEOPLE_PER_FLOOR];
    int j = 0;
    for (int i = 0; i < numPeople; i++) {
        if (people[i].tick(currentTime)) {
            idx[j] = i;
            count++;
            j++;
        }
    }
    removePeople(idx, count);
    return count;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
    }
    if (request > 0) {
        hasUpRequest = true;
    } else if (request < 0) {
        hasDownRequest = true;
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {

    //copy elements for sorting
    int arr[MAX_PEOPLE_PER_FLOOR];
    for(int i = 0; i < numPeopleToRemove; i++){
        arr[i] = indicesToRemove[i];
    }
    
    // Sort indicesToRemove
    for (int i = 0; i < numPeopleToRemove - 1; i++) {
        for (int j = 0; j < numPeopleToRemove - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    //remove people
    for (int i = numPeopleToRemove - 1; i >= 0; i--) {
        int num = arr[i];
        for (int j = num; j < numPeople - 1; j++) {
            people[j] = people[j + 1];
        }
        numPeople--;
     }
     resetRequests();
 }

void Floor::resetRequests() {
    int currentfloor, targetfloor;
    hasUpRequest = false;
    hasDownRequest = false;
    for (int i = 0; i < numPeople; i++) {
        currentfloor = people[i].getCurrentFloor();
        targetfloor = people[i].getTargetFloor();
        if(currentfloor < targetfloor){
            hasUpRequest = true;
        }
        else if(currentfloor > targetfloor){
            hasDownRequest = true;
        }
  }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
  hasDownRequest = false;
  hasUpRequest = false;
  numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream &outs) const {
  string up = "U";
  outs << (hasUpRequest ? up : " ") << " ";
  for (int i = 0; i < numPeople; ++i) {
    outs << people[i].getAngerLevel();
    outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
  }
  outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream &outs) const {
  string down = "D";
  outs << (hasDownRequest ? down : " ") << " ";
  for (int i = 0; i < numPeople; ++i) {
    outs << "o   ";
  }
  outs << endl;
}

void Floor::printFloorPickupMenu(ostream &outs) const {
  cout << endl;
  outs << "Select People to Load by Index" << endl;
  outs << "All people must be going in same direction!";
  /*  O   O
  // -|- -|-
  //  |   |
  // / \ / \  */
  outs << endl << "              ";
  for (int i = 0; i < numPeople; ++i) {
    outs << " O   ";
  }
  outs << endl << "              ";
  for (int i = 0; i < numPeople; ++i) {
    outs << "-|-  ";
  }
  outs << endl << "              ";
  for (int i = 0; i < numPeople; ++i) {
    outs << " |   ";
  }
  outs << endl << "              ";
  for (int i = 0; i < numPeople; ++i) {
    outs << "/ \\  ";
  }
  outs << endl << "INDEX:        ";
  for (int i = 0; i < numPeople; ++i) {
    outs << " " << i << "   ";
  }
  outs << endl << "ANGER:        ";
  for (int i = 0; i < numPeople; ++i) {
    outs << " " << people[i].getAngerLevel() << "   ";
  }
  outs << endl << "TARGET FLOOR: ";
  for (int i = 0; i < numPeople; ++i) {
    outs << " " << people[i].getTargetFloor() << "   ";
  }
}

void Floor::setHasUpRequest(bool hasRequest) { hasUpRequest = hasRequest; }

bool Floor::getHasUpRequest() const { return hasUpRequest; }

void Floor::setHasDownRequest(bool hasRequest) { hasDownRequest = hasRequest; }

bool Floor::getHasDownRequest() const { return hasDownRequest; }

int Floor::getNumPeople() const { return numPeople; }

Person Floor::getPersonByIndex(int index) const { return people[index]; }
