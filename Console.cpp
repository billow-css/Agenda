#include<iostream>
#include<string>
#include"Agenda.h"
#include"AgendaItem.h"
#include"FileProcess.h"
#include"Console.h"


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
    std::cin.ignore();
}
void Console::clearScreen(){
    system("cls"); // For Windows
}

void Console::menuA01(){
    if (is_first_open == 0)
    {
        cout << std::endl;
        cout << "\033[1;36m欢迎使用 \033[1;33mAgenda 日程管理   \033[1;36m\033[0m" << std::endl;
        cout << "\033[1;35m首次打开，教程如下：\033[0m" << std::endl << std::endl;
        
        cout << "\033[1;34m=== 快速指令指引 ===\033[0m" << std::endl;
        cout << "  \033[1;33m[\033[4;32mA\033[0;1;33mdd]\033[0m::添加日程" << std::endl;
        cout << "  \033[1;33m[\033[4;32mI\033[0;1;33mmport]\033[0m::导入日程" << std::endl;
        cout << "  \033[1;33m[\033[4;32mV\033[0;1;33miew]\033[0m::查看设置" << std::endl;
        cout << "  \033[1;33m[inser\033[4;32mT\033[0;1;33m]\033[0m::插入日程" << std::endl;
        cout << "  \033[1;33m[\033[1;36m数字键\033[1;33m]\033[0m::选择项目" << std::endl;
        cout << "  \033[1;33m[\033[1;36mQ\033[1;33m]\033[0m::快速完成" << std::endl;
        cout << "  \033[1;33m[\033[1;31m0\033[1;33m]\033[0m::保存并退出" << std::endl << std::endl;
        
        cout << "\033[3;90m提示: 其他指令请查看帮助菜单 \033[1;93mH\033[3;90m\033[0m" << std::endl;
        cout << "\033[3;90m注意: 再次回到菜单将不再显示此教程\033[0m" << std::endl << std::endl;
        cout << "\033[1;92m>> 现在按任意键继续... <<\033[0m" << std::endl;
        
        is_first_open = -1;
        std::cin.ignore();
    }
    clearScreen();
    cout << "\033[103m\033[30m=====AGENDA日程清单查看页=====\033[0m" << std::endl;
    agenda_ptr->displayList();
    std::string choice = input();
    processA01(choice);
}
void Console::menuA02(){
    clearScreen();
    AgendaItem item = agenda_ptr->getItem(selected_item_id);
    if (item.getId() == -1 || item.getId() == 0 || item.getName() == "")
    {
        showMessage("\033[101m\033[30m  未找到元素 \033[0m");
        menuA01();
    }
    else
    {
        item.displaySingle();
        cout << "\033[43m  \033[0m";
        cout << "\033[91mR::删除记录\033[0m  " ;
        cout << "E::编辑  " ;
        cout << "S::保存  ";
        cout << "0::退出  " <<std::endl;
        std::string choice = input();
        processA02(choice);
    }
}
void Console::menuB01(){
    clearScreen();
    AgendaItem item = agenda_ptr->getItem(selected_item_id);
    if (item.getId() == -1)
    {
        showMessage("\033[101m\033[30m  未找到元素 \033[0m");
        menuA01();
    }
    else
    {
        item.displaySingle();
        cout << "1::编辑名称" <<std::endl;
        cout << "2::编辑描述" <<std::endl;
        cout << "3::编辑DDL" <<std::endl;
        cout << "4::编辑时间" <<std::endl;
        cout << "5::编辑状态" <<std::endl;
        cout << "6::编辑优先级" <<std::endl;
        cout << "0::退出" <<std::endl;
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
    showMessage("\033[102m\033[30m  日程成功创建，在下方输入0结束  \033[0m");
    int cont;
    cin >> cont;
    cin.ignore();
    if (cont == 0)
    {
        menuA01();
    }
    else
    {
        menuB03();
    }
}
void Console::menuB04(){
    clearScreen();
    cout << "\033[103m\033[30m=====AGENDA日程清单查看页 标记模式 =====\033[0m" << std::endl;
    agenda_ptr->displayList();
    int target_id;
    cout << "[x] ";
    cin >> target_id;
    cin.ignore();
    if(target_id == 0){
        menuA01();
    }
    AgendaItem item = agenda_ptr->getItem( target_id);
    if (item.getId() == -1|| item.getName() == "")
    {
        showMessage("\033[101m\033[30m  未找到元素 \033[0m");
        menuB04();
    }
    else
    {
        if (item.getStatus() == COMPLETED)
        {
            item.setStatus(QUEUE);
            agenda_ptr->updateItem( target_id, item);
            showMessage("\033[102m\033[30m  日程已标记为未完成  \033[0m");
            menuB04();
        }
        else
        {
            item.setStatus(COMPLETED);
            agenda_ptr->updateItem( target_id, item);
            showMessage("\033[102m\033[30m  日程已标记为完成  \033[0m");
            menuB04();
        }
    }
}
void Console::menuC01(){
    clearScreen();
    std::string file_path;
    cout << "Enter file path to import: ";
    getline(cin, file_path);
    if (file_processor.importList(*agenda_ptr, file_path))
    {
        showMessage("\033[102m\033[30m  导入成功  \033[0m");
    }
    else
    {
        showMessage("\033[101m\033[30m  导入失败 \033[0m");
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
        showMessage("\033[102m\033[30m  保存成功  \033[0m");
    }
    else
    {
        showMessage("\033[101m\033[30m  无法保存 \033[0m");
    }
    menuA01();
}
void Console::menuH01() {
        clearScreen();
        
        // 顶部标题
        cout << "\033[1;36m\033[1;33m    日程管理系统     \033[1;36m\033[0m\n";

        // 简介部分
        cout << "\033[1;34m【系统介绍】\033[0m\n";
        cout << "\033[3;90m  本系统支持对日程信息进行新增、删除、查看、筛选等全方位管理操作。\033[0m\n\n";

        // A01 列表操作
        cout << "\033[1;92m【日程查看区 - 列表操作】\033[0m\033[1;32m(A01 LIST)\033[0m\n";
        cout << "  \033[1;33m[\033[1;36mA\033[1;33m] \033[0m:: 新增全部日程数据\n";
        cout << "  \033[1;33m[\033[1;36mS\033[1;33m] \033[0m:: 保存当前操作的日程\n";
        cout << "  \033[1;33m[\033[1;36mI\033[1;33m] \033[1;33m] \033[0m:: 导入外部日程数据\n";
        cout << "  \033[1;33m[\033[1;36mV\033[1;33m] \033[0m:: 查看/筛选日程数据\n";
        cout << "  \033[1;33m[\033[1;36mT\033[1;33m] \033[0m:: 统计日程完成情况\n";
        cout << "  \033[1;33m[\033[1;36mC\033[1;33m] \033[0m:: 清空所有日程\n";
        cout << "  \033[1;33m[\033[1;36mQ\033[1;33m] \033[0m:: 退出管理系统\n";
        cout << "  \033[1;33m[\033[1;36m数字键\033[1;33m] \033[0m:: 按编号查询日程数据\n";
        cout << "  \033[1;33m[\033[1;36mH\033[1;33m] \033[0m:: 查看系统帮助\n";
        cout << "  \033[1;33m[\033[1;31m0\033[1;33m] \033[0m:: 保存并返回主菜单\n\n";

        // A02 查看/编辑操作
        cout << "\033[1;92m【日程操作区 - 查看/编辑】\033[0m\033[1;32m(A02 VIEW/EDIT)\033[0m\n";
        cout << "  \033[1;33m[\033[1;36mR\033[1;33m] \033[0m:: 读取指定日程\n";
        cout << "  \033[1;33m[\033[1;36mE\033[1;33m] \033[0m:: 编辑指定日程\n";
        cout << "  \033[1;33m[\033[1;36mS\033[1;33m] \033[0m:: 保存编辑后的日程\n";
        cout << "  \033[1;33m[\033[1;36m0\033[1;33m] \033[0m:: 返回列表操作\n\n";

        // B01 编辑操作
        cout << "\033[1;92m【日程编辑页】\033[0m\033[1;32m(B01 EDITOR)\033[0m\n";
        cout << "  \033[1;33m[1] \033[0m:: 编辑日程名称\n";
        cout << "  \033[1;33m[2] \033[0m:: 编辑日程内容\n";
        cout << "  \033[1;33m[3] \033[0m:: 编辑截止日期 (DDL)\n";
        cout << "  \033[1;33m[4] \033[0m:: 编辑备注信息\n";
        cout << "  \033[1;33m[5] \033[0m:: 编辑优先级\n";
        cout << "  \033[1;33m[6] \033[0m:: 编辑状态值\n";
        cout << "  \033[1;33m[0] \033[0m:: 返回上一级菜单\n\n";

        // B02 筛选操作
        cout << "\033[1;92m【日程筛选页】\033[0m\033[1;32m(B02 FILTER)\033[0m\n";
        cout << "  \033[1;33m[1] \033[0m:: 按名称筛选\n";
        cout << "  \033[1;33m[2] \033[0m:: 按状态值筛选\n";
        cout << "  \033[1;33m[3] \033[0m:: 按截止日期筛选\n";
        cout << "  \033[1;33m[4] \033[0m:: 按优先级筛选\n";
        cout << "  \033[1;33m[5] \033[0m:: 清空筛选条件\n";
        cout << "  \033[1;33m[0] \033[0m:: 返回列表操作\n\n";

        // 优先级说明
        cout << "\033[1;34m【优先级说明】\033[0m\n";
        cout << "  \033[1;33m优先级标识: \033[0m";
        cout << "\033[101m\033[30m 1 紧急 \033[0m ";
        cout << "\033[103m\033[30m 2 优先 \033[0m ";
        cout << "\033[102m\033[30m 3 中等 \033[0m ";
        cout << "\033[106m\033[30m 4 一般 \033[0m\n";
        
        cout << "  \033[1;33m状态值: \033[0m";
        cout << "\033[106m\033[30m QUEUE 未完成 \033[0m ";
        cout << "\033[102m\033[30m COMPLETED 已完成 \033[0m ";
        cout << "\033[101m\033[30m OVERTIME 超时 \033[0m ";
        cout << "\033[103m\033[30m PAUSE 暂停 \033[0m\n\n";

        // 温馨提示
        cout << "\033[3;90m〖提示〗\033[0m\033[3;90m 操作前请确认系统状态，避免误操作导致数据丢失。\033[0m\n";
        cout << "\033[1;92m>> 请输入指令进行列表操作 <<\033[0m\n";
        
        cin.ignore(128, '\n'); // 修正 ignore 用法（避免缓冲区问题）
        menuA01();
}

void Console::processA01(const std::string &choice){
    if (choice == "A" || choice == "a")
    {
        menuB03();
    }
    else if (choice == "S" || choice == "s")
    {
        menuC02(0);
    }
    else if (choice == "I" || choice == "i")
    {
        menuC01();
    }
    else if (choice == "V" || choice == "v")
    {
        menuB02();
    }
    else if (choice == "T" || choice == "t")
    {
        int position;
        cout << "Enter position to insert the new item: ";
        cin >> position;
        cin.ignore(); // To ignore the newline character after integer input
        AgendaItem newItem = createItemFromInput();
        newItem.setId(position); // Temporary ID, will be set by Agenda
        agenda_ptr->insertItem(position-1, newItem);
        showMessage("\033[102m\033[30m  日程成功创建  \033[0m");
    }
    else if (choice == "C" || choice == "c")
    {
        agenda_ptr->clearAll();
        showMessage("\033[102m\033[30m  表单已格式化  \033[0m");
    }
    else if (choice == "H" || choice == "h")
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
    else if (choice == "Q" || choice == "q")
    {
        menuB04();
    }
    else
    {
        showMessage("\033[103m\033[30m  输入不合法 \033[0m");
    }
    
}
void Console::processA02(const std::string &choice){
    if (choice == "R" || choice == "r")
    {
        if (agenda_ptr->removeItem(selected_item_id))
        {
            showMessage("\033[102m\033[30m  日程已删除  \033[0m");
        }
        else
        {
            showMessage("\033[101m\033[30m  无法删除，请稍后重试 \033[0m");
        }
        menuA01();
    }
    else if (choice == "E" 
        || choice == "e")
    {
        menuB01();
    }
    else if (choice == "S" || choice == "s")
    {
        menuC02(1);
    }
    else if (choice == "0")
    {
        menuA01();
    }
    else
    {
        showMessage("\033[103m\033[30m  输入不合法 \033[0m");
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
            cout << "如图所示: " << std::endl;
            cout << "\033[106m\033[30m 0 未完成 \033[0m ";
            cout << "\033[102m\033[30m 1 完成 \033[0m ";
            cout << "\033[101m\033[30m 2 超时 \033[0m ";
            cout << "\033[103m\033[30m 3 暂停 \033[0m " << std::endl;
            cin >> newStatus;
            cin.ignore(); // To ignore the newline character after integer input
            item.setStatus(newStatus);
            agenda_ptr->updateItem(selected_item_id, item);
            break;}
    case 6:
        {
            int newPriority;
            cout << "如图所示: " << std::endl;
            cout << "\033[101m\033[30m 1 紧急 \033[0m ";
            cout << "\033[103m\033[30m 2 优先 \033[0m ";
            cout << "\033[102m\033[30m 3 中等 \033[0m ";
            cout << "\033[106m\033[30m 4 一般 \033[0m " << std::endl;
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
        showMessage("\033[102m\033[30m  筛选器已生效  \033[0m");
    }
    else if (choice == "2")
    {
        std::string priority_filter;
        cout << "Enter priority to filter by: ";
        getline(cin, priority_filter);
        agenda_ptr->applyFilter(1, priority_filter);
        showMessage("\033[102m\033[30m  筛选器已生效  \033[0m");
    }
    else if (choice == "3")
    {
        std::string ddl_filter;
        cout << "Enter DDL to filter by: ";
        getline(cin, ddl_filter);
        agenda_ptr->applyFilter(2, ddl_filter);
        showMessage("\033[102m\033[30m  筛选器已生效  \033[0m");
    }
    else if (choice == "4")
    {
        std::string status_filter;
        cout << "Enter status to filter by: ";
        getline(cin, status_filter);
        agenda_ptr->applyFilter(3, status_filter);
        showMessage("\033[102m\033[30m  筛选器已生效  \033[0m");
    }
    else if (choice == "5")
    {
        agenda_ptr->clearFilter();
        showMessage("\033[102m\033[30m  已清理筛选器  \033[0m");
    }
    else if (choice == "0")
    {
        menuA01();
        return;
    }
    else
    {
        showMessage("\033[103m\033[30m  输入不合法 \033[0m");
    }
    menuB02(); 
}
std::string Console::input(){
    std::string input_str;
    cout << "> ";
    getline(cin, input_str);
    if (input_str.empty())
    {
        printf("\033[103m\033[30m  输入为空 \033[0m");
        return "null";
    }
    
    return input_str;
}

AgendaItem Console::createItemFromInput(){
    string name, description, ddl, time;
    int priority;
    cout << "\033[103m\033[30m=====新建日程=====\033[0m" << std::endl;
    cout << "请输入日程名称: ";
    getline(cin, name);

    cout << "请输入日程描述: ";
    getline(cin, description);

    cout << "请输入日程截止时间 (DDL): ";
    getline(cin, ddl);

    cout << "请输入日程时间: ";
    getline(cin, time);

    cout << "请输入日程优先级，如图所示: " << std::endl;
    cout << "\033[101m\033[30m 1 紧急 \033[0m ";
    cout << "\033[103m\033[30m 2 优先 \033[0m ";
    cout << "\033[102m\033[30m 3 中等 \033[0m ";
    cout << "\033[106m\033[30m 4 一般 \033[0m " << std::endl;
    cin >> priority;

    AgendaItem newItem(name, description, ddl, time, priority);
    return newItem;
}
