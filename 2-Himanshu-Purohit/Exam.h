#ifndef EXAM_H
#define EXAM_H

#include "../1-Himanshu-Suthar/Question.h"
#include <string>
#include <vector>

struct RecordedAnswer {
    int questionID;
    char answer;
};

class Exam {
private:
    std::vector<Question> questions;
    std::vector<RecordedAnswer> answers;
    std::string questionFile;
    std::string answerFile;

    bool loadQuestions();
    bool saveAnswers(const std::string& studentName) const;

public:
    Exam();
    void conduct();
};

#endif
