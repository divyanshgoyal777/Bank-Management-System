#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct account
{
    char name[25];
    long long int accountNumber;
    float accountBalance;
    float loanBalance;
};

struct entry
{
    char senderName[25];
    long long int senderaccountNumber;
    char receiverName[25];
    long long int receiveraccountNumber;
    float amount;
};

struct account accounts[100];
struct entry entries[1000];
int numAccounts = 0;
int numEntries = 0;
int changesMade = 0;

long long int GenerateAccountNumber();
void NewAccount();
void EditAccount(long long int accountNumber);
void AccountDetails(long long int accountNumber);
void NewEntry();
void AllEntries(long long int accountNumber);
void Loan(long long int accountNumber);
void DownloadAccountDetails(long long int accountNumber);
void DownloadEntries(long long int accountNumber);
void DownloadAccountDetailsAndEntries(long long int accountNumber);
int AccountExists(long long int accountNumber);
void SaveAccountsToFile();
void LoadAccountsFromFile();
void SaveEntriesToFile();
void LoadEntriesFromFile();

int main()
{
    srand(time(NULL));
    LoadAccountsFromFile();
    LoadEntriesFromFile();
    int choice;
    int exitFlag = 0;

    while (!exitFlag)
    {
        printf("\033[1;32m\n\t\t\tWelcome to \033[1;33mAPNA \033[1;36mBank\n");
        printf("\033[1;91m\t\t       Made by Divyansh Goyal\n");
        printf("\033[0;36m----------------------------------------------------------------------\n");
        printf("\033[1;34m1. \033[0;34mCreate a New Account\n");
        printf("\033[1;34m2. \033[0;34mEdit an Existing Account\n");
        printf("\033[1;34m3. \033[0;34mView Account Details\n");
        printf("\033[1;34m4. \033[0;34mCreate a New Entry\n");
        printf("\033[1;34m5. \033[0;34mCheck All Entries\n");
        printf("\033[1;34m6. \033[0;34mIssue Loan\n");
        printf("\033[1;34m7. \033[0;34mDownload Account Details\n");
        printf("\033[1;34m8. \033[0;34mDownload Entries\n");
        printf("\033[1;34m9. \033[0;34mDownload Account Details and Entries\n");
        printf("\033[1;34m10. \033[0;34mExit the Program\n");
        printf("\033[1;95mEnter your choice (1-10): \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("You have selected option 1: Create a New Account\n");
            NewAccount();
            SaveAccountsToFile();
            break;

        case 2:
            printf("You have selected option 2: Edit an Existing Account\n");
            long long int accountNumber;
            printf("Please enter your account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                AccountDetails(accountNumber);
                EditAccount(accountNumber);
                SaveAccountsToFile();
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 3:
            printf("You have selected option 3: View Account Details\n");
            printf("Please enter your account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                AccountDetails(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 4:
            printf("You have selected option 4: Create a New Entry\n");
            NewEntry();
            SaveEntriesToFile();
            SaveAccountsToFile();
            break;

        case 5:
            printf("You have selected option 5: Check All Entries\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                AllEntries(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 6:
            printf("You have selected option 6: Loan\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                Loan(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            SaveAccountsToFile();
            break;

        case 7:
            printf("You have selected option 7: Download Account Details\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                DownloadAccountDetails(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 8:
            printf("You have selected option 8: Download Entries\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                DownloadEntries(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 9:
            printf("You have selected option 10: Download Account Details and Entries\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();

            if (AccountExists(accountNumber))
            {
                DownloadAccountDetailsAndEntries(accountNumber);
            }
            else
            {
                printf("\033[1;31mError: Account does not exist!\033[0m\n");
            }
            break;

        case 10:
            printf("You have selected option 10: Exit the Program\nThank you!");

            if (changesMade)
            {
                SaveAccountsToFile();
                SaveEntriesToFile();
            }
            exitFlag = 1;
            break;

        default:
            printf("\033[1;31mError: Invalid choice!\033[0m\n");
            break;
        }
    }

    return 0;
}

long long int GenerateAccountNumber()
{
    long long int accNumber = 0;

    for (int i = 0; i < 10; ++i)
    {
        accNumber = accNumber * 10 + (rand() % 10);
    }
    return accNumber;
}

void NewAccount()
{
    struct account newAccount;
    printf("Enter your name: ");
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    strtok(newAccount.name, "\n");
    printf("Enter initial account balance: ");
    scanf("%f", &newAccount.accountBalance);
    getchar();
    newAccount.accountNumber = GenerateAccountNumber();
    newAccount.loanBalance = 0;
    accounts[numAccounts++] = newAccount;
    printf("\033[1;32mAccount created successfully! Your account number is: %lld\033[0m\n", newAccount.accountNumber);
}

void EditAccount(long long int accountNumber)
{
    for (int i = 0; i < numAccounts; ++i)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            int choice;
            printf("Which detail would you like to change?\n");
            printf("1. Name\n");
            printf("2. Balance\n");
            printf("Enter your choice (1 or 2): ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                printf("Enter new name for your account (Your previous name is %s) - ", accounts[i].name);
                fgets(accounts[i].name, sizeof(accounts[i].name), stdin);
                strtok(accounts[i].name, "\n");
                changesMade = 1;
                break;

            case 2:
                printf("Enter new balance for your account (Your previous balance is %.2f) - ", accounts[i].accountBalance);
                scanf("%f", &accounts[i].accountBalance);
                getchar();
                changesMade = 1;
                break;

            default:
                printf("\033[1;31mError: Invalid choice!\033[0m\n");
                break;
            }
            printf("\033[1;32mAccount updated successfully!\033[0m\n");
            return;
        }
    }
}

void AccountDetails(long long int accountNumber)
{
    for (int i = 0; i < numAccounts; ++i)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            char tempName[25];
            strcpy(tempName, accounts[i].name);
            printf("Account Details: \n");
            printf("Name: %s\n", strtok(tempName, "\n"));
            printf("Account Number: %lld\n", accounts[i].accountNumber);
            printf("Account Balance: %.2f\n", accounts[i].accountBalance);
            printf("Loan Balance: %.2f\n", accounts[i].loanBalance);
            return;
        }
    }
    printf("\033[1;31mError: Invalid choice!\033[0m\n");
}

void NewEntry()
{
    struct entry newEntry;
    int choice;
    int senderIndex = -1, receiverIndex = -1;

    printf("What transaction would you like to perform?\n");
    printf("1. Send money\n");
    printf("2. Receive money\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("Sender's name: ");
        fgets(newEntry.senderName, sizeof(newEntry.senderName), stdin);
        strtok(newEntry.senderName, "\n");

        printf("Sender's account number: ");
        scanf("%lld", &newEntry.senderaccountNumber);
        getchar();

        printf("Receiver's name: ");
        fgets(newEntry.receiverName, sizeof(newEntry.receiverName), stdin);
        strtok(newEntry.receiverName, "\n");

        printf("Receiver's account number: ");
        scanf("%lld", &newEntry.receiveraccountNumber);
        getchar();

        printf("Amount to send: ");
        scanf("%f", &newEntry.amount);
        getchar();

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].accountNumber == newEntry.senderaccountNumber)
            {
                senderIndex = i;
                strcpy(newEntry.senderName, accounts[senderIndex].name);
                break;
            }
        }

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].accountNumber == newEntry.receiveraccountNumber)
            {
                receiverIndex = i;
                strcpy(newEntry.receiverName, accounts[receiverIndex].name);
                break;
            }
        }

        if (senderIndex != -1 && receiverIndex != -1)
        {
            if (newEntry.amount <= accounts[senderIndex].accountBalance)
            {
                accounts[senderIndex].accountBalance -= newEntry.amount;
                accounts[receiverIndex].accountBalance += newEntry.amount;
                printf("\033[1;32mMoney sent successfully!\033[0m\n");
                entries[numEntries++] = newEntry;
            }
            else
            {
                printf("\033[1;31mInsufficient balance to send money!\033[0m\n");
            }
        }
        else
        {
            printf("\033[1;31mSender's or receiver's account not found. Transaction failed!\033[0m\n");
        }
        break;

    case 2:
        printf("Receiver's name: ");
        fgets(newEntry.receiverName, sizeof(newEntry.receiverName), stdin);
        strtok(newEntry.receiverName, "\n");

        printf("Receiver's account number: ");
        scanf("%lld", &newEntry.receiveraccountNumber);
        getchar();

        printf("Sender's name: ");
        fgets(newEntry.senderName, sizeof(newEntry.senderName), stdin);
        strtok(newEntry.senderName, "\n");

        printf("Sender's account number: ");
        scanf("%lld", &newEntry.senderaccountNumber);
        getchar();

        printf("Amount received: ");
        scanf("%f", &newEntry.amount);
        getchar();

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].accountNumber == newEntry.senderaccountNumber)
            {
                senderIndex = i;
                strcpy(newEntry.senderName, accounts[senderIndex].name);
                break;
            }
        }

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].accountNumber == newEntry.receiveraccountNumber)
            {
                receiverIndex = i;
                strcpy(newEntry.receiverName, accounts[receiverIndex].name);
                break;
            }
        }

        if (senderIndex != -1 && receiverIndex != -1)
        {
            if (newEntry.amount <= accounts[senderIndex].accountBalance)
            {
                accounts[receiverIndex].accountBalance += newEntry.amount;
                accounts[senderIndex].accountBalance -= newEntry.amount;
                printf("\033[1;32mMoney received successfully!\033[0m\n");
                entries[numEntries++] = newEntry;
            }
            else
            {
                printf("\033[1;31mInsufficient balance to send money!\033[0m\n");
            }
        }
        else
        {
            printf("\033[1;31mSender's or receiver's account not found. Transaction failed!\033[0m\n");
        }
        break;

    default:
        printf("\033[1;31mError: Invalid choice!\033[0m\n");
        break;
    }
}

void AllEntries(long long int accountNumber)
{
    printf("Entries for account number %lld:\n", accountNumber);
    int found = 0;

    for (int i = 0; i < numEntries; ++i)
    {
        if (entries[i].senderaccountNumber == accountNumber || entries[i].receiveraccountNumber == accountNumber)
        {
            printf("Sender's name: %s\n", entries[i].senderName);
            printf("Receiver's name: %s\n", entries[i].receiverName);
            printf("Amount: %.2f\n", entries[i].amount);
            printf("\n");
            found = 1;
        }
    }
    if (!found)
    {
        printf("\033[1;31mNo entries found for this account.\033[0m\n");
    }
}

void Loan(long long int accountNumber)
{
    int choice;
    printf("Choose a option:\n1. Take loan from bank\n2. Pay previous loan to bank\nEnter your Choice (1 or 2): ");
    scanf("%d", &choice);
    getchar();

    int existingLoan = 0;
    for (int i = 0; i < numAccounts; ++i)
    {
        if (accounts[i].accountNumber == accountNumber && accounts[i].loanBalance > 0)
        {
            existingLoan = 1;
            break;
        }
    }

    if (choice == 1)
    {
        if (existingLoan)
        {
            printf("\033[1;31mYou cannot take a new loan until your previous loan is fully paid off.\033[0m\n");
        }
        else
        {
            float amount;
            char wantLoan;
            printf("You chose option 1: Take a loan from the bank.\n");
            printf("How much money do you need to borrow from the bank? (Loans start from Rs. 1000 to Rs. 1000000) - ");
            scanf("%f", &amount);
            getchar();

            if (amount >= 1000 && amount <= 1000000)
            {
                int loanTermMonths;
                float interestRate;
                if (amount >= 1000 && amount <= 100000)
                {
                    loanTermMonths = 12;
                    interestRate = 0.08;
                }
                else if (amount >= 100001 && amount <= 500000)
                {
                    loanTermMonths = 36;
                    interestRate = 0.12;
                }
                else if (amount >= 500001 && amount <= 1000000)
                {
                    loanTermMonths = 60;
                    interestRate = 0.15;
                }

                float monthlyInterestRate = interestRate / 12;
                float powerFactor = pow((1 + monthlyInterestRate), loanTermMonths);
                float installment = amount * monthlyInterestRate * powerFactor / (powerFactor - 1);

                printf("\nFor a loan of Rs. %.2f:\n", amount);
                printf("Loan term: %d months\n", loanTermMonths);
                printf("Interest rate: %.2f%% per annum\n", interestRate * 100);
                printf("Monthly installment: Rs. %.2f\n\n", installment);
                printf("Would you want to take the loan? (Y for Yes and N for No) - ");
                scanf("%c", &wantLoan);
                getchar();

                if (wantLoan == 'Y' || wantLoan == 'y')
                {
                    for (int i = 0; i < numAccounts; ++i)
                    {
                        if (accounts[i].accountNumber == accountNumber)
                        {
                            accounts[i].loanBalance = amount;
                            accounts[i].accountBalance += accounts[i].loanBalance;
                            printf("\033[1;32mCongratulations, You got the loan!\033[0m\n");
                            printf("\033[1;32mPlease don't be late in paying back the loan amount. Otherwise, you cannot take a new loan until your loan amount is paid.\033[0m\n");
                            for (int i = 0; i < numAccounts; ++i)
                            {
                                if (accounts[i].accountNumber == accountNumber)
                                {
                                    char tempName[25];
                                    strcpy(tempName, accounts[i].name);
                                    printf("Updated Account Details: \n");
                                    printf("Name: %s\n", strtok(tempName, "\n"));
                                    printf("Account Number: %lld\n", accounts[i].accountNumber);
                                    printf("Account Balance: %.2f\n", accounts[i].accountBalance);
                                    printf("Loan Balance: %.2f\n", accounts[i].loanBalance);
                                    return;
                                }
                            }
                            return;
                        }
                    }
                }
                else if (wantLoan == 'N' || wantLoan == 'n')
                {
                    printf("\033[1;31mLoan cancelled.\033[0m\n");
                }
                else
                {
                    printf("\033[1;31mError: Invalid choice!\033[0m\n");
                }
            }

            else if (amount > 1000000)
            {
                printf("\033[1;31mYou need a very high amount. Sorry, we can't provide you with a loan due to the high amount and associated risks.\033[0m\n");
            }
            else if (amount < 1000)
            {
                printf("\033[1;31mThis amount is too low for a loan.\033[0m\n");
            }
            else
            {
                printf("\033[1;31mPlease enter a correct value.\033[0m\n");
            }
        }
    }

    else if (choice == 2)
    {
        int c;
        float payLoan;
        int payerindex = -1;
        printf("You chose option 2: Pay back a previous loan to the bank.\nPlease choose an option:\n1. Pay the full loan amount\n2. Pay some amount of the loan\nEnter your choice (1 or 2): ");
        scanf("%d", &c);
        getchar();

        if (c == 1)
        {
            printf("You chose option 1: Pay loan amount.\n");
            for (int i = 0; i < numAccounts; ++i)
            {
                if (accounts[i].accountNumber == accountNumber)
                {
                    printf("Loan Balance: %.2f\n", accounts[i].loanBalance);
                    payerindex = i;
                }
            }

            printf("Enter the amount for paying loan - ");
            scanf("%f", &payLoan);
            getchar();

            if (payerindex != -1)
            {
                if (accounts[payerindex].loanBalance == payLoan && accounts[payerindex].accountBalance >= payLoan)
                {
                    accounts[payerindex].accountBalance -= payLoan;
                    accounts[payerindex].loanBalance -= payLoan;
                    printf("\033[1;32mAmount paid successfully!\033[0m\n\033[1;32mThank you for your cooperation with our bank.\033[0m\n");
                }
                else
                {
                    printf("\033[1;31mInvalid amount! Please check your loan amount and account balance.\033[0m\n");
                }
            }
        }
        else if (c == 2)
        {
            printf("You chose option 2: Pay some amount of the loan.\n");
            for (int i = 0; i < numAccounts; ++i)
            {
                if (accounts[i].accountNumber == accountNumber)
                {
                    printf("Loan Balance: %.2f\n", accounts[i].loanBalance);
                    payerindex = i;
                }
            }

            printf("Enter the amount for paying loan - ");
            scanf("%f", &payLoan);
            getchar();

            if (payerindex != -1)
            {
                if (accounts[payerindex].loanBalance >= payLoan && accounts[payerindex].accountBalance >= payLoan)
                {
                    accounts[payerindex].accountBalance -= payLoan;
                    accounts[payerindex].loanBalance -= payLoan;
                    printf("\033[1;32mAmount paid successfully!\033[0m\n\033[1;32mThank you for your cooperation with our bank.\033[0m\n");
                    printf("\033[1;32mUpdated Loan amount of your account: %.2f\033[0m\n", accounts[payerindex].loanBalance);
                }
                else
                {
                    printf("\033[1;31mInvalid amount! Please check your loan amount and account balance.\033[0m\n");
                }
            }
        }
        else
        {
            printf("\033[1;31mInvalid option!\033[0m\n");
        }
    }
    else
    {
        printf("\033[1;31mThe loan has been cancelled due to an invalid answer.\033[0m\n");
    }
}

void DownloadAccountDetails(long long int accountNumber)
{
    char choice;
    printf("Do you want to download account details for account %lld? (Y/N): ", accountNumber);
    scanf("%c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        char filename[100];
        sprintf(filename, "account_details_%lld.txt", accountNumber);
        FILE *file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("\033[1;31mError opening file for writing.\033[0m\n");
            return;
        }

        int found = 0;

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].accountNumber == accountNumber)
            {
                char tempName[25];
                strcpy(tempName, accounts[i].name);
                fprintf(file, "Account Details: \n");
                fprintf(file, "Name: %s\n", strtok(tempName, "\n"));
                fprintf(file, "Account Number: %lld\n", accounts[i].accountNumber);
                fprintf(file, "Account Balance: %.2f\n", accounts[i].accountBalance);
                fprintf(file, "Loan Balance: %.2f\n", accounts[i].loanBalance);
                found = 1;
            }
        }
        fclose(file);

        if (found)
        {
            printf("\033[1;32mAccount details downloaded successfully!\033[0m\n");
        }
        else
        {
            printf("\033[1;31mNo details found for this account.\033[0m\n");
        }
    }

    else
    {
        printf("\033[1;31mAccount details download cancelled.\033[0m\n");
    }
}

void DownloadEntries(long long int accountNumber)
{
    char choice;
    printf("Do you want to download all entries for account %lld? (Y/N): ", accountNumber);
    scanf("%c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        char filename[50];
        sprintf(filename, "entries_%lld.txt", accountNumber);
        FILE *file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("\033[1;31mError opening file for writing.\033[0m\n");
            return;
        }

        int found = 0;

        for (int i = 0; i < numEntries; ++i)
        {
            if (entries[i].senderaccountNumber == accountNumber || entries[i].receiveraccountNumber == accountNumber)
            {
                fprintf(file, "Sender's name: %s\n", entries[i].senderName);
                fprintf(file, "Receiver's name: %s\n", entries[i].receiverName);
                fprintf(file, "Amount: %.2f\n", entries[i].amount);
                fprintf(file, "\n");
                found = 1;
            }
        }

        fclose(file);

        if (found)
        {
            printf("\033[1;32mEntries downloaded successfully!\033[0m\n");
        }
        else
        {
            printf("\033[1;31mNo entries found for this account.\033[0m\n");
        }
    }

    else
    {
        printf("\033[1;31mEntries download cancelled.\033[0m\n");
    }
}

void DownloadAccountDetailsAndEntries(long long int accountNumber)
{
    char choice;
    printf("Do you want to download account details and all entries for account %lld? (Y/N): ", accountNumber);
    scanf("%c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        char filename[100];
        sprintf(filename, "account_details_entries_%lld.txt", accountNumber);
        FILE *file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("\033[1;31mError opening file for writing.\033[0m\n");
            return;
        }

        int found = 0;
        for (int i = 0; i < numEntries; ++i)
        {
            if ((accounts[i].accountNumber == accountNumber) && (entries[i].senderaccountNumber == accountNumber || entries[i].receiveraccountNumber == accountNumber))
            {
                char tempName[25];
                strcpy(tempName, accounts[i].name);
                fprintf(file, "Account Details: \n");
                fprintf(file, "Name: %s\n", strtok(tempName, "\n"));
                fprintf(file, "Account Number: %lld\n", accounts[i].accountNumber);
                fprintf(file, "Account Balance: %.2f\n", accounts[i].accountBalance);
                fprintf(file, "Loan Balance: %.2f\n", accounts[i].loanBalance);
                fprintf(file, "\nEntries: \n");

                for (int i = 0; i < numEntries; ++i)
                {
                    if (entries[i].senderaccountNumber == accountNumber || entries[i].receiveraccountNumber == accountNumber)
                    {
                        fprintf(file, "Sender's name: %s\n", entries[i].senderName);
                        fprintf(file, "Receiver's name: %s\n", entries[i].receiverName);
                        fprintf(file, "Amount: %.2f\n", entries[i].amount);
                        fprintf(file, "\n");
                    }
                }
                found = 1;
            }
        }

        fclose(file);

        if (found)
        {
            printf("\033[1;32mAccount details and entries downloaded successfully!\033[0m\n");
        }
        else
        {
            printf("\033[1;31mNo account details and entries found for this account.\033[0m\n");
        }
    }

    else
    {
        printf("\033[1;31mAccount details and entries download cancelled.\033[0m\n");
    }
}

int AccountExists(long long int accountNumber)
{
    for (int i = 0; i < numAccounts; ++i)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            return 1;
        }
    }
    return 0;
}

void SaveAccountsToFile()
{
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL)
    {
        // printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numAccounts; ++i)
    {
        fprintf(file, "%s|%lld|%.2f|%.2f\n", accounts[i].name, accounts[i].accountNumber, accounts[i].accountBalance, accounts[i].loanBalance);
    }

    fclose(file);
}

void LoadAccountsFromFile()
{
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        // printf("Error opening file for reading.\n");
        return;
    }

    char line[100];

    while (numAccounts < 100 && fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, "|");
        strcpy(accounts[numAccounts].name, token);

        token = strtok(NULL, "|");
        sscanf(token, "%lld", &accounts[numAccounts].accountNumber);

        token = strtok(NULL, "|");
        sscanf(token, "%f", &accounts[numAccounts].accountBalance);

        token = strtok(NULL, "|");
        sscanf(token, "%f", &accounts[numAccounts].loanBalance);

        numAccounts++;
    }

    fclose(file);
}

void SaveEntriesToFile()
{
    FILE *file = fopen("entries.txt", "w");

    if (file == NULL)
    {
        // printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numEntries; ++i)
    {
        fprintf(file, "%s|%lld|%s|%lld|%.2f\n", entries[i].senderName, entries[i].senderaccountNumber, entries[i].receiverName, entries[i].receiveraccountNumber, entries[i].amount);
    }

    fclose(file);
}

void LoadEntriesFromFile()
{
    FILE *file = fopen("entries.txt", "r");

    if (file == NULL)
    {
        // printf("Error opening file for reading.\n");
        return;
    }

    char line[1000];

    while (numEntries < 1000 && fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, "|");
        if (token != NULL)
        {
            strcpy(entries[numEntries].senderName, token);
            token = strtok(NULL, "|");
            if (token != NULL)
            {
                entries[numEntries].senderaccountNumber = atoll(token);
                token = strtok(NULL, "|");
                if (token != NULL)
                {
                    strcpy(entries[numEntries].receiverName, token);
                    token = strtok(NULL, "|");
                    if (token != NULL)
                    {
                        entries[numEntries].receiveraccountNumber = atoll(token);
                        token = strtok(NULL, "|");
                        if (token != NULL)
                        {
                            entries[numEntries].amount = atof(token);
                            numEntries++;
                        }
                    }
                }
            }
        }
    }

    fclose(file);
}