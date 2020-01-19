#ifndef __EVENT__
#define __EVENT__
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
using namespace std;
//--------------------------
//!Class Event
/*!
Main class for the handling of the events of the calendar. Class is working with the basic\n
From-To events. Other types of the events are included in the derived class Event_R.
Class is handling:\n
###From-To events:
Basic type of the event which is identified by the UID. Event contains start date and end date.\n
Every event has event class which can be: public, private or shared. These classes tell\n
the user about the nature of the event. You can also set up the summary and some logical categories\n
for every event so the event can tell more about itself. Every event is set as mandatory or not\n
mandatory and as moveable or not moveable. There is also an option to limit the number of moves of the event.\n
*/
class Event {
public: 
    //!Default constructor
    /*!This constructor is for the From-To event type.
      \param UID - a size_t value of the UID.
      \param From - a Date_Time object of the event start.
      \param To - a Date_Time object of the event end.
      \param Summary - a string value of the summary.
      \param Class - a string value of the class.
      \param Categories - a vector of the categories.
      \param Duty - a bool value telling about the mandatory.
      \param Moveable - a bool value telling about the moveability.
      \param Limit - an integer value of the moving limit.
    */
    Event ( size_t UID, Date_Time From, Date_Time To, string Summary, 
            string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit );
    //!Virtual destructor
    /*!Destructs the Event object and derived Event_R object.
    */
    virtual ~Event ();
    //!Virtual overloaded operator ==
    /*!Handles comparison between two Event objects.
      \param src - an Event object we are comparing with.
      \return true if this == src else false.
    */
    virtual bool operator == ( shared_ptr<Event> src ) const;
    //!Method getFrom
    /*!A normal member which returns a Date_Time object of the event start.
      \return a Date_Time object.
    */
    Date_Time getFrom () const;
    //!Method getTo
    /*!A normal member which returns a Date_Time object of the event end.
      \return a Date_Time object.
    */
    Date_Time getTo () const;
    //!Virtual method getTill
    /*!A normal member which returns a Date_Time object of the event recurrence limit.\n
      In this case 0 value of the Date_Time will be returned.
      \return a Date_Time object.
    */
    virtual Date_Time getTill () const;
    //!Method getSummary
    /*!A normal member which returns a string value of the m_Summary.
      \return a string value.
    */
    string getSummary () const;
    //!Method getClass
    /*!A normal member which returns a string value of the m_Class.
      \return a string value.
    */
    string getClass () const;
    //!Method getCategories
    /*!A normal member which returns a vector of the categories of the event.
      \return a vector.
    */
    vector<string> getCategories () const;
    //!Method getDuty
    /*!A normal member which returns a bool value of the m_Duty.
      \return a bool value.
    */
    bool getDuty () const;
    //!Method getMoveable
    /*!A normal member which returns a bool value of the m_Moveable.
      \return a bool value.
    */
    bool getMoveable () const;
    //!Method getLimit
    /*!A normal member which returns an integer value of the m_Limit.
      \return an integer value.
    */
    int getLimit () const;
    //!Method getType
    /*!A normal member which returns an integer value of the m_Type.
      \return an integer value.
    */
    int getType () const;
    //!Method UID
    /*!A normal member which returns a size_t value of the m_UID.
      \return a size_t value.
    */
    size_t UID () const;
    //!Virtual method rUID
    /*!A normal member which returns a size_t value of the m_rUID.\n
      In this case 0 value will be returned
      \return a size_t value.
    */
    virtual size_t rUID () const;
    //!Virtual method fUID
    /*!A normal member which returns a size_t value of the m_fUID.\n
      In this case value of the m_UID will be returned.
      \return a size_t value.
    */
    virtual size_t fUID () const;
    //!Virtual method getCycle
    /*!A normal member which returns a string value of the m_Cycle.
      In this case "default" string value will be returned.
      \return a string value.
    */
    virtual string getCycle () const;
    //!Method getSharedWith
    /*!A normal member which returns a vector of the users which is the event shared with.
      \return a vector.
    */
    vector<string> getSharedWith () const;
    //!Method setSummary
    /*!A normal member which sets the summary from the input string value.
      \param Summary - a string value which will be set as the new value of m_Summary.
    */
    void setSummary ( string Summary );
    //!Method setClass
    /*!A normal member which sets the class from the input string value.
      \param Class - a string value which will be set as the new value of m_Class.
    */
    void setClass ( string Class );
    //!Method setCategories
    /*!A normal member which sets the categories from the input vector.
      \param Categories - a vector which will be set as the new value of m_Categories.
    */
    void setCategories ( vector<string> Categories );
    //!Method setDuty
    /*!A normal member which sets the mandatory from the input bool value.
      \param Duty - a bool value which will be set as the new value of m_Duty.
    */
    void setDuty ( bool Duty );
    //!Method setMoveable
    /*!A normal member which sets the moveability from the input bool value.
      \param Moveable - a bool value which will be set as the new value of m_Moveable.
    */
    void setMoveable ( bool Moveable );
    //!Method setLimit
    /*!A normal member which sets the limit from the input integer value.
      \param Limit - an integer value which will be set as the new value of m_Limit.
    */
    void setLimit ( int Limit );
    //!Method setFrom
    /*!A normal member which sets a Date_Time of the start of the Event.
      \param From - a Date_Time object
    */
    void setFrom ( Date_Time From );
    //!Method setTo
    /*!A normal member which sets a Date_Time of the end of the Event.
      \param To - a Date_Time object
    */
    void setTo ( Date_Time To );
    //!Method setUID
    /*!A normal member which sets the UID from the input size_t value.
      \param UID - a size_t value which will be set as the new value of m_UID.
    */
    void setUID ( size_t UID );
    //!Method setrUID
    /*!A normal member which sets the rUID from the input size_t value.
      In this case nothing will be set.
      \param rUID - a size_t value which will be set as the new value of m_rUID.
    */
    virtual void setrUID ( size_t rUID );
    //!Method setfUID
    /*!A normal member which sets the fUID from the input size_t value.
      In this case nothing will be set.
      \param fUID - a size_t value which will be set as the new value of m_fUID.
    */
    virtual void setfUID ( size_t fUID );
    //!Method setSharedWith
    /*!A normal member which sets the accounts which is the event shared with from input vector.
      \param SharedWith - a vector which will be set as the new value of m_SharedWith.
    */
    void setSharedWith ( vector<string> SharedWith );
    //!Method setType
    /*!A normal member which sets the m_Ind from the input integer value.
      \param Ind - an integer value which will be set as the new value of m_Ind.
    */
    void setType ( int Ind );
    //!Virtual method clone
    /*!This method creates exact clone of the shared_ptr<Event> object with all of the members.
      \return shared_ptr<Event> object of the clone.
    */
    virtual shared_ptr<Event> clone () const;
protected:
    //!Overloaded operator <<
    /*!Used for the output of the information about the event to the ostream.\n
       These information can be then shown to the user by sending the ostream output to the cout.
       \param os - an ostream input value.
       \param e - an Event object.
       \return ostream output with the information about the event.
    */
    friend ostream & operator << ( ostream & os, shared_ptr<Event> e );
    //!Virtual method print
    /*!Method which inputs the information about the Event object into the ostream parameter.
      \param os - an ostream input value.
    */
    virtual void print ( ostream & os ) const;
    size_t m_UID;
    Date_Time m_From = Date_Time ( 0, 0, 0, 0, 0 );
    Date_Time m_To = Date_Time ( 0, 0, 0, 0, 0 );
    string m_Summary;
    string m_Class;
    vector<string> m_Categories;
    bool m_Duty;
    bool m_Moveable;
    int m_Limit;
    int m_Ind;
    vector<string> m_SharedWith;
};
//!Class Event_R
/*!
Main class for the handling of the recurring events of the calendar. Class is working with the\n
Repeatable and Repeatable until events. Class inherit from the Event class and ads own types of\n
the methods and members. This is the example of the polimorphism.
Class is handling:\n
*/
/*###Recurring events:
This type of the event has same options as From-To event but can be repeated in some cycle.\n
This cycle can be set to: daily, weekly, monthly and yearly. The event will be repeating in\n
the given period. This type also contains the rUID which connects it with every other event in this\n
cycle and the fUID which connects it to the parent event - Event on the very begining of the cycle.\n
###Recurring events until:
In contrast with the classic recurring event, this event adds the option to limit the recurrence\n
by some datetime. However other functionalities are the same as in the other two types of the events.*/
class Event_R : public Event { 
public:
    //!Default constructor
    /*!This constructor is overloaded for the Repeatable event type.
      \param UID - a size_t value of the UID.
      \param rUID - a size_t value of the rUID.
      \param From - a Date_Time object of the event start.
      \param To - a Date_Time object of the event end.
      \param Cycle - a string value of the cycle.
      \param Summary - a string value of the summary.
      \param Class - a string value of the class.
      \param Categories - a vector of the categories.
      \param Duty - a bool value telling about the mandatory.
      \param Moveable - a bool value telling about the moveability.
      \param Limit - an integer value of the moving limit.
    */
    Event_R ( size_t UID, size_t rUID, Date_Time From, Date_Time To, string Cycle, string Summary,
        string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit );
    //!Default constructor
    /*!This constructor is overloaded for the Repeatable until event type.
      \param UID - a size_t value of the UID.
      \param rUID - a size_t value of the rUID.
      \param From - a Date_Time object of the event start.
      \param To - a Date_Time object of the event end.
      \param Till - a Date_Time object of the recurrence limit.
      \param Cycle - a string value of the cycle.
      \param Summary - a string value of the summary.
      \param Class - a string value of the class.
      \param Categories - a vector of the categories.
      \param Duty - a bool value telling about the mandatory.
      \param Moveable - a bool value telling about the moveability.
      \param Limit - an integer value of the moving limit.
    */
    Event_R ( size_t UID, size_t rUID, Date_Time From, Date_Time To, Date_Time Till, string Cycle, string Summary,
        string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit );
    //!Default destructor
    /*!Destructs the Event_R object.
    */
    ~Event_R ();
    //!Virtual method rUID
    /*!A normal member which returns a size_t value of the m_rUID.
      \return a size_t value.
    */
    virtual size_t rUID () const override;
    //!Virtual method fUID
    /*!A normal member which returns a size_t value of the m_fUID.
      \return a size_t value.
    */
    virtual size_t fUID () const override;
    //!Virtual method getCycle
    /*!A normal member which returns a string value of the m_Cycle.
      \return a string value.
    */
    virtual string getCycle () const override;
    //!Virtual method getTill
    /*!A normal member which returns a Date_Time object of the event recurrence limit.
      \return a Date_Time object.
    */
    virtual Date_Time getTill () const override;
    //!Virtual method setrUID
    /*!A normal member which sets the rUID from the input size_t value.
      \param rUID - a size_t value which will be set as the new value of m_rUID.
    */
    virtual void setrUID ( size_t rUID ) override;
    //!Virtual method setfUID
    /*!A normal member which sets the fUID from the input size_t value.
      \param fUID - a size_t value which will be set as the new value of m_fUID.
    */
    virtual void setfUID ( size_t fUID ) override;
    //!Virtual method clone
    /*!This method creates exact clone of the shared_ptr<Event> object with all of the members.
      \return shared_ptr<Event> object of the clone.
    */
    virtual shared_ptr<Event> clone () const override;
protected:
    //!Virtual method print
    /*!Method which inputs the information about the Event_R object into the ostream parameter.
      \param os - an ostream input value.
    */  
    virtual void print ( ostream & os ) const;
    size_t m_rUID;
    size_t m_fUID;
    string m_Cycle;
    Date_Time m_Till = Date_Time ( 0, 0, 0, 0, 0 );
};
//--------------------------
#endif
