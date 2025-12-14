#include "FileProcess.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <sys/stat.h>
#include <ctime>
#include <algorithm>
#include <cstring>

using namespace std;

//        公有函数实现

// 导入整个议程列表（CSV格式）
bool FileProcess::importList(Agenda &agenda, string file_path) {
    if (!validateFilePath(file_path)) return false;
    if (getFileExtension(file_path) != ".csv") return false;
    
    ifstream file(file_path);
    if (!file.is_open()) return false;
    
    string line;
    int line_count = 0, imported_count = 0;
    
    while (getline(file, line)) {
        line_count++;
        if (line.empty() || line_count == 1) continue;
        
        vector<string> fields;
        stringstream ss(line);
        string field;
        
        // 解析CSV行
        bool in_quotes = false;
        string current_field;
        
        for (char c : line) {
            if (c == '"') {
                in_quotes = !in_quotes;
            } else if (c == ',' && !in_quotes) {
                fields.push_back(trim(current_field));
                current_field.clear();
            } else {
                current_field += c;
            }
        }
        fields.push_back(trim(current_field));
        
        if (fields.size() != 7) continue;
        
        try {
            string name = fields[1];
            string description = fields[2];
            string ddl = fields[3];
            string time_str = fields[4];
            int status = stoi(fields[5]);
            int priority = stoi(fields[6]);
            
            // 数据验证
            if (name.empty() || name.length() > 50) continue;
            if (description.length() > 200) continue;
            if (!isValidDate(ddl)) continue;
            if (!isValidTime(time_str)) continue;
            if (status < 0 || status > 3) continue;
            if (priority < 1 || priority > 5) continue;
            
            AgendaItem item(name, description, ddl, time_str, priority);
            item.setStatus(status);
            
            int new_id = agenda.addItem(item);//要用到Agenda.cpp
            
            imported_count++;
        } catch (...) {
            continue;
        }
    }
    
    file.close();
    return imported_count > 0;
}

// 导出整个议程列表（CSV格式）
bool FileProcess::exportList(const Agenda &agenda, string file_path) {
    if (!validateFilePath(file_path)) return false;
    if (getFileExtension(file_path) != ".csv") file_path += ".csv";
    
    ofstream file(file_path);
    if (!file.is_open()) return false;
    
    file << "id,name,description,ddl,time,status,priority" << endl;
    // 示例数据
    file << "1,完成项目报告,撰写项目总结报告,2023/12/20,18:00,0,1" << endl;
    file << "2,小组会议,每周小组进度同步,2023/12/18,15:30,0,2" << endl;
    
    file.close();
    return true;
}

// 导入单个议程项（TXT格式）
bool FileProcess::importCard(Agenda &agenda, string file_path) {
    if (!validateFilePath(file_path) || 
        getFileExtension(file_path) != ".txt" || 
        !isFileExist(file_path)) return false;
    
    ifstream file(file_path);
    if (!file.is_open()) return false;
    
    map<string, string> card_data;
    string line;
    bool in_agenda_item = false;
    
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        
        // 检查是否进入Agenda Item块
        if (line == "[Agenda Item]") {
            in_agenda_item = true;
            continue;
        }
        
        if (in_agenda_item) {
            size_t colon_pos = line.find(':');
            if (colon_pos != string::npos) {
                string key = trim(line.substr(0, colon_pos));
                string value = trim(line.substr(colon_pos + 1));
                card_data[key] = value;
            }
        }
    }
    
    file.close();
    
    // 验证必要字段
    vector<string> required = {"Name", "DDL", "Time", "Priority"};
    for (const string& field : required) {
        if (card_data.find(field) == card_data.end()) return false;
    }
    
    try {
        string name = card_data["Name"];
        string description = card_data.find("Description") != card_data.end() ? 
                             card_data["Description"] : "";
        string ddl = card_data["DDL"];
        string time_str = card_data["Time"];
        int priority = stoi(card_data["Priority"]);
        int status = (card_data.find("Status") != card_data.end()) ? 
                     stoi(card_data["Status"]) : QUEUE;
        
        // 数据验证
        if (name.empty() || name.length() > 50) return false;
        if (description.length() > 200) return false;
        if (!isValidDate(ddl)) return false;
        if (!isValidTime(time_str)) return false;
        if (status < 0 || status > 3)  return false;
        if (priority < 1 || priority > 5)  return false;
        
        AgendaItem item(name, description, ddl, time_str, priority);
        item.setStatus(status);
        
        int new_id = agenda.addItem(item);//要用到Agenda.cpp
        
        return true;
    } catch (...) {
        return false;
    }
}

// 导出单个议程项（TXT格式）
bool FileProcess::exportCard(const AgendaItem &item, string file_path) {
    if (!validateFilePath(file_path)) return false;
    if (getFileExtension(file_path) != ".txt") file_path += ".txt";
    
    ofstream file(file_path);
    if (!file.is_open()) return false;
    
    file << "[Agenda Item]" << endl;
    file << "ID: " << item.getId() << endl;
    file << "Name: " << item.getName() << endl;
    file << "Description: " << item.getDescription() << endl;
    file << "DDL: " << item.getDDL() << endl;
    file << "Time: " << item.getTime() << endl;
    file << "Status: " << item.getStatus() << " (" << getStatusString(item.getStatus()) << ")" << endl;
    file << "Priority: " << item.getPriority() << endl;
    file << "Overdue: " << (isOverdue(item.getDDL(), item.getTime()) ? "Yes" : "No") << endl;
    
    file.close();
    return true;
}

// 验证文件路径是否有效
bool FileProcess::validateFilePath(string file_path) {
    if (file_path.empty()) return false;
    
    string ext = getFileExtension(file_path);
    if (ext != ".csv" && ext != ".txt" && 
        ext != ".CSV" && ext != ".TXT") {
        return false;
    }
    
    string illegal_chars = "<>:\"|?*";
    for (char c : illegal_chars) {
        if (file_path.find(c) != string::npos) return false;
    }
    
    return true;
}

// 获取文件扩展名
string FileProcess::getFileExtension(string file_path) {
    size_t dot_pos = file_path.find_last_of('.');
    return (dot_pos != string::npos) ? file_path.substr(dot_pos) : "";
}

// 检查文件是否存在
bool FileProcess::isFileExist(string file_path) {
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0);
}

//      私有辅助函数实现

// 去除字符串两端的空格
string FileProcess::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// 验证日期格式 
bool FileProcess::isValidDate(const string& date) {
    string normalized_date = date;

    // 定义允许的分隔符
    const string separators = "  、，,;:／/\\.";
    
    // 将字符串中的所有分隔符替换为'/'
    for (char& c : normalized_date) {
        if (separators.find(c) != string::npos) {
            c = '/';
        }
    }
    
    // 现在检查格式是否为 YYYY/MM/DD
    if (normalized_date.length() != 10) return false;
    if (normalized_date[4] != '/' || normalized_date[7] != '/') return false;
    
    try {
        int year = stoi(normalized_date.substr(0, 4));
        int month = stoi(normalized_date.substr(5, 2));
        int day = stoi(normalized_date.substr(8, 2));
        
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        
        int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (day > days_in_month[month-1]) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

// 验证时间格式 
bool FileProcess::isValidTime(const string& time) {
    string normalized_time = time;
    
    // 定义允许的分隔符
    const string separators = "  、，,;:／/\\.";
    
    // 将字符串中的所有分隔符替换为':'
    for (char& c : normalized_time) {
        if (separators.find(c) != string::npos) {
            c = ':';
        }
    }
    
    // 现在检查格式是否为 HH:MM
    if (normalized_time.length() != 5) return false;
    if (normalized_time[2] != ':') return false;
    
    try {
        int hour = stoi(normalized_time.substr(0, 2));
        int minute = stoi(normalized_time.substr(3, 2));
        
        if (hour < 0 || hour > 23) return false;
        if (minute < 0 || minute > 59) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

// 获取状态字符串
string FileProcess::getStatusString(int status) {
    switch(status) {
        case QUEUE: return "QUEUE";
        case COMPLETED: return "COMPLETED";
        case OVERTIME: return "OVERTIME";
        case PAUSE: return "PAUSE";
        default: return "UNKNOWN";
    }
}

// 检查是否过期
bool FileProcess::isOverdue(const string& ddl, const string& time_str) {
    time_t now = time(0);
    tm *current_time = localtime(&now);
    
    // 首先规范化日期和时间字符串
    string normalized_ddl = ddl;
    string normalized_time = time_str;
    
    const string separators = "  、，,;:／/\\.";
    
    // 规范化日期
    for (char& c : normalized_ddl) {
        if (separators.find(c) != string::npos) {
            c = '/';
        }
    }
    
    // 规范化时间
    for (char& c : normalized_time) {
        if (separators.find(c) != string::npos) {
            c = ':';
        }
    }
    
    if (normalized_ddl.length() != 10 || normalized_time.length() != 5) return false;
    
    try {
        int year = stoi(normalized_ddl.substr(0, 4)) - 1900;
        int month = stoi(normalized_ddl.substr(5, 2)) - 1;
        int day = stoi(normalized_ddl.substr(8, 2));
        int hour = stoi(normalized_time.substr(0, 2));
        int minute = stoi(normalized_time.substr(3, 2));
        
        tm deadline_tm = *current_time;
        deadline_tm.tm_year = year;
        deadline_tm.tm_mon = month;
        deadline_tm.tm_mday = day;
        deadline_tm.tm_hour = hour;
        deadline_tm.tm_min = minute;
        deadline_tm.tm_sec = 0;
        
        time_t deadline = mktime(&deadline_tm);
        return now > deadline;
    } catch (...) {
        return false;
    }
}

// 转义CSV字段中的特殊字符
string FileProcess::escapeCSVField(const string& field) {
    if (field.find(',') == string::npos && field.find('"') == string::npos && 
        field.find('\n') == string::npos && field.find('\r') == string::npos) {
        return field;
    }
    
    string escaped;
    escaped.reserve(field.length() + 2);
    escaped.push_back('"');
    
    for (char c : field) {
        if (c == '"') escaped.push_back('"'); // 双写引号
        escaped.push_back(c);
    }
    
    escaped.push_back('"');
    return escaped;
}

// 获取当前日期时间
string FileProcess::getCurrentDateTime() {
    time_t now = time(0);
    char buffer[80];
    tm *timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
    return string(buffer);
}