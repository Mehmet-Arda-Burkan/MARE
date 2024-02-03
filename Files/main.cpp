#include<bits/stdc++.h>

#define endl "\n"

#define CEND "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

using namespace std;

enum CodeType {
	Empty,
	Console,
	In,
	Out,
	String,
	Int,
	Variable,
	Plus,
	Minus,
	Multiply,
	Divide,
	Equal,
	Small,
	Large,
	NonEqual,
	If,
	While,
	End
};

void Error(string error) {
	cout << RED << error << CEND << endl;
	exit(1);
}

int main(int argc, char *argv[]) {

	if(argc == 1) {
		Error("Error 404: File Path Is Not Here");
	}
	string path = argv[1];


	ifstream fileRead;
	fileRead.open(path);

	vector<string> codes;
	string temp;


	vector<string> varNames;
	vector<string> varValues;

	while (getline(fileRead, temp)) {
	  codes.push_back(temp);
	}

	bool iff = true;
	int loop = 0;

	for(int j = 0; j < codes.size(); j++) {
		
		string code = codes[j];
		vector<pair<CodeType,char>> token;
		int i = 0;


		while(i < code.length()) {

				if(code[i] == '|' && code[i+1] == '|') token.push_back(make_pair(Console,' '));
				else if(code[i] == '<' && code[i+1] == '<') token.push_back(make_pair(In,' '));
				else if(code[i] == '>' && code[i+1] == '>') token.push_back(make_pair(Out,' '));
				else if(code[i] == '&' && code[i+1] == '&') token.push_back(make_pair(End, ' '));
				else if(code[i] == '+' && code[i+1] == '+') token.push_back(make_pair(Plus, ' '));
				else if(code[i] == '-' && code[i+1] == '-') token.push_back(make_pair(Minus, ' '));
				else if(code[i] == '*' && code[i+1] == '*') token.push_back(make_pair(Multiply, ' '));
				else if(code[i] == '/' && code[i+1] == '/') token.push_back(make_pair(Divide, ' '));
				else if(code[i] == '=' && code[i+1] == '=') token.push_back(make_pair(Equal, ' '));
				else if(code[i] == '<' && code[i+1] == '=') token.push_back(make_pair(Small, ' '));
				else if(code[i] == '>' && code[i+1] == '=') token.push_back(make_pair(Large, ' '));
				else if(code[i] == '!' && code[i+1] == '=') token.push_back(make_pair(NonEqual, ' '));
				else if(code[i] == '[' && code[i+1] == ']') token.push_back(make_pair(If, ' '));
				else if(code[i] == '{' && code[i+1] == '}') token.push_back(make_pair(While, ' '));
				else if(code[i] == '\\' && code[i+1] == '\\') token.push_back(make_pair(String,' '));
				else if(code[i] == '\\' && code[i+1] == '*') token.push_back(make_pair(String,'\n'));
				else if(code[i] == '/' && code[i+1] == '\\') token.push_back(make_pair(String,'\\'));
				else if(code[i] == '/' && code[i+1] == '*') token.push_back(make_pair(String,'*'));
				else if(code[i] == '\\') token.push_back(make_pair(String,code[i+1]));
				else if(code[i] == '-') token.push_back(make_pair(Int,code[i+1]));
				else if(code[i] == '&') token.push_back(make_pair(Variable,code[i+1]));

				i+=3;

		}

		vector<pair<CodeType,string>> parser;

		i = 0;


		while(i < token.size()) {

				if(token[i].first == String){
					string s;
					while(token[i].first == String) {
						s += token[i].second;
						i++;
					}
					parser.push_back(make_pair(String,s));
					i--;
				}
				else if(token[i].first == Int){
					string s;
					while(token[i].first == Int) {
						s += token[i].second;
						i++;
					}
					parser.push_back(make_pair(Int,s));
					i--;
				}
				else if(token[i].first == Variable){
					string s;
					while(token[i].first == Variable) {
						s += token[i].second;
						i++;
					}
					parser.push_back(make_pair(Variable,s));
					i--;
				}
				else { parser.push_back(make_pair(token[i].first," "));}


				i++;

		}

		pair<CodeType,CodeType> function;
		string variable;

		/*for(int i = 0; i < parser.size(); i++) {

			cout << parser[i].first << parser[i].second << " - ";

		}
		cout << endl;*/

		for(int i = 0; i < parser.size(); i++) {

			if(iff) {


				if(parser[i].first == End) {
					function = make_pair(Empty,Empty);
					continue;
				}

				if(function.first == Empty) {
					if(parser[i].first == String || parser[i].first == Int) Error("There Must Be A Target!");
					function.first = parser[i].first;
					if(function.first == Variable) variable = parser[i].second;
				}
				else if(function.second == Empty) {
					if(parser[i].first == String || parser[i].first == Int) Error("There Must Be A Function!");
					function.second = parser[i].first;
				}
				else {
					

					if(function.first == Console) {


						if(function.second == In) {

							if(parser[i].first == String || parser[i].first == Int) {

								cout << parser[i].second;

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
								    cout << varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}

						if(function.second == Out) {

							if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
								    cin >> varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Variable!");
							}

						}

					}

					if(function.first == While) {


						if(function.second == In) {

							
							if(parser[i].first == Variable) {


								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
								    if(!(varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()] == to_string(false))) {j = loop;continue;}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Variable!as");
							}

						}

						if(function.second == Out) {

							loop = j;

						}

					}

					if(function.first == If) {


						if(function.second == In) {

							if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
								    if(varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()] == to_string(false)) iff = false;
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Variable!");
							}

						}


					}

					if(function.first == Variable) {


						if(function.second == In) {

							if(parser[i].first == String || parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varNames[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = variable;
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = parser[i].second;
								}
								else {
									varNames.push_back(variable);
									varValues.push_back(parser[i].second);
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varNames[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = variable;
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = parser[i].second;
									}
									else {
										varNames.push_back(variable);
										varValues.push_back(parser[i].second);
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Plus) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) + stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) + stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Minus) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) - stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) - stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Multiply) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) * stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) * stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Divide) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) / stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) / stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Equal) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) == stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) == stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Small) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) < stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) < stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == Large) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) > stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) > stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}
						else if(function.second == NonEqual) {

							if(parser[i].first == Int) {

								if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
								{
								    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) != stoi(parser[i].second));
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else if(parser[i].first == Variable) {

								if (find(varNames.begin(), varNames.end(), parser[i].second) != varNames.end()) 
								{
									parser[i].second = varValues[find(varNames.begin(), varNames.end(), parser[i].second) - varNames.begin()];
									if (find(varNames.begin(), varNames.end(), variable) != varNames.end()) 
									{
									    varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()] = to_string(stoi(varValues[find(varNames.begin(), varNames.end(), variable) - varNames.begin()]) != stoi(parser[i].second));
									}
									else {
										Error("Variable Is Unavailable");
									}
								}
								else {
									Error("Variable Is Unavailable");
								}

							}
							else {
								Error("There Must Be A Value!");
							}

						}



					}





				}

			}
			else {


				if(parser[i].first == End) {
					function = make_pair(Empty,Empty);
					continue;
				}

				if(function.first == Empty) {
					if(parser[i].first == If) function.first = parser[i].first;
				}
				else if(function.second == Empty) {
					if(parser[i].first == Out) function.second = parser[i].first;
				}
				else {
					

					if(function.first == If) {


						if(function.second == Out) {

							iff = true;

						}

					}



				}




			}

		}

	}

}