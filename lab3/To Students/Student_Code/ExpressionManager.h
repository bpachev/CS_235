#include "ExpressionManagerInterface.h"
#include <string>
#include <map>
using namespace std;

class ExpressionManager: public ExpressionManagerInterface
{
  public:
    ExpressionManager()
    {
      
      ops_prec['+'] = 2;
      ops_prec['-'] = 2;
      ops_prec['/'] = 3;
      ops_prec['*'] = 3;
      ops_prec['^'] = 4;
      ops_prec['%'] = 3;

      left_assoc['+'] = true;
      left_assoc['-'] = true;
      left_assoc['/'] = true;
      left_assoc['*'] = true;
      left_assoc['^'] = false;
      left_assoc['%'] = true;

      balance_map[']'] = '[';
      balance_map['}'] = '{';
      balance_map[')'] = '(';

    }
    bool isBalanced(string expression); 
    string postfixToInfix(string postfixExpression); 
    string infixToPostfix(string infixExpression);
    string postfixEvaluate(string postfixExpression);
    const char* getIntToken(const char *p,int& num);
    map<char, int> ops_prec;
    map<char, bool> left_assoc; //true if left associative, false if right
  private:
    map<char, char> balance_map;
};