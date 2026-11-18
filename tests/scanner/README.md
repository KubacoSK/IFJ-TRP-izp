# Prompty pouzite na vygenerovanie testov pre scanner (Gemini)

## 01_normal_valid

1. `01_prolog_and_main`
Prompt: "dobre tu mas zo zadania ze program zacina import ifj26.* a potom tam musi byt @main def a navratovy typ Unit co sa pise ako () sprav mi na to prvy zakladny test .in a .out"

2. `02_keywords_and_identifiers`
Prompt: "tu su klucove slova zo zadania def do Double else if import Int return String then Unit val var while a identifikator zacina pismenom alebo podciarkovnikom sprav mi test kde budu vsetky tieto klucove slova a nejake normalne identifikatory"

3. `03_int_literals`
Prompt: "potrebujem test na cele cisla Int podla zadania tam mozu byt podciarkovniky medzi cislicami ako 1_000_000 a zaporne cisla cez minus sprav mi na to .in a .out"

4. `04_double_literals`
Prompt: "teraz sprav test na desatinne cisla Double mozu byt normalne s bodkou alebo len .5 bez celej casti potom s exponentom e alebo E plus minus a na konci male d alebo velke D"

5. `05_string_literals`
Prompt: "sprav mi test na stringy klasicke v uvodzovkach kde su escape sekvencie \\ \" \n \r \t a potom aj ten viacriadkovy string s troma uvodzovkami """ "

6. `06_operators_and_delimiters`
Prompt: "potrebujem otestovat vsetky operatory + - * / potom porovnavanie < <= > >= == != priradenie = a zatvorky dvojbodku ciarku bodkociarku nech viem ci to scanner berie"

7. `07_comments_and_whitespace`
Prompt: "sprav mi test na komentare riadkove // a blokove /* */ aj vnorene blokove komentare v sebe ci ich scanner normalne preskoci"

8. `08_indentation_blocks`
Prompt: "v zadani su bloky riesene cez odsadenie medzerami tak mi sprav jednoduchy test s funkciou a if else nech to otestuje indent a dedent"

9. `09_complete_program`
Prompt: "daj mi do testu aj ten cely priklad na factorial co je v zadani na strane 5 nech mame otestovany cely normalny program"

## 02_edge_cases_valid

10. `01_identifiers_case_and_keywords`
Prompt: "dobre a teraz z tych identifikatorov a klucovych slov sprav edgecase lebo v zadani je ze zalezi na velkosti pismen a ze samotne _ nie je identifikator ale __ alebo _a uz hej a takisto main bez zavinaca"

11. `02_numbers_tricky_valid`
Prompt: "sprav mi nejaky edgecase na cisla co by este malo prejst bez chyby napr .0 alebo 0e0 alebo ked napisem 10-5 bez medzier alebo komentar priamo medzi cislami 1/*komentar*/+2"

12. `03_multiline_strings_edge`
Prompt: "v zadani pisu ze vo viacriadkovom stringu """ sa escape sekvencie nevyhodnocuju a berie to vsetky znaky tak sprav edgecase kde je vo vnutri jedna uvodzovka alebo dve "" a aj nejake \a \0 co by v normalnom stringu padlo ale tu to musi prejst"

13. `04_nested_comments_edge`
Prompt: "sprav mi edgecase na komentare kde je viacurovnovy vnoreny komentar /* /* /* */ */ */ a potom komentar bez medzier val/*c1*/x=10 a // vo vnutri blokoveho komentara"

14. `05_parens_multiline_and_trailing_comma`
Prompt: "tu je v zadani ze novy riadok vo vnutri zatvoriek () sa berie ako biely znak a ze za poslednym parametrom moze byt koncova ciarka ak je za nou novy riadok a ) sprav mi na to edgecase test"

## 03_lexical_errors

15. `01_err_unknown_chars`
Prompt: "teraz potrebujem chybove testy co maju hodit chybu 1 sprav prvy test kde je nejaky neznamy znak napr dolar $ mimo stringu"

16. `02_err_at_symbol_space`
Prompt: "v zadani je ze medzi @ a main nesmie byt ziadny znak sprav test kde je medzera @ main nech to hodi chybu 1"

17. `03_err_at_symbol_other_id`
Prompt: "znak @ sa v inom kontexte ako @main nepouziva tak sprav test kde je napr @override nech to skonci s chybou 1"

18. `04_err_lone_underscore`
Prompt: "samotny podciarkovnik _ nie je identifikator v zakladnom zadani sprav test val _ = 5 co ma hodit chybu 1"

19. `05_err_int_leading_zero`
Prompt: "nenulovy celociselny literal nesmie zacinat nulou sprav test na cislo 0123 nech to vrati chybu 1"

20. `06_err_int_double_zero`
Prompt: "sprav este jeden test na nuly kde je 00 lebo ani to nemoze byt"

21. `07_err_int_trailing_underscore`
Prompt: "podciarkovnik v cisle moze byt len medzi dvoma cislicami sprav chybovy test kde je podciarkovnik na konci cisla 1_000_"

22. `08_err_int_unsupported_base_or_suffix`
Prompt: "ine ciselne sustavy ako 0x1F a sufix L ako 100L nie su podporovane sprav na to chybovy test"

23. `09_err_double_trailing_dot`
Prompt: "pri double musi byt za bodkou desatinna cast takze samotne 5. nie je platne sprav na to test co hodi chybu 1"

24. `10_err_double_empty_exponent`
Prompt: "za e alebo E v exponente musi byt aspon jedna cislica sprav chybovy test na 1.5e+ bez cislice"

25. `11_err_double_invalid_underscore`
Prompt: "sprav chybovy test na double kde je podciarkovnik rovno pred bodkou 1_.5"

26. `12_err_double_float_suffix`
Prompt: "sufixy f a F pri desatinnych cislach nie su podporovane sprav test na 1.5f nech to hodi chybu 1"

27. `13_err_string_invalid_escape`
Prompt: "v stringu su povolene len \\ \" \n \r \t a ina escape sekvencia je chyba 1 sprav test kde je v stringu \a"

28. `14_err_string_unterminated_newline`
Prompt: "jednoriadkovy string nesmie obsahovat normalny koniec riadku enter sprav test s neukoncenym stringom na viac riadkov"

29. `15_err_multiline_string_unterminated`
Prompt: "sprav test na neukonceny viacriadkovy string """ kde na konci suboru su len dve uvodzovky "" namiesto troch"

30. `16_err_comment_unterminated_nested`
Prompt: "sprav test na neukonceny vnoreny komentar kde sa otvoria dva /* /* ale zatvori sa len jeden */ pred koncom suboru"

31. `17_err_multiline_comment_trailing_token`
Prompt: "v zadani pisu ze ked je v blokovom komentari novy riadok tak za jeho koncom */ uz nesmu byt dalsie tokeny na tom istom riadku sprav na to chybovy test"

32. `18_err_indentation_tab`
Prompt: "na odsadenie sa pouzivaju len medzery a tabulator na zaciatku riadku je lexikalna chyba 1 sprav na to test"

33. `19_err_indentation_inside_parens`
Prompt: "vo vnutri zatvoriek musi byt dalsi riadok odsadeny viac ako zaciatok toho logickeho riadku sprav test kde to vo vnutri () nie je odsadene viac"
