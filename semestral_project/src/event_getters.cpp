#include "event.h"
using namespace std;
//--------------------------
Date_Time Event::getFrom () const { return m_From; }
//--------------------------
Date_Time Event::getTo () const { return m_To; }
//--------------------------
Date_Time Event::getTill () const { return Date_Time ( 0, 0, 0, 0, 0 ); }
//--------------------------
string Event::getSummary () const { return m_Summary; }
//--------------------------
string Event::getClass () const { return m_Class; }
//--------------------------
vector<string> Event::getCategories () const { return m_Categories; }
//--------------------------
bool Event::getDuty () const { return m_Duty; }
//--------------------------
bool Event::getMoveable () const { return m_Moveable; }
//--------------------------
int Event::getLimit () const { return m_Limit; }
//--------------------------
int Event::getType () const { return m_Ind; }
//--------------------------
size_t Event::UID () const { return m_UID; }
//--------------------------
size_t Event::rUID () const { return 0; }
//--------------------------
size_t Event::fUID () const { return m_UID; }
//--------------------------
string Event::getCycle () const { return "default"; }
//--------------------------
vector<string> Event::getSharedWith () const { return m_SharedWith; }
//==========================
size_t Event_R::rUID () const { return m_rUID; }
//--------------------------
size_t Event_R::fUID () const { return m_fUID; }
//--------------------------
string Event_R::getCycle () const { return m_Cycle; }
//--------------------------
Date_Time Event_R::getTill () const { return m_Till; }
