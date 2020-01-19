#include "calendar.h"
using namespace std;
//--------------------------
bool Calendar::setSummary ( size_t UID, string Summary ) { 
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(), 
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setSummary ( Summary );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
bool Calendar::setClass ( size_t UID, string Class ) { 
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(), 
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setClass ( Class );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
bool Calendar::setCategories ( size_t UID, vector<string> Categories ) { 
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(), 
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setCategories ( Categories );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
bool Calendar::setDuty ( size_t UID, bool Duty ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setDuty ( Duty );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
bool Calendar::setMoveable ( size_t UID, bool Moveable ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setMoveable ( Moveable );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
bool Calendar::setLimit ( size_t UID, int Limit ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    auto newEvent = (*it)->clone();
    m_Eventlist.erase ( (*it) );
    newEvent->setLimit ( Limit );
    m_Eventlist.insert ( newEvent );
    return true;
}
//--------------------------
