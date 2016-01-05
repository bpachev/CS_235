#include "ExpressionManager.h"
#include <stack>
#include <map>
using namespace std

bool ExpressionManager::isBalanced(string expression)
{
  char* ptr = c_str(expression);
  stack <char> opening;
  map<char, char> balance_map = {{']','['}, {'}','{'}, {')', '('}};
  
  while (*ptr != 0)
  {
    switch (*ptr)
    {
      case '{':
	opening.push(*ptr);
	break;
      case '[':
        opening.push(*ptr);
	break;
      case '(':
	opening.push(*ptr);
	break;
      case '}':
	
	break;
      case ']':
	break;
      case ')':
	break;
      default:
	break;
    }
    ptr++;
  }
}

string postfixToInfix(string postfixExpression)
{
  
}

string infixToPostfix(string infixExpression)
{
  
}

string postfixEvaluate(string postfixExpression)
{
  
}
