# Report Assignment 02: Smart Waste Disposal System

Membri del gruppo:
- Caberletti Sofia
- Marrelli Marco
- Zanchini Margherita

## Descrizione del Programma

Il programma fornisce un'implementazione di un bidone intelligente per lo smaltimento di rifiuti tossici, simulato con Arduino Uno. Il sistema è composta da vari sensori e attuatori per monitorare e controllare lo stato del bidone. Inoltre, viene fornita una GUI per permettere agli operatori di interagire con il bidone e per monitorarlo.

## Componenti Principali

### Sensori e Attuatori

- **ServoMotor**: Utilizzato per controllare l'apertura e la chiusura del coperchio del bidone.
- **LED**: Indicatori di stato per segnalare condizioni normali o di errore.
- **Button**: Pulsanti per aprire e chiudere manualmente il coperchio del bidone.
- **PIR (Passive Infrared Sensor)**: Sensore di movimento per rilevare la presenza di utenti.
- **Thermistor**: Sensore di temperatura per monitorare la temperatura dei liquidi tossici all'interno.
- **Sonar**: Sensore a ultrasuoni per misurare il livello di riempimento del bidone.

### Task Scheduler

Il programma utilizza un task scheduler per eseguire periodicamente i vari task attraverso il metodo `schedule`. I task sono contenuti in un array `taskList` situato all'interno dello scheduler. I task sono delle classi astratte e il loro comportamento è descritto all'interno del metodo `tick`.
Ogni task è responsabile di una specifica funzionalità del sistema:

- **UserDetectorTask**: Rileva la presenza di utenti tramite il sensore PIR.
- **UserDisplayTask**: Aggiorna il display LCD con messaggi di stato.
- **TemperatureTask**: Monitora la temperatura interna del bidone e gestisce le condizioni di allarme.
- **WasteDetectorTask**: Monitora il livello di riempimento del bidone e gestisce le condizioni di allarme.
- **DoorTask**: Gestisce l'apertura e la chiusura del coperchio del bidone.
- **LedsTask**: Gestisce gli indicatori LED per segnalare lo stato del sistema.

## Funzionamento

### UserDetectorTask

<img src="img/UserDetectorTask.png" alt="UserDetectorTask" width="550"/>

### UserDisplayTask

<img src="img/UserDisplayTask.png" alt="UserDisplayTask" width="550"/>

### TemperatureTask

<img src="img/TemperatureTask.png" alt="TemperatureTask" width="550"/>

### WasteDetectorTask

<img src="img/WasteDetectorTask.png" alt="WasteDetectorTask" width="550"/>

### DoorTask

<img src="img/DoorTask.png" alt="DoorTask" width="550"/>

### LedsTask

<img src="img/LedsTask.png" alt="LedsTask" width="550"/>

## Schema della Breadboard

<img src="img/SmartWasteDisposalSchema.png" alt="Schema della Breadboard" width="750"/>

## Comunicazione

Il sistema utilizza la comunicazione seriale per inviare e ricevere messaggi. La classe [`MsgService`](src/arduino/lib/communication/MsgService.h) gestisce la comunicazione seriale, permettendo al sistema di inviare messaggi di stato e ricevere comandi da un'interfaccia utente esterna.

## Conclusione

Il programma per il bidone intelligente per rifiuti tossici è un sistema complesso che integra vari sensori e attuatori per monitorare e controllare lo stato del bidone. Utilizzando un task scheduler, il sistema esegue periodicamente i task necessari per garantire il corretto funzionamento e la sicurezza del bidone. La comunicazione seriale permette l'interazione con un'interfaccia utente esterna, fornendo un controllo completo del sistema.