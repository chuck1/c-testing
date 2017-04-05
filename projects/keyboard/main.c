

#include <ncurses.h>
#include <unistd.h>  /* only for sleep() */

char map[4][4][4] = {
	{
		{'a','b','c','d'},
		{'e','f','g','h'},
		{'i','j','k','l'},
		{'m','n','o','p'}
	},
	{
		{'q','r','s','t'},
		{'u','v','w','x'},
		{'y','z','k','l'},
		{'m','n','o','p'}
	},
	{
		{'A','B','C','D'},
		{'E','F','G','H'},
		{'I','J','K','L'},
		{'M','N','O','P'}
	},
	{
		{'Q','R','S','T'},
		{'U','V','W','X'},
		{'Y','Z','K','L'},
		{'M','N','O','P'}
	}
};

int kbhit(void)
{
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}

int main(void)
{
	initscr();

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	scrollok(stdscr, TRUE);
	while (1) {
		if (kbhit()) {
			printw("Key pressed! It was: %d\n",
					getch());
			refresh();
		} else {
			//printw("No key pressed yet...\n");
			refresh();
			//sleep(1);
		}
	}
}


