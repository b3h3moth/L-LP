# Advanced Input / Output

* [Manipulate file descriptor; fcntl()](#headIOA0)
* [Read from or write to a file descriptor at a given offset; pread(), pwrite()](#headIOA1)
* [Scatter/Gather I/O (or Vectored I/O); readv(), writev()](#headIOA2)
* [File Descriptor duplication; dup(), dup2(), dup3()](#headIOA3)
* [Set the size of a file: truncate(), ftruncate()](#headIOA4)
* [Working with temporary files; tmpfile(), mkstemp(), tmpnam(), tempnam()](#headIOA5)

---

## <a name="headIOA0"></a>Manipulate file descriptor; fcntl()

__```int fcntl(int fd, int cmd, ... < arg > );```__

La funzione `fcntl()` e' una sorta di punto di accesso per l'esecuzione di 
diverse operazioni sul file descriptor. Il primo argomento `fd'` e' un file
descriptor aperto, il secondo argomento `cmd` indica il tipo di operazione da
eseguire, il terzo argomento `arg` e' opzionale, se utilizzarlo o meno e' 
determinato da `cmd'`. I valori di ritorno sono diversi a seconda dell'
operazione eseguita, in caso di errore ritorna sempre `-1`.

La funzione `fcntl()` puo' modificare le proprieta' di un file descriptor, 
tuttavia il numero degli argomenti, il valore di ritorno, errori compresi, 
sono strettamente legati al valore della variabile intera `cmd`, che puo' 
assumere i seguenti valori:

* `F_DUPFD`, duplica il file descriptor;
* `F_GETFD`, ritorna il valore del file descriptor flag;
* `F_SETFD`, setta il valore del file descpritor flag;
* `F_GETFL`, ritorna il valore del file status flag;
* `F_SETFL`, setta il valore del file status flag;
* `F_GETLK`, ritorna informazioni sul record locking;
* `F_SETLK`, setta informazioni sul record locking;
* `F_SETLKW`, come sopra, non ritorna subito ma attende il rilascio del blocco;
* `F_GETOWN`, ritorna il PID o il PGID, preposto alla ricezione dei segnali SIGURS;
* `F_SETOWN`, setta il PID o il PGID, preposto alla ricezione dei segnali SIGURS;
* `F_GETSIG`, ritorna il segnale inviato quando l'input o l'output e' disponibile;
* `F_SETSIG`, setta il segnale inviato quando l'input o l'output e' disponibile;
* `F_SETLEASE`, imposta o rimuove un file lease; 
* `F_GETLEASE`, setta un file lease;
* `F_NOTIFY`, attiva un meccanismo di notifica.

Una delle operazioni piu' importanti realizzabili con e' il blocco in lettura o
in scrittura di un file descriptor, così come la duplicazione del file 
descriptor.

## <a name="headIOA1"></a>Read from or write to a file descriptor at a given offset; pread(), pwrite()

Le system call `pread()` e `pwrite()` combinano gli effetti di una chiamata a
`lseek()`, `read()` - o `write()` - in una singola system call, tutto cio'
fornisce un miglioramento nelle performance.

__```ssize_t pread(int fd, void *buf, size_t count, off_t offset);```__

La funzione `pread()` legge `count` byte dal file descriptor `fd` all'offset 
`offset` (dall'inizio del file) nel buffer a partire da `buf`.

__```ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);```__

La funzione `pwrite()` scrive `count` byte dal buffer a partire da `buf` nel 
file descriptor `fd` all'offset `offset`.

In entrambi i casi l'offset del file non viene modificato. In caso di successo 
ritornano il numero di byte letti o scritti. `0` indica che nessun byte e' stato
scritto dalla `pwrite()`, mentre `EOF` che la `pread()` ha raggiunto la fine del
file. In caso di errore ciascuna di esse ritorna `-1`.

> **Nota**: Non sono standard C, per cui e' necessario informare il compilatore
di aggiungere delle funzioni extra POSIX per far si che non vengano inviati
messaggi di warning in fase di compilazione.

La compilazione sara' la seguente:
    
```$ gcc -Wall -pedantic -std=c11 -D_XOPEN_SOURCE=500 file.c```


## <a name="headIOA2"></a>Scatter/Gather I/O (or Vectored I/O); readv(), writev()

Lo **scatter-gather I/O** e' un metodo di input output per gestire con una
singola system call la lettura e la scrittura di buffer mulipli non contigui
da un unico stream.

Le system call deputate a tale scopo sono `readv()` per la lettura e `writev()` 
per la scrittura.

__```ssize_t readv(int fd, const struct iovec *iov, int iovcnt);```__

La funzione `readv()` legge i buffer `iovcnt` dal file associato al file 
descriptor `fd` nei buffer descritti da `iov` (__scatter input__).

__```ssize_t writev(int fd, const struct iovec *iov, int iovcnt);```__

La funzione `writev()` scrive i buffer `iovcnt` descritti da `iov` nel file 
associato al file descriptor `fd` (__gather output__).

In caso di successo la funzione readv() restituisce il numero di byte letti, 
mentre la funzione writev() il numero di byte scritti. In caso di errore 
entrambe restituiscono -1.

`iov` e' un puntatore alla struttura `iovec` definita in `sys/uio.h`:
```
struct iovec {
  void   *iov_base;   // Indirizzo di partenza
  size_t *iov_len;    // Numero di byte da trasfeerire
}
```

> I trafserimenti eseguiti da entrambe le system call sono atomici.


## <a name="headIOA3"></a>File Descriptor duplication; dup(), dup2(), dup3()

La duplicazione di un file descriptor puo' essere gestita in maniera ottimale
da diverse system call.

__```int dup(int oldfd);```__

La funzione `dup` crea una copia del file descriptor `oldfd`, attribuendogli 
un intero prelevato da un range di numeri bassi non utilizzati da nessun 
descrittore. La copia e il vecchio file descriptor condividono sia l'`offset` 
sia i `file status flags` ma non i `file descriptor flags`. Ritorna il nuovo 
file descriptor in caso di successo, altrimenti -1 in caso di errore.

__```int dup2(int oldfd, int newfd);```__

La funzione `dup2()` crea una copia del file descriptor `oldfd` in `newfd`. 
Ritorna il nuovo file descriptor oppure -1 in caso di errore.

__```int dup3(int oldfd, int newfd, int flags);```__

La funzione `dup3()` si comporta come `dup2()`, ad eccezione del fatto che il
chiamante puo' forzare il flag `close-on-exec` sul nuovo file descriptor 
settando il parametro `flags` su `O_CLOEXEC`. Inoltre se `oldfd` e' uguale a
`newfd` fallisce con l'errore `EINVAL`. Ritorna il nuovo file descriptor oppure
-1 in caso di errore.


## <a name="headIOA4"></a>Set the size of a file: truncate(), ftruncate()

__```int truncate(const char *path, off_t length);```__

La funzione `truncate()` setta la grandezza del file `path` al valore 
impostato in `length`. Ritorna zero in caso di successo, altrimenti -1 in caso 
di errore.

__```int ftruncate(int fd, off_t length);```__

La differenza sostanziale rispetto alla funzione `truncate()` riguarda 
l'uso del file descriptor come parametro per individuare un file aperto.


## <a name="headIOA5"></a>Working with temporary files;  tmpfile(), mkstemp(), tmpnam(), tempnam()

> **Security**: Le funzioni per la creazione di file temporanei sono `tmpfile()`
>, mkstemp()`, `tmpnam()` e `tempnam()`, tuttavia le uniche che si consiglia di
> utilizzare sono `mkstemp()` e `tmpfile()` poiche' le altre due possono causare
> falle nella sicurezza dell'applicazione.

__```int mkstemp(char *template);```__

La funzione `mkstemp()` crea un file temporaneo unico dalla stringa `template`.
L'argomento `template` e' utilizzato come modello per il percorso temporaneo, 
gli ultimi 6 caratteri devono essere necessariamente composti dalla
stringa **XXXXXX**, dopodiche' saranno sovrascritti affinche' il percorso 
risulti unico. Il file creato avra' permessi di lettura e scrittura per l'
`owner` e nessun permesso per gli altri utenti, inoltre il parametro `flag` 
sara' impostato a `O_EXCL`, garantendo in tal modo al chiamante l'accesso 
esclusivo al file. Ritorna il file descriptor del file temporaneo in caso di 
successo, `-1` in caso di errore

__```FILE *tmpfile(void);```__

La funzione `tmpfile()` apre un file temporaneo unico, binario in lettura e 
scrittura. La sua peculiarita' e' che il file temporaneo sara' automaticamente
eliminato alla chiusura del programma. Ritorna lo stream relativo al file in 
caso di successo, `NULL` in caso di errore.

__```char *tmpnam(char *str);```__

La funzione `tmpnam()` ritorna il puntatore ad una stringa, che dev'essere un 
filename valido e non esistente al momento della creazione. Ritorna il 
puntatore al file temporaneo in caso di successo, NULL in caso di esito 
negativo. Non sono definiti errori.

__```char *tempnam(const char *dir, const char *pfx);```__

La funzione `tempnam()` ritorna il puntatore ad una stringa unica indicante il
file temporaneo in caso di successo, `NULL` in caso di errore.

