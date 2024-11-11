#include "kernel/types.h"       //Für grundlegende Typdefinitionen wie int
#include "user/user.h"          //für Systemaufrufe wie sleep(), exit und Funktionen iwe printf(), atoi()


int main(int argc, char *argv[]) {
    //überprüfen ob Parameter eingegeben wurde
    if (argc < 2) {
        //Ausgabe Meldung 
        printf("Benutze: sleeo [sec]\n");
        exit(1); //Beenden des Programmes wie es in xv6 erforderlich ist
    }

    int seconds = atoi(argv[1]);
    //Überprüfen ob eingabe einen gültigen Wert hat 
    if  (seconds < 0) {
        printf("Error: Zeit muss positiv sein");
        exit(1);
    }
    //Zu "ticks" konvertieren (10 Ticks pro Sekunde, getestet)
	int ticks = seconds * 10;
    //Systemaufruf sleep() verwenden um die zeit abzuwarten
    sleep(ticks);
    //Programm beenden
    exit(0);
}