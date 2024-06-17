# Wemos-D1-mini_Temperatur-Humidity
Auslesen von DS18B20 und BodenfeuchteSensor mit einem Wemos D1 mini und anschliessende übertragung der Daten an einen MQTT-Server.

## Benötigte Hardware
mind. 1x DS18B20 (Temperatursensor)
<br>
1x Bodenfeuchtesensor Hygrometer Modul V1.2 (https://www.az-delivery.de/products/bodenfeuchte-sensor-modul-v1-2)
<br>
1x Wemos D1 mini oder ähnlich
<br>
versch. Kabel
<br>
je nach Anzahl der DS18B20 Widerstände (mind. 1) // 220 Ohm


## Einrichtung

### Hardware

![alt text](https://user-images.githubusercontent.com/42981810/113784088-179a9680-9735-11eb-85a6-e79a50098a5c.png)


### Software

Auskommentierte Befehle sind für einen zweiten Temperatursensor (DS18B20) um diesen zu aktivieren die betroffenen Zeilen reaktivieren.
In dem Beispiel werden die Daten an einen ioBroker gesendet.
