# Progress projektu IFJ a IAL (variant TRP-izp)

Posledná aktualizácia: 14. 11. 2026

## Legenda

- [x] Hotové a pokryté aktuálnym kódom alebo testami
- [~] Rozpracované / implementované iba čiastočne
- [ ] Ešte treba dorobiť

## Aktuálny stav

- Základné C moduly existujú: scanner, parser (syntax + sémantika v jednom
  module), hash tabuľka, tabuľka symbolov, pomocné funkcie, chybové kódy a `main`.
- Build bol overený v Linux prostredí (WSL Ubuntu, gcc 13.3) s
  `-Wall -Wextra -pedantic -std=c99`, bez warningov.
- Unit testy prechádzajú: scanner 56/56, hash tabuľka 26/26, tabuľka
  symbolov 19/19 (`make test`).
- Parser je dvojpriechodový: 1. priechod zbiera hlavičky funkcií, 2. priechod
  analyzuje telá. Všetkých 10 nálezov z `REVIEW_FINDINGS.md` je opravených
  (finding 4 v commite `d03b5ee`), vetva je zlúčená do `main` (PR #3).
- Formátovanie: v `main` je `.clang-format` s čistým štýlom LLVM. Všetky
  zdrojové súbory sú preformátované a zmeny sú zlúčené do `main`; build bez
  warningov a unit testy prechádzajú rovnako ako predtým.
- Parser bol ručne otestovaný sadou ~90 malých IFJ26 programov s očakávanými
  návratovými kódmi a cez `valgrind`; sada zatiaľ nie je v repozitári.
- Generovanie IFJcode26 zatiaľ nie je implementované (vetva `CodeGenerator`
  neobsahuje generátor).
- **Pokusné odovzdanie je 19. 11. 2026** – bez generátora kódu prejdú iba
  testy chybových návratových kódov.
- Projekt bol porovnaný s demo cvičeniami (časť 1 a 2), slidmi prednášok a
  špecifikáciou; podrobnosti sú v `Democvika feedback.md`. Najväčšie riziko je
  precedenčná analýza (časť 4), generátor má pred písaním niekoľko
  rozhodnutí (časť 6).

## 1. Príprava a architektúra

- [x] Vytvorenie / nastavenie spoločného Git repozitára.
- [x] Dohodnutie pravidiel práce: Conventional Commits, pull requesty a code review.
- [x] Vytvorenie základného `Makefile` s cieľmi `all`, `ifj26`, `test`,
  `test_scanner`, `test_ht`, `test_symtable` a `clean`.
- [x] Doplniť samostatné ciele `check` alebo `build-check`.
- [x] Nastaviť a overiť `clang-format` pre všetky zdrojové súbory (zadanie 2.5
  to vyžaduje povinne): `.clang-format` (LLVM bez úprav), kód je preformátovaný
  a zlúčený do `main` (PR #4). Odvtedy musí každý formátovať pred commitom
  (VS Code: Shift+Alt+F alebo Format On Save).
- [x] Architektúra bez AST: parser riadi preklad a generátor bude vypisovať kód
  priamo pri rozpoznaní konštrukcie. Zodpovedá prístupu 3 z prednášky 9
  („Direct Generation of 3AC“). Na obhajobu pripraviť zdôvodnenie (bez AST,
  dva priechody); demo cvičenie odporúča skôr AST, ale priamy prístup je povolený.
- [x] Navrhnutie základných dátových štruktúr tokenov v `scanner.h`.
- [x] Navrhnutie dátových štruktúr hash tabuľky a tabuľky symbolov.
- [~] Základná modulárna architektúra existuje, treba ju ešte prepojiť s
  kompletným tokom parser -> sémantika -> generovanie kódu.
- [x] Bez `tmpfile()`: 1. priechod načíta všetky tokeny do poľa v pamäti
  (lexikálna chyba ako zarážka, vráti sa až keď k nej parser dôjde),
  2. priechod ide po tom istom poli. Scanner sa číta zo stdin iba raz.
- [~] Jednotné vlastníctvo pamäte: parametre funkcií majú `free_params`,
  `parse_params` uvoľňuje pri chybe; pri chybe sa ešte neuvoľní `current_tok`
  a symbolová tabuľka v niektorých vetvách.
- [ ] Hlavičky zdrojových súborov neobsahujú mená a loginy autorov
  (zadanie 2.5 to vyžaduje). Demo cvičenie: hlavička s autorom a popisom má
  byť v každom súbore a všade rovnaká.

## 2. Hash tabuľka a tabuľka symbolov (IAL)

### Hash tabuľka

- [x] Zvolená hashovacia funkcia djb2.
- [x] Implementovaná otvorená adresácia s lineárnym prehľadávaním.
- [x] Implementované stavy `EMPTY`, `OCCUPIED` a `DELETED`.
- [x] Implementované `ht_init`, `ht_insert`, `ht_search`, `ht_delete` a
  `ht_clear`.
- [x] Ošetrené kolízie, aktualizácia duplicitného kľúča a hrobčeky.
- [x] Napísané unit testy pre inicializáciu, vkladanie, vyhľadávanie,
  kolízie, mazanie a čistenie tabuľky (26/26 prechádza).
- [ ] Overiť správanie pri zaplnenej tabuľke a pri zlyhaní alokácie.

### Tabuľka symbolov

- [x] Navrhnuté typy `DataType`, `SymbolKind`, `Param`, `VarData` a `FuncData`.
- [x] Implementovaná globálna tabuľka funkcií.
- [x] Implementované lokálne scopes s rodičovským scope.
- [x] Implementované pridávanie a vyhľadávanie premenných a funkcií.
- [x] Implementované zatienenie premenných vo vnorenom scope.
- [x] Implementované uvoľnenie symbolov, parametrov a scope-ov.
- [x] Napísané unit testy pre funkcie, premenné, scopes a zatienenie (19/19).
- [x] Redefinícia v rovnakom scope: rieši parser cez
  `symtable_find_var_current_scope` pred vložením (chyba 4).
- [x] Vstavané funkcie (`print`, `readLine`, `readInt`, `readDouble`, `toStr`,
  `toInt`, `strLength`, `subStr`, `ord`, `chr`) sú vložené do tabuľky.
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
- [x] Lookahead cez `unget_token` (využíva ho parser pri príkaze s identifikátorom).
- [x] Príznak `had_preceding_newline` sa nastavuje (potrebné pre koncovú čiarku).
- [x] Detekcia lexikálnych chýb a interných chýb alokácie.
- [x] Unit testy scanneru pokrývajúce základné tokeny a chybové vstupy (56/56).
- [x] Spustiť testy na Linux prostredí (WSL Ubuntu).
- [ ] Overiť na serveri Merlin (gcc 14+/clang).
- [ ] Doplniť regresné testy pre hraničné prípady čísel, komentárov,
  odsadenia, konca súboru a `had_preceding_newline`.

## 4. Syntaktická analýza / parser (Dominik)

- [x] Rekurzívny zostup, dvojpriechodový (hlavičky -> telá).
- [x] Povinný prolog `import ifj26.*`, iba definície funkcií na najvyššej úrovni.
- [x] Anotácia `@main` na rovnakom aj samostatnom riadku (oba priechody).
- [x] Parametre a návratové typy funkcií, ľubovoľný počet parametrov
  (dynamické pole namiesto `Param[20]`).
- [x] Koncová čiarka v parametroch a argumentoch iba pred novým riadkom.
- [x] Bloky cez `INDENT` / `DEDENT`, prázdny blok je chyba 2.
- [x] `val` / `var`, priradenie, volanie funkcie ako príkaz.
- [x] Samostatný výraz ako príkaz vrátane výrazu začínajúceho identifikátorom.
- [x] Stredník ako oddeľovač príkazov na jednom logickom riadku.
- [x] `if ... then ... else` (else povinné), `while ... do`, `return [výraz]`.
- [x] Precedenčná analýza výrazov s `+ - * /`, relačnými operátormi a zátvorkami.
- [x] Precedenčná tabuľka navrhnutá ručne podľa prednášky 8 (priorita,
  asociativita, zátvorky, `$`); hodnoty sú správne.
- [ ] **RIZIKO – overiť u cvičiaceho / na fóre:** slučka `parse_expression_inner`
  sa líši od algoritmu z prednášky 8. Slidy: jeden zásobník s terminálmi, `E` a
  značkami `<`, identifikátor `i` v tabuľke, redukcia hľadá pravidlo `A → y`.
  Kód: dva zásobníky (operátory a typy), bez `<`, bez `i` v tabuľke, redukcia
  vyberie operátor a dva operandy. Zadanie žiada analýzu „odpovídající výkladu
  v přednáškách“ a autor zadania na democviku varoval pred Shunting Yard.
  Ak treba zmeniť: tabuľka ostane, pribudne riadok/stĺpec `i` a slučka sa
  prepíše na jeden zásobník (formalizmy navrhnúť ručne, nie cez AI).
- [x] Unárne `+`/`-` vrátane `-( ... )`.
- [x] Vnorené zátvorky vo výrazoch (`((x))`, `1 + (2 * (3))`); prázdne `()`
  sa rozpozná podľa `expect_opd`.
- [x] Precedenčná analýza kontroluje poradie operand/operátor
  (`1 2 +`, `1 + * 2`, `x *` sú chyba 2).
- [x] Zásobníky v `parse_expression` sú dynamické (`realloc`), hlboké výrazy
  (5000 zátvoriek) prejdú bez pretečenia, overené ASan aj valgrind.
- [x] Logický riadok nesmie začínať operátorom (`-x` na začiatku riadku je
  chyba 2, za `;` na tom istom riadku je povolené).
- [x] Neznámy názov typu (`val a: Foo`, `a: Foo`, `): Foo`) je chyba 3
  (spoločná funkcia `parse_type`).
- [ ] Scanner neberie `Boolean`, `case`, `class`, `extension`, `for`, `List`,
  `match`, `type` ako kľúčové slová (špecifikácia: v základe je vhodné ich
  neprijímať ako identifikátor, netestuje sa). `val a: Boolean` dnes vráti 3.
- [~] Volanie funkcie vo výraze (`1 + f(x)`) a výraz/volanie v argumentoch sú
  prijímané – v základnom zadaní je to chyba, platné iba s rozšírením FUNEXP.
  Demo cvičenie FUNEXP silno odporúča (hlavne úpravy precedenčnej analýzy,
  zároveň rieši nejednoznačnosť priradenia), polovicu už máme → dokončiť
  a zapísať do `rozsireni`.
- [ ] Navrhnúť a zdokumentovať kompletnú LL gramatiku a LL tabuľku.
- [~] Vytvoriť samostatné syntaktické testy s očakávanými návratovými kódmi
  (existujú lokálne, treba ich pridať do `tests/` a skriptu).

## 5. Sémantická analýza (Dominik)

- [x] Prepojenie parsera s tabuľkou symbolov pre funkcie, parametre a premenné.
- [x] Nedefinovaná premenná/funkcia (3), redefinícia premennej/funkcie (4).
- [x] Duplicitné mená parametrov (4).
- [x] Inicializácia je povinná syntakticky, čítanie neinicializovanej premennej
  nemôže nastať.
- [x] Typová kontrola výrazov, inicializácie a priradení vrátane `Int -> Double`.
- [x] Zápis do `val` a do parametra (7).
- [x] Počet a typy argumentov pri volaní vstavaných aj užívateľských funkcií (5).
- [x] `@main`: chýbajúci (3), viacnásobný (4), s parametrami (5),
  iný návratový typ ako `Unit` (6).
- [x] Boolean iba v podmienke `if` / `while` (inde chyba 6).
- [x] Explicitný `Unit`: hodnota `return` a jednoriadkového tela sa zahodí.
- [x] `return` vo funkcii bez explicitného návratového typu (6).
- [x] **Finding 4:** odvodený návratový typ sa ukladá do symtable; funkcia bez
  typu volaná pred definíciou sa analyzuje na požiadanie (skok v poli tokenov,
  bez prístupu k lokálnym premenným volajúceho, potom sa v poradí preskočí).
- [x] Rekurzia bez typu v hlavičke (6): priama/vzájomná počas analýzy (stav
  „prebieha“), nepriama cez funkciu s typom cez graf volaní (DFS na konci).
- [ ] Parser pri analýze na požiadanie priamo mení `symtab->current_scope`
  (Symtable nie je skrytý ADT). Na obhajobu by bolo čistejšie pridať do
  `symtable` funkciu na odpojenie/obnovenie rozsahov – rozhodnúť v tíme
  (pozor: AI sa pri implementácii vyhľadávacej štruktúry nesmie použiť).
- [x] Výsledok bloku (`StmtResult`): posledný príkaz určuje výsledok tela,
  definícia/priradenie/`while` = `Unit`; kontroluje sa aj nedosiahnuteľný kód.
- [x] Pravidlá pre `if` na konci tela funkcie (explicitný `Unit` / všetky vetvy
  `return` / bez typu a všetky vetvy `Unit`), rekurzívne pre vnorený `if`.
- [x] `@main` bez typu musí mať výsledok tela `Unit`.
- [ ] Porovnanie `==` / `!=` dvoch hodnôt `Unit` vracia 6, špecifikácia
  povoľuje porovnanie hodnôt rovnakého typu.
- [ ] Overiť na fóre: chyba 6 vs. 10 pre nepovolený `return` (samostatný
  `return` mimo `Unit`, `return` vo funkcii bez typu).
- [ ] Overiť na fóre: zreťazenie relačných operátorov (`1 < 2 < 3`) teraz
  vracia 6, môže sa očakávať 2.
- [ ] Overiť: `val x` v tele funkcie s parametrom `x` vracia 4 (parametre sú
  v rovnakom scope ako telo), Scala to povoľuje.
- [ ] Poradie chýb medzi priechodmi: 1. priechod hlási chyby hlavičiek skôr, než
  2. priechod skontroluje prolog (napr. chýbajúci prolog + duplicitná funkcia
  vráti 4 namiesto 2).
- [~] Testy sémantických chybových kódov `3`, `4`, `5`, `6`, `7` existujú
  lokálne; kód `10` zatiaľ nikde nevzniká.

## 6. Generovanie cieľového kódu IFJcode26 (Jakub)

Rozhodnutia pred písaním (demo cvičenie 2, overené v špecifikácii):

- [ ] Rozsahy platnosti: jeden lokálny rámec na funkciu, premenné premenovať
  podľa rozsahu (`x$1`, `x$2`). Číslo rozsahu musí byť jedinečné z počítadla,
  nie hĺbka zanorenia → doplniť ID do `Scope` v `symtable.h`.
- [ ] Všetky `DEFVAR` presunúť na začiatok funkcie (`DEFVAR` v cykle = chyba 52
  pri druhom prechode) → dva buffery na funkciu: `DEFVAR`-y a telo.
- [ ] Výstup bufferovať po funkciách a vypísať až na konci bez chyby (telo sa
  môže generovať prerušovane pri analýze na požiadanie).
- [ ] Volacia konvencia: argumenty aj návratová hodnota na dátovom zásobníku
  (odporúčané, hlavne s FUNEXP). Nevracať hodnotu v `TF` – `POPFRAME` ju prepíše.
- [ ] Výrazy zásobníkovými inštrukciami (`PUSHS`, `ADDS`, …) pri redukcii
  v precedenčnej analýze; pozor na `Int → Double` pri ľavom operande.
- [ ] Jedinečné návestia z počítadla (napr. `fun$while$3$end`).
- [ ] `Unit` ako `nil@nil`, ale `print(())` musí vypísať `()` (nie `nil`).
- [ ] `Double` literály cez `printf("%a")`; `print` = `WRITE` (`%a`),
  `toStr` pre `Double` = `FLOAT2STR` (`%.2f`).

Implementácia:

- [ ] Navrhnúť rozhranie a dátové štruktúry generátora.
- [ ] Implementovať výpis hlavičky a základných inštrukcií IFJcode26.
- [ ] Implementovať tvorbu a rušenie rámcov.
- [ ] Implementovať prácu s premennými, parametrami a dočasnými hodnotami.
- [ ] Implementovať generovanie výrazov a konverzií typov.
- [ ] Implementovať generovanie volaní funkcií a návratových hodnôt.
- [ ] Implementovať generovanie `if` / `else` a `while` cez návestia a skoky.
- [ ] Implementovať požadované vstavané funkcie (vrátane chyby 40 pri `subStr`).
- [ ] Otestovať výstup cez referenčný interpret IFJcode26.
- [ ] Overiť, že diagnostika ide na `stderr` a generovaný kód na `stdout`.

## 7. Testovanie, kvalita a ladenie

- [x] Existujú unit testy hash tabuľky, tabuľky symbolov a scanneru.
- [ ] Doplniť end-to-end testovací skript pre preklad a návratové kódy.
- [ ] Pridať validné vstupy s očakávaným výstupom.
- [~] Lexikálne, syntaktické a sémantické chybové vstupy existujú lokálne,
  treba ich pridať do `tests/`.
- [ ] Pridať testy generovaného IFJcode26.
- [~] Build overený cez gcc 13 (WSL); treba ešte gcc 14+/clang 19+ (Merlin).
- [ ] Overiť kompatibilitu s požiadavkami servera Merlin.
- [~] Parser skontrolovaný cez `valgrind` na testovacích vstupoch – bez únikov
  a neplatných prístupov; overflow pri hlbokých zátvorkách (ASan) je opravený.
- [ ] Pridať testy hraničných prípadov a regresné testy po každej väčšej zmene.
- [x] Warning-free build s `-Wall -Wextra -pedantic -std=c99`.
- [x] Pomenovanie je jednotné: funkcie a premenné `slovo_slovo`, typy
  `PascalCase`, konštanty a makrá `VELKE_PISMENA`.
- [ ] Drobné výnimky v pomenovaní: `Token_type` (nepoužitý alias) a
  `Token_attribute` v `scanner.h`, lokálne `p_toStr`, `p_toInt`,
  `p_strLength`, `p_subStr` v `symtable.c`, makro `current_tok` v `parser.c`.

## 8. Dokumentácia a odovzdanie

- [~] Zdrojové súbory obsahujú základné komentáre k verejným rozhraniam.
  Demo cvičenie: dokumentácia funkcií má byť v `.h` (ideálne Doxygen),
  vo vnútri funkcií stručné komentáre – prejsť všetky `.h`.
- [ ] Pripraviť odpovede na obhajobu: prečo bez AST, prečo dva priechody,
  prečo scanner s vnorenými komentármi nie je čistý konečný automat, prečo
  scanner nepracuje s tabuľkou symbolov (prednáška 5 to pripúšťa), parametre
  hash tabuľky (djb2, 2039 slotov, lineárny krok), tvar precedenčnej analýzy.
- [ ] Priebežne zapisovať použitie AI podľa požiadaviek predmetu.
- [ ] Vytvoriť súbor `rozdeleni` (LF konce riadkov, súčet 100 %).
- [ ] Vytvoriť súbor `rozsireni` (identifikátory rozšírení, LF konce riadkov).
- [ ] Dokončiť `dokumentace.pdf`:
  - [ ] Úvodná strana, členovia tímu, varianta, rozdelenie bodov, rozšírenia,
    odkaz na repozitár.
  - [ ] Diagram architektúry a dátových tokov.
  - [ ] Diagram konečného automatu scanneru.
  - [ ] LL gramatika/tabuľka a precedenčná tabuľka.
  - [ ] Popis tabuľky symbolov a generovania kódu.
  - [ ] Zhodnotenie použitia AI a rozdelenia práce.
  - [ ] Uviesť štýl formátovania kódu (`clang-format`, LLVM).
- [ ] Doplniť a aktualizovať `README.md` o build, testy a použitie prekladača.
- [ ] Spustiť `is_it_ok.sh` nad finálnym archívom.
- [ ] Skontrolovať obsah archívu a odstrániť objektové, dočasné a testovacie súbory.
- [ ] **POKUSNÉ ODOVZDANIE** do 19. novembra 2026 23:59:59.
- [ ] **FINÁLNE ODOVZDANIE** do 27. novembra 2026 11:59:59.

## Odporúčané poradie ďalšej práce

1. ~~Odstrániť `tmpfile()` – pole tokenov v pamäti.~~ Hotové.
2. ~~Opraviť chyby precedenčnej analýzy.~~ Hotové.
3. ~~Výsledok bloku, pravidlá návratovej hodnoty (O11), analýza na požiadanie
   a graf volaní (O12, finding 4).~~ Hotové.
4. ~~Zlúčiť vetvu `formatovanie-llvm` (`clang-format`).~~ Hotové (PR #4).
5. **Overiť precedenčnú analýzu u cvičiaceho / na fóre** (časť 4); ak treba,
   prepísať slučku na algoritmus z prednášky 8 skôr, než sa na ňu napojí generátor.
6. Rozhodnúť návrh generátora (časť 6): rozsahy s jedinečným ID, `DEFVAR`
   na začiatok funkcie, buffery po funkciách, volacia konvencia cez zásobník.
7. Implementovať generátor IFJcode26 – bez neho nepôjdu validné testy
   (do pokusného odovzdania 19. 11. aspoň `print`, výrazy, premenné, `if`, `while`).
8. Dokončiť FUNEXP a zapísať ho do `rozsireni`.
9. Pridať end-to-end testy a skript do `tests/`.
10. Spustiť build a testy na Merlin, doplniť hlavičky súborov a dokumentáciu
    funkcií v `.h`.
11. Dokončiť dokumentáciu, `rozdeleni`, `rozsireni`, `is_it_ok.sh` a archív;
    pripraviť odpovede na obhajobu (časť 8).

## Zoznam úloh

Všetky otvorené úlohy na jednom mieste (podrobnosti v príslušnej časti).

**Pred pokusným odovzdaním (19. 11. 2026):**

- [ ] Overiť precedenčnú analýzu u cvičiaceho / na fóre (časť 4).
- [ ] Rozhodnúť návrh generátora: rozsahy, `DEFVAR`, buffery, volacia konvencia (časť 6).
- [ ] Doplniť jedinečné ID rozsahu do `Scope` (časť 6).
- [ ] Implementovať základ generátora: hlavička, `print`, výrazy, premenné,
  `if`, `while`, volania funkcií (časť 6).
- [ ] Otestovať výstup cez interpret `ic26int`, kód iba na `stdout` (časť 6).
- [ ] Hlavičky zdrojových súborov s autormi a popisom (časť 1).
- [ ] Vytvoriť `rozdeleni` a `rozsireni` (časť 8).

**Do finálneho odovzdania (27. 11. 2026):**

- [ ] Dokončiť generátor vrátane vstavaných funkcií a chyby 40 pri `subStr` (časť 6).
- [ ] Dokončiť FUNEXP (časť 4).
- [ ] Rozhodnúť kľúčové slová `Boolean`, `case`, `for`, … v scanneri (časť 4).
- [ ] Opraviť porovnanie `Unit == Unit` a poradie chýb medzi priechodmi (časť 5).
- [ ] Overiť na fóre: chyba 6 vs. 10 pri `return`, `1 < 2 < 3`, `val x`
  s parametrom `x` (časť 5).
- [ ] Uvoľnenie pamäte pri chybe (`current_tok`, symbolová tabuľka) (časť 1).
- [ ] End-to-end testy a skript v `tests/`, chybové vstupy z lokálnej sady (časť 7).
- [ ] Testy hraničných prípadov scanneru a tabuliek (časti 2, 3).
- [ ] Build a testy na serveri Merlin (časť 7).
- [ ] Drobné výnimky v pomenovaní (časť 7).
- [ ] Dokumentácia funkcií v `.h` (časť 8).
- [ ] LL gramatika a LL tabuľka, stavový diagram scanneru (časti 3, 4).
- [ ] `dokumentace.pdf`, `README.md`, záznam použitia AI (časť 8).
- [ ] Odpovede na obhajobu (časť 8).
- [ ] `is_it_ok.sh` a kontrola archívu (časť 8).
