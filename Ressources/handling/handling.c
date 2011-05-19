
#include "includes\includes.c"


void set_colors (void) {			// ändert die Text- und Hintergrundfarbe
									// der Konsole
	_textcolor (TEXT_COLOR);
	_textbackground (BACKGROUND_COLOR);
	_clrscr ();
}


void error_msg (const char *string) {			// Funktion die bei einem Fehler aufgerufen wird
												// und das Programm verlässt
	printf (STR_ERROR "%s\n\n", string);
	_getch ();
	_fcloseall();
	exit (1);
}


void bubble_sort (unit *data) {				// sotiert ein Datenfeld nach der Verkäufernummer
											// mit der Bubbelsort-Methode
	unit temp;
	unit *pdata;

	for (; data->seller_id != -1; ++data) {
		for (pdata = data + 1; pdata->seller_id != -1; ++pdata) {
			
			if (data->seller_id > pdata->seller_id) {					// wenn ein folgender Wert grösser als
																		// der Aktuelle ist werden beide getauscht
				temp.seller_id = data->seller_id;
				temp.price = data->price;

				data->seller_id = pdata->seller_id;
				data->price = pdata->price;

				pdata->seller_id = temp.seller_id;
				pdata->price = temp.price;
			}
		}
	}
}


long count_seller (unit *data) {			// zählt die Anzahl der verschiedenen Verkäufernummern
											// in einem Datenfeld und gibt sie zurück
	long counter; 

	for (counter = 1; data->seller_id != -1; ++data) {		// durchgehen aller Artikel und inkrementieren des Zähler,
		if (data->seller_id != (data + 1)->seller_id)		// wenn zwei verschiedene Verkäufernummern gefunden wurden
			++counter;
	}
	return counter;
}


void sum_data (unit *data, unit *sum) {			// summiert die Preise aller Artikel eines Vekäufers
												// und schreibt sie in das Feld auf das 'sum' zeigt

	for (sum->seller_id = data->seller_id; data->seller_id != -1; ++data) {
		sum->price += data->price;

		if (data->seller_id != (data + 1)->seller_id) {			// ändern der Verkäufernummer
			++sum;												// auf die neue aktuelle
			sum->seller_id = (data + 1)->seller_id;
		}
	}
}
