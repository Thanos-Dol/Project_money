#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define day_std 30
/*
void setright(FILE *file) {

    while(1) {
        if (fgetc(file) != ':') break;
    }
}
*/

typedef struct{
    unsigned short int balance;
    unsigned short int month_salary;
    unsigned short int expenses;
    unsigned short int year_expenses[3];
    unsigned short int month_expenses[3][12];
    unsigned short int week_expenses[3][12][4];
    unsigned short int day_expenses[3][12][31];
}catalog;

int main() {

    char stay = 1, choice;
    short int  y, m, d, current_day, current_month, current_year, save_dif;
    unsigned short int cash_to_move, temp_day, temp_month, temp_year;
    double loss, save_percentage;
    FILE *monet;
    catalog ledger;

    //read file
    if ((monet = fopen("monet.txt", "r")) != NULL) {

        while(1) {
            if (fgetc(monet) == ':') break;
        }
        fscanf(monet, " %hu", &ledger.balance);

        while(1) {
            if (fgetc(monet) == ':') break;
        }
        fscanf(monet, " %hu", &ledger.expenses);

        while(1) {
            if (fgetc(monet) == ':') break;
        }
        fscanf(monet, " %hu", &ledger.month_salary);

        for (y = 0; y < 3; y++) {

            while(1) {
                if (fgetc(monet) == ':') break;
            }

            fscanf(monet, " %hu", &ledger.year_expenses[y]);

            for (m = 0; m < 12; m++) {

                while(1) {
                    if (fgetc(monet) == ':') break;
                }

                fscanf(monet, " %hu", &ledger.month_expenses[y][m]);

                for (d = 0; d < 31; d++) {

                    while(1) {
                        if (fgetc(monet) == ':' || feof(monet)) break;
                    }

                    fscanf(monet, " %hu", &ledger.day_expenses[y][m][d]);

                    if (d > 26) {

                        if ( ((y + 2019) % 4) && (m == 1) && (d == 27))
                            break;
                        else
                        if ( !((y + 2019) % 4) && (m == 1) && (d == 28))
                            break;
                        else
                        if (((m == 3) || (m == 5) || (m == 8) || (m == 10)) && (d == 29))
                            break;
                    }
                }
            }
        }

        fclose(monet);

    } else puts("Cannot open file!");

    //get date
    printf("Give current date in a dd/mm/yyyy format \nDate: ");
    scanf("%hd/%hd/%hd", &current_day, &current_month, &current_year);
    fseek(stdin, 0, SEEK_END);
    system("cls");

    current_day -= 1;
    current_month -= 1;
    current_year -= 2019;

    //main program
    while(stay)
    {
        printf("1) Reset \n2) Give more expenses \n3) See current balance \n4) Percentage of monthly loss \n5) See loss of month \n6) Show monthly savings \n7) Exit \n\nOption: ");
        choice = getchar();
        fseek(stdin,0,SEEK_END);
        system("cls");

        switch(choice) {

            case '1':

                printf("1) Reset balance \n2) Reset monthly payment \n3) Reset any day \n4) Reset any month \n5) Reset any year \n\nOption: ");
                choice = getchar();
                fseek(stdin, 0, SEEK_END);

                switch(choice) {

                    case '1':

                        printf("Give new balance: ");
                        scanf("%hu", &ledger.balance);
                        system("cls");

                        break;

                    case '2':

                        printf("Give new monthly payment: ");
                        scanf("%hu", &ledger.month_salary);
                        system("pause");

                        break;

                    case '3':

                        printf("Give the desired day in a dd/mm/yyyy format \nDate: ");
                        scanf("%hd/%hd/%hd", &d, &m, &y);

                        d -= 1;
                        m -= 1;
                        y -= 2019;

                        printf("Give new day expenses: ");
                        scanf("%hu", &ledger.day_expenses[y][m][d]);

                        fseek(stdin, 0, SEEK_END);
                        system("cls");

                        break;

                    case '4':

                        printf("Give the desired month in a mm/yyyy format \nDate: ");
                        scanf("%hd/%hd", &m, &y);

                        m -= 1;
                        y -= 2019;

                        printf("Give new day expenses: ");
                        scanf("%hu", &ledger.month_expenses[y][m]);

                        fseek(stdin, 0, SEEK_END);
                        system("cls");

                        break;

                    case '5':

                        printf("Give the desired year in a yyyy format \nDate: ");
                        scanf("%hd", &y);

                        y -= 2019;

                        printf("Give new day expenses: ");
                        scanf("%hu", &ledger.year_expenses[y]);

                        fseek(stdin, 0, SEEK_END);
                        system("cls");

                        break;

                    default:
                        puts("Wrong Input!");
                        system("pause");
                        system("cls");
                }
                fseek(stdin, 0, SEEK_END);
                break;

            case '2':
                printf("Insert amount of expenses: ");
                scanf("%hu", &cash_to_move);
                fseek(stdin, 0, SEEK_END);

                ledger.day_expenses[current_year][current_month][current_day] += cash_to_move;
                ledger.month_expenses[current_year][current_month] += cash_to_move;
                ledger.year_expenses[current_year] += cash_to_move;
                ledger.expenses += cash_to_move;
                ledger.balance -= cash_to_move;

                system("cls");
                break;

            case '3':
                printf("Current balance: %hu \n\n", ledger.balance);
                system("pause");
                system("cls");
                break;

            case '4':
                loss = (((double) (ledger.month_expenses[current_year][current_month])) / ((double) (ledger.month_salary))) * 100;
                printf("monthly take: %hu \nMonthy loss: %hd \npercentage: %.2lf%% \n\n", ledger.month_salary, ledger.month_expenses[current_year][current_month], loss);
                system("pause");
                system("cls");
                break;

            case '5':

                printf("Select month: ");
                scanf("%hu", &temp_month);
                fseek(stdin, 0, SEEK_END);

                temp_month -= 1;

                printf("Selected month expected: %hu", ledger.month_expenses[current_year][temp_month]);
                system("pause");
                break;

            case '6':

                printf("Select month and year (mm/yyyy): ");
                scanf("%hd/%hd", &temp_month, &temp_year);
                fseek(stdin, 0, SEEK_END);

                temp_month -= 1;
                temp_year -= 2019;

                save_dif = (short int) (ledger.month_salary) - (short int) (ledger.month_expenses[temp_year][temp_month]);
                save_percentage = ((double) (save_dif) / (double) (ledger.month_salary)) * 100;
                printf("Selected month's savings: %hu (%.2lf%%)\n\n", save_dif, save_percentage);
                system("pause");

                break;

            case '7':
                stay = 0;
                break;

            default:
                puts("Wrong choice!\n\n");
                system("pause");
                system("cls");
        }
        system("cls");
    }

    //update file
    if ((monet = fopen("monet.txt", "w")) != NULL)
    {
        fprintf(monet, "Overall Balance: %hu\nOverall Expenses: %hu\nMontly Salary: %hu\n", ledger.balance, ledger.expenses, ledger.month_salary);

        for (y = 0; y < 3; y++) {

            fprintf(monet, "year %d: %hu\n", y + 2019, ledger.year_expenses[y]);

            for (m = 0; m < 12; m++) {

                fprintf(monet, "month %d: %hu\n", m + 1, ledger.month_expenses[y][m]);

                for (d = 0; d < 31; d++) {

                    fprintf(monet, "day %d: %hu\n", d + 1, ledger.day_expenses[y][m][d]);

                    if (d > 26) {

                        if ( ((y + 2019) % 4) && (m == 1) && (d == 27))
                            break;
                        else
                        if ( !((y + 2019) % 4) && (m == 1) && (d == 28))
                            break;
                        else
                        if (((m == 3) || (m == 5) || (m == 8) || (m == 10)) && (d == 29))
                            break;
                    }
                }
            }
        }

        fclose(monet);

    } else puts("File not properly updated!");

    return 0;
}
