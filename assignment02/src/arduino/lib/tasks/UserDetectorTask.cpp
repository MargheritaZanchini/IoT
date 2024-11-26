#include "UserDetectorTask.h"
#include <Arduino.h>
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
    _deltaTime = 6000; //tempo dopo il quale nessun user è rilevato e il sistema va in sleep
}

void UserDetectorTask::tick(){
    switch (_state){
    case NOT_DETECTED:
        Serial.println("Sono in NOT_DETECTED");
        _userDetected = _pir->isUserDetected();
        if(_userDetected){ //se rileva un utente cambia stato
            _state = DETECTED; 
        }else{  //se nessun utente viene rilevato si controlla da quanto tempo siamo nello stato NOT_DETECTED
            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime > _deltaTime){
                _state = SLEEP;
            }
        }

        break;
    
    case DETECTED:
        Serial.println("Sono in DETECTED");
        _userDetected = _pir->isUserDetected();
        _lastDetectedTime = 0;
        if(!_userDetected){
            _state = NOT_DETECTED; 
        }
        break;
    
    case SLEEP:
        Serial.println("Sono in SLEEP");
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();

        power_adc_disable();
        power_spi_disable();
        power_timer0_disable();
        power_timer1_disable();
        power_timer2_disable();
        power_twi_disable();  
        /* Now enter sleep mode. */
        sleep_mode();  
        /* The program will continue from here after the timer timeout*/
        sleep_disable(); /* First thing to do is disable sleep. */
        /* Re-enable the peripherals. */
        power_all_enable();

        _lastDetectedTime = 0;
        _state = DETECTED;
        break;
    }
}