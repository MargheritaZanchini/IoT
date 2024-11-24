#include "UserDetectorTask.h"
#include "Arduino.h"
#include "avr/sleep.h"
#include "avr/power.h"

//Il pir viene creato nel main e poi passato al costruttore
UserDetectorTask::UserDetectorTask(PIR& pir) {
    _pir = &pir;
}

void UserDetectorTask::init(int period){
    Task::init(period);
    _state = NOT_DETECTED; //inizialmente non c'è nessuno user
    _lastDetectedTime = 0; //per calcolare il tempo in cui nessun user è rilevato   
    _deltaTime = 5000; //tempo dopo il quale nessun user è rilevato e il sistema va in sleep
}

void UserDetectorTask::tick(){
    switch (_state){
    case NOT_DETECTED:
        _userDetected = _pir->read();
        if(_userDetected == HIGH){ //se rileva un utente cambia stato
            _lastDetectedTime = 0;
            _state = DETECTED; 
        }else{  //se nessun utente viene rilevato si controlla da quanto tempo siamo nello stato NOT_DETECTED
            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime >_deltaTime){
                    _state = SLEEP;
            }
        }

        break;
    
    case DETECTED:
        _userDetected = _pir->read();
        if(_userDetected == LOW){
            _state = NOT_DETECTED; 
        }
        break;
    
    case SLEEP:
        /*set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();*/

        /* Disable all of the unused peripherals. This will reduce power
        * consumption further and, more importantly, some of these
        * peripherals may generate interrupts that will wake our Arduino from
        * sleep!
        */
        /*power_adc_disable();
        power_spi_disable();
        power_twi_disable();  
        /* Now enter sleep mode. */
       // sleep_mode();  
        /* The program will continue from here after the timer timeout*/
        //sleep_disable(); /* First thing to do is disable sleep. */
        /* Re-enable the peripherals. */
        //power_all_enable();
        break;
    }
}