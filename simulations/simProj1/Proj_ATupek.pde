// Proj1_ATupek.pde
// Ann Tupek
// Project 1 Draft
// Due 2/27/15
  
// Cellular Automaton
// Implemented in Processing
// for Proj1_ATupek.html

//color for Rule 30 conus textile: 210, 105, 30
//color for Rule 90 sierpinski gasket: 100, 149, 237
// decent source for colors: http://www.rapidtables.com/web/color/RGB_Color.htm



// Cell class
class Cell
{
    boolean filled;
    int numFilledNeighbors;

    Cell()
    {
        filled = false;
        numFilledNeighbors = 0;
    }

    Cell(boolean fillStatus, int numFillNeigh)
    {
        filled = fillStatus;
        numFilledNeighbors = numFillNeigh;
    }
}

Cell[][] cellArray = new Cell[100][50];

int lastUpdateTime = 0;

boolean checkLeft(int i, int j)
{
    return cellArray[i-1][j].filled;
}

boolean checkRight(int i, int j)
{
    return cellArray[i+1][j].filled;
}

boolean checkCell(int i, int j)
{
    return cellArray[i][j].filled;
}

//update
void update()
{

  for(int i = 1; i< 99; ++i)
    {
        for(int j = 1; j<49; ++j)
        {
            //fill(255, 255, 255);
            //rect(0+10*i, 0+10*j, 10, 10);
            //Rule 30?!?!?!
            /*if((checkCell(i, j) && checkLeft(i, j) && !checkRight(i, j))||
                (checkCell(i, j) && !checkLeft(i, j) && checkRight(i, j))||
                (checkCell(i, j) && !checkLeft(i, j) && !checkRight(i, j))||
                (!checkCell(i, j) && !checkLeft(i, j) && checkRight(i, j)))*/
            //if(checkCell(i, j))
            //Rule 60?!?!?!
            if(!checkCell(i, j) && !checkRight(i, j))
            {
                cellArray[i][j+1].filled = checkLeft(i, j);

            }
            else
            {
                cellArray[i][j+1].filled = !checkLeft(i, j);
            }
            //Rule 57
            /*if((!checkCell(i, j) && !checkLeft(i, j) && !checkRight(i, j))||
                (checkCell(i, j) && !checkLeft(i, j) && checkRight(i, j))||
                (!checkCell(i, j) && checkLeft(i, j) && !checkRight(i, j))||
                (!checkCell(i, j) && checkLeft(i, j) && checkRight(i, j)))*/
            //{
            //    cellArray[i][j+1].filled = true;
            //}
            if(cellArray[i][j].filled == true)
            {
              fill(5*i, 105, 30);
              rect(0+10*i, 0+10*j, 10, 10);
            }
        }
    }
    //noLoop();
}

//initial settings for Pulsar
void pulsarSetup()
{
    cellArray[15][17].filled = true;

}

//initial setting for Gosper Glider Gun
void gosperSetup()
{
    cellArray[1][5].filled = true;

}

void gosper()
{
    clear();
  loop();
  gosperSetup();
}

void pulsar()
{
    clear();
  loop();
  pulsarSetup();
}

void ruleSetup()
{
    cellArray[50][1].filled = true;
}

//initial setting for Small Things
void rule30()
{
    clear();
    loop();
    ruleSetup();
}

//Gosper Glider Gun + Pulsar = Chaos
void chaos()
{
  clear();
  gosperSetup();
  pulsarSetup();
}

//clear the settings
void clear()
{
      for(int i = 0; i<100; ++i)
    {
      for(int j = 0; j<50; ++j)
      {
        cellArray[i][j].filled = false;
        cellArray[i][j].numFilledNeighbors = 0;
      }
    }
}

// setup
// Processing.js setup function
void setup()
{
    size(1010, 510);
    background(0, 0, 0);
    
    for(int i = 0; i< 100; ++i)
    {
        for(int j = 0; j<50; ++j)
        {
          cellArray[i][j] = new Cell(false, 0);
        }
    }

    //gosper();
    //determineNumNeighbors();
    rule30();
    
    for(int i = 1; i< 100; ++i)
    {
        for(int j = 1; j<50; ++j)
        {
            noStroke();
            rect(0+10*i, 0+10*j, 10, 10);
            /*if(cellArray[i][j].filled == true)
            {
                //fill(255, 255, 255);
                //rect(0+10*i, 0+10*j, 10, 10);
            }*/
        }
    }
}

// draw
// Processing.js drawing function
void draw()
{
//clear();
    resetMatrix();
  int m = millis();

  if(m>lastUpdateTime+100)
  {
    lastUpdateTime = m;
    update();
  }
  

}
