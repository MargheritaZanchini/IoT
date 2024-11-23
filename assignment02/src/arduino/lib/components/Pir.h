#ifndef __PIR__
#define __PIR__

class Pir {
public:
  Pir(int pin); 
  int read(); //funzione che legge il valore del pir
    
private:
  int _pin; 
  
};

#endif
