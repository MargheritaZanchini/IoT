# Assignment 03 - Smart Temperature Monitoring
- Caberletti Sofia 0001071417
- Marrelli Marco
- Margherita Zanchini

## Descrizione del Sistema
Il sistema di monitoraggio della temperatura è composto da quattro sottosistemi principali: il sottosistema di monitoraggio della temperatura, il sottosistema di controllo, il sottosistema di controllo della finestra e il sottosistema dashboard. Il sistema è progettato per monitorare la temperatura di un ambiente chiuso e controllare l'apertura della finestra in base alla temperatura rilevata. Il sistema può operare in due modalità: AUTOMATICO e MANUALE. In modalità AUTOMATICO, il sistema decide automaticamente quanto aprire la finestra in base alla temperatura corrente. In modalità MANUALE, l'apertura è controllata manualmente da un operatore. La modalità iniziale all'avvio è AUTOMATICO.

## Control Unit Subsystem
Il sottosistema di controllo è il principale sottosistema che governa e coordina l'intero sistema. Interagisce tramite MQTT con il sottosistema di monitoraggio della temperatura, tramite linea seriale con il sottosistema di controllo della finestra e tramite HTTP con il sottosistema dashboard. Questo sottosistema tiene traccia delle ultime N misurazioni della temperatura, dei valori medi/minimi/massimi della temperatura per periodo (ad esempio, giornaliero) e decide l'apertura della finestra in modalità AUTOMATICO in base alla temperatura corrente.

## Temperature Monitoring Subsystem
Il sottosistema di monitoraggio della temperatura è responsabile del monitoraggio continuo della temperatura dell'ambiente chiuso tramite un sensore di temperatura. Il valore della temperatura viene campionato e inviato al sottosistema di controllo con una certa frequenza F, che dipende dallo stato del sistema e viene stabilita dal sottosistema di controllo. Quando il sistema funziona correttamente (rete ok, invio dati ok), il LED verde è acceso e il LED rosso è spento; in caso di problemi di rete, il LED rosso è acceso e il LED verde è spento.

## Window Controller Subsystem
Il sottosistema di controllo della finestra è responsabile del controllo del motore che apre la finestra, da 0% (finestra chiusa) a 100% (finestra completamente aperta). Il livello di apertura della finestra dipende dallo stato del sistema, stabilito dal sottosistema di controllo. Il sottosistema di controllo della finestra fornisce anche un pulsante per abilitare la modalità MANUALE, in cui il livello di apertura della finestra può essere controllato manualmente dagli operatori tramite un potenziometro. Il sottosistema è dotato di un display LCD che riporta il livello di apertura della finestra, la modalità corrente (AUTOMATICO o MANUALE) e il valore della temperatura corrente in modalità MANUALE.

## Dashboard Subsystem
Il sottosistema dashboard ha due funzionalità principali: visualizzare lo stato del sistema di monitoraggio della temperatura e consentire agli operatori di interagire con il sistema. La dashboard visualizza un grafico della temperatura considerando le ultime N misurazioni, i valori medi/massimi/minimi correnti, lo stato del sistema (NORMALE, CALDO, TROPPO CALDO, ALLARME) e il livello di apertura della finestra (percentuale). Inoltre, permette di entrare in modalità MANUALE e controllare l'apertura della finestra tramite un controller GUI specifico e di gestire lo stato di ALLARME premendo un pulsante per notificare che il problema è stato risolto, riportando il sistema allo stato NORMALE.