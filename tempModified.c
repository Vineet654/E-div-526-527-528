#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include<ctype.h>

#define MAX_USERS 100
#define DATABASE_FILE "user_database.txt"
#define MAX 5
#define INFINITY 9999

struct info
{
    char cityName[50];
    int pincode;
    int population;
    int numHospitals;
    int numPatients;
    int numDoctors;
    int cityCode;
};
struct node
{
    struct info data;
    int distance;
};

// Function prototypes
void readCity(FILE *, struct node *);
void displayCity(struct node *);
int comparePincode(const struct node *, const struct node *);
int compareCityName(const struct node *, const struct node *);
int comparePopulation(const struct node *, const struct node *);
int compareCityCode(const struct node *, const struct node *);
int compareNumHospitals(const struct node *, const struct node *);
int compareNumPatients(const struct node *, const struct node *);
int compareNumDoctors(const struct node *, const struct node *);
int KMPSearch(char  [], char []);
void readFile(char* ,char  []);


void Dijkstra(int Graph[MAX][MAX], int n, int start, struct node *city);

void merge(struct node arr[], int l, int m, int r, int (*cmp)(const struct node *, const struct node *));
void mergeSort(struct node arr[], int l, int r, int (*cmp)(const struct node *, const struct node *));


typedef struct
 {
    char username[30];
    char password[30];
} User;

User users[MAX_USERS];
int numUsers = 0;
void saveUserToFile(User );
int userExists(char *);
int createUser();
int loginUser();




void saveUserToFile(User newUser)
 {
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(0);
    }

    fprintf(file, "%s %s\n", newUser.username, newUser.password);

    fclose(file);
}

int userExists(char *username)
 {
    for (int i = 0; i < numUsers; ++i)
        {
        if (strcmp(users[i].username, username) == 0) {
            return 1; // User exists
        }
    }
    return 0; // User does not exist
}

int createUser()
 {
    User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);

    if (userExists(newUser.username))
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED| FOREGROUND_INTENSITY);
           printf("Error: Username already exists.\n");
            // Reset the text color to default (you may want to do this after printing colored text)
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return 0;
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    saveUserToFile(newUser);
    users[numUsers++] = newUser;

    printf("Account created successfully!\n");

    return 1;
}

int loginUser()
{
    char username[30];
    char password[30];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; ++i)
        {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
            {
            const WORD darkGreen = 2;
            // Get the handle to the console
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole,darkGreen| FOREGROUND_INTENSITY);
            printf("Login successful!\n");
            // Reset the text color to default (you may want to do this after printing colored text)
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return 1;
        }
    }
            // Get the handle to the console
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED| FOREGROUND_INTENSITY);
            printf("Login failed: Invalid username or password.\n");
            // Reset the text color to default (you may want to do this after printing colored text)
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return 0;
}

int main()
 {
    int flag,flag1;
    int j;
    int num;
    int sortCh;
    char searchCity[15];
    char gfname[50];
    char fname[50];
    char content[1000];
    int (*cmp)(const struct node *, const struct node *);
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file != NULL)
    {
        while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2)
            numUsers++;
        fclose(file);
    }

        printf("Enter File name to copy data from:");
    scanf("%s",fname);
    FILE *fp=fopen(fname,"r");
    if(fp==NULL)
    {
        perror("File open unsuccessful");
        exit(0);
    }

    fscanf(fp,"%d",&num);

    //structure of cities
    struct node city[num];
    for(int j=0;j<num;j++)
            readCity(fp,&city[j]);
fclose(fp);

    int choice, choice2;
    while (1&&flag!=1)
    {
        printf("\n\t\t\t\t\t\tMenu:\n");
        printf("\t\t\t\t\t\t1. Create account\n");
        printf("\t\t\t\t\t\t2. Login\n");
        printf("\t\t\t\t\t\t3. Exit\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

switch (choice)
{
    case 1:
        createUser();
        break;
    case 2:
    {
        flag = loginUser();

        while (flag == 1)
        {
            printf("\n----------------------------------------------------\n");
            printf("\n1--display the details\n"); //done
            printf("2--Find shortest path\n");     //dijstra`s algorithm
            printf("3--Find minimum distance to cover different cities from a city\n"); //kruskal
            printf("4--Sort cities.\n");                                               // insertion or selection sort
            printf("5--Search whether your city appears in health camp plan.\n");
            printf("6--Logout\n");

           printf("\nEnter your choice\n");
            scanf("%d", &choice2);
            switch (choice2)
            {
                case 1:
                    printf("\n___________________________________________\n");
                    for (int j = 0; j < num; j++)
                        displayCity(&city[j]);
                    break;
                case 2:
                    printf("Enter graph file: ");
                    scanf("%s", gfname);
                    int graph[5][5];
                    FILE *fp2 = fopen(gfname, "r");
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                            fscanf(fp2, "%d", &graph[i][j]);
                    }
                    fclose(fp2);
                    printf("Enter the source node\n");
                    int source;
                    scanf("%d", &source);
                    Dijkstra(graph, 5, source, city);
                    break;
                case 3: printf("Enter graph file: ");
                    scanf("%s", gfname);
                    FILE *fp3 = fopen(gfname, "r");
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                            fscanf(fp2, "%d", &graph[i][j]);
                    }
                    fclose(fp2);

                    kruskalAlgo(5, graph);
                    break;
                case 4:
                    printf("Sort cities based on:\n");
                    printf("\t1. City Name\n");
                    printf("\t2. Pincode\n");
                    printf("\t3. Population\n");
                    printf("\t4. Number of Hospitals\n");
                    printf("\t5. Number of Patients\n");
                    printf("\t6. Number of Doctors\n");
                    printf("\t7. City Code\n");

                    scanf("%d", &sortCh);

                    if (sortCh == 1)
                        cmp = compareCityName;
                    else if (sortCh == 2)
                        cmp = comparePincode;
                    else if (sortCh == 3)
                        cmp = comparePopulation;
                    else if (sortCh == 4)
                        cmp = compareNumHospitals;
                    else if (sortCh == 5)
                        cmp = compareNumPatients;
                    else if (sortCh == 6)
                        cmp = compareNumDoctors;
                    else if (sortCh == 7)
                        cmp = compareCityCode;
                    else
                    {
                        // Handle invalid choice
                        printf("Invalid choice. Please choose a number between 1 and 7.\n");
                    }

                    mergeSort(city, 0, num - 1,cmp);
                    break;
                case 5:
                    printf("Enter city name to search:");
                    scanf("%s",searchCity);
                    readFile(fname,content);
                    flag1=KMPSearch(searchCity,content);
                    if(flag1==1)
                    {
                                    const WORD darkGreen = 2;
                        // Get the handle to the console
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole,darkGreen| FOREGROUND_INTENSITY);
                        printf("Yes, your city is in health camp plan.\n");
                        // Reset the text color to default (you may want to do this after printing colored text)
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else
                    {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole,FOREGROUND_RED| FOREGROUND_INTENSITY);
                        printf("No, your city does n't appear in health camp plan.\n");
                        // Reset the text color to default (you may want to do this after printing colored text)
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    break;

                case 6:
                    printf("");
                    const WORD darkGreen = 2;
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, darkGreen | FOREGROUND_INTENSITY);
                    printf("You are now logged out..!!\n");
                    // Reset the text color to default (you may want to do this after printing colored text)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    flag = 0;
                    break;
                default:
                    printf("Enter correct Choice\n");
                    break;
            }
        }
    }
    break;
    case 3:
        printf("");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Thank you for using our app.\n");
        // Reset the text color to default (you may want to do this after printing colored text)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        exit(0);
    default:
        printf("");
        HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole1, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Invalid choice. Please try again.\n");
        // Reset the text color to default (you may want to do this after printing colored text)
        SetConsoleTextAttribute(hConsole1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
}
    return 0;
}
/* ___________________________________
        Functions starts
    ___________________________________
*/
void readCity(FILE *fp,struct node *c)
{
    fscanf(fp,"%s",c->data.cityName);
    fscanf(fp,"%d",&c->data.pincode);
    fscanf(fp,"%d",&c->data.population);
    fscanf(fp,"%d",&c->data.numHospitals);
    fscanf(fp,"%d",&c->data.numPatients);
    fscanf(fp,"%d",&c->data.numDoctors);
    fscanf(fp,"%d",&c->data.cityCode);
}

void displayCity(struct node *c)
{
    printf("City name:%s\n",c->data.cityName);
    printf("City code:%d\n",c->data.cityCode);
    printf("Pincode:%d\n",c->data.pincode);
    printf("Population:%d\n",c->data.population);
    printf("Number of hospitals:%d\n",c->data.numHospitals);
    printf("Number of patients:%d\n",c->data.numPatients);
    printf("Number of doctors:%d\n",c->data.numDoctors);
    printf("\n-----------------------------------------\n");
}
void Dijkstra(int Graph[MAX][MAX], int n, int start,struct node *city)
{
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < n; i++)
    {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1)
  {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  // Printing the distance
  for (i = 0; i < n; i++)
    if (i != start)
    {
      printf("\nDistance from %s to %s : %d",city[start].data.cityName,city[i].data.cityName, distance[i]);
    }
}

// Function to merge two subarrays of struct node arr[]
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct node arr[], int l, int m, int r,int (*cmp)(const struct node *, const struct node *))
{
    int i;
    int j;
    int k;
    int n1;
    n1 = m - l + 1;
    int n2;
    n2 = r - m;

    // Create temporary arrays
    struct node L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (cmp(&L[i], &R[j]) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
        {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(struct node arr[], int l, int r,    int (*cmp)(const struct node *, const struct node *))
{
    if (l < r)
        {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m,cmp);
        mergeSort(arr, m + 1, r,cmp);

        // Merge the sorted halves
        merge(arr, l, m, r,cmp);
    }
}


//All the compare functions

// Example comparator function to sort based on pincode
int comparePincode(const struct node *a, const struct node *b)
 {
    return a->data.pincode - b->data.pincode;
}

// Example comparator function to sort based on cityName
int compareCityName(const struct node *a, const struct node *b)
 {
    return strcmp(a->data.cityName, b->data.cityName);
}

// Example comparator function to sort based on population
int comparePopulation(const struct node *a, const struct node *b)
{
    return a->data.population - b->data.population;
}

// Example comparator function to sort based on cityCode
int compareCityCode(const struct node *a, const struct node *b)
{
    return a->data.cityCode - b->data.cityCode;
}

// Example comparator function to sort based on numHospitals
int compareNumHospitals(const struct node *a, const struct node *b)
{
    return a->data.numHospitals - b->data.numHospitals;
}

// Example comparator function to sort based on numPatients
int compareNumPatients(const struct node *a, const struct node *b)
{
    return a->data.numPatients - b->data.numPatients;
}

// Example comparator function to sort based on numDoctors
int compareNumDoctors(const struct node *a, const struct node *b)
 {
    int ans=a->data.numDoctors - b->data.numDoctors;
    return ans;
}

void computeLPSArray(char pat[], int M, int lps [])
{
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(char pat [], char txt[])
{
    int M = strlen(pat);
    int N = strlen(txt);

    int lps[M];
    computeLPSArray(pat, M, lps);

    int i = 0;
    int j = 0;
    while (i < N)
    {
        if (tolower(pat[j]) == tolower(txt[i]))
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return 1;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
    return 0;
}

// Function to read file content and print it
void readFile(char fname [],char content [])
{
    long fileSize;
    // Open the file for reading
     FILE * fp = fopen(fname, "r");

    if (fp == NULL)
        {
        perror("Error opening file");
        return; // Return without printing if there's an error
    }

    // Determine the file size
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Ensure the file size does not exceed the capacity of the content array
    if (fileSize >= 1000)
        {
        fclose(fp);
        printf("File is too large for the program to handle.\n");
        return; // Return without printing if the file is too large
    }

    // Read the file content
    fread(content, 1, fileSize, fp);

    // Add a null terminator at the end of the string
    content[fileSize] = '\0';

    // Close the file
    fclose(fp);
}

int comparator(const void* p1, const void* p2)
{
    const int(*x)[3] = p1;
    const int(*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

// Initialization of parent[] and rank[] arrays
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Function to find the parent of a node
int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component]
           = findParent(parent, parent[component]);
}

// Function to unite two sets
void unionSet(int u, int v, int parent[], int rank[], int n)
{
    // Finding the parents
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;

        // Since the rank increases if
        // the ranks of two sets are same
        rank[u]++;
    }
}

// Function to find the MST
void kruskalAlgo(int n, int edge[n][3])
{
    // First we sort the edge array in ascending order
    // so that we can access minimum distances/cost
    qsort(edge, n, sizeof(edge[0]), comparator);

    int parent[n];
    int rank[n];

    // Function to initialize parent[] and rank[]
    makeSet(parent, rank, n);

    // To store the minimun cost
    int minCost = 0;

    printf(
        "Following are the edges in the constructed MST\n");
    for (int i = 0; i < n; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        // If the parents are different that
        // means they are in different sets so
        // union them
        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0],
                   edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}
