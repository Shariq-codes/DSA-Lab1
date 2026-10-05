#include <iostream>
using namespace std;

// Node structure for Singly Circular Linked List
struct Person {
    int id;
    Person* next;

    Person(int personId) {
        id = personId;
        next = NULL;
    }
};

class JosephusCircle {
private:
    Person* head;

public:
    JosephusCircle() {
        head = NULL;
    }
// 1. Create Circle of N people
    void createCircle(int N) {
        if (N <= 0) {
            cout << "Number of people must be greater than 0.\n";
            return;
        }

        head = new Person(1);
        Person* current = head;

        for (int i = 2; i <= N; i++) {
            current->next = new Person(i);
            current = current->next;
        }

        // Complete the circle by connecting the last node to the head
        current->next = head;
    }

//2. Elimination Process
    void eliminate(int N, int k) {
        if (head == NULL) {
            cout << "The circle is empty!\n";
            return;
        }
        if (k <= 0) {
            cout << "Step count k must be greater than 0.\n";
            return;
        }

    cout << "\nElimination Order: ";

        Person* current = head;
        Person* prev = NULL;

        // Find the tail node (prev of head) to properly handle removals
        while (current->next != head) {
            current = current->next;
        }
        prev = current;
        current = head;

        // Continue until only 1 person remains in the circle
        while (current->next != current) {
            // Move (k - 1) steps forward to find the k-th person
            for (int count = 1; count < k; count++) {
                prev = current;
                current = current->next;
            }

            // Display eliminated person ID
            cout << current->id << " ";

            // Update links to eliminate the node
            prev->next = current->next;
            
            // If head is deleted, update head pointer
            if (current == head) {
                head = current->next;
            }

            delete current;

            // Move to the next starting person
            current = prev->next;
        }
    //Print survivor details
        cout << "\n-----------------------------------";
        cout << "\nSurvivor (Last Person Standing): Person " << current->id << endl;
        cout << "-----------------------------------\n";

    //Clean up last remaining node
        delete current;
        head = NULL;
    }
};
int main() {
    int N, k;
    cout << "========== JOSEPHUS PROBLEM SIMULATION ==========\n";
    cout << "Enter total number of people (N): ";
    cin >> N;
    cout << "Enter step count for elimination (k): ";
    cin >> k;

    if (N <= 0 || k <= 0) {
        cout << "Invalid input. Both N and k must be positive integers.\n";
        return 0;
    }
    JosephusCircle game;
  
//Create the circular linked list
    game.createCircle(N);

//Run the elimination process and show survivor
    game.eliminate(N, k);

    return 0;
}