#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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
        std::vector<Question> search(std::string query = "", std::vector<std::string> tags = {}) {

        }
};

class Account {
    public:
        Account(std::string name, std::string email, std::string password) {
            name_ = name;
            email_ = email;
            password_ = password;
        }

        static void registerAccount(std::string name, std::string email, std::string password) {
            accounts_.push_back(Account(name, email, password));
        }

        static Member* login(std::string email, std::string password) {
            for (Account acc: accounts_) {
                if(email == acc.email_ && password == acc.password_) {
                    return new Member(acc);
                }
            }
            return nullptr;
        }

        std::string getEmail() {
            return email_;
        }

        std::string getName() {
            return name_;
        }

    private:
        std::string name_;
        std::string email_;
        std::string password_;
        static std::vector<Account> accounts_;
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

        void close() {
            isClosed_ = false;
        }

        void reOpen() {
            isClosed_ = true;
        }

        void deleteQuestion() {
            isDeleted_ = true; 
        }

        void undelete() {
            isDeleted_ = false;
        }

        std::vector<Answer> getAnswers() {
            return answers_;
        }

        int getVotes() {
            return votes_;
        }

        bool getIsClosed() {
            return isClosed_;
        }

        bool getIsDeleted() {
            return isDeleted_;
        }

        std::vector<Tag> getTags() {
            return tags_;
        }

    private:
        std::string question_;
        std::vector<Tag> tags_;
        Member member_;
        std::vector<Answer> answers_;
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

class SearchIndex {
    public:
        static Question askQuestion(Member member, std::string question, std::vector<Tag> tags) {
            Question newQuestion(member, question, tags);
            questions_.push_back(newQuestion);
            return newQuestion;
        }

        static std::vector<Question> search(std::vector<Tag> tags = {}) {
            std::vector<Question> results;
            for (Tag tag: tags) {
                for (int questionIdx: tagsToQuestionIndex_[tag.getName()]) {
                    results.push_back(questions_[questionIdx]);
                }
            }
            return results;
        }

    private:
        static std::vector<Question> questions_;
        static std::unordered_map<Tag, std::vector<int>> tagsToQuestionIndex_;
};

int main() {

}