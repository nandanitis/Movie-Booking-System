#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
struct Movie
{
    char seats[10];
    char Name[10];
    char Phone[10];
    char Price[10];
    struct Movie *next;
};
struct Movie *head = NULL;

void insertbeg(struct Movie *newnode)
{
    struct Movie *temp = head;
    if (head == NULL)
    {
        newnode->next = NULL;
        head = newnode;
        return;
    }
    newnode->next = temp;
    head = newnode;
}

void insert_records()
{
    char *filename = "details.txt";
    FILE *fp = fopen(filename, "r");

    char word[50];
    char ch;
    int count = 0;

    struct Movie *newnode;
    newnode = (struct Movie *)malloc(sizeof(struct Movie));

    while (fscanf(fp, "%s%c", word, &ch) != EOF)
    {
        if (count == 0)
        {
            newnode = (struct Movie *)malloc(sizeof(struct Movie));
        }

        count++;
        //printf("%d", count);
        switch (count)
        {
        case 1:
            strcpy(newnode->seats, word);
            //printf("%s", newnode->seats);
            break;

        case 2:
            strcpy(newnode->Name, word);
            //printf("%s", newnode->Name);
            break;

        case 3:
            strcpy(newnode->Phone, word);
            //printf("%s", newnode->Phone);
            break;

        case 4:
            strcpy(newnode->Price, word);
           // printf("%s", newnode->Price);
            insertbeg(newnode);
            count = 0;
            break;
        }
    }

    fclose(fp);
}

int checkforbooked(const char *check)
{
    struct Movie *temp=head;
    while(temp!=NULL)
    {
        if( strcmp(temp->Name,check)==0 )
        {
            printf("\n Hold on.......");
            sleep(2);
            printf(" Congrats %s, You have availed 100 rupees of as you have... ", temp->Name);
            printf("\n Previously Booked %s tickets with phone number %s  ", temp->seats, temp->Phone);
            sleep(3);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

void print_records()
{
    struct Movie *temp=head;
    while(temp!=NULL)
    {
        printf(" Seats:%s ",temp->seats);
        printf(" User_Name:%s ",temp->Name);
        printf(" Mobile_Numb :%s ",temp->Phone);
         printf(" Amount Paid:%s \n",temp->Price);
        temp=temp->next;
    }
}

int edit_file(int lines, int seat)
{
    FILE *frplus = fopen("show1.txt", "r+");
    char ch;
    int count = 0;
    for (int i = 0; i < lines; i++)
    {
        char buffer[100];
        fgets(buffer, 100, frplus);
    }
    if (frplus == NULL)
    {
        printf("can not open target file\n");
        return 1;
    }
    while (1)
    {
        ch = fgetc(frplus);

        if (ch == '_' || ch == '*')
            count++;
        if (ch == '*' && count == seat)
        {
            printf("This seat is already taken");
            exit(0);
        }
        if (ch == '_' && count == seat)
        {
            fseek(frplus, -1, SEEK_CUR);
            fputc('*', frplus);
            fseek(frplus, 0, SEEK_CUR);
            fclose(frplus);
            break;
        }
        if (ch == EOF)
            break;
    }
    fclose(frplus);
    return 0;
}

void display_seats(int lines)
{
    FILE *fptr;
    char c;
    fptr = fopen("show1.txt", "r");
    for (int i = 0; i < lines; i++)
    {
        char buffer[100];
        fgets(buffer, 100, fptr);
    }

    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    c = fgetc(fptr);
    while (c != EOF && c != '=')
    {
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
}

void display_text(int lines)
{
    FILE *fptr;
    char c;
    fptr = fopen("text.txt", "r");
    for (int i = 0; i < lines; i++)
    {
        char buffer[100];
        fgets(buffer, 100, fptr);
    }

    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    c = fgetc(fptr);
    while (c != EOF && c != '=')
    {
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
}

void display_options()
{
    printf("\n--------------------------------\n");
    printf("| WELCOME TO NANDU THEATHRE |\n");
    printf("--------------------------------\n");

    printf("   1.Book Tickets on 12th Feb\n");
    printf("   2.About our Theathre\n");
    printf("   3.Terms and Conditions\n");
    printf("   4.Log out\n");
    printf("    Your choice : ");
    return;
}

void book_movie()
{
    int choice1, movie, time, tickets, price;
    char ch[2];
    printf("\n Which Movie Do You Want to Book : ");
    printf("\n 1.Spiderman No Way Home 2.The Batman 3.Sooryavnashi 4.Hotel Transylvania : ");
    scanf("%d", &movie);
    if (movie < 1 || movie > 4)
    {
        printf("Invalid Option");
        return;
    }
    price = 500 - (50 * (movie + 1));
    printf("\n What Time Do You Want To Book the Show[%d PER HEAD] : ", price);
    printf("\n 1.10AM 2.1PM 3.4PM  4.7PM : ");
    scanf("%d", &time);
    if (time < 1 || time > 4)
    {
        printf("Invalid Option");
        return;
    }
    printf("\n");
    int display = ((movie - 1) * 50) + ((time - 1) * 10);
    display_seats(display);
    printf("\n How many tickets You do Want to Purchase : ");
    scanf("%d", &tickets);
    printf("\n Enter %d ticket places where you want to sit  with spaces : ", tickets);
    for (int i = 0; i < tickets; i++)
    {
        char ch[2];
        int place;
        scanf("%s", ch);
        place = ((int)(ch[0]) - 65) * 10 + ((int)(ch[1] - '0'));
        int flag = edit_file(display, place);
        if (flag == 1)
            exit(0);
    }

    char name1[10], phone1[12];
    printf("\n Enter Your Name : ");
    scanf("%s", name1);
    printf("\n Enter Your Phone No : ");
    scanf("%s", phone1);

    int gross_price = price * tickets;
    int net_price = gross_price + (0.05 * gross_price);
    if(checkforbooked(name1)) net_price=net_price-100;
    printf("\n\n %d Ticket Have Been booked sucessfully ", tickets);
    printf("\n Payable Amount : %d", net_price);
    printf("\n The booking details have been sent to %s, Pay the amount at venue", phone1);
    printf("\n          NO CANCELLATION, NO REFUNDS  ");


    sleep(3);

    FILE *fp3 = fopen("details.txt", "a");
    if (fp3 == NULL)
    {
        printf("Error opening the file %s");
    }
    fprintf(fp3, "%d %s %s %d \n", tickets, name1, phone1, net_price);
    fclose(fp3);

    return;
}

int main()
{
    int choice1, movie, time;
    insert_records();
    display_options();
    scanf("%d", &choice1);

    while (choice1 != 4)
    {
        switch (choice1)
        {
        case 1:
            book_movie();
            break;
        case 2:
            printf("\n\n");
            display_text(0);
            printf("\n\n");
            break;
        case 3:
            printf("\n\n");
            display_text(20);
            printf("\n\n");
            break;
        case 4:
            printf("Thank You See you Again");
            break;

        default:
            printf("Wrong Choice , Please try Again");
            break;
        }
        display_options();
        scanf("%d", &choice1);
    }

    return 0;
}