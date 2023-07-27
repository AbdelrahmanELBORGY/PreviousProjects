#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct //DATE
{
    int month;
    int year;
    char monthname[20];
} date;
typedef struct //BOOKS
{
    char isbn[20];
    char title[100];
    char authname[60];
    int quantity;
    float price;
    date publish;
} book;

typedef struct //USERS
{
    char name[30];
    char pass[30];
} user;
//GLOBAL VARIABLES:
book books[100]; // array contains books

int l,recordedbooks;           // number of stored books

char str[20];    // array to store the ISBN of deleted books

void login()
{
    char username[30], password[30];
    int i = 0, j = 0, flag = 0;
    user user[30]; //array of 30 users
    FILE *f = fopen("credentials.txt", "r");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fscanf(f, "%s\n%s", user[i].name, user[i].pass); //reads the usernames and passwords from credentials.txt and stores them in the array of users
            i++;
        }
    }
    fclose(f);

    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);
        for (j = 0; j < i; j++)
        {
            if (!strcmp(username, user[j].name))
            {
                if (!strcmp(password, user[j].pass))
                {
                    flag = 1;
                    printf("\nLogin successful.\n");
                    break;
                }
                else
                {
                    printf("Wrong username or password.\n");
                    break;
                }
            }
            else if (j == i - 1)
            {
                printf("Wrong username or password.\n");
                break;
            }
        }
        if(flag == 0)
            main();
}

int isbnvalid(char isbn[]) // to validate ISBN is all numbers. Takes ISBN as a string
{
    int i, flag=1;
    if(strlen(isbn) != 13)
        return 0;
    for (i = 0; i < strlen(isbn); i++) // checks each character individually
    {
        if (!(isbn[i] >= '0' && isbn[i] <= '9')) // if the character belongs to the numbers from 0 to 9
            {
                flag =0;
                break;
            }
    }
    return flag; // returns 0 if the ISBN contains a character ,1 if it is all numbers
}
int decimalcheck(char arr[])
{
    int i,flag=1;
    for(i=0;i<strlen(arr);i++)
    {
        if(!((arr[i]>='0'&&arr[i]<='9')||arr[i]=='.'))
        {
            flag=0;
        }
    }
    return flag;
}
    int digitcheck(char arr[])
{
    int i,flag=1;
    for(i=0;i<strlen(arr);i++)
    {
        if(isdigit(arr[i])==0)
        {
            flag=0;
        }
    }
    return flag;
}
void load()
{
    FILE *bookf;
    int i = 0;
    recordedbooks = 0;
    bookf = fopen("books.txt", "r");
    if (bookf == NULL)
    {
        printf("File does not exist \n");
        exit(1);
    }
    do
    {
        fscanf(bookf, "%[^,],%[^,],%[^,],%d,%f,%d-%d\n",
               books[i].isbn,
               books[i].title,
               books[i].authname,
               &books[i].quantity,
               &books[i].price,
               &books[i].publish.month,
               &books[i].publish.year);
        monthname(books[i].publish.month,i);

        i++;
        recordedbooks++;

    }
    while (!feof(bookf));   // while the pointer hasn't reached the end of the file
    l = recordedbooks;
    fclose(bookf);
}

void monthname(int month, int index) // assigns month name to the book depending on the month number
{
    switch (month)
    {
    case 1:
        strcpy(books[index].publish.monthname, "January");
        break;
    case 2:
        strcpy(books[index].publish.monthname, "February");
        break;
    case 3:
        strcpy(books[index].publish.monthname, "March");
        break;
    case 4:
        strcpy(books[index].publish.monthname, "April");
        break;
    case 5:
        strcpy(books[index].publish.monthname, "May");
        break;
    case 6:
        strcpy(books[index].publish.monthname, "June");
        break;
    case 7:
        strcpy(books[index].publish.monthname, "July");
        break;
    case 8:
        strcpy(books[index].publish.monthname, "August");
        break;
    case 9:
        strcpy(books[index].publish.monthname, "September");
        break;
    case 10:
        strcpy(books[index].publish.monthname, "October");
        break;
    case 11:
        strcpy(books[index].publish.monthname, "November");
        break;
    case 12:
        strcpy(books[index].publish.monthname, "December");
        break;
    default:
        strcpy(books[index].publish.monthname, "UNKNOWN MONTH");
        break;
    }
}

void query() // search by ISBN
{
    int i, flag = 0;
    char bnum[20];

    printf("Enter ISBN of The Book You Are looking For: ");
    scanf("%s", bnum);
    for (i = 0; i < l; i++)
    {
        if (strcmp(bnum, books[i].isbn) == 0) // compares the entered ISBN with each ISBN in the book array
        {
            flag = 1; // when found, loop breaks
            break;
        }
    }
    if (flag == 1)
    {

        printf("ISBN: %s\n", books[i].isbn);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].authname);
        printf("Quantity: %d\n", books[i].quantity);
        printf("Price: %.2f$\n", books[i].price);
        printf("Published: %s-%d", books[i].publish.monthname, books[i].publish.year);
    }
    else if (flag == 0)
    {
        printf("BOOK Not FOUND!");
    }
}

void adsearch()
{
    int i, counter = 0, flag = 0;
    char key[50];
    printf("Enter Keyword: ");
    scanf("%s", &key);
    printf("\n*****SEARCH RESULTS******\n");
    for (i = 0; i < l; i++)
    { if (strstr(books[i].title, key) != NULL) // if the keyword found in any title of the stored books
        {
            monthname(books[i].publish.month, i); // assigns the month name to the book
            printf("\nISBN: %s\n", books[i].isbn);
            printf("Title: %s\n", books[i].title);
            printf("Authour: %s\n", books[i].authname);
            printf("Quantity: %d\n", books[i].quantity);
            printf("Price: %.2f$\n", books[i].price);
            printf("Published: %s-%d\n", books[i].publish.monthname, books[i].publish.year);
            counter++;
        }
    }
    if(counter == 0)
    printf("No Matches Found!");
}

void add()
{
    int i, m, q, y;
    float p;
    char month[10], isbn[20], quantity[10], price[10], year[10];
    // each property is stored as string to be able to validate if there are any non integer characters
    printf("*****Add a New Book*****\n");
    getchar();
    do
    {
        printf("ISBN: ");
        gets(isbn);
    }while (isbnvalid(isbn) == 0);   // if the ISBN contains a non integer character, it prompts the user to enter the isbn again

    strcpy(books[l].isbn, isbn); // if the entered isbn has no non-integer characters, it stores the new isbn

    printf("Title: ");
    gets(books[l].title);

    printf("Author Name:");
    gets(books[l].authname);

    do
    {
        printf("New Quantity:");
        gets(quantity);
    } while (digitcheck(quantity) == 0);
    q = atoi(quantity);
    books[l].quantity = q;
    do
    {
        printf("New Price:");
        gets(price);

    }while (decimalcheck(price) == 0);

    p = atoi(price);
    books[l].price = p;
     do
    {
        printf("New Publish Month:");
        gets(month);
    }while (digitcheck(month) == 0);

    m = atoi(month);
    books[l].publish.month = m;
    do
    {
        printf("New Publish Year:");
        gets(year);

    }while (digitcheck(year) == 0);
    y = atoi(year);
    books[l].publish.year = y;
    l++;
    recordedbooks++;
}

void delete()
{
    int i, index, flag =0;
    char booknum[20];
    do
    {
        printf("Enter the ISBN of the book you want to delete: ");
        scanf("%s", booknum);
    }while (isbnvalid ==0);
    strcpy(str, booknum);

    for (i = 0; i < l; i++)
    {
        if (strcmp(booknum, books[i].isbn) == 0) // compares the entered isbn to the isbn of each book
        {
            index = i;
            flag= 1;
            break;
        }
    }

    if (flag == 1)
    {
        for (i = index; i < l; i++) // starts from the index of the specified book
            books[i] = books[i + 1]; // each book carries the data of the book of the next index
    printf("Book Deleted Successfully.\n");
    l--; // decreasing the number of stored books
    }
    else
       if (flag ==0)
            printf("ENTERED BOOK NOT FOUND.");
}

void modify()
{
    int i, m, q, y, flag =0;
    char booknum[20], month[10], quantity[10], price[10], year[10];
    float p;
    do
    {
        printf("Enter the ISBN of the targeted Book:");
        scanf("%s", booknum);
    }while(isbnvalid == 0);

    for (i = 0; i < l; i++)
    {

        if (strcmp(booknum, books[i].isbn) == 0)
        {
            printf("Found!\n");
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        getchar();
    printf("New Title: ");
    gets(books[i].title);
    printf("Author Name: ");
    gets(books[i].authname);

       do
    {
        printf("New Quantity:");
        gets(quantity);
    } while (digitcheck(quantity) == 0);
    q = atoi(quantity);
    books[l].quantity = q;
    do
    {
        printf("New Price:");
        gets(price);

    }while (decimalcheck(quantity) == 0);

    p = atoi(price);
    books[l].price = p;
     do
    {
        printf("New Publish Month:");
        gets(month);
    }while (digitcheck(month) == 0);

    m = atoi(month);
    books[l].publish.month = m;
    do
    {
        printf("New Publish Year:");
        gets(year);

    }while (digitcheck(year) == 0);
    y = atoi(year);
    books[i].publish.year = y;
    }
    else if(flag ==0)
        printf("BOOK NOT FOUND.");
}

void sortbytitle()
{
    int i, j;
    book temp;
    for (i = 1; i < l; i++) // iterations
    {
        for (j = 0; j < l - 1; j++) // swaps
        {
            if (strcmp(books[j].title, books[j + 1].title) > 0) // compares the title of the book of index with the title of the next book
            {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            } // strcmp returns +v if str2 precedes/is before str1 alphabetically
        }
    }
}

void sortbydate()
{
    int i, j;
    book temp;
    for (i = 1; i < l; i++) // iterations
    {
        for (j = 0; j < l - 1; j++) // swaps
        {
            if (books[j].publish.year < books[j + 1].publish.year) // comares the years first
            {

                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
            else if (books[j].publish.year == books[j + 1].publish.year) // if the years are equal, compares the month
            {
                if (books[j].publish.month < books[j + 1].publish.month)
                {
                    temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
}

void sortbyprice()
{
    int i, j;
    book temp;
    for (i = 1; i < l; i++) // iterations
    {
        for (j = 0; j < l - 1; j++) // swaps
        {
            if (books[j].price > books[j + 1].price)
            {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

void PRINT()
{
    int i, choice;
    printf("Choose Sort Type:\n");
    printf("1.Sort By Title\n2.Sort By Date\n3.Sort By Price\n>");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        sortbytitle();
        break;
    case 2:
        sortbydate();
        break;
    case 3:
        sortbyprice();
        break;
    default:
        break;
    }
    for (i = 0; i < l; i++)
    {
        monthname(books[i].publish.month, i);
        printf("\nISBN: %s\n", books[i].isbn);
        printf("Title: %s\n", books[i].title);
        printf("Authour: %s\n", books[i].authname);
        printf("Quantity: %d\n", books[i].quantity);
        printf("Price: %.2f$\n", books[i].price);
        printf("Published: %s-%d\n", books[i].publish.monthname, books[i].publish.year);
    }
}

void save()
{
    FILE *fptr;
    int i;
    fptr = fopen("books.txt", "w");
    for (i = 0; i < l; i++)
    {
        if (strcmp(str, books[i].isbn) != 0) // checks if the isbn is deleted from the array, if yes it will not be printed

            fprintf(fptr, "%s,%s,%s,%d,%.2f,%d-%d\n", books[i].isbn, books[i].title, books[i].authname, books[i].quantity, books[i].price, books[i].publish.month, books[i].publish.year);
    }
    printf("\nData saved successfully.\n");
    fclose(fptr);
}

void menu() // made as a function to be able to call it anytime
{
    int input, input2;
    char userinput[5] = {}, exitinput[5] = {};
    // userinput to take user choice from 1:8 and check it is a number
    //  exit input to take user choice to exit or not and check it is a number
    printf("\n*****MENU*****\n");
    printf("1.ADD\n2.DELETE\n3.MODIFY\n4.SEARCH\n5.ADVANCED SEARCH\n6.PRINT\n7.SAVE\n8.QUIT\n>");
    scanf("%s", &userinput);
    if (atoi(userinput) > 8 || (!atoi(userinput)) || atoi(userinput) < 1)
    {
        printf("ENTER A VALID CHOICE.");
        menu(); // if the user input >8 or <1 or a character it returns him to the login page
    }
    input = atoi(userinput);
    switch (input)
    {
    case 1:
        add();
        menu();
        break;

    case 2:
        delete ();
        menu();
        break;
    case 3:
        modify();
        menu();
        break;
    case 4:
        query();
        menu();
        break;
    case 5:
        adsearch();
        menu();
        break;
    case 6:
        PRINT();
        menu();
        break;
    case 7:
        save();
        menu();
        break;
    case 8:
            printf("All unsaved data will be discarded!\nAre you sure to quit?\n1.Yes\n2.No\n");
        do
        {
            printf(">");
            scanf("%s", &exitinput);
            input = atoi(exitinput);
            switch(input)
            {
            case 1:
                printf("Logged out.");
                exit(1); break;
            case 2:
                menu(); break;
            }

        } while (atoi(exitinput) > 2 || !atoi(exitinput) || atoi(exitinput) < 1);
         break;
    }
}

int main()
{
    int input;
    char userinput[20];
    printf("*****Home Page.*****\n");
    printf("1.Login\n2.Quit\n>");
    scanf("%s", &userinput);
    while (atoi(userinput) > 2 || !atoi(userinput) || atoi(userinput) < 1)
    {
        printf(">");
        scanf("%s", &userinput);
    }
    input = atoi(userinput);
        switch (input)
        {
        case 1:
            login();
            load();
            printf("Available Books: %d", recordedbooks);
            break;

        case 2:
            return 0;
        }
    input = 0;
    menu();
    return 0;
}
