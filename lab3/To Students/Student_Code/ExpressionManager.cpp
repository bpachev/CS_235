#include "ExpressionManager.h"
#include <stack>
#include <queue>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

bool ExpressionManager::isBalanced(string expression)
{
  const char* ptr = expression.c_str();
  stack <char> opening;	
  map<char, char>::iterator it;
  char temp;
  
  while (*ptr != 0)
  {
    if (balance_map.find(*ptr) != balance_map.end())
    {
      if(opening.size() == 0) return false;
      temp = opening.top();
      opening.pop();
      if(balance_map[*ptr]!=temp) return false;
    }
       
    for(it = balance_map.begin(); it != balance_map.end(); ++it)
    {
      if (it->second==*ptr)
      {
        opening.push(*ptr);
      }
    }
    
    ptr++;
  }
  if(opening.size()==0) return true;
  else return false;
}

#define PUSH_STRING(var) temp_str = ""; temp_str += var; output.push(temp_str);
#define IS_OPERATOR(var) (ops_prec.find(var) != ops_prec.end())
#define EXP_ERROR { return "invalid";}

string ExpressionManager::infixToPostfix(string infixExpression)
{
  if(!isBalanced(infixExpression)){
//    cout << "unbalanced" << endl;
    EXP_ERROR
  }
  const char* ptr = infixExpression.c_str();
  stack <char> ops;
  queue <string> output;
  string postfix_exp = "";
  string curr_int = "";
  map<char, char>::iterator it;
  char temp_exp;
  string temp_str;
  bool prev_was_num = false;
  //cout << infixExpression << endl;
  while(*ptr != 0)
  {
    //cout << *ptr << endl;
    if(*ptr == ' ')
    {
      if(curr_int != "")
      {
        output.push(curr_int);
        curr_int = "";
      }
    }
    else if(isdigit(*ptr)) {
      curr_int += *ptr;
      prev_was_num = true;
    }
    else if(balance_map.find(*ptr) != balance_map.end())
    {
      temp_exp = ops.top();
      while(temp_exp != balance_map[*ptr])
      {
	if(ops.size() == 0) EXP_ERROR
	PUSH_STRING(temp_exp);
	ops.pop();
	temp_exp = ops.top();
      }
      ops.pop();
    }
    else if(((*ptr == '(')||(*ptr == '['))||(*ptr == '{')) ops.push(*ptr);
    else if(ops_prec.find(*ptr) != ops_prec.end())
    {
      if(!prev_was_num) EXP_ERROR
      prev_was_num = false;
      if(!ops.size())
      {
	ops.push(*ptr++);
	continue;
      }
     // cout  << "size " << ops.size() << " top " << ops.top() << endl;
      temp_exp = ops.top();
      while (IS_OPERATOR(temp_exp) && (ops_prec[*ptr] < ops_prec[temp_exp]) || ((ops_prec[*ptr] == ops_prec[temp_exp]) && (left_assoc[*ptr])))
      {
	//cout << temp_exp << endl;
        PUSH_STRING(temp_exp);
	ops.pop();
	if(ops.size()) temp_exp = ops.top();
	else break;
      }
      ops.push(*ptr);
    }
    else {
      //cout << "bad char" << *ptr << endl; 
      EXP_ERROR
    }
    ptr++;
  }
  if(curr_int != "") output.push(curr_int);
  while(ops.size() != 0)
  {
    PUSH_STRING(ops.top());
    ops.pop();
  }
  
  bool isFirst = true;
  while(output.size() != 0)
  {
    if(!isFirst) postfix_exp += " ";  //space delimit output
    postfix_exp += output.front();
    output.pop();
    if(isFirst) isFirst = false;
  }
 // cout << "Infix: " << infixExpression << endl;
  //cout << "Postfix: " << postfix_exp << endl;
  return postfix_exp;
}

#define REAL_POP(var,stack_name) var = stack_name.top(); stack_name.pop(); 

string ExpressionManager::postfixToInfix(string postfixExpression)
{
 // cout << "Postfix: " << postfixExpression << endl;  
  const char* ptr = postfixExpression.c_str();
  string curr_int = "";
  stack <string> operands;
  string temp_str;
  string oper1, oper2;
  string infix_exp = "";
  while (*ptr != 0)
  {
    if(isdigit(*ptr))
    {
      curr_int += *ptr;
    }
    else if (*ptr==' ')
    {
      if (curr_int != "") 
      {
	operands.push(curr_int);
	curr_int = "";
      }
    }
    else if (IS_OPERATOR(*ptr))
    {
      if (operands.size() < 2) EXP_ERROR
      REAL_POP(oper1, operands)
      REAL_POP(oper2, operands)
      temp_str = "( ";
      temp_str += oper2;
      temp_str += " ";
      temp_str += *ptr; 
      temp_str += " ";
      temp_str += oper1 + " )";
      operands.push(temp_str);
    }
    else {
 //     cout << "bad char " << *ptr << "ugh" << endl;
      EXP_ERROR
    }
    ptr++;
  }
  if (curr_int != "") operands.push(curr_int);
  if (operands.size() != 1) EXP_ERROR
  REAL_POP(infix_exp,operands)
  //cout << "Infix:" << infix_exp << endl;
  return infix_exp;
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
  const char* ptr = postfixExpression.c_str();
  stack <int> operands;
  int temp_int = 0;
  int oper1, oper2, val;
  
  while(*ptr != 0)
  {
    if(isdigit(*ptr))
    {
      ptr = getIntToken(ptr, temp_int);
      operands.push(temp_int);
    }
    else if (*ptr == ' ') { ptr++; continue;}
    else if (IS_OPERATOR(*ptr))
    {
      if (operands.size() < 2) EXP_ERROR
      REAL_POP(oper1,operands)
      REAL_POP(oper2,operands)
      switch (*ptr)
      {
	case '+':
	  operands.push(oper2 + oper1);
	  break;
	case '-':
	  operands.push(oper2 - oper1);
	  break;
	case '*':
	  operands.push(oper2 * oper1);
	  break;
	case '^':
	  operands.push((int)pow(oper2 , oper1));
	  break;
	case '/':
	  if (oper1 == 0) EXP_ERROR
	  else operands.push(oper2/oper1);
	  break;
	case '%':
	  if (oper1 == 0) EXP_ERROR
	  operands.push(oper2 % oper1);
	  break;
	default:
	  EXP_ERROR
      }
      ptr++;
    }
    else EXP_ERROR
  }
  
  if (operands.size() != 1) EXP_ERROR
  else REAL_POP(val,operands)
    
  char buf[22];
  snprintf(buf, sizeof(buf), "%d", val);
 // cout << postfixExpression <<  " = " << string(buf) << endl; 
  return string(buf);
}

const char* ExpressionManager::getIntToken(const char *p,int& num)
{
  num = 0;
  
  while (*p && *p != ' ')
  {
    if (!isdigit(*p)) return 0;
    num = 10*num + (*p - '0');
    p++;
  }
  if(*p) p++;
  return p;
}
