
//conexiones

int Vgas=A3;
int Vref=A4;
int Vtemp=A5;
int Vflo=A6;
//valores
float Vgas_value = 0;
float Vref_value = 0;
float Vtemp_value = 0;
float Vflo_value = 0; 
float Voffset=0;
float Vgas0=0;

//cada sensor tiene un valor por defecto para calibrar esto es solo para pruebas ya que realmente se calibra en el movil
float calibracionDelSensor= 48.31;

//-------------------------------------------
//tomamos voltajes
//-------------------------------------------

void tomarVoltajes(){
  float VgasAcumulado=0;
  float VtempAcumulado=0;
  float VrefAcumulado=0;

  //hacemos las 1000 mediciones para eliminar errores una cada 50 ms 
  for (int i=0;i<1000;i++){
    /*
    //O3
    VgasAcumulado=VgasAcumulado + (analogRead(Vgas)*3.3/4096);
    VrefAcumulado=VrefAcumulado + (analogRead(Vref)*3.3/4096);
//Temperatura
    VtempAcumulado=VtempAcumulado + (analogRead(Vtemp)*3.3/4096);

    Serial.println(VrefAcumulado/(i+1),9);
    */
    VgasAcumulado=VgasAcumulado + analogRead(Vgas);
    VtempAcumulado=VtempAcumulado + analogRead(Vtemp);
    VrefAcumulado=VrefAcumulado + analogRead(Vref);
    delay(50);
  }

  Vgas_value=VgasAcumulado/100;
  Vtemp_value=VtempAcumulado/100;
  Vref_value=VrefAcumulado/100;
  
  //Globales::elPuerto.escribir( " voltajes tomados\n" );
}
//-------------------------------------------
//mostramos en el seria para ver si los valores corresponden
//-------------------------------------------

void mostrarParaCalibrar(){
  float Vgas_Real=Vgas_value*3.3/4096;
  float Vref_Real=Vref_value*3.3/4096;


  float Vsensor=(Vgas_Real-Vref_Real);
  float calibracion=calibracionDelSensor*499*pow(10,-6);
  float ConcentracionDeGas=Vsensor/calibracion;

 Serial.print(Vgas_Real,6);
 Serial.print(",");
 Serial.print(Vref_Real,6);
 Serial.print(",");
 Serial.println(ConcentracionDeGas,6);
}
//-------------------------------------------
//obtenemos el voltaje de VTEMP
//->obtenerTemperatura()->float
//-------------------------------------------


float obtenerTemperatura(){
  /*
  Prueba para mandar dato calibrado
  return (29*Vtemp_value)-18;
  */
  return Vtemp_value;
}

//-------------------------------------------
//obtenemos el voltaje guardado de Vgas y Vref y calculamos el valor en bruto
//->obtenerO3()->float

//-------------------------------------------


float obtenerO3(){
  
  /*
  //Prueba de calibracion segun datasheet anterior para mandar dato calibrado

  float calibracionDelSensorConTemperatura;
  float T=obtenerTemperatura();
  if(T<=20){
    calibracionDelSensorConTemperatura = calibracionDelSensor * (1.3*T+74);
  }else{
    calibracionDelSensorConTemperatura = calibracionDelSensor * (0.4*T+92);
  }
  return (Vgas_value-Vgas0)/(calibracionDelSensorConTemperatura*pow(10,-6)*499);
  */



return Vgas_value-Vref_value;


}

