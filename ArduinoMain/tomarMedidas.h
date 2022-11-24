
//datasheet de calibracion: http://www.kwjengineering.com/wp-content/uploads/2014/07/Technical-Document-ULPSM-CO.pdf

//conexiones

int Vgas=A5;
int Vref=A4;
int Vtemp=A3;
int Vflo=A6;
//valores
float Vgas_value = 0;
float Vref_value = 0;
float Vtemp_value = 0;
float Vflo_value = 0; 
float Voffset=0;
float Vgas0=0;


float calibracionDelSensor= 42.31;


void tomarVoltajes(){
  float VgasAcumulado=0;
  float VtempAcumulado=0;
  float VrefAcumulado=0;
  //hacemos las 100 mediciones para eliminar errores una cada 50 ms 
  for (int i=0;i<100;i++){
    VgasAcumulado=VgasAcumulado + (analogRead(Vgas)*3.3/4096);
    VtempAcumulado=VtempAcumulado + (analogRead(Vtemp)*3.3/4096);
    VrefAcumulado=VrefAcumulado + (analogRead(Vref)*3.3/4096);
    delay(50);
  }
 

  Vgas_value=VgasAcumulado/100;
  Vtemp_value=VtempAcumulado/100;
  Vref_value=VrefAcumulado/100;

  Vgas0 = Vref_value+Voffset;
  Globales::elPuerto.escribir( " voltajes tomados\n" );
}

float obtenerTemperatura(){
  return (29*Vtemp_value)-18;
}

float obtenerO3(){
  
  /*
  //Prueba de calibracion segun datasheet anterior

  float calibracionDelSensorConTemperatura;
  float T=obtenerTemperatura();
  if(T<=20){
    calibracionDelSensorConTemperatura = calibracionDelSensor * (1.3*T+74);
  }else{
    calibracionDelSensorConTemperatura = calibracionDelSensor * (0.4*T+92);
  }
  return (Vgas_value-Vgas0)/calibracionDelSensorConTemperatura;
  */

return (Vgas_value-Vgas0)/calibracionDelSensor;

}

