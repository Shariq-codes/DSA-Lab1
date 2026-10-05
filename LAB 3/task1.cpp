#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to check if a character is alphanumeric
bool isAlphaNumericChar(char c) {
    return isalnum(static_cast<unsigned char>(c));
}

// Iterative function to check if a string is a palindrome
bool isPalindrome(const string& str) {
    if (str.empty()) return true;

    int left = 0;
    int right = static_cast<int>(str.length()) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters from left
        while (left < right && !isAlphaNumericChar(str[left])) {
            left++;
        }
        // Skip non-alphanumeric characters from right
        while (left < right && !isAlphaNumericChar(str[right])) {
            right--;
        }
        // Compare characters case-insensitively
        if (tolower(static_cast<unsigned char>(str[left])) !=
            tolower(static_cast<unsigned char>(str[right]))) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    string userInput;
    cout << "<<<==========================================>>>" << endl;
    cout << "         PART 1: PALINDROME CHECKER         " << endl;
    cout << "<<<==========================================>>>" << endl;
    cout << "Enter a string to test: ";
    getline(cin, userInput);

    if (isPalindrome(userInput)) {
        cout << "\nResult: \"" << userInput << "\" is a palindrome!\n";
    } else {
        cout << "\nResult: \"" << userInput << "\" is NOT a palindrome.\n";
    }
    return 0;
}