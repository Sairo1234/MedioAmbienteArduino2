#include <bluefruit.h>

#undef min  // vaya tela, están definidos en bluefruit.h y  !
#undef max  // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"

#include "PuertoSerie.h"
// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

LED elLED(7);
PuertoSerie elPuerto(115200);
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "tomarMedidas.h"
#include "Publicador.h"
#include "Medidor.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

Publicador elPublicador;

Medidor elMedidor;

};  // namespace





// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  Globales::elPublicador.encenderEmisora();

  Globales::elMedidor.iniciarMedidor();

  esperar(1000);

  //Globales::elPuerto.escribir("---- setup(): fin ---- \n ");

}  // setup ()

// --------------------------------------------------------------
// loop ()
// ----------------------------------------------------------
void loop() {

using namespace Globales;
  tomarVoltajes();
  //Para calibrar
  mostrarParaCalibrar();

  //
  // mido y publico
  //
  float valorTemperatura = elMedidor.medirTemperatura();

  elPublicador.publicarTemperatura(valorTemperatura,                                  
                                   500  // intervalo de emisión
  );
  elPublicador.laEmisora.detenerAnuncio();

  esperar(500);
  
  //
  // mido y publico
  //

float valorO3 = elMedidor.medirO3();
if(valorO3>0){
  elPublicador.publicarO3(valorO3,                          
                           1000  // intervalo de emisión
  );

  elPublicador.laEmisora.detenerAnuncio();
  esperar(1000);
 
}
  
}  // loop ()
   // --------------------------------------------------------------
   // --------------------------------------------------------------
   // --------------------------------------------------------------
   // --------------------------------------------------------------