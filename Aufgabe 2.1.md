Aufgabe 2.1

a)

Durch den Patch werden in den Funktionen exec(), fork(), exit() und wait() printf-Befehle hinzufügt, die Informationen über die Prozesse liefern. In exec() werden die PID und der Dateipfad ausgegeben, in fork() wird ausgegeben, durch den Elternprozess mit seiner PID ein fork()-Befehl ausgeführt wurde und welche PID der Kindprozess jetzt hat. In exit() wird ausgegeben, welche PID gerade beendet wird. In wait() wird ausgegeben welche PID gerade den wait()-Befehl aufgerufen, dass dieser auf den Kindprozess mit seiner PID wartet und dann anschließend, dass der Elternprozess (mit PID) das warten beendet hat.



b)

Lebenszyklus:

Die Shell (PID 2) führt den fork()-Befehl aus und erstellt einen Kindprozess (PID 3). Der Elternprozess (PID 2) wartet, bis PID 3 beendet ist. Der Kindprozess (PID 3) führt den echo-Befehl und anschließend den exit-Befehl aus. Danach ist das warten des Elternprozesses beendet und dieser führt auch den exit-Befehl aus und beendet sich.  



c)

Der erste Prozess im System ist der Init-Prozess mit der PID 1. Er wird direkt nach dem Booten des Kernels gestartet und endet nicht solange das OS läuft.
    


d)

Die Shell (PID 2) führt den fork()-Befehl aus und erstellt einen neuen Prozess (PID 4) (der für cat und wc zuständig ist) und wartet. PID 4 forked erneut und erstellt die PID 5 (cat) und PID 6 (wc) und wartet anschließend ebenfalls. Der cat-Prozess (PID 5) liest die Eingabe von der Konsole und sendet sie über die Pipe weiter. Anschließend beendet er sich mit exit(). Der wc-Prozess (PID 6) empfängt die Ausgabe des cat-Prozesses durch die Pipe und zählt die Zeilen, Wörter und Zeichen. Nach dem Drücken von STRG + D wird die Pipe geschlossen und PID 5 und 6 beenden sich jeweils durch exit(). Danach hat PID 4 das warten beendet und führt exit() aus. PID 2, also die Shell, ist wieder bereit neue Befehle entgegenzuehmen.



e)

Der init-Prozess der erste Prozess (PID 1) und die anschließend gestartete Shell immer PID 2. Danach werden PIDs fortlaufend zugewiesen. Werden diese beendet, dann ist diese Nummer wieder zur Vergabe frei.



f)

Bei einem Aufruf von exec() wird zuerst die zu ladende Datei im Dateisystem geöffnet. In einer erweiterten exec()-Funktion könnte die erste Zeile des Skripts daraufhin überprüft werden, ob sie mit einem Shebang beginnt (#!).

Wenn die Datei mit einer Shebang beginnt, würde der Prozess die angegebene Shell oder das angegebene Interpreter-Programm (z. B. /bin/sh) aufrufen und den Rest des Skripts als Argumente übergeben.



g)

Siehe "Aufgabe 2.1 g.pdf".
