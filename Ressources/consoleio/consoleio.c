
#include "includes\includes.c"


void fb (void) {							// flush buffer
	while (_kbhit ()) {
		_getch ();
	}
}


int get_mod (int *modus) {					// fragt ab welche Option man benutzen will 

	printf (STR_CHOOSE_MOD);
	fb ();

	while (!((*modus  = _getche ()) == 'i' || isdigit (*modus)) || *modus != 'i' && (*modus -= '0') > 7) {	// (*modus -= '0') macht char zu int
		printf (STR_WRONG_INPUT);
		fb ();
	}

	_getch ();
	_clrscr ();
			
	return *modus;
}
	

unit* get_values (unit* article, int article_number) {			// Hauptfunktion, die Verkäufennummer und Preis entgegen nimmt
	char buffer_1[BUFFER_SIZE];
	char buffer_2[BUFFER_SIZE-25];
	int i = 0, k = 0;
	
	//fb ();	// wahrscheinlich nicht so gut
	printf ("³%2i³ ", article_number);		// UI

	jump_label:							// Sprungmarke :'( für das zurückgehen in die erste Schleife
	
	for (i; i < BUFFER_SIZE && !((buffer_1[i] = _getche ()) == '\r' || buffer_1[i] == '\t'); ++i) {		// erste Haupt-for-Schleife für
																										// den Verkäufer, die solange
		printf (STR_ERASE_SYNTAX1);					// löschen alter Fehlermeldungen					// Zeichen einliest, bis [ENTER],
		_gotoxy (i + 7, _wherey () - 1);																// [TAB] oder die maximale Anzahl
																										// an Zeichen eingelesen wurde.
		if (buffer_1[i] == '\b' && i > 0) {			// löschen der Eingabe bei [Backspace]
			i -= 2;
			printf ("\b\b \b");
		}

		else if ( !(buffer_1[i] == '\x1B') && !(isdigit (buffer_1[i]))) {
			printf (STR_INPUT_SYNTAX1);				// Ausgabe einer Fehlermeldung und Dekrementieren von 'i'
			_gotoxy (i + 6, _wherey () - 1);		// wenn keine Zahl oder [ESC] gedrückt wurde
			--i;
		}
	}

	buffer_1[i] = 0;								// setzen des letzen Elements des Buffer-Arrays auf '\0' oder nur 0

	if ( strpbrk (buffer_1, "\x1B") == NULL) {		// Aktionen wenn nicht [ESC] gedrückt wurde
 
		if ((article->seller_id = atoi (buffer_1)) == 0 || (unsigned)article->seller_id > 999999) {	// Umwandel des Buffers in eine Zahl
			printf (STR_INPUT_SYNTAX3);
			if (i == BUFFER_SIZE) {
				_gotoxy (i + 5, _wherey () - 1);
				--i;
				printf(" \b");
			}
			else {
				_gotoxy (i + 6, _wherey () - 1);				// Fehlermeldung und zurückspringen in die for-Schleife
			}
			goto jump_label;									// wenn die Verkäufernummer == '0' ist
		}
	}
	else if (article->seller_id == 0){				// signalisiert, dass man zweimal [ESC] gedrückt hat, da die 
		article->seller_id = -1;					// Verkäufernummer nur '0' ist wenn man vorher schon mal [ESC] gedrückt hat

		return article;
	}
	else {
		article->seller_id = 0;						// setzt die Verkäufernummer auf '0' wenn man [ESC] gedrückt hat
		article->price = 0.0;

		return article;
	}

	printf (STR_ERASE_SYNTAX1);
	_gotoxy (POSITION_PRICE, _wherey () - 1);		// Cursor in die rechte Bildschirmhälfte setzen

////////////////////////////////////////////////////////////////////////////////////////////////////////// Verarbeitung für den Preis

	for (k; k < BUFFER_SIZE-26 && !((buffer_2[k] = _getche ()) == '\r' || buffer_2[k] == '\t'); ++k) {		// zweite Haupt-for-Schleife
																										// für den Preis, die solange
		printf (STR_ERASE_SYNTAX2);						// löschen alter Fehlermeldungen				// Zeichen einliest, bis [ENTER],
		_gotoxy (POSITION_PRICE + 1 + k, _wherey () - 1);												// [TAB] oder die maximale Anzahl
																										// an Zeichen eingelesen wurde.

		if (buffer_2[k] == ',' || buffer_2[k] == '.') 	// ersetzen eines Kommas durch einen Punkt
			buffer_2[k] = '.';

		
		else if (buffer_2[k] == '\b') {					// löschen der Eingabe bei [Backspace]
			printf ("\b\b \b");
			
			if (k == 0) {
				--i;
				_gotoxy (i + 6, _wherey ());			// zurückspringen in die Verkäufer-Schleife
				printf (" \b");							// wenn das erste Zeichen gelöscht wurde
				goto jump_label;
			}

			else {
				k -= 2;
			}
		}

		else if ( (!(buffer_2[k] == '-')) && !(buffer_2[k] == '\x1B') && !(isdigit (buffer_2[k]))) {
			printf (STR_INPUT_SYNTAX2);
			_gotoxy (k + POSITION_PRICE, _wherey () - 1);	// Ausgabe einer Fehlermeldung und Dekrementieren von 'k'
			--k;											// wenn keine Zahl, kein Minus oder [ESC] gedrückt wurde
		}
	}

	buffer_2[k] = 0;									// setzen des letzen Elements des Buffer-Arrays auf '\0' oder nur 0

	if ( strpbrk (buffer_2, "\x1B") == NULL) {
		article->price = strtof (buffer_2, NULL);		// Umwandel des Buffers in eine Gleitkommazahl
		putch ('\n');
	}
	else if (article->seller_id == 0){					// signalisiert, dass man zweimal [ESC] gedrückt hat, da die
		article->seller_id = -1;						// Verkäufernummer nur '0' ist wenn man vorher schon mal [ESC] gedrückt hat
	}
	else {
		article->seller_id = 0;							// setzt die Verkäufernummer auf '0' wenn man [ESC] gedrückt hat
		article->price = 0.0;
	}
	
	return article;
}
	

void print_sum (float sum) {				// gibt die Summe des aktuellen Kunden aus
	
	print_ui (3);

	_gotoxy (3, _wherey () - 3);
	_textcolor (HIGHLIGHT_COLOR);
	printf (STR_OUTPUT_SUM ": %5.2f\n\n\n\n",sum);		// Ausgabe in rot
	_textcolor (TEXT_COLOR);
}


void file_opening_failed (char check) {		// gibt aus welche Dateien nicht gefunden wurden
	
	printf (STR_OPENING_FAIL);

	if ((check & 1) != 0) {					// Bitweises Prüfen der Variable 'check' 
		printf ("\n\t" STR_FILENAME_1);		// und anschließende Ausgabe der entsprechenden Dateinamen
	}
	if ((check & 2) != 0) {
		printf ("\n\t" STR_FILENAME_2);
	}
	if ((check & 4) != 0) {
		printf ("\n\t" STR_FILENAME_3);
	}
	if ((check & 8) != 0) {
		printf ("\n\t" STR_FILENAME_4);
	}
	if ((check & 16) != 0) {
		printf ("\n\t" STR_FILENAME_5);
	}
	if ((check & 32) != 0) {
		printf ("\n\t" STR_FILENAME_6);
	}
	printf (STR_WANT_CONTINUE);

	want_continue ();
}


void print_ui (int mod) {					// gibt verschiedene UI-Elemente aus

	int i;
	
	switch (mod) {
		case 1:
			
			_gotoxy (1, 1);									// ganzes UI mit Rahmen und Mittelstreifen
			printf ("ÚÄÄÂ");

			while (_wherex () != BUFFER_SIZE + 7){
				putch ('Ä');
			}
			putch ('Â');

			while (_wherex () != 80) {
				putch ('Ä');
			}
			printf ("¿");
			

			for (i = 2; i < 300; ++i) {
				_gotoxy (1, i);
				printf ("³  ³");

				_gotoxy (BUFFER_SIZE + 7, i);
				putch ('³');

				_gotoxy (80, i);
				putch ('³');
			}

			_gotoxy (1, 1);
			_gotoxy (1, 2);
			break;

		case 2:

			printf ("ÃÄÄÅ");								// horizontaler Trennstrich

			while (_wherex () != BUFFER_SIZE + 7) {
				putch ('Ä');
			}
			putch ('Å');

			while (_wherex () != 80) {
				putch ('Ä');
			}
			putch ('´');

			break;

		case 3:

			_gotoxy (1, _wherey () - 1);					// gibt das Grundgerüst für die Summe eines Kunden aus
			printf ("ÃÍÍÊ");

			while (_wherex () != BUFFER_SIZE + 7) {
				putch ('Í');
			}
			putch ('Ê');

			while (_wherex () != 80) {
				putch ('Í');
			}
			putch ('´');


			for (i = 0; i < 3; ++i) {
				_gotoxy (2, _wherey ());
				while (_wherex () != 80) {
					putch (' ');
				}
				putch ('\n');
			}

			printf ("ÃÍÍË");

			while (_wherex () != BUFFER_SIZE + 7) {
				putch ('Í');
			}
			putch ('Ë');

			while (_wherex () != 80) {
				putch ('Í');
			}
			putch ('´');

			break;

		case 4:

			i = _wherey ();									// positioniert Cursor in der Mitte des Bildschirms
			if ( i > 285) {
				_gotoxy (1, 300);
				
				for (int k = 0; k < 5; ++k) {
					putch ('³');

					_gotoxy (BUFFER_SIZE + 7, _wherey ());
					putch ('³');

					_gotoxy (80, _wherey ());
					putch ('³');
				}
				i -= 5;
				_gotoxy (1, 275);
			}

			if ( i > INPUT_POSITION) {
				_gotoxy (1, i + (25 - INPUT_POSITION));
				_gotoxy (1, i);
			}
			break;
	}
}


void set_title (int modus) {				// setzt den Fenstertitel

	char string[30];

	switch (modus) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			sprintf (string, "title " STR_TITLE_INPUT "%i", modus);
			system (string);
			break;

		case 7:
			system ("title " STR_TITLE_OUTPUT);
			break;

		case 0:
			system ("title " STR_TITLE_MODE);
			break;

		case 105:
			system ("title " STR_TITLE_CREDITS);
	}
}


void want_continue (void) {					//nimmt entgegen, ob man das Programm nach einem Fehler fortsetzen will
	
	char input;

	do {
		switch (input = _getche ()) {
			case 'j':
			case 'J':
				printf (STR_CONTINUE_PROG);
				break;
			
			case 'n':
			case 'N':
				printf (STR_STOP_PROG);
				_getch ();
				exit (1);

			default:
				printf (STR_ONLY_J_N);
			}
	} while (!(input == 'j' || input == 'J'));
}	

