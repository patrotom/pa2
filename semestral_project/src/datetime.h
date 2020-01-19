#ifndef __DATETIME__
#define __DATETIME__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <memory>
using namespace std;
//--------------------------
//! Class Time
/*!
Handles custom time format including hours and minutes. Class has methods which\n
read the time format and decide whether it is valid or invalid. This class is\n
working with standard time format in integer values:\n 
#####-> hour - {0..23}
#####-> minute - {0..59} 
However this class is not working with local time so the values have to be set manually.\n
This class is the parent of the class Date_Time.
*/
class Time {
public:
    //!Default constructor
    /*!Reads value of minute and hour.
      \param Min - an integer value of minute.
      \param Hour - an integer value of hour.
    */
    Time ( int Min, int Hour );
    //!Default destructor
    /*!Destructs the Time object.
    */
    virtual ~Time ();
    //!Overloaded operator =
    /*!Handles a deep copy of the Time object.
      \param src - a Time object we are copying from.
      \return Time object
    */
    Time & operator = ( const Time & src );
    //!Overloaded operator >
    /*!Handles comparison between two Time objects.
      \param src - a Time object we are comparing with.
      \return true if this > src else returns false.
    */
    bool operator > ( const Time & src ) const;
    //!Overloaded operator <
    /*!Handles comparison between two Time objects.
      \param src - a Time object we are comparing with.
      \return true if this < src else returns false.
    */
    bool operator < ( const Time & src ) const;
    //!Overloaded operator <=
    /*!Handles comparison between two Time objects.
      \param src - a Time object we are comparing with.
      \return true if this <= src else returns false.
    */
    bool operator <= ( const Time & src ) const;
    //!Overloaded operator >=
    /*!Handles comparison between two Time objects.
      \param src - a Time object we are comparing with.
      \return true if this >= src else returns false.
    */
    bool operator >= ( const Time & src ) const;
    //!Overloaded operator ==
    /*!Handles comparison between two Time objects.
      \param src - a Time object we are comparing with.
      \return true if this == src else false.
    */
    bool operator == ( const Time & src ) const;
    //!Virtual method min
    /*!A normal member which returns an integer value of a minute.
      \return an integer value of the member m_Min.
    */
    virtual int min () const;
    //!Virtual method hour
    /*!A normal member which returns an integer value of an hour.
      \return an integer value of the member m_Hour.
    */
    virtual int hour () const;
    //!Virtual method setMin
    /*!A normal member which sets a minute from the input integer value.
      \param min - an integer value which will be set as the new value of m_Min.
    */
    virtual void setMin ( int min );
    //!Virtual method setHour
    /*!A normal member which sets an hour from the input integer value.
      \param hour - an integer value which will be set as the new value of m_Hour.
    */
    virtual void setHour ( int hour );
    //!Virtual method validateTime
    /*!Validates the current values of m_Min and m_Hour respecting the standard time format.
      \return true if m_Hour is in {0..23} interval and m_Min is in {0..59} interval else returns false.
    */
    virtual bool validateTime () const;
protected:
    int m_Min;
    int m_Hour;
};
//! Class Date_Time
/*!
Handles custom datetime format including years, months, days, hours and minutes.\n
Class has methods which read the datetime format and decide whether it is valid or invalid.\n
This class is working with standard Gregorian calendar in integer values:\n 
#####-> hour - {0..23}
#####-> minute - {0..59}
#####-> day - {1..31}
#####-> month - {1..12}
#####-> year - {1970..2100}
This class is also capable of detecting invalid dates in leap years however it does not work\n
with local date and time so these values have to be set manually.\n
This class is the child of the class Time and inherits some of the methods and members from it.
*/
class Date_Time : public Time {
public:
    //!Default constructor
    /*!Reads value of minute, hour, day, month and year.
      \param Min - an integer value of minute.
      \param Hour - an integer value of hour.
      \param Day - an integer value of day.
      \param Month - an integer value of month.
      \param Year - an integer value of year.
    */
    Date_Time ( int Min, int Hour, int Day, int Month, int Year );
    //!Default destructor
    /*!Destructs the Date_Time object.
    */
    ~Date_Time ();
    //!Overloaded operator =
    /*!Handles a deep copy of the Date_Time object.
      \param src - a Date_Time object we are copying from.
      \return Date_Time object
    */
    Date_Time & operator = ( const Date_Time & src );
    //!Overloaded operator >
    /*!Handles comparison between two Date_Time objects.
      \param src - a Date_Time object we are comparing with.
      \return true if this > src else returns false.
    */
    bool operator > ( const Date_Time & src ) const;
    //!Overloaded operator <
    /*!Handles comparison between two Date_Time objects.
      \param src - a Date_Time object we are comparing with.
      \return true if this < src else returns false.
    */
    bool operator < ( const Date_Time & src ) const;
    //!Overloaded operator ==
    /*!Handles comparison between two Date_Time objects.
      \param src - a Date_Time object we are comparing with.
      \return true if this == src else false.
    */
    bool operator == ( const Date_Time & src ) const;
    //!Method day
    /*!A normal member which returns an integer value of a day.
      \return an integer value of the member m_Day.
    */ 
    int day () const;
    //!Method month
    /*!A normal member which returns an integer value of a month.
      \return an integer value of the member m_Month.
    */ 
    int month () const;
    //!Method year
    /*!A normal member which returns an integer value of a year.
      \return an integer value of the member m_Year;
    */ 
    int year () const;
    //!Method setDay
    /*!A normal member which sets a day from the input integer value.
      \param day - an integer value which will be set as the new value of m_Day.
    */
    void setDay ( int day );
    //!Method setMonth
    /*!A normal member which sets a month from the input integer value.
      \param month - an integer value which will be set as the new value of m_Month.
    */
    void setMonth ( int month );
    //!Method setYear
    /*!A normal member which sets a year from the input integer value.
      \param year - an integer value which will be set as the new value of m_Year.
    */
    void setYear ( int year );
    //!Method validateDate
    /*!Validate the current values combination of m_Day, m_Month and m_Year respecting the Gregorian calendar.
     \return true if the date is valid part of Gregorian calendar and year is in {1970..2100} interval else returns false.
    */
    bool validateDate () const;
    //!Method LeapYear
    /*!Checks the given year and calculates if it is leap or not and returns extra day if the\n
       the year is leap beceause of the handling of 29./28. February.
      \param y - an integer value of the year.
      \return 1 if the year is leap and 0 if not.
    */
    int LeapYear ( int y ) const;
protected:
    int m_Day;
    int m_Month;
    int m_Year; 
    //!Method DaysOfMonth
    /*!Calculates the number of the days in the given month and year.
      \param m - an integer value of the month.
      \param y - an integer value of the year.
      \return number of the days in the given month and year.
    */
    int DaysOfMonth ( int m, int y ) const;
};
//--------------------------
#endif
