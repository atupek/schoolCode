// Proj1_ATupek.pde
// Ann Tupek
// Project 1
// Due 3/27/15
  
// Cellular Automata from Stephen Wolfram's A New Kind of Science
// I've implemented 5 rules.  For the final draft, I made the width & height
// of the grid variables and allow the user to set the initial starting point
// of the automata within the canvas.
// for Proj1_ATupek.html

// Cell class
class Cell
{
    boolean filled;

    Cell()
    {
        filled = false;
    }

    Cell(boolean fillStatus)
    {
        filled = fillStatus;
    }
}

int lastUpdateTime = 0;

int currentLine;

int currentRule;

int startX = 200;
int startY = 1;

int R;
int G;
int B;

int width = 400;
int height = 100;

Cell[][] cellArray = new Cell[width][height];

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
void updateCells30()
{
    if(currentLine<height-1)
    {
        for(int i = 1; i<width-1; i++)
        {
            //Rule 90
            if(!checkCell(i, currentLine) && !checkRight(i, currentLine))
            {
                cellArray[i][currentLine+1].filled = checkLeft(i, currentLine);

            }
            else
            {
                cellArray[i][currentLine+1].filled = !checkLeft(i, currentLine);
            }
        }
    }
    currentLine++;
}

void updateCells57()
{
    if(currentLine<height-1)
    {
        for(int i = 1; i<width-1; i++)
        {
            //Rule 57
            if((!checkCell(i, currentLine) && !checkLeft(i, currentLine) && !checkRight(i, currentLine))||
                (checkCell(i, currentLine) && !checkLeft(i, currentLine) && checkRight(i, currentLine))||
                (!checkCell(i, currentLine) && checkLeft(i, currentLine) && !checkRight(i, currentLine))||
                (!checkCell(i, currentLine) && checkLeft(i, currentLine) && checkRight(i, currentLine)))
            {
                cellArray[i][currentLine+1].filled = true;

            }
            else
            {
                cellArray[i][currentLine+1].filled = false;
            }
        }
    }
    currentLine++;
}

void updateCells90()
{
    if(currentLine<height-1)
    {
        for(int i = 1; i<width-1; i++)
        {
            //Rule 90 It's an XOR, but Processing doesn't have a logical XOR :-(
            if(!checkLeft(i, currentLine) && checkRight(i, currentLine)||
                checkLeft(i, currentLine) && !checkRight(i, currentLine))
            {
                cellArray[i][currentLine+1].filled = true;

            }
            else
            {
                cellArray[i][currentLine+1].filled = false;
            }
        }
    }
    currentLine++;
}

void updateCells145()
{
    if(currentLine<height-1)
    {
        for(int i = 1; i<width-1; i++)
        {
            //Rule 145
            if(!checkLeft(i, currentLine) && !checkRight(i, currentLine) && !checkCell(i, currentLine)||
                checkLeft(i, currentLine) && checkRight(i, currentLine) && checkCell(i, currentLine)||
                checkLeft(i, currentLine) && !checkRight(i, currentLine) && !checkCell(i, currentLine))
            {
                cellArray[i][currentLine+1].filled = true;

            }
            else
            {
                cellArray[i][currentLine+1].filled = false;
            }
        }
    }
    currentLine++;
}

void updateCells225()
{
    if(currentLine<height-1)
    {
        for(int i = 1; i<width-1; i++)
        {
            //Rule 225
            if(!checkLeft(i, currentLine) && !checkRight(i, currentLine) && !checkCell(i, currentLine)||
                checkLeft(i, currentLine) && checkRight(i, currentLine)||
                checkLeft(i, currentLine) && !checkRight(i, currentLine) && checkCell(i, currentLine))
            {
                cellArray[i][currentLine+1].filled = true;

            }
            else
            {
                cellArray[i][currentLine+1].filled = false;
            }
        }
    }
    currentLine++;
}

//drawCells
void drawCells()
{

  for(int i = 1; i< ((width/2)-1); ++i)
    {
        for(int j = 1; j<height-1; ++j)
        {
            if(cellArray[i+100][j].filled == true)
            {
              fill(R, G, B);
              rect(0+5*i, 0+5*j, 5, 5);
            }
        }
    }
}

void setRuleNumber(num)
{
    reset();
    currentRule = num;
}

//updateCells
void updateCells()
{
    if(currentRule == 30)
    {
        R=210;
        G=105;
        B=30;
        updateCells30(); 
    }
    else if(currentRule == 57)
    {
        R=221;
        G=160;
        B=221;
        updateCells57();
    }
    else if(currentRule == 90)
    {
        R=100;
        G=149;
        B=237;
        updateCells90();
    }
    else if(currentRule == 145)
    {
        R=102;
        G=205;
        B=170;
        updateCells145();
    }
    else if(currentRule == 225)
    {
        R=220;
        G=20;
        B=60;
        updateCells225();
    }
}

void reset()
{
    for(int i = 0; i< width; ++i)
    {
        for(int j = 0; j<height; ++j)
        {
          cellArray[i][j].filled = false;
        }
    }
    cellArray[startX][startY].filled = true;
    currentLine=startY;
    for(int i = 1; i< width; ++i)
    {
        for(int j = 1; j<height; ++j)
        {
            noStroke();
            rect(0+5*i, 0+5*j, 5, 5);
        }
    }
}

void mouseClicked()
{
    startX = floor(mouseX/5)+100;
    startY = floor(mouseY/5);
}

// setup
// Processing.js setup function
void setup()
{
    size(1010, 510);
    background(0, 0, 0);
    
    for(int i = 0; i< width; ++i)
    {
        for(int j = 0; j<height; ++j)
        {
          cellArray[i][j] = new Cell(false, 0);
        }
    }
    
    for(int i = 1; i< width; ++i)
    {
        for(int j = 1; j<height; ++j)
        {
            noStroke();
            rect(0+5*i, 0+5*j, 5, 5);
        }
    }
}

// draw
void draw()
{
    background(255,255,255);

  int m = millis();

  if(m>lastUpdateTime+100)
  {
    lastUpdateTime = m;
    updateCells();
  }

    drawCells();

}
