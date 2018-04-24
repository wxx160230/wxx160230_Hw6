//Wulan Xu
//wxx160230@utdallas.edu
//3377.002

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include "program6.h"
#include <stdlib.h>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"0", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //create a binary record file
  BinaryFileRecord myRecord;
  
  //open the binary file
  system("strings cs3377.bin >> cs3377.txt");
  ifstream binInfile, ifl;
  binInfile.open("cs3377.bin", ios::in | ios::binary);
  ifl.open("cs3377.txt");

  //check that file opened successfully
  if(!binInfile){
    cout << "Unable to open binary file\n";
    return 0;
  }

  //Initialize the Cdk screen.
  //Make sure the putty terminal is large enough

  window = initscr();
  cdkscreen = initCDKScreen(window);

  //Start CDK Colors
  initCDKColor();

  //Create the matrix.  Need to manually cast (const char**) to (char **)
  
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //Display the Matrix
  drawCDKMatrix(myMatrix, true);

  char buf[25];
  
  //Dipslay
  setCDKMatrixCell(myMatrix, 1, 1, "Magic: 0xFEEDFACE");
  setCDKMatrixCell(myMatrix, 1, 2, "Version: 16");
  setCDKMatrixCell(myMatrix, 1, 3, "NumRecords: 4");
  
  int r = 2;
  string line;
  while(getline(ifl, line) && r < 6){
    int c = 1;
    stringstream str, str2;
    
    str << "strlen: " << line.length();
    string tstr = str.str();
    char const* loc = tstr.c_str();
    setCDKMatrixCell(myMatrix, r, c, loc);
    
    c = 2;
    str2 << line;
    tstr = str2.str();
    loc = tstr.c_str();
    setCDKMatrixCell(myMatrix, r, c, loc);
  
    r++;
  }

  //setCDKMatrixCell(myMatrix, 2, 2, reinterpret_cast<char*>(myRecord->myVal);
  drawCDKMatrix(myMatrix, true);    //required

  //so we can see results
  unsigned char x;
  cin >> x;

  system("rm cs3377.txt");
  // Cleanup screen
  endCDK();
  binInfile.close();
}
