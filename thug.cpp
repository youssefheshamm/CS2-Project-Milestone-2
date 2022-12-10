#include "thug.h"
//Please make sure to run the app at least once and then
// move all the assets to the project build file for the
// program to work correctly
#define ROW 17
#define COL 23
#define FLT_MAX 3.40282e+038
int xp;
int yp;


typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > pPair;


thug::thug(){health =2; die = false;}
void thug::setthug(int mapData[17][23], int r, int c)
{
    // Set Image
    QPixmap npc("thug.png");
    npc = npc.scaledToWidth(50);
    npc = npc.scaledToHeight(50);
    setPixmap(npc);

    // Set Position
    row = r;
    column = c;
    setPos(50 + column * 50, 50 + row * 50);

    // Set data Array
    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 23; j++)
            map[i][j] = mapData[i][j];


}
void thug::setpng( QPixmap npc){

    setPixmap(npc);
}
void thug:: resetpos(int r, int c){
row = r;
column = c;
setPos(50 + column * 50, 50 + row * 50);
}
// A* algorthim
struct cell {

    int parent_i, parent_j;

    double f, g, h;
};


bool isValid(int row, int col)
{

    return (row >= 0) && (row < ROW) && (col >= 0)
        && (col < COL);
}


bool isUnBlocked(int grid[][COL], int row, int col)
{

    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}


bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}


double calculateHValue(int row, int col, Pair dest)
{

    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}


void tracePath(cell cellDetails[][COL], Pair dest)
{

    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    int counter = 0;
    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();

        if (counter == 1) {
            xp = p.first;
            yp = p.second;

        }
        counter++;
    }

    return;
}


void aStarSearch(int grid[][COL], Pair src, Pair dest)
{


    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));


    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }


    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;


    set<pPair> openList;


    openList.insert(make_pair(0.0, make_pair(i, j)));




    while (!openList.empty()) {
        pPair p = *openList.begin();


        openList.erase(openList.begin());


        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;


        double gNew, hNew, fNew;


        if (isValid(i - 1, j) == true) {

            if (isDestination(i - 1, j, dest) == true) {

                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;

                tracePath(cellDetails, dest);

                return;
            }

            else if (closedList[i - 1][j] == false
                && isUnBlocked(grid, i - 1, j)
                == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;


                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j)));


                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }




        if (isValid(i + 1, j) == true) {

            if (isDestination(i + 1, j, dest) == true) {

                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;

                tracePath(cellDetails, dest);

                return;
            }

            else if (closedList[i + 1][j] == false
                && isUnBlocked(grid, i + 1, j)
                == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;


                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j)));

                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }


        if (isValid(i, j + 1) == true) {

            if (isDestination(i, j + 1, dest) == true) {

                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;

                tracePath(cellDetails, dest);

                return;
            }


            else if (closedList[i][j + 1] == false
                && isUnBlocked(grid, i, j + 1)
                == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));


                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }


        if (isValid(i, j - 1) == true) {

            if (isDestination(i, j - 1, dest) == true) {

                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;

                tracePath(cellDetails, dest);

                return;
            }


            else if (closedList[i][j - 1] == false
                && isUnBlocked(grid, i, j - 1)
                == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j - 1)));


                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }



}

    return;
}

void shortest(int tr, int tc, int pr, int pc, int map[17][23]){
    int grid[ROW][COL];
    for(int i=0;i<17;i++){
        for(int j=0; j<23;j++){
            if(map[i][j]>=1000){
                grid[i][j]=0;
            }else {grid[i][j]=1;}
        }
    }
    Pair src = make_pair(tr, tc);

        // Destination is the left-most top-most corner
        Pair dest = make_pair(pr, pc);

        aStarSearch(grid, src, dest);
}




//thug movement
void thug::move(int pr, int pc)
{


    shortest(row, column, pr, pc, map);

    row = xp;
    column = yp;
     setPos(50 + column * 50, 50 + row * 50);


}
