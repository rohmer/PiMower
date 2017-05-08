void contadorT()
{
//medidor de tiempo
  unsigned long currentMillis = millis();        
  if(currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
     contador = contador +1;
  }   
//medidor de tiempo
}
