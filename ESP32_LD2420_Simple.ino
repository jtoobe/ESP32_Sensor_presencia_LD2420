#include <HardwareSerial.h>

#define RX_PIN 16
#define TX_PIN 17

HardwareSerial radar(2);

String linea = "";

bool presencia = false;
int zona = -1;

void mostrarEstado()
{
  Serial.println();
  Serial.println("================================");
  Serial.println("      ESTADO DEL RADAR");
  Serial.println("================================");

  Serial.print("Presencia : ");
  Serial.println(presencia ? "SI" : "NO");

  Serial.print("Ocupacion : ");
  Serial.println(presencia ? "OCUPADO" : "LIBRE");

  Serial.print("Zona      : ");

  if (zona >= 0)
    Serial.println(zona);
  else
    Serial.println("-");

  Serial.println("================================");
}

void setup()
{
  Serial.begin(115200);

  radar.begin(
      115200,
      SERIAL_8N1,
      RX_PIN,
      TX_PIN);

  Serial.println("Monitor didactico LD2420");
}

void loop()
{
  while (radar.available())
  {
    char c = radar.read();

    if (c == '\n')
    {
      linea.trim();

      // Mostrar línea original
      Serial.print("Recibido: ");
      Serial.println(linea);

      if (linea == "ON")
      {
        presencia = true;
      }
      else if (linea == "OFF")
      {
        presencia = false;
        zona = -1;
      }
      else if (linea.startsWith("Range "))
      {
        zona = linea.substring(6).toInt();
      }

      mostrarEstado();

      linea = "";
    }
    else
    {
      linea += c;
    }
  }
}
