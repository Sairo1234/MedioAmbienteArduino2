#ifndef EMISORA_H_INCLUIDO
#define EMISORA_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
#include "ServicioEnEmisora.h"

// ----------------------------------------------------------
// ----------------------------------------------------------
class EmisoraBLE {
private:

  const char* nombreEmisora;
  const uint16_t fabricanteID;
  const int8_t txPower;

public:

  // .........................................................
  // .........................................................
  using CallbackConexionEstablecida = void(uint16_t connHandle);
  using CallbackConexionTerminada = void(uint16_t connHandle, uint8_t reason);

  // .........................................................
  // .........................................................
  EmisoraBLE(const char* nombreEmisora_, const uint16_t fabricanteID_,
             const int8_t txPower_)
    : nombreEmisora(nombreEmisora_),
      fabricanteID(fabricanteID_),
      txPower(txPower_) {
    // no encender ahora la emisora, tal vez sea por el println()
    // que hace que todo falle si lo llamo en el contructor
    // ( = antes que configuremos Serial )
    // No parece que sea por el println,
    // por tanto NO_encenderEmisora();
  }  // ()

  // .........................................................
  // .........................................................
  void encenderEmisora() {
    
    Bluefruit.begin();

    // por si acaso:
    (*this).detenerAnuncio();
  }  // ()

  // .........................................................
  // .........................................................
  void encenderEmisora(CallbackConexionEstablecida cbce,
                       CallbackConexionTerminada cbct) {

    encenderEmisora();

    instalarCallbackConexionEstablecida(cbce);
    instalarCallbackConexionTerminada(cbct);

  }  // ()

  // .........................................................
  // .........................................................
  void detenerAnuncio() {

    if ((*this).estaAnunciando()) {
      // Serial.println ( "Bluefruit.Advertising.stop() " );
      Bluefruit.Advertising.stop();
    }

  }  // ()

  // .........................................................
  // estaAnunciando() -> Boleano
  // .........................................................
  bool estaAnunciando() {
    return Bluefruit.Advertising.isRunning();
  }  // ()

  // .........................................................
  // .........................................................
  void emitirAnuncioIBeacon(uint8_t* beaconUUID, int16_t major, int16_t minor, uint8_t rssi) {

    //
    //
    //
    (*this).detenerAnuncio();

    //
    // creo el beacon
    //
    BLEBeacon elBeacon(beaconUUID, major, minor, rssi);
    elBeacon.setManufacturer((*this).fabricanteID);

    //
    // parece que esto debe ponerse todo aquí
    //

    Bluefruit.setTxPower((*this).txPower);
    Bluefruit.setName((*this).nombreEmisora);
    Bluefruit.ScanResponse.addName();  // para que envíe el nombre de emisora (?!)

    //
    // pongo el beacon
    //
    Bluefruit.Advertising.setBeacon(elBeacon);

    //
    // ? qué valorers poner aquí
    //
    Bluefruit.Advertising.restartOnDisconnect(true);  // no hace falta, pero lo pongo
    Bluefruit.Advertising.setInterval(100, 100);      // in unit of 0.625 ms

    //
    // empieza el anuncio, 0 = tiempo indefinido (ya lo pararán)
    //
    Bluefruit.Advertising.start(0);

  }  // ()


  // .........................................................
  // .........................................................
  bool anyadirServicio(ServicioEnEmisora& servicio) {

    Globales::elPuerto.escribir(" Bluefruit.Advertising.addService( servicio ); \n");

    bool r = Bluefruit.Advertising.addService(servicio);

    if (!r) {
      Serial.println(" SERVICION NO AÑADIDO \n");
    }


    return r;
    // nota: uso conversión de tipo de servicio (ServicioEnEmisora) a BLEService
    // para addService()
  }  // ()


  // .........................................................
  // .........................................................
  bool anyadirServicioConSusCaracteristicas(ServicioEnEmisora& servicio) {
    return (*this).anyadirServicio(servicio);
  }  //

  // .........................................................
  template<typename... T>
  bool anyadirServicioConSusCaracteristicas(ServicioEnEmisora& servicio,
                                            ServicioEnEmisora::Caracteristica& caracteristica,
                                            T&... restoCaracteristicas) {

    servicio.anyadirCaracteristica(caracteristica);

    return anyadirServicioConSusCaracteristicas(servicio, restoCaracteristicas...);

  }  // ()

  // .........................................................
  template<typename... T>
  bool anyadirServicioConSusCaracteristicasYActivar(ServicioEnEmisora& servicio,
                                                    // ServicioEnEmisora::Caracteristica & caracteristica,
                                                    T&... restoCaracteristicas) {

    bool r = anyadirServicioConSusCaracteristicas(servicio, restoCaracteristicas...);

    servicio.activarServicio();

    return r;

  }  // ()

  // .........................................................
  // .........................................................
  void instalarCallbackConexionEstablecida(CallbackConexionEstablecida cb) {
    Bluefruit.Periph.setConnectCallback(cb);
  }  // ()

  // .........................................................
  // .........................................................
  void instalarCallbackConexionTerminada(CallbackConexionTerminada cb) {
    Bluefruit.Periph.setDisconnectCallback(cb);
  }  // ()

  // .........................................................
  // .........................................................
  BLEConnection* getConexion(uint16_t connHandle) {
    return Bluefruit.Connection(connHandle);
  }  // ()

};  // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------