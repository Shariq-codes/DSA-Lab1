#include <iostream>
using namespace std;

// Definition of Linked List Node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // Destructor to free remaining nodes on program termination
    ~SinglyLinkedList() {
        destroyList();
    }

    // 1. Insert a new node at the head
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        cout << "[Success] Inserted " << value << " at head.\n";
    }

    // 2. Insert a node specifically at the 3rd location (index 3, 1-based)
    void insertAtThird(int value) {
        Node* newNode = new Node(value);

        // Case A: List is completely empty
        if (head == nullptr) {
            cout << "[Notice] List is empty. Inserting " << value << " as head node (1st position).\n";
            head = newNode;
            return;
        }

        // Case B: List has only 1 node
        if (head->next == nullptr) {
            cout << "[Notice] List has only 1 node. Appending " << value << " as 2nd node.\n";
            head->next = newNode;
            return;
        }

        // Case C: List has at least 2 nodes; place new node at 3rd position
        Node* current = head->next; // Currently at 2nd node
        newNode->next = current->next;
        current->next = newNode;

        cout << "[Success] Inserted " << value << " at position 3.\n";
    }

    // 3. Display the contents of the linked list
    void displayList() const {
        if (head == nullptr) {
            cout << "[Notice] List is empty.\n";
            return;
        }
        Node* temp = head;
        cout << "Head -> ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // 4. Delete the last node
    void deleteLast() {
        if (head == nullptr) {
            cout << "[Error] List is empty! Nothing to delete.\n";
            return;
        }

        if (head->next == nullptr) {
            cout << "[Deleted] Removed final node with value: " << head->data << endl;
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        cout << "[Deleted] Removed final node with value: " << current->next->data << endl;
        delete current->next;
        current->next = nullptr;
    }

    // 5. Count total number of nodes in the list
    int countNodes() const {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 6. Reverse the linked list iteratively
    void reverseList() {
        if (head == nullptr || head->next == nullptr) {
            cout << "[Notice] List has fewer than 2 nodes. Reversal not required.\n";
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next; // Save next node
            current->next = prev;     // Reverse pointer direction
            prev = current;           // Advance prev
            current = nextNode;       // Advance current
        }

        head = prev; // Update head pointer
        cout << "[Success] Linked list reversed successfully.\n";
    }

    // 7. Search for a given value and return its position
    void searchValue(int value) const {
        if (head == nullptr) {
            cout << "[Error] List is empty! Cannot perform search.\n";
            return;
        }

        Node* temp = head;
        int position = 1;
        bool found = false;

        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "[Found] Value " << value << " exists at position (index) " << position << endl;
                found = true;
                break;
            }
            temp = temp->next;
            position++;
        }

        if (!found) {
            cout << "[Not Found] Value " << value << " does not exist in the list.\n";
        }
    }

    // Helper: Deallocate entire list memory
    void destroyList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
};

void showMenu() {
    cout << "\n====================================\n";
    cout << "   PART 3: SINGLY LINKED LIST MENU  \n";
    cout << "====================================\n";
    cout << "1. Insert at Head\n";
    cout << "2. Insert at 3rd Location\n";
    cout << "3. Display List\n";
    cout << "4. Delete Last Node\n";
    cout << "5. Count Total Nodes\n";
    cout << "6. Reverse List Iteratively\n";
    cout << "7. Search for a Value\n";
    cout << "8. Exit\n";
    cout << "------------------------------------\n";
    cout << "Enter your choice (1-8): ";
}

int main() {
    SinglyLinkedList list;
    int choice, val;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> val;
                list.insertAtHead(val);
                list.displayList();
                break;
            case 2:
                cout << "Enter value to insert at 3rd position: ";
                cin >> val;
                list.insertAtThird(val);
                list.displayList();
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                list.deleteLast();
                list.displayList();
                break;
            case 5:
                cout << "Total nodes present in list: " << list.countNodes() << endl;
                break;
            case 6:
                list.reverseList();
                list.displayList();
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> val;
                list.searchValue(val);
                break;
            case 8:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}