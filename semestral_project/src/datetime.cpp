#include "datetime.h"
using namespace std;
//--------------------------
Date_Time::Date_Time ( int Min, int Hour, int Day, int Month, int Year )
: Time ( Min, Hour ) { 
    m_Day = Day;
    m_Month = Month;
    m_Year = Year;
}
//--------------------------
Date_Time::~Date_Time () {}
//--------------------------
Date_Time & Date_Time::operator = ( const Date_Time & src ) {
    if ( &src == this ) return (*this);
    m_Min = src.m_Min;
    m_Hour = src.m_Hour;
    m_Day = src.m_Day;
    m_Month = src.m_Month;
    m_Year = src.m_Year;
    return (*this);
}
//--------------------------
bool Date_Time::operator > ( const Date_Time & src ) const {

    if ( this->m_Year > src.m_Year ) {
        return true;
    }
    else if ( this->m_Year == src.m_Year ) {
        if ( this->m_Month > src.m_Month ) {
            return true;
        }
        else if ( this->m_Month == src.m_Month ) {
            if ( this->m_Day > src.m_Day ) {
                return true;
            }
            else if ( this->m_Day == src.m_Day ) {
                if ( this->m_Hour > src.m_Hour ) {
                    return true;
                }
                else if ( this->m_Hour == src.m_Hour ) {
                    if ( this->m_Min > src.m_Min ) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
//--------------------------
bool Date_Time::operator < ( const Date_Time & src ) const {

    if ( this->m_Year < src.m_Year ) {
        return true;
    }
    else if ( this->m_Year == src.m_Year ) {
        if ( this->m_Month < src.m_Month ) {
            return true;
        }
        else if ( this->m_Month == src.m_Month ) {
            if ( this->m_Day < src.m_Day ) {
                return true;
            }
            else if ( this->m_Day == src.m_Day ) { 
                if ( this->m_Hour < src.m_Hour ) {
                    return true;
                }
                else if ( this->m_Hour == src.m_Hour ) {
                    if ( this->m_Min < src.m_Min ) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
//--------------------------
bool Date_Time::operator == ( const Date_Time & src ) const {

    if ( ( this->m_Year == src.m_Year ) && ( this->m_Month == src.m_Month ) &&
         ( this->m_Day == src.m_Day ) )
        return true;
    return false;
}
//--------------------------
int Date_Time::day () const { return m_Day; }
int Date_Time::month () const { return m_Month; }
int Date_Time::year () const { return m_Year; }
//--------------------------
void Date_Time::setDay ( int day ) { m_Day = day; }
void Date_Time::setMonth ( int month ) { m_Month = month; }
void Date_Time::setYear ( int year ) { m_Year = year; }
//--------------------------
bool Date_Time::validateDate () const {
    int days = DaysOfMonth ( m_Month, m_Year );

    if ( days == 0 || m_Day <= 0 )
        return false;
    else if ( m_Day > days )
        return false;
    if ( m_Year > 2100 || m_Year < 1970 )
        return false;
    return true;
}
//--------------------------
int Date_Time::LeapYear ( int y ) const {
    if (((y % 4)==0) && ((y % 100)!=0 || (y % 400)==0)) {
        if (y>=4000) {  
            if ((y%4000)==0)
                return 0;
            else
                return 1;
        }
        else
            return 1;
    }
    else
        return 0;
}
//--------------------------
int Date_Time::DaysOfMonth ( int m, int y ) const {
    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return 28 + LeapYear(y);
    }
    return 0;
}
//--------------------------
