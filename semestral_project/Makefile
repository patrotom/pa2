CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
LD=g++
LDFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb

all: patrotom
	doxygen
patrotom: main.o datetime.o event.o account_calendar.o calendar_setters.o calendar_getters.o event_getters.o event_setters.o time.o healthy_life.o icalendar.o database.o interface.o
	$(LD) $(LDFLAGS) main.o datetime.o event.o account_calendar.o calendar_setters.o calendar_getters.o event_getters.o event_setters.o time.o healthy_life.o icalendar.o database.o interface.o -o patrotom

clean:
	rm -rf patrotom *.o *~ core doc *.ics

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o dummy/$@

run: patrotom
	./patrotom

doc:
	doxygen

compile: patrotom

main.o: src/main.cpp src/interface.h
datetime.o: src/datetime.cpp src/calendar.h
event.o: src/event.cpp src/event.h
account_calendar.o: src/account_calendar.cpp src/calendar.h
calendar_setters.o: src/calendar_setters.cpp src/calendar.h
calendar_getters.o: src/calendar_getters.cpp src/calendar.h
event_getters.o: src/event_getters.cpp src/event.h
event_setters.o: src/event_setters.cpp src/event.h
time.o: src/time.cpp src/datetime.h
healthy_life.o: src/healthy_life.cpp src/calendar.h
icalendar.o: src/icalendar.cpp src/calendar.h
database.o: src/database.cpp src/calendar.h
interface.o: src/interface.cpp src/interface.h
