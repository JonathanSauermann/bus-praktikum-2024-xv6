**Aufgabe 0.5: Fehler finden und beheben**

Die Fehlermeldung des Kompilers lautet:

***ANFANG MELDUNG***

user/ls.c: In function ‘main’:
user/ls.c:81:4: error: character constant too long for its type [-Werror]
   81 |   I'm so secret that you can't even compile me
      |    ^~~~~~~~~~~~~~~~~~~~~~~~~~
user/ls.c:81:3: error: ‘I’ undeclared (first use in this function)
   81 |   I'm so secret that you can't even compile me
      |   ^
user/ls.c:81:3: note: each undeclared identifier is reported only once for each function it appears in
user/ls.c:81:4: error: expected ‘;’ before '\x2063616e'
   81 |   I'm so secret that you can't even compile me
      |    ^~~~~~~~~~~~~~~~~~~~~~~~~~
      |    ;
user/ls.c:78:7: error: unused variable ‘i’ [-Werror=unused-variable]
   78 |   int i;
      |       ^
cc1: all warnings being treated as errors
make: *** [<builtin>: user/ls.o] Error 1

***ENDE MELDUNG***


Das Problem wird in der Datei ls.c im Ordner user verursacht. In Zeile 81 stellt der Kompiler fest, dass ein unbekannter Befehl auftaucht, da in dieser Zeile nur 

	I'm so secret that you can't even compile me
	
steht. Wenn man diese Zeile löscht, dann lässt sich das Programm wieder ausführen.

Dies haben wur gefunden, indem wir geschaut haben wo im Programmcode "SUPER_SECRET" verwendet wird.



**Code in Userprogrammen finden**

Das Problem wird in der Datei echo.c im Ordner user verursacht. In Zeile 10 beginnt eine if-Abfrage die die Ausgabe von gerade diesem String verhindert. Wird diese gelöscht, funktioniert das Program auch hier wieder. 

Dies haben wir gefunden, indme wir alle Datein mit hilfe der Suchfunktion nach dem Wort "Hello" durchsucht haben und so die if-Abfrage gefunden.



**Code im Kernel finden**

Der Fehler lag in der Datei sysfiles.c in den Zeilen 99 bis 116. Hier wurde abgefragt, ob das Wort "Kassel" eingegeben wurde und wenn dies der
Fall war, das Wort "Kassel" durch "Baunatal" erstetzt. 

Offensichtlich hat der Fehler etwas mit der Datei echo.c zutun. dort wird der Systemcall "write" aufgerufen. Daraufhin haben wir mithilfe der Suchfuktion alle Datein nach dem write durchsucht und und jeweils angeschaut, was dort jeweils passiert. 



**Aufgabe 0.6: Pointer**

Der Befehl

	char array[] = " Keine Panik vor Pointern ! :) ";
	
erstellt ein Char-Array gefüllt mit der Zeichenfolge in den Anführungszeichen. Die Anweisung

	char* ptr = array;
	
erstellt einen Pointer der auf die Adresse des ersten Elementes des Arrays zeigt. Die Schleife läuft solange, Zeichen für Zeichen, durch das Array und gibt jedesmal das aktuelle Zeichen aus, bis die Bedinigung 

	*ptr
	
nicht mehr "true" ist. Dies ist der Fall, solange es kein "\0" trifft, also das Ende des Array. An dieser Stele bricht die Schleife ab und das Programm endet.














