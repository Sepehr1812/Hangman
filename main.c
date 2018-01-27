//***                     Hangman                     ***//
//**         C Programming    |    Dr. Bakhshi         **//
//*                   Sepehr Akhoundi                   *//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

//Colors
#define backcolor 240 //back white, black
#define watercolor 51 //lite aqua
#define heartcolor 252 //lite red
#define menucolor 113 //back gray, dark blue
#define bluemodecolor 185 //back sky blue, blue
#define bluemodeheartcolor 188 //back sky blue, lite red

char gamer_name[20];
int coins, sub_coin;
char guess_buff[58]; //to avoid repeating letters.
int q, zz; //They help to save scores.

int let_G, t_letter= 4, use_I, do_B, B_time; //for market


struct data_to_save
{
   char name[20];

   int scores[26]; //for different topics
   int market[5]; //0: Green, 1: Red, 2: Gill, 3: Hour, 4: Blue.
   int t_coins;
};

typedef struct data_to_save dts;

dts data;

void get_id(); void menu(); void new_game(); void resume_game(); void tops(char a); void sort(); void show_coins(); void check_name(); void add_topic();void market(); void Blue_Mode();
void check_coin(); void build_list(); void choosing_word(); void gaming(); int check_letter(); int check_repeat(char a); void saving(); void drowning(); void heart_drowning(); void water_drowning();

//START beginning*******************************************************
void beginning()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    int i;
    for(i=0; i < 10; i++)
    {
        SetConsoleTextAttribute(hConsole, 223); //lite pink
        system("cls");
        printf("WELCOME to HANGMAN ON CONSOL!!!\n");
        Sleep(100);

        SetConsoleTextAttribute(hConsole, 253); //change
        system("cls");
        printf("WELCOME to HANGMAN ON CONSOL!!!\n");
        Sleep(100);
    }

    SetConsoleTextAttribute(hConsole, menucolor);

    Sleep(2000);
    system("cls");

    get_id();

    strcpy(data.name, gamer_name); //for saving

    system("cls");

    menu();
}

void menu()
{
    int w;

    printf("WELCOME '%s'!\nChoose what do you want to do:\n", gamer_name);
    printf("\n[1] Start a new game,\nor\n[2] Resume last game,\n\n\n[3] Top Players,\n\n[4] Add Topic,\n\n\n[0] Quit.\n\n");

    scanf("%d", &w);
    while(1) //checking wrong input.
    {
        if(w >= 0 && w <= 4)
            break;
        else
            printf("Please enter a defined option: ");

        scanf("%d", &w);
    }

    system("cls");

    if(w == 1)
    {
        check_name();

        int k;
        for(k=0; k < 26; k++)
            data.scores[k]= 0;
        for(k=0; k < 5; k++)
            data.market[k]= 0;

        new_game();
    }

    else if(w == 2)
        resume_game();

    else if( w == 3)
        tops('m');

    else if(w == 4)
        add_topic();

    else if(w == 0)
    {
        system("cls");
        printf("Come Back Soon ;(\nBYE!");
        Sleep(1500);
        exit(0);
    }
}

void new_game()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    if(do_B != 1)
    {
        SetConsoleTextAttribute(hConsole, menucolor);
        system("cls");
    }

    FILE *sub_name;

    sub_name= fopen("../TOPICS/AVAILABLE_TOPICS.txt", "r");
    if(sub_name == NULL)
    {
        printf("\nSomething goes wrong... :(\n");
        exit(-1);
    }

    char sub[50];
    int c, i;

    use_I= 0; //for Gill
    t_letter= 4; //for Hourglass

    printf("Choose one of the below topics:\n\n");

    for(c=97; fscanf(sub_name, "%s", sub) != EOF; c++)
    {
        printf("(%c) ", c);
        for(i=0; sub[i] != '.'; i++) //to print without ".txt" .
            printf("%c", sub[i]);

        printf("\n");
    }
    printf("\n");

    if(do_B != 1) //normal
    {
        printf("\n(1) Show Records, Things & Coins\n(2) Top players\n\n");
        SetConsoleTextAttribute(hConsole, 118); //gray back, golden
        printf("(3) Golden Market");
        SetConsoleTextAttribute(hConsole, 123); //gray back, blue
        printf("\n\n(4) Be Blue!");
        SetConsoleTextAttribute(hConsole, menucolor);
        printf("\n\n(0) Quit\n\n");
    }

    char w, b;
    scanf("%c", &b);
    scanf("%c", &w);
    while(1) //checking wrong input.
    {
        if((w >= 97 && w < c))
            break;
        else if(do_B != 1) //normal
        {
            if(w == '0' || w == '1' || w == '2' || w == '3' || w == '4')
                break;
        }
        else
            printf("Please enter a defined option: ");

        scanf("%c", &b); //to not repeat last printf two times.
        scanf("%c", &w);
    }

    system("cls");

    if(w != '0' && w != '1' && w != '2' && w != '3' && w != '4')
    {
        rewind(sub_name);
        for(i=0; i <= w-97; i++)
            fscanf(sub_name, "%s", sub);

        q= i-1; //It helps to save.

        fclose(sub_name);

        build_list(sub);
    }

    else if(w == '0')
    {
        fclose(sub_name);
        printf("Come Back Soon ;(\nBYE!");
        Sleep(1500);
        exit(0);
    }

    else if(w == '1')
        show_coins();

    else if(w == '2')
        tops('n');

    else if(w == '3')
        market();

    else if(w == '4')
        Blue_Mode();
}

void resume_game()
{
    FILE *account;

    char save_buff[100]= "../Scores/" ; //to add the address.
    strcat(save_buff, gamer_name);
    char add_bin[]= ".bin";
    strcat(save_buff, add_bin);

    account= fopen(save_buff, "rb");
    if(account == NULL)
    {
        printf("There is no account named '%s' .", gamer_name);
        fclose(account);
        Sleep(1500);
        system("cls");
        menu();
    }

    zz= 1; //It helps saving function.

    fread(&data, sizeof(data), 1, account);

    strcpy(gamer_name, data.name);
    coins= data.t_coins;

    fclose(account);

    new_game();
}
//END beginning******************************************************

void show_coins()
{
    FILE *sub_name;

    sub_name= fopen("../TOPICS/AVAILABLE_TOPICS.txt", "r");

    char sub[50];
    int i, j;

    printf("Your Name: %s\n\n\nYour Records:\n\n", gamer_name);
    for(j=0; fscanf(sub_name, "%s", sub) != EOF; j++)
    {
        for(i=0; sub[i] != '.'; i++) //to print without ".txt" .
            printf("%c", sub[i]);
        printf(": %d", data.scores[j]);

        printf("\n");
    }

    printf("\n\nThings:\n\nGreen Sheet: %d\nRed Diamond: %d\nGill: %d\nHourglass: %d\nBlue Card: %d", data.market[0], data.market[1], data.market[2], data.market[3], data.market[4]);

    printf("\n\n\nTotal Coins: %d\n", coins);

    system("timeout /t 30");

    system("cls");
    new_game();
}

void check_name() //to avoid overwriting.
{
    FILE *account;

    char save_buff[100]= "../Scores/" ; //to add the address.
    strcat(save_buff, gamer_name);
    char add_bin[]= ".bin";
    strcat(save_buff, add_bin);

    account= fopen(save_buff, "rb");
    if(account != NULL) //When there is an similar account.
    {
        printf("There is an account named '%s' .\nYou can't start a new game.\n\nChoose:\n\n  [1]Resume last game,\n\nor\n\n  [0]Quit and then come back with a new name.\n", gamer_name);

        char w, b;
        scanf("%c", &b);
        scanf("%c", &w);
        while(1) //checking wrong input.
        {
            if(w == '1' || w == '0')
                break;
            else
                printf("Please enter a defined option: ");

            scanf("%c", &b);
            scanf("%c", &w);
        }

        system("cls");
        fclose(account);

        if(w == '1')
            resume_game();
        else if(w == '0')
            exit(0);
    }
}

void get_id() //to get and check appropriate name id.
{
    printf("Please enter your name: ");
    gets(gamer_name);

    int i;
    for(i=0; gamer_name[i] != '\0'; i++)
    {
        if((gamer_name[i] >= 65 && gamer_name[i] <= 90) || (gamer_name[i] >= 97 && gamer_name[i] <= 122) || (gamer_name[i] >=49 && gamer_name[i] <= 57) || gamer_name[i] == 95)
            continue;
        else
        {
            printf("\nPlease just use alphabetical characters or numbers or '_'.\n");
            get_id();
        }
    }
}

//START tops*********************************************************
void tops(char s) //s: n->new game, m->menu.
{
    int score[1000]= {0}, index[1000];
    char name[20];
    FILE *infos, *infon;

    infos= fopen("../Scores/SAVE_INFO_S.bins", "rb");
    infon= fopen("../Scores/SAVE_INFO_N.txt", "r");
    if(infos == NULL || infon == NULL)
    {
        printf("\nSomething goes wrong... :(\n");
        fclose(infos); fclose(infon);
        Sleep(3000);
        system("cls");

        if(s == 'n')
            new_game();
        else if(s == 'm')
            menu();
    }

    int i=0, j, k;
    while(1)
    {
        if(fread(&score[i], sizeof(int), 1, infos) < 1)
            break;
        i++;
    }

    for(j=0; j<i; j++)
        index[j]= j;

    sort(score, index, i);

    printf("Top Players:\n\n");

    for(k=0; k < 10; k++)
    {
        if(score[k] == 0)
            break;

        for(j=0; j <= index[k]; j++)
            fscanf(infon, "%s", name);

        printf("[%d] %s: %d\n", k+1, name, score[k]);

        fseek(infon, 0, SEEK_SET);
    }

    system("timeout /t 30");

    fclose(infon); fclose(infos);
    system("cls");

    if(s == 'n')
        new_game();
    else if(s == 'm')
        menu();
}

void swap(int arr[], int i, int j) //It help sort function.
{
    int temp;

    temp= arr[i];
    arr[i]= arr[j];
    arr[j]= temp;
}

void sort(int arr[], int index[], int l) //It helps tops function.
{
    int i, k;
    for(k=0; k < l-1; k++)
    {
        for(i=k+1; i < l; i++)
        {
            if(arr[i] > arr[k])
            {
                swap(arr, i, k);
                swap(index, i, k);
            }
        }
    }
}
//END tops***********************************************************

void add_topic()
{
    char name[50], address[65]= "../TOPICS/" , words[2500], b;
    FILE *list, *new_topic;

    printf("Enter topic name: ");
    scanf("%c", &b);
    gets(name);

    strcat(address, name);
    strcat(address, ".txt");
    printf("%s\n", address);

    list= fopen("../TOPICS/AVAILABLE_TOPICS.txt", "a");
    new_topic= fopen(address, "w");
    if(list == NULL || new_topic == NULL)
    {
        printf("\n\nSomething goes wrong... :(\n");
        fclose(list); fclose(new_topic);
        Sleep(3000);
        system("cls");
        menu();
    }

    fprintf(list, "\n%s%s", name, ".txt"); //in list.

    printf("\n\nNow, enter words you want to add with a space between them (up to 50 words), then press enter:\n");
    gets(words);

    fprintf(new_topic, "%s", words);

    printf("\n\nAdded Successfully!");
    Sleep(2000);
    system("cls");

    fclose(list); fclose(new_topic);

    menu();
}

//START market*******************************************************
void market()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 110); //gold
    system("cls");

    printf("Welcome to Golden Market!\n\n\nTotal Coins: %d\n\n\n\nThings to buy:\n\n", coins);
    printf("(a) Green Sheet     ||     35 Coins\n     %c When you have just one heart, you can discover one letter reminds.\n\n", 16); //due to ASCII
    printf("(b) Red Diamond     ||     50 Coins\n     %c Whenever you want, you can receive an offered letter. It might be correct or not.\n\n", 16);
    printf("(c) Gill            ||     220 Coins\n     %c When you have just one heart, you can try 3 more letters. It's for one topic and for one time; and you can't use Green Sheet or Red Diamond with Gill.\n\n", 16);
    printf("(d) Hourglass       ||     400 Coins\n     %c Time will be doubled for one topic and for one time. (4 seconds %c 8 seconds)\n\n", 16, 26);
    printf("(e) Blue Card       ||     4000 Coins\n     %c By this, you can play in ", 16);
    SetConsoleTextAttribute(hConsole, 107); //sky blue
    printf("Blue Mode");
    SetConsoleTextAttribute(hConsole, 110);
    printf(" for one time! You can't use any other things in ");
    SetConsoleTextAttribute(hConsole, 107);
    printf("Blue Mode");
    SetConsoleTextAttribute(hConsole, 110);
    printf(".\n\n");

    printf("\n\n(1) Back\n\n");

    char w, b;
    scanf("%c", &b);
    scanf("%c", &w);
    while(1) //checking wrong input.
    {
        if((w >= 97 && w <= 101) || w == '1')
            break;
        else
            printf("Please enter a defined option: ");

        scanf("%c", &b); //to not repeat last printf two times.
        scanf("%c", &w);
    }

    if(w == '1')
    {
        SetConsoleTextAttribute(hConsole, menucolor);
        system("cls");
        new_game();
    }

    else if(w == 'a')
    {
        check_coin(35);
        coins-= 35;
        data.market[0]++;
    }
    else if(w == 'b')
    {
        check_coin(50);
        coins-= 50;
        data.market[1]++;
    }
    else if(w == 'c')
    {
        check_coin(220);
        coins-= 220;
        data.market[2]++;
    }
    else if(w == 'd')
    {
        check_coin(400);
        coins-= 400;
        data.market[3]++;
    }
    else if(w == 'e')
    {
        check_coin(4000);
        coins-= 4000;
        data.market[4]++;
    }

    printf("Done!");
    Sleep(1500);
    market();
}

void check_coin(int x)
{
    if(x > coins)
    {
        printf("Your coins are not enough.");
        Sleep(1500);
        market();
    }
}

void Green_Sheet(char *word, char *letters, int length)
{
    time_t t= time(NULL);
    srand(t);

    int i, k= 0;
    for(i=0; i < length; i++)
    {
        if(letters[i] == '-')
            k++;
    }

    int r= rand()%k+1;
    k= 0;

    for(i=0; i < length; i++)
    {
        if(letters[i] == '-')
            k++;
        if(k == r)
        {
            letters[i]= word[i];
            data.market[0]--;
            let_G= 0;
            break;
        }
    }
}

void Red_Diamond(char *word, char *letters, int length)
{
    data.market[1]--;

    time_t t= time(NULL);
    srand(t);

    int i, k= 0, z= 0;
    for(i=0; i < length; i++)
    {
        if(letters[i] == '-')
            k++;
    }

    int w= rand()%2;
    int r= rand()%k+1;
    k= 0;

    if(w == 1)
    for(i=0; i < length; i++)
    {
        if(letters[i] == '-')
            k++;
        if(k == r)
        {
            printf("\nTry %c .\n\n", word[i]);
            break;
        }
    }

    else if(w == 0)
    {
        while(1)
        {
            w= rand()%26+97;

            for(i=0; i < length; i++)
            {
                if(word[i] == w)
                {
                    z= 1;
                    break;
                }
            }

            if(z == 0)
                break;
        }

        printf("\nTry %c .\n\n", w);
    }
}

void Blue_Mode()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bluemodecolor);
    system("cls");

    printf("Welcome to Blue Mode!\n\n\nWhat is Blue Mode?\n\nIn Blue Mode, You have just half of a normal time for a topic to play; but your coins will be x10!!");
    Sleep(3000);

    printf("\n\n\nDo you want to be Blue? [y/n]\n\n");

    char w, b;
    scanf("%c", &b);
    scanf("%c", &w);
    while(1) //checking wrong input.
    {
        if(w == 'y' || w == 'n')
            break;
        else
            printf("Please enter a defined option: ");

        scanf("%c", &b);
        scanf("%c", &w);
    }

    system("cls");

    if(w == 'n')
    {
        SetConsoleTextAttribute(hConsole, menucolor);
        system("cls");
        new_game();
    }

    if(data.market[4] == 0)
    {
        printf("For being Blue, you have to give a Blue Card.\nUnfortunately, you don't have any Blue Card. You can buy it in ");
        SetConsoleTextAttribute(hConsole, 182); //back sky gray, golden
        printf("Golden Market");
        SetConsoleTextAttribute(hConsole, bluemodecolor);
        printf(".");

        Sleep(10000);
        SetConsoleTextAttribute(hConsole, menucolor);
        system("cls");
        new_game();
    }

    printf("Blueing"); Sleep(1000); printf("."); Sleep(1000); printf("."); Sleep(1000); printf("."); Sleep(2000);

    data.market[4]--;
    do_B= 1;

    system("cls");

    new_game();
}

void Blue_end()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    printf("Good! Come Back to Blue again!");
    Sleep(3000);

    do_B= 0;

    SetConsoleTextAttribute(hConsole, menucolor);
    system("cls");

    new_game();
}
//END market*********************************************************

//to create linked list**********************************************
struct node
{
    char word[50];
    struct node *next;
};

typedef struct node node;

void add_front(node *new_node, node **list)
{
    new_node->next= *list;
    *list= new_node;
}

void add_end(node *new_node, node *list)
{
    node *current;

    for(current= list; current->next != NULL; current= current->next);
        current->next= new_node;

    new_node->next= NULL;
}

void print_list(node *list)
{
    node *current= list;

    while(current != NULL)
    {
        printf("%s\n", current->word);
        current= current->next;
    }
}

node *create_list(node *list, char *word)
{
    node *new_node= (node *)malloc(sizeof(node));
    if(new_node ==  NULL)
    {
        printf("\nSomething goes wrong... :(\n");
        exit(-1);
    }

    strcpy(new_node->word, word); new_node->next= NULL;

    if(list == NULL)
        add_front(new_node, &(list));

    else
        add_end(new_node, list);

    return list;
}

void delete_node(node *list, int i)
{
    node *current;
    int j;

    if(i != 1)
    {
        for(current= list, j=0; j < i-1-1; current= current->next, j++);
        free(current->next);

        for(current= list, j=0; j < i-1-1; current= current->next, j++);
        current->next= current->next->next;
    }
}
//*******************************************************************

void build_list(char *sub_name)
{
    FILE *subject;

    char sub_name_buff[100]= "../TOPICS/" ; //to add the address.
    strcat(sub_name_buff, sub_name);

    subject= fopen(sub_name_buff, "r");
    if(subject == NULL)
    {
        printf("\nSomething goes wrong... :(\n");
        exit(-1);
    }

    node *words= NULL;
    char word[50], c;
    int i, k= 0;

    if(do_B == 1) //for Blue Mode
    {
        while(fscanf(subject, "%c", &c) != EOF)
        {
            if(c != ' ')
                k++;
        }

        B_time= k*2;
    }

    rewind(subject);

    for(i=0; fscanf(subject, "%s", word) != EOF; i++)
        words= create_list(words, word);

    choosing_word(words, i);

    fclose(subject);
}

void choosing_word(node *list, int number)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, backcolor);
    system("cls");

    if(do_B == 1) //for Blue Mode
    {
        SetConsoleTextAttribute(hConsole, bluemodecolor);
        system("cls");
    }

    time_t t= time(NULL);
    srand(t);

    sub_coin= 0;

    printf("***    Let's Go!    ***");
    Sleep(1000);

    printf("\n\n\nDefined Characters:\n\n");
    if(do_B != 1) //normal
        printf("G: Green Sheet\nR: Red Diamond\nI: Gill\nH: Hourglass\n\n");
    printf("Q: Quit.\n");

    if(do_B == 1)
        printf("\n\n** Your time for being Blue: %d **", B_time);

    Sleep(4000);
    system("cls");

    while(number != 0)
    {
        int r= rand()%number+1, i;
        char *selected;

        node *current;

        if(r != 1)
        {
            for(current= list, i=1; i != r; current= current->next, i++);

            selected= current->word;
            gaming(selected, number);
            delete_node(list, i);
        }
        else //for the first node.
        {
            current = list;
            selected= current->word;
            gaming(selected, number);

            list = list->next;
            free(current);
        }

        number--;
    }

    new_game();
}

void gaming(char *word, int number)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    time_t start, end;
    int time_coin, buf_coin= 0;

    int length= strlen(word);

    char letters[20];

    int I_time= 0, c_score= 3; //c_score: correct score, for Blue Mode

    if(do_B == 1)
        c_score= 30;

    int i, j, k, l= 0, n;
    for(k=0; k < length; k++)
        letters[k]='-';
    letters[k]='\0';

    for(i=0; i < 58; i++) //It helps avoid repeating letters.
        guess_buff[i]= '0';

    if(do_B == 0)
        printf("* Whole Time for This Word: %d *\n\n", k * t_letter);

    drowning(0);

    time(&start);
    for(i=0; i < 5; )
    {
        if(i == 4) //for Green Sheet.
            let_G= 1;

        if(use_I != 1 || i != 4)
            printf("\n%s    **    Wrong Guesses: %d of 5.\n\n", letters, i); //normal
        else
            printf("\n%s    **    Wrong Guesses: %.2f of 5.\n\n", letters, 4+(I_time/4.0)); //for Gill

        printf("Your Guess: ");

        n= check_letter(word, letters, length);

        if(n == 2) //Red Diamond occurred.
            continue;

        else if(n == 3) //Gill occurred.
        {
            printf("\n\n* Gill Activated! *\n\n");
            continue;
        }

        else if(n == 4) //Hourglass occurred.
        {
            printf("\n\n* Whole Time for This Word: %d *\n\n", k * t_letter);
            continue;
        }

        else if(n == 0) //When guess is wrong.
        {
            i++;
            buf_coin-= 1;
            l= 0;

            if(use_I == 1 && i == 5 && I_time != 3) //for Gill
            {
                i--;
                I_time++;
            }

            printf(" | You lost 1 coin.\n\n");
            drowning(i);
        }
        else if(n == 1) //When guess is correct.
        {
            l++;
            buf_coin+= c_score*l;

            if(l == 1)
                printf(" | You earned %d coins!\n\n", c_score);
            else
                printf(" | You earned %dx%d coins!\n\n",c_score, l);
        }


        for(j=0; j < length; j++) //for checking if the word is complete or not.
        {
            if(letters[j] == '-')
                break;
        }

        if(j == length)
            break;
    }
    time(&end);


    if(i == 5) //When it was unsuccessful.
    {
        if(buf_coin < 0)
        {
            sub_coin+= buf_coin;
            coins+= buf_coin;
        }

        SetConsoleTextAttribute(hConsole, 244); //dark red
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, 180); //back sky blue

        printf("\nHe was drowned. You lost coins of this word :( .\nThe word was: %s.\n\n", word);

        SetConsoleTextAttribute(hConsole, backcolor);
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, bluemodecolor);

        printf("Total Coins: %d.", coins);
    }

    else //When it was successful.
    {
        SetConsoleTextAttribute(hConsole, 242); //dark green
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, 178); //back sky blue

        printf("\nYou saved him! It Was Great! %c\nThe word was: %s.\n\n", 1, word); //due to ASCII.

        SetConsoleTextAttribute(hConsole, backcolor);
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, bluemodecolor);


        time_coin= (int)(difftime(end, start));

        if(do_B == 1) //for Blue Mode
        {
            sub_coin+= buf_coin;
            coins+= buf_coin;

            printf("Coins you earned: Guesses Coins: %d  ===>  Total Coins: %d.", buf_coin, coins);

            B_time-= time_coin;
            if(B_time <= 0)
            {
                Sleep(3000);
                system("cls");

                printf("Time's up!");
                Sleep(1500);

                printf("\n\nYou earned %d Coins in Blue!", sub_coin);

                printf("\n\nDo you want to save your coins? [y/n]\n");

                char ww, bw;
                scanf("%c", &bw);
                scanf("%c", &ww);
                while(1) //checking wrong input.
                {
                    if(ww == 'y' || ww == 'n')
                        break;
                    else
                        printf("Please enter a defined option: ");

                    scanf("%c", &bw);
                    scanf("%c", &ww);
                }

                if(ww == 'y')
                    saving();
                else if(ww == 'n')
                    coins-= sub_coin;

                Blue_end();
            }
        }

        else
        {
            if((k * t_letter)-time_coin < 0)
                time_coin= 0;
            else
                time_coin= (k * t_letter)-time_coin;

            sub_coin+= buf_coin + time_coin;
            coins+= buf_coin + time_coin;

            printf("Coins you earned: Guesses Coins: %d  +  Time Coins: %d.  ===>  Total Coins: %d.", buf_coin, time_coin, coins);
        }
    }

    Sleep(3000);
    system("cls");

    if(number != 1)
        printf("Next Word:\n\n");
    else //When no word remind, to exit.
    {
        printf("Subject Finished!\nYou earned %d Coins in this subject. Total Coins: %d.", sub_coin, coins);

        if(do_B != 1) //normal
        {
            if(sub_coin > data.scores[q])
            {
                printf("\n\nYou have a new record in this subject!");
                data.scores[q]= sub_coin;
            }
        }

        printf("\n\nDo you want to save your coins? [y/n]\n");

        char w, b;
        scanf("%c", &b);
        scanf("%c", &w);
        while(1) //checking wrong input.
        {
            if(w == 'y' || w == 'n')
                break;
            else
                printf("Please enter a defined option: ");

            scanf("%c", &b);
            scanf("%c", &w);
        }

        if(w == 'y')
            saving();
        else if(w == 'n')
            coins-= sub_coin;

        if(do_B == 1)
            Blue_end();

        system("cls");
    }

    let_G= 0; //for Green Sheet.
}

int check_letter(char *word, char *letters, int length)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    int i, z=0;
    char c, b;

    scanf("%c", &b);
    scanf("%c", &c);
    while(1) //checking wrong input.
    {
        if((c >= 97 && c <= 122 && check_repeat(c) == 1) || c == 'Q')
            break;
        else if(c == 'G') //for Green Sheet
        {
            if(let_G == 0 || data.market[0] == 0 || use_I == 1 || do_B == 1)
                printf("You can't use it! Enter another character: ");
            else
                break;
        }
        else if(c == 'R') //for Red Diamond
        {
            if(data.market[1] == 0 || use_I == 1 || do_B == 1)
                printf("You can't use it! Enter another character: ");
            else
                break;
        }
        else if(c == 'I') //for Gill
        {
            if(data.market[2] == 0 || do_B == 1)
                printf("You can't use it! Enter another character: ");
            else
            {
                data.market[2]--;
                use_I= 1;
                return 3;
            }
        }
        else if(c == 'H') //for Hourglass
        {
            if(data.market[3] == 0 || do_B == 1)
                printf("You can't use it! Enter another character: ");
            else
            {
                data.market[3]--;
                t_letter= 8;
                return 4;
            }
        }
        else if(check_repeat(c) == 0)
            printf("You tried this letter before; try another letter: ");
        else
            printf("Please enter a lowercase letter or a defined character: ");

        scanf("%c", &b);
        scanf("%c", &c);
    }

    printf("\n");

    if(c == 'Q') //to exit.
    {
        printf("Are you sure? [y/n]\n");

        char a, bb;

        scanf("%c", &a);
        scanf("%c", &a);
        scanf("%c", &bb);
        while(1) //checking wrong input.
        {
            if(a == 'y' || a == 'n')
                break;
            else
                printf("Please enter a defined option: ");

            scanf("%c", &a);
            scanf("%c", &bb);
        }

        printf("\n\n");

        if(a == 'y')
        {
            printf("You earned %d Coins in this subject. Total Coins: %d.", sub_coin, coins);

            if(do_B != 1) //normal
            {
                if(sub_coin > data.scores[q])
                {
                    printf("\n\nYou have a new record in this subject!");
                    data.scores[q]= sub_coin;
                }
            }

            printf("\n\nDo you want to save your coins? [y/n]\n");

            char w, b;
            scanf("%c", &w);
            while(1) //checking wrong input.
            {
                if(w == 'y' || w == 'n')
                    break;
                else
                    printf("Please enter a defined option: ");

                scanf("%c", &b);
                scanf("%c", &w);
            }

            if(w == 'y')
                saving();
            else if(w == 'n')
                coins-= sub_coin;

            if(do_B == 1)
                Blue_end();

            system("cls");
            new_game();
        }
        else
        {
            printf("Your Guess: ");
            scanf("%c", &c);
        }
    }

    else if(c == 'G') //Green Sheet
    {
        Green_Sheet(word, letters, length);
        z= 1;
    }

    else if(c == 'R')
    {
        Red_Diamond(word, letters, length);
        return 2;
    }

    else
    {
        int k;
        for(k=0; guess_buff[k] != '0'; k++);

        guess_buff[k]= c; //for check_repeat function.

        for(i=0; i < length; i++) //check letter.
        {
            if(word[i] == c)
            {
                letters[i]= c;
                z=1;
            }
        }
    }

    if(z == 1)
    {
        SetConsoleTextAttribute(hConsole, 250); //lite green
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, 186); //back sky blue

        printf("Well Done!");

        SetConsoleTextAttribute(hConsole, backcolor);
        if(do_B == 1)
            SetConsoleTextAttribute(hConsole, bluemodecolor);

        return 1;
    }

    SetConsoleTextAttribute(hConsole, 252); //lite red
    if(do_B == 1)
            SetConsoleTextAttribute(hConsole, 188); //back sky blue

    printf("Oh... NOOOO!!! It was incorrect!"); //if z=0.

    SetConsoleTextAttribute(hConsole, backcolor);
    if(do_B == 1)
            SetConsoleTextAttribute(hConsole, bluemodecolor);

    return 0;
}

int check_repeat(char c)
{
    int i;
    for(i=0; guess_buff[i] != '0'; i++)
    {
        if(c == guess_buff[i])
            return 0;
    }

    return 1;
}

void saving()
{
    FILE *save, *infon, *infos;

    char save_buff[100]= "../Scores/" ; //to add the address.
    strcat(save_buff, gamer_name);
    char add_bin[]= ".bin";
    strcat(save_buff, add_bin);

    save= fopen(save_buff, "wb");
    if(save == NULL)
    {
        printf("\nSomething goes wrong... :(\nCANNOT save...");
        fclose(save);
        Sleep(3000);
        system("cls");
        new_game();
    }

    data.t_coins= coins;

    fwrite(&data, sizeof(data), 1, save); //for binary file

    fclose(save);

    //for info files; they help tops function.
    char scan[20];
    int score[1000];
    int i= 0, k= 0, s;

    if(zz == 1) //the name repeated before
    {
        infon= fopen("../Scores/SAVE_INFO_N.txt", "r");
        infos= fopen("../Scores/SAVE_INFO_S.bins", "rb");
        if(infon == NULL || infos == NULL)
        {
            printf("\nSomething goes wrong... :(\nCANNOT save...");
            fclose(infon); fclose(infos);
            Sleep(3000);
            system("cls");
            new_game();
        }

        while(1)
        {
            fscanf(infon, "%s", scan);

            if(strcmp(scan, data.name) == 0)
            {
                k= i;
                break;
            }

            i++;
        }

        i= 0;
        while(1)
        {
            if(fread(&s, sizeof(int), 1, infos) < 1)
                break;

            if(i != k)
                score[i]= s;
            else
                score[i]= data.t_coins;

            i++;
        }

        fclose(infon); fclose(infos);

        infos= fopen("../Scores/SAVE_INFO_S.bins", "wb");

        for(k=0; k < i; k++)
            fwrite(&score[k], sizeof(int), 1, infos);

        fclose(infos);
    }

    else if(zz == 0) //the name not repeated before
    {
        infon= fopen("../Scores/SAVE_INFO_N.txt", "a");
        infos= fopen("../Scores/SAVE_INFO_S.bins", "ab");
        if(infon == NULL || infos == NULL)
        {
            printf("\nSomething goes wrong... :(\nCANNOT save...");
            fclose(infon); fclose(infos);
            Sleep(3000);
            system("cls");
            new_game();
        }

        fprintf(infon, "%s ", data.name);
        fwrite(&data.t_coins, sizeof(int), 1, infos);

        fclose(infon); fclose(infos);
    }

    zz= 1;

    printf("\n\nSaved successfully!");
    Sleep(1000);
}

//START drowning*****************************************************
void drowning(int i)
{
    printf("\n\n");

    //Numbers is in ASCII.
    if(i == 0)
    {
        heart_drowning(5);

        printf("          %c%c%c%c%c%c%c\n", 218, 193, 193, 193, 193, 193, 191);
        printf("        %c %c %c %c %c\n", 14, 179, 15, 15, 179);
        printf("         %c%c%c %c  %c\n", 14, 179, 14, 127, 179);
        printf("          %c %co  %c\n", 179, 14, 179);
        printf("          %c%c%c%c%c%c%c\n", 192, 196, 194, 196, 194, 196, 217);
        printf("            %c %c\n", 179, 179);
        printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 193, 196, 193, 196, 196, 196, 196, 191);
        printf("      *%c           %c*\n", 179, 179);
        printf("     * *           * *\n");
        printf("    * *%c           %c* *\n", 179, 179);
        printf("       %c           %c\n       %c           %c\n       %c           %c\n", 179, 179, 179, 179, 179, 179);
        printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 194, 196, 194, 196, 196, 196, 194, 196, 194, 196, 217);
        printf("         %c %c   %c %c\n         %c %c   %c %c\n         %c %c   %c %c\n", 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179);

        water_drowning();
    }

    else if(i == 1)
    {
        heart_drowning(4);

        printf("          %c%c%c%c%c%c%c %c\n", 218, 193, 193, 193, 193, 193, 191, 19);
        printf("          %c o o %c\n", 179, 179);
        printf("          %c  %c  %c\n", 179, 127, 179);
        printf("          %c ~~~ %c\n", 179, 179);
        printf("          %c%c%c%c%c%c%c\n", 192, 196, 194, 196, 194, 196, 217);
        printf("            %c %c\n", 179, 179);
        printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 193, 196, 193, 196, 196, 196, 196, 191);
        printf("      *%c           %c*\n", 179, 179);
        printf("     * *           * *\n");
        printf("    * *%c           %c* *\n", 179, 179);
        printf("       %c           %c\n       %c           %c\n       %c           %c\n", 179, 179, 179, 179, 179, 179);

        water_drowning();
    }

    else if(i == 2)
    {
        heart_drowning(3);

        printf("          %c%c%c%c%c%c%c\n", 218, 193, 193, 193, 193, 193, 191);
        printf("          %c O O %c\n", 179, 179);
        printf("          %c  %c  %c\n", 179, 127, 179);
        printf("          %c %c%c%c %c\n", 179, 247, 247, 247, 179);
        printf("          %c%c%c%c%c%c%c\n", 192, 196, 194, 196, 194, 196, 217);
        printf("            %c %c\n", 179, 179);
        printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 193, 196, 193, 196, 196, 196, 196, 191);
        printf("      *%c           %c*\n", 179, 179);
        printf("     * *           * *\n");

        water_drowning();
    }

    else if(i == 3)
    {
        heart_drowning(2);

        printf("          %c%c%c%c%c%c%c\n", 218, 193, 193, 193, 193, 193, 191);
        printf("          %c %c %c %c\n", 179, 233, 233, 179);
        printf("          %c  %c  %c\n", 179, 127, 179);
        printf("          %c ### %c\n", 179, 179);
        printf("          %c%c%c%c%c%c%c\n", 192, 196, 194, 196, 194, 196, 217);
        printf("            %c %c\n", 179, 179);

        water_drowning();
    }

    else if(i == 4)
    {
        heart_drowning(1);

        printf("          %c%c%c%c%c%c%c\n", 218, 193, 193, 193, 193, 193, 191);
        printf("          %c * * %c\n", 179, 179);
        printf("          %c  %c  %c\n", 179, 127, 179);

        water_drowning();
    }

    else if(i == 5)
    {
        printf("          R.I.P.\n\n");

        water_drowning();
    }

    printf("\n");
}

void heart_drowning(int k)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    int i;

    SetConsoleTextAttribute(hConsole, heartcolor);
    if(do_B == 1) //for Blue Mode
        SetConsoleTextAttribute(hConsole, bluemodeheartcolor);

    printf("           ");
    for(i=0; i < k; i++)
        printf("%c", 3); //Hearts
    printf("\n\n");

    SetConsoleTextAttribute(hConsole, backcolor);
    if(do_B == 1) //for Blue Mode
        SetConsoleTextAttribute(hConsole, bluemodecolor);
}

void water_drowning()
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, watercolor);

    printf("                           \n                           \n                           \n                           \n                           \n");

    SetConsoleTextAttribute(hConsole, backcolor);
    if(do_B == 1) //for Blue Mode
        SetConsoleTextAttribute(hConsole, bluemodecolor);
}
//END drowning*******************************************************

int main()
{
    beginning();

    return 0;
}

/* ************************************************************************************************

                        HOW TO USE SetConsoleTextAttribute FUNCTION

#include <stdio.h>
#include <windows.h>   // WinApi header

int main()
{
  HANDLE  hConsole;
    int k;

  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // you can loop k higher to see more color choices
  for(k = 1; k < 255; k++)
  {
    SetConsoleTextAttribute(hConsole, k);
    printf("%3d  %s\n", k, "I want to be nice today!");
  }

  return 0;
}

************************************************************************************************ */
