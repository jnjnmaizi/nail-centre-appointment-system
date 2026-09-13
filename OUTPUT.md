# Program Output

A sample run of the Nail Centre Appointment System using the demo data included in this repository. The excerpts below are captured from the program. Repeated menus are omitted, and the entered values are listed separately.

## Main Menu

```text
==================================================
         NAIL CENTRE APPOINTMENT SYSTEM
==================================================
  [1] Add Customer
  [2] Add Artist
  [3] Add Service
  [4] Make Appointment
  [5] Cancel Appointment
  [6] Edit Appointment
  [7] Delete Service
  [8] Delete Artist
  [9] Find Customer Appointments
  [10] Find Artist Appointments
  [11] Process Payment & Print Receipt
  [12] Print All Customers
  [13] Print All Artists
  [14] Print All Services
  [15] Save and Exit
==================================================
Enter your choice:
```

## Customers

Choose `12` to display the customer list.

```text
ID     Name                           Phone
------ ------------------------------ ---------------
2      Sample Customer                0000000000
1      Demo Customer                  0000000000
```

## Artists

Choose `13` to display the artist list.

```text
ID     Name                 Type         Contact
------ -------------------- ------------ ------------------------------
1      Demo Artist          Address      Demo studio
```

## Services

Choose `14` to display the service catalogue.

```text
*** Service List ***
ID: 1 | Name: Spa | Price: 250.00
```

## Booking an Appointment

Choose `4` and enter these values in order:

| Field | Value |
| --- | --- |
| Customer ID | 1 |
| Artist ID | 1 |
| Service ID | 1 |
| Year | 2026 |
| Month | 10 |
| Day | 1 |
| Hour | 13 |
| Appointment ID | 1 |

```text
Appointment created, and added successfully
```

Choose `9`, then enter customer ID `1`, to view the booking:

```text
Appointment ID: 1 | Customer: Demo Customer | Artist: Demo Artist | Service: Spa | Date: 1-Oct-2026 | Time: 13:00 | Status: Unpaid
```

## An Artist Is Already Booked

Choose `4` again. Use customer ID `2` and appointment ID `2`, keeping artist `1`, service `1`, and the same date and hour.

```text
Artist already has an appointment at that time.
```

## Payment Receipt

Choose `11`, then enter customer ID `1`.

```text
***Receipt for Customer: Demo Customer (ID: 1) ===
Unpaid Services:
- Spa: 250.00
Total Due: 250.00
Marking all as paid...
```

The program records the payment locally. Choose `9` and customer ID `1` again to see the updated status:

```text
Appointment ID: 1 | Customer: Demo Customer | Artist: Demo Artist | Service: Spa | Date: 1-Oct-2026 | Time: 13:00 | Status: Paid
```

## Cancelling a Paid Appointment

Choose `5`, then enter appointment ID `1`. Because this appointment is now paid, cancellation is rejected.

```text
Cannot cancel paid appointment or appointment not found.
```

## Saving and Exiting

Choose `15`.

```text
Data saved. Exiting...
```

This is the program's exit message. The current appointment-file bug still prevents saved appointments from being restored on restart; see [Testing and Known Issues](README.md#testing-and-known-issues).
