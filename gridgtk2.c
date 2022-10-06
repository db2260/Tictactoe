#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int player=1;
//pressed[3][3]={{0,0,0},{0,0,0},{0,0,0}};;
GtkWidget* grid, *window, *status;
GtkWidget *b1, *b2, *b3, *b4, *b5, *b6, *b7, *b8, *b9;
int game_is_over = 0;

int pressed[] = {0,0,0,0,0,0,0,0,0};
int arr[] = {0,0,0,0,0,0,0,0,0};
//int arr[3][3]={{0,0,0},{0,0,0},{0,0,0}};;

// put X's and O's on the board depending on which player's turn it is
void pick(GtkWidget *click_button, gpointer user_data) {
	GtkButton *change_button = (GtkButton*) user_data;

	player = (player % 2) ? 1 : 2;
	int p = player;

	if(p == 1) {
		gtk_button_set_label(change_button, "X");
		player++;
	}
	else {
		gtk_button_set_label(change_button, "O");
                player--;
	}
}

// check for draw condition
int draww() {
	for(int i=0; i<9; i++) {
		//g_print("%d", pressed[i][j]);
                if(pressed[i] == 0) {
			return 0;
		}
        }
	return 1;
}

// check for win condition
int winner() {
	if(arr[0] == arr[1] && arr[1] == arr[2]) {
		if(arr[0] == 1) {
			return 1;
		}
		if(arr[0] == 2) {
			return 2;
		}
	}

	else if(arr[3] == arr[4] && arr[4] == arr[5]) {
		if(arr[3] == 1) {
                        return 1;
                }
                if(arr[3] == 2) {
                        return 2;
                }

	}
	
	else if(arr[6] == arr[7] && arr[7] == arr[8]) {
		if(arr[6] == 1) {
                        return 1;
                }
                if(arr[6] == 2) {
                        return 2;
                }
	}

	else if(arr[0] == arr[3] && arr[3] == arr[6]) {
		if(arr[0] == 1) {
                        return 1;
                }
                if(arr[0] == 2) {
                        return 2;
                }
	}

	else if(arr[1] == arr[4] && arr[4] == arr[7]) {
		if(arr[1] == 1) {
                        return 1;
                }
                if(arr[1] == 2) {
                        return 2;
                }
	}
	
	else if(arr[2] == arr[5] && arr[5] == arr[8]) {
		if(arr[2] == 1) {
                        return 1;
                }
                if(arr[2] == 2) {
                        return 2;
                }
	}


	else if(arr[0] == arr[4] && arr[4] == arr[8]) {
		if(arr[0] == 1) {
                        return 1;
                }
                if(arr[0] == 2) {
                        return 2;
                }
	}

	else if(arr[2] == arr[4] && arr[4] == arr[6]) {
		if(arr[2] == 1) {
                        return 1;
                }
                if(arr[2] == 2) {
                        return 2;
                }
	}
	
	return 0;
}

// print current status of the game
void check() {

	int win = winner();
	int draw = draww();

	if(draw == 1) {
		status = gtk_label_new("Draw");
		g_print("Draw");
		game_is_over = 1;
	}
	if(win == 1) {
		status = gtk_label_new("Player 1 won");
		g_print("Player 1 won");
		game_is_over = 1;
        }
        if(win == 2) {
                status = gtk_label_new("Player 2 won");
		g_print("Player 2 won");
		game_is_over = 1;
	}

	gtk_grid_attach (GTK_GRID (grid), status, 5, 0, 2, 2);
	gtk_widget_show_all(window);

	if(game_is_over) {
		exit(0);
	}
}

// Switch players until game ends
void turns() {
	check();
	
        if(player == 1) {
	        status = gtk_label_new("Player 1's move");
                player--;
        }

        if(player == 2) {
                status = gtk_label_new("Player 2's move");
                player++;
        }
}

void btn(GtkWidget *widget, gpointer user_data) {
	int n = (int)(intptr_t) user_data;

	if(!pressed[n]) {
		arr[n] = player;
		pressed[n] = 1;
		check();
	}
	else {
		turns();
	}
}

// print Tic-Tac-Toe grid
void ttt_grid(GtkApplication *app, gpointer user_data) {
	//GtkWidget *window;
	//GtkWidget *grid;
	GtkWidget *button;

	/* create a new window, and set its title */
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Game");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	/* Here we construct the container that is going pack our buttons */
	grid = gtk_grid_new ();

	/* Pack the container in the window */
	gtk_container_add (GTK_CONTAINER (window), grid);

	b1 = gtk_button_new_with_label ("1");
	g_signal_connect (b1, "clicked", G_CALLBACK (btn), (void*) 0);
	g_signal_connect(b1, "clicked", G_CALLBACK(pick), b1);
	gtk_grid_attach (GTK_GRID (grid), b1, 0, 0, 1, 1);

	b2 = gtk_button_new_with_label ("2");
	g_signal_connect (b2, "clicked", G_CALLBACK (btn), (void*) 1);
	g_signal_connect(b2, "clicked", G_CALLBACK(pick), b2);
	gtk_grid_attach(GTK_GRID(grid), b2, 1, 0, 1, 1);

	b3 = gtk_button_new_with_label ("3");
        g_signal_connect (b3, "clicked", G_CALLBACK (btn), (void*) 2);
	g_signal_connect(b3, "clicked", G_CALLBACK(pick), b3);
        gtk_grid_attach(GTK_GRID(grid), b3, 2, 0, 1, 1);

	b4 = gtk_button_new_with_label ("4");
        g_signal_connect (b4, "clicked", G_CALLBACK (btn), (void*) 3);
	g_signal_connect(b4, "clicked", G_CALLBACK(pick), b4);
        gtk_grid_attach (GTK_GRID (grid), b4, 0, 1, 1, 1);

        b5 = gtk_button_new_with_label ("5");
        g_signal_connect (b5, "clicked", G_CALLBACK (btn), (void*) 4);
	g_signal_connect(b5, "clicked", G_CALLBACK(pick), b5);
        gtk_grid_attach(GTK_GRID(grid), b5, 1, 1, 1, 1);

        b6 = gtk_button_new_with_label ("6");
        g_signal_connect (b6, "clicked", G_CALLBACK (btn), (void*) 5);
	g_signal_connect(b6, "clicked", G_CALLBACK(pick), b6);
        gtk_grid_attach(GTK_GRID(grid), b6, 2, 1, 1, 1);

        b7 = gtk_button_new_with_label ("7");
        g_signal_connect (b7, "clicked", G_CALLBACK (btn), (void*) 6);
	g_signal_connect(b7, "clicked", G_CALLBACK(pick), b7);
        gtk_grid_attach (GTK_GRID (grid), b7, 0, 2, 1, 1);

        b8 = gtk_button_new_with_label ("8");
        g_signal_connect (b8, "clicked", G_CALLBACK (btn), (void*) 7);
	g_signal_connect(b8, "clicked", G_CALLBACK(pick), b8);
        gtk_grid_attach(GTK_GRID(grid), b8, 1, 2, 1, 1);

        b9 = gtk_button_new_with_label ("9");
        g_signal_connect (b9, "clicked", G_CALLBACK (btn), (void*) 8);
	g_signal_connect(b9, "clicked", G_CALLBACK(pick), b9);
        gtk_grid_attach(GTK_GRID(grid), b9, 2, 2, 1, 1);
	
	button = gtk_button_new_with_label ("Quit");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 2, 1);

	status = gtk_label_new(" ");
	gtk_grid_attach (GTK_GRID (grid), status, 5, 0, 2, 2);

	/* Now that we are done packing our widgets, we show them all
	 * in one go, by calling gtk_widget_show_all() on the window.
	 * This call recursively calls gtk_widget_show() on all widgets
	 * that are contained in the window, directly or indirectly.
	 */
	gtk_widget_show_all (window);
}

int main(int argc, char *argv[]) {
	GtkApplication *app;
	int status_num;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (ttt_grid), NULL);

	status_num = g_application_run (G_APPLICATION (app), argc, argv);

	g_object_unref (app);

	return status_num;
}
