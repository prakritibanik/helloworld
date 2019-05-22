/*Write a program to change directory like cd command. The function will take two arguments: 
1) current directory and 
2) path to new directory
Return the new directory as string
*/

/* Test cases:
1. /foo/bar, ../tab
2. /, /
3. /a, /b
4. /, ./foo/gif
5. /foo/bar , ../../../../tab
6. /foo/bar. /p/./q
7. /foo/bar, /p/../q
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

void getToken(const string& dir, vector<string>& tokens)
{
	string path = dir;
	string delim = "/";
	if (path[0]=='/')
		path.erase(0,1);
	size_t pos = 0;
	string token;
	while ((pos = path.find(delim)) != string::npos) {
		token = path.substr(0, pos);
		tokens.push_back(token);
		path.erase(0, pos+delim.length());
	}
	if (path.length() != 0) {
		tokens.push_back(path);
	}
}

string changeDir(const string& cwd, const string& arg)
{
	string newDir = "/";
	vector<string> cwd_token, arg_token;
	getToken(cwd, cwd_token);
	getToken(arg, arg_token);
	stack<string> newPath;
	for (auto item : cwd_token) {
		newPath.push(item);
	}
	bool seen = false;
	for (auto item : arg_token) {
		if (item == ".." && !newPath.empty()) {
			newPath.pop();
			seen = true;
		} else if (item == ".." && newPath.empty()) {
			break;
		} else if (item == "." ) {
			seen = true;
		} else if (item != ".." && item != "." && !seen) {
			while (!newPath.empty()) {
				newPath.pop();
			}
			newPath.push(item);
		} else if (item != ".." && item != "." && seen) {
			newPath.push(item);
		}
	}
  
  // newPath contains directory in reverse order so we need to make it proper order
	stack<string> tempStack;
	while (!newPath.empty()) {
		tempStack.push(newPath.top());
		newPath.pop();
	}
	while (!tempStack.empty()) {
		newDir += tempStack.top();
		tempStack.pop();
		if (!tempStack.empty()) {
			newDir += "/";
		}
	}
	return newDir;
}

int main()
{
	string cwd = "/foo/bar";
	string arg = "../../tab";
	string newd = changeDir(cwd, arg);
	cout << cwd << " => " << arg << " = " << newd << endl;
	return 0; 
}
