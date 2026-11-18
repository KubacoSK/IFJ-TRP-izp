# Prompty pouzite na vygenerovanie testov pre parser (Gemini)

## 01_normal_valid

1. `01_minimal_program`
Prompt: "sprav mi najjednoduchsi program pre parser len import ifj26.* a @main funkcia co vracia () nech viem ci prejde uplny zaklad"

2. `02_function_definitions`
Prompt: "potrebujem otestovat definicie funkcii v parseri jednoriadkove aj viacriadkove s navratovym typom aj bez neho a ked je @main na samostatnom riadku"

3. `03_variables_and_assignments`
Prompt: "sprav mi test na premenne val a var s typom Int Double String Unit aj bez uvedeneho typu a potom prepriradenie hodnoty do var"

4. `04_function_calls_places`
Prompt: "v zadani je 5 miest kde sa moze volat funkcia samostatne pri inicializacii v priradeni v jednoriadkovej funkcii a v return tak mi sprav test kde je vsetkych 5"

5. `05_if_else_statements`
Prompt: "sprav mi normalny test na if then else a aj ked je jeden if vnoreny v druhom"

6. `06_while_loops`
Prompt: "potrebujem test na while do cyklus a vnoreny while cyklus v nom"

7. `07_expressions_precedence`
Prompt: "sprav mi test na precedencnu analyzu vyrazov nech tam je scitanie odcitanie nasobenie delenie zatvorky unarny minus spajanie stringov a porovnavania v ife"

8. `08_return_and_block_results`
Prompt: "otestuj mi return ked vracia vyraz ked je len samotny return vo funkcii Unit a ked funkcia vracia posledny vyraz v bloku bez return"

## 02_edge_cases_valid

9. `01_semicolon_separators`
Prompt: "a teraz edgecase pre parser v zadani je ze viac prikazov na jednom riadku sa da oddelit bodkociarkou ; tak mi sprav na to test"

10. `02_trailing_commas_newlines`
Prompt: "sprav edgecase na koncovu ciarku za poslednym parametrom funkcie a argumentom ked je za nou novy riadok a zatvorka )"

11. `03_multiline_expressions_in_parens`
Prompt: "mimo zatvoriek vyraz nemoze ist na dalsi riadok ale v zatvorkach () to prejst musi tak mi sprav edgecase s vyrazom rozdelenym na viac riadkov v zatvorkach"

12. `04_unary_minus_combinations`
Prompt: "sprav mi edgecase na unarny minus vo vyrazoch napr -a alebo -(a - 3) alebo a * -2 a a - -5 ci to precedencna tabulka spravne zoberie"

13. `05_deep_nesting_and_empty_blocks_unit`
Prompt: "v zadani je ze prazdny blok sa pise cez () tak sprav viac vnorenych while a if else kde su v niektorych vetvach len ()"

14. `06_standalone_expressions_as_statements`
Prompt: "v sekcii 2.1 sa pise ze prikazom je aj samostatne stojace vyhodnotenie vyrazu tak sprav test kde je v bloku len tak napisane x + 100 alebo 42 alebo 1 + 2 * 3"

15. `07_funexp_calls_in_expressions`
Prompt: "mame spravene aj rozsirenie FUNEXP cize volanie funkcie moze byt sucastou vyrazu argument moze byt vyraz a volania sa daju vnorovat sprav mi na to test pre parser podla prikladu zo zadania"

## 03_syntax_errors

16. `01_err_missing_prolog`
Prompt: "teraz potrebujem syntakticke chyby co maju vracat kod 2 sprav prvy test kde uplne chyba prolog import ifj26.*"

17. `02_err_wrong_prolog_target`
Prompt: "sprav chybovy test kde je prolog zle napisany napr import ifj26.print namiesto hviezdicky"

18. `03_err_duplicate_prolog`
Prompt: "prolog musi byt uvedeny prave raz sprav test kde je import ifj26.* dvakrat za sebou"

19. `04_err_top_level_statement`
Prompt: "za prologom mozu byt na najvyssej urovni len definicie funkcii sprav test kde je globalna premenna val mimo funkcie nech to hodi chybu 2"

20. `05_err_at_main_on_variable`
Prompt: "sprav test kde dam @main pred premennu val namiesto pred def funkciu"

21. `06_err_param_missing_type`
Prompt: "parameter funkcie musi mat tvar id : typ sprav chybovy test def foo(x) kde chyba typ parametra"

22. `07_err_func_missing_assign`
Prompt: "sprav test kde v hlavicke funkcie def chyba rovna sa = pred telom"

23. `08_err_trailing_comma_same_line_params`
Prompt: "koncova ciarka je povolena len ked je za nou novy riadok pred ) tak sprav chybovy test def foo(a: Int, ) na jednom riadku"

24. `09_err_trailing_comma_same_line_args`
Prompt: "to iste s koncovou ciarkou na jednom riadku sprav aj pri volani funkcie print(1, )"

25. `10_err_empty_list_comma`
Prompt: "koncova ciarka moze byt len v neprazdnom zozname sprav chybovy test kde je v zatvorkach len samotna ciarka readInt( , )"

26. `11_err_var_uninitialized`
Prompt: "pri val a var je inicializacia povinna sprav chybovy test var x: Int bez = hodnoty"

27. `12_err_assign_to_expression`
Prompt: "na lavej strane priradenia musi byt len id premennej sprav chybovy test a + b = 10"

28. `13_err_func_call_missing_rparen`
Prompt: "sprav chybovy test na volanie funkcie kde chyba uzatvaracia zatvorka add(1, 2"

29. `14_err_func_call_double_comma`
Prompt: "sprav chybovy test kde su pri volani funkcie dve ciarky za sebou bez argumentu add(1, , 2)"

30. `15_err_func_def_missing_parens`
Prompt: "funkcia bez zatvoriek def answer: Int = 42 je povolena az v rozsireni PARAMLISTS tak sprav chybovy test nech to bez zatvoriek hodi chybu 2"

31. `16_err_if_without_else`
Prompt: "v zadani je vetva else pri if povinna sprav chybovy test kde je if bez else"

32. `17_err_if_missing_then`
Prompt: "sprav chybovy test kde v if podmienke zabudnem napisat then"

33. `18_err_if_as_expression`
Prompt: "bez rozsirenia CONTROL sa if neda pouzit ako vyraz sprav chybovy test val x = if a > 0 then 1 else 0"

34. `19_err_else_misaligned`
Prompt: "else musi byt odsadene presne tak isto ako if sprav chybovy test kde je else posunute viac doprava"

35. `20_err_while_missing_do`
Prompt: "sprav chybovy test na while cyklus kde za podmienkou chyba slovo do"

36. `21_err_empty_block_body`
Prompt: "bloky nemozu byt prazdne sprav chybovy test kde za if x > 0 then nic nie je a hned ide else"

37. `22_err_inconsistent_block_indent`
Prompt: "vsetky prikazy v tom istom bloku musia mat rovnake odsadenie sprav test kde je druhy riadok v bloku odsadeny viac"

38. `23_err_curly_braces_block`
Prompt: "zlozene zatvorky {} nie su v IFJ26 podporovane na bloky sprav s nimi chybovy test"

39. `24_err_double_semicolon`
Prompt: "bodkociarka oddeluje prikazy na riadku sprav chybovy test kde su dve bodkociarky za sebou val x = 1;; val y = 2"

40. `25_err_expr_missing_operand`
Prompt: "teraz chyby vo vyrazoch sprav test kde su dva operatory za sebou val x = 1 + * 2"

41. `26_err_expr_trailing_operator_newline`
Prompt: "neukonceny vyraz mimo zatvoriek nemoze pokracovat na dalsom riadku sprav chybovy test kde riadok konci 1 + a na dalsom je 2"

42. `27_err_expr_leading_operator_newline`
Prompt: "logicky riadok nemoze zacinat operatorom sprav chybovy test kde dalsi riadok zacina + 2"

43. `28_err_expr_unbalanced_parens`
Prompt: "sprav chybovy test na neuzavretu zatvorku vo vyraze"

44. `29_err_expr_empty_parens_in_arith`
Prompt: "sprav chybovy test kde su prazdne zatvorky s medzerou v nasobeni val x = ( ) * 5"

45. `30_err_chained_relational_operators`
Prompt: "relacne operatory sa v IFJ26 nedaju retazit za sebou lebo nemaju asociativitu sprav chybovy test na if a < b < c then"
