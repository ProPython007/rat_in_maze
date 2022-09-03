
//BINARY MATRIX MAZE SOLVER!!! -by SAYAN KARMAKAR

#include<stdio.h>           //For standard i/o functions
#include<stdbool.h>         //For using true false
#include<stdlib.h>          //For using rand()
#include<time.h>            //For initializing rand() and fetching date and time

// Delay function for pretty printing in windows
void delay(float number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;
	// Storing start time
	clock_t start_time = clock();
	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}

// Function to generate a random integer
int findRandom()
{
  int num = rand() % 2;
  return num;
}

// Fucntion for color green in the terminal
void colorq(){
  printf("\x1b[32m");        //ANSI escape codes green
}

// Fucntion for color majenda in the terminal
void colorm(){
  printf("\x1b[35m");        //ANSI escape codes magenda
}

// Function for color cyan in the terminal
void color(){
  printf("\033[0;36m");      //ANSI escape codes cyan
}

// Fucntion for color red in the terminal
void colorr(){
  printf("\x1b[31m");        //ANSI escape codes red
}

// Function for resetting the terminal color
void reset(){
  printf("\033[0m");
}

// Funtion to differentiante between walls(0) and paths(1)
bool isOk(int arr[20][20], int x, int y, int ex, int ey)
{
  if(x<=ex && y<=ey && arr[x][y]==1){
    return true;            //If 1 then ok
  }
  return false;             //Or else its a wall
}

//Recursive funtion to determine the solution matrix using backtracking
bool ratMap(int arr[20][20], int x, int y, int ex, int ey, int solMap[20][20]){
  if((x==ex) && (y==ey)){
    solMap[x][y]=1;
    return true;     //If dest. reached return true
  }

  if(isOk(arr,x,y,ex,ey)){     //Check if it is a path or not first
    solMap[x][y]=1;      //Assume a potential solution path
    if(ratMap(arr,x+1,y,ex,ey,solMap)){
      return true;     //Check in right direction
    }
    if(ratMap(arr,x,y+1,ex,ey,solMap)){
      return true;     //Check in down direction
    }
    solMap[x][y]=0;
    return false;     //If path can't be found then back track
  }
  return false;     //If counter a wall return false
}

// Recursive funtion to determine the solution matrix using backtracking
bool ratMapProgress(int arr[20][20], int x, int y, int ex, int ey, int solMap[20][20], int n)
{
  // Displaying the progress of solmap
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(solMap[i][j]==1){
        colorm();
        printf("  %d",solMap[i][j]);   //Printing 1s with color
        if(n<=5)
          delay(0.1);                  //Delay for pretty printing
        else if(n<=10)
          delay(0.05);
        else
          delay(0.001);

        reset();
      }
      else{
        printf("  %d",solMap[i][j]);
      }
    }
    printf("\n");
  }
	printf("\nSearching...\b\b\b\b\b\b\b\b\b\b\b\b");
  for(int i=0; i<n+1; i++){           //For going to initial cursor position
    printf("\033[A");                 //ANSI code for going up a line
  }

  //Finding the path
  if((x==ex) && (y==ey)){
    solMap[x][y]=1;
    return true;                     //If dest. reached return true
  }

  if(isOk(arr,x,y,ex,ey))            //Check if it is a path or not first
  {
    solMap[x][y]=1;                 //Assume a potential solution path
    if(ratMapProgress(arr,x+1,y,ex,ey,solMap,n)){
      return true;                  //Check in right direction
    }
    if(ratMapProgress(arr,x,y+1,ex,ey,solMap,n)){
      return true;                  //Check in down direction
    }
    solMap[x][y]=0;
    return false;                  //If path can't be found then back track
  }

  return false;                    //If counter a wall return false
}


// MAIN FUNCTION
int main(){
  // START
  FILE *f;             //Initializing a file var
  int n, ch, temp;     //n: dim, ch: choice temp: temporary var
  int sx, sy;          //sx: starting row, sy: starting col
  int ex, ey;          //ex: ending row, ey: ending col
  int arr[20][20], solMap[20][20]; //initializing aze matrix and solution matrix
  bool flag = false;               //initializing flag as default false

  f = fopen("RatInMaze.txt","a");  //Opening the file for record keeping purpose

  // Handling file exception
  if(f == NULL){
    printf("\nFile error encountered!!!\n");
  }

  time_t t;   //The time_t is a data type defined for storing system time values
  time(&t);   //Setting current calender date & time

  // ctime() returns the string representing the localtime based on the argument timer.
  fprintf(f,"\n>>%s", ctime(&t));

  printf("\nBINARY MATRIX MAZE SOLVER!!! -by SAYAN KARMAKAR");
  printf("\n\nEnter the size of the binary matrix maze (max 20): ");
  fprintf(f,"Enter the size of the binary matrix maze (max 20): ");
  scanf("%d",&n);               //Taking dim. input in n
  fprintf(f,"%d",n);


  printf("\nEnter 0 for default (1,1)/(%d,%d) & 1 for user start/end coordinates: ",n,n);
  fprintf(f,"\nEnter 0 for default (1,1)/(%d,%d) & 1 for user start/end coordinates: ",n,n);
  scanf("%d",&temp);            //Asking for default or custom start and end points
  fprintf(f,"%d",temp);

  if(temp){
    printf("\nEnter the starting coordinate: ");
    fprintf(f,"\nEnter the starting coordinate: ");
    scanf("%d %d",&sx, &sy);   //Setting up custom starting points
    fprintf(f,"%d,%d",sx, sy); //Setting up custom ending points
    sx--;
    sy--;

    printf("\nEnter the ending coordinate: ");
    fprintf(f,"\nEnter the ending coordinate: ");
    scanf("%d %d",&ex, &ey);   //Setting up custom ending points
    fprintf(f,"%d,%d",ex, ey);
    ex--;
    ey--;
  }
  else{
    sx = 0;
    sy = 0;                    //Setting up default starting points
    ex = n-1;
    ey = n-1;                  //Setting up default ending points
  }

  printf("\nEnter 1 for user input maze and 2 for random maze: ");
  fprintf(f,"\nEnter 1 for user input maze and 2 for random maze: ");
  scanf("%d",&ch);
  fprintf(f,"%d",ch);

  if(ch==1){
    // Taking user input maze matrix
    fprintf(f,"\n\nInput Matrix is:\n\n");
    printf("\nEnter your matrix:\n\n");
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        scanf("%d",&arr[i][j]);
        fprintf(f,"  %d",arr[i][j]);
      }
      fprintf(f,"\n");
    }

    // Initializing sol matrix with 0s
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        solMap[i][j]=0;
      }
    }

    printf("\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
    fprintf(f,"\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
    // Function Call
    if(ratMap(arr,sx,sy,ex,ey,solMap)){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          solMap[i][j]=0;
        }
      }
      ratMapProgress(arr,sx,sy,ex,ey,solMap,n);
      // Solution matrix representation
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          if(solMap[i][j]==1){
            if((i==sx && j==sy) || (i==ex && j==ey)){
              colorr();
              delay(0.1);                    //Delay for pretty printing
              printf("  %d",solMap[i][j]);   //Printing 1s with color
              delay(0.1);                    //Delay for pretty printing
              reset();
            }
            else{
              color();
              delay(0.1);                    //Delay for pretty printing
              printf("  %d",solMap[i][j]);   //Printing 1s with color
              delay(0.1);                    //Delay for pretty printing
              reset();
            }
          }
          else{
            printf("  %d",solMap[i][j]);
          }
          fprintf(f,"  %d",solMap[i][j]);
        }
        printf("\n");
        fprintf(f,"\n");
      }
			printf("\nPath found!!!");
			fprintf(f,"\nPath found!!!");
			printf("\n\nGame data sucessfully stored in RatInMaze.txt!!!");
      printf("\n\n");
      fprintf(f,"\n\n");
    }
    else{
      // If no path exists
      printf("No valid path exist!!!\n\n");
      fprintf(f,"No valid path exist!!!\n\n");
    }
  }

  else if(ch==2){
    // INITIALISING A MAZE
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        arr[i][j] = 0;
      }
    }

    //FIXING ATLEAST ONE PATH IN THE MAZE RANDOMELY
    srand(time(0));                  //Initializing the rand()
    for(int i=0; i<ex+1; i++){
      for(int j=0; j<ey+1; j++){

        if(i == sx && j == sy){
          arr[i][j] = 1;
          flag = true;
        }
        if(flag){
          if(i == ex && j == ey){
            arr[i][j] = 1;
            break;
          }
          temp = findRandom();       //For randomising the path making
          if(temp == 0){
            if(i!=(ex)){
              arr[i+1][j]=1;
              i++;
              j--;
              continue;
            }
            else{
              arr[i][j+1]=1;
              j--;
              continue;
            }
          }
          if(temp == 1){
            if(j!=(ey)){
              arr[i][j+1]=1;
              continue;
            }
            else{
              arr[i+1][j]=1;
              j--;
              continue;
            }
          }
        }
      }
    }

    // RANDOMISING THE MAZE
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(arr[i][j] == 1)
          continue;
        else
          arr[i][j] = findRandom();   //Filling the 0s with random 1s or 0s
      }
    }

    // DISPLAYING THE MAZE
    printf("\nGenerated Random Maze:\n\n");
    fprintf(f,"\n\nGenerated Random Maze:\n\n");
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        if(arr[i][j]==1){
          colorq();
          printf("  %d",arr[i][j]);   //Printing 1s with color
          delay(0.1);                 //Delay for pretty printing
          reset();
        }
        else{
          printf("  %d",arr[i][j]);
          delay(0.01);                //Delay for pretty printing
        }
        fprintf(f,"  %d",arr[i][j]);
      }
      printf("\n");
      fprintf(f,"\n");
    }

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        solMap[i][j]=0;
      }
    }

    printf("\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
    fprintf(f,"\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
    // Function Call
    if(ratMap(arr,sx,sy,ex,ey,solMap)){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          solMap[i][j]=0;
        }
      }
      ratMapProgress(arr,sx,sy,ex,ey,solMap,n);
      // Displaying the sol matrix
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          if(solMap[i][j]==1){
            if((i==sx && j==sy) || (i==ex && j==ey)){
              colorr();
              delay(0.1);                    //Delay for pretty printing
              printf("  %d",solMap[i][j]);   //Printing 1s with color
              delay(0.1);                    //Delay for pretty printing
              reset();
            }
            else{
              color();
              delay(0.1);                    //Delay for pretty printing
              printf("  %d",solMap[i][j]);   //Printing 1s with color
              delay(0.1);                    //Delay for pretty printing
              reset();
            }
          }
          else{
            printf("  %d",solMap[i][j]);
          }
          fprintf(f,"  %d",solMap[i][j]);
        }
        printf("\n");
        fprintf(f,"\n");
      }
			printf("\nPath found!!!");
			fprintf(f,"\nPath found!!!");
			printf("\n\nGame data sucessfully stored in RatInMaze.txt!!!");
      printf("\n\n");
      fprintf(f,"\n\n");

    }
    else{
      // If no path exits for custom input points
      printf("No valid path exist!!!\n\n");
      fprintf(f,"No valid path exist!!!\n\n");
    }
  }

  else{
    // If any invalid user inputs encountered
    printf("\nEnter valid choices!!!\n");
    fprintf(f,"\nEnter valid choices!!!\n");
  }

  // Closing the file
  fclose(f);
  return 0;
  // END
}
