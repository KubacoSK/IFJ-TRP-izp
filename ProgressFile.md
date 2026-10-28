# Progress projektu IFJ a IAL (variant TRP-izp)

Posledná aktualizácia: 25. 10. 2026

## Legenda

- [x] Hotové a pokryté aktuálnym kódom alebo testami
- [~] Rozpracované / implementované iba čiastočne
- [ ] Ešte treba dorobiť

## Aktuálny stav

- Základné C moduly už existujú: scanner, parser, hash tabuľka, tabuľka symbolov,
  pomocné funkcie, chybové kódy a `main`.
- Hash tabuľka a tabuľka symbolov majú samostatné unit testy.
- Scanner má rozsiahlu testovaciu sadu pre tokeny, literály, komentáre, odsadenie
  a lexikálne chyby.
- Parser je zatiaľ iba základná kostra rekurzívneho zostupu. Vie spracovať
  základnú štruktúru programu, funkcie, bloky, deklarácie, priradenia, volania,
  `if`, `while` a `return`, ale nepokrýva celú gramatiku ani sémantiku.
- Generovanie IFJcode26 zatiaľ nie je implementované.
- Testy a build neboli v tomto prostredí overené, pretože nie sú dostupné
  príkazy `make`, `gcc` ani `clang`.

## 1. Príprava a architektúra

- [x] Vytvorenie / nastavenie spoločného Git repozitára.
- [x] Dohodnutie pravidiel práce: Conventional Commits, pull requesty a code review.
- [x] Vytvorenie základného `Makefile` s cieľmi `all`, `ifj26`, `test`,
  `test_scanner`, `test_ht`, `test_symtable` a `clean`.
- [x] Doplniť samostatné ciele `check` alebo `build-check`.
- [ ] Nastaviť a overiť `clang-format` pre všetky zdrojové súbory.
- [x] Navrhnutie základných dátových štruktúr tokenov v `scanner.h`.
- [x] Navrhnutie dátových štruktúr hash tabuľky a tabuľky symbolov.
- [~] Základná modulárna architektúra existuje, treba ju ešte prepojiť s
  kompletným tokom parser -> sémantika -> generovanie kódu.
- [ ] Doplniť jednotné vlastníctvo pamäte a pravidlá uvoľňovania pre všetky
  nové štruktúry parsera a generátora.

## 2. Hash tabuľka a tabuľka symbolov (IAL)

### Hash tabuľka

- [x] Zvolená hashovacia funkcia djb2.
- [x] Implementovaná otvorená adresácia s lineárnym prehľadávaním.
- [x] Implementované stavy `EMPTY`, `OCCUPIED` a `DELETED`.
- [x] Implementované `ht_init`, `ht_insert`, `ht_search`, `ht_delete` a
  `ht_clear`.
- [x] Ošetrené kolízie, aktualizácia duplicitného kľúča a hrobčeky.
- [x] Napísané unit testy pre inicializáciu, vkladanie, vyhľadávanie,
  kolízie, mazanie a čistenie tabuľky.
- [ ] Overiť správanie pri zaplnenej tabuľke a pri zlyhaní alokácie.

### Tabuľka symbolov

- [x] Navrhnuté typy `DataType`, `SymbolKind`, `Param`, `VarData` a `FuncData`.
- [x] Implementovaná globálna tabuľka funkcií.
- [x] Implementované lokálne scopes s rodičovským scope.
- [x] Implementované pridávanie a vyhľadávanie premenných a funkcií.
- [x] Implementované zatienenie premenných vo vnorenom scope.
- [x] Implementované uvoľnenie symbolov, parametrov a scope-ov.
- [x] Napísané unit testy pre funkcie, premenné, scopes a zatienenie.
- [ ] Rozhodnúť a implementovať správanie pri redefinícii v rovnakom scope
  (aktuálne hash tabuľka duplicitný kľúč aktualizuje).
- [ ] Doplniť testy pre chybové stavy a zlyhanie alokácie.

## 3. Lexikálna analýza / scanner

- [ ] Dokončiť a archivovať stavový diagram scanneru.
- [x] Čítanie zo `stdin` aj z nastaveného `FILE *`.
- [x] Reset vnútorného stavu scanneru.
- [x] Tokenizácia identifikátorov, kľúčových slov a samostatného `_`.
- [x] Tokenizácia celočíselných a desatinných literálov vrátane exponentov,
  oddeľovačov `_` a sufixu `d/D`.
- [x] Tokenizácia jedno- a viacriadkových reťazcov s escape sekvenciami.
- [x] Tokenizácia operátorov, porovnania, priradenia a interpunkcie.
- [x] Podpora anotácie `@main`.
- [x] Spracovanie komentárov vrátane vnorených blokových komentárov.
- [x] Spracovanie odsadenia cez tokeny `INDENT` a `DEDENT`.
- [x] Lookahead cez `unget_token`.
- [x] Detekcia lexikálnych chýb a interných chýb alokácie.
- [x] Unit testy scanneru pokrývajúce základné tokeny a chybové vstupy.
- [ ] Spustiť testy na dostupnom Linux/Merlin prostredí.
- [ ] Doplniť regresné testy pre hraničné prípady čísel, komentárov,
  odsadenia a konca súboru.

## 4. Syntaktická analýza / parser (Dominik)

- [x] Základný rekurzívny zostup je implementovaný.
- [x] Spracovanie programu, importov, funkcií a anotácie `@main`.
- [x] Spracovanie parametrov a návratových typov funkcií.
- [x] Spracovanie blokov cez `INDENT` / `DEDENT`.
- [x] Spracovanie deklarácií `val` a `var`, priradení a jednoduchých volaní.
- [x] Spracovanie `if ... then ... else`, `while ... do` a `return`.
- [x] Jednoduché výrazy podporujú literály, identifikátory a volania funkcií.
- [ ] Navrhnúť a skontrolovať kompletnú LL gramatiku podľa zadania.
- [ ] Doplniť pravidlá pre všetky povolené typy príkazov a návratov.
- [x] Implementovať výrazy s operátormi `+`, `-`, `*`, `/` a porovnaniami.
- [x] Implementovať precedenčnú analýzu alebo ekvivalentné pravidlá priorít.
- [x] Doplniť zátvorkovanie, unárne operátory a kombinované výrazy podľa zadania.
- [x] Správne rozlíšiť kontext `@main` a bežných definícií funkcií.
- [~] Doplniť detekciu chýb na konci bloku, chýbajúcich častí a nadbytočných tokenov.
- [~] Vytvoriť samostatné syntaktické testy s očakávanými návratovými kódmi.

## 5. Sémantická analýza (Dominik)

- [~] Dátové štruktúry tabuľky symbolov už obsahujú typy, parametre,
  inicializáciu, konštanty a príznaky definície funkcie.
- [x] Prepojiť pridávanie funkcií a premenných z parsera do tabuľky symbolov.
- [x] Kontrolovať definovanie premennej/funkcie pred použitím.
- [x] Kontrolovať redefiníciu premennej alebo funkcie.
- [ ] Kontrolovať inicializáciu premennej pred čítaním.
- [~] Implementovať typovú kontrolu výrazov a priradení.
- [ ] Kontrolovať zápis do `val` a ďalších nemenných identifikátorov.
- [ ] Kontrolovať počet a typy argumentov pri volaní funkcie.
- [ ] Kontrolovať návratový typ a platnosť príkazu `return`.
- [~] Overiť povinnosť a jedinečnosť `@main`.
- [~] Doplniť testy všetkých sémantických chybových kódov `3`, `4`, `5`, `6`,
  `7` a `10`.

## 6. Generovanie cieľového kódu IFJcode26 (Jakub)

- [ ] Navrhnúť rozhranie a dátové štruktúry generátora.
- [ ] Implementovať výpis hlavičky a základných inštrukcií IFJcode26.
- [ ] Implementovať tvorbu a rušenie rámcov.
- [ ] Implementovať prácu s premennými, parametrami a dočasnými hodnotami.
- [ ] Implementovať generovanie výrazov a konverzií typov.
- [ ] Implementovať generovanie volaní funkcií a návratových hodnôt.
- [ ] Implementovať generovanie `if` / `else` a `while` cez návestia a skoky.
- [ ] Implementovať požadované vstavané funkcie.
- [ ] Otestovať výstup cez referenčný interpret IFJcode26.
- [ ] Overiť, že diagnostika ide na `stderr` a generovaný kód na `stdout`.

## 7. Testovanie, kvalita a ladenie

- [x] Existujú unit testy hash tabuľky, tabuľky symbolov a scanneru.
- [ ] Doplniť end-to-end testovací skript pre preklad a návratové kódy.
- [ ] Pridať validné vstupy s očakávaným výstupom.
- [ ] Pridať lexikálne, syntaktické a sémantické chybové vstupy.
- [ ] Pridať testy generovaného IFJcode26.
- [ ] Spustiť testy cez `gcc` aj `clang`.
- [ ] Overiť kompatibilitu s požiadavkami servera Merlin.
- [ ] Skontrolovať úniky pamäte cez `valgrind` alebo dostupný ekvivalent.
- [ ] Pridať testy hraničných prípadov a regresné testy po každej väčšej zmene.
- [ ] Overiť warning-free build s `-Wall -Wextra -pedantic -std=c99`.

## 8. Dokumentácia a odovzdanie

- [~] Zdrojové súbory obsahujú základné komentáre k verejným rozhraniam.
- [ ] Priebežne zapisovať použitie AI podľa požiadaviek predmetu.
- [ ] Vytvoriť súbor `rozdeleni` podľa špecifikácie.
- [ ] Dokončiť `dokumentace.pdf`:
  - [ ] Úvodná strana, členovia tímu a rozdelenie práce.
  - [ ] Diagram architektúry a dátových tokov.
  - [ ] Diagram konečného automatu scanneru.
  - [ ] LL gramatika/tabuľka a precedenčná tabuľka.
  - [ ] Popis tabuľky symbolov a generovania kódu.
  - [ ] Zhodnotenie použitia AI a rozdelenia práce.
- [ ] Doplniť a aktualizovať `README.md` o build, testy a použitie prekladača.
- [ ] Spustiť `is_it_ok.sh` nad finálnym archívom.
- [ ] Skontrolovať obsah archívu a odstrániť objektové, dočasné a testovacie súbory.
- [ ] **POKUSNÉ ODOVZDANIE** do 19. novembra 2026.
- [ ] **FINÁLNE ODOVZDANIE** do 27. novembra 2026 11:59:59.

## Odporúčané poradie ďalšej práce

1. Dokončiť gramatiku, výrazy a parserové testy.
2. Prepojiť parser so symbolovou tabuľkou a doplniť sémantické kontroly.
3. Navrhnúť a implementovať generátor IFJcode26.
4. Pridať end-to-end testy a referenčné výstupy.
5. Spustiť build, testy, sanitizéry a kontroly na Merlin/Linuxe.
6. Dokončiť dokumentáciu, odovzdávací skript a finálny archív.
