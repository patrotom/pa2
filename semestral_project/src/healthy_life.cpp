#include "calendar.h"
//--------------------------
void Calendar::hl_status ( bool status ) {  hlm_Status = status; }
//--------------------------
bool Calendar::hl_statusGet () const { return hlm_Status; }
//--------------------------
int Calendar::hl_eventSum ( string type ) const {
    int sum = 0;
    Time From = Time ( 0, 0 );
    Time To = Time ( 0, 0 );

    if ( hlm_Status == false )
        return -1;

    if ( type == "breakfast" ) {
        From = hlm_BreakfastF;
        To = hlm_BreakfastT;
    }
    else if ( type == "snack" ) {
        From = hlm_SnackF;
        To = hlm_SnackT;
    }
    else if ( type == "lunch" ) {
        From = hlm_LunchF;
        To = hlm_LunchT;
    }
    else if ( type == "dinner" ) {
        From = hlm_DinnerF;
        To = hlm_DinnerT;
    }
    else
        return -2;

    time_t var = time ( NULL );
    tm f = *localtime ( &var );
    tm t = *localtime ( &var );

    for ( auto it : m_Eventlist ) {

        f.tm_year = it->getFrom().year() - 1900;
        f.tm_mon = it->getFrom().month() - 1;
        f.tm_mday = it->getFrom().day();
        mktime ( &f );
        t.tm_year = it->getTo().year() - 1900;
        t.tm_mon = it->getTo().month() - 1;
        t.tm_mday = it->getTo().day();
        mktime ( &t );
        Time timeF ( it->getFrom().min(), it->getFrom().hour() );
        Time timeT ( it->getTo().min(), it->getTo().hour() );
    
        if ( ( ( t.tm_yday - f.tm_yday ) == 0 ) && ( it->getFrom().year() == it->getFrom().year() ) ) {
            if ( timeF >= From && timeF <= To && timeT >= To )
                sum++;
            else if ( timeF >= From && timeF <= To && timeT <= To )
                sum++;
            else if ( timeF <= From && timeT >= From && timeT <= To )
                sum++;
            else if ( From >= timeF && From <= timeT && To <= timeT )
                sum++;
        }
        else {
            int diff = abs ( t.tm_yday - f.tm_yday );
            if ( ( timeF <= From ) || ( timeF >= From && timeF <= To ) )
                sum++;
            if ( timeT >= To || ( timeT >= From && timeT <= To ) )
                sum++;
            sum += ( diff - 1 );
        }
    }
    return sum;
}
//--------------------------
void Calendar::hl_Stats () const {

    int b = hl_eventSum ( "breakfast" );
    int s = hl_eventSum ( "snack" );
    int l = hl_eventSum ( "lunch" );
    int d = hl_eventSum ( "dinner" );

    cout << "Healthy life statistics:" << endl;
    cout << "------------------------" << endl;
    cout << "Number of times when events interfere with:" << endl;
    cout << "\t- Breakfast: " << b << endl;
    cout << "\t- Snack: " << s << endl;
    cout << "\t- Lunch: " << l << endl;
    cout << "\t- Dinner: " << d << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Summary:" << endl;
    cout << endl;
    cout << "- Breakfast:" << endl;
    if ( b <= 5 )
        cout << "\t* You have almost nothing planned during your breakfast time, well done !" << endl;
    else if ( b > 5 && b <= 10 )
        cout << "\t* You have planned few events during your breakfast time but it is still in normal limit." << endl;
    else if ( b > 10 && b <= 20 )
        cout << "\t* You are starting to ignore your breakfast time, please consider canceling some of your events during this time." << endl;
    else if ( b > 20 )
        cout << "\t* You are almost completely ignoring your breakfast time, you have to cancel some of your events to stay healthy !" << endl;
    cout << "-----" << endl;
    cout << "- Snack:" << endl;
    if ( s <= 5 )
        cout << "\t* You have almost nothing planned during your snack time, well done !" << endl;
    else if ( s > 5 && s <= 10 )
        cout << "\t* You have planned few events during your snack time but it is still in normal limit." << endl;
    else if ( s > 10 && s <= 20 )
        cout << "\t* You are starting to ignore your snack time, please consider canceling some of your events during this time." << endl;
    else if ( s > 20 )
        cout << "\t* You are almost completely ignoring your snack time, you have to cancel some of your events to stay healthy !" << endl;
    cout << "-----" << endl;
    cout << "- Lunch:" << endl;
    if ( l <= 5 )
        cout << "\t* You have almost nothing planned during your lunch time, well done !" << endl;
    else if ( l > 5 && l <= 10 )
        cout << "\t* You have planned few events during your lunch time but it is still in normal limit." << endl;
    else if ( l > 10 && l <= 20 )
        cout << "\t* You are starting to ignore your lunch time, please consider canceling some of your events during this time." << endl;
    else if ( l > 20 )
        cout << "\t* You are almost completely ignoring your lunch time, you have to cancel some of your events to stay healthy !" << endl;
    cout << "-----" << endl;
    cout << "- Dinner:" << endl;
    if ( d <= 5 )
        cout << "\t* You have almost nothing planned during your dinner time, well done !" << endl;
    else if ( d > 5 && d <= 10 )
        cout << "\t* You have planned few events during your dinner time but it is still in normal limit." << endl;
    else if ( d > 10 && d <= 20 )
        cout << "\t* You are starting to ignore your dinner time, please consider canceling some of your events during this time." << endl;
    else if ( d > 20 )
        cout << "\t* You are almost completely ignoring your dinner time, you have to cancel some of your events to stay healthy !" << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Overall:" << endl;
    cout << endl;
    int o = b + s + l + d;
    cout << "* Number of times when events interfere with your meal times: "
         << o << endl;
    cout << endl;
    if ( o <= 10 )
        cout << "You have stable routine for your meal times." << endl;
    else if ( o > 10 && o <= 20 )
        cout << "Some of the events break your stable routine but it is not critical." << endl;
    else if ( o > 20 && o <= 30 )
        cout << "Your stable routine is falling apart and you should reconsider time for your meals." << endl;
    else if ( o > 30 )
        cout << "Your routines for meals are completely broken ! Please cancel the events during your meal times to not to get hurt !" << endl;
}
//--------------------------
