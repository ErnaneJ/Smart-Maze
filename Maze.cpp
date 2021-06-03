#include <iostream>
#include <cstdlib> //for using srand() and rand() in generating random values;
#include <ctime> //for using date and time functions with time() used with srand() to avoid sequence repetition;
#include <stdlib.h> //just for aesthetic use, i imported the library to use the system() function with the parameter "clear||cls" which clears the windows or linux terminal screen;

using namespace std;

/*--------------------| Constants |--------------------*/
#define VERTICAL_WALL '@'
#define HORIZONTAL_WALL '@' 
#define EMPTY ' ' 
#define OBSTACLE '#' 
#define MAX 50
#define PROBABILITY 0.7 
#define START 'S' 
#define END 'E' 

#define PATH '.'
#define NO_WAY_OUT 'x'


/*--------------------| Usual variables |--------------------*/
int startLine, startColumn, endLine, endColumn;
float randomNumber;

/*--------------------| Functions |--------------------*/
void startBoard(char board[][MAX], int size);
void printMaze(char board[][MAX], int size);

bool emptyPosition(char maze[][MAX], int size, int line, int column);
bool tryWay(char maze[][MAX], int size, int nextLine, int nextColumn);
bool lookingForPath(char maze[][MAX], int size, int currentLine, int currentColumn);

/*--------------------| Main |--------------------*/
int main () {
    srand(time(0));
    char checker = 'Y';
    do{
        char maze[MAX][MAX];
        int size;
        system("clear||cls");
        cout<<"> Enter the size of the maze: ";cin>>size;
        system("clear||cls");
        startBoard(maze, size);
        printMaze(maze, size);
 
        bool found = lookingForPath(maze, size, startLine, startColumn); 
        if (found) { 
            cout<<"\n> I found the way! :) :)\n> The output is in the position ["<<endLine<<"]["<<endColumn<<"] from the board!"; 
            checker = 'N';
        } else { 
            cout<<"\n> Sorry! the generated maze has no possible path. :("<<endl; 
            cout<<"\n> Do you want to generate a new one? Yes(Y) or No(N): ";cin>>checker;
        }
    } while (checker == 'Y' || checker == 'y');
    
    cout<<"\n\n> Developed with S2 by Ernane Ferreira"<<endl;

    return 0;
}

void startBoard(char maze[][MAX], int size){ 
	
    
    
    for(int i = 0; i < size; i++) { 
	    maze[i][0] = VERTICAL_WALL; 
		maze[i][size - 1] = VERTICAL_WALL; 
		maze[0][i] = HORIZONTAL_WALL; 
		maze[size - 1][i] = HORIZONTAL_WALL ;    
	} 
	for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            randomNumber =  (float) rand()/RAND_MAX;
            if (randomNumber > PROBABILITY) {
                maze[i][j] = OBSTACLE;
            } else {
                maze[i][j] = EMPTY;
            }
        }
    }
    //Positioning the start - START - of the maze
    startLine = (rand() % (size-1)) + 1;
    if(startLine==0 || startLine==(size-1)){
        startColumn =(rand() % (size-1)) + 1;
    }else{
        startColumn=0;
    }
    maze[startLine][startColumn] = START;

    //Positioning the end (exit) - END - of the maze (F)
    endLine = (rand() % (size-1)) + 1;
    if(endLine==0 || endLine==(size-1)){
        endColumn =(rand() % (size-1)) + 1;
    }else{
        endColumn=(size-1);
    }
    maze[endLine][endColumn] = END;
}


void printMaze(char maze[][MAX], int size){
    for (int i = 0; i < size; i++) { 
		for (int j = 0; j < size; j++) { 
			cout<<(maze[i][j])<<" "; 
		} 
		cout<<endl;
	} 
}


bool lookingForPath(char maze[][MAX], int size, int currentLine, int currentColumn){
    int nextLine; 
	int nextColumn; 
	bool found = false; 
	//trying the closest position above the current one;
	nextLine = currentLine - 1; 
	nextColumn = currentColumn; 
	found = tryWay(maze, size,nextLine, nextColumn); 
	//trying the closest position below the current one;;
	if (!found) { 
		nextLine = currentLine + 1; 
		nextColumn = currentColumn; 
		found = tryWay(maze, size, nextLine, nextColumn); 
	} 
	//trying the closest position to the left of the current one;
	if (!found) { 
		nextLine = currentLine; 
		nextColumn = currentColumn - 1; 
		found = tryWay(maze, size, nextLine, nextColumn); 
	} 
	//trying the closest position to the right of the current;
	if (!found) { 
		nextLine = currentLine; 
		nextColumn = currentColumn + 1; 
		found = tryWay(maze, size, nextLine, nextColumn); 
	} 
	return found; 
}

bool tryWay(char maze[][MAX], int size, int nextLine, int nextColumn){
    bool found = false; 
	if (maze[nextLine][nextColumn] == END) { 
		found = true; 
	} else if (emptyPosition(maze, size,nextLine, nextColumn)) { 
		//Check the position and mark if possible as a possible path (.);
		maze[nextLine][nextColumn] = PATH; 
        system("clear||cls");
		printMaze(maze, size);
		found = lookingForPath(maze, size,nextLine, nextColumn); 
		if (!found) { 
            //Check the position and mark if it does not give any output and does not show possible path (x);
			maze[nextLine][nextColumn] = NO_WAY_OUT; 
            system("clear||cls");
			printMaze(maze, size); 
		} 
	} 
	return found; 
}

bool emptyPosition(char maze[][MAX], int size, int line, int column) { 
	bool empty = false; 
	if (line >= 0 && column >= 0 && line < size && column < size) { 
		empty = (maze[line][column] == EMPTY); 
	} 
	return empty; 
}