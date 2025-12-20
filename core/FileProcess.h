#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include "Agenda.h"
#include "AgendaItem.h"
#include <string>

using namespace std;

class FileProcess {
public:
    static bool importList(Agenda &agenda, string file_path);
    static bool exportList(const Agenda &agenda, string file_path);
    static bool importCard(Agenda &agenda, string file_path);
    static bool exportCard(const AgendaItem &item, string file_path);
    
    static bool validateFilePath(string file_path);
    static string getFileExtension(string file_path);
    static bool isFileExist(string file_path);
    static bool isValidDate(const string& date);
    static bool isValidTime(const string& time);
    
private:
    static string trim(const string& str);
    static string getStatusString(int status);
    static bool isOverdue(const string& ddl, const string& time_str);
    static string escapeCSVField(const string& field);
    static string getCurrentDateTime();
};

#endif // FILEPROCESS_H
