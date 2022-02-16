
#include<cmath>
#include <iostream>
#include<stack>

using namespace std;

/*TASk
The user enters the expression that contains  ( , ) , + , - , * , / , ^ , % and numbers from R+
Expression is then converted to Reverse Polish Notation and calculated 
*/


bool is_operator(char c) {
	static char list_of_operators[] = { '+', '-', '*', '/', '^', '%' };
	bool is_op = true;
	for (char op : list_of_operators) {
		if (c == op) {
			is_op = true;
			break;
		}
		else {
			is_op = false;
		}
	}
	return is_op;
}




bool is_num(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	else {
		return false;
	}
}

/*Gets the priority of operator in calculating*/
int get_value_of_operator(char c) {
	if (c == '+' || c == '-') {
		return 1;
	}
	else if (c == '*' || c == '/' || c == '%') {
		return 2;
	}
	else if (c == '^') {
		return 3;
	}
}


/*Compares operator priorities*/
bool equal_or_higher_value(char c1, char c2) {
	return(get_value_of_operator(c1) >= get_value_of_operator(c2) ? true : false);
}

string Convert_to_RPN(string input) {
	stack<char> Stack;
	string output = "";
	Stack.push('(');
	input += ')';

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			continue;
		}
		else if (input[i] == '(') {
			Stack.push(input[i]);
		}
		else if (is_num(input[i]) || input[i] == '.') {
			if (is_num(input[i + 1]) || input[i+1]=='.') {
				output += input[i];
			}
			else {
				output += input[i];
				output += " ";
			}
		}
		else if (is_operator(input[i])) {
			if (i != 0) {
				if (is_operator(input[i - 1]) || input[i - 1] == '(') {
					output += "0 ";
				}
			}
			else if (i == 0) {
				if (input[i] == '-' || input[i] == '+') {
					output += "0 ";
				}
			}
			while (Stack.top() != '(' && equal_or_higher_value(Stack.top(), input[i])) {
				output += Stack.top();
				Stack.pop();
			}
			Stack.push(input[i]);
		}
		else if (input[i] == ')') {
			while (!Stack.empty() && Stack.top() != '(') {
				output += Stack.top();
				Stack.pop();
			}
			Stack.pop();
		}
		
	}
	return output;
}


double Count(double a, double b, char sign) {

	if (sign == '+') {
		return a + b;
	}
	else if(sign == '-'){
		return a - b;
	}
	else if (sign == '*') {
		return a * b;
	}
	else if (sign == '/') {
		if (b == 0) {
			cout << "ERROR: unable to divide by 0    ";
			return 0;
		}
		else {
			return a / b;
		}
	}

	else if (sign == '%'){
		int a_int = a;
		int b_int = b;

		if (b_int == 0) {
			cout << "ERROR: unable to divide by 0     ";
			return 0;
		}
		else {
			cout << b_int << '\t' << a_int;
			return a_int % b_int;
		}
	}
	else if (sign == '^') {
		return pow(a, b);
	}

}


double Count_RPN(string RPN_Input) {
	stack<double> num_stack;
	double a, b;
	bool is_dec = false;
	for (int i = 0; i < RPN_Input.length(); i++) {
		if (RPN_Input[i] == ' ') {
			is_dec = false;
			continue;
		}
		else if (is_num(RPN_Input[i])) {
			a = RPN_Input[i] - '0';
			if (i == 0) {
				if (is_num(RPN_Input[i + 1])) {
					a *= 10;
				}
			}
			else {
				if (!is_dec) {
					if (is_num(RPN_Input[i - 1])) {
						a += num_stack.top();
						num_stack.pop();
					}
					if (is_num(RPN_Input[i + 1])) {
						a *= 10;
					}
				}
				else {
					int j = i;
					while (RPN_Input[j] != '.') {
						a = a / 10;
						j--;
					}
					a += num_stack.top();
					num_stack.pop();
				}
			}
			num_stack.push(a);
		}
		else if (RPN_Input[i] == '.') {
			is_dec = true;
		}
		else if (is_operator(RPN_Input[i])) {
			is_dec = false;
			a = num_stack.top();
			num_stack.pop();
			b = num_stack.top();
			num_stack.pop();

			num_stack.push(Count(b, a, RPN_Input[i]));
		}
		//cout << num_stack.top() << endl;
	}
	
	return num_stack.top();
}

int main()
{

	string input;
	cout << "Enter expression, please: ";
	cin >> input;
	string output = Convert_to_RPN(input);
	cout << "RPN be like:  " << output<< endl;
	cout << "And if we try to solve this expression:  " << Count_RPN(output);
}



