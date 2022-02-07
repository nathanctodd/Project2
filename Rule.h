#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Token.h"
#include "Predicate.h"

using namespace std;



class Rule {

    private:
        Predicate headPredicate;
        vector<Predicate> predicateList;

    public:

    Rule() {
  
    }

    Rule(Predicate head, vector<Predicate> predicateLi) {
        headPredicate = head;
        predicateList = predicateLi;
    }

    void addToRules(Predicate addedPredicate) {
        predicateList.push_back(addedPredicate);
    }

    vector<Predicate> getPredicateList() {
        return predicateList;
    }

    Predicate getHeadPredicate() {
        return headPredicate;
    }

    void setHeadPredicate(Predicate head) {
        headPredicate = head;
    }

    void setPredicateList(vector<Predicate> pred) {
        predicateList = pred;
    }

    string toString() {
        stringstream output;
        output << headPredicate.toString();
        output << " :- ";
        output << predicateList[0].toString();
        for (unsigned int i = 1; i < predicateList.size(); i++) {
            output << "," << predicateList[i].toString();
        }
        return output.str();
    }



};