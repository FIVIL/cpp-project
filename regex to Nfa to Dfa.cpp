// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<SFML\Graphics.hpp>
#include<vector>
#include<algorithm>
#include<fstream>
#include<math.h>
using namespace std;
using namespace sf;
void push(int value, vector<int> &v) {
	for (int i = 0; i < v.size(); i++) if (value == v[i])return;
	v.push_back(value);
	sort(v.begin(), v.end());
}
void push(string &s, char c) {
	for (int i = 0; i < s.length(); i++) if (c == s[i])return;
	s += c;
}
string removes(string s, int i, int j) {
	string v = s;
	v = s.substr(0, i);
	string k = "";
	k = s.substr(j + 1, s.length() - j);
	v += k;
	//for (int k = i; k <= j; k++)v[k] = '*';
	return v;
}
class nfa {
public:
	struct state {
		int *ns;
		void create(int en) {
			ns = new int[en];
			for (int i = 0; i < en; i++)ns[i] = -1;
		}
		vector <int> epsilon;

	};
	vector <state> states;
	int elphnum;
	state curs;
	char *elph;
	int cur;
	bool checkelph(char c) {
		bool flag = false;
		for (int i = 0; i < elphnum; i++) {
			if (c == elph[i]) flag = !flag;
			if (flag) break;
		}
		return flag;
	}
	int map(char ch) {
		for (int i = 0; i < elphnum; i++) {
			if (ch == elph[i]) return i;
		}
	}
	void getelph(string s) {
		elphnum = s.length();
		elph = new char[s.length()];
		for (int j = 0; j < s.length(); j++) {
			elph[j] = s[j];
		}
		cur = create_state();
	}
	int create_state(void) {
		curs.create(elphnum);
		states.push_back(curs);
		return states.size() - 1;
	}
	void chs(char ch) {
		if (ch == '*' || ch == '(' || ch == ')' || ch == '|' || ch == '\n')return;
		int hold = create_state();
		states[cur].ns[map(ch)] = hold;
		cur = hold;
	}
	void chss(char ch) {
		if (ch == '*' || ch == '(' || ch == ')' || ch == '|')return;
		int hold = create_state();
		states[cur].ns[map(ch)] = hold;
		states[cur].epsilon.push_back(hold);
		states[hold].epsilon.push_back(cur);
		cur = hold;
	}
	void par(string s) {
		//cout <<"par: "<< s << endl;
		int stack = 0;
		bool endf = false;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(') {
				for (int j = i; j < s.length(); j++) {
					if (s[j] == '(')stack++;
					if (s[j] == ')')stack--;
					if (s[j] == ')'&&stack == 0) {
						int stackii = 0;
						bool flag = false;
						for (int k = i + 1; k <j; k++) {
							if (s.length()>k)	if (s[k] == '(')stackii++;
							if (s.length()>k)	if (s[k] == ')')stackii--;
							if (s.length() > k)	if (s[k] == '|'&&stackii == 0) {
								flag = true;
								if (s.length() > j&&s[j + 1] == '*')ors(s.substr(i + 1, k - i - 1), s.substr(k + 1, j - k - 1));
								else or (s.substr(i + 1, k - i - 1), s.substr(k + 1, j - k - 1));
								//cout << s << endl;
								s = removes(s, i, j);
								// << s << endl;
								for (int ii = 0; ii < s.length(); ii++) {
									if (s[ii] == '(') {
										par(s);
										return;
									}
								}
							}
						}
						if (!flag) {
							if (s.length() > j&&s[j + 1] == '*')pars(s.substr(i + 1, j - i - 1));
							else par(s.substr(i + 1, j - i - 1));
							//s = removes(s, i, j);
							//par(s);
							//return;
							i = j;
						}
					}
				}
			}
			else {
				if (s.length()>i&&s[i + 1] != '*') {
					chs(s[i]);
				}
				else {
					chss(s[i]);
					i++;
				}
			}
		}
	}
	void pars(string s) {
		//cout << "pars" << endl;
		int incur = cur;
		par(s);
		states[incur].epsilon.push_back(cur);
		states[cur].epsilon.push_back(incur);
	}
	void or (string s, string v) {
		//cout << s << ";;;" << v << endl;
		int hh = cur;
		int i = create_state();
		states[hh].epsilon.push_back(i);
		cur = i;
		par(s);
		int h = cur;
		i = create_state();
		states[hh].epsilon.push_back(i);
		cur = i;
		par(v);
		i = create_state();
		states[h].epsilon.push_back(i);
		states[cur].epsilon.push_back(i);
		cur = i;
	}
	void ors(string s, string v) {

		int incur = cur;
		or (s, v);
		states[incur].epsilon.push_back(cur);
		states[cur].epsilon.push_back(incur);
	}

	void print() {
		ofstream f("C:\\Users\\h\\Desktop\\a.txt", ios::trunc);
		f << "nfa:" << endl;
		for (int i = 0; i < states.size(); i++) {
			f << "state: " << i << endl;
			for (int j = 0; j < elphnum; j++)
				f << setw(2) << elph[j] << " ";
			f << endl;
			for (int j = 0; j < elphnum; j++)
				f << setw(2) << states[i].ns[j] << " ";
			f << endl << "epsilon" << endl;
			for (int j = 0; j < states[i].epsilon.size(); j++)cout << states[i].epsilon[j] << "  ";
			f << endl << "______________________" << endl;
		}
	}
	string tostring() {
		string s;
		for (int i = 0; i < states.size(); i++) {
			s += "state: ";
			s += to_string(i);
			s += "\n";
			for (int j = 0; j < elphnum; j++) {
				s.push_back(elph[j]);
				s += "  ";
			}
			s += '\n';
			for (int j = 0; j < elphnum; j++) {
				s += to_string(states[i].ns[j]);
				s += "  ";
			}
			s += "\nEpsilons:\n";
			for (int j = 0; j < states[i].epsilon.size(); j++) {
				s += to_string(states[i].epsilon[j]);
				s += "  ";
			}
			s += "\n______________________\n";
		}
		return s;
	}
};
class dfa {
public:
	struct state {
		vector <int> nfastates;
		bool mark;
		int *ns;
		void create(int en, vector<int> v) {
			ns = new int[en];
			for (int i = 0; i < en; i++)ns[i] = -1;
			for (int i = 0; i < v.size(); i++) push(v[i], nfastates);
			mark = false;
		}
		float x, y;
	};
	void statemake(float x, float y, float r) {
		float angle;
		for (int i = 1; i <= states.size(); i++)
		{
			angle = i * (360 / states.size());
			angle = (angle*3.14) / 180;
			states[i - 1].x = x + r * cos(angle);
			states[i - 1].y = y + r * sin(angle);
		}
	}
	int check(vector<int> v) {
		/*vector <int> s = v;
		bool flag = false;
		for (int i = 0; i < states.size(); i++) {
		if (s.size() == states[i].nfastates.size()) {
		flag = true;
		for (int j = 0; j < s.size(); j++) {
		if (s[j] != states[i].nfastates[j]) {
		flag = false;
		break;
		}
		}
		}
		if (flag) return i;
		}
		return -100;*/
		for (int i = 0; i < states.size(); i++) {
			if (v == states[i].nfastates)return i;
		}
		return -100;
	}
	vector <state> states;
	int elphnum;
	state *curs;
	char *elph;
	int cur;
	bool checkelph(char c) {
		bool flag = false;
		for (int i = 0; i < elphnum; i++) {
			if (c == elph[i]) flag = !flag;
			if (flag) break;
		}
		return flag;
	}
	int map(char ch) {
		for (int i = 0; i < elphnum; i++) {
			if (ch == elph[i]) return i;
		}
	}

	void getelph(string s) {
		elphnum = s.length();
		elph = new char[s.length()];
		for (int j = 0; j < s.length(); j++) {
			elph[j] = s[j];
		}
		nfa.getelph(s);
	}
	int create_state(vector<int> v) {
		curs = new state();
		curs->create(elphnum, v);
		states.push_back(*curs);
		return states.size() - 1;
	}
	nfa nfa;
	void Landacloser(vector<int> &v) {
		for (int i = 0; i < v.size(); i++) {
			//cout << v[i] << " "<<endl;
			for (int j = 0; j < nfa.states[v[i]].epsilon.size(); j++) push(nfa.states[v[i]].epsilon[j], v);
		}
	}
	void landacloser(vector<int> &v) {
		vector<int> h = v;
		Landacloser(v);
		if (h == v)return;
		else Landacloser(v);
	}

	vector<int> move(vector<int> v, char ch) {
		vector<int> s;
		for (int i = 0; i < v.size(); i++) {
			if (nfa.states[v[i]].ns[map(ch)] != -1) push(nfa.states[v[i]].ns[map(ch)], s);
		}
		return s;
	}

	void start(string v)
	{
		string s = "(";
		s += v;
		s += ')';
		string p = "";
		for (int i = 0; i < s.length(); i++) {
			if (s[i] != '('&&s[i] != '|'&&s[i] != ')'&&s[i] != '*'&&s[i] != '\n'&&s[i] != ' ') push(p, s[i]);
		}
		getelph(p);
		nfa.par(s);
	}
	void converter() {
		vector<int> p;
		p.push_back(0);
		landacloser(p);
		create_state(p);
		for (int i = 0; i < states.size(); i++) {
			//cout << "_____________________________"<<endl<<i << endl;
			//cout << "nfas" << endl;
			//for (int nfs = 0; nfs < states[i].nfastates.size(); nfs++) cout << states[i].nfastates[nfs] << " ";
			//cout << endl;
			for (int j = 0; j < elphnum; j++) {
				//cout << elph[j] << endl;
				vector<int> p = move(states[i].nfastates, elph[j]);
				landacloser(p);
				//cout << "p:" << p.size() << endl;;
				if (p.size() != 0) {
					int n = check(p);
					//	cout << n << endl;
					if (n == -100) {
						states[i].ns[j] = create_state(p);
						//cout << "true" << endl;
					}
					else {
						//	cout << "else" << endl;
						states[i].ns[j] = n;
					}
				}
				states[i].mark = true;
			}
			p.clear();
			bool flag = true;
			for (int k = 0; k < states.size(); k++) {
				flag = states[k].mark;
			}
			if (flag)break;
		}
	}
	void print() {
		ofstream ff("C:\\Users\\h\\Desktop\\a.txt", ios::app);
		ff << "\n\n\n\n\n\ndfa:" << endl;
		for (int i = 0; i < states.size(); i++) {
			ff << "state :" << i << endl;
			for (int j = 0; j < elphnum; j++)
				ff << setw(2) << elph[j] << " ";
			ff << endl;
			for (int j = 0; j < elphnum; j++)
				ff << setw(2) << states[i].ns[j] << " ";
			ff << endl << "______________________" << endl;
		}
		f();
		ff << "final states: ";
		for (int i = 0; i < finals.size(); i++) ff << finals[i] << " ";
		ff << endl;
	}
	string tostring() {
		string s;
		for (int i = 0; i < states.size(); i++) {
			s += "state :";
			s += to_string(i);
			s += "\n";
			for (int j = 0; j < elphnum; j++) {
				s.push_back(elph[j]);
				s += "  ";
			}
			s += "\n";
			for (int j = 0; j < elphnum; j++) {
				s += to_string(states[i].ns[j]);
				s += "  ";
			}
			s += "\n______________________\n";
		}
		s += "final states: ";
		for (int i = 0; i < finals.size(); i++) {
			s += to_string(finals[i]);
			s += "  ";
		}
		s += "\n";
		return s;
	}
	vector<int> finals;
	int cheq(vector<int>i, vector<int>j) {
		for (int k = 0; k < i.size(); k++) {
			for (int l = 0; l < j.size(); l++) {
				if (i[k] == j[l])return i[k];
			}
		}
		return -100;
	}
	void f() {
		vector<int> p;
		push(nfa.states.size() - 1, p);
		for (int i = 0; i < nfa.states[nfa.states.size() - 1].epsilon.size(); i++) push(nfa.states[nfa.states.size() - 1].epsilon[i], p);
		//for (int i = 0; i < p.size(); i++)cout << p[i] << " ";
		for (int i = 0; i < states.size(); i++) {
			if (cheq(states[i].nfastates, p) != -100) push(i, finals);
		}
	}

};
sf::RenderWindow window(sf::VideoMode(2500, 1750), "regex to nfa to dfa!");
class geraphic {
public:
	bool check(int k) {
		for (int i = 0; i < dfa.finals.size(); i++) if (k == dfa.finals[i])return true;
		return false;
	}
	Color co[6];
	float dx = 1250, dy = 875, dr = 150;
	dfa dfa;
	string input;
	string outputn, outputd;
	//0 refer to geting input
	//1 refer to show result as strings
	//2 refer to graphic dfa
	int con = 0;
	bool start = false;
	Font font;
	Text text;
	RectangleShape rectangel;
	CircleShape circle;
	int n = 45;
	float  x2 = 0, y = 0, y2 = 0, drr = 0;
	char ch;
	geraphic(int v) {
		circle.setFillColor(Color::Blue);
		circle.setOutlineThickness(2);
		circle.setOutlineColor(Color::Black);
		circle.setRadius(50);
		co[0] = Color::Yellow;
		co[1] = Color::Red;
		co[2] = Color::Black;
		co[3] = Color::Cyan;
		co[4] = Color::Magenta;
		co[5] = Color::Green;
		font.loadFromFile("arial.ttf");
		text.setFont(font);
	}
	void drawrect(int x, int y, Vector2f size, Color c, int th, Color c2) {
		rectangel.setPosition(x, y);
		rectangel.setFillColor(c);
		rectangel.setOutlineThickness(th);
		rectangel.setSize(size);
		rectangel.setOutlineColor(c2);
		window.draw(rectangel);
	}
	void drawstring(string s, int x, int y, int ch, Color c) {
		text.setCharacterSize(ch);
		text.setColor(c);
		text.setPosition(x, y);
		text.setString(s);
		window.draw(text);
	}
	void sfline(float x1, float y1, float x2, float y2, Color c, char ch) {
		float d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
		string s;
		Text t;
		t.setFont(font);
		t.setColor(c);
		s.push_back(ch);
		t.setString(s);
		float a = (y2 - y1) / (x2 - x1);
		a = atan(a);
		a *= (180 / 3.14);
		RectangleShape r;
		r.setPosition(x1, y1);
		r.setSize(Vector2f(5, d));
		r.setFillColor(c);
		t.setPosition((x2 + x1) / 2, (y2 + y1) / 2);
		if (x1 < x2&&y1 < y2) {
			r.setRotation(-a);
			r.setSize(Vector2f(5, d));
		}
		if (x1<x2&&y1>y2) {
			r.setRotation(a);
			r.setSize(Vector2f(d, 5));
		}

		if (x1 > x2&&y1 < y2) {
			r.setRotation(-a);
			r.setSize(Vector2f(5, d));
		}
		if (x1>x2&&y1>y2) {
			r.setPosition(x2, y2);
			r.setRotation(-a);
			r.setSize(Vector2f(5, d));
		}
		CircleShape ci;
		ci.setRadius(5);
		ci.setFillColor(Color::White);
		ci.setPosition(x2, y2);
		window.draw(ci);
		window.draw(t);
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x1, y1),c),
			sf::Vertex(sf::Vector2f(x2, y2),c)
		};

		window.draw(line, 2, sf::Lines);
		//window.draw(r);

	}
	void sfmainloop() {

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128) {
						ch = static_cast<char>(event.text.unicode);
						if (con == 0) {
							if (ch == 13) start = true;
							else if (ch == 8 && input.length()>0)input.pop_back();
							else if (ch != 8)input.push_back(ch);
						}

					}


				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (con == 1) {
						if (event.key.code == sf::Keyboard::Up) y -= 50;
						if (event.key.code == sf::Keyboard::Down) y += 50;
					}
					if (con == 2) {
						if (event.key.code == sf::Keyboard::Up)  y2 -= 50;
						if (event.key.code == sf::Keyboard::Down)  y2 += 50;
						if (event.key.code == sf::Keyboard::Right) x2 += 50;
						if (event.key.code == sf::Keyboard::Left) x2 -= 50;
						if (event.key.code == sf::Keyboard::Space) drr += 10;
						if (event.key.code == sf::Keyboard::BackSpace) drr -= 10;
					}
				}
				if (event.type == sf::Event::MouseWheelScrolled)
				{
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
						if (con == 1) {
							y -= (event.mouseWheelScroll.delta) * 5;
						}
					}
					if (con == 2) {
						if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) y2 -= (event.mouseWheelScroll.delta) * 5;
						if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) x2 -= (event.mouseWheelScroll.delta) * 5;
					}

				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (con == 1) {
							if (event.mouseButton.x >= 2020 && event.mouseButton.x <= 2220 && event.mouseButton.y >= 1550 && event.mouseButton.y <= 1650)con = 2;
						}
					}
					if (event.mouseButton.button == sf::Mouse::Right)
					{
						std::cout << "the right button was pressed" << std::endl;
						std::cout << "mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (con == 0) {
				window.clear(sf::Color::Green);
				drawrect(20, 20, Vector2f(2000, 250), Color::Cyan, 5, Color::Black);
				drawstring("Enter regular expression: " + input, 30, 120, 50, Color::Black);
			}
			if (con == 0 && start) {
				dfa.start(input);
				dfa.converter();
				dfa.f();
				outputn = dfa.nfa.tostring();
				outputd = dfa.tostring();
				con = 1;
			}
			if (con == 1) {
				window.clear(sf::Color::Green);
				drawrect(20, 150, Vector2f(1000, 1500), Color::White, 5, Color::Black);
				drawstring(outputn, 30, 160 + y, 50, Color::Black);
				drawrect(1220, 150, Vector2f(1000, 1500), Color::White, 5, Color::Black);
				drawstring(outputd, 1230, 160 + y, 50, Color::Black);
				drawrect(0, 0, Vector2f(2500, 145), Color::Green, 0, Color::Green);
				drawrect(420, 50, Vector2f(130, 70), Color::Yellow, 3, Color::Black);
				drawstring("NFA:", 435, 55, 50, Color::Black);
				drawrect(1620, 50, Vector2f(130, 70), Color::Yellow, 3, Color::Black);
				drawstring("DFA:", 1635, 50, 50, Color::Black);
				drawrect(0, 1655, Vector2f(2500, 500), Color::Green, 0, Color::Green);
				drawrect(2020, 1550, Vector2f(200, 100), Color::Magenta, 5, Color::Black);
				drawstring("draw DFA", 2030, 1575, 30, Color::Black);
			}
			if (con == 2) {
				window.clear(sf::Color::White);
				int cc = 0;
				dfa.statemake(dx + x2, dy + y2, dr + drr);
				for (int i = 0; i < dfa.states.size(); i++) {
					circle.setFillColor(Color::Blue);
					text.setString(to_string(i));
					text.setPosition(dfa.states[i].x + 30, dfa.states[i].y + 30);
					circle.setPosition(dfa.states[i].x, dfa.states[i].y);
					if (check(i)) {
						circle.setOutlineColor(Color::Black);
						circle.setOutlineThickness(5);
					}
					else {
						circle.setOutlineThickness(0);
					}
					for (int j = 0; j <dfa.elphnum; j++) {
						if (dfa.states[i].ns[j] == i)circle.setFillColor(Color::Magenta);
					}
					window.draw(circle);
					window.draw(text);
				}
				for (int i = 0; i < dfa.states.size(); i++) {
					for (int j = 0; j < dfa.elphnum; j++) {
						if (dfa.states[i].ns[j] != -1) {
							sfline(dfa.states[i].x + 30, dfa.states[i].y + 30, dfa.states[dfa.states[i].ns[j]].x + 30, dfa.states[dfa.states[i].ns[j]].y + 30, co[cc % 6], dfa.elph[j]);
							cc++;
						}
					}
				}
			}
			window.display();
		}
	}
};
int main()
{
	geraphic g(5);
	//g.states(5, 200, 200);
	g.sfmainloop();
	return 0;
}
