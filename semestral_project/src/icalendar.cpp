#include "calendar.h"
//--------------------------
void Calendar::Export () const {
    ofstream file;
    file.open ( "myCal.ics", ios::out | ios::trunc );

    file << "BEGIN:VCALENDAR\r\n";
    file << "VERSION:2.0\r\n";
    file << "PRODID:-//Tomas Patro//CVUT FIT v1.0//EN\r\n";

    for ( auto it : m_Eventlist ) { 
        if ( it->fUID() == it->UID() ) {
            time_t t = time ( NULL );
            tm now = *localtime ( &t );

            file << "BEGIN:VEVENT\r\n";
            string yearN = to_string ( now.tm_year + 1900 );
            string monthN = to_string ( now.tm_mon + 1 );
            string dayN = to_string ( now.tm_mday );
            string hourN = to_string ( now.tm_hour );
            string minN = to_string ( now.tm_min );
            string secN = to_string ( now.tm_sec );
            //--------------------------
            if ( ( now.tm_mon + 1 ) < 10 )
                monthN = "0" + monthN;
            if ( ( now.tm_mday ) < 10 )
                dayN = "0" + dayN;
            if ( ( now.tm_hour ) < 10 )
                hourN = "0" + hourN;
            if ( ( now.tm_min ) < 10 )
                minN = "0" + minN;
            if ( ( now.tm_sec ) < 10 )
                secN = "0" + secN;

            file << "UID:" << yearN+monthN+dayN+"T"+hourN+minN+secN 
                 << "-" << it->UID() << "@fit.cvut.cz\r\n";
            file << "DTSTAMP:" << yearN+monthN+dayN+"T"+hourN+minN+secN << "\r\n";
            //--------------------------
            string yearF = to_string ( it->getFrom().year() );
            string monthF = to_string ( it->getFrom().month() );
            string dayF = to_string ( it->getFrom().day() );
            string hourF = to_string ( it->getFrom().hour() );
            string minF = to_string ( it->getFrom().min() );
            if ( it->getFrom().month() < 10 )
                monthF = "0" + monthF;
            if ( it->getFrom().day() < 10 )
                dayF = "0" + dayF;
            if ( it->getFrom().hour() < 10 )
                hourF = "0" + hourF;
            if ( it->getFrom().min() < 10 )
                minF = "0" + minF;

            file << "DTSTART:" << yearF+monthF+dayF+"T"+hourF+minF+"00" << "\r\n";
            //--------------------------
            string yearT = to_string ( it->getTo().year() );
            string monthT = to_string ( it->getTo().month() );
            string dayT = to_string ( it->getTo().day() );
            string hourT = to_string ( it->getTo().hour() );
            string minT = to_string ( it->getTo().min() );
            if ( it->getTo().month() < 10 )
                monthT = "0" + monthT;
            if ( it->getTo().day() < 10 )
                dayT = "0" + dayT;
            if ( it->getTo().hour() < 10 )
                hourT = "0" + hourT;
            if ( it->getTo().min() < 10 )
                minT = "0" + minT;

            file << "DTEND:" << yearT+monthT+dayT+"T"+hourT+minT+"00" << "\r\n";
            //--------------------------
            if ( it->getSummary() != "" )
                file << "SUMMARY:" << it->getSummary() << "\r\n";
            //--------------------------
            file << "CLASS:" << it->getClass() << "\r\n";
            //--------------------------
            if ( ! it->getCategories().empty() ) {
                file << "CATEGORIES:";
                for ( auto iter : it->getCategories() ) {
                    if ( iter == it->getCategories().end()[-1] )
                        file << iter << "\r\n";
                    else
                        file << iter << ",";
                }
            }   
            //--------------------------
            file << "TRANSP:";
            if ( it->getDuty() == false )
                file << "OPAQUE\r\n";
            else
                file << "TRANSPARENT\r\n";
            //--------------------------
            if ( it->getType() == 2 ) {
                string rule = it->getCycle();
                transform ( rule.begin(), rule.end(), rule.begin(), ::toupper );
                file << "RRULE:FREQ=" << rule << "\r\n";
            }
            else if ( it->getType() == 3 ) {
                string rule = it->getCycle();
                transform ( rule.begin(), rule.end(), rule.begin(), ::toupper );
                string yearU = to_string ( it->getTill().year() );
                string monthU = to_string ( it->getTill().month() );
                string dayU = to_string ( it->getTill().day() );
                string hourU = to_string ( it->getTill().hour() );
                string minU = to_string ( it->getTill().min() );
                if ( it->getTill().month() < 10 )
                    monthU = "0" + monthU;
                if ( it->getTill().day() < 10 )
                    dayU = "0" + dayU;
                if ( it->getTill().hour() < 10 )
                    hourU = "0" + hourU;
                if ( it->getTill().min() < 10 )
                    minU = "0" + minU;

                file << "RRULE:FREQ=" << rule << ";UNTIL=" 
                     << yearU+monthU+dayU+"T"+hourU+minU+"00" << "\r\n";
            }
            file << "END:VEVENT\r\n";
        }
    }
    file << "END:VCALENDAR\r\n";
    file.close();
}
//--------------------------
