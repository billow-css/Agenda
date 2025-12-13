#pragma once
#include <string>

using namespace std;

enum Status {
    QUEUE = 0,
    COMPLETED = 1,
    OVERTIME = 2,
    PAUSE = 3
};


class AgendaItem {
public:
    AgendaItem();
    AgendaItem(string nname,string descriptionn, string dddl,string ttime,int ppriority);
    AgendaItem(const AgendaItem &other);
    ~AgendaItem();

    void setId(int newId);
    
    void setName(std::string newName);
    void setDescription(std::string newDesc);
    void setDDL(std::string newDDL);
    void setTime(std::string newTime);
    void setStatus(int newStatus);
    void setPriority(int newPriority);
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getDDL() const;
    std::string getTime() const;
    int getStatus() const;
    int getPriority() const;
    std::string getStatusString() const;
    
    // bool isOverdue() const;
     void displaySingle() const;
     void displayBrief() const;
    // std::string toString() const;
    // static AgendaItem fromString(std::string str);

private:
    int id = 0;
    std::string name;
    std::string description;
    std::string ddl;
    std::string time;
    int status;
    int priority;
};
