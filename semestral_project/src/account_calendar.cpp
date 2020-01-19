#include "calendar.h"
using namespace std;
//--------------------------
Account::Account ( string Name, string Surname, string Nickname ) {
    m_Name = Name;
    m_Surname = Surname;
    m_Nickname = Nickname;
}
//--------------------------
string Account::getName () const { return m_Name; }
//--------------------------
string Account::getSurname () const { return m_Surname; }
//--------------------------
string Account::getNickname () const { return m_Nickname; }
//--------------------------
Calendar::Calendar ( string Name, string Surname, string Nickname ) 
: Account ( Name, Surname, Nickname ) {
    hlm_Status = false;
}
//--------------------------
Calendar::~Calendar () {}
//--------------------------
bool Calendar::operator == ( const Calendar & src ) const {
    return ( this->getNickname() == src.getNickname() );
}
//--------------------------
size_t Calendar::addEvent ( shared_ptr<Event> Ev ) {
    if ( m_Eventlist.find ( Ev ) != m_Eventlist.end() )
        return 0;

    int counter = 0, type = 0;
    size_t globalUID = Ev->UID();

    if ( Ev->getType() == 2 || Ev->getType() == 3 ) {

        if ( Ev->getCycle() == "daily" ) {
            counter = 1;
            type = 365;
        }
        else if ( Ev->getCycle() == "weekly" ) {
            counter = 7;
            type = 735;
        }   
        else if ( Ev->getCycle() == "monthly" ) {
            counter = 30;
            type = 1800;
        }   
        else if ( Ev->getCycle() == "yearly" ) {
            counter = 365;
            type = 21900;
        }

        time_t t = time ( NULL );
        tm from = *localtime ( &t );
        tm to = *localtime ( &t );

        from.tm_year = Ev->getFrom().year() - 1900;
        from.tm_mon = Ev->getFrom().month() - 1;
        from.tm_mday = Ev->getFrom().day();
        
        to.tm_year = Ev->getTo().year() - 1900;
        to.tm_mon = Ev->getTo().month() - 1;
        to.tm_mday = Ev->getTo().day();
        mktime ( &from );
        mktime ( &to );

        for ( int i = counter; i <= type; i+=counter ) {

            shared_ptr<Event> newEvent = Ev->clone();
            if ( counter == 365 ) {
                from.tm_year += 1;
                to.tm_year += 1;
            }
            else {
                from.tm_mday += counter;
                to.tm_mday += counter;
            }
            mktime ( &from );
            newEvent->setFrom ( Date_Time (  newEvent->getFrom().min(),
                                            newEvent->getFrom().hour(),
                                            from.tm_mday,
                                            from.tm_mon + 1,
                                            from.tm_year + 1900 ) );
            mktime ( &to );
            newEvent->setTo ( Date_Time (  newEvent->getTo().min(),
                                            newEvent->getTo().hour(),
                                            to.tm_mday,
                                            to.tm_mon + 1,
                                            to.tm_year + 1900 ) );

            newEvent->setUID ( ++ globalUID );
            newEvent->setfUID ( Ev->UID() );
            if ( Ev->getType() == 3 )
                if ( newEvent->getTo() > Ev->getTill() )
                    break;
            m_Eventlist.insert ( newEvent );
        }
    }

    Ev->setfUID ( Ev->UID() );
    m_Eventlist.insert ( Ev );
    return globalUID;
}
//--------------------------
bool Calendar::removeEvent ( size_t UID ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;

    if ( (*it)->getType() == 2 || (*it)->getType() == 3 ) {
        size_t rUID = (*it)->rUID();
        for ( auto i = m_Eventlist.begin(); i != m_Eventlist.end(); ) {
            if ( (*i)->rUID() == rUID )
                m_Eventlist.erase ( i ++ );
            else
                ++ i;
        }
    }
    else
        m_Eventlist.erase ( (*it) );
    return true;
}
//--------------------------
int Calendar::moveEvent ( size_t UID, Date_Time From, Date_Time To  ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(), 
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );

    if ( it == m_Eventlist.end() )
        return 0;
    if ( (*it)->getMoveable() == false )
        return 1;
    if ( (*it)->getLimit() == 0 )
        return 2;

    auto iter = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                          [&] ( shared_ptr<Event> e ) { return e->UID() == (*it)->fUID(); } );
    shared_ptr<Event> newEvent = (*iter)->clone();    

    if ( newEvent->getLimit() != -1 ) {
        int lim = newEvent->getLimit();
        newEvent->setLimit ( -- lim );
    }

    if ( newEvent->getType() == 2 || newEvent->getType() == 3 ) {
        
        this->removeEvent ( (*it)->UID() );
        newEvent->setFrom ( From );
        newEvent->setTo ( To );
        this->addEvent ( newEvent );
    }
    else { 
        m_Eventlist.erase ( (*it) );
        newEvent->setFrom ( From );
        newEvent->setTo ( To );
        m_Eventlist.insert ( newEvent );;
    }

    return 3;
}
//--------------------------
Date_Time Calendar::freeDate ( Date_Time From, string Task ) const {

    Date_Time Free ( 0, 0, 0, 0, 0 );
    int hourIndex = 0, dayIndex = 0;

    if ( Task == "hour" ) 
        hourIndex = 1;
    else if ( Task == "day" ) {
        dayIndex = 1;
    }

    From.setMin ( 0 );
    int cnt = 0;
    bool ind = true;
    time_t t = time ( NULL );
    tm time = *localtime ( &t );
    time.tm_hour = From.hour() + 1;
    time.tm_min = From.min();
    time.tm_mday = From.day();
    time.tm_mon = From.month() - 1;
    time.tm_year = From.year() - 1900;
    mktime ( &time );

    while (1) {
        for ( auto it : m_Eventlist ) {
            shared_ptr<Event> temp = it->clone();
            tm t1 = *localtime ( &t );
            t1.tm_year = temp->getFrom().year() - 1900;
            t1.tm_mon = temp->getFrom().month() - 1;
            t1.tm_mday = temp->getFrom().day() - dayIndex;

            if ( dayIndex == 1 )
                t1.tm_hour = 23;
            else {
                t1.tm_hour = temp->getFrom().hour() - hourIndex; 
                t1.tm_min = 59;
            }
            mktime ( &t1 );
            temp->setFrom ( Date_Time ( t1.tm_min, t1.tm_hour, t1.tm_mday,
                                       t1.tm_mon + 1, t1.tm_year + 1900 ) );
            tm t2 = *localtime ( &t );
            t2.tm_year = temp->getTo().year() - 1900;
            t2.tm_mon = temp->getTo().month() - 1;
            t2.tm_mday = temp->getTo().day();

            if ( dayIndex == 1 )
                t2.tm_hour = 23;
            else {
                t2.tm_hour = temp->getTo().hour();
            }
            t2.tm_min = 59;
            mktime ( &t2 );
            temp->setTo ( Date_Time ( t2.tm_min, t2.tm_hour, t2.tm_mday,
                                     t2.tm_mon + 1, t2.tm_year + 1900 ) );

            if ( From > temp->getFrom() && From < temp->getTo() ) {
                ind = false;
                cnt++;
                break;
            }
        }
        if ( ind == true ) {

            time.tm_year = From.year() - 1900;
            time.tm_mon = From.month() - 1;
            time.tm_min = 0;

            if ( cnt == 0 && Task == "hour" ) {
                time.tm_mday = From.day();
                time.tm_hour = From.hour() + 1;
            }
            else if ( cnt == 0 && Task == "day" ) {
                time.tm_hour = 0;
                time.tm_mday = From.day() + 1;
            }
            else if ( Task == "hour" && cnt != 0 )
                time.tm_hour = From.hour() + 1; 
            else if ( Task == "day" && cnt != 0 )
                time.tm_hour = 0;
            mktime ( &time );

            Free = Date_Time ( time.tm_min, time.tm_hour, time.tm_mday,
                               time.tm_mon + 1, time.tm_year + 1900 );
            break;
        }


        if ( Task == "hour" )
            time.tm_hour = From.hour() + 1;
        else if ( Task == "day" )
            time.tm_mday = From.day() + 1;
        mktime ( &time );
        From = Date_Time ( time.tm_min, time.tm_hour, time.tm_mday, time.tm_mon + 1,
                           time.tm_year + 1900 );
        ind = true;
    }

    return Free;
}
//--------------------------
int Calendar::shareEvent ( size_t UID, string Nickname ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return 0;

    shared_ptr<Event> newEvent = (*it)->clone();
    vector<string> SW = newEvent->getSharedWith();

    if ( find ( SW.begin(), SW.end(), Nickname ) != SW.end() )
        return 1;

    SW.push_back( Nickname );
    newEvent->setSharedWith ( SW );
    newEvent->setClass ( "Shared" );
    m_Eventlist.erase ( (*it) );
    m_Eventlist.insert ( newEvent );
    return 2;
}
//--------------------------
int Calendar::unshareEvent ( size_t UID, string Nickname ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                        [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return 0;

    shared_ptr<Event> newEvent = (*it)->clone();
    vector<string> SW = newEvent->getSharedWith();
    
    if ( find ( SW.begin(), SW.end(), Nickname ) == SW.end() )
        return 1;

    SW.erase ( find ( SW.begin(), SW.end(), Nickname ) );

    if ( SW.empty() )
        newEvent->setClass ( "Private" );

    newEvent->setSharedWith ( SW );
    m_Eventlist.erase ( (*it) );
    m_Eventlist.insert ( newEvent );
    return 2;
}
//--------------------------
bool Calendar::isEmpty () const { return m_Eventlist.empty(); }
//--------------------------
shared_ptr<Event> Calendar::getEvent ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                    [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        throw "Event not found";
    shared_ptr<Event> returnEvent = (*it)->clone();

    return ( returnEvent );
}
//--------------------------
bool Calendar::printEvent ( size_t UID ) {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(), 
                    [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;

    cout << (*it);
    return true;
}
//--------------------------
void Calendar::printAll () const {
    cout << "--------------------------" << endl;
    for ( auto it : m_Eventlist ) {
        cout << it;
        cout << "--------------------------" << endl;
    }
    cout << "--------------------------" << endl;
}
//--------------------------
bool Calendar::evExists ( size_t UID ) const {
    auto it = find_if ( m_Eventlist.begin(), m_Eventlist.end(),
                    [&] ( shared_ptr<Event> e ) { return e->UID() == UID; } );
    if ( it == m_Eventlist.end() )
        return false;
    return true;
}
//--------------------------
