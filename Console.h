#pragma once

#include<iostream>
#include<string>
#include<stack>
#include"Agenda.h"
#include"AgendaItem.h"
#include"Fileprocees.h"

enum ConsoleState {
    A01_MAIN_MENU = 0,
    A02_VIEW_ITEMS = 1,
    B01_EDIT_ITEM = 2,
    B02_FILTER_ITEM = 3,
    B03_ADD_ITEMS = 4,
    C01_IMPORT = 5,
    C02_EXPORT = 6,
    H01_HELP = 7
};

class Console {
    public:
        Console();
        Console(Agenda* agenda);
        ~Console();
        void run();
        void shutdown();

        void showMessage(const std::string& message);
        void clearMessage();
        void refreshDisplay();
        void clearScreen();

        void menuA01();
        void menuA02();
        void menuB01();
        void menuB02();
        void menuB03();
        void menuC01();
        void menuC02(int export_type);
        void menuH01();

        void processA01(const std::string &choice);
        void processA02(const std::string &choice);
        void processB01(const std::string &choice);
        void processB02(const std::string &choice);

        std::string input();

        AgendaItem Console::createItemFromInput();

    private:
        Agenda* agenda_ptr;
        FileProcess file_processor;
        int current_state;
        std::stack<ConsoleState> state_history;
        int selected_item_id;
};
