#include "Question.h"
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>

Question::Question() : questionID(0), correctAnswer('A'), marks(1) {}

int Question::getID() const { return questionID; }
const string& Question::getSubject() const { return subject; }
const string& Question::getQuestionText() const { return questionText; }
const string& Question::getOption(int index) const { return options[index]; }
int Question::getMarks() const { return marks; }
char Question::getCorrectAnswer() const { return correctAnswer; }

void Question::inputQuestion(int id) {
    questionID = id;
    cout << "Subject: "; getline(cin, subject);
    cout << "Question: "; getline(cin, questionText);
    for (int i = 0; i < 4; ++i) {
        cout << "Option " << char('A' + i) << ": "; getline(cin, options[i]);
    }
    do {
        cout << "Correct option (A-D): ";
        string input; getline(cin, input);
        correctAnswer = input.empty() ? '\0' : char(toupper(input[0]));
    } while (correctAnswer < 'A' || correctAnswer > 'D');
    do {
        cout << "Marks: ";
        string input; getline(cin, input);
        try { marks = stoi(input); } catch (...) { marks = 0; }
    } while (marks <= 0);
}

void Question::displayQuestion() const {
    cout << "\nID: " << questionID << " | Subject: " << subject
         << " | Marks: " << marks << "\n" << questionText << "\n";
    for (int i = 0; i < 4; ++i) cout << char('A' + i) << ". " << options[i] << "\n";
}

void Question::updateQuestion(int id) { inputQuestion(id); }

QuestionManager::QuestionManager() : fileName("1-Himanshu-Suthar/data/questions.txt") { loadFromFile(); }

void QuestionManager::loadFromFile() {
    questions.clear();
    ifstream in(fileName.c_str());
    Question q;
    while (in >> q.questionID >> quoted(q.subject) >> quoted(q.questionText)
              >> quoted(q.options[0]) >> quoted(q.options[1])
              >> quoted(q.options[2]) >> quoted(q.options[3])
              >> q.correctAnswer >> q.marks) questions.push_back(q);
}

void QuestionManager::saveToFile() const {
    ofstream out(fileName.c_str());
    for (size_t i = 0; i < questions.size(); ++i) {
        const Question& q = questions[i];
        out << q.questionID << '\n' << quoted(q.subject) << '\n' << quoted(q.questionText) << '\n'
            << quoted(q.options[0]) << '\n' << quoted(q.options[1]) << '\n'
            << quoted(q.options[2]) << '\n' << quoted(q.options[3]) << '\n'
            << q.correctAnswer << '\n' << q.marks << '\n';
    }
}

void QuestionManager::addQuestion() {
    int id = 1;
    for (size_t i = 0; i < questions.size(); ++i) if (questions[i].questionID >= id) id = questions[i].questionID + 1;
    Question q; q.inputQuestion(id); questions.push_back(q); saveToFile();
    cout << "Question saved.\n";
}

void QuestionManager::viewAllQuestions() const {
    if (questions.empty()) { cout << "No questions found.\n"; return; }
    for (size_t i = 0; i < questions.size(); ++i) questions[i].displayQuestion();
}

void QuestionManager::searchQuestion() const {
    cout << "Enter question ID: "; string input; getline(cin, input);
    int id = 0; try { id = stoi(input); } catch (...) {}
    for (size_t i = 0; i < questions.size(); ++i) if (questions[i].questionID == id) { questions[i].displayQuestion(); return; }
    cout << "Question not found.\n";
}

void QuestionManager::updateQuestion() {
    cout << "Enter question ID to update: "; string input; getline(cin, input);
    int id = 0; try { id = stoi(input); } catch (...) {}
    for (size_t i = 0; i < questions.size(); ++i) if (questions[i].questionID == id) {
        questions[i].updateQuestion(id); saveToFile(); cout << "Question updated.\n"; return;
    }
    cout << "Question not found.\n";
}

void QuestionManager::deleteQuestion() {
    cout << "Enter question ID to delete: "; string input; getline(cin, input);
    int id = 0; try { id = stoi(input); } catch (...) {}
    for (vector<Question>::iterator it = questions.begin(); it != questions.end(); ++it) if (it->questionID == id) {
        questions.erase(it); saveToFile(); cout << "Question deleted.\n"; return;
    }
    cout << "Question not found.\n";
}
