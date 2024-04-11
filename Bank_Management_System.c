#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct account
{
    char name[25];
    long long int accountNumber;
    float accountBalance;
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
void DownloadEntries(long long int accountNumber);
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
        printf("\n1. Create a New Account\n");
        printf("2. Edit an Existing Account\n");
        printf("3. View Account Details\n");
        printf("4. Create a New Entry\n");
        printf("5. Check All Entries\n");
        printf("6. Download Entries\n");
        printf("7. Exit the Program\n");
        printf("Enter your choice (1-7): ");
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
                printf("Error: Account does not exist!\n");
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
                printf("Error: Account does not exist!\n");
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
                printf("Error: Account does not exist!\n");
            }
            break;

        case 6:
            printf("You have selected option 6: Download Entries\n");
            printf("Please enter the account number: ");
            scanf("%lld", &accountNumber);
            getchar();
            if (AccountExists(accountNumber))
            {
                DownloadEntries(accountNumber);
            }
            else
            {
                printf("Error: Account does not exist!\n");
            }
            break;

        case 7:
            printf("You have selected option 7: Exit the Program\n");
            if (changesMade)
            {
                SaveAccountsToFile();
                SaveEntriesToFile();
            }
            exitFlag = 1;
            break;

        default:
            printf("Error: Invalid choice!\n");
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
    accounts[numAccounts++] = newAccount;

    printf("Account created successfully! Your account number is: %lld\n", newAccount.accountNumber);
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
                printf("Invalid Choice!\n");
                break;
            }
            printf("Account updated successfully!\n");
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
            return;
        }
    }
    printf("Account not found!\n");
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
                printf("Money sent successfully!\n");
                entries[numEntries++] = newEntry;
            }
            else
            {
                printf("Insufficient balance to send money!\n");
            }
        }
        else
        {
            printf("Sender's or receiver's account not found. Transaction failed!\n");
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
                printf("Money received successfully!\n");
                entries[numEntries++] = newEntry;
            }
            else
            {
                printf("Insufficient balance to send money!\n");
            }
        }
        else
        {
            printf("Sender's or receiver's account not found. Transaction failed!\n");
        }
        break;

    default:
        printf("Invalid choice!\n");
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
        printf("No entries found for this account.\n");
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
            printf("Error opening file for writing.\n");
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
            printf("Entries downloaded successfully!\n");
        }
        else
        {
            printf("No entries found for this account.\n");
        }
    }
    else
    {
        printf("Entries download cancelled.\n");
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
        fprintf(file, "%s|%lld|%.2f\n", accounts[i].name, accounts[i].accountNumber, accounts[i].accountBalance);
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
