#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include "Agenda.h"
#include "AgendaItem.h"

class FileProcess {
public:
    static bool importList(Agenda &agenda, string file_path);
    static bool exportList(const Agenda &agenda, string file_path);
    static bool importCard(Agenda &agenda, string file_path);
    static bool exportCard(const AgendaItem &item, string file_path);
    static bool validateFilePath(string file_path);
    static string getFileExtension(string file_path);
    static bool isFileExist(string file_path);
};


#endif // FILEPROCESS_H

