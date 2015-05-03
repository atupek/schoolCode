/* fgetc example: money counter */
#include <stdio.h>
int main ()
{
  FILE * pFile;
  FILE * oFile;
  int c;
  int n = 0;
  pFile=fopen ("message.txt","r");
  oFile=fopen ("out.txt", "w");
  if (pFile==NULL) perror ("Error opening file");
  else
  {
    do {
      c = fgetc (pFile);
      if (c == '$') n++;
      fprintf(oFile, "%02x ", c);
    } while (c != EOF);
    fclose (pFile);
    fclose (oFile);
    printf ("The file contains %d dollar sign characters ($).\n",n);
  }
  return 0;
}