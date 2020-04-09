//
// Created by Colton on 2/26/2019.
//
//Specific linked list application for maintaining a ledger of transactions.
//

#include "Ledger.h"
#include <iostream>
#include <algorithm>

//Constructor, creates a new empty linked list with a NULL head.
Ledger::Ledger() {
    head = NULL;
    identifier = 1000;
}

//Destructor: clear all nodes and deletes head to clean up allocated memory
Ledger::~Ledger() {
    Clear();
    delete head;
}

//Adds Amount money to the system in the name of ToName user from external source.
void Ledger::AddExternalMoney(string to, int amount) {
    AddPayment("external", to, amount);
}

//Enters a transfer from FromName to ToName in the amount of Amount. FromName now has Amount
//less money and ToName now has Amount more money. Returns a int transaction Id.
int Ledger::AddPayment(string from, string to, int amount) {

    //Create new node and assign data.
    Node *newNode = new Node;

    newNode->amount = amount;
    newNode->to = to;
    newNode->from = from;
    newNode->id = identifier;
    newNode->next = NULL;

    identifier++;

    //Place node at end of list.
    if (head == NULL) {
        head = newNode;
    } else {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    //Check if either name is in vector yet, if not add it to the list.
    if (find(begin(accounts), end(accounts), from) == end(accounts)) {
        accounts.push_back(from);
    }

    if (find(begin(accounts), end(accounts), to) == end(accounts)) {
        accounts.push_back(to);
    }

    return newNode->id;

}

//Removes transaction from linked list using id. Returns -1 if node is not found
int Ledger::RefundPayment(int id) {
    Node *current = head;
    Node *previous = new Node;


    while (current != NULL) {

        if (current->id == id) {
            previous->next = current->next;
            delete current;
            return 1;
        }

        previous = current;
        current = current->next;
    }
    return -1;
}

//Remove transaction from linked list using transaction info. Returns -1 if node is not found
int Ledger::RefundPayment(string from, string to, int amount) {
    Node *current = head;
    Node *previous = new Node;

    while (current != NULL) {

        if (current->from == from && current->to == to && current->amount == amount) {
            previous->next = current->next;
            delete current;
            return 1;
        }

        previous = current;
        current = current->next;
    }
    return -1;
}

//Removes all of the transactions and deletes nodes
void Ledger::Clear() {
    Node *iterator = head;

    while (iterator != NULL) {
        head = iterator->next;
        delete iterator;
        iterator = head;
    }
}

//Prints the ledger
void Ledger::Print() {
    cout << endl << "All transaction" << endl;
    Node *temp = head;
	
	if (temp == NULL)
		cout << endl << "List is empty" << endl;
	
    while (temp != NULL) {
        cout << "ID: " << temp->id << ", From: " << temp->from << ", To: " << temp->to << ", Amount: " << temp->amount
             << endl;
        temp = temp->next;
    }
}

//Print the ledger for desired user
void Ledger::Print(string name) {
    cout << name << "'s transaction" << endl;
    Node *temp = head;
    while (temp != NULL) {
        if (temp->to == name || temp->from == name) {
            cout << "ID: " << temp->id << " From: " << temp->from << " To: " << temp->to << " Amount: " << temp->amount
                 << endl;
        }
        temp = temp->next;
    }
}

//Prints the name and balance of each user
void Ledger::Settle() {
    cout << "Settling balances" << endl;
	
    for (string person : accounts) 
        cout << person << "'s balance: " << Balance(person) << endl;
    
}

//Prints the name and balance of each user who has positive money
void Ledger::InTheBlack() {
	cout << "Postive balances" << endl;
    for (string person : accounts) {
        int balance = Balance(person);
		
        if (balance >= 0) 
            cout << person << "'s balance: " << balance << endl;
        
    }
}

//Prints the name and balance of each user who has negative money
void Ledger::InTheRed() {
	cout << "Negative balances" << endl;
    for (string person : accounts) {
        int balance = Balance(person);
		
        if (balance < 0) 
            cout << person << "'s balance: " << balance << endl;
        
    }
}

//Determines a specified users account balance by iterating through linked list
int Ledger::Balance(string name) {
    int balance = 0;
    Node *temp = head;
    while (temp != NULL) {
        if (temp->from == name) {
            balance -= temp->amount;
        }
        if (temp->to == name) {
            balance += temp->amount;
        }
        temp = temp->next;
    }
    return balance;
}