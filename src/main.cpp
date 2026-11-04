
#include <iostream>
#include <string>

#include "../include/Question.h"

using namespace std;

int main() {

    QuestionManager manager;
    string choice;

    do {
        cout << "\n";
        cout << "========================================\n";
        cout << "       ONLINE EXAMINATION SYSTEM\n";
        cout << "          QUESTION MANAGEMENT\n";
        cout << "========================================\n";

        cout << "1. Add New Question\n";
        cout << "2. View All Questions\n";
        cout << "3. Search Question\n";
        cout << "4. Update Question\n";
        cout << "5. Delete Question\n";
        cout << "6. Exit\n";

        cout << "========================================\n";
        cout << "Enter your choice: ";

        getline(cin, choice);

        if (choice == "1") {
            manager.addQuestion();
        }
        else if (choice == "2") {
            manager.viewAllQuestions();
        }
        else if (choice == "3") {
            manager.searchQuestion();
        }
        else if (choice == "4") {
            manager.updateQuestion();
        }
        else if (choice == "5") {
            manager.deleteQuestion();
        }
        else if (choice == "6") {
            cout << "\nThank you for using the system!\n";
        }
        else {
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != "6");

    return 0;
}
