# Calendar

Simple calendar application developed as a semester project for PA2 (Programming and Algorithmics 2).

## Original Assignment (Progtest)

Your goal is to implement an application for managing calendars and their events.

Implement the following features:

1. The calendar must display at least daily, weekly, and monthly overviews of events.
2. For events, the following information must be recorded at a minimum: event name, date and time, duration, location, attendees, tags, and a text note. 
You may add other interesting attributes in your implementation (e.g., attendance: mandatory, reschedulable, optional, etc.).
3. Events can be one-time or recurring. 
Allow defining the recurrence frequency at least on a daily level.
4. The calendar must allow searching for events by individual attributes, including combinations using "AND" and "OR" logical operators (e.g., events before 23.1.2022 AND in Prague, etc.).
5. Allow exporting and importing events. 
It must be possible to export a selection defined by a search query.
6. The calendar must not allow event collisions; in case of a collision, it must find the nearest available time slot or reschedule the event (if possible). 
Alternatively, you can allow a maximum number of collisions (e.g., 24 collisions for a classroom, based on its student capacity), but collisions cannot be ignored.

Where can polymorphism be used? (recommended)

- Calendar views: daily, weekly, monthly, etc.
- Collision resolution strategies: finding the nearest possible time slot, rescheduling max X other events to free slots, etc.
- Export formats: proprietary, iCalendar, CSV, etc.
- User interfaces: console, ncurses, SDL, OpenGL (various variants), etc.
- Event types (consider beforehand whether this actually represents polymorphism in your specific case).

## Usage

Build and run the application:
```
make run
```

Generate documentation:
```
make doc
```

Run tests:
```
make test
```

## Calendar Application Specification
We will create a "Calendar" application where the user can launch the program and manage the event database using simple terminal commands.

- `select ...` outputs events meeting specified conditions to the terminal (e.g., select place=T9:105 200 and start<01.01.2023)
- `day [date]` outputs a daily event overview to the terminal (format for date is dd.mm.yyyy)
- `week [week]` outputs a weekly event overview to the terminal (format for week is [week_number_in_year].yyyy)
- `month [month]` outputs a monthly event overview to the terminal (format for month is [month_number_in_year].yyyy)
- `-e [filename]` this flag can be appended to any of the above commands to redirect the output from the terminal to a file
- `add ...` adds a new event
  - Event format:
  
```
DD.MM.YYYY HH:MM;[Event duration];[Event name];[Place name] [Place capacity];[Participant name Participant mail,...];[tag1,...];[frequency in days (use 0 for one-time event)];[note];
```

- `import [filename]` imports data from a file
- `help` displays the help menu
- `quit` exits the program

The application simulates a standard calendar (or event database). 
Upon entering one of the queries above, it outputs brief information to the terminal; for detailed information, the data must be exported. 
The example below illustrates the program's workflow, where $ denotes user inputs.

```
Enter query or type 'help':
$ import prednasky.txt
Enter query or type 'help':
$ day 02.05.2023
+---------------------------------------+
| 09:15 - 10:45 -> Prednaska MA1, Praha |
| 12:45 - 14:15 -> Prednaska PA2, Praha |
+---------------------------------------+
Enter query or type 'help':
```

Individual commands are implemented using a base `CCommand` class, managed by `CApplication`, which handles the overall program execution.
It includes a `CInterface` class for handling inputs and outputs.

Additionally, it contains a `CCalendar` class that stores individual `CEvent` instances. 
The `CCalendar` class allows adding events via the `addEvent` method, which also handles collision detection (automatically rescheduling the event to the nearest possible time slot).
The `CEvent` class encapsulates the required properties of each event, including `CPerson` (storing data about participants/invitees) and `CPlace` (specifying room name and capacity).

Event recurrence is handled by specifying a repetition period in days. 
Collisions are resolved by rescheduling to the nearest available time slot.

For a comprehensive overview of the utilized classes, please refer to the documentation or the simplified class diagram in `calendar.png`.

## Polymorphism Usage

- Polymorphism is applied to the base `CCommand` class, which is inherited by the `CImport`, `CSelect`, `CPrint`, `CAdd`, and `CHelp` classes (these execute commands entered via `CInterface`).
- It is also utilized with the `CCalendarFormat` class, inherited by `CCalendarFormatDay`, `CCalendarFormatMonth`, and `CCalendarFormatWeek`, which adjust the output to the requested format.
