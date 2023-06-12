PROGRAM=beczatom

CXX = g++
CFLAGS = -std=c++17 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb
OBJECTS = objs/main.o objs/CApplication.o objs/CCalendar.o objs/CCommand.o objs/CDateTime.o objs/CEvent.o objs/CExport.o objs/CHelp.o objs/CImport.o objs/CAdd.o objs/CInterface.o objs/CPerson.o objs/CPlace.o objs/CPrint.o objs/CCalendarFormat.o objs/CCalendarFormatDay.o objs/CCalendarFormatWeek.o objs/CCalendarFormatMonth.o objs/CSelect.o
HEADERS = src/headers/*.h

all: objs compile doc

run: compile
	./$(PROGRAM)

compile: objs $(PROGRAM)

doc: $(HEADERS) src/constants.h
	doxygen Doxyfile

$(PROGRAM) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(PROGRAM)

-include $(OBJECTS:.o=.d)

objs/%.o: src/source/%.cpp
	$(CXX) -c $(CFLAGS) src/source/$*.cpp -o objs/$*.o

objs:
	mkdir objs

clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null

.PHONY: clean