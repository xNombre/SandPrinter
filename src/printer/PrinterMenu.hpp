#pragma once

#include <list>

#include <plotter/HeadController.hpp>

class PrinterMenu {
public:
    PrinterMenu() = default;
    ~PrinterMenu() = default;

    void enter_menu();

    enum class Entry {
        PRINT,
        AUTOPOS,
        MANUAL_POS,

        DONOTUSE_LAST_ENTRY
    };
    

private:
    Entry get_option_for_user();
};

inline PrinterMenu::Entry& operator++(PrinterMenu::Entry& entry, int)
{
    const auto next_entry_value = (int(entry) + 1) % int(PrinterMenu::Entry::DONOTUSE_LAST_ENTRY);
    entry = PrinterMenu::Entry(next_entry_value);
    
    return entry;
}

inline PrinterMenu::Entry& operator--(PrinterMenu::Entry &entry, int)
{
    auto prev_entry_value = int(entry);
    if (prev_entry_value == 0)
        prev_entry_value = int(PrinterMenu::Entry::DONOTUSE_LAST_ENTRY) - 1;
    else
        prev_entry_value -= 1;
    
    entry = PrinterMenu::Entry(prev_entry_value);

    return entry;
}

inline PrinterMenu::Entry operator+(PrinterMenu::Entry lhs, int rhs)
{
    auto val = int(lhs) + rhs;
    lhs = PrinterMenu::Entry(val);

    return lhs;
}
