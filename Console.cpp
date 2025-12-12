#include<iostream>
#include<string>
#include"Agenda.h"
#include"AgendaItem.h"
#include"FileProcess.h"
#include"Console.h"

// enum ConsoleState {
//     A01_MAIN_MENU = 0,
//     A02_VIEW_ITEMS = 1,
//     B01_EDIT_ITEM = 2,
//     B02_FILTER_ITEM = 3,
//     B03_ADD_ITEMS = 4,
//     C01_IMPORT = 5,
//     C02_EXPORT = 6,
//     H01_HELP = 7
// };

bool isAllDigit(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

Console::Console(){
    agenda_ptr = new Agenda();
}
Console::Console(Agenda* agenda){
    agenda_ptr = agenda;
}
Console::~Console(){
    delete agenda_ptr;
}
void Console::run(){
    menuA01();
}
void Console::shutdown(){
    std::cout << "Shutting down the console..." << std::endl;
    file_processor.exportList(*agenda_ptr, "autosave.txt");
    exit(0);
}


void Console::showMessage(const std::string& message){
    std::cout << message << std::endl;
}
void Console::clearScreen(){
    system("pause"); // Pause before clearing
    system("cls"); // For Windows
}

void Console::menuA01(){
    clearScreen();
    cout << "=== Agenda Items ===" << std::endl;
    agenda_ptr->displayList();
    cout << "\033[43m  \033[0m";
    std::string choice = input();
    processA01(choice);
}
void Console::menuA02(){
    clearScreen();
    AgendaItem item = agenda_ptr->getItem(selected_item_id);
    if (item.getId() == -1)
    {
        showMessage("Item not found.");
        menuA01();
    }
    else
    {
        item.displaySingle();
        cout << "\033[43m  \033[0m";
        cout << "R::delete" <<std::endl;
        cout << "E::edit" <<std::endl;
        cout << "S::save" <<std::endl;
        cout << "0::quit" <<std::endl;
        std::string choice = input();
        processA02(choice);
    }
}
void Console::menuB01(){
    clearScreen();
    AgendaItem item = agenda_ptr->getItem(selected_item_id);
    if (item.getId() == -1)
    {
        showMessage("Item not found.");
        menuA01();
    }
    else
    {
        item.displaySingle();
        cout << "\033[43m  \033[0m";
        cout << "1::edit name" <<std::endl;
        cout << "2::edit description" <<std::endl;
        cout << "3::edit DDL" <<std::endl;
        cout << "4::edit time" <<std::endl;
        cout << "5::edit status" <<std::endl;
        cout << "6::edit priority" <<std::endl;
        cout << "0::quit" <<std::endl;
        std::string choice = input();
        processB01(choice);
    }
}
void Console::menuB02(){
    clearScreen();
    agenda_ptr->displayList();
    std::string choice;
    cout << "1::By_name" << std::endl;
    cout << "2::By_priority" << std::endl;
    cout << "3::By_DDL" << std::endl;
    cout << "4::By_status" << std::endl;
    cout << "5::clear" << std::endl;
    cout << "0::quit" << std::endl;
    cout << "Enter filter code: ";
    getline(cin, choice);
    processB02(choice);
}
void Console::menuB03(){
    clearScreen();
    AgendaItem newItem = createItemFromInput();
    agenda_ptr->addItem(newItem);
    showMessage("Item added successfully.");
    menuA01();
}
void Console::menuC01(){
    clearScreen();
    std::string file_path;
    cout << "Enter file path to import: ";
    getline(cin, file_path);
    if (file_processor.importList(*agenda_ptr, file_path))
    {
        showMessage("Import successful.");
    }
    else
    {
        showMessage("Import failed.");
    }
    menuA01();
}
void Console::menuC02(int export_type){
    clearScreen();
    std::string file_path;
    cout << "Enter file path to export: ";
    getline(cin, file_path);
    bool success = false;
    if (export_type == 0) // Export entire list
    {
        success = file_processor.exportList(*agenda_ptr, file_path);
    }
    else if (export_type == 1) // Export single item
    {
        AgendaItem item = agenda_ptr->getItem(selected_item_id);
        success = file_processor.exportCard(item, file_path);
    }

    if (success)
    {
        showMessage("Export successful.");
    }
    else
    {
        showMessage("Export failed.");
    }
    menuA01();
}
void Console::menuH01(){
    clearScreen();
    cout << "Help Menu:" << std::endl;
    cout << "---------"<< std::endl;
    cout << "In this application, you can manage your agenda items using the following commands:" << std::endl;
    cout << "In A01 LIST:" << std::endl;
    cout << "A::Add new item" << std::endl;
    cout << "S::Save items to file" << std::endl;
    cout << "I::Import items from file" << std::endl;
    cout << "V::View/Filter items" << std::endl;
    cout << "T::Insert item at position" << std::endl;
    cout << "C::Clear all items" << std::endl;
    cout << "H::Help menu" << std::endl;
    cout << std::endl;
    cout << "In A02 VIEW/EDIT:" << std::endl;
    cout << "R::Delete item" << std::endl;
    cout << "E::Edit item" << std::endl;
    cout << "S::Save item to file" << std::endl;
    cout << "0::Return to main menu" << std::endl;
    cout << std::endl;
    cin.ignore();
    menuA01();
}
void Console::processA01(const std::string &choice){
    if (choice == "A")
    {
        menuB03();
    }
    else if (choice == "S")
    {
        menuC02(0);
    }
    else if (choice == "I")
    {
        menuC01();
    }
    else if (choice == "V")
    {
        menuB02();
    }
    else if (choice == "T")
    {
        int position;
        cout << "Enter position to insert the new item: ";
        cin >> position;
        cin.ignore(); // To ignore the newline character after integer input
        AgendaItem newItem = createItemFromInput();
        newItem.setId(position); // Temporary ID, will be set by Agenda
        agenda_ptr->insertItem(position-1, newItem);
        showMessage("Item inserted successfully.");
    }
    else if (choice == "C")
    {
        agenda_ptr->clearAll();
        showMessage("All items cleared.");
    }
    else if (choice == "H")
    {
        menuH01();
    }
    else if (isAllDigit(choice))
    {
        selected_item_id = std::stoi(choice);
        if (selected_item_id == 0)
        {
            shutdown();
            return;
        }
        menuA02();
    }
    else
    {
        showMessage("Invalid choice. Please try again.");
    }
    
}
void Console::processA02(const std::string &choice){
    if (choice == "R")
    {
        if (agenda_ptr->removeItem(selected_item_id))
        {
            showMessage("Item deleted successfully.");
        }
        else
        {
            showMessage("Failed to delete item.");
        }
        menuA01();
    }
    else if (choice == "E")
    {
        menuB01();
    }
    else if (choice == "S")
    {
        menuC02(1);
    }
    else if (choice == "0")
    {
        menuA01();
    }
    else
    {
        showMessage("Invalid choice. Please try again.");
        menuA02();
    }
}
void Console::processB01(const std::string &choice){
    int code = std::stoi(choice);
    AgendaItem item = agenda_ptr->getItem(selected_item_id);
    switch (code)
    {
    case 1:{
         item.setName(input());
        agenda_ptr->updateItem(selected_item_id, item);
        break;}
    case 2:{
        item.setDescription(input());
        agenda_ptr->updateItem(selected_item_id, item);
        break;}
    case 3:{
        item.setDDL(input());
        agenda_ptr->updateItem(selected_item_id, item);
        break;}
    case 4:{
        item.setTime(input());
        agenda_ptr->updateItem(selected_item_id, item);
        break; }
    case 5:
        {
            int newStatus;
            cin >> newStatus;
            cin.ignore(); // To ignore the newline character after integer input
            item.setStatus(newStatus);
            agenda_ptr->updateItem(selected_item_id, item);
            break;}
    case 6:
        {
            int newPriority;
            cin >> newPriority;
            cin.ignore(); // To ignore the newline character after integer input
            item.setPriority(newPriority);
            agenda_ptr->updateItem(selected_item_id, item);
            break;}
    case 0:
        menuA02();
        return;
    default:
        break;
    }
    menuB01();
}
void Console::processB02(const std::string &choice){
    if (choice == "1")
    {
        std::string name_filter;
        cout << "Enter name to filter by: ";
        getline(cin, name_filter);
        agenda_ptr->applyFilter(4, name_filter);
        showMessage("Filter applied.");
    }
    else if (choice == "2")
    {
        std::string priority_filter;
        cout << "Enter priority to filter by: ";
        getline(cin, priority_filter);
        agenda_ptr->applyFilter(1, priority_filter);
        showMessage("Filter applied.");
    }
    else if (choice == "3")
    {
        std::string ddl_filter;
        cout << "Enter DDL to filter by: ";
        getline(cin, ddl_filter);
        agenda_ptr->applyFilter(2, ddl_filter);
        showMessage("Filter applied.");
    }
    else if (choice == "4")
    {
        std::string status_filter;
        cout << "Enter status to filter by: ";
        getline(cin, status_filter);
        agenda_ptr->applyFilter(3, status_filter);
        showMessage("Filter applied.");
    }
    else if (choice == "5")
    {
        agenda_ptr->clearFilter();
        showMessage("Filters cleared.");
    }
    else if (choice == "0")
    {
        menuA01();
        return;
    }
    else
    {
        showMessage("Invalid choice. Please try again.");
    }
    menuB02();
}
std::string Console::input(){
    std::string input_str;
    cout << "> ";
    getline(cin, input_str);
    return input_str;
}

AgendaItem Console::createItemFromInput(){
    string name, description, ddl, time;
    int priority;

    cout << "Enter item name: ";
    getline(cin, name);

    cout << "Enter item description: ";
    getline(cin, description);

    cout << "Enter item deadline (DDL): ";
    getline(cin, ddl);

    cout << "Enter item time: ";
    getline(cin, time);

    cout << "Enter item priority (integer): ";
    cin >> priority;
    cin.ignore(); // To ignore the newline character after integer input

    AgendaItem newItem(name, description, ddl, time, priority);
    return newItem;
}
