// hw7_ATupek.pde
// Ann Tupek
// 8 Dec 2014
//
// CS381 HW 7
// Conway's Game of Life
// for hw7_ATupek.html

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

Cell[][] cellArray = new Cell[50][40];

int lastUpdateTime = 0;

//determine number of filled neighbors
void determineNumNeighbors()
{
    for(int i = 1; i < 49; ++i)
    {
        for(int j = 1; j < 39; ++j)
        {
            cellArray[i][j].numFilledNeighbors = 0;
            if(cellArray[i-1][j-1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i][j-1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i+1][j-1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i-1][j].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i+1][j].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i-1][j+1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i][j+1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
            if(cellArray[i+1][j+1].filled == true)
            {
                cellArray[i][j].numFilledNeighbors++;
            }
        }
    }
}

//determine filled status of cells
void determineCellStatus()
{
    for(int i = 1; i < 49; ++i)
    {
        for(int j = 1; j < 39; ++j)
        {
            if(cellArray[i][j].filled == false && cellArray[i][j].numFilledNeighbors == 3)
            {
                cellArray[i][j].filled = true;
            }
            if(cellArray[i][j].filled == true && (cellArray[i][j].numFilledNeighbors == 0 ||
                cellArray[i][j].numFilledNeighbors == 1 || cellArray[i][j].numFilledNeighbors >= 4))
            {
                cellArray[i][j].filled = false;
            }
        }
    }   
}

//update
void update()
{
  determineNumNeighbors();
  determineCellStatus();
  for(int i = 1; i< 50; ++i)
    {
        for(int j = 1; j<40; ++j)
        {
            fill(255, 255, 255);
            rect(0+10*i, 0+10*j, 10, 10);
            if(cellArray[i][j].filled == true)
            {
              fill(0, 10*i, 10*j);
              rect(0+10*i, 0+10*j, 10, 10);
            }
        }
    }
}

//initial settings for Pulsar
void pulsarSetup()
{
    cellArray[15][17].filled = true;
    cellArray[15][18].filled = true;
    cellArray[15][19].filled = true;
    cellArray[15][23].filled = true;
    cellArray[15][24].filled = true;
    cellArray[15][25].filled = true;
    cellArray[17][15].filled = true;
    cellArray[18][15].filled = true;
    cellArray[19][15].filled = true;
    cellArray[17][20].filled = true;
    cellArray[18][20].filled = true;
    cellArray[19][20].filled = true;
    cellArray[17][22].filled = true;
    cellArray[18][22].filled = true;
    cellArray[19][22].filled = true;
    cellArray[17][27].filled = true;
    cellArray[18][27].filled = true;
    cellArray[19][27].filled = true;
    cellArray[20][17].filled = true;
    cellArray[20][18].filled = true;
    cellArray[20][19].filled = true;
    cellArray[20][23].filled = true;
    cellArray[20][24].filled = true;
    cellArray[20][25].filled = true;
    cellArray[22][17].filled = true;
    cellArray[22][18].filled = true;
    cellArray[22][19].filled = true;
    cellArray[22][23].filled = true;
    cellArray[22][24].filled = true;
    cellArray[22][25].filled = true;
    cellArray[23][15].filled = true;
    cellArray[24][15].filled = true;
    cellArray[25][15].filled = true;
    cellArray[23][20].filled = true;
    cellArray[24][20].filled = true;
    cellArray[25][20].filled = true;
    cellArray[23][22].filled = true;
    cellArray[24][22].filled = true;
    cellArray[25][22].filled = true;
    cellArray[23][27].filled = true;
    cellArray[24][27].filled = true;
    cellArray[25][27].filled = true;
    cellArray[27][17].filled = true;
    cellArray[27][18].filled = true;
    cellArray[27][19].filled = true;
    cellArray[27][23].filled = true;
    cellArray[27][24].filled = true;
    cellArray[27][25].filled = true;
}

//initial setting for Gosper Glider Gun
void gosperSetup()
{
    cellArray[1][5].filled = true;
    cellArray[1][6].filled = true;
    cellArray[2][5].filled = true;
    cellArray[2][6].filled = true;
    
    cellArray[11][5].filled = true;
    cellArray[11][6].filled = true;
    cellArray[11][7].filled = true;
    cellArray[12][4].filled = true;
    cellArray[12][8].filled = true;
    cellArray[13][3].filled = true;
    cellArray[13][9].filled = true;
    cellArray[14][3].filled = true;
    cellArray[14][9].filled = true;
    cellArray[15][6].filled = true;
    cellArray[16][4].filled = true;
    cellArray[16][8].filled = true;
    cellArray[17][5].filled = true;
    cellArray[17][6].filled = true;
    cellArray[17][7].filled = true;
    cellArray[18][6].filled = true;
    
    cellArray[21][3].filled = true;
    cellArray[21][4].filled = true;
    cellArray[21][5].filled = true;
    cellArray[22][3].filled = true;
    cellArray[22][4].filled = true;
    cellArray[22][5].filled = true;
    cellArray[23][2].filled = true;
    cellArray[23][6].filled = true;
    cellArray[25][1].filled = true;
    cellArray[25][2].filled = true;
    cellArray[25][6].filled = true;
    cellArray[25][7].filled = true;
    
    cellArray[35][3].filled = true;
    cellArray[35][4].filled = true;
    cellArray[36][3].filled = true;
    cellArray[36][4].filled = true;
}

void gosper()
{
  clear();
  gosperSetup();
}

void pulsar()
{
  clear();
  pulsarSetup();
}

//initial setting for Small Things
void smallThings()
{
    clear();
    for(int i = 0; i<4; ++i)
    {
    //toad
    cellArray[3+12*i][5].filled = true;
    cellArray[4+12*i][5].filled = true;
    cellArray[5+12*i][5].filled = true;
    cellArray[4+12*i][6].filled = true;
    cellArray[5+12*i][6].filled = true;
    cellArray[6+12*i][6].filled = true;
    
    //blinker
    cellArray[11+12*i][5].filled = true;
    cellArray[11+12*i][6].filled = true;
    cellArray[11+12*i][7].filled = true;
    }
    for(int i = 0; i<8; ++i)
    {
    //glider
    cellArray[5+5*i][10].filled = true;
    cellArray[6+5*i][11].filled = true;
    cellArray[4+5*i][12].filled = true;
    cellArray[5+5*i][12].filled = true;
    cellArray[6+5*i][12].filled = true;
    }
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
      for(int i = 0; i<50; ++i)
    {
      for(int j = 0; j<40; ++j)
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
    size(510, 410);
    background(0, 177, 177);
    
    for(int i = 0; i< 50; ++i)
    {
        for(int j = 0; j<40; ++j)
        {
          cellArray[i][j] = new Cell(false, 0);
        }
    }
    
    gosper();
    determineNumNeighbors();
    
    for(int i = 1; i< 50; ++i)
    {
        for(int j = 1; j<40; ++j)
        {
            noStroke();
            rect(0+10*i, 0+10*j, 10, 10);
            if(cellArray[i][j].filled == true)
            {
                fill(255, 255, 255);
                rect(0+10*i, 0+10*j, 10, 10);
            }
        }
    }
}

// draw
// Processing.js drawing function
void draw()
{
  int m = millis();

  if(m>lastUpdateTime+100)
  {
    lastUpdateTime = m;
    update();
  }

}

