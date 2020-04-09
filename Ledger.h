//
// Created by Colton on 2/26/2019.
//

#ifndef ASS4_LEDGER_H
#define ASS4_LEDGER_H

#include <string>
#include <vector>
using namespace std;

struct Node{
    string from;
    string to;
    int amount;
    int id;
    Node *next;
};

class Ledger {
public:
    Ledger();
    ~Ledger();
    void AddExternalMoney(string, int);
    int AddPayment(string, string, int);
    int RefundPayment(int);
    int RefundPayment(string, string, int);
    void Clear();
    void Print();
    void Print(string);
    void Settle();
    void InTheBlack();
    void InTheRed();
private:
    vector<string> accounts;
    int identifier;
    Node *head;
    int Balance(string);
};


#endif //ASS4_LEDGER_H
