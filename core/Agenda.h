
#pragma once

#include"AgendaItem.h"
#include <vector>
#include <string>

enum SortMethod{
    BY_ID = 0,
    BY_PRIORITY = 1,
    BY_DDL = 2,
    BY_STATUS = 3,
    BY_NAME = 4
};

class Agenda {
    public:
        Agenda();
        ~Agenda() = default;

        int addItem(const AgendaItem& item);
        bool removeItem(int target_id);
        bool updateItem(int target_id, const AgendaItem& new_item);
        void insertItem(int position, const AgendaItem& item);
        AgendaItem getItem(int target_id) const;
        void sortItems(int sort_code);
        void applyFilter(int filter_code , std::string filter_value = "");
        void clearFilter();
        void displayList(int begin = 0 , int end = -1) const;
        void refreshAllIds();
        void clearAll();
        int getItemCount() const;
        int getFilteredCount() const;
        bool isDirty() const;
        void markClean();
        std::vector<int> filtered_indices;

    private:
        std::vector<AgendaItem> items;
        int next_id;
        bool is_dirty;
        SortMethod current_sort;
};
