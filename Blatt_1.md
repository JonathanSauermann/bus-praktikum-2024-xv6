Aufgabe 1.1:
a)
Theo de Raadt hat geschrieben, dass der direkte Aufruf vom syscall #0 verhindert werden sollte um damit die Sicherheit des Systems zu verbessern, da es so schwieriger wird schädlichen Code auszuführen. Das verringert die Angriffsmöglichkeiten.

b)
Nach dem Patch gibt es in der kernel/syscall.h einen neuen Systemaufruf:

	#define SYS_strace 22

Der Kernel kann jetzt das strace-Kommando ausführen und dadurch das Tracken von nachfolgenden Systemaufrufen ermöglichen

c)
Durch "strace command" werden die Systemaufrufe die nach dem Kommando kommen protokolliert und angezeigt.

$ strace echo Hallo
>strace used syscall exec				Load a file and execute it with arguments; only returns if error.
Hallo
>echo used syscall write 2x times		Write n bytes from buf to file descriptor fd; returns n.
>echo used syscall exit					Terminate the current process; status reported to wait(). No return.


$ strace ls
>strace used syscall exec				
>ls used syscall open					Open a file; flags indicate read/write; returns an fd (file descriptor).
>ls used syscall fstat					Place info about an open file into *st.
>ls used syscall read					Read n bytes into buf; returns number read; or 0 if end of file.
>ls used syscall open					Open a file; flags indicate read/write; returns an fd (file descriptor).
>ls used syscall fstat
>ls used syscall close					Release open file fd.
.              1 1 1024
>ls used syscall write 24x times		
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
..             1 1 1024
>ls used syscall write 24x times
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
README         2 2 2292
>ls used syscall write 24x times
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
>ls used syscall exit
$

Es werden alle Aufrufe protokolliert und deren Anzahl angegeben.

d)
$ strace enable
>strace used syscall exit
$ >sh used syscall write 1x times
>sh used syscall read
echo Hallo
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall fork
>sh used syscall wait
>sh used syscall sbrk
>sh used syscall exec
Hallo
>echo used syscall write 2x times
>echo used syscall exit
$ >sh used syscall write 1x times
>sh used syscall read


ls
>sh used syscall read
>sh used syscall read
>sh used syscall fork
>sh used syscall wait
>sh used syscall sbrk
>sh used syscall exec
>ls used syscall open
>ls used syscall fstat
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
.              1 1 1024
>ls used syscall write 24x times
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
..             1 1 1024
>ls used syscall write 24x times
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
README         2 2 2292
>ls used syscall write 24x times
>ls used syscall read
>ls used syscall open
>ls used syscall fstat
>ls used syscall close
>ls used syscall exit
$ >sh used syscall write 1x times
>sh used syscall read
strace disable
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall read
>sh used syscall fork
>sh used syscall wait
>sh used syscall sbrk
>sh used syscall exec
>strace used syscall strace

Der Unterschied ist, dass die Auflistung anders ist. Dies liegt daran, dass wenn man strace direkt auf einen Command ausführt werden nur die Syscalls ausgegeben welche von dem Command ausgeführ werden. Wenn man strace enable eingibt, werden alles Syscalls des Systems ausgegeben.


Aufgabe 1.2:
b)
$ ./hello
Hello xv6!
$ strace hello
>strace used syscall exec
Hello xv6!
>hello used syscall write 11x times
>hello used syscall exit


Aufgerufen werden "exec", "write" und "exit".

Das exec-Kommando ist nicht im Code zu finden, da das OS diesen Befehl beim Laden und dem Starten des Programms ausführt.

Das write-Kommando wird von der printf-Funktion ausgeführt um den String "Hello xv6!" im Terminal darzustellen.

Des exit(0)-Kommando wird als Ende des Programms ausgeführt, da damit der Prozess von hello.c, mit dem Exit-Status 0, vom OS beendet wird.

c)
In xv6 ist libc eine Menge an Funktionen die die Systemaufrufe des Kernels starten können. Dadurch können Anwendungen mit der Hardware und den OS-Serciven arbeiten, also mit dem Kernel interagieren. Die Systemaufrufe sind z. B. in kernel/syscall.h und kernel/syscall.c und können dann über libc-Funktionen ausgelöst werden. So würde ein fork()-Kommando den Syscall SYS_fork aufrufen, um einen neuen Prozess zu erzeugen, während "exit()" den Syscall SYS_exit aufruft um damit einen Prozess zu beenden.

Wir brauchen die stdio.h nicht, da deren Funktionen bereits durch die verwendete ulib.c abgedeckt sind. So wird "printf()" z.B. durch den write()-Syscall ausgeführt der das Schreiben auf das Terminal ermöglicht.

In user/user.h sind alle Userland-Aufrufe und einige Hilfsfunktionen definiert. Die eben genannten Befehle fork(), exit() und write() liegen z.B. dort, aber auch Funktionen wie das neue strace() sind dort eingetragen, da diese vom User aufgerufen werden. 

Im makefile ist "ULIB = $U/ulib.o $U/usys.o $U/printf.o $U/umalloc.o" zu finden. Dieser Befehl kombiert die in diesen Dateien vorhandenen Befehle in die Variable ULIB und ermöglich so sehr leichten Zugriff auf diese Befehle.

d)
In der Datei werden die Datentypen für unsigned-Integer von verschiedenen Längen definiert. Gerade für Speichermanagement und Registerzugriffe sind die definierten Längen besonders wichtig, da diese sonst nicht funktionieren würden oder jedes einzelne Mal im Code vor deren Verwendung neu definiert werden müssten. Dies wäre nicht mit gutem Code vereinbar.

Diese Datei existiert um die darin definierten Datentypen allen einbindenden Programmen zentral zugänglich zu machen. Die dient der Lesbarkeit, der Portabilität, der Fehlervermeidung und dem Speichermanagement.


Aufgabe 1.4:
a) 
Der Bootvorgang hat folgenden Ablauf:

1. Wird der PC gestartet führt er selbst den im ROM gespeicherten Bootloader aus. Dieser lädt den Kernel in den Speicher.

2. Der Prozessor führt den Kernels ab der Adresse _entry aus.

3. Der Bootloader lädt den Kernel an die physische Adresse 0x80000000.

4. Die Befehle im _entry-Abschnitt richten den Stack ein.

5. Danach wird in C der start-Befehl aufgerufen, der Dinge einrichtet die die nur im machine mode möglich sind. So z.B., dass der Programmzähler nach dem Wechsel zum Supervisor-Modus auf main zeigt und der Timerchip wird so eingstellt, dass Timer-Interrupts erzeugt werden können.

6. Nach dem Befehl mret wechselt das OS zum Supervisor-Modus und mehrere Prozesse werden in diesen Modus umgeleitet.

7. Die main-Funktion initialisiert mehrere Geräte und Systeme, wie Services und Prozessverwaltung. Danach wird der erste Prozess durch userinit gestartet.

8. Der erste Syscall wird durch das Programm initcode.S aufgerufen und lädt das Programm /init.
    
9. Anschließend wird zum Benutzermodus gewechselt. Der init-Prozess erstellt und öffnet die erste Shell.

Ab hier kann der User das System nutzen.

b)
Der erste Prozess ist init. Dessen Aufgabe ist es das System zu initialisieren und die Systemumgebung für den User vorzubereiten. Er erstellt und startet die erste Shell.

c)
Um statt der Shell das "Hello World"-Programm zu starten, muss in Zeile 34 die Startsequenz in init.c zu "exec("/bin/hello", argv);" geändert werden. Das "Hello World"-Programm muss dazu in die Liste von UPROGS in der Makefile hinzugefügt werden.