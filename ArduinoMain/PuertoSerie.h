#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie {

public:
  // .........................................................
  // .........................................................
  PuertoSerie(long baudios) {
    Serial.begin(baudios);
    // mejor no poner esto aquí: while ( !Serial ) delay(10);
  }  // ()

  // .........................................................
  // .........................................................
  void esperarDisponible() {
/*
    while (!Serial) {
      delay(10);
    }
*/
  }  // ()

  // .........................................................
  // .........................................................
  template<typename T>
  void escribir(T mensaje) {
    Serial.print(mensaje);
  }  // ()

};  // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif