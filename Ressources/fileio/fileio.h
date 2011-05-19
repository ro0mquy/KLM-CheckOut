
	////////////////////////////////////
	//                                //
	// Header für Schreiben und Lesen //
	// in und aus einer Datei         //
	//                                //
	////////////////////////////////////


#ifndef FILEIO_H
#define FILEIO_H


FILE *open_file (int filenumber);
void init_file (FILE *file, long *counter);
void write_data (unit *data, long *counter, FILE *file);
long load_files (FILE *file[]);
void load_data (unit *data, FILE *file[]);
void print_file (unit *data);
void change_dir (char *argv_0);
void copy_file (FILE *source, int modus);
void check_file (FILE *file, int modus, long counter);
void restore_file (FILE *target, int modus);


#endif		// FILEIO_H
