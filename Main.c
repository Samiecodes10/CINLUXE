
#include <stdio.h>

struct Movie {
    char name[30];
    int price;
    int seats[3][5];
};

struct Movie movies[3] = {
    {"Interstellar", 200, {{0}}},
    {"Inception", 180, {{0}}},
    {"Avengers", 250, {{0}}}
};

int bookingID = 1001;

// Display available movies
void displayMovies() {
    int i;

    printf("\n================================");
    printf("\n       NOW SHOWING MOVIES");
    printf("\n================================\n");

    for (i = 0; i < 3; i++) {
        printf("%d. %s - Rs.%d per ticket\n",
               i + 1, movies[i].name, movies[i].price);
    }

    printf("\nEnjoy choosing your movie!\n");
}

// Display seat layout
void displaySeats(int m) {
    int i, j;

    printf("\n--------- SEAT LAYOUT ---------\n");
    printf("O = Available   X = Booked\n\n");
    printf("     1  2  3  4  5\n");

    for (i = 0; i < 3; i++) {
        printf(" %c   ", 'A' + i);

        for (j = 0; j < 5; j++) {
            if (movies[m].seats[i][j] == 0)
                printf(" O ");
            else
                printf(" X ");
        }
        printf("\n");
    }
}

// Book movie tickets
void bookTickets() {
    char customer[50];
    char bookedSeats[15][4];
    char seatRow;
    int m, ticketCount, total = 0;
    int i, row, col;

    displayMovies();

    printf("\nPlease select your movie: ");
    scanf("%d", &m);

    if (m < 1 || m > 3) {
        printf("\nOops! Invalid movie selection.\n");
        printf("Please try again. Thank you!\n");
        return;
    }

    m--;

    printf("\nGreat choice! You selected %s.\n",
           movies[m].name);

    printf("\nMay I know your name? ");
    scanf(" %49[^\n]", customer);

    printf("\nWelcome, %s! Let's book your seats.\n",
           customer);

    printf("\nHow many tickets would you like? (1-15): ");
    scanf("%d", &ticketCount);

    if (ticketCount < 1 || ticketCount > 15) {
        printf("\nSorry! Please enter a valid ticket count.\n");
        return;
    }

    for (i = 0; i < ticketCount; i++) {

        displaySeats(m);

        printf("\nSelect seat row (A-C): ");
        scanf(" %c", &seatRow);

        printf("Select seat number (1-5): ");
        scanf("%d", &col);

        if (seatRow >= 'a' && seatRow <= 'c')
            seatRow = seatRow - 32;

        row = seatRow - 'A';

        if (row < 0 || row >= 3 || col < 1 || col > 5) {
            printf("\nInvalid seat! Please choose again.\n");
            i--;
            continue;
        }

        if (movies[m].seats[row][col - 1] == 1) {
            printf("\nSorry! This seat is already booked.\n");
            printf("Please select another seat.\n");
            i--;
            continue;
        }

        movies[m].seats[row][col - 1] = 1;

        sprintf(bookedSeats[i], "%c%d", seatRow, col);

        printf("\nWonderful! Seat %s selected successfully.\n",
               bookedSeats[i]);
    }

    total = ticketCount * movies[m].price;

    printf("\nAll seats selected successfully!\n");
    printf("Your booking is being confirmed...\n");

    // Display final ticket
    printf("\n================================");
    printf("\n       BOOKING CONFIRMED");
    printf("\n================================\n");

    printf("Booking ID    : %d\n", bookingID);
    printf("Customer Name : %s\n", customer);
    printf("Movie Name    : %s\n", movies[m].name);

    printf("Booked Seats  : ");

    for (i = 0; i < ticketCount; i++) {
        printf("%s ", bookedSeats[i]);
    }

    printf("\nTotal Tickets : %d\n", ticketCount);
    printf("Ticket Price  : Rs.%d\n", movies[m].price);
    printf("Total Amount  : Rs.%d\n", total);

    printf("\nThank you for booking with us, %s!\n", customer);
    printf("We hope you have a wonderful movie experience!\n");
    printf("Enjoy your show! Have a great day!\n");
    printf("================================\n");

    bookingID++;
}

// Main function
int main() {
    int choice, m;

    printf("\n********************************");
    printf("\n  WELCOME TO MOVIE TICKET BOOKING");
    printf("\n********************************");

    do {
        printf("\n\n========= MAIN MENU =========");
        printf("\n1. View Available Movies");
        printf("\n2. Book Movie Tickets");
        printf("\n3. View Seat Layout");
        printf("\n4. Exit");
        printf("\n=============================");

        printf("\nWhat would you like to do today? ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayMovies();
                break;

            case 2:
                bookTickets();
                break;

            case 3:
                displayMovies();

                printf("\nSelect movie number to view seats: ");
                scanf("%d", &m);

                if (m >= 1 && m <= 3) {
                    printf("\nHere is the seat layout for %s.\n",
                           movies[m - 1].name);
                    displaySeats(m - 1);
                }
                else {
                    printf("\nOops! Invalid movie selection.\n");
                }
                break;

            case 4:
                printf("\nThank you for visiting our cinema!\n");
                printf("We look forward to seeing you again.\n");
                printf("Have a wonderful day!\n");
                break;

            default:
                printf("\nSorry, that option is not available.\n");
                printf("Please select a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}

