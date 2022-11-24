
#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID[16] = {
    'C', 'O', 'M', 'M', 'U', 'N', '-', 'O',
    '3', '-', 'G', 'T', 'I', '-', '3', 'A'
  };

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora{
    "COMMUNO3-GTI",  //  nombre emisora
    0x004c,          // fabricanteID (Apple)
    4                // txPower
  };

  const int RSSI = -53;  // por poner algo de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID {
    O3 = 11,
    TEMPERATURA = 12,
  };

  // ............................................................
  // ............................................................
  Publicador() {
    // ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
    // Pondremos un método para llamarlo desde el setup() más tarde
  }  // ()

  // ............................................................
  // ............................................................
  void encenderEmisora() {
    (*this).laEmisora.encenderEmisora();
  }  // ()

  // ............................................................
  // ............................................................
  void publicarO3(float valorO3, 
                   long tiempoEspera) {

    //
    // 1. empezamos anuncio
    //
    uint16_t major = (MedicionesID::O3 ) ;
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID,
                                           major,
                                           valorO3,     // minor
                                           (*this).RSSI  // rssi
    );

        
	      Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	      Globales::elPuerto.escribir( valorO3);
	      Globales::elPuerto.escribir( "   todo="  );
	      Globales::elPuerto.escribir( major );
	      Globales::elPuerto.escribir( "\n" );
	      

    //
    // 2. esperamos el tiempo que nos digan
    //
    esperar(tiempoEspera);

    //
    // 3. paramos anuncio
    //
    (*this).laEmisora.detenerAnuncio();
  }  // ()

  // ............................................................
  // ............................................................
  void publicarTemperatura(float valorTemperatura,
                            long tiempoEspera) {

    uint16_t major = (MedicionesID::TEMPERATURA);
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID,
                                           major,
                                           valorTemperatura,  // minor
                                           (*this).RSSI       // rssi
                                           
    );
        Globales::elPuerto.escribir( "   publicarTemperatura(): valor= " );
	      Globales::elPuerto.escribir( valorTemperatura);
	      Globales::elPuerto.escribir( " todo="  );
	      Globales::elPuerto.escribir( major );
	      Globales::elPuerto.escribir( "\n" );
	      
    esperar(tiempoEspera);

    (*this).laEmisora.detenerAnuncio();
  }  // ()

};   // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif