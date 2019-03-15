// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>
using namespace std;
class token {
public:
	string value, token_type_name,err;
	int token_type, line;
	token *t;
	token(int lk) {
		t = NULL;
	}
	void add(string s, int tt, int l,string v) {
		value = s;
		token_type = tt;
		line = l;
		if (tt == 0) token_type_name = "err";
		if (tt == 1) token_type_name = "id";
		if (tt == 2) token_type_name = "kw";
		if (tt == 3) token_type_name = "op";
		if (tt == 4) token_type_name = "num";
		if (tt == 5) token_type_name = "lit";
		if (tt == 6) token_type_name = "punc";
		if (tt == 7) token_type_name = "mac";
		if (tt == 8) token_type_name = "comm";
		err = v;
	}
	friend ostream& operator<<(ostream& os,const  token& t)
	{
	
			os <<setw(10) << t.value << setw(10) << t.token_type_name << setw(10) << t.line << setw(10) << t.err ;
		
		
		return os;
	}
};
int IndexOf(string s, char c) {
	int i;
	bool flag = false;
	for (i = 0; i < (int)s.length(); i++) {
		if (s[i] == c) {
			flag = !flag;
			break;
		}
	}
	if (flag)return i;
	else return -1;
}
int LastIndexOf(string s, char c) {
	int i;
	bool flag = false;
	for (i = s.length()-1; i >=0; i--) {
		if (s[i] == c) {
			flag = !flag;
			break;
		}
	}
	if (flag)return i;
	else return -1;
}
string remove(string s, int i, int j) {
	return s.substr(j, s.length() - j);
}
struct sarray{
	string* s;
	
	void initial(int i) {
		s = new string[i];
	}
	int i = 0;
	void Add(string in) {
		s[i] = in;
		i++;
	}
	void Add(char c) {
		string p="0";
		p[0] = c;
		s[i++] = p;
	}
	bool is_contain(string key) {
		bool flag = false;
		for (int j = 0; j<i; j++) {
			if (s[j] == key) {
				flag = !flag;
				break;
			}
		}
		return flag;
	}
	
	bool is_contain(char key) {
		bool flag = false;
		for (int j = 0; j<i; j++) {
			if ((s[j].length() == 1) && (s[j][0] == key)) {
				flag = !flag;
				break;
			}
		}
		return flag;
	}
};
struct tokenizer {

	sarray key_words, macros, notnum, numbers, numbers2, oks, operators, punctuators;
	void coun(){
		key_words.initial(41); macros.initial(2); notnum.initial(52); numbers.initial(10); numbers2.initial(11);
		oks.initial(62); punctuators.initial(3); operators.initial(35);
		macros.Add("#define");
		macros.Add("#include");
		punctuators.Add("{");
		punctuators.Add("}");
		punctuators.Add(";");
		key_words.Add("bool");
		key_words.Add("break");
		key_words.Add("case");
		key_words.Add("char");
		key_words.Add("class");
		key_words.Add("const");
		key_words.Add("continue");
		key_words.Add("delete");
		key_words.Add("do");
		key_words.Add("double");
		key_words.Add("else");
		key_words.Add("enume");
		key_words.Add("false");
		key_words.Add("float");
		key_words.Add("for");
		key_words.Add("friend");
		key_words.Add("goto");
		key_words.Add("if");
		key_words.Add("int");
		key_words.Add("do");
		key_words.Add("interface class");
		key_words.Add("long");
		key_words.Add("namespace");
		key_words.Add("new");
		key_words.Add("operator");
		key_words.Add("private");
		key_words.Add("public");
		key_words.Add("return");
		key_words.Add("short");
		key_words.Add("sizeof");
		key_words.Add("struct");
		key_words.Add("switch");
		key_words.Add("this");
		key_words.Add("tread");
		key_words.Add("true");
		key_words.Add("typedef");
		key_words.Add("union");
		key_words.Add("unsigned");
		key_words.Add("using");
		key_words.Add("void");
		key_words.Add("while");
		operators.Add("::");
		operators.Add(":");
		operators.Add("|");
		operators.Add("++");
		operators.Add("--");
		operators.Add("(");
		operators.Add(")");
		operators.Add("[");
		operators.Add("]");
		operators.Add(".");
		operators.Add("->");
		operators.Add("!");
		operators.Add("+");
		operators.Add("-");
		operators.Add("&");
		operators.Add("*");
		operators.Add("/");
		operators.Add("%");
		operators.Add(">>");
		operators.Add("<<");
		operators.Add("<");
		operators.Add(">");
		operators.Add("<=");
		operators.Add(">=");
		operators.Add("==");
		operators.Add("!=");
		operators.Add("&&");
		operators.Add("||");
		operators.Add("=");
		operators.Add("*=");
		operators.Add("/=");
		operators.Add("%=");
		operators.Add("+=");
		operators.Add("-=");
		operators.Add(",");
		for (char i = '0'; i <= '9'; i++) numbers.Add((char)i);
		for (char i = '0'; i <= '9'; i++) numbers2.Add((char)i);
		numbers2.Add('.');
		for (char i = '0'; i <= '9'; i++) oks.Add((char)i);
		for (char i = 'A'; i <= 'Z'; i++) oks.Add((char)i);
		for (char i = 'a'; i <= 'z'; i++) oks.Add((char)i);
		for (char i = 'A'; i <= 'Z'; i++) notnum.Add((char)i);
		for (char i = 'a'; i <= 'z'; i++) notnum.Add((char)i);
	}
	

	token* grouper(string in, int l,token &p)
	{
		token *t=new token(2);
		int tt = 1;
		string e = "";
		string s = in;
		if (key_words.is_contain(s)) tt = 2;
		else if (operators.is_contain(s)) tt = 3;
		else if (s == ".") tt = 3;
		else if (punctuators.is_contain(s)) tt = 6;
		else if (s[0] == ';') tt = 6;
		else if (s[0] == '\\') { tt = 0; e = "there is no any meaning for a singel '\\' or more.\n"; }
		else if (macros.is_contain(s)) tt = 7;
		else if (s[0] == '#') { tt = 0; e = "wrong macro.\n"; }
		else if (s[0] == '"')
		{
			if (LastIndexOf(s,'"') != (s.length() - 1)) { tt = 0; e = "new line in constant.\n"; }
			else if (s.length() < 2) { tt = 0; e = "new line in constant.\n";  }
			else tt = 5;
		}
		else if (s[0] == '\'')
		{
			if (s.length() > 4) { tt = 0; e = "too many characters in character literal.\n"; }
			else if (s.length() < 2) { tt = 0; e = "new line in constant.\n"; }
			else if (s.length() == 2 && s != "''") { tt = 0; e = "new line in constant.\n"; }
			else if (s.length() == 3 && LastIndexOf(s,'\'') != 2) { tt = 0; e = "new line in constant.\n";}
			else tt = 5;
		}
		else if (s[0] == '/' && s[1] == '*') tt = 8;
		else if (s[0] == '/' && s[1] == '/') tt = 8;
		else if (s[0] >= '0' && s[0] <= '9')
		{
			if (s.length() > 1)
			{
				bool flag = false;
				for (int i = 'A'; i <= 'z'; i++) if (IndexOf(s,(char)i) != -1) { tt = 0; e = "Identifiers cant start with numbers.\n"; flag = true; }
				if (!flag)
				{
					if (IndexOf(s,'.') == -1) tt = 4;
					else if (IndexOf(s,'.') != LastIndexOf(s,'.')) { tt = 0; e = "wrong definitions for number. (numbers cant have more than one '.' )\n"; }
					else tt = 4;
				}

			}
			else tt = 4;
		}
		p.t = t;
		t->add(s, tt, l, e);
		return t;
	}


	void lexem(string inp,token *ft)
	{
		string s = inp;
		string v = "", sv = "", svv = "";
		int i = 0;
		token *t = NULL;
		token *h;
		int l2;
		int line = 1;
		while (s.length() > 0)
		{
			l2 = 0;
			if (i + 1 <=(int) s.length()) sv = s.substr(i, 1);
			if (i + 2 <= (int)s.length()) svv = s.substr(i, 2);
			////////////////////////////////////////////////////space
			if (s[i] == ' ')
			{
				v = s.substr(0, i);
				s = remove(s,0, i + 1);
				i = -1;
				if (v != "")
				{
					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					
				}
				v = "";
			}
			////////////////////////////////////////////////enter
			else if (s[i] == '\n')
			{
				v = s.substr(0, i);
				s = remove(s,0, i + 1);
				i = -1;
				if (v != "")
				{
					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					
				}
				v = "";
				line++;
			}
			//////////////////////////////////////////com//
			else if (s.length() > i + 1 && s[i] == '/' && s[i + 1] == '/')
			{

				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				bool flag = false;
				for (int j = i; j < s.length(); j++)
				{
					if (s[j] == '\n')
					{
						v = s.substr(i, j - i);
						s = remove(s,0, j + 1);
						if (v != "")
						{
							if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
							
						}
						v = "";
						i = -1;
						line++;
						flag = !flag;
						break;
					}

				}
				if (!flag)
				{
					v = s.substr(i, s.length() - i);
					s = remove(s,0, s.length());
					if (v != "")
					{
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
					}
					v = "";
					i = -1;
				}
			}
			////////////////////////////////////////////com ba *
			else if (s.length() > i + 1 && s[i] == '/' && s[i + 1] == '*')
			{
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				bool flag = false;
				for (int j = i; j < s.length(); j++)
				{
					if (j > 0 && s[j] == '/' && s[j - 1] == '*')
					{
						v = s.substr(i, j - i + 1);
						s = remove(s,0, j + 1);
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
						v = "";
						i = -1;
						flag = !flag;
						break;
					}
					if (s[j] == '\r') l2++;
				}
				if (!flag)
				{
					v = s.substr(i, s.length() - i);
					s = remove(s,0, s.length());
					if (v != "")
					{
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
					}
					v = "";
					i = -1;
				}
			}
			//////////////////////////////////////////lit"
			else if (s[i] == '"')
			{
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				bool flag = false;
				for (int j = i + 1; j < s.length(); j++)
				{
					if ( s[j] == '"' )
					{
						v = s.substr(i, j - i + 1);
						s = remove(s,0, j + 1);
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
						v = "";
						i = -1;
						flag = !flag;
						break;
					}
					else if (s[j] == '\n')
					{
						v = s.substr(i, j - i);
						s = remove(s,0, j + 1);
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
						v = "";
						i = -1;
						flag = !flag;
						line++;
						break;
					}
				}
				if (!flag)
				{
					v = s.substr(i, s.length() - i);
					s = remove(s,0, s.length());
					if (v != "")
					{
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
					}
					v = "";
					i = -1;
				}
			}
			/////////////////////////////////////////lit'
			else if (s[i] == '\'')
			{
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				bool flag = false;
				for (int j = i + 1; j < s.length(); j++)
				{
					if (s[j] == '\'')
					{
						v = s.substr(i, j - i + 1);
						s = remove(s,0, j + 1);
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
						v = "";
						i = -1;
						flag = !flag;
						break;
					}
					else if (s[j] == '\n')
					{
						v = s.substr(i, j - i);
						s = remove(s,0, j + 1);
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
						v = "";
						i = -1;
						flag = !flag;
						line++;
						break;
					}
				}
				if (!flag)
				{
					v = s.substr(i, s.length() - i);
					s = remove(s,0, s.length());
					if (v != "")
					{
						if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
						
					}
					v = "";
					i = -1;
				}
			}
			/////////////////////////////////////////num
			else if (numbers.is_contain(s[i]) )
			{
				if (i != 0)
				{
					bool flag = false;

					for (int j = i; j < s.length(); j++)
					{
						if (!oks.is_contain(s[j]) )
						{
							v = s.substr(0, j);
							s = remove(s,0, j);
							if (v != "")
							{
								if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
								
							}
							i = -1;
							flag = !flag;
							break;
						}
					}
					if (!flag)
					{
						v = s.substr(0, s.length());
						s = remove(s,0, s.length());
						if (v != "")
						{
							if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
							
						}
						i = -1;

					}
					v = "";
				}
				else
				{
					bool flag = false, flagI = false, flagII = false;
					for (int j = i; j < s.length(); j++)
					{
						if (!numbers2.is_contain(s[j]) )
						{
							if (notnum.is_contain(s[j])) {
								flagI = !flagI;
								i = 0;
								break;
							}
							else
							{
								{
									v = s.substr(0, j);
									s = remove(s,0, j);
									if (v != "")
									{
										if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
										
									}
									i = -1;
									flagII = !flagII;
									v = "";
									break;
								}
							}
						}
					}
					if (!flagII&&!flagI)
					{
						v = s.substr(0, s.length());
						s = remove(s,0, s.length());
						if (v != "")
						{
							if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
							
						}
						v = "";
						i = -1;

					}
					if (flagI)
					{
						for (int j = 0; j < s.length(); j++)
						{
							if (!oks.is_contain(s[j]) )
							{
								v = s.substr(0, j);
								s = remove(s,0, j);
								if (v != "")
								{
									if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
									
								}
								i = -1;
								flag = !flag;
								v = "";
								break;
							}
						}
						if (!flag)
						{
							v = s.substr(0, s.length());
							s = remove(s,0, s.length());
							if (v != "")
							{
								if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
								
							}
							v = "";
							i = -1;

						}
					}
				}
			}
			//////////////////////////////////////////op
			else if (operators.is_contain(sv) )
			{
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				if (operators.is_contain(svv) )
				{
					s = remove(s,0, i + 2);
					i = -1;

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(svv,line,*h);
					

					v = "";
				}
				else
				{
					s = remove(s,0, i + 1);
					i = -1;

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(sv,line,*h);
					

					v = "";
				}
			}

			///////////////////////////////////////punch
			else if (punctuators.is_contain(sv))
			{
				
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				s = remove(s,0, i + 1);
				i = -1;

				if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(sv,line,*h);
				

				v = "";
			}
			else if (s[i] == ';')
			{
				if (i != 0)
				{
					v = s.substr(0, i);

					if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
					

					v = "";
				}
				s = remove(s,0, i + 1);
				i = -1;

				if (t == NULL) h = ft; else h = t; t = new token(1); t = grouper(";",line,*h);
				

				v = "";
			}
			////////////////////////////////////etc
			else if (i == s.length() - 1)
			{
				v = s.substr(0, i + 1);
				s = remove(s,0, i + 1);

				if(t==NULL) h=ft;else h=t;t=new token(1);t=grouper(v,line,*h);
				

				v = "";
				break;
			}

			sv = "";
			svv = "";
			line += l2;
			i++;

		}
	}  
};
class _file {
public:
	void save(token *p,string add) {
		ofstream f(add + ".txt", ios::trunc);
		if (f.is_open())
		{
			token *t = p;
			while (t != NULL) {
				if(t->token_type!=-1)f  <<setw(10) << t->value << setw(10) << t->token_type_name << setw(10) << t->line << setw(3) << t->err << "\n";
				t = t->t;
			}
			f.close();
		}
		else cout << "Unable to open file";
	}
	string load(string add) {
		string line,s="";
		ifstream f(add + ".txt");
		if (f.is_open())
		{
			while (getline(f, line))
			{
				s += (line + "\n");
			}
			f.close();
			return s;
		}

		else cout << "Unable to open file";
		return "";
	}
};
void print(token *t) {
	while (t!=NULL) {
		if(t->token_type==0)cout << *t<<endl;
		t = t->t;
	}
}
int main() {
	_file f;
	token* t = new token(3);
	t->add("first", -1, 1, "");
	tokenizer mff;
	mff.coun();
	char c;
	string add;
	while (true)
	{
		cout << "enter e for exite.\nenter s for start.\n";
		cin >> c;
		if (c == 'e')break;
		else if (c == 's') {
			cout << "enter input file name:";
			cin >> add;
			string s;
			s = f.load(add);
			mff.lexem(s, t);
			print(t);
			if (s != "") {
				cout << "do you want to save?!(y|n)";
				while (true)
				{
					cin >> c;
					if (c == 'n')break;
					else if (c == 'y') {
						cout << "enter file name:";
						cin >> add;
						f.save(t, add);
						break;
					}
					else {
						system("cls");
						cout << "wrong input!\n";
					}
				}
			}
		}
		else {
			system("cls");
			cout << "wrong input!\n";
		}
	}

	
}




