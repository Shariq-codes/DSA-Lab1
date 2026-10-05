#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Node structure for Doubly Linked List bit
struct Node {
    int bit;
    Node* next;
    Node* prev;

    Node(int b) {
        bit = b;
        next = NULL;
        prev = NULL;
    }
};
class BinaryNumber {
public:
    Node* head;
    Node* tail;

    BinaryNumber() {
        head = NULL;
        tail = NULL;
    }

    // Helper to insert bit at the end
    void appendBit(int b) {
        Node* newNode = new Node(b);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Helper to insert bit at the front
    void prependBit(int b) {
        Node* newNode = new Node(b);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // 1. Store Binary Number (padded to multiples of 8 bits)
    void storeBinary(string strBits) {
        // Clear previous data if any
        clear();

        // Convert string bits to DLL
        for (char ch : strBits) {
            if (ch == '0' || ch == '1') {
                appendBit(ch - '0');
            }
        }

        if (head == NULL) {
            appendBit(0);
        }

        // Calculate current bit length
        int length = 0;
        Node* temp = head;
        while (temp != NULL) {
            length++;
            temp = temp->next;
        }

        // Pad with leading zeros to complete 8-bit blocks
        int remainder = length % 8;
        if (remainder != 0) {
            int padCount = 8 - remainder;
            for (int i = 0; i < padCount; i++) {
                prependBit(0);
            }
        }
    }

    // Display binary number grouped in 8-bit blocks
    void display() {
        if (head == NULL) {
            cout << "00000000\n";
            return;
        }

        Node* temp = head;
        int count = 0;
        while (temp != NULL) {
            cout << temp->bit;
            count++;
            if (count % 8 == 0 && temp->next != NULL) {
                cout << " "; // Space separating 8-bit blocks
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // 2. 1's Complement
    BinaryNumber onesComplement() {
        BinaryNumber result;
        Node* temp = head;
        while (temp != NULL) {
            result.appendBit(temp->bit == 0 ? 1 : 0);
            temp = temp->next;
        }
        return result;
    }

    // 3. 2's Complement (1's complement + 1)
    BinaryNumber twosComplement() {
        BinaryNumber result = onesComplement();
        BinaryNumber one;
        one.storeBinary("1");

        return add(result, one);
    }

    // 4. Binary Addition (DLL Traversal from LSB to MSB)
    static BinaryNumber add(BinaryNumber& num1, BinaryNumber& num2) {
        BinaryNumber result;
        Node* p1 = num1.tail;
        Node* p2 = num2.tail;
        int carry = 0;

        while (p1 != NULL || p2 != NULL || carry != 0) {
            int b1 = (p1 != NULL) ? p1->bit : 0;
            int b2 = (p2 != NULL) ? p2->bit : 0;

            int sum = b1 + b2 + carry;
            result.prependBit(sum % 2);
            carry = sum / 2;

            if (p1 != NULL) p1 = p1->prev;
            if (p2 != NULL) p2 = p2->prev;
        }

        // Pad result to 8-bit alignment
        int length = 0;
        Node* temp = result.head;
        while (temp != NULL) {
            length++;
            temp = temp->next;
        }
        int remainder = length % 8;
        if (remainder != 0) {
            int padCount = 8 - remainder;
            for (int i = 0; i < padCount; i++) {
                result.prependBit(0);
            }
        }

        return result;
    }

    // 5. Binary Multiplication (Repeated Addition + Left Shift)
    static BinaryNumber multiply(BinaryNumber& num1, BinaryNumber& num2) {
        BinaryNumber product;
        product.storeBinary("0");

        Node* p2 = num2.tail;
        int shift = 0;

        while (p2 != NULL) {
            if (p2->bit == 1) {
                BinaryNumber currentShifted = num1;

                // Shift left by appending 'shift' zeros at LSB
                for (int i = 0; i < shift; i++) {
                    currentShifted.appendBit(0);
                }

                product = add(product, currentShifted);
            }
            shift++;
            p2 = p2->prev;
        }

        return product;
    }
// 6. Conversion to Decimal
    long long toDecimal() {
        long long decimal = 0;
        Node* temp = head;

        while (temp != NULL) {
            decimal = (decimal * 2) + temp->bit;
            temp = temp->next;
        }
        return decimal;
    }
// Cleanup allocated memory
    void clear() {
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = NULL;
    }
};

int main() {
    BinaryNumber bin1, bin2;
    string input1, input2;

    cout << "========== BINARY ARITHMETIC USING DLL ==========\n";
    cout << "Enter first binary number: ";
    cin >> input1;
    bin1.storeBinary(input1);

    cout << "First Number (8-bit aligned):  ";
    bin1.display();

    cout << "\n--- Basic Complement Operations (Number 1) ---\n";
    BinaryNumber ones = bin1.onesComplement();
    cout << "1's Complement: ";
    ones.display();

    BinaryNumber twos = bin1.twosComplement();
    cout << "2's Complement: ";
    twos.display();

    cout << "\nDecimal Equivalent: " << bin1.toDecimal() << endl;

    cout << "\n---------------------------------------------\n";
    cout << "Enter second binary number for arithmetic: ";
    cin >> input2;
    bin2.storeBinary(input2);

    cout << "Second Number (8-bit aligned): ";
    bin2.display();

    cout << "\n--- Binary Arithmetic Operations ---\n";
    BinaryNumber addition = BinaryNumber::add(bin1, bin2);
    cout << "Binary Addition (Num1 + Num2): ";
    addition.display();
    cout << "Sum in Decimal: " << addition.toDecimal() << endl;

    BinaryNumber multiplication = BinaryNumber::multiply(bin1, bin2);
    cout << "\nBinary Multiplication (Num1 * Num2): ";
    multiplication.display();
    cout << "Product in Decimal: " << multiplication.toDecimal() << endl;

    return 0;
}