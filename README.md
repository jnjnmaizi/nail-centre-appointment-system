# Nail Centre Appointment System

A console application written in C for managing a nail centre's customers, artists, services, and appointments. It brings together linked lists, arrays, structs, unions, pointers, and text files in a single menu-driven program.

Customers can book a service with an artist, change or cancel unpaid appointments, and receive a receipt for their unpaid services. Payment is recorded locally; the program does not connect to a payment provider.

## Features

- Add customers and artists, and look them up by ID.
- Maintain a catalogue of up to 10 services and their prices.
- Book appointments with a customer, artist, service, date, and hour.
- Reject a booking when the artist already has an appointment at the same date and hour.
- Edit or cancel unpaid appointments.
- Find appointments by customer or artist.
- Calculate a customer's unpaid total, print a receipt, and mark those appointments as paid.
- Display customers, artists, and services.
- Save records to text files on exit. Appointment restoration has a known issue described below.

## Tools Used

The project uses C and its standard library, with no external dependencies. It was compiled and checked with Apple Clang 17 using `-std=c2x`.

| Concept | Where it is used |
| --- | --- |
| Structs | Customer, artist, service, and appointment records |
| Singly linked lists | Customers, artists, and appointments |
| Fixed-size array | The service catalogue, limited by `MAX_SERVICES` |
| Pointers | Links between nodes and references from appointments to their records |
| Dynamic memory | Creating list nodes with `malloc()` and releasing them with `free()` |
| Union | An artist's phone number, national ID, or address |
| Enums | Months and appointment payment status |
| File handling | Loading and saving pipe-separated text records |

## Project Structure

```text
nail-centre-appointment-system/
├── main.c             # Menu, input handling, and application startup
├── customer.c         # Customer list and file operations
├── customer.h         # Customer struct and function declarations
├── artist.c           # Artist list and file operations
├── artist.h           # Artist struct and contact union
├── service.c          # Service catalogue and file operations
├── service.h          # Service struct and capacity limit
├── appointment.c      # Booking, editing, cancellation, and receipts
├── appointment.h      # Appointment struct, dates, and payment status
├── customers.txt      # Demo customer records
├── artists.txt        # Demo artist record
├── services.txt       # Example service
├── appointments.txt   # Starts empty
├── .gitignore
└── README.md
```

Object files, executables, and debugger output are excluded from the repository. The public data files use demo customer and artist details.

## How It Works

### Customers and Artists

Customers and artists are stored in separate linked lists. Adding a record allocates a node and places it at the head of its list. Finding a record means following the `next` pointers until its ID is found.

An artist's `ContactInfo` is a union, so it stores one contact value at a time. `Ctype` identifies the active field: `1` for phone, `2` for national ID, or `3` for address.

### Services

Services are stored in an array of `struct Service`. Each service has an ID, a name, and a price. The program checks for duplicate service IDs and limits the catalogue to 10 entries. Deleting a service shifts the following elements to close the gap.

### Appointments

Each appointment is a linked-list node holding pointers to its customer, artist, and service. It also stores an ID, date, hour, and payment status.

When creating a booking, the menu checks that the selected records exist, validates the date and hour, and checks for a duplicate appointment ID. `makeAppointment()` then scans existing appointments for an artist conflict before inserting the new node at the head.

New bookings accept years **2025–2030** and whole-hour slots from **13:00 to 20:00**, inclusive. Date validation accounts for month lengths and leap years. Conflict detection compares the artist, date, and hour; it does not model service duration or check the customer's other bookings.

### Payments

`processPaymentAndPrintReceipt()` walks through a customer's unpaid appointments, prints each service and price, adds the total, and changes their status to `PAID`. The menu prevents editing paid appointments, and cancellation also rejects them.

### The Main Menu

At startup, `main()` loads customers, artists, and services before attempting to load appointments. The menu then calls the relevant module for each choice. Option `15` saves the records and exits, after which the dynamically allocated lists are freed.

## Running the Project

You need a C compiler that supports the `-std=c2x` option, such as the Clang version used for the checks.

```bash
git clone https://github.com/jnjnmaizi/nail-centre-appointment-system.git
cd nail-centre-appointment-system
cc -std=c2x -Wall -Wextra main.c -o nail-centre
./nail-centre
```

The current source includes implementation files directly: `main.c` includes `service.c` and `appointment.c`, and `appointment.c` includes `customer.c` and `artist.c`. Compile **only `main.c`** with this layout. Compiling `*.c` together would define the same functions more than once.

Run the executable from the project directory so it can find the four text files. The compiler reports existing warnings; see the notes below.

### Try It Out

The demo files contain customers `1` and `2`, artist `1`, and service `1` (`Spa`, priced at `250.00`).

1. Use options `12`, `13`, and `14` to view the demo records.
2. Select `4` to make an appointment. Enter customer `1`, artist `1`, and service `1`.
3. Enter year `2026`, month `10`, day `1`, hour `13`, and appointment ID `1`.
4. Select `9` and enter customer `1` to view the booking.
5. Select `11` and enter customer `1` to print the receipt and mark the booking as paid.
6. Select `15` to save and exit.

Use copies of the data files when experimenting, since Save and Exit overwrites them.

## Data Files

Records use `|` as a separator and have no header row.

| File | Format |
| --- | --- |
| `customers.txt` | `id\|name\|phone` |
| `artists.txt` | `id\|name\|contactType\|contactValue` |
| `services.txt` | `id\|name\|price` |
| `appointments.txt` | Intended: `id\|customerId\|artistId\|serviceId\|year\|month\|day\|hour\|status` |

Appointment status is `0` for unpaid and `1` for paid. The current appointment writer omits this final field, and the reader cannot restore the saved records. The repository starts with an empty appointment file.

## Time Complexity

Let `c` be the number of customers, `a` the number of artists, `s` the number of services, and `p` the number of appointments. These estimates cover the main traversals and exclude string processing and file I/O.

| Operation | Worst-case time |
| --- | --- |
| Insert a customer or artist node at the head | `O(1)` after validation |
| Find a customer or artist | `O(c)` or `O(a)` |
| Check or delete a service | `O(s)` |
| Check artist availability | `O(p)` |
| Cancel or find an appointment | `O(p)` |
| Print a customer's or artist's appointments | `O(p)` |
| Calculate and record a customer's payment | `O(p)` |

The linked lists use `O(c + a + p)` space for their nodes. The service array has a fixed capacity of 10.

## Testing and Known Issues

Checks covered loading the demo records, making a booking, rejecting an artist conflict, calculating a `250.00` receipt, rejecting cancellation of a paid appointment, and saving and exiting. A restart check also confirmed the appointment-loading issue.

The source files are kept as provided. These are the main areas that still need work:

- **Appointment files:** The save and load format strings contain eight fields but pass nine values. The reader expects nine conversions, so appointments are not restored after a restart.
- **Deleting linked records:** The functions that check for future paid appointments currently return `0`. Deleting an artist can leave appointments pointing to freed memory, and deleting a service can shift array entries that appointments reference.
- **Editing appointments:** The edit path does not repeat the new-booking date checks. Its conflict scan includes the appointment being edited, and artist ID `0` can lead to a null pointer.
- **Input handling:** Several string reads and copies need tighter length limits. Names read with `fgets()` retain their newline, which can split saved records across lines. Numeric input also needs error handling.
- **Build layout:** Including `.c` files works with the command above, but separate compilation through the headers would make the modules easier to maintain.
