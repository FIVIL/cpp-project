#include"stdafx.h"
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<iomanip>
#include<math.h>
#include<vector>
#include<queue>
#include<time.h>
#include<Windows.h>
using namespace std;
using namespace sf;
int i;
string counti;
class student {
public:
	struct date {
		int y, m, d;
		void creat() {
			y = (rand() % 20) + 1990;
			m = (rand() % 12) + 1;
			d = (rand() % 30) + 1;
		}
		void set(int yi, int mi, int di) {
			y = yi; m = mi; d = di;
		}
		string write() {
			string s;
			s.clear();
			s = to_string(y) + " " + to_string(m) + " " + to_string(d);
			return s;
		}
	};
	string name, last_name;
	int nu, pas, pid;
	int avg;
	date d;

	void creat() {
		name.clear();
		last_name.clear();
		d.creat();
		nu = (rand() % 4000) + 90000;
		//nu=rand()%75;
		avg = (rand() % 15) + 5;
		pas = (rand() % 120) + 10;
		pid = (rand() % 1000) + d.d + d.m + d.y;
		char ch;
		for (int i = 0; i<(rand() % 8) + 3; i++) { ch = (rand() % 26) + 'a'; name.push_back(ch); }
		for (int i = 0; i<(rand() % 8) + 3; i++) { ch = (rand() % 26) + 'a'; last_name.push_back(ch); }
	}
	//<>==by nU
	bool operator <(const student &b) {
		return (nu<b.nu);
	}
	bool operator >(const student &b) {
		return (nu>b.nu);
	}
	bool operator ==(const student &b) {
		return (nu == b.nu);
	}
	//<=>= !=by last name
	bool operator <=(const student &b) {
		return (last_name<b.last_name);
	}
	bool operator >=(const student &b) {
		return (last_name>b.last_name);
	}
	bool operator !=(const student &b) {
		return (last_name == b.last_name);
	}
	//<<>>>^by  name
	bool operator <<(const student &b) {
		return (name<b.name);
	}
	bool operator >>(const student &b) {
		return (name>b.name);
	}
	bool operator ^(const student &b) {
		return (name == b.name);
	}
	//^= >>= <<= by pid
	bool operator <<=(const student &b) {
		return (pid<b.pid);
	}
	bool operator >>=(const student &b) {
		return (pid>b.pid);
	}
	bool operator ^=(const student &b) {
		return (pid == b.pid);
	}
	//  /%| by avg
	bool operator /(const student &b) {
		return (avg<b.avg);
	}
	bool operator %(const student &b) {
		return (avg>b.avg);
	}
	bool operator |(const student &b) {
		return (avg == b.avg);
	}
	//*+- by passed
	bool operator *(const student &b) {
		return (pas<b.pas);
	}
	bool operator +(const student &b) {
		return (pas>b.pas);
	}
	bool operator -(const student &b) {
		return (pas == b.pas);
	}
	void set(string n, string ln, int pidi, int nui, int pasi, int avgi, int y, int m, int D) {
		d.set(y, m, D);
		name = n;
		last_name = ln;
		nu = nui;
		pid = pidi;
		avg = avgi;
		pas = pasi;
	}
	string write() {
		string s;
		s.clear();
		s = name + " " + last_name + " " + to_string(pid) + " " + to_string(nu) + " " + to_string(pas) + " " + to_string(avg) + " " + d.write() + "\n";
		return s;
	}

};
//// for draw tree
struct graphicnode {
	student d;
	bool existence;
	int x, y, l, r;
};
vector<graphicnode> gnv;//graphic node vector
class bst {
public:
	struct node {
		bool ex;
		student d;
		node *p, *l, *r;
		void creat() {
			p = l = r = NULL;
		}
	};
	int dep;
	node *root;
	void insertroot(student i) {
		dep = 0;
		root = new node;
		root->creat();
		root->d = i;
		root->p = root;
		//cout<<"root"<<root<<endl;
	}
	///////////////////////////////////////////////////////////////////////insert
	//nu
	void insertbynu(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if (i>h->d&&h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.nu<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if (i<h->d&&h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.nu<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if (i>h->d&&h->r != NULL) {
					h = h->r;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if (i<h->d&&h->l != NULL) {
					h = h->l;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i == h->d) {
					//cout<<i.nu<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//last name
	void insertbyln(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if (i >= h->d&&h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.last_name<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if (i <= h->d&&h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.last_name<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if (i >= h->d&&h->r != NULL) {
					h = h->r;
					k++;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if (i <= h->d&&h->l != NULL) {
					h = h->l;
					k++;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i != h->d) {
					//cout<<i.last_name<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//name
	void insertbyn(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if (i >> h->d&&h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.nu<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if (i << h->d&&h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.nu<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if (i >> h->d&&h->r != NULL) {
					h = h->r;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if (i << h->d&&h->l != NULL) {
					h = h->l;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i^h->d) {
					//cout<<i.nu<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//pid +|| >
	void insertbypid(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if ((i >>= h->d) && h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.nu<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if ((i <<= h->d) && h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.nu<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if ((i >>= h->d) && h->r != NULL) {
					h = h->r;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if ((i <<= h->d) && h->l != NULL) {
					h = h->l;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i ^= h->d) {
					//cout<<i.nu<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//avg %>
	void insertbyavg(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if (i%h->d&&h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.nu<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if (i / h->d&&h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.nu<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if (i%h->d&&h->r != NULL) {
					h = h->r;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if (i / h->d&&h->l != NULL) {
					h = h->l;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i | h->d) {
					//cout<<i.nu<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//pas +>
	void insertbypas(student i) {
		int k = 0;
		node *h = root;
		node *p = new node;
		p->creat();
		p->d = i;
		if (h == NULL) { root = p; root->p = root; }
		else {
			while (1) {
				if (i + h->d&&h->r == NULL) {
					h->r = p;
					p->p = h;
					// cout<<"i:"<<i.nu<<" right insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}
				else if (i*h->d&&h->l == NULL) {
					h->l = p;
					p->p = h;
					//cout<<"i:"<<i.nu<<" left insert add: "<<p<<"parrent:: "<<p->p<<endl;
					return;
				}


				else if (i + h->d&&h->r != NULL) {
					h = h->r;
					k++;
					//	cout<<"k:"<<5k<<endl;
					if (k>dep)dep = k;
					//cout<<"right is root"<<endl;
				}
				else if (i*h->d&&h->l != NULL) {
					h = h->l;
					k++;
					//	cout<<"k:"<<k<<endl;
					if (k>dep)dep = k;
					//cout<<"left is root"<<endl;
				}
				else if (i - h->d) {
					//cout<<i.nu<<"eqaul"<<endl;
					delete(p);
					return;
				}

			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////searches
	// by last name
	node *search(string s) {
		node *h = root;
		while (1) {
			if (s == h->d.last_name) return h;
			else if (s<h->d.last_name) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	// by nu
	node *search(int n) {
		node *h = root;
		while (1) {
			if (n == h->d.nu) return h;
			else if (n<h->d.nu) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	//by avg
	node *searchavg(int n) {
		node *h = root;
		while (1) {
			if (n == h->d.avg) return h;
			else if (n<h->d.avg) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	//by name
	node *searchn(string s) {
		node *h = root;
		while (1) {
			if (s == h->d.name) return h;
			else if (s<h->d.name) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	// by PId
	node *searchpid(int n) {
		node *h = root;
		while (1) {
			if (n == h->d.pid) return h;
			else if (n<h->d.pid) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	//by pas
	node *searchpas(int n) {
		node *h = root;
		while (1) {
			if (n == h->d.pas) return h;
			else if (n<h->d.pas) h = h->l;
			else h = h->r;
			if (h == NULL)return NULL;
		}
	}
	//////////////////other search
	//by nu
	vector<node*>vh;
	void sernu(int n) {
		node *h = root;
		vh.clear();
		senu(n, h);
	}
	void senu(int n, node*t) {
		if (t == NULL)return;
		if (t->d.nu == n) vh.push_back(t);
		senu(n, t->l);
		senu(n, t->r);
	}
	//by name

	void sern(string n) {
		node *h = root;
		vh.clear();
		senn(n, h);
	}
	void senn(string n, node*t) {
		if (t == NULL)return;
		if (t->d.name == n) vh.push_back(t);
		senn(n, t->l);
		senn(n, t->r);
	}
	//by ln
	void serln(string n) {
		node *h = root;
		vh.clear();
		senln(n, h);
	}
	void senln(string n, node*t) {
		if (t == NULL)return;
		if (t->d.last_name == n) vh.push_back(t);
		senln(n, t->l);
		senln(n, t->r);
	}
	//by pid
	void serpid(int n) {
		node *h = root;
		vh.clear();
		senpid(n, h);
	}
	void senpid(int n, node*t) {
		if (t == NULL)return;
		if (t->d.pid == n) vh.push_back(t);
		senpid(n, t->l);
		senpid(n, t->r);
	}
	//by avg
	void seravg(int n) {
		node *h = root;
		vh.clear();
		senavg(n, h);
	}
	void senavg(int n, node*t) {
		if (t == NULL)return;
		if (t->d.avg == n) vh.push_back(t);
		senavg(n, t->l);
		senavg(n, t->r);
	}
	//by pas
	void serpas(int n) {
		node *h = root;
		vh.clear();
		sepas(n, h);
	}
	void sepas(int n, node*t) {
		if (t == NULL)return;
		if (t->d.pas == n) vh.push_back(t);
		sepas(n, t->l);
		sepas(n, t->r);
	}
	/////////////////////////////////////////////////////////////////////////////deps
	int deps() {
		return dep + 1;
	}
	//////////////////////////////////////////////////////////////////in order 
	string ih, ihn, ihln, ihpid, ihavg, ihnu, ihpas;
	void inorder() {
		node *t = root;
		ih.clear();
		ihn.clear();
		ihln.clear();
		ihnu.clear();
		ihavg.clear();
		ihpas.clear();
		ihpid.clear();
		if (t != NULL) {
			inorderer(t);
		}
		else return;
	}
	void inorderer(node *t) {
		if (t == NULL)return;
		inorderer(t->l);
		ih += (t->d.write() + "\n");
		ihn += (t->d.name + "\n");
		ihln += (t->d.last_name + "\n");
		ihnu += (to_string(t->d.nu) + "\n");
		ihavg += (to_string(t->d.avg) + "\n");
		ihpas += (to_string(t->d.pas) + "\n");
		ihpid += (to_string(t->d.pid) + "\n");
		inorderer(t->r);
	}
	////////////////////////////////////////////////////////// del 
	//// by last name
	void del(string s) {
		node *h = search(s);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			string k = p->d.last_name;
			del(k);
			h->d = hold;
			//	if(p->r==NULL) delete(p);
			//	else {
			//	p->r->p=p->p;
			//if(p->p->r==p) p->p->r=p->r;
			//	else p->p->l=p->r;
			//delete(p);
			//return;}
			return;
		}
	}
	//// by NU
	void del(int n) {
		node *h = search(n);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			int  k = p->d.nu;
			del(k);
			h->d = hold;

			return;
		}
	}

	//by name
	void del_name(string s) {
		node *h = searchn(s);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			string k = p->d.name;
			del_name(k);
			h->d = hold;
			//	if(p->r==NULL) delete(p);
			//	else {
			//	p->r->p=p->p;
			//if(p->p->r==p) p->p->r=p->r;
			//	else p->p->l=p->r;
			//delete(p);
			//return;}
			return;
		}
	}
	//by avg
	void del_avg(int n) {
		node *h = searchavg(n);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			int  k = p->d.avg;
			del_avg(k);
			h->d = hold;

			return;
		}
	}
	//by pas
	void del_pas(int n) {
		node *h = searchpas(n);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			int  k = p->d.pas;
			del_pas(k);
			h->d = hold;

			return;
		}
	}
	//by pid
	void del_pid(int n) {
		node *h = searchpid(n);
		if (h == NULL) return;
		else if (h->r == NULL&&h->l == NULL) {
			if (h == root) { delete(h); return; }
			else if (h->p->r == h) h->p->r = NULL;
			else h->p->l = NULL;
			delete(h);
			return;
		}
		else if (h->r != NULL&&h->l == NULL) {
			if (h == root) {
				root = h->r;
				h->r->p = root;
				delete(h);
				return;
			}
			h->r->p = h->p;
			if (h->p->r == h) h->p->r = h->r;
			else h->p->l = h->r;
			delete(h);
			return;
		}
		else if (h->r == NULL&&h->l != NULL) {
			if (h == root) {
				root = h->l;
				h->l->p = root;
				delete(h);
				return;
			}
			h->l->p = h->p;
			if (h->p->r == h) h->p->r = h->l;
			else h->p->l = h->l;
			delete(h);
			return;
		}
		else {
			node *p = next(h);
			student hold = p->d;
			cout << "done";
			int  k = p->d.pid;
			del_pid(k);
			h->d = hold;

			return;
		}
	}
	//////////////////////////////////////////////destroy
	void destroy() {
		node* t = root;
		destroier(t);
		root = NULL;
	}
	void destroier(node *t) {
		node *h = t;
		if (h == NULL)return;
		destroier(h->l);
		destroier(h->r);
		cout << i << "deleteed" << h << endl;
		i++;
		delete(h);
	}
	//////////////////////////////////////next 
	node* next(node *cur) {
		node *k = cur;
		if (k->r != NULL) {
			k = k->r;
			while (k->l != NULL) k = k->l;
			return k;
		}
		else return NULL;
	}
	////////////////////////////////////levelorder
	string levelorder() {
		if (root != NULL) {
			string lv;
			lv.clear();
			queue <node*> q;
			node *h = root;
			lv += (h->d.write() + "\n");
			q.push(h);
			while (!q.empty()) {
				h = q.front();
				q.pop();
				if (h->l != NULL) {
					//cout<<"l i:"<<i<<endl;
					q.push(h->l);
					lv += (h->l->d.write() + "\n");
				}
				if (h->r != NULL) {
					//cout<<"r i:"<<i<<endl;
					q.push(h->r);
					lv += (h->r->d.write() + "\n");
				}
			}

			return lv;
		}
		else return "no tree";
	}
	//////////////////////////////////////////////////////////////////////////////get size
	int getsize(node* t) {
		if (t == NULL)return 0;
		else return getsize(t->l) + getsize(t->r) + 1;
	}

	//////////////////////////////////////////////////////////////////////////////make fill
	node *fillroot;
	void cc/*creat copy*/() {
		fillroot = copytree(root);
	}
	node *copytree(node *t) {
		if (t == NULL)return NULL;
		node *p = new node;
		p->d = t->d;
		p->l = copytree(t->l);
		p->r = copytree(t->r);
		return p;
	}
	void mf() {
		int a;
		queue<node*>q;
		node *h;
		cc();
		a = getsize(fillroot);
		q.push(fillroot);
		while (!q.empty()) {
			h = q.front();
			q.pop();
			if (h->l != NULL) a--, h->l->ex = true, q.push(h->l);
			else if (h->l == NULL) h->l = new node, h->l->ex = false, h->l->l = h->l->r = NULL, q.push(h->l);
			if (h->r != NULL) a--, h->r->ex = true, q.push(h->r);
			else if (h->r == NULL) h->r = new node, h->r->ex = false, h->r->l = h->r->r = NULL, q.push(h->r);
			if (a == 1) break;
		}
	}
	////////////////////////////////////////////////////////creat graphic tree
	bool p_2(int a) {
		if (a == 0)return true;
		float b = a;
		while (1) {
			b /= 2;
			if (b == 1) return true;
			if (fmod(b, 2) != 0) return false;
		}
	}

	void cgt() {
		mf();
		graphicnode gn;
		gnv.clear();
		fillroot->ex = true;
		node *h = fillroot;
		queue<node*>q;
		q.push(h);
		while (!q.empty()) {
			h = q.front();
			gn.d = h->d;
			if (h->ex == true)gn.existence = true;
			else gn.existence = false;
			gn.l = (gnv.size() * 2) + 1;
			gn.r = (gnv.size() + 1) * 2;
			//cout<<gn.d.write()<<"l: "<<gn.l<<"r: "<<gn.r<<"e: "<<gn.existence<<endl;
			gnv.push_back(gn);
			if (h->l != NULL)q.push(h->l);
			if (h->r != NULL)q.push(h->r);
			q.pop();
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "/***********done************/" << endl;
	}
	void setxy() {
		float x = 735, y = 50;
		int hold = -1;
		for (int i = 0, j = 0; i<gnv.size(); i++, j++) {
			gnv[i].x = x;
			gnv[i].y = y;
			x += 90;
			if (p_2(j) && j>hold) {
				cout << "+++++++++++++" << i << "xxxx" << x << "yyyy" << y << endl;
				y += 90;
				x = (735 - (90 * ((j) / 2)));
				//x=735;
				hold = j;
				j = 0;
			}
		}
	}


};
class file {
public:
	void load(bst &a, bst &b, bst &c, bst &d, bst &e, bst &f) {
		a.destroy();
		b.destroy();
		c.destroy();
		d.destroy();
		e.destroy();
		f.destroy();
		string line, n, ln;
		student h;
		int nu, pid, avg, pas, y, m, da;
		ifstream myfile("save.txt");
		if (myfile.is_open()) {
			while (getline(myfile, line))
			{
				stringstream(line) >> n >> ln >> pid >> nu >> pas >> avg >> y >> m >> da;
				h.set(n, ln, pid, nu, pas, avg, y, m, da);
				a.insertbyn(h);
				b.insertbyln(h);
				c.insertbynu(h);
				d.insertbypid(h);
				e.insertbyavg(h);
				f.insertbypas(h);
			}
			myfile.close();
		}
		else cout << "not open";
	}
	void save(string s) {
		ofstream myfile;
		myfile.open("save.txt", ios::trunc);
		myfile << s;
		myfile.close();
	}


};
class graphics {
public:
	Font font;
	Text text, text1, btext;
	RectangleShape rectangel;
	CircleShape circle;
	Color bg, bu, bub, nod, tb, t;
	///back ground
	//button
	//button border
	//tree node
	//text box
	//text
	graphics(int a) {
		font.loadFromFile("arial.ttf");
		bg = Color::Green;
		bu = Color::Cyan;
		bub = Color::Black;
		nod = Color::Yellow;
		tb = Color::White;
		t = Color::Black;
		text.setFont(font);
		text1.setFont(font);
		btext.setFont(font);
		text.setCharacterSize(10);
		text1.setCharacterSize(20);
		btext.setCharacterSize(20);
		text.setColor(t);
		text1.setColor(t);
		btext.setColor(t);
	}

};




void generator(bst &a, bst &b, bst &c, bst &d, bst &e, bst &f) {
	student h;
	counti.clear();
	for (int i = 0; i<100; i++) {
		h.creat();
		cout << h.write() << endl;
		a.insertbyn(h);
		b.insertbyln(h);
		c.insertbynu(h);
		d.insertbypid(h);
		e.insertbyavg(h);
		f.insertbypas(h);
		counti += (to_string(i) + " : \n");
	}
}
int atois(string s) {
	char *a;
	a = new char[s.length()];
	for (int i = 0; i<s.length(); i++) a[i] = s[i];
	return atoi(a);
}
int main()

{
	srand(time(NULL));
	//0to not in box
	//1to search and delte box
	//2to nu box
	//3to name box
	//4to last name box
	//5to pid box
	//6to avg box
	//7to pas box
	int boxcon = 0;

	//0refer to there is no tree
	//1 refer to there is tree
	//2refer to show tree
	int con = 0;
	//0refer to no tree
	//1refer to nu
	//2refer to pid
	//3refr to name
	//4refer to last name
	//5refer to avg
	//6refer to pas
	//7refer to search result
	int treecon = 0;
	//0refer to let the function work
	//1prevent function from working
	int maneger = 0;
	string nu, pas, avg, pid, treenod, del, search, searched;
	string name, last_name;
	bst nutree, pidtree, nametree, last_nametree, avgtree, pastree;
	file file;
	//file class use for save in file or load from file
	graphics g(5);
	int x = 15, y = 50;
	//for draw 
	int mx = 375, my = 50;
	int mmx = 0, mmy = 0;
	//for mouse;
	//generator(nametree,last_nametree,nutree,pidtree,avgtree,pastree);
	//nutree.cgt();
	//cout<<endl<<endl<<"now"<<endl<<endl;
	//for(int i=0;i<gnv.size();i++) {
	//	if(gnv[i].existence) cout<<i<<" "<<gnv[i].d.write()<<" "<<gnv[i].l<<" "<<gnv[i].r<<endl;
	//else cout<<i<<" dont exist"<<endl;}
	sf::RenderWindow window(sf::VideoMode(1500, 800), "BST (^_^)");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{////////////////////////////////////////////////////////////////////////////////text
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
					std::cout << "ASCII character typed: " << (event.text.unicode) << std::endl;
				if (boxcon == 1) { if (event.text.unicode == 8)search.pop_back(); else { search.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 2) { if (event.text.unicode == 8)nu.pop_back(); else { nu.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 3) { if (event.text.unicode == 8)name.pop_back(); else { name.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 4) { if (event.text.unicode == 8)last_name.pop_back(); else { last_name.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 5) { if (event.text.unicode == 8)pid.pop_back(); else { pid.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 6) { if (event.text.unicode == 8)avg.pop_back(); else { avg.push_back(static_cast<char>(event.text.unicode)); } }
				if (boxcon == 7) { if (event.text.unicode == 8)pas.pop_back(); else { pas.push_back(static_cast<char>(event.text.unicode)); } }
			}
			///////////////////////////////////////////////////////////////////key
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) y -= 50, mmy -= 50;
				if (event.key.code == sf::Keyboard::Down) y += 50, mmy += 50;
				if (event.key.code == sf::Keyboard::Right) mmx += 50;
				if (event.key.code == sf::Keyboard::Left) mmx -= 50;
			}/////////////////////////////////////////////////////////////////////////////mouse left
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					my = event.mouseButton.y;
					mx = event.mouseButton.x;
					if (con == 0) {
						if (mx>600 && mx<900 && my>100 && my<250) {
							con = 1;
							generator(nametree, last_nametree, nutree, pidtree, avgtree, pastree);
							nametree.inorder();
							last_nametree.inorder();
							nutree.inorder();
							pidtree.inorder();
							avgtree.inorder();
							pastree.inorder();
							treecon = 1;
						}
						if (mx>600 && mx<900 && my>300 && my<450) {
							con = 1;
							treecon = 1;
							file.load(nametree, last_nametree, nutree, pidtree, avgtree, pastree);
							nametree.inorder();
							last_nametree.inorder();
							nutree.inorder();
							pidtree.inorder();
							avgtree.inorder();
							pastree.inorder();
						}
					}
					if (con == 1) {
						if (mx>10 && mx<130 && my>10 && my<40)  y = 50, treecon = 1, maneger = 0;
						if (mx>140 && mx<260 && my>10 && my<40) y = 50, treecon = 3, maneger = 0;
						if (mx>270 && mx<390 && my>10 && my<40) y = 50, treecon = 4, maneger = 0;
						if (mx>400 && mx<520 && my>10 && my<40) y = 50, treecon = 2, maneger = 0;
						if (mx>530 && mx<640 && my>10 && my<40) y = 50, treecon = 5, maneger = 0;
						if (mx>660 && mx<780 && my>10 && my<40) y = 50, treecon = 6, maneger = 0;
						if (mx>1230 && mx<1350 && my>10 && my<40) search.clear(), boxcon = 1;
						if (mx>1230 && mx<1350 && my>50 && my<80) {
							searched.clear();
							char *aa;
							aa = new char[search.length()];
							for (int i = 0; i<search.length(); i++) aa[i] = search[i];
							if (treecon == 1) {
								nutree.sernu(atoi(aa));
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.sernu(atoi(aa));
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.sernu(atoi(aa));
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.sernu(atoi(aa));
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.sernu(atoi(aa));
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.sernu(atoi(aa));
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						////////////////////////////////////////////////////////////////////////////////////////////////name search
						if (mx>1230 && mx<1350 && my>90 && my<120) {
							searched.clear();
							if (treecon == 1) {
								nutree.sern(search);
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.sern(search);
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.sern(search);
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.sern(search);
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.sern(search);
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.sern(search);
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						///////////////////////////////////////////////////////////////////////////////////////////////////last name serach
						if (mx>1230 && mx<1350 && my>130 && my<170) {
							searched.clear();
							if (treecon == 1) {
								nutree.serln(search);
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.serln(search);
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.serln(search);
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.serln(search);
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.serln(search);
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.serln(search);
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						/////////////////////////////////////////////////////////////////////////////////////////////////////pid search
						if (mx>1230 && mx<1350 && my>170 && my<200) {
							searched.clear();
							char *aa;
							aa = new char[search.length()];
							for (int i = 0; i<search.length(); i++) aa[i] = search[i];
							if (treecon == 1) {
								nutree.serpid(atoi(aa));
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.serpid(atoi(aa));
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.serpid(atoi(aa));
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.serpid(atoi(aa));
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.serpid(atoi(aa));
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.serpid(atoi(aa));
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						/////////////////////////////////////////////////////////////////////////////////////////avg search
						if (mx>1230 && mx<1350 && my>210 && my<240) {
							searched.clear();
							char *aa;
							aa = new char[search.length()];
							for (int i = 0; i<search.length(); i++) aa[i] = search[i];
							if (treecon == 1) {
								nutree.seravg(atoi(aa));
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.seravg(atoi(aa));
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.seravg(atoi(aa));
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.seravg(atoi(aa));
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.seravg(atoi(aa));
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.seravg(atoi(aa));
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						////////////////////////////////////////////////////////////////////////////////////////////pas search
						if (mx>1230 && mx<1350 && my>250 && my<280) {
							searched.clear();
							char *aa;
							aa = new char[search.length()];
							for (int i = 0; i<search.length(); i++) aa[i] = search[i];
							if (treecon == 1) {
								nutree.serpas(atoi(aa));
								for (int i = 0; i<nutree.vh.size(); i++) searched += (nutree.vh[i]->d.write() + "\n");
							}
							if (treecon == 2) {
								pidtree.serpas(atoi(aa));
								for (int i = 0; i<pidtree.vh.size(); i++) searched += (pidtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 3) {
								nametree.serpas(atoi(aa));
								for (int i = 0; i<nametree.vh.size(); i++) searched += (nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 4) {
								last_nametree.serpas(atoi(aa));
								for (int i = 0; i<last_nametree.vh.size(); i++) searched += (last_nametree.vh[i]->d.write() + "\n");
							}
							if (treecon == 5) {
								avgtree.serpas(atoi(aa));
								for (int i = 0; i<avgtree.vh.size(); i++) searched += (avgtree.vh[i]->d.write() + "\n");
							}
							if (treecon == 6) {
								pastree.serpas(atoi(aa));
								for (int i = 0; i<pastree.vh.size(); i++) searched += (pastree.vh[i]->d.write() + "\n");
							}
							treecon = 7;
						}
						/////////////////////////////////////////////////////////////////////////////////////////delete
						if (mx>1230 && mx<1350 && my>290 && my<320) {

							char *aa;
							aa = new char[search.length()];
							for (int i = 0; i<search.length(); i++) aa[i] = search[i];
							if (treecon == 1) nutree.del(atoi(aa)), nutree.inorder();
							if (treecon == 2) pidtree.del_pid(atoi(aa)), pidtree.inorder();
							if (treecon == 3) nametree.del_name(search), nametree.inorder();
							if (treecon == 4) last_nametree.del(search), last_nametree.inorder();
							if (treecon == 5) avgtree.del_avg(atoi(aa)), avgtree.inorder();
							if (treecon == 6) pastree.del_pas(atoi(aa)), pastree.inorder();
						}
						/////////////////////////////////////////////////////////////////////////destroy
						if (mx>1340 && mx<1440 && my>660 && my<690) {
							nutree.destroy();
							nametree.destroy();
							last_nametree.destroy();
							pidtree.destroy();
							avgtree.destroy();
							pastree.destroy();
							treecon = 0;
							boxcon = 0;
							y = 50;
							con = 0;
						}
						//////////////////////////////////////////////////////////////////save
						if (mx>1230 && mx<1330 && my>660 && my<690) {
							if (treecon == 1) file.save(nutree.levelorder());
							if (treecon == 2) file.save(pidtree.levelorder());
							if (treecon == 3) file.save(nametree.levelorder());
							if (treecon == 4) file.save(last_nametree.levelorder());
							if (treecon == 5) file.save(avgtree.levelorder());
							if (treecon == 6) file.save(pastree.levelorder());
						}
						///////////////////////////////////////////////////////////////show tree
						if (mx>1230 && mx<1485 && my>700 && my<730) {
							con = 3;
						}
						//////////////////////////////////////////////////////////insert
						if (mx>1235 && mx<1435 && my>360 && my<390) nu.clear(), boxcon = 2;
						if (mx>1235 && mx<1435 && my>400 && my<430) name.clear(), boxcon = 3;
						if (mx>1235 && mx<1435 && my>440 && my<470) last_name.clear(), boxcon = 4;
						if (mx>1235 && mx<1435 && my>480 && my<510) pid.clear(), boxcon = 5;
						if (mx>1235 && mx<1435 && my>520 && my<550) avg.clear(), boxcon = 6;
						if (mx>1235 && mx<1435 && my>560 && my<590) pas.clear(), boxcon = 7;
						if (mx>1370 && mx<1470 && my>610 && my<640) {
							nutree.ih.clear();
							nametree.ih.clear();
							last_nametree.ih.clear();
							pidtree.ih.clear();
							avgtree.ih.clear();
							pastree.ih.clear();
							student hold;
							hold.set(name, last_name, atois(pid), atois(nu), atois(pas), atois(avg), (rand() % 10) + 1995, rand() % 12, rand() % 30);
							nametree.insertbyn(hold);
							nutree.insertbynu(hold);
							last_nametree.insertbyln(hold);
							avgtree.insertbyavg(hold);
							pidtree.insertbypid(hold);
							pastree.insertbypas(hold);
							nametree.inorder();
							nutree.inorder();
							last_nametree.inorder();
							avgtree.inorder();
							pidtree.inorder();
							pastree.inorder();
						}

					}
					if (con == 3) {
						if (mx>10 && mx<110 && my>10 && my<60) con = 1;
					}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(g.bg);
		if (con == 0) {
			g.rectangel.setPosition(600, 100);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(10);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(300, 150));
			g.btext.setString("Generate new tree");
			g.btext.setPosition(670, 160);
			window.draw(g.rectangel);
			window.draw(g.btext);
			g.rectangel.setPosition(600, 300);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(10);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(300, 150));
			g.btext.setString("load from file");
			g.btext.setPosition(675, 365);
			window.draw(g.rectangel);
			window.draw(g.btext);
		}
		if (con == 1) {
			g.rectangel.setPosition(10, 50);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(5);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(1200, 730));
			window.draw(g.rectangel);
			if (treecon == 1) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihnu);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihn);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihln);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihpid);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihavg);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(nutree.ihpas);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 3) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihn);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihnu);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihln);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihpid);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihavg);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(nametree.ihpas);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 4) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihln);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihn);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihnu);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihpid);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihavg);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(last_nametree.ihpas);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 2) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihpid);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihn);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihln);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihnu);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihavg);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(pidtree.ihpas);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 5) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihavg);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihn);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihln);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihpid);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihnu);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(avgtree.ihpas);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 6) {
				g.text1.setString(counti);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihpas);
				g.text1.setPosition(x + 50, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihn);
				g.text1.setPosition(x + 150, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihln);
				g.text1.setPosition(x + 250, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihpid);
				g.text1.setPosition(x + 350, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihavg);
				g.text1.setPosition(x + 450, y);
				window.draw(g.text1);
				g.text1.setString(pastree.ihnu);
				g.text1.setPosition(x + 550, y);
				window.draw(g.text1);
			}
			if (treecon == 7) {
				g.text1.setString(searched);
				g.text1.setPosition(x, y);
				window.draw(g.text1);
			}
			g.rectangel.setPosition(0, 0);
			g.rectangel.setOutlineThickness(0);
			g.rectangel.setSize(Vector2f(1400, 45));
			g.rectangel.setFillColor(Color::Green);
			window.draw(g.rectangel);
			g.rectangel.setPosition(10, 10);
			if (treecon == 1)g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("student number");
			g.text.setPosition(15, 20);
			window.draw(g.text);
			g.rectangel.setPosition(140, 10);
			if (treecon == 3)g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("name");
			g.text.setPosition(150, 20);
			window.draw(g.text);
			g.rectangel.setPosition(270, 10);
			if (treecon == 4)g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("last name");
			g.text.setPosition(280, 20);
			window.draw(g.text);
			g.rectangel.setPosition(400, 10);
			if (treecon == 2) g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("personal ID");
			g.text.setPosition(405, 20);
			window.draw(g.text);
			g.rectangel.setPosition(530, 10);
			if (treecon == 5)g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("average");
			g.text.setPosition(535, 20);
			window.draw(g.text);
			g.rectangel.setPosition(660, 10);
			if (treecon == 6)g.rectangel.setFillColor(g.nod);
			else g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(120, 30));
			window.draw(g.rectangel);
			g.text.setString("pased");
			g.text.setPosition(670, 20);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 10);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString(search);
			g.text.setPosition(1235, 20);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 50);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by student number");
			g.text.setPosition(1235, 60);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 90);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by name");
			g.text.setPosition(1235, 100);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 130);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by last name");
			g.text.setPosition(1235, 140);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 170);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by personal ID");
			g.text.setPosition(1235, 180);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 210);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by average");
			g.text.setPosition(1235, 220);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 250);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.text.setString("search by pased");
			g.text.setPosition(1235, 260);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 290);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(150, 30));
			window.draw(g.rectangel);
			g.btext.setString("delete");
			g.btext.setPosition(1245, 295);
			window.draw(g.btext);
			g.rectangel.setPosition(1230, 350);
			g.rectangel.setFillColor(Color::Transparent);
			g.rectangel.setOutlineThickness(5);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(250, 300));
			window.draw(g.rectangel);
			g.rectangel.setPosition(1370, 610);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(100, 30));
			window.draw(g.rectangel);
			g.btext.setString("insert");
			g.btext.setPosition(1375, 615);
			window.draw(g.btext);
			g.rectangel.setPosition(1235, 360);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("student number: " + nu);
			g.text.setPosition(1240, 365);
			window.draw(g.text);
			g.rectangel.setPosition(1235, 400);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("name: " + name);
			g.text.setPosition(1240, 405);
			window.draw(g.text);
			g.rectangel.setPosition(1235, 440);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("last name: " + last_name);
			g.text.setPosition(1240, 445);
			window.draw(g.text);
			g.rectangel.setPosition(1235, 480);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("personal ID: " + pid);
			g.text.setPosition(1240, 485);
			window.draw(g.text);
			g.rectangel.setPosition(1235, 520);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("average: " + avg);
			g.text.setPosition(1240, 525);
			window.draw(g.text);
			g.rectangel.setPosition(1235, 560);
			g.rectangel.setFillColor(g.tb);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(200, 30));
			window.draw(g.rectangel);
			g.text.setString("pased: " + pas);
			g.text.setPosition(1240, 565);
			window.draw(g.text);
			g.rectangel.setPosition(1230, 660);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(100, 30));
			window.draw(g.rectangel);
			g.btext.setString("save");
			g.btext.setPosition(1235, 665);
			window.draw(g.btext);
			g.rectangel.setPosition(1340, 660);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(100, 30));
			window.draw(g.rectangel);
			g.btext.setString("destroy");
			g.btext.setPosition(1345, 665);
			window.draw(g.btext);
			g.rectangel.setPosition(1230, 700);
			g.rectangel.setFillColor(Color::Magenta);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(255, 30));
			window.draw(g.rectangel);
			g.btext.setString("show tree");
			g.btext.setPosition(1300, 705);
			window.draw(g.btext);
		}
		if (con == 3) {
			g.rectangel.setPosition(10, 10);
			g.rectangel.setFillColor(g.bu);
			g.rectangel.setOutlineThickness(1);
			g.rectangel.setOutlineColor(g.bub);
			g.rectangel.setSize(Vector2f(100, 50));
			window.draw(g.rectangel);
			g.btext.setString("back");
			g.btext.setPosition(45, 30);
			window.draw(g.btext);
			if (treecon == 1 && maneger == 0)nutree.cgt(), maneger++;
			if (treecon == 2 && maneger == 0)pidtree.cgt(), maneger++;
			if (treecon == 3 && maneger == 0)nametree.cgt(), maneger++;
			if (treecon == 4 && maneger == 0)last_nametree.cgt(), maneger++;
			if (treecon == 5 && maneger == 0)avgtree.cgt(), maneger++;
			if (treecon == 6 && maneger == 0)pastree.cgt(), maneger++;
			if (treecon == 7 && maneger == 0)nutree.cgt(), maneger++;
			if (maneger == 1) nutree.setxy(), maneger++;
			g.circle.setRadius(40);
			g.circle.setFillColor(g.nod);
			if (maneger == 2) {
				for (int i = 0; i<gnv.size(); i++) {//cout<<i<<"  "<<gnv[i].x+mmx<<"    "<<gnv[i].y+mmy<<endl;
					g.circle.setPosition(gnv[i].x + mmx, gnv[i].y + mmy);
					g.text.setPosition(gnv[i].x + mmx + 10, gnv[i].y + mmy + 30);
					g.text.setCharacterSize(10);
					if (treecon == 1)g.text.setString(to_string(gnv[i].d.nu));
					if (treecon == 2)g.text.setString(to_string(gnv[i].d.pid));
					if (treecon == 3)g.text.setString((gnv[i].d.name));
					if (treecon == 4)g.text.setString((gnv[i].d.last_name));
					if (treecon == 5)g.text.setString(to_string(gnv[i].d.avg));
					if (treecon == 6)g.text.setString(to_string(gnv[i].d.pas));
					if (treecon == 7)g.text.setString(to_string(gnv[i].d.nu));
					if (gnv[i].existence) { window.draw(g.circle); window.draw(g.text); }
				}
				//maneger++;
			}


		}
		window.display();
	}

	return 0;
}
