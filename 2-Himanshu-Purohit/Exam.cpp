#include "Exam.h"
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

Exam::Exam() : questionFile("1-Himanshu-Suthar/data/questions.txt"), answerFile("2-Himanshu-Purohit/data/answers.txt") {}

bool Exam::loadQuestions() {
    questions.clear();
    ifstream in(questionFile.c_str());
    if (!in) return false;
    Question q;
    while (in >> q.questionID >> quoted(q.subject) >> quoted(q.questionText)
              >> quoted(q.options[0]) >> quoted(q.options[1])
              >> quoted(q.options[2]) >> quoted(q.options[3])
              >> q.correctAnswer >> q.marks) questions.push_back(q);
    return !questions.empty();
}

bool Exam::saveAnswers(const string& studentName) const {
    ofstream out(answerFile.c_str(), ios::app);
    if (!out) return false;
    out << "ATTEMPT " << quoted(studentName) << ' ' << answers.size() << '\n';
    for (size_t i = 0; i < answers.size(); ++i)
        out << answers[i].questionID << ' ' << answers[i].answer << '\n';
    out << "END_ATTEMPT\n";
    return static_cast<bool>(out);
}

void Exam::conduct() {
    if (!loadQuestions()) {
        cout << "No questions are available. Add questions before starting an exam.\n";
        return;
    }
    string studentName;
    do {
        cout << "Enter your name: ";
        getline(cin, studentName);
        if (studentName.empty()) cout << "Name cannot be blank.\n";
    } while (studentName.empty());

    answers.clear();
    cout << "\nExam started. Enter A, B, C, or D for each answer.\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        const Question& q = questions[i];
        cout << "\nQuestion " << (i + 1) << " of " << questions.size()
             << " (" << q.getMarks() << " marks)\n" << q.getQuestionText() << '\n';
        for (int option = 0; option < 4; ++option)
            cout << char('A' + option) << ". " << q.getOption(option) << '\n';
        string input;
        char answer = '\0';
        do {
            cout << "Your answer (A-D): ";
            getline(cin, input);
            if (!input.empty()) answer = static_cast<char>(toupper(static_cast<unsigned char>(input[0])));
            if (answer < 'A' || answer > 'D') { answer = '\0'; cout << "Please enter A, B, C, or D.\n"; }
        } while (answer == '\0');
        RecordedAnswer recorded = { q.getID(), answer };
        answers.push_back(recorded);
    }

    if (saveAnswers(studentName))
        cout << "\nExam submitted. Your answers have been recorded.\n";
    else
        cout << "\nCould not save your answers. Check that the data folder is writable.\n";
}
