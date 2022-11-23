// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

  // .....................................................
  // .....................................................
private:

public:

  //Valor usado para mandar un dato inventado para el sprint 0, eliminar más tarde
  int medicion = 0;

  // .....................................................
  // constructor
  // .....................................................
  Medidor() {
  }  // ()

  // .....................................................
  // .....................................................
  void iniciarMedidor() {
    // las cosas que no se puedan hacer en el constructor, if any

    //Valor de prueba para mandarlo como minor en los beacons
    //Solo para el sprint 0, borrar más tarde
    int minorPrueba = 0;
  }  // ()

  // .....................................................
  // .....................................................
  int medirCO2() {
    return 235;
  }  // ()

  // .....................................................
  // .....................................................
  int medirTemperatura() {
    return -12;  // qué frío !
  }              // ()

  /*
  * Metodo para el sprint individual
  * para probar que cambie mayor y minor al mandar los beacons
  * Eliminar más tarde
  */
  int medirPrueba() {

    if (medicion >= 100) {
      medicion = 1; //resetea el valor a 1 despues de llegar a 100

    } else {
      medicion++; //si no el valor va aumentando de 1 en 1
    }

    return medicion; //devuelvo el valor
  }
};  // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif