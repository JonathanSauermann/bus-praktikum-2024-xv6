#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int seconds;
  
  // Wenn keine Argumente übergeben wurden
  if (argc != 2) {
    fprintf(2, "Usage: sleep [sec]\n");
    exit(1);
  }

  // Argument in Sekunden (String zu Integer konvertieren)
  seconds = atoi(argv[1]);

  // Falls die Konvertierung nicht erfolgreich war oder der Wert <= 0
  if (seconds <= 0) {
    fprintf(2, "sleep: invalid time specified\n");
    exit(1);
  }

  // Umrechnung der Sekunden in "Ticks" (10 Ticks pro Sekunde)
  int ticks = seconds * 10;

  // Syscall sleep aufrufen
  sleep(ticks);

  // Erfolgreicher Abschluss des Programms
  exit(0);
}
