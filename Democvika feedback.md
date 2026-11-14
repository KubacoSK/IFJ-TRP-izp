# Democvika feedback

Porovnanie projektu s demonštračným cvičením k projektu IFJ 2026/27Z (Ondřej Ondryáš).
Vychádza z automatického prepisu titulkov. Tvrdenia sú overené podľa slidov prednášok
(`Prednasky/Ifj01-en.md` až `Ifj11-en.md`) a špecifikácie IFJcode26; výsledok overenia je
v časti 8. Stav kódu k 14. 11. 2026.

- Časť 1: <https://www.youtube.com/watch?v=Fw6y4UPBCjs> (lexer, parser, precedenčná analýza, sémantika, tabuľka symbolov)
- Časť 2: <https://www.youtube.com/watch?v=lDos0kcR5CA> (IFJcode26, generovanie kódu, rozšírenia, kvalita kódu)

## 1. Najväčšie riziko: precedenčná analýza

Prednášajúci výslovne varuje (časť 1, ~58:00): precedenčnú analýzu treba implementovať podľa
algoritmu z prednášok. Iné metódy pod rovnakým názvom (napr. Shunting Yard) sú zakázané.
Zadanie (2.2) žiada precedenčnú analýzu, „která odpovídá výkladu v přednáškách“, a za
nedodržanie hrozí „značná ztráta bodů“.

`parse_expression_inner` v `parser.c` sa od algoritmu z prednášok líši:

| Algoritmus z prednášok | Náš kód |
|---|---|
| Jeden zásobník s terminálmi, neterminálom `E` a značkami `<` | Dva zásobníky: operátory a typy operandov |
| Identifikátor `i` je v precedenčnej tabuľke | Tabuľka 13×13 má len operátory, zátvorky a `$`; operandy sa načítajú mimo nej cez `parse_term` |
| Redukcia hľadá pravidlo medzi `<` a vrcholom (`E → i`, `E → E + E`, …) | Redukcia vyberie jeden operátor a dva operandy |

Pripomína to skôr dvojzásobníkové vyhodnocovanie výrazov (blízke Shunting Yard).

**Overené podľa prednášky 8 (Bottom-Up Parsing):** algoritmus na slidoch naozaj pracuje s jedným
zásobníkom, na ktorom sú terminály, `E` aj značka `<`; pri `>` hľadá reťazec `<y` na vrchu a
pravidlo `A → y`, inak hlási chybu. Tabuľka sa konštruuje aj pre identifikátor `i` (pravidlo 3:
„Identifiers“) a pre `$`. Naša implementácia je stále riadená tabuľkou (shift `<`, reduce `>`,
`=` pre zátvorky) a sémantická akcia pri redukcii zodpovedá prednáške 9, ale chýba jej `i`
v tabuľke, značky `<` a hľadanie pravidla. Slidy neriešia unárne operátory ani volania funkcií,
tie sú naša úprava a treba ich vedieť vysvetliť.

**Treba:** ukázať kód cvičiacemu alebo sa opýtať na fóre. Ak treba prerobiť, tabuľku a
gramatiku navrhnúť ručne (AI sa na formalizmy nesmie použiť, odporúča to aj prednášajúci).

## 2. Architektúra: AST, 3AC alebo priamo IFJcode26

- Zadanie postup **nepredpisuje**; povinné sú len konečný automat, rekurzívny zostup a precedenčná analýza.
- Prednášajúci za najprehľadnejšie považuje **AST → generátor**. Priame IFJcode26 je povolené,
  „ale můžou tam nastat komplikace“; odporúča generovať niečo podobné IFJcode26 a finálny výstup
  zložiť v ďalšom kroku (sedí s plánom bufferov pre každú funkciu).
- Nevýhoda priameho generovania: autor parsera musí dobre poznať výstupný jazyk.
- **My:** bez AST, bez 3AC, plánujeme priame generovanie. Na obhajobe treba vedieť zdôvodniť
  (pripravená odpoveď je v `ARCHITEKTURA_IFJ26.md`, „Prečo nemáte AST?“).
- **Overené podľa prednášky 9 (Syntax Directed Translation):** slidy uvádzajú tri základné prístupy:
  (1) parser vytvára AST → 3AC, (2) parser vytvára postfixovú notáciu → 3AC, (3) parser vytvára
  3AC priamo („Direct Generation of 3AC“, sémantická akcia `generate(...)` pri každej redukcii).
  Náš plán zodpovedá prístupu 3, takže je to metóda z prednášok, nie vlastný výmysel.
  Výraz sa tam prekladá post-order (napr. `a + b * c` → `*` pred `+`), čo sedí so zásobníkovými
  inštrukciami IFJcode26.

## 3. Analýza: stav oproti videu

| Téma z videa | Stav u nás |
|---|---|
| Rekurzívny zostup, „nevymýšľajte nové metódy“ | ✅ |
| Dvojpriechodová analýza s uloženými tokenmi je povolená, ale „škaredá“; lepšia je jednopriechodová s AST | Máme dvojpriechodovú; pripraviť zdôvodnenie |
| Odsadenie cez tokeny `INDENT` / `DEDENT` | ✅ jedna z dvoch spomenutých možností |
| Blokový komentár s novým riadkom = nový riadok, za ním nesmie nič byť | ✅ `verify_rest_of_multiline_line` |
| Vnorené komentáre: prečo to už nie je čistý konečný automat? | Pripraviť odpoveď na obhajobu |
| Do tabuľky symbolov vkladá parser, nie scanner | ✅ |
| Rozsahy platnosti ako zásobník tabuliek | ✅ `Scope` s ukazovateľom `parent` |
| Hash tabuľka s otvorenou adresáciou; pýtajú sa na parametre | djb2, 2039 slotov, lineárny krok; vedieť zdôvodniť prečo |
| Samostatný modul hash tabuľky pod `symtable` | ✅ povolené |

## 4. Generovanie kódu (zatiaľ neimplementované)

Rozhodnutia, ktoré treba urobiť pred písaním generátora:

1. **Rozsahy platnosti (časť 2, 11:46).** Rámce na to nestačia. Jeden lokálny rámec na funkciu
   a premenné premenovať podľa rozsahu (`x$1`, `x$2`). Číslo musí byť **jedinečné z počítadla**,
   nie hĺbka zanorenia. `Scope` v `symtable.h` takéto číslo zatiaľ nemá.
2. **`DEFVAR` na začiatok funkcie (27:46).** `DEFVAR` v cykle spadne pri druhom prechode
   (špecifikácia: redefinícia symbolu je chyba 52).
   Pri priamom generovaní: dva buffery na funkciu (`DEFVAR`-y a telo).
3. **Výrazy (16:13).** Zásobníkové inštrukcie (`PUSHS`, `ADDS`, …) sa dajú vypisovať pri redukcii
   v `parse_expression_inner`. Pozor na `Int → Double`: ľavý operand už nie je na vrchu zásobníka.
4. **Volacia konvencia (21:13).** Odporúča argumenty aj návratovú hodnotu na dátovom zásobníku
   (hlavne s FUNEXP). Návratová hodnota v `TF` je zlá, `POPFRAME` ju prepíše.
5. **Drobnosti:**
   - jedinečné návestia z počítadla (napr. `fun$while$3$end`),
   - `Unit` ako `nil@nil` – **pozor:** `WRITE` vypíše `nil` ako `nil`, ale `print` hodnoty `()`
     musí podľa špecifikácie vypísať `()`. Typ poznáme pri preklade, takže pre `Unit` treba
     generovať `WRITE string@()`,
   - desatinné literály cez `printf("%a")` (špecifikácia to potvrdzuje),
   - `print` → priamo `WRITE` pre `Int`, `Double`, `String` (`Double` sa vypíše cez `%a`);
     `toStr` pre `Double` → `FLOAT2STR`, ktorý píše vo formáte `%.2f`,
   - bez fungujúceho `WRITE` neprejde žiadny nechybový test.

## 5. Rozšírenia

- **FUNEXP silno odporúča** – hlavne úpravy precedenčnej analýzy, zároveň rieši nejednoznačnosť
  priradenia. `parse_term` už volania vo výrazoch prijíma → oplatí sa dokončiť.
- Jednoduchšie: **PARAMLISTS**, **EKTKW**, **VALMEM** (VALMEM a PARAMLISTS sa hodia k FUNEXP).
- Náročné: **LISTS**, **ALGEBDT**, **LAMBDAS** – treba s nimi počítať od začiatku.

## 6. Kvalita kódu

| Požiadavka | Stav u nás |
|---|---|
| Jednotné pomenovanie | ✅ tri drobné výnimky (`Token_type`, `Token_attribute`, `p_toStr`…, makro `current_tok`) |
| Formátovanie nástrojom | ✅ LLVM na vetve `formatovanie-llvm`, treba zlúčiť |
| Hlavička každého súboru: autor a popis, všade rovnaká | ❌ chýba |
| Dokumentácia funkcií v `.h`, ideálne Doxygen | Prejsť všetky `.h` |
| Žiadne duplicitné implementácie (napr. viac zásobníkov) | Generátor má použiť spoločný zásobník/buffer |
| Tímová spolupráca: každý má rozumieť celku, robiť si navzájom review | Priebežne |

## 7. Testovanie

- Chybové testy kontrolujú iba návratový kód; niektoré prijímajú viac kódov.
- Na `stdout` smie ísť iba vygenerovaný IFJcode26, ladiace výpisy na `stderr`.
- Testy rozšírení overujú funkčnosť, nie chybové hlásenia.

## 8. Overenie podľa prednášok a špecifikácie

| Finding | Zdroj | Výsledok |
|---|---|---|
| Precedenčná analýza sa líši od algoritmu z prednášok | Prednáška 8 | **Potvrdené.** Slidy majú `i` v tabuľke, značky `<` a redukciu podľa pravidla |
| Priame generovanie bez AST je povolené | Prednáška 9 | **Potvrdené a posilnené.** Je to prístup 3 („Direct Generation of 3AC“) |
| Parser simuluje derivačný strom, strom fyzicky nevzniká | Prednáška 2 | Potvrdené („Parse tree simulation“) |
| Rekurzívny zostup: jedna funkcia na neterminál | Prednáška 7 | Potvrdené |
| Rozsahy platnosti ako zásobník tabuliek symbolov | Prednáška 5 („Scope Rules“) | Potvrdené, zodpovedá nášmu `Scope` |
| Scanner nemá pracovať s tabuľkou symbolov | Prednáška 5 | **Rozpor.** Slidy medzi úlohy scannera uvádzajú „communication with symbol tables“; video to neodporúča. Náš scanner s ňou nepracuje, čo je v poriadku, len to vedieť zdôvodniť |
| Dvojpriechodová vs. jednopriechodová analýza | Prednášky | Slidy to nerozoberajú, je to len názor z videa |
| Unárne operátory, volania funkcií vo výrazoch, vnorené komentáre | Prednášky | Slidy ich nepokrývajú; sú to naše úpravy |
| `DEFVAR` v cykle spadne | Špecifikácia | Potvrdené (chyba 52) |
| `%a` pre desatinné literály a `WRITE` | Špecifikácia | Potvrdené |
| `Unit` ako `nil@nil` | Špecifikácia | **Doplnené:** `print(())` musí vypísať `()`, nie `nil` |
| `toStr` pre `Double` cez `FLOAT2STR` | Špecifikácia | Potvrdené, formát `%.2f` |

## 9. Čo urobiť

- [ ] Overiť precedenčnú analýzu u cvičiaceho / na fóre (bod 1).
- [ ] Rozhodnúť volaciu konvenciu a reprezentáciu rozsahov pred písaním generátora (bod 4).
- [ ] Doplniť jedinečné číslo rozsahu do `Scope`.
- [ ] Rozhodnúť a dokončiť FUNEXP.
- [ ] Hlavičky súborov s autormi, dokumentácia funkcií v `.h`.
- [ ] Zlúčiť vetvu `formatovanie-llvm`.
- [ ] Pripraviť odpovede na obhajobu: prečo bez AST, prečo dva priechody, konečný automat a vnorené komentáre, parametre hash tabuľky.
