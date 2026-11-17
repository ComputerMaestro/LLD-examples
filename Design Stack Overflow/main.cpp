#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define upVoteQuestionReputation 10
#define upVoteAnswerReputation 15

class Member;
class Question;

enum QuestionStatus {
    DRAFT,
    PUBLISHED,
    DELETED,
};

class Badge {
    public:
        Badge (std::string name) {
            name_ = name;
        }

        std::string getName() {
            return name_;
        }
    private:
        std::string name_;
};

class Tag {
    public:
        Tag(std::string name) {
            name_ = name;
        }

        std::string getName() {
            return name_;
        }
    private:
        std::string name_;
};

class Guest {
    public:
        std::vector<Question> search(std::string query, std::vector<std::string> tags = {}) {

        }
};

class Account {
    public:
        Account(std::string name, std::string email, std::string password) {
            name_ = name;
            email_ = email;
            password_ = password;
        }

        Member* login(std::string email, std::string password) {
            if (email == email_ && password == password_) {
                return new Member(*this);
            }
            return nullptr;
        }

        std::string getEmail() {
            return email_;
        }

    private:
        std::string name_;
        std::string email_;
        std::string password_;
};

class Member : public Guest {
    public:
        Member(Account account) : account_(account), reputation_(0), badges_() {}

        std::vector<Badge> getBadges() {
            return badges_;
        }

        int getReputation() {
            return reputation_;
        }

        void updateReputation(int reputation) {
            reputation_ = std::max(reputation_ + reputation, 0);
        }

    private:
        Account account_;
        int reputation_;
        std::vector<Badge> badges_;
};

class Question {
    public:
        Question(Member member, std::string question, std::vector<Tag> tags = {}) : member_(member), question_(question), tags_(tags) {}

        void upVote() {
            member_.updateReputation(upVoteQuestionReputation);
            votes_++;
        }

        void remoteVote() {
            member_.updateReputation(-upVoteQuestionReputation);
            votes_--;
        }

    private:
        std::string question_;
        std::vector<Tag> tags_;
        Member member_;
        std::vector<int> answers_;
        int votes_;
        bool isClosed_;
        bool isDeleted_;
};

class Answer {
    public:
        Answer(Member member, Question question, std::string answer) : member_(member), question_(question), answer_(answer) {}

        Member getMember() {
            return member_;
        }

        int getVotes() {
            return votes_;
        }

        void upVote() {
            member_.updateReputation(upVoteAnswerReputation);
            votes_++;
        }

        void removeVote() {
            member_.updateReputation(-upVoteAnswerReputation);
            votes_--;
        }

        std::vector<Comment> getComments() {
            return comments_;
        }

    private:
        std::string answer_;
        Member member_;
        Question question_;
        int votes_;
        std::vector<Comment> comments_;
};

class Comment {
    public:
        

    private:
        std::string comment_;
        Member member_;
        Answer answer_;
};

class QuestionStore {
    public:
        Question askQuestion(Member member, std::string question, std::vector<Tag> tags) {
            Question newQuestion(member, question, tags);
            questions_.push_back(newQuestion);
            return newQuestion;
        }

    private:
        std::vector<Question> questions_;
        std::vector<Tag> tags_;
};

int main() {

}