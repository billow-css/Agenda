#include<iostream>
#include<string> 
#include "AgendaItem.h"
using namespace std;

AgendaItem::AgendaItem(){
	status=0;
	std::cout<<"Default Constructor Called"<<std::endl;
}

AgendaItem::AgendaItem(string nname,string descriptionn, string dddl,string ttime,int ppriority):name(nname),description(descriptionn),ddl(dddl),time(ttime),priority(ppriority){
status=0;
}


AgendaItem::AgendaItem(const AgendaItem &other){
	id=other.id;name=other.name;description=other.description;
	ddl=other.ddl;time=other.time;status=other.status;priority=other.priority;
}

AgendaItem::~AgendaItem() {
}

void AgendaItem::setName(string newName){
	name=newName;
}

void AgendaItem::setDescription(string newDesc){
	description=newDesc;
}

void AgendaItem::setDDL(string newDDL){
	ddl=newDDL;
}

void AgendaItem::setTime(string newTime){
	time=newTime;
}

void AgendaItem::setStatus(int newStatus){
	status=newStatus;
}

void AgendaItem::setPriority(int newPriority){
	priority=newPriority;
}

int AgendaItem::getId() const{
return id;
}

string AgendaItem::getName() const{
return name;
}

string AgendaItem::getDescription() const{
return description;
}

string AgendaItem::getDDL() const{
return ddl;
}

string AgendaItem::getTime()const{
return time;
}

int AgendaItem::getStatus() const{
return status;
}

int AgendaItem::getPriority() const{
return priority;
}

void AgendaItem::displaySingle() const{
    cout << "ID: " << getId() << endl;
    cout << "Name: " << getName() <<endl;
    cout << "Description: " << getDescription() << endl;
    cout << "DDL: " << getDDL() << endl;
    cout << "Time: " << getTime() << endl;
    cout << "Status: " << getStatus() << endl;
    cout << "Priority: " << getPriority() << endl;
}

void AgendaItem::setId(int newId){
	id = newId;
}

// void AgendaItem::toString() const{

// }

// static  AgendaItem fromString(string str){
	
// }

// string AgendaItem::getStatusString() const{
// }

// bool AgendaItem::isOverdue() const{

// }

std::string AgendaItem::getStatusString() const {
	switch (status) {
		case QUEUE:
			return "QUEUE";
		case COMPLETED:
			return "COMPLETED";
		case OVERTIME:
			return "OVERTIME";
		case PAUSE:
			return "PAUSE";
		default:
			return "UNKNOWN";
	}
}
