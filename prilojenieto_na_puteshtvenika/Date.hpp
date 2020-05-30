#ifndef DATE_H
#define DATE_H

class Date {
public:
    int year;
    int month;
    int day;

    Date();
    Date(int, int, int);

    bool isLeap();
    static Date getCurrentDate();
};

std::ostream& operator<<(std::ostream&, const Date&);
std::istream& operator>>(std::istream&, Date&);

bool operator== (Date const&, Date const&);
bool operator!= (Date const&, Date const&);
bool operator> (Date const&, Date const&);
bool operator< (Date const&, Date const&);
bool operator>= (Date const&, Date const&);
bool operator<= (Date const&, Date const&);

#endif
