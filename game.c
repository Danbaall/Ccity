#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define nl printf("\n");

struct game
{
    char name[30];
    int day;
    char map[10][10];
    int money;
};

struct lbPoints
{
    char name[30];
    int points;
};

struct achievenent
{
    char first_buil; //gets y or n
    char millionaire;
    int upgrader;
    char perfect_city;
};

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void create_map(char arr[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = '.';
        }
    }
}

void load_map(char arr[10][10])
{
}

void display_map(char arr[10][10])
{
    printf("   1 2 3 4 5 6 7 8 9 10");
    nl;
    for (int i = 0; i < 10; i++)
    {
        if (i == 9)
            printf("%d ", i + 1);
        else
            printf("%d  ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%c ", arr[i][j]);
        }
        nl;
    }
    printf("=====================================\n");
    printf("commands :\n");
    printf("b : Build      u : Upgrade   d : Demolish\n");
    printf("n : Next day   s : save      e : Exit\n");
}

int border_check(int i, int j)
{
    if ((i < 11 && i > 0) && (j < 11 && j > 0))
        return 1;

    else
        return 0;
}

void build(char arr[10][10], int i, int j, int *money, struct achievenent *achiev)
{ 
    i -= 1;
    j -= 1;

    if (arr[i][j] != '.')
    {
        printf("you need to build your building on empty ground!\n");
        getchar();
        getchar();
        return;
    }

    char type;

    printf("please enter the type of building you wish to construct : \n");
    printf("h : home   f : farm   s : shop   p : park\n");
    printf("home : 50$   farm : 80$  shop : 100$  park : 40$\n");
    printf("if you wish to go back enter b\n");
    scanf(" %c", &type);

    if (type == 'b')
        return;

    while (!(type == 'h' || type == 's' || type == 'f' || type == 'p'))
    {
        printf("please select a type from the menu :\n");
        printf("if you wish to go back enter b\n");
        scanf("%c", &type);
        if (type == 'b')
            return;
    }

    int built = 0;

    if (type == 'h' && *money >= 50)
    {
        arr[i][j] = 'h';
        (*money) -= 50;
        built = 1;
    }
    else if (type == 'h' && *money < 50)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (type == 'f' && *money >= 80)
    {
        arr[i][j] = 'f';
        (*money) -= 80;
        built = 1;
    }
    else if (type == 'f' && *money < 80)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (type == 's' && *money >= 100)
    {
        arr[i][j] = 's';
        (*money) -= 100;
        built = 1;
    }
    else if (type == 's' && *money < 100)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (type == 'p' && *money >= 40)
    {
        arr[i][j] = 'p';
        (*money) -= 40;
        built = 1;
    }
    else if (type == 'p' && *money < 40)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (built && achiev->first_buil == 'n') {
        achiev->first_buil = 'y';
        printf("\nAchievement Unlocked: First Building!\n");
        printf("25$ has been added to your money");
        (*money) += 25;
        getchar(); getchar();
    }

    return;
}

void upgrade(char arr[10][10], int i, int j, int *money, struct achievenent *achiev)
{
    i -= 1;
    j -= 1;

    if (arr[i][j] == '.')
    {
        printf("there's nothing to upgrade!\n");
        getchar();
        getchar();
        return;
    }

    else if (arr[i][j] == 'H' || arr[i][j] == 'F' || arr[i][j] == 'P' || arr[i][j] == 'S')
    {
        printf("Building is Already Upgraded Mayor!\n");
        getchar();
        getchar();
        return;
    }

    int dec;
    printf("upgrade prices : \n");
    printf("home : 30$   farm : 50$  shop : 60$  park : 20$\n");
    printf("To confirm Enter 1, to go back enter any other number : ");
    scanf("%d", &dec);
    if (dec != 1)
        return;

    int upgraded = 0;

    if (arr[i][j] == 'h' && *money >= 30)
    {
        arr[i][j] = 'H';
        *money -= 30;
        upgraded = 1;
    }
    else if (arr[i][j] == 'h' && *money < 30)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (arr[i][j] == 's' && *money >= 60)
    {
        arr[i][j] = 'S';
        *money -= 60;
        upgraded = 1;
    }
    else if (arr[i][j] == 's' && *money < 60)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (arr[i][j] == 'p' && *money >= 20)
    {
        arr[i][j] = 'P';
        *money -= 20;
        upgraded = 1;
    }
    else if (arr[i][j] == 'p' && *money < 20)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (arr[i][j] == 'f' && *money >= 50)
    {
        arr[i][j] = 'F';
        *money -= 50;
        upgraded = 1;
    }
    else if (arr[i][j] == 'f' && *money < 50)
    {
        printf("Not enough money!");
        getchar();
        getchar();
    }

    if (upgraded) {
        achiev->upgrader++;
        
        if (achiev->upgrader == 5) {
            printf("\nAchievement Unlocked: The Upgrader! (5 upgrades)\n");
            printf("50$ has been added to your money");
            (*money) += 50;
            getchar(); getchar();
        }
    }
    
    return;
}

void demolish(char arr[10][10], int i, int j, int *money)
{
    i -= 1;
    j -= 1;
    if (arr[i][j] == '.')
    {
        printf("there's nothing to demolish!");
        getchar();
        getchar();
        return;
    }

    int dec;
    printf("only half of the BASE price will return to your treasury\n");
    printf("To confirm Enter 1, to go back enter any other number : ");
    scanf("%d", &dec);
    if (dec != 1)
        return;

    if (arr[i][j] == 'h' || arr[i][j] == 'H')
        *money += 25;
    else if (arr[i][j] == 's' || arr[i][j] == 'S')
        *money += 50;
    else if (arr[i][j] == 'p' || arr[i][j] == 'P')
        *money += 20;
    else if (arr[i][j] == 'f' || arr[i][j] == 'F')
        *money += 40;

    arr[i][j] = '.';
    return;
}

int is_neighbor(char src, char dst)
{
    if ((src == 'h' || src == 'H') && (dst == 'h' || dst == 'H'))
        return 1;
    if ((src == 'p' || src == 'P') && (dst == 'p' || dst == 'P'))
        return 1;
    if ((src == 'f' || src == 'F') && (dst == 'f' || dst == 'F'))
        return 1;
    if ((src == 's' || src == 'S') && (dst == 's' || dst == 'S'))
        return 1;
    return 0;
}

int type_income(char block)
{
    if (block == 'h')
        return 10;
    else if (block == 'H')
        return 25;
    else if (block == 's')
        return 20;
    else if (block == 'S')
        return 50;
    else if (block == 'p')
        return 5;
    else if (block == 'P')
        return 15;
    else if (block == 'f')
        return 15;
    else if (block == 'F')
        return 35;
    return 0;
}

void random_event(char map[10][10], int *money){
    int event = rand() % 6;

     if (event == 0) {
        // Rain: all farms get 10$
        int farm_count = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] == 'f' || map[i][j] == 'F') {
                    farm_count++;
                    *money += 10;
                }
            }
        }
        printf("\nRAIN EVENT: Your farms flourished! +%d$ (%d farms * 10$)\n", farm_count * 10, farm_count);
    }
    
    else if (event == 1) {
        // Festival: all shops get 15$
        int shop_count = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] == 's' || map[i][j] == 'S') {
                    shop_count++;
                    *money += 15;
                }
            }
        }
        printf("\nFESTIVAL EVENT: Your shops boomed! +%d$ (%d shops * 15$)\n", shop_count * 15, shop_count);
    }
    
    else if (event == 2) {
        //demolish
        int buildings[100][2];  // Store [i][j] coordinates
        int count = 0;
        
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] != '.') {
                    buildings[count][0] = i; //i and j-s with buildings
                    buildings[count][1] = j;
                    count++;
                }
            }
        }
        
        if (count > 0) {
            int random_idx = rand() % count; //use indexes with buildings only
            int demo_i = buildings[random_idx][0];
            int demo_j = buildings[random_idx][1]; //chose i and j to demolish
            char demolished = map[demo_i][demo_j];
            
            map[demo_i][demo_j] = '.';
            printf("\nEARTHQUAKE EVENT: A building at (%d, %d) was destroyed! (type: %c)\n", 
                   demo_i + 1, demo_j + 1, demolished);
        } else {
            printf("\nEARTHQUAKE EVENT: Luckily(or Sadly?), you had no buildings to damage!\n");
        }
    }
    
    else if (event == 3) {
        // Hidden treasure: get 100$
        *money += 100;
        printf("\nHIDDEN TREASURE EVENT: You found treasure! +100$\n");
    }
    
    else if (event == 4) {
        // Taxation: lose 10% of money
        int tax = *money / 10;
        *money -= tax;
        printf("\nTAXATION EVENT: The government collected taxes! -%d$ (10%% of treasury)\n", tax);
    }
    
    else if (event == 5) {
        // Population burst: all homes get 10$
        int home_count = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] == 'h' || map[i][j] == 'H') {
                    home_count++;
                    *money += 10;
                }
            }
        }
        printf("\nPOPULATION BURST EVENT: More residents moved in! +%d$ (%d homes × 10$)\n", 
               home_count * 10, home_count);
    }
}

void next_day(char arr[10][10], int *money, int *day)
{
    int income = 0;
    int house_in = 0, farm_in = 0, shop_in = 0, park_in = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            char current = arr[i][j];
            int neighbor_count = 0;
            int max_neighbors = 0;

            if (current == '.')
                continue;

            // up
            if (i > 0)
            {
                max_neighbors++;
                if (is_neighbor(current, arr[i - 1][j]))
                {
                    neighbor_count++;
                }
            }

            // down
            if (i < 9)
            {
                max_neighbors++;
                if (is_neighbor(current, arr[i + 1][j]))
                {
                    neighbor_count++;
                }
            }

            // left
            if (j > 0)
            {
                max_neighbors++;
                if (is_neighbor(current, arr[i][j - 1]))
                {
                    neighbor_count++;
                }
            }

            // right
            if (j < 9)
            {
                max_neighbors++;
                if (is_neighbor(current, arr[i][j + 1]))
                {
                    neighbor_count++;
                }
            }

            int base_income = type_income(current);
            float multiplier = ((float)neighbor_count / max_neighbors) + 1.0;
            int block_income = (int)(multiplier * base_income);

            income += block_income;

            if (current == 'h' || current == 'H')
            {
                house_in += block_income;
            }
            else if (current == 'f' || current == 'F')
            {
                farm_in += block_income;
            }
            else if (current == 's' || current == 'S')
            {
                shop_in += block_income;
            }
            else if (current == 'p' || current == 'P')
            {
                park_in += block_income;
            }
        }
    }

    *money += income;

    printf("----------Day %d has ended----------", *day);
    nl;
    printf("Daily Report : ");
    nl;
    printf("- House income : %d$", house_in);
    nl;
    printf("- Farm income : %d$", farm_in);
    nl;
    printf("- Shop income : %d$", shop_in);
    nl;
    printf("- Park income : %d$", park_in);
    nl;
    printf("------------------------------------");
    nl;
    printf("Total Income : %d$", income);
    nl;
    printf("Current Money : %d$", *money);
    nl;
    (*day)++;
    printf("Date Changed to Day %d", *day);
    nl;
    printf("------------------------------------");
    random_event(arr, money);
    printf("------------------------------------\n");

    printf("press enter to continue...");
    nl;
    getchar();
    getchar();

    return;
}

void save(char name[30], int day, int money, char map[10][10], struct achievenent *achiev)
{
    char filename[35];

    sprintf(filename, "%s.txt", name);

    FILE *file = fopen(filename, "w");

    if (!file)
    {
        printf("Error: Could not create save file!\n");
        return;
    }
    fprintf(file, "%s\n", name);
    fprintf(file, "%d\n", day);
    fprintf(file, "%d\n", money);
    fprintf(file, "%c %c %d %c\n", 
            achiev->first_buil, 
            achiev->millionaire, 
            achiev->upgrader, 
            achiev->perfect_city);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(file, "%c", map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    printf("Game saved successfully to %s!\n", filename);

    FILE *saved_games = fopen("saved_games.txt", "r");
    int flag = 0; // to see if name already exist or not
    char temp[30];

    if (saved_games != NULL)
    {
        while (fscanf(saved_games, "%s", temp) != EOF)
        {
            if (strcmp(temp, name) == 0)
            {
                flag = 1; // means already exist
                break;
            }
        }

        fclose(saved_games);
    }

    if (!flag)
    { // name doesn't exist on list
        saved_games = fopen("saved_games.txt", "a");
        if (saved_games == NULL)
        {
            printf("Error: Could not update saved games list!\n");
            return;
        }
        fprintf(saved_games, "%s\n", name);
        fclose(saved_games);
    }
}

int load(int *day, int *money, char map[10][10], struct achievenent *achiev)
{
    FILE *saves_list = fopen("saved_games.txt", "r");

    if (saves_list == NULL)
    {
        printf("No saved games found!\n");
        return 0;
    }

    printf("\n====== Saved Games ======\n");
    char saved_names[100][30];
    int count = 0;

    while (fscanf(saves_list, "%s", saved_names[count]) != EOF)
    {
        printf("%d. %s\n", count + 1, saved_names[count]);
        count++;
    }
    fclose(saves_list);

    if (count == 0)
    {
        printf("No saved games found!\n");
        return 0;
    }

    int choice;
    printf("\nEnter the number of the save to load (0 to cancel): ");
    scanf("%d", &choice);

    if (choice <= 0 || choice > count)
    {
        printf("Load cancelled.\n");
        return 0;
    }

    char selected_name[30];
    strcpy(selected_name, saved_names[choice - 1]);

    char filename[35];
    sprintf(filename, "%s.txt", selected_name);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Save file %s not found!\n", filename);
        return 0;
    }

    char temp_name[30];
    fscanf(file, "%s\n", temp_name);

    fscanf(file, "%d\n", day);

    fscanf(file, "%d\n", money);

    fscanf(file, " %c %c %d %c\n", 
           &achiev->first_buil, 
           &achiev->millionaire, 
           &achiev->upgrader, 
           &achiev->perfect_city);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fscanf(file, "%c", &map[i][j]);
        }
        fscanf(file, "\n");
    }

    fclose(file);

    printf("Game '%s' loaded successfully!\n", selected_name);
    printf("Day: %d, Money: %d\n", *day, *money);

    return 1;
}

int buildings_value(char a[10][10])
{
    int BV = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int ret = 0;
            char block = a[i][j];
            if (block == 'h')
                ret = 50;
            else if (block == 'H')
                ret = 100;
            else if (block == 's')
                ret = 100;
            else if (block == 'S')
                ret = 200;
            else if (block == 'p')
                ret = 40;
            else if (block == 'P')
                ret = 80;
            else if (block == 'f')
                ret = 80;
            else if (block == 'F')
                ret = 150;
            BV += ret;
        }
    }
    return BV;
}

void leader_board_save(char name[30], int final_points)
{ // saves a name to a leaderboard and sorts it.
    FILE *lb = fopen("leaderboard.txt", "r");

    /*if (lb == NULL)
    {
        printf("leaderboard doesn't exist yet!\ncomplete a game to start your leaderboard.");
        getchar();
        getchar();
        return;
    }*/ 

    struct lbPoints temp[100];

    int cnt = 0;
    if (lb != NULL)
    {
        while (fscanf(lb, "%s %d", temp[cnt].name, temp[cnt].points) == 2)
        {
            cnt++;
            if (cnt > 99)
                break;
        }
        fclose(lb);
    }

    strcpy(temp[cnt].name, name);
    temp[cnt].points = final_points;
    cnt++;

    // sort
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (temp[j].points < temp[j + 1].points)
            {
                struct lbPoints swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    lb = fopen("leaderboard.txt", "w");
    if (lb == NULL)
    {
        printf("Error: Could not save leaderboard!\n");
        return;
    }

    for (int j = 0; j < cnt; j++)
    {
        fprintf(lb, "%s %d\n", temp[j].name, temp[j].points);
    }

    fclose(lb);
    printf("Leaderboard updated successfully!\n");
    getchar();
    getchar();

    return;
}

void display_leaderboard()
{
    FILE *lb = fopen("leaderboard.txt", "r");

    if (lb == NULL)
    {
        printf("\n=====================================\n");
        printf("           LEADERBOARD\n");
        printf("=====================================\n");
        printf("No entries yet! Complete a game to\n");
        printf("appear on the leaderboard.\n");
        printf("=====================================\n");
        return;
    }

    struct lbPoints entries[100];
    int count = 0;

    while (fscanf(lb, "%s %d", entries[count].name, &entries[count].points) == 2)
    {
        count++;
        if (count >= 100)
            break;
    }
    fclose(lb);

    printf("\n=====================================\n");
    printf("            LEADERBOARD\n");
    printf("=====================================\n");

    if (count == 0)
    {
        printf("No entries yet!\n");
    }
    else
    {
        printf("Rank  Name                  Points\n");
        printf("-------------------------------------\n");

        for (int i = 0; i < count; i++)
        {
            printf("%-5d %-20s %d\n", i + 1, entries[i].name, entries[i].points);
        }
    }

    printf("=====================================\n");
}

void check_perfect_city(char map[10][10], struct achievenent *achiev, int *money)
{
    if (achiev->perfect_city == 'y') {
        return;  // Already unlocked
    }
    
    //row
    for (int i = 0; i < 10; i++) {
        int row_full = 1;
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == '.') {
                row_full = 0;
                break;
            }
        }
        if (row_full) {
            achiev->perfect_city = 'y';
            printf("\nAchievement Unlocked: Perfect City! (Complete row/column)\n");
            printf("200$ has been added to your money");
            (*money) += 200;
            getchar(); getchar();
            return;
        }
    }
    
    //column
    for (int j = 0; j < 10; j++) {
        int col_full = 1;
        for (int i = 0; i < 10; i++) {
            if (map[i][j] == '.') {
                col_full = 0;
                break;
            }
        }
        if (col_full) {
            achiev->perfect_city = 'y';
            printf("\nAchievement Unlocked: Perfect City! (Complete row/column)\n");
            printf("200$ has been added to your money");
            (*money) += 200;
            getchar(); getchar();
            return;
        }
    }
}

int main()
{
    srand(time(NULL));

    int option;
    struct game attr;
    struct achievenent achiev;

    while (1)
    {
        clear();
        printf("=====================================");
        nl;
        printf("      CITY MANAGEMENT SIMULATOR      ");
        nl;
        printf("=====================================");
        nl;
        printf("1. New Game");
        nl;
        printf("2. Load Game");
        nl;
        printf("3. LeaderBoard");
        nl;
        printf("4. Exit");
        nl;
        printf("=====================================");
        nl;
        printf("Select an option : ");
        scanf("%d", &option);

        while (!(option == 1 || option == 2 || option == 3 || option == 4))
        {
            printf("please select an option from the menu!!!...");
            scanf("%d", &option);
        }

        if (option == 1 || option == 2)
        {
            printf("\nStarting game...\n");
            printf("press enter\n");
            getchar();
            getchar();
            clear();

            if (option == 1)
            {
                printf("please enter your name :\n");
                scanf("%s", attr.name);

                attr.day = 1;
                attr.money = 200;
                create_map(attr.map);
                achiev.first_buil = 'n';
                achiev.millionaire = 'n';
                achiev.perfect_city = 'n';
                achiev.upgrader = 0;
                clear();
            }

            else
            { // option = 2
                if (load(&attr.day, &attr.money, attr.map, &achiev))
                {
                    printf("Resuming game...\n");
                }
                else
                {
                    printf("Failed to load game. Please try again.\n");
                    getchar();
                    //getchar();
                    clear();
                    continue;
                }
            }

            while (1)
            {
                if (attr.day == 11)
                {
                    clear();
                    int BV = buildings_value(attr.map);
                    printf("Congrats, you managed to end the game!!");
                    nl;
                    printf("here's your overall result, it will be saved and displayed on the leaderboard.");
                    nl;
                    printf("Name : %s     money : %d   buildings' value : %d", attr.name, attr.money, BV);
                    nl;
                    printf("final results : %d", attr.money + BV);
                    leader_board_save(attr.name, BV+attr.money);
                    break;
                }

                //check money achievement
                if(achiev.millionaire == 'n' && attr.money >= 1000){
                    printf("you have unlocked the millionaire achievement, well done!"); nl;
                    printf("100$ has been added to your money.\n");
                    attr.money += 100;
                    achiev.millionaire = 'y';
                    printf("press enter to continue...");
                    getchar(); getchar();
                    clear();
                }

                char command;
                printf("=====================================");
                nl;
                printf("Day : %d               Money : %d    ", attr.day, attr.money);
                nl;
                printf("=====================================");
                nl;
                display_map(attr.map);
                printf("----------------------------------------------------------------------"); nl;
                if(achiev.first_buil == 'n')
                    printf("- achievement locked : build something for the first time(25$)\n");
                if(achiev.upgrader < 5)
                    printf("- achievement locked : upgrade buildings 5 times(50$)\n");
                if(achiev.millionaire == 'n')
                    printf("- achievement locked : keep 1000$ in your wallet(100$)\n");
                if(achiev.perfect_city == 'n')
                    printf("- achievement locked : complete a row or a column\n");
                printf("----------------------------------------------------------------------"); nl;
                
                printf("Enter a Command Mayor : \n");
                scanf(" %c", &command);
                printf("=====================================\n");

                if (command == 'b' || command == 'u' || command == 'd')
                {

                    int i, j;
                    int valid = 1;
                    printf("pleae enter coordinations : \n(correct format : i j) ");
                    scanf("%d %d", &i, &j);
                    while (border_check(i, j) != 1)
                    {
                        int dec;
                        printf("Given coordinates are out of the city bounderies!\n");
                        printf("if you wish to try again enter number 1 and if you wish to go back any number :\n");
                        scanf("%d", &dec);
                        if (dec == 1)
                        {
                            printf("Please Try Again : ");
                            scanf("%d %d", &i, &j);
                            nl;
                        }
                        else{
                            valid = 0;
                            break;
                        }
                    }

                    if(valid == 0) continue;

                    if (command == 'b')
                    {
                        build(attr.map, i, j, &attr.money, &achiev);
                    }

                    else if (command == 'u')
                    {
                        upgrade(attr.map, i, j, &attr.money, &achiev);
                    }

                    else if (command == 'd')
                    {
                        demolish(attr.map, i, j, &attr.money);
                    }
                }

                if (command == 'n')
                {
                    clear();
                    next_day(attr.map, &attr.money, &attr.day);
                }

                if (command == 's')
                {
                    clear();
                    save(attr.name, attr.day, attr.money, attr.map, &achiev);
                    printf("press enter to continue...\n");
                    getchar();
                    getchar();
                    break;
                }

                if (command == 'e')
                {
                    printf("are you sure you want to exit the game?");
                    nl;
                    printf("if yes, enter 1, otherwise enter anything!");
                    nl;
                    int dec;
                    scanf("%d", &dec);
                    if (dec == 1)
                        break;
                }

                check_perfect_city(attr.map, &achiev, &attr.money);

                clear();
            }
        }
        else if (option == 3)
        {
            clear();
            display_leaderboard();
            printf("\npress enter to go back...");
            getchar();
            getchar();
        }
        else
        {
            printf("GoodBye! :)\n");
            break;
        }
    }
}