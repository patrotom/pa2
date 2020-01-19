#include "event.h"
//--------------------------
void Event::setSummary ( string Summary ) { m_Summary = Summary; }
//--------------------------
void Event::setClass ( string Class ) { m_Class = Class; }
//--------------------------
void Event::setCategories ( vector<string> Categories ) { m_Categories = Categories; }
//--------------------------
void Event::setDuty ( bool Duty ) { m_Duty = Duty; }
//--------------------------
void Event::setMoveable ( bool Moveable ) { m_Moveable = Moveable; }
//--------------------------
void Event::setLimit ( int Limit ) { m_Limit = Limit; }
//--------------------------
void Event::setFrom ( Date_Time From ) { m_From = From; }
//--------------------------
void Event::setTo ( Date_Time To ) { m_To = To; }
//--------------------------
void Event::setUID ( size_t UID ) { m_UID = UID; }
//--------------------------
void Event::setrUID ( size_t rUID ) { return; }
//--------------------------
void Event::setfUID ( size_t fUID ) { return; }
//--------------------------
void Event::setSharedWith ( vector<string> SharedWith ) { m_SharedWith = SharedWith; }
//--------------------------
void Event::setType ( int Ind ) { m_Ind = Ind; }
//==========================
void Event_R::setrUID ( size_t rUID ) { m_rUID = rUID; }
//--------------------------
void Event_R::setfUID ( size_t fUID ) { m_fUID = fUID; }
//--------------------------
