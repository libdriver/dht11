[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver DHT11

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/dht11/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

DHT11デジタル温度および湿度センサーは、校正されたデジタル信号出力を備えた温度および湿度複合センサーです。特殊なデジタルモジュール取得技術と温度および湿度検知技術を使用して、製品の高い信頼性と優れた長期安定性を保証します。センサーは、静電容量式湿度センサーとNTC温度センサーで構成され、高性能の8ビットMCUに接続されています。このセンサーには、低コスト、長期安定性、相対湿度および温度測定、優れた品質、超高速応答、強力な干渉防止能力、超長信号伝送距離、デジタル信号出力、および正確なキャリブレーションという利点があります。これは、HVAC、除湿機、農業、コールドチェーンストレージ、テストおよび検出機器、消費財、自動車、自動制御、データレコーダー、気象台、家電製品、湿度調整器、医療、およびその他の関連する湿度検出および制御で使用されます。

LibDriver DHT11は、LibDriverによって起動されたDHT11の全機能ドライバーであり、温度と相対湿度を読み取る機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver DHT11のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver DHT11用のプラットフォームに依存しないonewireバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver DHT11ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver DHT11プログラミング例が含まれています。

/ docディレクトリには、LibDriver DHT11オフラインドキュメントが含まれています。

/ datasheetディレクトリには、DHT11データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないonewireバステンプレートを参照して、指定したプラットフォームのonewireバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/dht11/index.html](https://www.libdriver.com/docs/dht11/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。