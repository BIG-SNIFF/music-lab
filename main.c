#include <stdio.h>

#define MAX 100

struct song {
    char band[100];
    char name[100];
    float price;
    int year;
};

struct song songs[MAX];

int songCount = 0;


void enterData(void)
{
    int number;
    int i;

    printf("\nHow many songs would you like to enter? ");
    scanf("%d", &number);

    if (number > MAX - songCount)
    {
        number = MAX - songCount;
        printf("You can only enter %d more songs.\n", number);
    }

    for (i = 0; i < number; i++)
    {
        printf("\nEnter band or singer name: ");
        scanf(" %99[^\n]", songs[songCount].band);

        printf("Enter song name: ");
        scanf(" %99[^\n]", songs[songCount].name);

        printf("Enter song price: ");
        scanf("%f", &songs[songCount].price);

        printf("Enter release year: ");
        scanf("%d", &songs[songCount].year);

        songCount++;

        printf("\nSong added successfully!\n");
    }
}

void saveData(void)
{
    FILE *file;
    int i;

    file = fopen("songs.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < songCount; i++)
    {
        fprintf(file, "%s|%s|%.2f|%d\n",
                songs[i].band,
                songs[i].name,
                songs[i].price,
                songs[i].year);
    }

    fclose(file);

    printf("\nSongs successfully saved to file!\n");
}

void readData(void)
{
    FILE *file;

    file = fopen("songs.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    songCount = 0;

    while (songCount < MAX &&
           fscanf(file, " %99[^|]|%99[^|]|%f|%d",
                  songs[songCount].band,
                  songs[songCount].name,
                  &songs[songCount].price,
                  &songs[songCount].year) == 4)
    {
        songCount++;
    }

    fclose(file);

    printf("\n%d songs successfully read from file!\n", songCount);
}


void sortSongs(void)
{
    int i, j;
    struct song temp;

    for (i = 0; i < songCount - 1; i++)
    {
        for (j = 0; j < songCount - 1 - i; j++)
        {
            if (songs[j].year < songs[j + 1].year)
            {
                temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}

void printCatalogue(void)
{
    int i;

    if (songCount == 0)
    {
        printf("\nNo songs available. Please enter or read songs first.\n");
        return;
    }

    sortSongs();

    printf("\n===== SONG CATALOGUE =====\n");

    for (i = 0; i < songCount; i++)
    {
        printf("\nSong %d\n", i + 1);
        printf("Band/Singer: %s\n", songs[i].band);
        printf("Song Name: %s\n", songs[i].name);
        printf("Price: £%.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }
}

int main(void)
{
    int choice;

    do
    {
        printf("\n===== SONG CATALOGUE =====\n");
        printf("1. Enter data\n");
        printf("2. Save data to file\n");
        printf("3. Read data from file\n");
        printf("4. Print out the catalogue to screen\n");
        printf("5. Exit Program\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Decide which function to execute
        switch (choice)
        {
            case 1:
                enterData();
                break;

            case 2:
                saveData();
                break;

            case 3:
                readData();
                break;

            case 4:
                printCatalogue();
                break;

            case 5:
                printf("\nYou selected Exit Program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}