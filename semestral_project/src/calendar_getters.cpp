#include "calendar.h"
using namespace std;
//--------------------------
string Calendar::getSummary ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getSummary();
}
//--------------------------
string Calendar::getClass ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getClass();
}
//--------------------------
vector<string> Calendar::getCategories ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getCategories();
}
//--------------------------
bool Calendar::getDuty ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getDuty();
}
//--------------------------
bool Calendar::getMoveable ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getMoveable();
}
//--------------------------
int Calendar::getLimit ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getMoveable();
}
//--------------------------
int Calendar::getType ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    return (*it)->getType(); 
}
//--------------------------
