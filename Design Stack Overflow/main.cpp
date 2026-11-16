#include <iostream>
#include <string>
#include <vector>

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
    private:
        std::string name_;
        std::string email_;
        std::string password_;
};

class Member : public Guest {
    public:
        Member(Account account) : account_(account) {}

        std::vector<Badge> getBadges() {
            return badges_;
        }

        int getReputation() {
            return reputation_;
        }

        void updateReputation(int reputation) {
            reputation_ += reputation;
            reputation_ = std::max(reputation, 0);
            return;
        }
    private:   
        Account account_;
        int reputation_;
        std::vector<Badge> badges_;
};

class Question {
    public:
        Question(std::string question, std::vector<Tag> tags = {}) {
            question_ = question;
            tags_ = tags;
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

int main() {

}