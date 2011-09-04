
#include "includes\includes.c"


FILE *open_file (int filenumber) {					// öffnet den Stream der Datendatei
													// und gibt ihn zurück
	FILE *file;
	FILE *copy;

	if ((file = fopen 	(filenumber == 1 ? STR_FILENAME_1 :		// übergabe des richtigen Dateinamens anhand des Moduses
						(filenumber == 2 ? STR_FILENAME_2 : 
						(filenumber == 3 ? STR_FILENAME_3 :		// überprüfen ob die Datendatei vorhanden ist
						(filenumber == 4 ? STR_FILENAME_4 :
						(filenumber == 5 ? STR_FILENAME_5 : STR_FILENAME_6)))), "rb+")) == NULL) {

		if ((file = fopen 	(filenumber == 1 ? STR_FILENAME_1 :
							(filenumber == 2 ? STR_FILENAME_2 : 	// ansonsten eine Neue erstellen
							(filenumber == 3 ? STR_FILENAME_3 :
							(filenumber == 4 ? STR_FILENAME_4 :
							(filenumber == 5 ? STR_FILENAME_5 : STR_FILENAME_6)))), "wb+")) == NULL) {
			error_msg ("open_file / fileio");
		}

		if ((copy = fopen 	(filenumber == 1 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_1 :
							(filenumber == 2 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_2 :
							(filenumber == 3 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_3 :
							(filenumber == 4 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_4 :
							(filenumber == 5 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_5 :
											   "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_6)))), "rb")) != NULL) {

			restore_file (file, filenumber);			// stellt eine alte Datendatei wieder her,
			fclose (copy);								// falls noch eine Kopie vorhanden ist
		}
	}
					
	check_file (file, filenumber, 0);

	return file;
}


void init_file (FILE *file, long *counter) {		// liest den Zähler aus einer Datei aus
													// oder schreibt den Wert '0' hinein,
	fseek (file, 0, SEEK_SET);						// wenn er nicht vorhanden ist

	if (fread (counter, sizeof (long), 1, file) == 0) {
																// schreibt '0' als Zähler in die
		fseek (file, 0, SEEK_SET);								// Datei, wenn keiner vorhanden ist
		*counter = 0;
		if (fwrite (counter, sizeof (long), 1, file) == 0)
			error_msg ("init_file / fileio");
	}
}


void write_data (unit *data, long *counter, FILE *file) {		// schreibt Daten in eine Datei
																// und überprüft und schreibt den Zähler 
	long temp;
	
	fseek (file, 0, SEEK_END);
	
	if (fwrite (data, sizeof (unit), 1, file) == 0) 
		error_msg ("write_data / fileio  #1");

	
	fseek (file, 0, SEEK_SET);

	if (fread (&temp, sizeof (long), 1, file) == 0 || temp != *counter){printf("\n\n %i != %i \n\n", temp, *counter);
		error_msg ("write_data / fileio  #2");}


	++(*counter);
	fseek(file, 0, SEEK_SET);

	if (fwrite (counter, sizeof (long), 1, file) == 0)
		error_msg ("write_data / fileio  #3");

}


long load_files (FILE *file[]) {					// öffnet alle Datendateien
													// und liest die Zähler aus
	long units = 0;
	long temp;
	char check;


	for (int i = 0; i < 6 ; ++i) {

		if (i == 0 && (file[i] = fopen (STR_FILENAME_1, "rb+")) == NULL) { 			// wenn das Auslesen erfolgreich
			check += 1;																// war geht es bei 'else' weiter
		}

		else if (i == 1 && (file[i] = fopen (STR_FILENAME_2, "rb+")) == NULL) { 
			check += 2;
		}

		else if (i == 2 && (file[i] = fopen (STR_FILENAME_3, "rb+")) == NULL) { 	// einzelne Bits der Variable check setzen,
			check += 4;																// um später anzugeben können, welche Dateien
		}																			// nicht gefunden werden konnten

		else if (i == 3 && (file[i] = fopen (STR_FILENAME_4, "rb+")) == NULL) { 
			check += 8;
		}

		else if (i == 4 && (file[i] = fopen (STR_FILENAME_5, "rb+")) == NULL) { 
			check += 16;
		}

		else if (i == 5 && (file[i] = fopen (STR_FILENAME_6, "rb+")) == NULL) { 
			check += 32;
		}
		else {
			check_file (file[i], i + 1, 0);
			fseek (file[i], 0, SEEK_SET);						// wenn das Öffnen der Datei erfolgreich war
			fread (&temp, sizeof (long), 1, file[i]);			// werden die Zähler geladen und addiert
			units += temp;
		}
	}
	if (check != 0 && check != 63) {
		file_opening_failed (check);
	}
	return units;
}


void load_data (unit *data, FILE *file[]) {			// lädt alle Daten aus den Dateien

	for (int i = 0; i < 6; ++i) {
	
		if (file[i] != NULL) {
			
			fseek (file[i], sizeof (long), SEEK_SET);
			
			for (; ; ++data) {									// lädt so lange Daten aus der Datei
																// bis ihr Ende erreicht wurde
				if (fread (data, sizeof (unit), 1, file[i]) == 0 ) {
					if (feof (file[i]))
						break;

					else
						error_msg ("load_data/fileio");
				}

			}
		}
	}

	data->seller_id = -1;
}


void print_file (unit *data) {						// erstellt die drei HTML-Ausgabedateien

	FILE *file;
	unit *var_struct;
	

	if ((file = fopen (STR_FILENAME_UNSORT, "w")) == NULL)		// erstellen der unsortierten Datei
		error_msg ("print_file / fileio #1");

	
	fprintf (file, STR_HTML_HEADER, "Unsortierte Ausgabe",	"				<th><u>Verk&auml;ufernummer</u></th>\n"
															"				<th><u>Preis</u></th>\n");

	for (var_struct = data; var_struct->seller_id != -1; ++var_struct) {		// ausgeben aller Artikel
		fprintf (file,	"			<tr>\n"										// solange nicht der letzte erreicht wurde
						"				<td>%i</td>\n"
						"				<td>%.2f</td>\n"
						"			</tr>\n", var_struct->seller_id, var_struct->price);
	}

	fprintf (file, STR_HTML_BODY);
	fclose (file);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if ((file = fopen (STR_FILENAME_SORT, "w")) == NULL)		// erstellen der sortieren Datei
		error_msg ("print_file/fileio #2");

	
	fprintf (file, STR_HTML_HEADER, "Sortierte Ausgabe",	"				<th><u>Verk&auml;ufernummer</u></th>\n"
															"				<th><u>Preis</u></th>\n");
	bubble_sort (data);						// sotiert das Datenfeld mit der Bubblesort-Methode

	for (var_struct = data; var_struct->seller_id != -1; ++var_struct) {		// gibt alle Artikel nach
		fprintf (file,	"			<tr>\n"										// Verkäufer sotiert aus
						"				<td>%i</td>\n"
						"				<td>%.2f</td>\n"
						"			</tr>\n", var_struct->seller_id, var_struct->price);

		if ((var_struct + 1)->seller_id != -1 && var_struct->seller_id != (var_struct + 1)->seller_id) {
			fprintf (file, 	"			<tr>\n"
							"				<td class = \"empty\"></td>\n"			// wenn die Artikel des nächsten Verkäufers
							"				<td class = \"empty\"></td>\n"			// kommen, wird eine leere Zeile eingeschoben
							"			</tr>\n");
		}
	}

	fprintf (file, STR_HTML_BODY);
	fclose (file);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if ((file = fopen (STR_FILENAME_SUM, "w")) == NULL)			// erstellen der Datei mit summierten Artikelpreisen
		error_msg ("print_file / fileio #3");

	
	fprintf (file, STR_HTML_HEADER, "Summierte Ausgabe",	"				<th><u>Verk&auml;ufernummer</u></th>\n"
															"				<th><u>Auszahlung</u></th>\n"
															"				<th><u>Unterschrift</u></th>\n");
	unit *sum = malloc (sizeof ( unit[count_seller (data)] ));
	sum_data (data, sum);										// aufsummieren der Artikel eines Verkäufers

	for (; sum->seller_id != -1; ++sum) {
		
		if (sum->price != 0) {
			fprintf (file,	"			<tr>\n"
							"				<td class = \"sign\">%i</td>\n"
							"				<td class = \"sign\">%.2f</td>\n"
							"				<td class = \"sign\">&nbsp;</td>\n"
							"			</tr>\n", sum->seller_id, CAUTION_WORTH * sum->price);
		

			if ((sum + 1)->seller_id != -1) {
				fprintf (file, 	"			<tr>\n"
								"				<td class = \"empty\"></td>\n"			// wenn der nächsten Verkäufer
								"				<td class = \"empty\"></td>\n"			// kommt, wird eine leere Zeile eingeschoben
								"				<td class = \"empty\"></td>\n"
								"			</tr>\n");
			}
		}

	}

	fprintf (file, STR_HTML_BODY);
	fclose (file);
	free (sum);
}


void change_dir (char *argv_0) {								// wechselt das Arbeitsverzeichnis
																// in das, wo das Programm sich befindet
	for (int i = strlen (argv_0) - 1; i >= 0; --i) {
		if (argv_0[i] == '\\'){
			argv_0[i] = 0;										// sucht von hinten beginnend nach einem
			break;												// '\' und ersetzt es durch ein '\0'
		}
	}
	_chdir (argv_0);
}


void copy_file (FILE *source, int modus) {			// macht eine Kopie von einer Datei
	
	char buffer;
	FILE *target;
	if ((target = fopen (modus == 1 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_1 :
						(modus == 2 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_2 :
						(modus == 3 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_3 :
						(modus == 4 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_4 :
						(modus == 5 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_5 :
									  "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_6)))), "wb")) == NULL) {

		error_msg (" copy_file / fileio");
	}

	fseek (source, 0, SEEK_SET);
	while (fread (&buffer, 1, 1, source)) {				// liest so lange, bis nicht das Ende der Quelldatei erreicht
		fwrite (&buffer, 1, 1, target);					// wurde, ein Zeichen aus und schreibt es in die Zieldatei
	}

	fclose (target);

}


void check_file (FILE *file, int modus, long counter) {								// überprüft den Zähler,
																					// und ob er mit der tatsächlichen Anzahl
	if (counter == 0) {																// an Datensätzen übereinstimmt
		fseek (file, 0, SEEK_SET);
		if (fread (&counter, sizeof (long), 1, file) == 0)
			return ;
	}
	fseek (file, 0, SEEK_END);
	if (( ftell (file) - sizeof (long) ) / (float) sizeof (unit) != counter) {

		printf (STR_FILE_CORRUPT, modus);
		want_continue ();
		restore_file (file, modus);						// Datei wird wiederhergestellt,
														// wenn das Programm fortgesezt werden soll
		printf (STR_FILE_RESTORED);
		print_ui (2);		
	}
}


void restore_file (FILE *target, int modus) {					// Wiederherstellung einer Datei
																// aus ihrer Sicherungsdatei, im Falle eines Fehlers
	FILE *source;
	char buffer = 0;

	source = fopen  (modus == 1 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_1 :
					(modus == 2 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_2 :
					(modus == 3 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_3 :
					(modus == 4 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_4 :
					(modus == 5 ? "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_5 :
								  "..\\" STR_COPY_DIR "\\" STR_COPY_PRE STR_FILENAME_6)))), "rb");
	
	_ftruncate (_fileno (target), 0);							// löscht den aktuellen Inhalt der Zieldatei
	fseek (target, 0, SEEK_SET);

	if (source != NULL){
		fseek (source, 0, SEEK_SET);
		while (fread (&buffer, 1, 1, source)) {						// liest so lange, bis nicht das Ende der Quelldatei erreicht
		fwrite (&buffer, 1, 1, target);								// wurde, ein Zeichen aus und schreibt es in die Zieldatei
	}
		fclose (source);
	}
	else {
		//fwrite (&buffer, sizeof (long), 1, target);
		printf (STR_CANT_RESTORE);
		error_msg ("restore_file / fileio");
	}

}


