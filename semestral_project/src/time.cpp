#include "datetime.h"
using namespace std;
//--------------------------
Time::Time ( int Min, int Hour ) {
    m_Min = Min;
    m_Hour = Hour;
}
//--------------------------
Time::~Time () {}
//--------------------------
Time & Time::operator = ( const Time & src ) {
    if ( &src == this ) return (*this);
    m_Min = src.m_Min;
    m_Hour = src.m_Hour;
    return (*this);
}
//--------------------------
bool Time::operator > ( const Time & src ) const {
    if ( this->hour() > src.hour() ){
        return true;
    }
    else if ( this->hour() == src.hour() ) {
        if ( this->min() > src.min() )
            return true;
    }
    return false;
}
//--------------------------
bool Time::operator < ( const Time & src ) const {
    if ( this->hour() < src.hour() ){
        return true;
    }
    else if ( this->hour() == src.hour() ) {
        if ( this->min() < src.min() )
            return true;
    }
    return false;
}
//--------------------------
bool Time::operator <= ( const Time & src ) const { 
    
    if ( ( ( ( this->hour() * 60 ) + this->min() ) - ( ( src.hour() * 60 ) + src.min() ) ) <= 0 )
        return true;
    return false;
}
//--------------------------
bool Time::operator >= ( const Time & src ) const { 
    if ( ( ( ( this->hour() * 60 ) + this->min() ) - ( ( src.hour() * 60 ) + src.min() ) ) >= 0 )
        return true;
    return false;
}
//--------------------------
bool Time::operator == ( const Time & src ) const {
    if ( ( this->hour() == src.hour() ) && ( this->min() == src.min() ) )
        return true;
    return false;
}
//--------------------------
int Time::min () const { return m_Min; }
int Time::hour () const { return m_Hour; }
//--------------------------
void Time::setMin ( int min ) { m_Min = min; }
void Time::setHour ( int hour ) { m_Hour = hour; }
//--------------------------
bool Time::validateTime () const {
    if ( m_Min < 0 || m_Min > 60 )
        return false;
    if ( m_Hour < 0 || m_Hour > 23 )
        return false;
    return true;
}
//--------------------------
