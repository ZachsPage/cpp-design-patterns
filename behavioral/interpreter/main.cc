#include <iostream>
#include <string>
#include <map>
#include <list>

////////////////////////////////////////////////////////////////////////////////
//! Class for components of an expression - like 5 + 7
struct Expression {
    using Map = std::map<std::string, Expression*>;
    using Stack = std::list<Expression*>;
    
    virtual int interpret(Map variables) = 0;
	virtual ~Expression() {}
};
// Expression Implementations
////////////////////////////////////////////////////////////////////////////////
class Number : public Expression {
private:
	int number;
public: 
	Number(int number) { this->number = number; }
	int interpret(Map variables)  override { return number; }
};
////////////////////////////////////////////////////////////////////////////////
class Plus : public Expression {
    Expression* leftOperand;
    Expression* rightOperand;
public: 
    Plus(Expression* left, Expression* right) : leftOperand(left), rightOperand(right)
    {}
    int interpret(Map variables) override { 
        return leftOperand->interpret(variables) + rightOperand->interpret(variables);
    }
};
////////////////////////////////////////////////////////////////////////////////
class Minus : public Expression {
    Expression* leftOperand;
    Expression* rightOperand;
public: 
    Minus(Expression* left, Expression* right) : leftOperand(left), rightOperand(right)
    {}
    int interpret(Map variables) override { 
        return leftOperand->interpret(variables) - rightOperand->interpret(variables);
    }
};
////////////////////////////////////////////////////////////////////////////////
class Variable : public Expression {
    std::string name;
public: 
	Variable(std::string name) { this->name = name; }
    int interpret(Map variables)  { 
        if(variables.end() == variables.find(name)) return 0;
        return variables[name]->interpret(variables); 
    }
};

////////////////////////////////////////////////////////////////////////////////
// While the `interpreter pattern` does not address parsing, a parser is 
//  provided for completeness.
class Evaluator : public Expression {
    Expression* syntaxTree;
public:
    int interpret(Map context) { return syntaxTree->interpret(context); }

	Evaluator(std::string expression) {
        constexpr auto kNoPos = std::string::npos;
        Stack expressionStack;
        size_t last = 0;
        for( size_t next = 0; last != kNoPos; last = (next == kNoPos) ? next : (1+next) ) 
        {
            next = expression.find(' ', last);
            auto substr_end = (next == kNoPos) ? 
                                (expression.length() - last) : (next - last);
            std::string token( expression.substr(last, substr_end) );

            if( token == "+" ) {
                Expression* right = expressionStack.back(); expressionStack.pop_back();
                Expression* left = expressionStack.back(); expressionStack.pop_back();
                Expression* subExpression = new Plus(right, left);
                expressionStack.push_back( subExpression );
            } else if( token == "-" ) {
                // it's necessary remove first the right operand from the stack
                Expression* right = expressionStack.back(); expressionStack.pop_back();
                // ..and after the left one
                Expression* left = expressionStack.back(); expressionStack.pop_back();
                Expression* subExpression = new Minus(left, right);
                expressionStack.push_back( subExpression );
            } else {
                expressionStack.push_back( new Variable(token) );
            }
        }
        syntaxTree = expressionStack.back(); expressionStack.pop_back();
    }
};
////////////////////////////////////////////////////////////////////////////////
int main()
{
	Evaluator sentence("a b c - +");
    struct SubNums { Number a, b, c; };
	SubNums kNumsToSub [] = {
		{5, 10, 42}, {1, 3, 2}, {7, 9, -5},
	};

	for( auto& nums_to_sub : kNumsToSub ) {
		Expression::Map vars_to_nums;
		vars_to_nums["a"] = &nums_to_sub.a;
		vars_to_nums["b"] = &nums_to_sub.b;
		vars_to_nums["c"] = &nums_to_sub.c;
		int result = sentence.interpret(vars_to_nums);
		std::cout << "Interpreter result: " << result << std::endl;
	}
    return 0;
}