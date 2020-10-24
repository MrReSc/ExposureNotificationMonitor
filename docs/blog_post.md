# Exposure Notification Monitor mit EPS32

![ic_launcher](https://raw.githubusercontent.com/DP-3T/dp3t-app-android-ch/master/app/src/main/res/mipmap-xxxhdpi/ic_launcher.png)

Da es aus meiner Sicht keine datenschutztechnischen Bedenken gibt die SwissCovid App zu verwenden, bin ich auch schon seit der öffentlichen Betapahse mit dabei. Das dezentrale Konzept ist sehr elegant und die App wurde transparent implementiert.

Die iOS und Android App sowie das Backend und Dokumentation sind auf [Github verfügbar](https://github.com/DP-3T).

## Problem
Leider erscheint auf meinem Smartphone immer mal wieder die Meldung, das etwas nicht funktioniert weil angeblich mein Bluetooth ausgeschaltet ist.

![screenshot](screenshot.png)

Ich denke, es hat was mit den "Akku Optimierungen" von OnePlus zu tun. Auch nachdem ich die App von den Akku Optimierungen ausgeschlossen habe, sehen ich diese Meldung ab und an mal.

## Vermutung
Da ja die Exposure Notification auf Betriebssystemebene gemacht wird, vermute ich, dass es trotz dieser Meldung Funktioniert. 

## IDE
Entwicklungsumgebung ist VS Code mit der [PlatformIO](https://platformio.org/) Erweiterung.

## Verifikation und Implementierung
Über die Service UUID im Advertising Payload kann festgestellt werden ob es sich um ein Exposure Notification handelt. Die UUID ist in der [Spezifikation](https://www.blog.google/documents/62/Exposure_Notification_-_Bluetooth_Specification_v1.1.pdf) verfügbar.

Mit der [ESP32 BLE for Arduino](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE) Bibliothek und einem ESP32 kann sehr einfach ein scanner gebaut werden.

Im Monitor sieht man nun folgende Informationen (sofern ein sendendes Gerät in der Nähe ist):

```
MAC: 60:d5:30:cf:41:66 | RSSI: -88 
MAC: 4d:c8:8c:b7:6b:d1 | RSSI: -64 
Currently visible devices: 2
```
In meiner Umgebung senden aktuell zwei Geräte eine Exposure Notification aus. Nun lasse ich mein Smartphone mal für eine längere Zeit unbenutzt liegen. Als beim entsperren die obige Meldung wieder angezeigt wurde, ich aber im Monitor kein zusätzliches Gerät gesehen habe, wusste ich, das die Exposure Notification trotz Meldung ausgesendet wird.

Zusätzlich sieht man auch gut, das die Bluetooth MAC Adresse alle 15-20 Minuten gewechselt wird, um ein Tracking zu verhindern.

Das komplette Projekt ist auf Github [https://github.com/MrReSc/ExposureNotificationMonitor/tree/main](https://github.com/MrReSc/ExposureNotificationMonitor/tree/main) verfügbar.