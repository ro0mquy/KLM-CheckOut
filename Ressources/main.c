
//////////////////////////////////////////////////////////
//														//
// Hauptfunktion des Datenverarbeitungsprogramm  für	//
// den Marokkaner Kleidermarkt - © by Yannik Zimmermann	//
//														//
//////////////////////////////////////////////////////////

#include "includes\includes.c"



int main (int argc, char *argv[]) {

	// set vars
	int modus;

	set_colors ();
	change_dir (argv[0]);					// setzt das Arbeitsverzeichnis in das, wo die auszuführende Datei liegt

	
	do {
		set_title (0);
 
		if (get_mod (&modus) == 105) {
			set_title (modus);
			printf (STR_CREDITS);
			_getch ();
			_clrscr ();
		}

		else if (modus == 7) {		// if-Abzweigung für das Auswerten der Dateien und Erstellen der HTMLs
			long counter_all;
			FILE *file[6];					// Feld für alle sechs Datendateien

			set_title (modus);
			counter_all = load_files (file);


			if (counter_all != 0) {
				unit *data_all = malloc ( sizeof ( unit[counter_all + 1] ));		// reserviert Speicher für alle Datenunits


				load_data (data_all, file);
				print_file (data_all);

				free (data_all);													// gibt den Speicher für alle Datenunits wieder frei
				_fcloseall();

				printf (STR_PRINTED);
				_getch ();
			}

			else {
				printf (STR_NO_FILES);								// dieser Programmzweig wird nur durchlaufen, 
				_getch ();											// wenn überhaupt keine passenden Dateien im
			}														// gleichen Verzeichnis liegen wie das Programm
		}

		else if (modus > 0) {				// if-Abzweigung für die Eingabe von Artikeldaten und Speicherung in einer Datei
			FILE* workfile;
			unit data;
			long counter;
			float sum = 0.0;						// Gesamtsumme eines Käufers
			data.seller_id = 0;						// reseten der Verkäufernummer

			print_ui (1);

			set_title (modus);
			workfile = open_file (modus);
			init_file (workfile, &counter);

			_mkdir ("..\\" STR_COPY_DIR);			// Erstellen des Sicherungs-Verzeichnisses
			system ("attrib +h ..\\" STR_COPY_DIR);	// und verstecken diese Verzeichnisses

			do {									// Schleife in der Daten eingelesen und gespeichert werden
				get_values (&data);

				if (data.seller_id == -1) {			// Abbruch bei Doppel-[ESC]
					continue;
				}
				else if (data.seller_id == 0) {					// Ausgabe der Zwischensumme und erstellen einer Sicherungskopie
					print_sum (sum);
					sum = 0.0;
					check_file (workfile, modus, counter);
					copy_file (workfile, modus);
				}
				else {											// sdchreiben des aktuellen Artikels in die Datei
					sum += data.price;

					write_data (&data, &counter, workfile);
					print_ui (2);
				}
				print_ui (4);
			} while (data.seller_id != -1);

			fclose (workfile);
		}

		_clrscr ();
	} while (modus != 0);

	printf (STR_END);

	fb ();
	_getch ();
	_fcloseall();

	return 0;
}
