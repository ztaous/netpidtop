#include "ui.h"
#include "process.h"
#include <ncurses.h>
#include <string.h>

void ui_init(void)
{
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_CYAN, COLOR_BLACK);
	}
}

void ui_display_connections(connection_t *connections, int count)
{
	clear();

	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(0, 0, "NetPidTop - Network monitor");
	attroff(COLOR_PAIR(4) | A_BOLD);

	mvprintw(2, 0, "%-20s %-8s %-21s %-21s %-12s", "Process", "PID",
		 "Local", "Remote", "State");

	int y = 3;
	int shown = 0;

	for (int i = 0; i < count && y < LINES - 2; i++) {
		if (connections[i].owner_pid <= 0)
			continue;

		char proc_name[256];
		if (process_get_name(connections[i].owner_pid, proc_name,
				     sizeof(proc_name)) < 0) {
			strcpy(proc_name, "unknown");
		}

		char local[32];
		addr_to_string(connections[i].local_addr,
			       connections[i].local_port, local, sizeof(local));

		char remote[32];
		addr_to_string(connections[i].remote_addr,
			       connections[i].remote_port, remote,
			       sizeof(remote));

		if (connections[i].state == 0x01) // ESTABLISHED
			attron(COLOR_PAIR(1));
		else if (connections[i].state == 0x0A) // LISTEN
			attron(COLOR_PAIR(2));
		else if (connections[i].state == 0x08) // CLOSE_WAIT
			attron(COLOR_PAIR(3));

		mvprintw(y, 0, "%-20s %-8d %-21s %-21s %-12s", proc_name,
			 connections[i].owner_pid, local, remote,
			 state_to_string(connections[i].state));

		attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
		y++;
		shown++;
	}

	mvprintw(LINES - 1, 0, "Showing %d connections | Press 'q' to quit",
		 shown);
	refresh();
}

int ui_handle_input(void)
{
	int ch = getch();
	if (ch == 'q' || ch == 'Q') {
		return 1;
	}
	return 0;
}

void ui_cleanup(void)
{
	endwin();
}