#include "PathfinderInterface.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

class Pathfinder: public PathfinderInterface
{
public:
  Pathfinder() 
  {
    srand(time(NULL));
    int i = 0;
    int j = 0;
    int k = 0;
    for (i=0;i<5;i++)
    {
      for (j=0;j<5;j++)
      {
	for (k=0;k<5;k++)
	{
	  curr_maze[i][j][k] = 1;
	}
      }
    }
  }
  string getMaze();
  void createRandomMaze();
  bool importMaze(string file_name);
  vector<string> solveMaze();
  bool recur_solve(vector<int> &path, vector<int> &visited, int curr_pos);
  
private:
  int curr_maze[5][5][5];  
};
  