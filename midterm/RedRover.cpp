//Benjamin Pachev CS Fall 235 Midterm
#include "RedRover.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


using namespace std;

enum {NAME, STRENGTH, SPEED};
enum {TA,TB};


void RedRover::menu()
{
  char str [20];
  char buf[20];
 
  //display menu options and read input
  printf("\nOptions:\nCreate Roster .1\nView Roster .2\nShuffle Roster .3\nCreate Teams .4\nView Teams .5\nUser Play .6\nAuto Play .7\nQuit .8\n");
  printf("Menu:");
  scanf("%19s", buf);
  
  //Perform the operation selected by the user, and return to the menu, unless the user wants to quit.
  switch(buf[0]-'0')
  {
    case 8:
      exit(1);
      break;
    case 1:
      char str[20];
      printf("\nFilename:");
      scanf("%19s", str);
      if(upload_roster(string(str))) printf("Roster Uploaded.\n");
      else printf("Error Loading Roster.");
      menu();
      break;
    case 2:
      view_roster();
      menu();
      break;
    case 3:
      shuffle_roster();
      menu();
    case 4:
      create_teams();
      menu();
      break;
    case 5:
      view_teams();
      menu();
      break;
    case 6:
      if (teamA->size==0||teamB->size==0) printf("\nNot enough people to play.");
      else user_play(TA);
      menu();
      break;
    case 7:
      if (teamA->size==0||teamB->size==0) printf("\nNot enough people to play.");
      else auto_play(TA);
      menu();
      break;
    default:
      printf("\nInvalid Input\n");
      menu();
      break;
  }
}


void RedRover::create_teams()
{
  if (roster->size < 4)
  {
    printf("Not enough people in roster to divide into teams.\n");
    return;
  }
  
  int team_size = roster->size/2;
  int i = 0;

  for (i = 0; i < team_size; i++)
  {
    teamA->add(roster->head->name,roster->head->speed,roster->head->strength);
    roster->remove(roster->head->name);
    teamB->add(roster->head->name,roster->head->speed,roster->head->strength);
    roster->remove(roster->head->name);
  }
  printf("Teams Created.");
}

void RedRover::view_roster()
{
  if (roster->size == 0) printf("Roster Empty");
  else roster->print_self();
}

//#define REPROMPT_FNAME char str[20];printf("Invalid Input\nFilename: ");scanf("%20s",str);upload_roster(string(str)); 

bool RedRover::upload_roster(string filename)
{
  //open file
  const char* fname = filename.c_str();
  FILE* f = fopen(fname, "r");
  if(f == NULL) return false;
  
  char c;
  string tname;
  int tstrength = 0;
  int tspeed = 0;
  int state = NAME;
  
  //iterate through file character by character
  //To parse the file, we implement a simple state machine with three states.
  //The name of each state corresponds to the field being read (name, speed, or strength).
  //After reading the name, we switch states to read the strength, and then the speed.
  //After reading the speed, we have all the information needed to add the next person.
  //Then we add the next person and switch states to name to read the next name. 
  while((c = fgetc(f)) != EOF)
  {
    switch (state)
    {
      case NAME:
        if (c == '\n')
        {
          state = STRENGTH;
        }
        else
        {
          tname += c;
        }
        break;
      case STRENGTH:
        if (c == '\n') state  = SPEED;
        else tstrength = 10*tstrength + (c - '0');
        break;      
      case SPEED:
        if (c == '\n')
        {
          roster->add(tname,tspeed,tstrength);
          state = NAME;
          tname = "";
          tspeed = 0;
          tstrength = 0;
        }
        else tspeed = 10*tspeed + (c - '0');
        break;
      default:
        break;
    }
    
  }
  
  if(tspeed||tstrength)  roster->add(tname,tspeed,tstrength);
  
  return true;
}

//Shuffles roster in place.
void RedRover::shuffle_roster()
{
  if (roster->size == 0) 
  {
    printf("Roster Empty.\n");
    return;
  }
  
  int i;
  Person* temp;
  int s = roster->size;
  
  //As i ranges from 0 to one less from the size s of the roster, one element from
  //the first s-i elements of the roster is randomly selected and appended to the end of the roster.
  //In the first iteration of the loop, one random element of the roster will be appended to the end.
  //In the second, one random element of the first s-1 elements, those which have not been moved, will be appended to the end.
  //In general, one random element of the subset of the roster which has not been moved by the shuffle will be moved to the end.
  //Thus, the order of roster will be randomly changed without creating any new linked lists.  
  for (i = 0; i < s; i++)
  {
    temp = roster->at(rand() % (s-i));
    roster->add(temp->name,temp->speed,temp->strength);
    roster->remove(temp->name);
  }
  
  printf("Roster Shuffled.");
  return;
}


//Prompts the user to pick a name from the given linked list, and returns a pointer to the person with that name.
//If the entered name is not in the linked list, the user is reprompted untill a valid name is entered.
Person* RedRover::pick_name(DoubleLinkedList* l)
{
  //Prompt for name
  char buf[20];
  printf("\nPick:");
  scanf("%19s",buf);
  Person* p;
  
  if ((p=l->get_by_name(string(buf)))==0)
  {
    printf("Name not found.\n");
    p = pick_name(l);
  }
  
  return p;
}

void RedRover::user_play(int turn)
{
  if (teamA->size == 1)
  {
    printf("The winner is Team B!\n");
    teamA->clear();
    teamB->clear();
    return;
  }
  
  else if(teamB->size == 1)
  {
    printf("The winner is Team A!\n");
    teamB->clear();
    teamA->clear();
    return;
  }
  
  Person* A = 0;
  Person* B = 0;
  
  switch (turn)
  {
    case TA: //Team A's turn
      //Print teams and prompt the user to pick names from each team.      
      printf("Team A: ");
      teamA->print_names();
      A = pick_name(teamA); //Person from team A charging at team B.
      printf("Team B: ");
      teamB->print_names(); //Person from team B whose link to his sucessor is being threatened. 
      B = pick_name(teamB);

      //If the person selected as a 'target' for team A is the last person in line, the link being threatened
      //is the link between the last two people in team B.
      if(B == teamB->tail) B = B->prev; 

      //If the sum of person A's strength and speed exceed the sum of the strengths of person B and his successor, 
      //the stronger of person B and his successor will join team A.
      //If the link isn't broken, person A joins team B.
      if(A->strength+A->speed > B->strength + B->next->strength)
      {
        Person* C = (B->strength > B->next->strength) ? B : B->next;
        teamA->insert(A->name,C->name,C->speed,C->strength);
        teamB->remove(C->name);
      }
      else
      {
        teamB->insert(B->name,A->name,A->speed,A->strength);
        teamA->remove(A->name);
      }
      user_play(TB); //Now it's team B's turn
      break;
    case TB:
      // The logic when it's team B's turn is identical to when it is team A's turn, except the roles of team B and team A are reversed. 
      printf("Team B: ");
      teamB->print_names();
      B = pick_name(teamB);
      printf("Team A: ");
      teamA->print_names();
      A = pick_name(teamA);
      if(A == teamA->tail) A = A->prev;
      if(B->strength+B->speed > A->strength + A->next->strength)
      {
        Person* C = (A->strength > A->next->strength) ? A : A->next;
        teamB->insert(B->name,C->name,C->speed,C->strength);
        teamA->remove(C->name);
      }
      else
      {
        teamA->insert(A->name,B->name,B->speed,B->strength);
        teamB->remove(B->name);
      }
      user_play(TA); //Now it's team A's turn
      break;
  }
}


void RedRover::auto_play(int turn)
{
  if (teamA->size == 1)
  {
    printf("The winner is Team B!\n");
    teamA->clear();
    teamB->clear();
    return;
  }
  
  else if(teamB->size == 1)
  {
    printf("The winner is Team A!\n");
    teamB->clear();
    teamA->clear();
    return;
  }
  Person* A = 0;
  Person* B = 0;
  
  switch (turn)
  {
    case TA:
      A = teamA->random_pick();
      B = teamB->random_pick();

      if(B == teamB->tail) B = B->prev;

      if(A->strength+A->speed > B->strength + B->next->strength)
      {
        Person* C = (B->strength > B->next->strength) ? B : B->next;
        teamA->insert(A->name,C->name,C->speed,C->strength);
        teamB->remove(C->name);
      }
      else
      {
        teamB->insert(B->name,A->name,A->speed,A->strength);
        teamA->remove(A->name);
      }
      
      //print teams
      printf("\nTeam A: ");
      teamA->print_names();
      printf("Team B: ");
      teamB->print_names();

      auto_play(TB); // Now it's team B's turn
      break;
    case TB:
      B = teamB->random_pick();
      A = teamA->random_pick();

      if(A == teamA->tail) A = A->prev;

      if(B->strength+B->speed > A->strength + A->next->strength)
      {
        Person* C = (A->strength > A->next->strength) ? A : A->next;
        teamB->insert(B->name,C->name,C->speed,C->strength);
        teamA->remove(C->name);
      }
      else
      {
        teamA->insert(A->name,B->name,B->speed,B->strength);
        teamB->remove(B->name);
      }
      
      //print teams
      printf("\nTeam A: ");
      teamA->print_names();
      printf("Team B: ");
      teamB->print_names();      
      
      auto_play(TA); //Now it's team A's turn
      break;
  }
  
}

void RedRover::view_teams()
{
  //print a list of the members of teams A and B
  printf("Team A:\n");
  teamA->print_self(); 
  printf("Team B:\n");
  teamB->print_self();
}
  