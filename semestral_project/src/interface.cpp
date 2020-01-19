#include "interface.h"
//--------------------------
Interface::Interface () {
    Database data;
}
Interface::~Interface () {}
//--------------------------
Date_Time readDatetime () {
    int year, month, day, hour, min;
    string opt;
    cout << "\t[Type only the numbers of year, month, month day, hour, minute]" << endl;
    cout << "Year: ";
    getline ( cin, opt );
    char * c = (char*)opt.c_str(), *endptr[1];
    year = (int)(strtol ( c, endptr, 0 ));
    if ( *endptr == c || !cin ) {
        cin.clear();
        year = -1;
    }
    cout << "Month: ";
    getline ( cin, opt );
    c = (char*)opt.c_str();
    month = (int)(strtol ( c, endptr, 0 ));
    if ( *endptr == c || !cin ) {
        cin.clear();
        month = -1;
    }
    cout << "Day: ";
    getline ( cin, opt );
    c = (char*)opt.c_str();
    day = (int)(strtol ( c, endptr, 0 ));
    if ( *endptr == c || !cin ) {
        cin.clear();
        day = -1;
    }
    cout << "Hour: ";
    getline ( cin, opt );
    c = (char*)opt.c_str();
    hour = (int)(strtol ( c, endptr, 0 ));
    if ( *endptr == c || !cin ) {
        cin.clear();
        hour = -1;
    }
    cout << "Minute: ";
    getline ( cin, opt );
    c = (char*)opt.c_str();
    min = (int)(strtol ( c, endptr, 0 ));
    if ( *endptr == c ) {
        cin.clear();
        min = -1;
    }
    return Date_Time ( min, hour, day, month, year );
}
//--------------------------
void Interface::setup () {
    long int initial_option = -1;
    string opt;
    cout << "*** Welcome to the FITcal v1.0 ***" << endl;
    cout << endl;
    while (1) {
        cout << "--------------------------" << endl;
        cout << "Next step:" << endl;
        cout << "0 - create new account\n"
             << "1 - login to existing account\n"
             << "2 - exit" << endl;

        while (1) {  
            cout << "Option: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            initial_option = strtol ( c, endptr, 0 );

            if ( ! ( initial_option == 0 || initial_option == 1 || initial_option == 2 ) ||
                 ( *endptr == c ) || !cin ) {
                cout << "!! You have entered wrong option !!" << endl;
                cin.clear();
            }
            else 
                break;
        }

        switch ( initial_option ) {
            case 0: {
                newAccount();
                break;
            }
            case 1: {
                login();
                break;
            }
            case 2:
                return;
        }
    }
}
//--------------------------
void Interface::newAccount () {
    string name, surname, nickname, opt;
    cout << "--------------------------" << endl;
    while (1) {
        cout << "Please, type in your name: ";
        getline ( cin, name );
        if ( name.empty() ) {
            cout << "!! Invalid name !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }
    while (1) {
        cout << "Please, type in your surname: ";
        getline ( cin, surname );
        if ( surname.empty() ) { 
            cout << "!! Invalid surname !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }
    cout << "Now choose your nickname which will be used to login to the system: ";
    while (1) {
        getline ( cin, nickname );
        if ( data.accExists ( nickname ) || nickname.empty() || !cin ) {
            cout << endl;
            cout << "!! Account with the same username already exists, please choose another one !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            cin.clear();
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else {
            data.addAccount ( name, surname, nickname );
            break;
        }
        cout << "Nickname: ";
    }
    cout << endl;
    cout << "Account has been successfuly created !" << endl;
    return;
}
//--------------------------
void Interface::login () {
    string nickname = "", opt;
    cout << "--------------------------" << endl;
    while (1) { 
        cout << "Login: ";
        getline ( cin, nickname );
        if ( !data.accExists ( nickname ) || !cin ) {
            cout << endl;
            cout << "!! Account with this username does not exist !!" << endl;
            cout << endl;
            cin.clear();
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else {
            logged( nickname );
            return;
        }
    }
}
//--------------------------
void Interface::logged ( string nickname ) {
    long int temp;
    string opt;
    cout << "--------------------------" << endl;
    cout << "You have been successfuly logged in to the system !" << endl;
    while (1) {
        cout << "--------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "\t0 - add new event\n"
             << "\t1 - remove event\n"
             << "\t2 - move event\n"
             << "\t3 - find free time\n"
             << "\t4 - share event\n"
             << "\t5 - unshare event\n"
             << "\t6 - show events\n"
             << "\t7 - export to .ics\n"
             << "\t8 - healthy life manager\n"
             << "\t9 - log out" << endl; 

        while (1) {
            cout << "Option: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            temp = strtol ( c, endptr, 0 );
            if ( ! ( temp == 0 || temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5 ||
                     temp == 6 || temp == 7 || temp == 8 || temp == 9 ) || *endptr == c || !cin ) {
                cin.clear();
                cout << "!! Wrong option !!" << endl;
                break;
            }
            switch ( temp ) {
                case 0: {
                    addEvent ( nickname );
                    break;
                }
                case 1: {
                    removeEvent ( nickname );
                    break;
                }
                case 2: {
                    moveEvent ( nickname );
                    break;
                }
                case 3: {
                    freeTime ( nickname );
                    break;
                }
                case 4: {
                    shareEvent ( nickname );
                    break;
                }
                case 5: {
                    unshareEvent ( nickname );
                    break;
                }
                case 6: {
                    showEvents ( nickname );
                    break;
                }
                case 7: { 
                    exportCal ( nickname ); 
                    break;
                }
                case 8: { 
                    healthyLife ( nickname );
                    break;
                }
                case 9: {
                    return;
                    break;
                }
            }
            break;
        }
    }
}
//--------------------------
void Interface::addEvent ( string nickname ) {
    Date_Time From ( 0, 0, 0, 0, 0 );
    Date_Time To ( 0, 0, 0, 0, 0 );
    Date_Time Till ( 0, 0, 0, 0, 0 );
    string Cycle = "";
    string Summary = "";
    string Class = "";
    vector<string> Categories;
    bool Duty;
    bool Moveable;
    int Limit;
    int Type = 0;
    string opt;

    cout << "--------------------------" << endl; 
    cout << "The wizzard will guide you during the adding of a new event." << endl;

    while (1) {
        while (1) {
            cout << "Enter when the event starts:" << endl;
            From = readDatetime();
            if ( !From.validateTime() || !From.validateDate() ) {
                cout << "!! Invalid date or time !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return;
                }
            }
            else
                break;
        }
        cout << endl;
        while (1) {
            cout << "Enter when the event ends:" << endl;
            To = readDatetime();
            if ( !To.validateTime() || !To.validateDate() ) {
                cout << "!! Invalid date or time !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" )
                    return;
            }
            else
                break;
        }

        if ( ( ( From == To ) && From.hour() == To.hour() && From.min() == To.min() ) ||
                ( From > To ) ) {
            cout << "!! Start of the event is same as the end or the event ends sooner than it starts !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }   
    cout << endl;
    cout << "Do you want to set this event as recurring ? [Y/N]: ";
    getline ( cin, opt );
    if ( !cin )
        cin.clear();

    if ( opt != "N" && opt != "n" ) {
        cout << endl;
        cout << "Do you want to enter recurrence limit ? [Y/N]: ";
        getline ( cin, opt );
        if ( !cin )
            cin.clear();
        if ( opt != "N" && opt != "n" ) {
            while (1) {
                while (1) {
                    Type = 3;
                    cout << "Enter when the recurrence will be stopped:" << endl;
                    Till = readDatetime();
                    if ( !Till.validateTime() || !Till.validateDate() ) {
                        cout << "!! Invalid date or time !!" << endl;
                        cout << endl;
                        cout << "Do you want to continue ? [Y/N]: ";
                        getline ( cin, opt );
                        if ( opt == "N" || opt == "n" )
                            return;
                }
                else
                    break;
                }   
                if ( Till < To ) {
                    cout << "!! Limit can not be set before the first instance of the recurring event ends !!" << endl;
                    cout << "Do you want to continue ? [Y/N]: ";
                    getline ( cin, opt );
                    if ( opt == "N" || opt == "n" || !cin ) {
                        cin.clear();
                        return;
                    }
                }
                else
                    break;
            }
        }
        else
            Type = 2;

        while (1) {
            cout << endl;
            cout << "Enter recurrence period, [daily,weekly,monthly,yearly] : ";
            getline ( cin, Cycle );

            if ( ! ( Cycle == "daily" || Cycle == "weekly" || Cycle == "monthly" ||
                     Cycle == "yearly" ) || !cin ) {
                cin.clear();      
                cout << "!! Invalid cycle period !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return; 
                }
            }
            else break;
        }
    }
    else
        Type = 1;
    cout << endl;
    cout << "Do you want to set up summary for this event ? [Y/N]: ";
    getline ( cin, opt );
    if ( !cin )
        cin.clear();

    if ( opt != "N" && opt != "n" ) {
        cout << "Summary: ";
        getline ( cin, Summary );
    }

    while (1) {
        cout << endl;
        cout << "Please enter the class of this event [Public/Private] : ";
        getline ( cin, Class );
        if ( ! ( Class == "Public" || Class == "Private" ) || !cin ) {
            cin.clear();
            cout << "!! Invalid class !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }
    cout << endl;
    cout << "Do you want to set up some categories for this event ? [Y/N]: ";
    getline ( cin, opt );
    if ( !cin )
        cin.clear();
    if ( opt != "N" && opt != "n" ) {
        string category;
        while (1) { 
            cout << "Enter the category: ";
            getline ( cin, category );
            Categories.push_back ( category );
            cout << endl;
            cout << "Do you want to enter another one ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                break;
            }
        }
    }
    while (1) {
        cout << endl;
        cout << "Is this event mandatory or not mandatory ? [IS/IS NOT] : ";
        getline ( cin, opt );
        if ( opt == "IS" || opt == "is" ) {
            Duty = false;
            break;
        }
        else if ( opt == "IS NOT" || opt == "is not" ) {
            Duty = true;
            break;
        }
        else {
            cin.clear();
            cout << "!! Invalid information !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" )
                return;
        }
    }

    while (1) {
        cout << endl;
        cout << "Is this event moveable or not moveable ? [IS/IS NOT] : ";
        getline ( cin, opt );
        if ( opt == "IS" || opt == "is" ) {
            Moveable = true;
            break;
        }
        else if ( opt == "IS NOT" || opt == "is not" ) {
            Moveable = false;
            break;
        }
        else { 
            cin.clear();
            cout << "!! Invalid information !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" )
                return;
        }
    }

    if ( Moveable == true ) {
        cout << endl;
        cout << "Do you want to limit how many times it will be possible to move this event ? [Y/N]: ";
        getline ( cin, opt );
        if ( opt != "N" && opt != "n" ) {
            while (1) { 
                cout << "Enter how many times [n > 0] : ";
                getline ( cin, opt );
                char * c = (char*)opt.c_str(), *endptr[1];
                Limit = (int)(strtol ( c, endptr, 0 ));
                if ( Limit <= 0 || *endptr == c || !cin ) {
                    cin.clear();
                    cout << "!! Invalid number !!" << endl;
                    cout << endl;
                    cout << "Do you want to continue ? [Y/N]: ";
                    getline ( cin, opt );
                    if ( opt == "N" || opt == "n" )
                        return;
                }
                else break;
            }
        }
        else 
            Limit = -1;
    }
    else
        Limit = -1;
    switch ( Type ) {

        case 1: {
            Event newEvent ( ++data.globalUID, From, To, Summary, Class, Categories, Duty, Moveable, Limit );
            auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

            size_t temp = (*it).addEvent ( make_shared<Event> ( newEvent ) );

            if ( temp == 0 ) {
                cout << endl;
                cout << "Unexpected error has occured !";
                return;
            }
            else
                data.globalUID = temp;
            break;
        }
        case 2: {
            Event_R newEvent ( ++data.globalUID, ++data.rUID, From, To, Cycle, Summary, Class, Categories, Duty, Moveable, Limit );
            auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

            size_t temp = (*it).addEvent ( make_shared<Event> ( newEvent ) );

            if ( temp == 0 ) {
                cout << endl;
                cout << "Unexpected error has occured !";
                return;
            }
            else
                data.globalUID = temp;
            break;
        }
        case 3: {
            
            auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

            size_t temp = (*it).addEvent ( make_shared<Event_R> ( ++data.globalUID, ++data.rUID, From, To, Till, Cycle, Summary, Class, Categories, Duty, Moveable, Limit ) );

            if ( temp == 0 ) {
                cout << endl;
                cout << "Unexpected error has occured !";
                return;
            }
            else
                data.globalUID = temp;
            break;
        }
    }
    cout << endl;
    cout << "Event has been successfuly created !" << endl;
    return;
}
//--------------------------
void Interface::showEvents ( string nickname ) const {
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

    if ( (*it).isEmpty() ) {
        cout << "You have not set up any event yet, there is nothing to show !" << endl;
        return;
    }
    (*it).printAll();
    return;
}
//--------------------------
void Interface::removeEvent ( string nickname ) {
    size_t UID;
    string opt;
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );
    if ( (*it).isEmpty() ) {
        cout << "There is nothing to remove !" << endl;
        return;
    }
    cout << "Note: you will need the event UID to remove it, you can find it in menu option >show events< !" << endl;
    while (1) {
        while (1) {
            cout << "Type in the UID of the event: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            UID = (size_t)(strtol ( c, endptr, 0 ));
            if ( *endptr == c ) { 
                cout << "!! Invalid format of the UID !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return;
                }
            }
            else
                break;
        }   
        if ( !(*it).removeEvent( UID ) ) {
            cout << "!! Event with specified UID not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }   
    cout << "Event has been successfuly removed !" << endl;
    return;
}
//--------------------------
void Interface::moveEvent ( string nickname ) {
    Date_Time From ( 0, 0, 0, 0, 0 );
    Date_Time To ( 0, 0, 0, 0, 0 );
    size_t UID;
    string opt;
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );
    if ( (*it).isEmpty() ) {
        cout << "There is nothing to move !" << endl;
        return;
    }
    cout << "Note: you will need the event UID to move it, you can find it in menu option >show events< !" << endl;
    while (1) {
        while (1) {
            cout << "Type in the UID of the event: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            UID = (size_t)(strtol ( c, endptr, 0 ));
            if ( *endptr == c || !cin ) {
                cin.clear(); 
                cout << "!! Invalid format of the UID !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" )
                    return;
            }
            else
                break;
        }   
        if ( !(*it).evExists ( UID ) ) { 
            cout << "!! Event with specified UID not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }

    cout << "Please enter new information about date and time:" << endl;
    while (1) {
        while (1) {
            cout << "Enter when the event starts:" << endl;
            From = readDatetime();
            if ( !From.validateTime() || !From.validateDate() ) {
                cout << "!! Invalid date or time !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return;
                }
            }
            else
                break;
        }
        cout << endl;
        while (1) {
            cout << "Enter when the event ends:" << endl;
            To = readDatetime();
            if ( !To.validateTime() || !To.validateDate() ) {
                cout << "!! Invalid date or time !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" )
                    return; 
            }
            else
                break;
        }
        shared_ptr<Event> temp = (*it).getEvent ( UID );

        if ( temp->getType() == 3 && To > temp->getTill() ) { 
            cout << "!! You have moved your event over the recurrence limit !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else if ( ( ( From == To ) && ( From.hour() == To.hour() ) && ( From.min() == To.min() ) ) ||
            ( From > To ) ) {
            cout << "!! Start of the event is same as the end or the event ends sooner than it starts !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }   
    int ind = (*it).moveEvent ( UID, From, To );

    if ( ind == 0 ) {
        cout << endl;
        cout << "Unexpected error has occured !";
        return;
    }
    else if ( ind == 1 ) {
        cout << endl;
        cout << "This event is not moveable !" << endl;
        return;
    }
    else if ( ind == 2 ) {
        cout << endl;
        cout << "This event has overloaded moving limit !" << endl;
        return;
    }


    cout << "Event has been successfuly moved !" << endl;
    return;
}
//--------------------------
void Interface::freeTime ( string nickname ) const {
    cout << "--------------------------" << endl;
    cout << "This option will find you next free time in [hour/day] -> next free hour, next free day." << endl;
    Date_Time Free ( 0, 0, 0, 0, 0 );
    string opt;
    while (1) {
        cout << "Enter date and time, from you want to find next free space:" << endl;
        Free = readDatetime();
        if ( !Free.validateTime() || !Free.validateDate() ) {
            cout << "!! Invalid date or time !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }
    string task;
    while (1) {
        cout << "Enter free time task [hour/day] : ";
        getline ( cin, task );
        if ( ! ( task == "hour" || task == "day" ) || task.empty() || !cin ) {
            cin.clear();
            cout << "!! Invalid task !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

    Date_Time freeTime =  (*it).freeDate ( Free, task );
    cout << endl;

    cout << "Next free date and time is: " << freeTime.day() << "."
                                           << freeTime.month() << "."
                                           << freeTime.year() << " "
                                           << freeTime.hour() << ":"
                                           << freeTime.min() << endl;
    cout << endl;
    return;
}
//--------------------------
void Interface::shareEvent ( string nickname ) {
    size_t UID;
    string opt;
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );
    if ( (*it).isEmpty() ) {
        cout << "There is nothing to share !" << endl;
        return;
    }
    cout << "Note: you will need the event UID to share it, you can find it in menu option >show events< !" << endl;
    while (1) {
        while (1) {
            cout << "Type in the UID of the event: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            UID = (size_t)(strtol ( c, endptr, 0 ));
            if ( *endptr == c || !cin ) {
                cin.clear(); 
                cout << "!! Invalid format of the UID !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return;
                }
            }
            else
                break;
        }   
        if ( !(*it).evExists ( UID ) ) {
            cout << "!! Event with specified UID not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }

    while (1) {
        cout << "Type in the nickname of the user you want to share this event with: ";
        getline ( cin, opt );
        auto n = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                           [&] ( Calendar const & e ) { return e.getNickname() == opt; } );
        if ( n == data.m_Accountlist.end() || !cin || opt == nickname ) {
            cin.clear(); 
            cout << "!! Account not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }

    int ind = (*it).shareEvent ( UID, opt );

    if ( ind == 0 )
        cout << "Unexpected error has occured" << endl;
    else if ( ind == 1 ) {
        cout << "You are already sharing this event with this person !" << endl;
        return;
    }
    cout << "You are now sharing this event with: " << opt << endl;
    cout << endl;
    return;
}
//--------------------------
void Interface::unshareEvent ( string nickname ) {
    size_t UID;
    string opt;
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );
    if ( (*it).isEmpty() ) {
        cout << "There is nothing to unshare !" << endl;
        return;
    }
    cout << "Note: you will need the event UID to unshare it, you can find it in menu option >show events< !" << endl;
    while (1) {
        while (1) {
            cout << "Type in the UID of the event: ";
            getline ( cin, opt );
            char * c = (char*)opt.c_str(), *endptr[1];
            UID = (size_t)(strtol ( c, endptr, 0 ));
            if ( *endptr == c || !cin ) {
                cin.clear();
                cout << "!! Invalid format of the UID !!" << endl;
                cout << endl;
                cout << "Do you want to continue ? [Y/N]: ";
                getline ( cin, opt );
                if ( opt == "N" || opt == "n" || !cin ) {
                    cin.clear();
                    return;
                }
            }
            else 
                break;
        }   
        if ( !(*it).evExists ( UID ) ) {
            cout << "!! Event with specified UID not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }

    while (1) {
        cout << "Type in the nickname of the user you want to unshare this event from: ";
        getline ( cin, opt );
        auto n = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                           [&] ( Calendar const & e ) { return e.getNickname() == opt; } );
        if ( n == data.m_Accountlist.end() || !cin || opt == nickname ) {
            cin.clear();
            cout << "!! Account not found !!" << endl;
            cout << endl;
            cout << "Do you want to continue ? [Y/N]: ";
            getline ( cin, opt );
            if ( opt == "N" || opt == "n" || !cin ) {
                cin.clear();
                return;
            }
        }
        else
            break;
    }

    int ind = (*it).unshareEvent ( UID, opt );
    if ( ind == 0 ) {
        cout << "Unexpected error has occured !" << endl;
        return;
    }
    else if ( ind == 1 ) {
        cout << "You are not sharing this event with this account !" << endl;
        return;
    }

    cout << "You have successfuly unshared this event from: " << opt << endl;
    cout << endl;
    return;
}
//--------------------------
void Interface::exportCal ( string nickname ) const {
    cout << "--------------------------" << endl;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(),
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );
    if ( (*it).isEmpty() ) {
        cout << "There is nothing to export !" << endl;
        return;
    }
    (*it).Export();
    cout << "Calendar has been to successfuly exported to .ics file !" << endl;
    return;
}
//--------------------------
void Interface::healthyLife ( string nickname ) {
    cout << "--------------------------" << endl;
    string opt;
    auto it = find_if ( data.m_Accountlist.begin(), data.m_Accountlist.end(), 
                        [&] ( Calendar const & e ) { return e.getNickname() == nickname; } );

    if ( (*it).hl_statusGet() == false ) {
        cout << "You have not set up the tracking of the healthy life yet !" << endl;
        cout << "Do you want to continue and turn the tracking on ? [Y/N]: ";
        getline ( cin, opt );
        if ( opt == "N" || opt == "n" || !cin ) {
            cin.clear();
            return;
        }
        else
            (*it).hl_status ( true );
    }
    (*it).hl_Stats();
    return;
}
//--------------------------
