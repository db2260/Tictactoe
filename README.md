# Tictactoe
A tictactoe game written in C using GTK

Run on your system using this command:
gcc gridgtk2.c -Wl,--export-dynamic  `pkg-config --cflags --libs gtk+-3.0` && ./a.out
