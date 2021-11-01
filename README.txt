Task 1 
	Citim fiecare instructiune cu fgets si o spargem in componente cu strtok.
	Preluam valorile y , x , d si le convertim in int .
	Punem cuvintele in game_board cu ajutorul functiilor  put_orizontal si  put_vertical .

Task 2 
	Citirea se face exact ca la taskul 1, iar punctele le adaugam la fiecare player cu regula data care se afla in functua pct_cuv.

Task 3 
	Dupa citire calculam pentru fiecare cuvant bonusul si il inmultim cu punctele date de cuvant, acest lucru fiind facut in functi pct .
Task 4 
	Apelam cerinta de la taskul 1 si retinem o lista cu cuvintele puse in matrice in variabila list_cuv, dar si numarul de cuvinte in variabila nr_cuv care sunt transmise 
ca parametru in functia do_task_1.
	Luam fiecare cuvant din lista words si verificam sa nu se afle in list_cuv . Cautam in matricea game_board toate aparitiile primei litere a cuvantului 
si verificam daca poate fi pusa in matrice cu ajutorul functiilor put_word_orizontal si put_word_vertical . Daca poate fi pus, va fi plasat in matrice cu functiile
put_vertical si put_orizontal.
 
Taskul 5 
	Punem cuvintele pe game_board si calculam punctajele  fiecarui jucator . Dupa aceea verificam pt fiecare cuvant din words fiecare loc din matrice unde poate fi pus si vedem 
ca prin plasarea sa castigul sa fie maximal . Daca castigul dat de plasarea unui cuvant este ce-a mai mare de pana acum il memoram.
	Daca castigul maxim calculat anterior este mai mare sau egal cu W - T, deci ofera castigul sau remiza vom pune cuvantul si vom afisa game_boardul, in caz contrar afisam "Fail!"