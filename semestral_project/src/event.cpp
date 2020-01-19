#include "event.h"
using namespace std;
//--------------------------
Event::Event ( size_t UID, Date_Time From, Date_Time To, string Summary,
        string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit ) {
    m_UID = UID;
    m_From = From;
    m_To = To;
    m_Summary = Summary;
    m_Class = Class;
    m_Categories = Categories;
    m_Duty = Duty;
    m_Moveable = Moveable;
    m_Limit = Limit;
    m_Ind = 1;
}
//--------------------------
Event_R::Event_R ( size_t UID, size_t rUID, Date_Time From, Date_Time To, string Cycle, string Summary,
        string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit )
: Event ( UID, From, To, Summary, Class, Categories, Duty, Moveable, Limit ) {
    m_rUID = rUID;
    m_Cycle = Cycle;
    m_Ind = 2;
}
//--------------------------
Event_R::Event_R ( size_t UID, size_t rUID, Date_Time From, Date_Time To, Date_Time Till, string Cycle, string Summary,
        string Class, vector<string> Categories, bool Duty, bool Moveable, int Limit )
: Event ( UID, From, To, Summary, Class, Categories, Duty, Moveable, Limit ) {
    m_rUID = rUID;
    m_Till = Till;
    m_Cycle = Cycle;
    m_Ind = 3;
}
//--------------------------
Event::~Event () {}
//--------------------------
Event_R::~Event_R () {}
//--------------------------
bool Event::operator == ( shared_ptr<Event> src ) const {
    return ( this->m_UID == src->UID() );
}
//--------------------------
ostream & operator << ( ostream & os, shared_ptr<Event> e ) {

    e->print ( os );

    return os;
}
//--------------------------
void Event::print ( ostream & os ) const {

    os << "UID: " << UID() << endl;;
    os << "\t" << "* From: "  << getFrom().day() << "." 
                              << getFrom().month() << "."
                              << getFrom().year() << " "
                              << getFrom().hour() << ":"
                              << getFrom().min() << endl;
    
    os << "\t" << "* To: "   << getTo().day() << "." 
                             << getTo().month() << "."
                             << getTo().year() << " "
                             << getTo().hour() << ":"
                             << getTo().min() << endl;
    
    os << "\t" << "* Summary: " << getSummary() << endl;
    os << "\t" << "* Class: " << getClass() << endl;
    
    if ( ! getCategories().empty() ) {
        os << "\t" << "* Categories: ";
        for ( auto it : getCategories() ) {
            if ( it == getCategories().end()[-1] )
                os << it << endl;
            else
                os << it << ", ";
        }
    }
    else
        os << "\t" << "* Categories: " << endl;
    if ( getDuty() == false )
        os << "\t* Duty: " << "mandatory" << endl;
    else
        os << "\t* Duty: " << "optional" << endl;
    if ( getMoveable() == false )
        os << "\t* Moveable: " << "no" << endl;
    else
        os << "\t* Moveable: " << "yes" << endl;

    if ( getClass() == "Shared" && !( getSharedWith().empty() ) ) {
        os << "* Shared with: ";
        for ( auto it : getSharedWith() ) { 
            if ( it == getSharedWith().end()[-1] )
                os << it << endl;
            else
                os << it << ", ";
        }
    }
}
//--------------------------
void Event_R::print ( ostream & os ) const {

    os << "UID: " << UID() << endl;;
    os << "\t" << "* From: " << getFrom().day() << "." 
                              << getFrom().month() << "."
                              << getFrom().year() << " "
                              << getFrom().hour() << ":"
                              << getFrom().min() << endl;
    
    os << "\t" << "* To: "   << getTo().day() << "." 
                             << getTo().month() << "."
                             << getTo().year() << " "
                             << getTo().hour() << ":"
                             << getTo().min() << endl;

    if ( getType() == 3 ) {
        os << "\t" << "* Repeating until: " << getTill().day() << "."
                                            << getTill().month() << "."
                                            << getTill().year() << " "
                                            << getTill().hour() << ":"
                                            << getTill().min() << endl;
    }

    os << "\t" << "* Cycle: " << getCycle() << endl;
    
    os << "\t" << "* Summary: " << getSummary() << endl;
    os << "\t" << "* Class: " << getClass() << endl;

    if ( ! getCategories().empty() ) {
        os << "\t" << "* Categories: ";
        for ( auto it : getCategories() ) { 
            if ( it == getCategories().end()[-1] )
                os << it << endl;
            else
                os << it << ", ";
        }
    }
    else
        os << "\t" << "* Categories: " << endl;
    if ( getDuty() == false )
        os << "\t* Duty: " << "mandatory" << endl;
    else
        os << "\t* Duty: " << "optional" << endl;
    if ( getMoveable() == false )
        os << "\t* Moveable: " << "no" << endl;
    else
        os << "\t* Moveable: " << "yes" << endl;

    if ( getClass() == "Shared" && !( getSharedWith().empty() ) ) {
        os << "* Shared with: ";
        for ( auto it : getSharedWith() ) { 
            if ( it == getSharedWith().end()[-1] )
                os << it << endl;
            else
                os << it << ", ";
        }
    }
}
//--------------------------
shared_ptr<Event> Event::clone () const {
    Event temp ( m_UID, m_From, m_To, m_Summary, m_Class, m_Categories, m_Duty, m_Moveable, m_Limit );
    temp.setType ( m_Ind );
    temp.setSharedWith ( m_SharedWith );
    return make_shared<Event> ( temp );
}
//--------------------------
shared_ptr<Event> Event_R::clone () const {
    if ( m_Ind == 2 ) {
        Event_R temp ( m_UID, m_rUID, m_From, m_To, m_Cycle, m_Summary, m_Class, m_Categories, m_Duty, m_Moveable, m_Limit );
        temp.setType ( m_Ind );
        temp.setSharedWith ( m_SharedWith );
        return make_shared<Event_R> ( temp );
    }
    Event_R temp ( m_UID, m_rUID, m_From, m_To, m_Till, m_Cycle, m_Summary, m_Class, m_Categories, m_Duty, m_Moveable, m_Limit );
    temp.setType ( m_Ind );
    temp.setSharedWith ( m_SharedWith );
    return make_shared<Event_R> ( temp );
}
//--------------------------
