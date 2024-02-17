[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver DHT11
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/dht11/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der digitale Temperatur- und Feuchtigkeitssensor DHT11 ist ein zusammengesetzter Temperatur- und Feuchtigkeitssensor mit kalibriertem Digitalsignalausgang. Es verwendet eine spezielle digitale Modulerfassungstechnologie sowie Temperatur- und Feuchtigkeitsmesstechnologie, um sicherzustellen, dass das Produkt eine hohe Zuverlässigkeit und ausgezeichnete Langzeitstabilität aufweist. Der Sensor besteht aus einem kapazitiven Feuchtigkeitssensor und einem NTC-Temperatursensor und ist mit einer leistungsstarken 8-Bit-MCU verbunden. Der Sensor hat die Vorteile von niedrigen Kosten, Langzeitstabilität, relativer Feuchtigkeits- und Temperaturmessung, ausgezeichneter Qualität, ultraschneller Reaktion, starker Entstörungsfähigkeit, ultralanger Signalübertragungsdistanz, digitaler Signalausgabe und genauer Kalibrierung. Es wird in HVAC, Luftentfeuchtern, Landwirtschaft, Kühlkettenlagerung, Test- und Erkennungsgeräten, Konsumgütern, Automobilen, automatischen Steuerungen, Datenrekordern, Wetterstationen, Haushaltsgeräten, Feuchtigkeitsreglern, medizinischen Behandlungen und anderen verwandten Feuchtigkeitserkennungen und -kontrollen verwendet.

LibDriver DHT11 ist der voll funktionsfähige Treiber von DHT11, der von LibDriver gestartet wurde. Er bietet die Funktion zum Lesen von Temperatur und relativer Luftfeuchtigkeit. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver DHT11-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver DHT11 onewire.

/test enthält den Testcode des LibDriver DHT11-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver DHT11-Beispielcode.

/doc enthält das LibDriver DHT11-Offlinedokument.

/Datenblatt enthält DHT11-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige onewire-Schnittstellenvorlage und stellen Sie Ihren Plattform-onewire-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_dht11_basic.h"

uint8_t res;
uint8_t i;
float temperature;
uint8_t humidity;

res = dht11_basic_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    dht11_interface_delay_ms(2000);
    res = dht11_basic_read((float *)&temperature, (uint8_t *)&humidity);
    if (res != 0)
    {
        (void)dht11_basic_deinit();

        return 1;
    }
    dht11_interface_debug_print("dht11: temperature is %0.2fC.\n", temperature);
    dht11_interface_debug_print("dht11: humidity is %d%%.\n", humidity); 
    
    ...
        
}

...

(void)dht11_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/dht11/index.html](https://www.libdriver.com/docs/dht11/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.