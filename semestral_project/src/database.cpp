#include "calendar.h"
//--------------------------
Database::Database() {
    globalUID = 1;
    rUID = 1;
}
//--------------------------
Database::~Database() {}
//--------------------------
bool Database::addAccount ( string Name, string Surname, string Nickname ) {

    auto it = find_if ( m_Accountlist.begin(), m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == Nickname; } );
    if ( it != m_Accountlist.end() )
        return false;

    Calendar newCal ( Name, Surname, Nickname );
    m_Accountlist.push_back ( newCal );
    return true;
}
//--------------------------
bool Database::accExists ( string Nickname ) const {
    auto it = find_if ( m_Accountlist.begin(), m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == Nickname; } );
    if ( it == m_Accountlist.end() )
        return false;
    return true;
}
//--------------------------
