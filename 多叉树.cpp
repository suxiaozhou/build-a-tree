#include <bits/stdc++.h>
//gb2312
using namespace std;
string cmd, newdata, path, sure, renam, conten;
int now = 1, libl = 2, stopflag = 0, cdflag = 0, importopen = 0;
const int maxn = 8000;

struct lib_trees {
	int brother = -1, father = -1, son = -1;
	string data, conten_lib;
} lib[maxn];

string bigli(string s) {
	string ans = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] <= 'Z' && s[i] >= 'A') {
			ans += s[i] - 'A' + 'a';
		} else {
			ans += s[i];
		}
	}
	return ans;
}

int bll(int pos) {
	int ans = pos;
	while (lib[ans].brother != -1) {
		ans = lib[ans].brother;
	}
	return ans;
}
const string helpdocm = "None :)";

int main() {
	if (0 == 1) {//调试模式
		freopen("整活.in", "r", stdin);
	}
	cout << "by suxiaozhou in 2023 04,lets build trees!!" << endl;
	cout << "do not press \" \",thanks you!" << endl;
	lib[1].data = "gen";
	while (!stopflag) {
		cout << "in>>";
		cin >> cmd;
		cmd = bigli(cmd);
		if (cmd == "exit") {
			stopflag = true;
		} else if (cmd == "new") {
			cin >> newdata;
			if (lib[now].son != -1) {
				lib[bll(lib[now].son)].brother = libl;
			} else {
				lib[now].son = libl;
			}
			lib[libl].father = now;
			lib[libl].data = newdata;
			libl++;
		} else if (cmd == "dir") {
			cout << "his name is:" << lib[now].data << endl;
			if (!importopen) {
				cout << "his content is:" << endl << "\"\"\""  << lib[now].conten_lib << endl << "\"\"\"" << endl;
			}
			if (lib[now].father != -1) {
				cout << "His father is:" << lib[lib[now].father].data << endl;
			}
			cout << "son list:" << endl;
			int next = lib[now].son;
			while (next != -1) {
				cout << lib[next].data << endl;
				next = lib[next].brother;
			}
			cout << endl;
		} else if (cmd == "del") {
			//删完爸爸删哥哥
			cin >> path;
			cout << "Are you sure to delete this?(Y/N)" << endl;
			cin >> sure;
			if (sure == "Y") {
				//
				int next = lib[now].son, delb;
				while (next != -1) {
					if (lib[next].data == path) {
						delb = next;
						cdflag = 1;
					}
					next = lib[next].brother;
				}
				if (cdflag == 0) {
					cout << "No such path named " << path << endl;
				} else {
					if (lib[lib[delb].father].son == delb) { //如果他是长子的话
						lib[lib[delb].father].son = lib[delb].brother; //他的兄弟继承他的地位,同时让爸爸把他忘得一干二净
					} else { //说明只有一个兄弟记得他
						for (int i = 1; i <= libl; i++) {
							//找到记得他的人了！
							if (lib[i].brother == delb) {
								lib[i].brother = lib[delb].brother; //直接记忆到下个兄弟
								break;
							}
						}
					}
					cout << "deleteing..." << endl;
					cout << "Success!!" << endl;
				}
				cdflag = 0;
				//从此，再无人记得他的存在。。。
			} else {
				cout << "Canceled" << endl;
			}
		} else if (cmd == "cd") {
			cin >> path;
			if (path == "..") {
				if (lib[now].father != -1) {
					now = lib[now].father;
				} else {
					cout << "Error:this is gen,i can not find his father!" << endl;
				}
			} else {
				int next = lib[now].son;
				while (next != -1) {
					if (lib[next].data == path) {
						now = next;
						cdflag = 1;
					}
					next = lib[next].brother;
				}
				if (cdflag == 0) {
					cout << "No such path named " << path << endl;
				}
				cdflag = 0;
			}
		} else if (cmd == "help") {
			cout << helpdocm << endl;
		} else if (cmd == "rename") {
			cin >> renam;
			lib[now].data = renam;
			cout << "Rename success!!" << endl;
		} else if (cmd == "newcon") {
			cout << "press a \";\" on a line to stop." << endl;
			if (lib[now].conten_lib != "") {
				lib[now].conten_lib += "\n";
			}
			while (1) {
				cin >> conten;
				if (conten == ";") {
					break;
				}
				lib[now].conten_lib = lib[now].conten_lib  + conten + "\n";
			}
			cout << "Success,now this trees content is:" << endl << "\"\"\"" << endl << lib[now].conten_lib << endl << "\"\"\""
			     <<
			     endl;
		} else if (cmd == "outcon") {
			if (lib[now].conten_lib == "") {
				cout << "none" << endl;
			} else {
				cout << lib[now].conten_lib << endl;
			}
		} else if (cmd == "delcon") {
			cout << "this trees content is:" << endl << "\"\"\"" << endl << lib[now].conten_lib << endl << "\"\"\"" << endl;
			lib[now].conten_lib = "";
			cout << "Success!!" << endl;
		} else {
			cout << "Error:No command named " << cmd << " ! Please try again!" << endl;
		}
	}
	cout << "Good Bye!" << endl;
	return 0;
}