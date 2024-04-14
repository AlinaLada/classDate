#include <iostream>
#include <cmath>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        if (!isValid()) {
            cerr << "Invalid date! Set to default (01/01/2000)." << endl;
            day = 1;
            month = 1;
            year = 2000;
        }
    }

    friend istream& operator>>(istream& in, Date& date);
    friend ostream& operator<<(ostream& out, const Date& date);

    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const;
    bool operator<=(const Date& rhs) const;
    bool operator>=(const Date& rhs) const;

    Date& operator=(const Date& rhs);

    Date operator++();    
    Date operator--();    

    int operator-(const Date& rhs) const;

    bool isValid() const;
    int daysInMonth(int m, int y) const;
};


istream& operator>>(istream& in, Date& date) {
    in >> date.day >> date.month >> date.year;
    if (!date.isValid()) {
        cerr << "Invalid date! Set to default (01/01/2000)." << endl;
        date.day = 1;
        date.month = 1;
        date.year = 2000;
    }
    return in;
}

ostream& operator<<(ostream& out, const Date& date) {
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}

bool Date::operator==(const Date& rhs) const {
    return day == rhs.day && month == rhs.month && year == rhs.year;
}

bool Date::operator!=(const Date& rhs) const {
    return !(*this == rhs);
}

bool Date::operator<(const Date& rhs) const {
    if (year != rhs.year) return year < rhs.year;
    if (month != rhs.month) return month < rhs.month;
    return day < rhs.day;
}

bool Date::operator>(const Date& rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date& rhs) const {
    return !(rhs < *this);
}

bool Date::operator>=(const Date& rhs) const {
    return !(*this < rhs);
}

Date& Date::operator=(const Date& rhs) {
    if (this != &rhs) {
        day = rhs.day;
        month = rhs.month;
        year = rhs.year;
    }
    return *this;
}

Date Date::operator++() {
    day++;
    if (day > daysInMonth(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return *this;
}

Date Date::operator--() {
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = daysInMonth(month, year);
    }
    return *this;
}

int Date::operator-(const Date& rhs) const {
    int days = 0;
    Date temp = *this;

    if (temp < rhs) {
        while (temp != rhs) {
            days++;
            ++temp;
        }
    }
    else {
        while (temp != rhs) {
            days--;
            --temp;
        }
    }
    return days;
}

bool Date::isValid() const {
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year)) {
        return false;
    }
    return true;
}

int Date::daysInMonth(int m, int y) const {
    switch (m) {
    case 2:
        return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

int main() {
    Date d1, d2;
    cout << "Enter a date 1 (dd mm yyyy): ";
    cin >> d1;

    cout << "Enter a date 2 (dd mm yyyy): ";
    cin >> d2;

    cout << "Date 1: " << d1 << endl;
    cout << "Date 2: " << d2 << endl;

    cout << "Difference between dates: " << (d2 - d1) << " days" << endl;

    ++d1;
    cout << "Date 1 after increment: " << d1 << endl;

    --d2;
    cout << "Date 2 after decrement: " << d2 << endl;

    return 0;
}