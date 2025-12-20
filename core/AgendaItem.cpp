#include<iostream>
#include<string> 
#include "AgendaItem.h"
using namespace std;

AgendaItem::AgendaItem(){
	status=0;
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
	std::string color_status;
	switch (status) {
		case QUEUE:
			color_status = "\033[106m";
			break;
		case COMPLETED:
			color_status = "\033[102m";
			break;
		case OVERTIME:
			color_status = "\033[101m";
			break;
		case PAUSE:
			color_status = "\033[103m";
			break;
		default:
			color_status = "\033[107m";
			break;
	}
	std::string color_priority;
	switch (priority) {
		case 1:
			color_priority = "\033[101m\033[30m LEVEL_1 紧急 \033[0m";
			break;
		case 2:
			color_priority = "\033[103m\033[30m LEVEL_2 优先 \033[0m";
			break;
		case 3:
			color_priority = "\033[102m\033[30m LEVEL_3 中等 \033[0m";
			break;
		case 4:
			color_priority = "\033[106m\033[30m LEVEL_4 一般 \033[0m";
			break;
		default:
			color_priority = "\033[107m\033[30m OTHERS \033[0m";
			break;
	}
    cout << "\033[103m\033[30m#   第" << getId() << "条记录   \033[0m"<< endl;
    cout << "\n| " << getName() <<endl;
    cout << "DDL: " << getDDL();
    cout << " " << getTime() << endl;
    cout << "状态: \033[30m" << color_status << getStatusString() << "\033[0m" << endl;
    cout << "优先级: " << color_priority << endl;
	cout << "| \033[3;90m 日程描述：" << getDescription() << "\033[0m" << endl;
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
			return "QUEUE 等待完成";
		case COMPLETED:
			return "COMPLETED 完成";
		case OVERTIME:
			return "OVERTIME 超时";
		case PAUSE:
			return "PAUSE 暂停";
		default:
			return "UNKNOWN 未知属性";
	}
}



void AgendaItem::displayBrief() const {
	std::string delete_line;
	if (status == COMPLETED)
	{
		delete_line = "\033[9m\033[2m\033[3m";
	} else {
		delete_line = "";
	}
	
	std::string color_status;
	switch (status) {
		case QUEUE:
			color_status = "\033[106m";
			break;
		case COMPLETED:
			color_status = "\033[102m";
			break;
		case OVERTIME:
			color_status = "\033[101m";
			break;
		case PAUSE:
			color_status = "\033[103m";
			break;
		default:
			color_status = "\033[107m";
			break;
	}
	std::string color_priority;
	switch (priority) {
		case 1:
			color_priority = "\033[101m\033[30m LEVEL_1 紧急 \033[0m";
			break;
		case 2:
			color_priority = "\033[103m\033[30m LEVEL_2 优先 \033[0m";
			break;
		case 3:
			color_priority = "\033[102m\033[30m LEVEL_3 中等 \033[0m";
			break;
		case 4:
			color_priority = "\033[106m\033[30m LEVEL_4 一般 \033[0m";
			break;
		default:
			color_priority = "\033[107m\033[30m OTHERS \033[0m";
			break;
	}
	cout << "\033[36m\033[1m  " << getId() << "  \033[0m|  " << delete_line << getName() << "  |  \033[33m" << getDDL() << "\033[0m  |\033[30m  "<< color_status << getStatusString() <<"\033[0m "<< color_priority << "  \033[0m" << endl;
}