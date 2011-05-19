
	////////////////////////////////
	//                            //
	// Header für die Speicherung //
	// der verwendeten Strings    //
	//                            //
	////////////////////////////////

#ifndef STRING_H
#define STRING_H


#define STR_FILENAME_1 "daten_kasse_1.klm"					// primäre Dateiname
#define STR_FILENAME_2 "daten_kasse_2.klm"
#define STR_FILENAME_3 "daten_kasse_3.klm"
#define STR_FILENAME_4 "daten_kasse_4.klm"
#define STR_FILENAME_5 "daten_kasse_5.klm"
#define STR_FILENAME_6 "daten_kasse_6.klm"
#define STR_COPY_DIR "Sicherung"							// Name des Sicherungsverzeichnisses
#define STR_COPY_PRE "kopie_"								// Präfix für die Kopien

#define STR_FILENAME_UNSORT "ausgabe_unsortiert.html"		// Name der HTML-Dateien
#define STR_FILENAME_SORT "ausgabe_sortiert.html"
#define STR_FILENAME_SUM "ausgabe_summiert.html"

#define STR_TITLE_MODE "KLM-CheckOut - Datenverarbeitungsprogramm für den Marg. Kleidermarkt"
#define STR_TITLE_INPUT "Eingabe für Kasse "
#define STR_TITLE_OUTPUT "Ausgabe-Dateien werden erstellt..."		// Fenstertitel
#define STR_TITLE_CREDITS "KLM-CheckOut - Impressum"

#define STR_ERROR "FEHLER IN "			// Ausgabestring bei Programmfehler (Abbruch)
#define STR_FILE_CORRUPT "\n Die aktuelle Datei (Kasse Nr. %i) ist besch„digt!\n"\
						 " îîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîî\n"\
						 " Soll die Sicherung geladen werden? (j/n)\n\n "
#define STR_FILE_RESTORED 	"\n\n Die Datei wurde wiederhergestellt!\n"\
							" Falls dieser Fehler w„hrend der Eingabe auftritt,\n"\
							" k”nnte der letzte Kunde nicht registriert worden sein!\n\n"

#define STR_NO_FILES "\n Keine Daten gefunden!\n Daten-Dateien bitte in das gleiche Verzeichniss wie dieses Programm kopieren.\n\n "
#define STR_OPENING_FAIL "\n Folgende Dateien konnten nicht gefunden werden:\n"
#define STR_WANT_CONTINUE "\n\n Trotzdem weitermachen (j/n)?\n\n "
#define STR_CONTINUE_PROG "\n\n Das Programm wird fortgesetzt!\n "		// diverse Meldungen
#define STR_STOP_PROG "\n\n Das Programm wird abgebrochen!\n "			// bei Datenauswertung
#define STR_ONLY_J_N "\n\n Nur \'j\' oder \'n\' eingeben!\n\n "

#define STR_CHOOSE_MOD  "\n Bitte Modus ausw„hlen:\n\n"		/* Splash-Screen */\
						" [1]. Kasse\n"\
						" [2]. Kasse\n"\
						" [3]. Kasse\n"\
						" [4]. Kasse\n"\
						" [5]. Kasse\n"\
						" [6]. Kasse\n\n"\
						" [7]  Auswerten\n"\
						" [0]  Beenden\n\n"\
						" [i]  Impressum\n\n "

#define STR_OUTPUT_SUM "Summe dieses Kunden"							// diverse Bestätigungen
#define STR_PRINTED "\n Alle Dateien wurden erfolgreich erstellt\n "
#define STR_END "\n Programm wird beendet!\n "

#define STR_WRONG_INPUT "\n\n Falsche Eingabe!\n\n "				// Eingabenfehler-Korrektur
#define STR_INPUT_SYNTAX1 "\b \n³  ³Bitte nur Zahlen eingeben!"
#define STR_ERASE_SYNTAX1 "\n³  ³                              "
#define STR_INPUT_SYNTAX2 "\b \n³  ³Bitte nur Zahlen und Komma eingeben!"
#define STR_ERASE_SYNTAX2 "\n³  ³                                    "
#define STR_INPUT_SYNTAX3 "\n³  Bitte Verk„ufernummer angeben!"

#define STR_HTML_HEADER	"<html>\n"					/* HTML-Ausgabe-Code */\
						"<head>\n"\
						"	<title>%s</title>\n"\
						"	<style>\n"\
						"		tr, td, th {border: 2px solid #c0c0c0; padding:3px;}\n"\
						"		tr, td {text-align: right;}\n"\
						"		tr, td, th {width: 200px;}\n"\
						"		.empty {background-color:#c0c0c0;padding:1px;}\n"\
						"		.sign {padding:5px;}\n"\
						"		table {border-style:solid; border-size: 1px;border-collapse:collapse;}\n"\
						"	</style>\n"\
						"</head>\n"\
						"<body>\n"\
						"	<table border=\"1\">\n"\
						"		<thead>\n"\
						"			<tr>\n"\
						"%s"\
						"			</tr>\n"\
						"		</thead>\n"\
						"		<tbody>\n"\
						"			<tr>\n"\
						"				<td></td>\n"\
						"				<td></td>\n"\
						"			</tr>\n"

#define STR_HTML_BODY	"		</tbody>\n"\
						"	</table>\n"\
						"</body>\n"\
						"</html>"

#define STR_CREDITS "\n"\
					" KLM-CheckOut - Datenverarbeitungsprogramm fr den Marg. Kleidermarkt\n"\
					" ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n\n\n"\
					" Code, Programmstruktur, UI und Idee von:\n"\
					" îîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîî\n"\
					" Yannik Zimmermann (zimmermannyannik@web.de) alias Ro0mquy (ro0mquy@web.de)\n\n\n"\
					" Icon- und UI-Design-Beratung von:\n"\
					" îîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîîî\n"\
					" Philipp Stephan (design@psoke.de) alias Ps0ke (http://www.psoke.de)\n\n\n\n"\
					" ¸ 2010 - 2011 Yannik Zimmermann\n"\
					" All rights reserved\n "

#endif // STRING_H
