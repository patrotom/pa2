#ifndef __INTERFACE__
#define __INTERFACE__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <memory>
#include "calendar.h"
#include "datetime.h"
#include "event.h"
using namespace std;
//--------------------------
//!Class Interface
/*!
This class handles interaction between the user and the program via terminal using some\n
predefined commands and the wizzard which guides the user trough creating new event, removing\n
events, sharing them etc.. Interface si capable of detecting wrong inputs as so empty inputs and\n
the user is warned when something goes wrong.\n\n
Interface works on final state machine principle. You can get from starter page to every branch of\n
the Interface and it is guaranteed that you will find your way back to end the program or make some other actions.\n
Interface is working with the Database object which handles calendars of the accounts which handles all of the\n
events.
*/
class Interface {
public:
    //!Default constructor
    /*!Object does not recieve any values.
    */
    Interface();
    //!Default destructor
    /*!Destructs the Interface object.
    */
    ~Interface();
    //!Method setup
    /*!Main menu of the interface with options like login, create new account or exit.
    */
    void setup ();
    //!Method newAccount
    /*!In this menu the wizzard will guide you trough the process of creating a new account.
    */
    void newAccount ();
    //!Method login
    /*!In this menu the wizzard will guide you trough the process of login to the system.
    */
    void login ();
    //!Method logged
    /*!Menu of the system after login with all of the options to work with events itself.
      \param nickname - a string value of the nickname of the user.
    */
    void logged ( string nickname );
    //!Method addEvent
    /*!In this option the wizzard will guide you trough the process of creating the new Event.
      \param nickname - a string value of the nickname of the user.
    */
    void addEvent ( string nickname );
    //!Method showEvents
    /*!In this option all of the events will be listed.
      \param nickname - a string value of the nickname of the user.
    */
    void showEvents ( string nickname ) const;
    //!Method removeEvent
    /*!In this option the wizzard will guide you trough the process of removing the Event.
      \param nickname - a string value of the nickname of the user.
    */
    void removeEvent ( string nickname );
    //!Method moveEvent
    /*!In this option the wizzard will guide you trough the process of moving the Event.
      \param nickname - a string value of the nickname of the user.
    */
    void moveEvent ( string nickname );
    //!Method freeEvent
    /*!In this option the wizzard will guide you trough the process of finding next free datetime.
      \param nickname - a string value of the nickname of the user.
    */
    void freeTime ( string nickname ) const;
    //!Method shareEvent
    /*!In this option the wizzard will guide you trough the process of sharing the Event with other user.
      \param nickname - a string value of the nickname of the user.
    */
    void shareEvent ( string nickname );
    //!Method unshareEvent
    /*!In this option the wizzard will guide you trough the process of unsharing the Event from other user.
      \param nickname - a string value of the nickname of the user.
    */
    void unshareEvent ( string nickname );
    //!Method exportCal
    /*!In this option all of your events will be exported to the .ics file.
      \param nickname - a string value of the nickname of the user.
    */
    void exportCal ( string nickname ) const;
    //!Method healthyLife
    /*!In this option you can turn on/off the tracking of the event and check yours healthy life stats.
      \param nickname - a string value of the nickname of the user.
    */
    void healthyLife ( string nickname );
private:
	//!Method readDateTime
	/*!Helper method for the interface to read the datetime members values and return the Date_Time object.
	  \return a Date_Time object.
	*/
	Date_Time readDateTime ();
    Database data;
};
//--------------------------
#endif
