#include <iostream>
#include <string>

using namespace std;

// Node structure for Doubly Linked List
struct Song {
    int id;
    string name;
    string duration; 
    Song* next;
    Song* prev;

    Song(int sId, string sName, string sDur) {
        id = sId;
        name = sName;
        duration = sDur;
        next = NULL;
        prev = NULL;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* currentSong; //Pointer to simulate active playback

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        currentSong = NULL;
    }

 //1.Add Song at the end
    void addSong(int id, string name, string duration) {
        Song* newSong = new Song(id, name, duration);
        if (head == NULL) {
            head = tail = currentSong = newSong;
            cout << "Song added successfully as the first song!\n";
            return;
        }
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
        cout << "Song added to the end of the playlist!\n";
    }

    // 2. Delete Song by ID
    void deleteSong(int id) {
        if (head == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* temp = head;

        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Song with ID " << id << " not found.\n";
            return;
        }

        // If active playback song is being deleted, update currentSong
        if (currentSong == temp) {
            if (temp->next != NULL) {
                currentSong = temp->next;
            } else {
                currentSong = temp->prev;
            }
        }

        // Deleting head node
        if (temp == head) {
            head = head->next;
            if (head != NULL) {
                head->prev = NULL;
            } else {
                tail = NULL;
            }
        }
        // Deleting tail node
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        }
        // Deleting middle node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Song deleted successfully!\n";
    }

    // 3. Display Playlist Forward
    void displayForward() {
        if (head == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "\n--- Playlist (First to Last) ---\n";
        Song* temp = head;
        while (temp != NULL) {
            cout << "ID: " << temp->id 
                 << " | Name: " << temp->name 
                 << " | Duration: " << temp->duration;
            if (temp == currentSong) {
                cout << "  <-- Currently Playing";
            }
            cout << endl;
            temp = temp->next;
        }
    }

    // 4. Display Playlist Backward
    void displayBackward() {
        if (tail == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "\n--- Playlist (Last to First) ---\n";
        Song* temp = tail;
        while (temp != NULL) {
            cout << "ID: " << temp->id 
                 << " | Name: " << temp->name 
                 << " | Duration: " << temp->duration;
            if (temp == currentSong) {
                cout << "  <-- Currently Playing";
            }
            cout << endl;
            temp = temp->prev;
        }
    }

    // 5. Search Song by ID
    void searchSong(int id) {
        if (head == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        Song* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\nSong Found Details:\n";
                cout << "ID: " << temp->id << "\n";
                cout << "Name: " << temp->name << "\n";
                cout << "Duration: " << temp->duration << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song with ID " << id << " not found.\n";
    }

    // 6. Play Next / Previous Song
    void playNext() {
        if (currentSong == NULL) {
            cout << "No songs in playlist.\n";
            return;
        }
        if (currentSong->next != NULL) {
            currentSong = currentSong->next;
            cout << "Now Playing Next: " << currentSong->name << endl;
        } else {
            cout << "You are at the end of the playlist!\n";
        }
    }
    void playPrevious() {
        if (currentSong == NULL) {
            cout << "No songs in playlist.\n";
            return;
        }
        if (currentSong->prev != NULL) {
            currentSong = currentSong->prev;
            cout << "Now Playing Previous: " << currentSong->name << endl;
        } else {
            cout << "You are at the beginning of the playlist!\n";
        }
    }
    // 7. Reverse Playlist in place using pointer manipulation
    void reversePlaylist() {
        if (head == NULL || head->next == NULL) {
            cout << "Playlist reversed (or negligible nodes).\n";
            return;
        }
        Song* current = head;
        Song* temp = NULL;
        // Swap next and prev pointers for all nodes
        while (current != NULL) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; // Moves to next original node
        }
// Adjust head and tail pointers
        if (temp != NULL) {
            tail = head;
            head = temp->prev;
        }
        cout << "Playlist has been successfully reversed in place!\n";
    }
};

int main() {
    Playlist myPlaylist;
    int choice;

do {
        cout << "\n========== PLAYLIST MENU ==========\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

switch (choice) {
    case 1: {
        int id;
            string name, duration;
            cout << "Enter Song ID: ";
            cin >> id;
            cin.ignore(); // Clear buffer
            cout << "Enter Song Name: ";
            getline(cin, name);
            cout << "Enter Duration (min:sec): ";
            cin >> duration;
            myPlaylist.addSong(id, name, duration);
            break;
     }
    case 2: {
            int id;
                cout << "Enter Song ID to delete: ";
                cin >> id;
                myPlaylist.deleteSong(id);
                break;
            }
            case 3:
                myPlaylist.displayForward();
                break;
            case 4:
                myPlaylist.displayBackward();
                break;
            case 5: {
                int id;
                cout << "Enter Song ID to search: ";
                cin >> id;
                myPlaylist.searchSong(id);
                break;
            }
            case 6:
                myPlaylist.playNext();
                break;
            case 7:
                myPlaylist.playPrevious();
                break;
            case 8:
                myPlaylist.reversePlaylist();
                break;
            case 9:
                cout << "Exiting Playlist Manager. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);
    return 0;
}