# Kontrola parsera pred merge

## Zhrnutie

Merge vetvy `SematickaAnalyza-parser` do `main` sa zatiaľ neodporúča. Statická kontrola zdrojového kódu potvrdila viacero nesúladov so špecifikáciou IFJ26. Kompiláciu sa v aktuálnom prostredí nepodarilo spustiť, preto sú nižšie uvedené závery založené na prečítanom kóde a špecifikácii, nie na vykonaní regresných testov.

## Potvrdené nálezy

### 1. Výraz začínajúci identifikátorom ako samostatný príkaz

- **Súbor:** `parser.c`
- **Miesto:** `parse_id_statement()`, približne riadky 500–625
- **Závažnosť:** kritická
- **Popis:** Po načítaní identifikátora parser podporuje iba priradenie (`=`) alebo volanie funkcie (`(`). Ak identifikátor začína samostatný výraz, parser vráti `ERROR_SYNTAX`.
- **Dôsledok:** Posledný výraz bloku, napríklad `result`, nie je spracovaný podľa pravidiel návratovej hodnoty tela funkcie.
- **Špecifikácia:** Posledný príkaz bloku môže byť výraz alebo volanie a určuje výsledok tela.
- **Odporúčanie:** Zachovať token identifikátora alebo použiť bezpečný lookahead a následne spracovať celý výraz cez `parse_expression()`. Po úspešnom výraze musí byť podporený povolený koniec príkazu.

### 2. `@main` na samostatnom riadku

- **Súbor:** `parser.c`
- **Miesta:** `parse_headers()` a `parse_program()`
- **Závažnosť:** kritická
- **Popis:** Po spotrebovaní tokenu `TOKEN_TYPE_MAIN` parser okamžite očakáva `def`. Pri zápise:

  ```scala
  @main
  def run() = ()
  ```

  je aktuálnym tokenom `TOKEN_TYPE_EOL`, takže parser vráti `ERROR_SYNTAX`.
- **Dôsledok:** Platný formát anotácie podľa špecifikácie nie je akceptovaný.
- **Odporúčanie:** Po `@main` preskočiť povolené EOL pred spracovaním `def`, a to konzistentne v prvom aj druhom priechode.

### 3. Stredník ako oddeľovač príkazov

- **Súbor:** `parser.c`
- **Miesta:** `parse_var_def()`, `parse_id_statement()`, `parse_return()`, `parse_statement()`, `parse_block()`
- **Závažnosť:** kritická
- **Popis:** `parse_block()` spracuje stredník až po návrate z príkazu, ale jednotlivé príkazy samy vyžadujú `TOKEN_TYPE_EOL`.
- **Dôsledok:** Viac príkazov na jednom logickom riadku, napríklad `val a = 1; val b = 2`, skončí syntaktickou chybou ešte pred spracovaním stredníka.
- **Špecifikácia:** Príkazy môžu byť oddelené stredníkom.
- **Odporúčanie:** Zaviesť spoločnú kontrolu konca príkazu, ktorá akceptuje EOL aj stredník, a používať ju vo všetkých relevantných príkazoch.

### 4. Neuloženie odvodeného návratového typu funkcie

- **Súbor:** `parser.c`
- **Miesta:** `parse_function()`, približne riadky 849–978
- **Závažnosť:** kritická
- **Popis:** Pri funkcii bez explicitného návratového typu zostane symbol z prvého priechodu s `TYPE_UNDEF`. Po vyhodnotení tela sa odvodený typ do symbolovej tabuľky nezapíše.
- **Dôsledok:** Neskoršie volanie takejto funkcie môže mať typ `TYPE_UNDEF` a spôsobiť nesprávnu typovú chybu.
- **Odporúčanie:** Po odvodení typu aktualizovať `existing_func->data.func.return_type`. Rovnakú logiku treba zabezpečiť pre jedno- aj viacriadkové telo.

### 5. Nesprávne spracovanie explicitného návratového typu `Unit`

- **Súbor:** `parser.c`
- **Miesta:** `parse_return()` a jedno-riadkové telo v `parse_function()`
- **Závažnosť:** vysoká
- **Popis:** Parser porovnáva návratovú hodnotu s `TYPE_UNIT` ako s bežným typom.
- **Dôsledok:** Kód s explicitným návratovým typom `Unit`, ktorý vyhodnotí alebo vráti hodnotu, môže skončiť `ERROR_SEM_TYPE`.
- **Špecifikácia:** Pri explicitnom `Unit` sa návratová hodnota vyhodnotí, zahodí a funkcia vráti `()`.
- **Odporúčanie:** Pri explicitnom `Unit` vykonať syntaktické a potrebné sémantické spracovanie výrazu, ale nevyžadovať jeho typovú zhodu s `Unit`.

### 6. Unárne mínus pred zloženým výrazom

- **Súbor:** `parser.c`
- **Miesto:** `parse_term()`
- **Závažnosť:** vysoká
- **Popis:** Unárny operátor rekurzívne volá `parse_term()`, ale zátvorkovaný operand je v `parse_term()` interpretovaný iba ako prázdny Unit výraz `()`.
- **Dôsledok:** Výrazy ako `-(x + 1)` alebo `-(1 + 2)` nie sú spracované.
- **Odporúčanie:** Zjednotiť spracovanie zátvoriek s výrazovou gramatikou a overiť, že unárny operátor pracuje s celým zátvorkovaným výrazom.

### 7. `return` bez explicitného typu funkcie

- **Súbor:** `parser.c`
- **Miesto:** `parse_return()`, približne riadok 690
- **Závažnosť:** vysoká
- **Popis:** Kontrola návratového typu sa úplne preskočí, keď `current_func_return_type == TYPE_UNDEF`.
- **Dôsledok:** Funkcia bez explicitného návratového typu môže obsahovať `return`, hoci špecifikácia v takom prípade vyžaduje explicitný návratový typ.
- **Odporúčanie:** Evidovať výskyt `return` v tele funkcie a pri odvodenom návratovom type vrátiť príslušnú sémantickú chybu.

### 8. Riziko pretečenia poľa parametrov

- **Súbor:** `parser.c`
- **Miesta:** `parse_params()` a lokálne polia `Param temp_params[20]`
- **Závažnosť:** kritická
- **Popis:** Pred zápisom do `params[*param_count]` sa nekontroluje maximálny počet prvkov poľa.
- **Dôsledok:** Funkcia s viac ako 20 parametrami môže zapisovať mimo hraníc zásobníkového poľa.
- **Odporúčanie:** Pred každým zápisom overiť kapacitu poľa a pri prekročení vrátiť definovaný chybový kód. Kontrola musí byť v oboch priechodoch.

### 9. Duplicitné mená parametrov

- **Súbor:** `parser.c`
- **Miesto:** `parse_params()`
- **Závažnosť:** vysoká
- **Popis:** Parser nekontroluje, či sa meno parametra v zozname už nachádza.
- **Dôsledok:** Zápis ako `def foo(x: Int, x: Int) = ...` nie je odmietnutý ako redefinícia parametra; následné správanie závisí od vloženia do symbolovej tabuľky.
- **Odporúčanie:** Porovnať nové meno s už načítanými parametrami a pri duplicite vrátiť `ERROR_SEM_REDEF`.

## Čiastočne potvrdený alebo neúplný nález

### 10. Koncová čiarka pri volaní funkcie

- **Súbor:** `parser.c`
- **Miesta:** volanie funkcie v `parse_term()` a `parse_id_statement()`
- **Závažnosť:** stredná
- **Popis:** Po čiarke parser vždy pokračuje v načítaní ďalšieho argumentu. Ak nasleduje `)`, volanie zlyhá.
- **Dôležitá podmienka:** Špecifikácia povoľuje koncovú čiarku iba vtedy, keď medzi čiarkou a `)` existuje koniec riadku. Samotné `foo(a,)` na tom istom riadku preto nie je automaticky platný vstup.
- **Ďalší problém:** `parse_params()` prijíma koncovú čiarku bez kontroly, či medzi čiarkou a `)` bol EOL. To je samostatný nesúlad so špecifikáciou.
- **Odporúčanie:** Využiť informáciu o novom riadku zo scanneru a povoliť koncovú čiarku iba za podmienok špecifikácie.

## Ďalšie zistené problémy

### Výsledok viacriadkového tela funkcie sa nekontroluje

- **Súbor:** `parser.c`
- **Miesta:** `parse_block()` a `parse_function()`
- **Závažnosť:** kritická
- **Popis:** `parse_block()` vracia iba stav parsovania, nie typ výsledku posledného príkazu. `parse_function()` preto nevie overiť návratový typ posledného výrazu ani odvodiť typ funkcie z viacriadkového tela.
- **Dôsledok:** Môžu byť prijaté funkcie s nekompatibilným alebo neodvodeným výsledným typom.
- **Odporúčanie:** Rozšíriť výsledok parsovania bloku o informáciu o type posledného príkazu a o tom, či blok končí definíciou, priradením alebo cyklom, ktoré majú výsledok `Unit`.

### Chýba úplná kontrola pravidiel pre `return`

Špecifikácia vyžaduje:

- explicitný návratový typ pri každom výskyte `return`;
- kompatibilitu všetkých explicitných aj implicitných návratových hodnôt;
- špeciálne správanie pri explicitnom `Unit`;
- správne odvodenie návratového typu z výsledku tela.

Aktuálna implementácia pokrýva iba časť týchto pravidiel.

## Overenie a obmedzenia

- Kontrolované boli zdrojové súbory parsera, scanner, symbolová tabuľka a text špecifikácie.
- Vetva: `SematickaAnalyza-parser`.
- `make` nebolo možné spustiť, pretože príkaz `make` nie je v aktuálnom prostredí dostupný.
- Regresné testy parsera pre uvedené prípady v repozitári neboli nájdené.
- Pred merge treba opravy overiť kompiláciou a samostatnými vstupmi pre každý nález.
