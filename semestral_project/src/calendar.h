#ifndef __CALENDAR__
#define __CALENDAR__
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
#include "datetime.h"
#include "event.h"
using namespace std;
//--------------------------
//!Class Account
/*!
Class is specified to store the information about the account. Information about the account\n
are created when the constructor of this object is called. Class handles the information about: name\n
surname and nickname of the user. This class is the parent of the Calendar class and contains virtual destructor.
*/
class Account {
public:
    //!Default constructor
    /*!Reads value of name, surname and nickname.
      \param Name - a string value of name.
      \param Surname - a string value of surname.
      \param Nickname - a string value of nickname.
    */
    Account ( string Name, string Surname, string Nickname );
    //!Virtual destructor
    /*!Destructs the Account object and derived Calendar object
    */
    virtual ~Account () = default;
    //!Method getName
    /*!A normal member which returns a string value of the m_Name.
      \return a string value.
    */
    string getName () const;
    //!Method getSurname
    /*!A normal member which returns a string value of the m_Surname.
      \return a string value.
    */
    string getSurname () const;
    //!Method getName
    /*!A normal member which returns a string value of the m_Nickname.
      \return a string value.
    */
    string getNickname () const;
protected:
    string m_Name;
    string m_Surname;
    string m_Nickname;
};
//!Class Calendar
/*!
Main class for handling the operations over the accounts. This class is mainly working with\n
the Event and Event_R objects and operations within them. Handling focuses on adding, removing, sharing,\n
unsharing etc.. Class also handles sending the information about healthy life and daily routines\n
to the user. This system is a little bit selfish beceause the times are fixed and it is not up to\n
you to to change but to strictly follow them.\n\n
There is also the option to export all of the events to .ics format which is the universal format for\n
handling calendars in many calendar applications including Google calendars and Yahoo calendars.\n\n
Note: This class is the child of the class Account and is calling Account's constructor.
*/
class Calendar : public Account {
public:
    //!Default constructor
    /*!Object is calling the constructor from the class Account.
      \param Name - a string value of name.
      \param Surname - a string value of surname.
      \param Nickname - a string value of nickname.
    */
    Calendar ( string Name, string Surname, string Nickname );
    //!Default destructor
    /*!Destructs the Calendar object.
    */
    ~Calendar ();
    //!Overloaded operator ==
    /*!Handles comparison between two Calendar objects.
      \param src - a Calendar object we are comparing with.
      \return true if this == src else false.
    */
    bool operator == ( const Calendar & src ) const;
    //!Method addEvent
    /*!This method recieves the whole Event object as the input parameter. It has to be\n
      guaranteed that the UID of the Event is unique else the method returns 0 value.\n
      Every event type has different adding process:\n
      ####From-To event
      Method checks whether the UID is unique and the information are valid and adds the\n
      event to the database.
      ####Repeating event
      Same as From-To event. Event is recurring and literally there are "no limits". In fact\n
      the system has some limitations for every type of the cycle. The system will add:\n
      -> daily - 365 events\n
      -> weekly - 105 events\n
      -> monthly - 60 events\n
      -> yearly - 60 events\n
      ####Repeating until event
      The process of adding is simillar to the Repeating event but there is the limitation.\n
      System is also strict beceause there is not an option to cross the recurrence limits\n
      as they are described above in the Repeating event.\n
      \param Ev - a shared_ptr<Event> object.
      \return - a size_t value of error or UID (why: UID will be changed when adding the recurrent events).
    */
    size_t addEvent ( shared_ptr<Event> Ev );
    //!Method removeEvent
    /*!Checks whether the event exists by the UID and then removes it from the database.\n
      For the recurrent events all of the instances will be removed. Method uses rUID to\n
      workout which events are the instances of the given event.
      \param UID - a size_t value of the UID.
      \return true if the event has been removed else false.
    */
    bool removeEvent ( size_t UID );
    //!Method moveEvent
    /*!Method moves the event with the given UID and set it's start and end date to the\n
      given values. For the recurrent events all of the instances will be moved.
      \param UID - a size_t value of the UID.
      \param From - a Date_Time objects of the event start.
      \param To - a Date_Time objects of the event end.
      \return 0 if event was not found, 1 if event is not moveable, 2 if the moving event is overloaded and 3 if the event has been moved.
    */
    int moveEvent ( size_t UID, Date_Time From, Date_Time To );
    //!Method freeDate
    /*!Searches trough the whole event list for the next free time from the given Date_Time.\n
      Method recieves two types of tasks: hour, day. For hour it will find next free hour from\n
      the given Date_Time and for the day it will find next free day.
      \param From - a Date_Time object.
      \param Task - a string value.
      \return a Date_Time object of the next free datetime.
    */
    Date_Time freeDate ( Date_Time From, string Task ) const;
    //!Method shareEvent
    /*!Checks whether the event with the given UID exists and shares it with the nickname.\n
      Nickname is added to the events's m_SharedWith vector of accounts. If the user is\n
      already sharing this event with the nickname it will return value 1.
      \sa unshareEvent()
      \param UID - a size_t value of the UID.
      \param Nickname - a string value of the nickname.
      \return 0 if the event was not found, 1 if the event is already shared with given Nickname and 2 if the event has been shared.
    */
    int shareEvent ( size_t UID, string Nickname );
    //!Method unshareEvent
    /*!Checks whether the event with the given UID exists and unshares it from the nickname.\n
      Nickname is removed from the events's m_SharedWith vector of accounts. If the user is\n
      not sharing this event with the nickname it will return value 1.
      \sa shareEvent()
      \param UID - a size_t value of the UID.
      \param Nickname - a string value of the nickname.
      \return 0 if the event was not found, 1 if the event is already shared with given Nickname and 2 if the event has been shared.
    */
    int unshareEvent ( size_t UID, string Nickname );
    //!Method isEmpty
    /*!Checks if there is at least one event in the events list.
      \return true if the list is empty else false.
    */
    bool isEmpty () const;
    //!Method getEvent
    /*!A normal member which returns a shared_ptr<Event> object of the given UID.
      \return a shared_ptr<Event> object.
    */
    shared_ptr<Event> getEvent ( size_t UID ) const;
    //!Method printEvent
    /*!A normal member which prints the information about the event of the given UID.
      \return false if the event was not found else true.
    */
    bool printEvent ( size_t UID );
    //!Method printAll
    /*!A normal member which prints the information about all of the events.
    */
    void printAll () const;
    //!Method evExists
    /*!A normal member which checks whether the event exists with the given UID.
      \return true if the event exists else false.
    */
    bool evExists ( size_t UID ) const;
    //!Method setSummary
    /*!A normal member which sets the summary of the event by the given UID.
      \param UID - a size_t value.
      \param Summary - a string value of the new summary.
      \return false if the event was not found else true.
    */
    bool setSummary ( size_t UID, string Summary );
    //!Method setClass
    /*!A normal member which sets the class of the event by the given UID.
      \param UID - a size_t value.
      \param Class - a string value of the new class.
      \return false if the event was not found else true.
    */
    bool setClass ( size_t UID, string Class );
    //!Method setSummary
    /*!A normal member which sets the categories of the event by the given UID.
      \param UID - a size_t value.
      \param Categories - a vector of the new categories.
      \return false if the event was not found else true.
    */
    bool setCategories ( size_t UID, vector<string> Categories );
    //!Method setDuty
    /*!A normal member which sets the mandatory of the event by the given UID.
      \param UID - a size_t value.
      \param Duty - a bool value of the new mandatory.
      \return false if the event was not found else true.
    */
    bool setDuty ( size_t UID, bool Duty );
    //!Method setMoveable
    /*!A normal member which sets the moveability of the event by the given UID.
      \param UID - a size_t value.
      \param Moveable - a bool value of the new moveability.
      \return false if the event was not found else true.
    */
    bool setMoveable ( size_t UID, bool Moveable );
    //!Method setLimit
    /*!A normal member which sets the moving limit of the event by the given UID.
      \param UID - a size_t value.
      \param Limit - an integer value of the new moving limit.
      \return false if the event was not found else true.
    */
    bool setLimit ( size_t UID, int Limit );
    //!Method hl_status
    /*!Part of the healthy life manager. Turns on or off the healthy manager by the given status.
      \param status - a bool value of status.
      \sa hl_statusGet(), hl_Stats() and hl_eventSum().
    */
    void hl_status ( bool status );
    //!Method hl_statusGet
    /*!Part of the healthy life manager. Returns whether the manager is turned on or off.
      \return a bool value of the manager status.
      \sa hl_status, hl_Stats() and hl_eventSum().
    */
    bool hl_statusGet () const;
    //!Method hl_Stats
    /*!Part of the healthy life manager. Prints out the information about your healthy life\n
      statistics. Mainly it will count the events during the breakfast time, snack time, lunch time\n
      and dinner time. Method will then tell you if you are living healthy life or if you should\n
      consider removing some of your events during the meal times.\n\n 
      Note: The system is educateable so the times are fixed beceause they are part of the scientific research and they are ideal for everyone.
    */
    void hl_Stats () const;
    //!Method Export
    /*!Method takes all of the events, format them and export to the .ics format file which will be\n
      stored in the current folder. This format is the part of the iCalendar project.
    */
    void Export () const;
    //!Method getSummary
    /*!A normal member which returns a string value of the m_Summary of the given event by the UID.
      \param UID - a size_t value.
      \return a string value.
    */
    string getSummary ( size_t UID ) const;
    //!Method getClass
    /*!A normal member which returns a string value of the m_Class of the given event by the UID.
      \param UID - a size_t value.
      \return a string value.
    */
    string getClass ( size_t UID ) const;
    //!Method getCategories
    /*!A normal member which returns a vector of the m_Categories of the given event by the UID.
      \param UID - a size_t value.
      \return a vector.
    */
    vector<string> getCategories ( size_t UID ) const;
    //!Method getDuty
    /*!A normal member which returns a bool value of the m_Duty of the given event by the UID.
      \param UID - a size_t value.
      \return a bool value.
    */
    bool getDuty ( size_t UID ) const;
    //!Method getMoveable
    /*!A normal member which returns a bool value of the m_Moveable of the given event by the UID.
      \param UID - a size_t value.
      \return a bool value.
    */
    bool getMoveable ( size_t UID ) const;
    //!Method getLimit
    /*!A normal member which returns an integer value of the m_limit of the given event by the UID.
      \param UID - a size_t value.
      \return an integer value.
    */
    int getLimit ( size_t UID ) const;
    //!Method getType
    /*!A normal member which returns an integer value of the m_Type of the given event by the UID.
      \param UID - a size_t value.
      \return an integer value.
    */
    int getType ( size_t UID ) const;
protected:
    //!Method hl_eventSum
    /*!Part of the healthy life manager. Helper method which counts the number of the events\n
      during the given type of the meal time [breakfast, snack, lunch, dinner].
      \param type - a string value of the meal time type.
      \return -1 if the manager is not turned on, -2 if wrong type of the meal time was given else returns number of the events.
    */
    int hl_eventSum ( string type ) const;
    //!Struct Hasher
    /*!This structure handles the hashing of the m_Eventlist which is unordered_set.
    */
    struct Hasher {
        //!Overloaded operator ()
        /*!Hashes the shared_ptr<Event> objects by its UID which is unique for every object.
          \param src - a shared_ptr<Event> object.
          \return - a size_t value of the hash.
        */
        size_t operator() ( const shared_ptr<Event> & src ) const {
            return ( hash<int>()( src->UID() ) );
        }
    };
    unordered_set<shared_ptr<Event>, Hasher> m_Eventlist;
    //--------------------------
    bool hlm_Status;
    Time hlm_BreakfastF = Time ( 45, 7 );
    Time hlm_BreakfastT = Time ( 0, 8 );
    Time hlm_SnackF = Time ( 0, 10 );
    Time hlm_SnackT = Time ( 15, 10 );
    Time hlm_LunchF = Time ( 0, 12 );
    Time hlm_LunchT = Time ( 30, 12 );
    Time hlm_DinnerF = Time ( 0, 17 );
    Time hlm_DinnerT = Time ( 0, 18 );
};
//!Class Database
/*!
This database is handling all of the accounts which have been created. Database has methods\n
to add new account and check wheter the account exists. All of the members are public to ease\n
the working with this database by direct access to it's content. Database is handling the working\n
with the global UID types which are necessary for the keeping the data consistent.
*/
class Database {
public:
    //!Default constructor
    /*!Object does not recieve any values.
    */
    Database ();
    //!Default destructor
    /*!Destructs the Database object.
    */
    ~Database ();
    //!Method addAccount
    /*!Adds new account to the database and checks whether there is not any other account\n
      with the same nickname.
      \param Name - a string value of the name.
      \param Surname - a string value of the surname.
      \param Nickname - a string value of the nickname.
      \return true if the account has been added else returns false beceause the account with the same nickname already exists.
    */
    bool addAccount ( string Name, string Surname, string Nickname );
    //!Method accExists
    /*!Checks whether the account with the given nickname exists in the database.
      \param Nickname - a string value of the nickname.
      \return true if the account exists else returns false.
    */
    bool accExists ( string Nickname ) const;
    vector<Calendar> m_Accountlist;
    size_t globalUID;
    size_t rUID;
};
//--------------------------
#endif
