
/////////////////////////////////
//                             //
// Header für die Verarbeitung //
// von Werten und Variablen    //
//                             //
/////////////////////////////////

#ifndef HANDLING_H
#define HANDLING_H


typedef struct {					// Struktur zum Aufnehmen des 
	long seller_id;					// Verkäufers und Preises eines Artikels
	float price;
} unit;

void set_colors (void);
void error_msg (const char *string);
void bubble_sort (unit *data);
long count_seller (unit *data);
void sum_data (unit *data, unit *sum);


#endif		// HANDLING_H
