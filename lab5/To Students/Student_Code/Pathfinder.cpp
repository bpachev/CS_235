#include "Pathfinder.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <stack>

using namespace std;

enum  {FORWARD=0,RIGHT,UP,BACK,LEFT,DOWN};
inline int get_pos(int direction, int curr_pos);


string Pathfinder::getMaze()
{
  int i = 0;
  int j = 0;
  int k = 0;
  string str_maze = "";
  int num_ones = 0;
  for (k=0;k<5;k++)
  {
    for (j=0;j<5;j++)
    {
      for (i=0;i<5;i++)
      {
        if (curr_maze[i][j][k])
        {
	  num_ones++;
          str_maze += '1';
        }
        else str_maze += '0';
        if (i+j+k!=12) str_maze += ' ';
      }
    }
    if (i+j+k!=12) str_maze += "\n";
  }
//  cout << "Num ones: " << num_ones << endl;
  return str_maze;
}

void Pathfinder::createRandomMaze()
{
  int i, j, k;
  for (i=0;i<5;i++)
  {
    for (j=0;j<5;j++)
    {
      for (k=0;k<5;k++)
      {
        if((i+j+k==0)||(i+j+k==12)) curr_maze[i][j][k] = 1;
        else curr_maze[i][j][k] = (rand() % 3 > 0) ? 1 : 0;
        //else curr_maze[i][j][k] = (rand() % 3 > 0) ? 0 : 1;
      }
    }
  }
}

bool Pathfinder::importMaze(string file_name)
{
  const char* foo = file_name.c_str();
  FILE* f = fopen(foo, "r");
  if (f == NULL) return false;
  int num_ones = 0;
  int num_zeros = 0;
  int num_d = 0;
  int temp_maze[5][5][5];
  char c;
  while ((c = fgetc(f)) != EOF)
  {
    switch (c)
    {
      case '1':
        num_d = num_ones + num_zeros;
        temp_maze[num_d % 5][(num_d / 5) % 5][(num_d / 25) % 5] = 1;
        num_ones++;
        break;
      case '0':
        num_d = num_ones + num_zeros;      
        temp_maze[num_d % 5][(num_d / 5) % 5][(num_d / 25) % 5] = 0;
        num_zeros++;
        break;  
      case ' ':
      case '\r':
      case '\n': continue;
      default:
        fclose(f);
        return false;
    }
  }
  fclose(f);
  if (num_ones + num_zeros > 125) 
  {
   // cout << "Too many digits" << endl;
    return false;
  }
  if (temp_maze[0][0][0] != 1 || temp_maze[4][4][4] != 1) 
  {
    //cout << "No ones in entrace/exit." << endl;
    return false;
  }
  for(int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        curr_maze[i][j][k] = temp_maze[i][j][k];
      }
    }
  }
  //cout << "Made it!" << endl;
  return true;
}


#define GET_NTH_ELEMENT(n) curr_maze[n % 5][(n / 5) % 5][(n / 25) % 5]

vector<string> Pathfinder::solveMaze()
{
  vector<int> path;
  vector<int> visited;
  vector<string> str_path;
  if (!recur_solve(path, visited, 0)) return str_path;
  else 
  {
    for (long index=0; index<(long)path.size(); ++index)
    {
      string temp = "(";
      temp += ('0' + (path[index] % 5));
      temp += ", ";
      temp += ( '0'  + ((path[index] / 5) % 5));
      temp += ", ";
      temp += ('0' + ((path[index] / 25) % 5));
      temp += ")";
      str_path.push_back(temp);
    }
    return str_path;
  }
    
}

bool Pathfinder::recur_solve(vector<int> &path, vector<int> &visited, int curr_pos)
{
  int n_pos = -1;
  
  if (!GET_NTH_ELEMENT(curr_pos)||( (curr_pos < 0) || (curr_pos >= 125))) {
    return false;
  }
  for (unsigned int i = 0; i < visited.size(); ++i)
  {
    if (visited[i] == curr_pos) {
      return false;
    }
  }
  
  visited.push_back(curr_pos);
  path.push_back(curr_pos);
  if (curr_pos == 124) return true;
  
  for (int dir = FORWARD; dir <= DOWN; dir++)
  {
    if ((n_pos = get_pos(dir, curr_pos)) >= 0)
    {
      if (recur_solve(path, visited, n_pos)) return true;
    }
  }
  
  path.pop_back();
  return false;
          
}

inline int get_pos(int direction, int curr_pos)
{
  switch(direction)
  {
    case FORWARD:
      if (curr_pos % 5 == 4) return -1;
      else return curr_pos + 1;
      break;
    case RIGHT:
      if ((curr_pos / 5) % 5 == 4) return -1;
      else return curr_pos + 5;
      break;
    case UP:
      if ((curr_pos / 25) % 5 == 4) return -1;
      else return curr_pos + 25;
      break;
    case BACK:
      if (curr_pos % 5 == 0) return -1;
      else return curr_pos - 1;
      break;
    case LEFT:
      if ((curr_pos / 5) % 5 == 0) return -1;
      else return curr_pos - 5;
      break;
    case DOWN:
      if ((curr_pos / 25) % 5 == 0) return -1;
      else return curr_pos - 25;
      break;
    default:
      return -1;
  }
}