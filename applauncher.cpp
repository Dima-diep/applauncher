#include <ncurses.h>
#include <vector>
#include <string>
#include <filesystem>
#include <stdio.h>
#include <fstream>
#include <signal.h>
using namespace std;
namespace file = std::filesystem;

void sigign(int signal) {
	;
}

class Main {
	private:
		vector<string> getapps() {
			ifstream getapp;
			getapp.open("app.conf", ios::in);
			string appn;
			vector<string> apps;
			while (getline(getapp, appn)) {
				apps.push_back(appn);
			}
			getapp.close();
			return apps;
		}

		vector<string> getexec() {
			ifstream getapp;
			getapp.open("run.conf", ios::in);
			string appn;
			vector<string> apps;
			while (getline(getapp, appn)) {
				apps.push_back(appn);
			}	
			getapp.close();
			return apps;
		}

		unsigned int getmaxlen(vector<string> apps) {
			static unsigned int retint = 0;
			for (unsigned int i = 0; i < apps.size(); i++) {
				if (apps[i].length() > retint) {
					retint = apps[i].length();
				}
			}
			return retint;
		}

	public:
		int main() {
	    	if (file::exists("app.conf") && file::exists("run.conf")) {
    			unsigned int maxy, maxx;
	    		vector<string> apps = getapps();
    			vector<string> runs = getexec();
    			static unsigned int xl = getmaxlen(apps);
    			if (xl < 16) {
    				xl = 20;
    			} else {
    				xl += 6;
    			}
	    		initscr();
	    		keypad(stdscr, true);
	    		curs_set(0);
		    	getmaxyx(stdscr, maxy, maxx);
    			WINDOW * win = newwin(10, xl, maxy / 2 - 5, maxx / 2 - (xl / 2) );
    			keypad(win, true);
    			wrefresh(win);
		    	refresh();
    			box(win, 0, 0);
    			wrefresh(win);
    			refresh();
    			WINDOW * namewin = newwin(3, xl, maxy / 2 - 5, maxx / 2 - (xl / 2) );
    			keypad(namewin, true);
    			wrefresh(namewin);
    			refresh();
    			box(namewin, 0, 0);
    			wrefresh(namewin);
    			refresh();
    			wmove(namewin, 1, 1);
    			waddstr(namewin, "Select activity:");
    			wrefresh(namewin);
    			vector<string> applist;
    			for (unsigned int k=0; k < apps.size(); k++) {
    				if (k < 6) {
    					wmove(win, 3 + k, 3);
    					waddstr(win, apps[k].c_str());
    					applist.push_back(apps[k]);
    				} else {
    					break;
    				}
    			}
    			wmove(win, 3, 1);
    			waddch(win, '>');
    			wrefresh(win);
    			refresh();
    			while (true) {
    				int key = getch();
    				static unsigned int numapp = 1;
    				static unsigned int relapp = 1;
    				if (key == KEY_UP) {
    				    if (relapp > 1) {
    				    	relapp--;
    				    }
    					if (numapp > 1) {
    						wmove(win, 2 + numapp, 1);
    						waddch(win, ' ');
    						numapp--;
    						wmove(win, 2 + numapp, 1);
    						waddch(win, '>');
    						wrefresh(win);
    					} else {
    					    if (relapp > 1) {
	    						for (unsigned int i=0; i < 6; i++) {
    							    applist[i] = applist[i + 1];
    							    for (unsigned int j=0; j < xl; j++) {
    							    	wmove(win, 3 + i, 3 + j);
    							    	waddch(win, ' ');
    								}
    							}
    							applist.push_back(apps[relapp]);
	    						for (unsigned int s=0; s < 6; s++) {
    							    wmove(win, 3 + s, 3);
    								waddstr(win, applist[s].c_str());
    							}
    							wrefresh(win);
    						}
    					}
    				} else if (key == KEY_DOWN) {
    					if (relapp < apps.size()) {
    						relapp++;
    					}
    					if (numapp < 6) {
    						wmove(win, 2 + numapp, 1);
    					    waddch(win, ' ');
    					    numapp++;
    					    wmove(win, 2 + numapp, 1);
    					    waddch(win, '>');
    					    wrefresh(win);
    			    	} else {
    			    		if (relapp < apps.size()) {
    							for (unsigned int i=0; i < 6; i++) {
	    							applist[i] = applist[i + 1];
    								for (unsigned int j=0; j < xl; j++) {
    								    wmove(win, 3 + i, 3 + j);
    								    waddch(win, ' ');
    								}
    							}
    							applist.push_back(apps[relapp]);
	    						for (unsigned int s=0; s < 6; s++) {
    								wmove(win, 3 + s, 3);
    								waddstr(win, applist[s].c_str());
    							}
    							wrefresh(win);
    						}
    					}
    				} else if (key == 10) {
    					const string rrun = runs[relapp - 1].c_str();
    					delwin(namewin);
    					delwin(win);
    					refresh();
    					endwin();
    					system(rrun.c_str());
    					break;
    				}
    			}
	    	} else {
    			fprintf(stderr, "There is no configuration files!!!\n");
	    		return 1;
		    }
			return 0;
		}
};

int main() {
	signal(SIGWINCH, sigign);
	Main m;
	return m.main();
}
