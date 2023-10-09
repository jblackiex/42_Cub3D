# 42_Cub3d
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever.

//PROGRESSI//

Se vai nel main vedi che ho creato una funzione che fa il check dell'estensione del file della mappa,
che deve essere un file .cub. Nella cartella mappe vedrai alcuni esempi di mappa che ho trovato da un altro progetto git.
Il file della mappa deve contenere esattamente le cose in un determinato ordine come da subject (non ho letto bene se va rispettato un ordine preciso oppure no), quindi dopo
il check dell' estensione del file provvedo a fare un check delle prime 8 linee del file .cub, e lo faccio
all'interno di check_cub. Di conseguenza controllo se esistono i file .xpm etc.. salvandomi le cose che mi servono (ancora da definire questo punto).

Dopo aver controllato le 8 linee iniziali del file .cub, se vai sempre nel main, vedi che entro in check_core ed inizio il controllo della
validita' della mappa (quella vera e propria), dalla linea 8 in poi. Faccio prima un parsing della mappa per levare le prime 8 linee e tenermi solo 
la mappa del gioco e poi mi creo un altra mappa (perche' poi con floodfill vado a sovrascrivere i caratteri della mappa), faccio il char_check per capire se non contiene caratteri sbagliati oltre a quelli consentiti e poi in path_check.

In questa funzione che si trova in check_map_utils vado a prendere una delle 2 mappe che mi sono creato e aumento la sua dimensione
per creare una muraglia di 'L' attorno alla mappa. Questo mi servira' in floodfill per capire se la mappa e' valida oppure no.

In pratica la funzione floodfill parte dall interno della mappa dove si trova il personaggio e inizia a scorrere le caselle: se trova il carattere spazio
da subito errore, altrimenti "colora" la
mappa di 1; ma se trova degli 1 gia posizionati smette di "colorare". Se la mappa non e' circondata da 1 (esempio: c'e' uno 0 sul muro) lui uscira' dallo spazio
giocabile della mappa (guarda in maps/ e capirai meglio come e' fatta la mappa) per entrare in quello sconosciuto

MA quest'ultimo spazio e' a sua volta racchiuso da una muraglia di 'L', visto che prima ho modificato la mappa piazzando questo carattere.
Floodfill, trovato lo 0 sul muro di 1 della mappa, entrando nello spazio sconosciuto, andra' a colorare di 1 anche qualche carattere 'L'.

Se lui colora almeno una 'L' di 1 significa che la mappa non e' racchiusa dai muri e non e' giocabile. Questo lo scopro con un check successivo
a floodfill dove vedo se ho ancora la muraglia di 'L' intatta oppure no.

Il check della mappa dovrebbe essere completo, devo solo testare se fanno alcune di questi controlli, tipo quest'ultimo e implementare cose via via
che scriviamo il resto del codice semmai. Inoltre vedrai tante funzioni inutili per ora che sono quelle
di so_long. Se vuoi rimpiazzale pure con le tua ed inizia a creare le finestre cercando di capire quali funzioni di minilbx ci servono in piu'.

Insomma vedi un po te come procedere che ancora non ne ho idea.

La creazione delle finestre dovrebbe iniziare con una funzione che ho chiamato lessgo(), vedi te se cambiargli il nome ahah. Spero di essere stato piu
o meno chiaro poi ti dico meglio dal vivo! Buon lavoro
