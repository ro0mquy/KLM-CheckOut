
	/////////////////////////////////
	//                             //
	// Header für Ein- und Ausgabe //
	// von und auf den Bildschirm  //
	//                             //
	/////////////////////////////////

#ifndef CONSOLEIO_H
#define CONSOLEIO_H


#define putch(ch) putchar ((unsigned char) ch)			// private putchar-Funktion um
														// einen Converting-Error zu verhindern
void fb (void);
int get_mod (int* modus);
unit *get_values (unit* article);
void print_sum (float sum);
void file_opening_failed (char string);
void print_ui (int mod);
void set_title (int modus);
void want_continue (void);

#endif	// CONSOLEIO_H
