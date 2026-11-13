
#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class to store one question
class Question {
private:
    int questionID;
    string subject;
    string questionText;
    string options[4];
    char correctAnswer;
    int marks;

    friend class QuestionManager;
    friend class Exam;

public:
    Question();

    void inputQuestion(int id);
    void displayQuestion() const;
    void updateQuestion(int id);

    int getID() const;
    const string& getSubject() const;
    const string& getQuestionText() const;
    const string& getOption(int index) const;
    int getMarks() const;
    char getCorrectAnswer() const;
};

// Class to manage all questions
class QuestionManager {
private:
    vector<Question> questions;
    string fileName;

    void loadFromFile();
    void saveToFile() const;

public:
    QuestionManager();

    void addQuestion();
    void viewAllQuestions() const;
    void searchQuestion() const;
    void updateQuestion();
    void deleteQuestion();
};

#endif
