
// constants
#define _CONIO_RETRO_COLORS
#define BUFFER_SIZE 35							// legt fest wie viele zeichen man maximal in eine Spalte schreiben kann
#define POSITION_PRICE (BUFFER_SIZE + 9)		// legt fest an welcher Position die zweite Spalte beginnt
#define CAUTION_WORTH 0.85						// legt fest wie viel des Gesamtgewinns ausgegeben wird
#define INPUT_POSITION 15						// legt fest auf welcher Höhe sich der Inputcursor befindet
#define TEXT_COLOR WHITE
#define BACKGROUND_COLOR BLACK
#define HIGHLIGHT_COLOR LIGHTRED

// public headers
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <io.h>

// private headers
#include "handling\handling.h"
#include "consoleio\consoleio.h"
#include "fileio\fileio.h"
#include "string\mystrings.h"
