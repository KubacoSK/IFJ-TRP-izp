# Progress projektu IFJ a IAL (variant TRP-izp)

Posledná aktualizácia: 26. 11. 2026 večer (vetva `Finalne-upravy`, commit
`dca97b0`, kontrola pred finálnym odovzdaním)

## Legenda

- [x] Hotové a pokryté aktuálnym kódom alebo testami
- [~] Rozpracované / implementované iba čiastočne
- [ ] Ešte treba dorobiť

## Aktuálny stav

- Prekladač je funkčný celok: scanner → parser (syntax + sémantika) →
  generátor IFJcode26 priamo z parsera → výpis až po úspešnej analýze.
- Build v WSL Ubuntu (gcc 13.3) s `-Wall -Wextra -pedantic -std=c99` je bez
  warningov (cez `make` aj ručne, aj s `-O2`). Preklad na gcc 14/15/16
  (Merlin) zatiaľ nie je overený.
- Unit testy prechádzajú: scanner 55/55, hash tabuľka 26/26, tabuľka
  symbolov 27/27 (`make test`; `test_hashtable.c` má 28 známych warningov
  `-Wpointer-sign`). Pod `valgrind` aj ASan/UBSan bez chýb a únikov.
- End-to-end testy prechádzajú: 184/184 (`make test_e2e`, `tests/e2e.sh`,
  preklad → `ic26int` → porovnanie výstupu a návratových kódov).
- Adamove testy: návratový kód prekladača 101/104 (3 sporné kódy, časti 3
  a 5), codegen testy cez interpret 26/26 vrátane výstupu a kódov 40, 57, 58.
- `valgrind` je čistý na úspešnom preklade aj na chybových cestách (kódy 1–7,
  chyba počas analýzy na požiadanie, chyba vo vnorenom výraze).
- **Chýba dokumentácia:** `dokumentace.pdf` má 0 B (časť 8).
- Pri chybe prekladu je `stdout` prázdny; kód nepoužíva súbory, sieť ani
  podprocesy, iba štandardnú knižnicu C.
- Rozšírenie FUNEXP je implementované a uvedené v súbore `rozsireni`.
- **Pokusné odovzdanie (19. 11.): 13–18 b.** Základ prešiel celý okrem 3 testov
  (ERR_SYN 64 a 82, BASE_LEXSYN 199). Opravené v `0194d7f` a `58f5c91`:
  neuzavretá zátvorka pred menej odsadeným riadkom → 2, komentár `/* */` na
  začiatku riadku nemení odsadenie, `{` a `}` → 2. Overené vlastnými programami
  (preklad + interpret).

## 1. Príprava a architektúra

- [x] Vytvorenie / nastavenie spoločného Git repozitára.
- [x] Dohodnutie pravidiel práce: Conventional Commits, pull requesty a code review.
- [x] `Makefile` s cieľmi `all` (predvolený, `ifj26`), `build`, `test`,
  `test_scanner`, `test_ht`, `test_symtable`, `test_e2e`, `test_adam`
  (`adam`), `check`, `build-check`, `clean`.
- [x] Architektúra bez AST: parser riadi preklad a generátor vypisuje kód
  priamo pri rozpoznaní konštrukcie (prednáška 9, prístup 3).
- [x] Dátové štruktúry tokenov, hash tabuľky a tabuľky symbolov.
- [x] Celý tok parser → sémantika → generovanie kódu je prepojený.
- [x] Bez `tmpfile()`: 1. priechod načíta všetky tokeny do poľa v pamäti
  (lexikálna chyba ako zarážka, vráti sa až keď k nej parser dôjde),
  2. priechod ide po tom istom poli. Scanner číta stdin iba raz.
- [x] Uvoľnenie pamäte aj pri chybe (pole tokenov, symbolová tabuľka, buffery
  generátora), overené `valgrind`.
- [ ] `hashtable.h`: `#include` a `#define HT_CAPACITY` sú pred
  `#ifndef _HASHTABLE_H`; meno makra s `_` + veľkým písmenom je v C
  rezervované.

## 2. Hash tabuľka a tabuľka symbolov (IAL)

### Hash tabuľka

- [x] Hashovacia funkcia djb2, otvorená adresácia s dvojitým rozptyľovaním:
  začiatok `hash % 4093`, krok `hash % 4092 + 1` (4093 je prvočíslo, takže
  sa prejdú všetky sloty), stavy `EMPTY`, `OCCUPIED`, `DELETED`.
- [x] `ht_init`, `ht_insert`, `ht_search`, `ht_delete`, `ht_clear`.
- [x] Unit testy (26/26).
- [ ] Pevná kapacita `HT_CAPACITY 4093` bez zväčšovania: viac ako ~4093
  premenných v jednom bloku alebo funkcií vráti 99, hoci 99 má byť iba chyba
  neovplyvnená vstupom.

### Tabuľka symbolov

- [x] Typy `DataType`, `SymbolKind`, `Param`, `VarData` (s jedinečným `id`),
  `FuncData`.
- [x] Globálna tabuľka funkcií, lokálne scopes s rodičom, zatienenie.
- [x] Jedinečné ID premennej z počítadla (`next_var_id`) pre premenovanie
  `LF@meno$ID`.
- [x] Vstavané funkcie vložené do tabuľky.
- [x] Unit testy (27/27) vrátane jedinečných ID.
- [ ] `symtable_add_builtins` vracia `void` a výsledky `symtable_add_func`
  nekontroluje, takže `main.c` zlyhanie alokácie nezistí (pri použití
  chýbajúcej vstavanej funkcie by prekladač vrátil 3 namiesto 99).
- [x] `symtable_push_scope` v `parser.c` a `str_dup` mena parametra
  v `symtable_add_func` sa kontrolujú (overené 26. 11.).
- [x] Symtable je skrytý ADT (`symtable_create` / `symtable_free`, `978a84b`),
  parser už nepristupuje priamo k `current_scope`.

## 3. Lexikálna analýza / scanner

- [x] Identifikátory, kľúčové slová, `_`, celé a desatinné literály
  (exponent, `_`, sufix `d/D`), jedno- a viacriadkové reťazce s escape
  sekvenciami, operátory, `@main`, vnorené komentáre, `INDENT` / `DEDENT`,
  `had_preceding_newline`.
- [x] Unit testy scanneru (55/55), vrátane zátvoriek a `{` / `}`.
- [x] Desatinný literál mimo rozsahu Double (`1e999`) → lexikálna chyba 1
  (`ERANGE` / `HUGE_VAL` po `strtod`).
- [x] V zátvorkách: pokračovací riadok odsadený rovnako alebo menej ako logický
  riadok → scanner vráti EOL a parser hlási 2 (`)` smie byť na rovnakom
  odsadení, napr. za koncovou čiarkou).
- [x] Jednoriadkový `/* */` na začiatku riadku je biely znak, odsadenie určujú
  iba medzery pred ním.
- [x] `{` a `}` sú tokeny, parser ich zamietne chybou 2.
- [ ] Odsadenie hlbšie ako 127 úrovní vráti 99 (`MAX_INDENT_LEVELS`).
- [x] Skutočný tabulátor v jednoriadkovom reťazci a `"""a""""` (úvodzovky
  navyše na konci patria do reťazca, výsledok `a"`) prechádzajú
  (overené 26. 11.).
- [ ] `val x = 5.` vráti 2, Adamov test `09_err_double_trailing_dot` čaká 1
  (špecifikácia 1.1: desatinná časť za bodkou je povinná).
- [ ] Samotné `_` (`val _ = 5`) vráti 2, Adamov test `04_err_lone_underscore`
  čaká 1, ale pripúšťa aj 2.

## 4. Syntaktická analýza / parser (Dominik)

- [x] Rekurzívny zostup, dvojpriechodový (hlavičky → telá).
- [x] Prolog `import ifj26.*` (aj s bielymi znakmi medzi tokenmi), iba
  definície funkcií na najvyššej úrovni, `@main` na rovnakom aj samostatnom
  riadku.
- [x] Parametre, návratové typy, koncová čiarka iba pred novým riadkom.
- [x] Bloky cez `INDENT` / `DEDENT`, prázdny blok je chyba 2.
- [x] `val` / `var`, priradenie, volanie ako príkaz, samostatný výraz,
  stredník, `if … then … else`, `while … do`, `return [výraz]`.
- [x] Precedenčná analýza podľa prednášky 8: jeden zásobník s terminálmi,
  `E` a značkami `<`, `i` v tabuľke, redukcia hľadá pravidlo
  (`E → i`, `E → u E`, `E → ( E )`, `E → ( )`, `E → E op E`).
- [x] `==` a `!=` sú v tabuľke na rovnakej úrovni ako `<`, `<=`, `>`, `>=`
  (celý blok 6×6 je chyba), hoci špecifikácia im dáva nižšiu prioritu.
  Platné programy to neovplyvní, lebo zreťazenie je zakázané; zmiešaný
  reťazec `1 < 2 == 3 < 4` vráti 2. Na obhajobe vedieť zdôvodniť.
- [x] Mimo slidov (vedieť vysvetliť): volanie `id(` sa spracuje pri presune
  `i`, unárny operátor sa rozpozná podľa vrcholu zásobníka.
- [x] Unárne `+` / `-`, zátvorky, `()` ako literál `Unit`.
- [x] Logický riadok nesmie začínať operátorom (za `;` je povolené).
- [x] FUNEXP: volania vo výrazoch a výrazy v argumentoch, vnorené volania,
  vyhodnocovanie zľava doprava.
- [x] Hlboké výrazy: 100 000 vnorených zátvoriek aj výraz s 200 000 členmi
  prejdú.
- [ ] Hlboko vnorené volania `f(f(…))` (~50 000 úrovní) spadnú na
  segfault (rekurzia); 20 000 prejde.

## 5. Sémantická analýza (Dominik)

- [x] Nedefinovaná premenná/funkcia/typ (3), redefinícia premennej/funkcie,
  duplicitné parametre (4).
- [x] Typová kontrola výrazov, inicializácie, priradení, argumentov a návratu
  vrátane `Int → Double`.
- [x] Zápis do `val` a do parametra (7).
- [x] Počet a typy argumentov vstavaných aj užívateľských funkcií (5).
- [x] `@main`: chýbajúci (3), viacnásobný (4), s parametrami (5), iný
  návratový typ ako `Unit` (6).
- [x] Boolean iba v podmienke `if` / `while` (inde 6).
- [x] Explicitný `Unit`: hodnota `return` a tela sa zahodí.
- [x] `return` vo funkcii bez explicitného typu (6).
- [x] Odvodený návratový typ, analýza na požiadanie pri volaní pred
  definíciou, rekurzia bez typu (6) cez stav „prebieha“ a graf volaní.
- [x] Pravidlá pre `if` na konci tela funkcie, rekurzívne pre vnorený `if`.
- [x] `() == ()` a `() != ()` prechádzajú.
- [x] Zreťazenie `1 < 2 < 3` vráti 2.
- [ ] `val x = ( ) * 5` vráti 6 (`( )` sa berie ako `Unit`), Adamov test
  `29_err_expr_empty_parens_in_arith` čaká 2, ale pripúšťa aj 6.
- [ ] Poradie chýb: 1. priechod nájde lexikálnu chybu a duplicitnú funkciu
  skôr než 2. priechod (syntaktická chyba pred neukončeným reťazcom vráti 1;
  chýbajúci prolog + duplicitná funkcia vráti 4 namiesto 2).

## 6. Generovanie cieľového kódu IFJcode26 (Jakub)

Rozhodnutia (implementované):

- [x] Priame generovanie z parsera, zásobníkové inštrukcie.
- [x] Argumenty aj návratová hodnota cez dátový zásobník, rámec vytvára volaná
  funkcia (`CREATEFRAME`, `PUSHFRAME` v prológu).
- [x] Premenné `LF@meno$ID`, všetky `DEFVAR` na začiatku funkcie (buffer
  `defs`), žiadna chyba 52 pri premenných v cykloch.
- [x] Pomocné premenné lokálne `LF@%t1`, `LF@%t2`.
- [x] Vstupný bod `CALL $f$<main>`, `CLEARS`, `EXIT int@0`; výpis až na konci.
- [x] Každý príkaz nechá na zásobníku 1 hodnotu, pred ďalším sa zahodí.
- [x] `Unit` = `nil@nil`, `print(())` vypíše `()`.
- [x] Statická konverzia `Int → Double`, `<=` / `>=` ako `(a < b) OR (a == b)`,
  `Int / Int` cez `IDIVS`, `+` reťazcov cez `CONCAT`.
- [x] Literály `int@`, `float@%a`, `string@` s escape `\xyz`.
- [x] Vstavané funkcie: inline `print`, `toStr`, `toInt`, `chr`,
  `strLength`; knižnica `$b$` `readLine`, `readInt`, `readDouble`, `ord`,
  `subStr` (chyba 40 vo všetkých 5 prípadoch). Knižnica sa vypíše vždy celá.
- [x] Otestované cez `ic26int` (e2e aj Adamove codegen testy), kód iba na
  `stdout`.

- [x] `readInt` mimo rozsahu Int vráti 0 (`$b$readInt` porovná s 32-bit
  hranicami); test `readint_pretecenie` očakáva `0|0|0`, vlastný program so
  vstupmi `2147483647`, `2147483648`, `9999…`, `12a`, ` 5` dá
  `2147483647|0|0|0|0`.
- [x] `readLine` pri EOF: `$b$readLine` kontroluje `nil` z `READ` a vráti `""`.
- [ ] Pretečenie Int nemá 32-bitovú sémantiku Scaly (`2147483647 + 1` →
  `2147483648`, `toInt(1e20)` → 64-bitová hodnota).
- [ ] Literál `-2147483648` sa vo Windows verzii vypíše ako `-2147483647`.

## 7. Testovanie, kvalita a ladenie

- [x] Unit testy hash tabuľky, tabuľky symbolov a scanneru (108).
- [x] Adamove testy `tests/{scanner,parser,codegen}/**` (104). `make test_adam`
  kontroluje iba návratový kód prekladača: 101/104, sporné sú 3 kódy
  (časti 3 a 5). Codegen testy cez `ic26int` 26/26 vrátane výstupu.
- [x] End-to-end skript `tests/e2e.sh` (184 testov): parser, precedenčná
  analýza, literály, výrazy, riadenie toku, funkcie, vstavané funkcie,
  príklady zo špecifikácie.
- [x] Warning-free build, `valgrind` čistý.

## 8. Dokumentácia a odovzdanie

- [x] Súbor `rozdeleni` (súčet 100 %: 23, 23, 23, 31) a `rozsireni`
  (`FUNEXP`), v gite s LF.
- [x] Hlavičky s menami a loginmi vo všetkých 14 súboroch `.c` / `.h`.
- [x] **POKUSNÉ ODOVZDANIE** do 19. novembra 2026 23:59:59 (13–18 b).


## Zoznam úloh

**Pred pokusným odovzdaním (19. 11. 2026):** hotové

- [x] `rozsireni` (`FUNEXP`) a `rozdeleni` (časť 8).
- [x] `readInt` mimo rozsahu Int a test `readint_pretecenie` (časť 6).
- [x] Kontrola `nil` v `readLine` pri EOF (časť 6).
- [x] `1e999` ako lexikálna chyba 1 (časť 3).
- [x] `clang-format` na súboroch prekladača (časť 1).

**Po pokusnom odovzdaní:** hotové

- [x] Neuzavretá zátvorka, `/* */` na začiatku riadku, `{` / `}` (časť 3).
- [x] Dopridavanie ulozenych AI komentarov do finalneho odovzdania
- [x] `clang-format` (LLVM) na všetkých súboroch `.c` / `.h` vrátane testov
  (26. 11.).

**Pred finálnym odovzdaním (27. 11. 2026 11:59):**

- [x] `dokumentace.pdf` a jej zdroj v gite (časť 8).
- [x] Archív s LF a kontrola is_it_ok.sh na Merlinovi (časť 8).
