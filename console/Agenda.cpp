#include "Agenda.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <sstream>

Agenda::Agenda(){
    next_id = 1;
    is_dirty = false;
}

void Agenda::refreshAllIds(){
    if (is_dirty == true)
    {
        int id_counter = 1;
        for (auto& i : items)
        {
            i.setId(id_counter++);
        }    
        is_dirty = false;
    }
    else{
        return;
    }
}


int Agenda::addItem(const AgendaItem& item) {
    AgendaItem new_item = item;
    // for (auto i: items)
    // {
    //     if (i.getName() == new_item.getName() && i.getDDL() == new_item.getDDL() && i.getTime() == new_item.getTime()) {
    //         std::cerr << "Duplicate item detected. Item not added." << std::endl;
    //         return -1; 
    //     }
    // }
    new_item.setId(next_id++);
    items.push_back(new_item);
    return new_item.getId();
}

bool Agenda::removeItem(int target_id){
    try
    {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == target_id) {
                items.erase(it);
                next_id--;
                is_dirty = true;
                refreshAllIds();
                return true;
            }
            else if (target_id < 0 || target_id >= next_id) {
                throw std::out_of_range("Invalid ID: " + std::to_string(target_id));
            }
        }        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    refreshAllIds();
    return false;
}

bool Agenda::updateItem(int target_id, const AgendaItem& new_item) {
    try
    {
        // for (auto i : items)
        // {
        //     if(i.getName() == new_item.getName() && i.getDDL() == new_item.getDDL() && i.getTime() == new_item.getTime()){
        //         std::cerr << "Duplicate item detected. Update not performed." << std::endl;
        //         return false; 
        //     }
        // }
        for (auto& item : items) {
            if (item.getId() == target_id) {
                item = new_item;
                item.setId(target_id); // Ensure the ID remains the same
                is_dirty = true;
                refreshAllIds();
                return true;
            }
        }
        throw std::out_of_range("Invalid ID: " + std::to_string(target_id));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    refreshAllIds();
    return false;
}

void Agenda::insertItem(int position, const AgendaItem &item){
    try
    {
        if (position < 0 || position > items.size()) {
            throw std::out_of_range("Invalid position: " + std::to_string(position));
        }
        AgendaItem new_item = item;
        // for (auto i : items)
        // {
        //     if(i.getName() == new_item.getName() && i.getDDL() == new_item.getDDL() && i.getTime() == new_item.getTime()){
        //         throw std::runtime_error("Duplicate item detected. Update not performed.");
        //     }
        // }
        new_item.setId(next_id++);
        items.insert(items.begin() + position, new_item);
        is_dirty = true;
        refreshAllIds();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    refreshAllIds();
}

AgendaItem Agenda::getItem(int target_id) const {
    for (const auto& item : items) {
        if (item.getId() == target_id) {
            return item;
        }
    }
    if (target_id < 0 || target_id >= next_id) {
        AgendaItem invalid_item;
        invalid_item.setId(-1);
    }
    return AgendaItem(); 
}

void Agenda::sortItems(int sort_code) {
    current_sort = static_cast<SortMethod>(sort_code);
    switch (current_sort) {
        case BY_ID:
            std::sort(items.begin(), items.end(), [](const AgendaItem& a, const AgendaItem& b) {
                return a.getId() < b.getId();
            });
            break;
        case BY_PRIORITY:
            std::sort(items.begin(), items.end(), [](const AgendaItem& a, const AgendaItem& b) {
                return a.getPriority() < b.getPriority();
            });
            break;
        case BY_DDL:
            std::sort(items.begin(), items.end(), [](const AgendaItem& a, const AgendaItem& b) {
                return a.getDDL() < b.getDDL();
            });
            break;
        case BY_STATUS:
            std::sort(items.begin(), items.end(), [](const AgendaItem& a, const AgendaItem& b) {
                return a.getStatus() < b.getStatus();
            });
            break;
        case BY_NAME:
            std::sort(items.begin(), items.end(), [](const AgendaItem& a, const AgendaItem& b) {
                return a.getName() < b.getName();
            });
            break;
        default:
            break;
    }
    is_dirty = true;
    refreshAllIds();
}

void Agenda::applyFilter(int filter_code, std::string filter_value) {
    SortMethod filter_method = static_cast<SortMethod>(filter_code);
    filtered_indices.clear();
    switch (filter_method)
    {
    case BY_STATUS:
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].getStatus() == std::stoi(filter_value)) {
                filtered_indices.push_back(i);
            }
        }
        break;
    case BY_PRIORITY:
        for (size_t i = 0; i < items.size(); ++i) {
            if (std::to_string(items[i].getPriority()) == filter_value) {
                filtered_indices.push_back(i);
            }
        }
        break;
    default:
        break;
    }
}

void Agenda::clearFilter() {
    filtered_indices.clear();
}

void Agenda::displayList(int begin, int end) const {
    std::cout << std::endl;
    if (!items.size()) {
        std::cout << "  [ÔÝÎÞÊý¾Ý NO DATA]  " << std::endl;
        return;
    }
    if (!filtered_indices.empty()) {
        std::cout << "\033[3m\033[2m  [FILTERED]  \033[0m" << std::endl;
        int display_end = (end == -1 || end >= filtered_indices.size()) ? filtered_indices.size() : end + 1;
        for (int i = begin; i < display_end; ++i) {
            std::cout << "#";
            items[filtered_indices[i]].displayBrief();
        }
    } else {
        int display_end = (end == -1 || end >= items.size()) ? items.size() : end + 1;
        for (int i = begin; i < display_end; ++i) {
            std::cout << "|";
            items[i].displayBrief();
        }
    }
}

void Agenda::clearAll() {
    items.clear();
    next_id = 1;
    is_dirty = false;
    filtered_indices.clear();
}

int Agenda::getItemCount() const {
    return items.size();
}

int Agenda::getFilteredCount() const {
    return filtered_indices.size();
}

bool Agenda::isDirty() const {
    return is_dirty;
}  

void Agenda::markClean() {
    is_dirty = false;
}
