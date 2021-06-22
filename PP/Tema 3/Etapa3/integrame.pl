:- ensure_loaded('checker.pl').

%test_mode(detailed).

% Considerăm următoarele reprezentări:
%
% O integramă este reprezentată prin structura (compusul)
% integ(H, W, Lista, Vocab), unde:
% H este înălțimea integramei
% W este lățimea integramei
% Lista este o listă de tupluri (Poz, Valoare), unde
%   Poz este un tuplu (R, C) conținând rândul și coloana (0-based)
%   Valoare este una dintre:
%     x - dacă celula este neagră (nu poate fi completată cu litere)
%     o literă, dacă celula este completată cu o literă
%     o listă de întrebări, reprezentate ca tupluri (Text, Dir, ID), cu
%       Text - un literal, textul întrebării
%       Dir - una dintre valorile j sau d, indicând direcția întrebării
%       ID - un identificator numeric al întrebării
% Vocab este o listă de literali reprezentând cuvinte disponibile
% pentru a rezolva întrebarea.
%
% În ieșirea predicatului intrebări, o întrebare este reprezentată ca
% ((R, C), Text, Dir, ID), unde
% R este rândul căsuței cu întrebarea (0-based)
% C este coloana căsuței cu întrebarea (0-based)
% Text este textul întrebării (un literal)
% Dir este j sau d, reprezentând direcția în care trebuie să fie plasat
% răspunsul (jos sau dreapta)
% ID este un identificator numeric al întrebării.

% Puteți vizualiza integramele cu:
% integrama(0, W), print_integrama(W).
% integrama(1, W), print_integrama(W).
% integrama(2, W), print_integrama(W).
% integrama(3, W), print_integrama(W).
%
% Testați cu
% vmtest.
% Testați teste individuale (vedeți predicatul tt din checker.pl) cu
% vmtest(Test).
% de exemplu cu vmtest(intrebari).


% intrebari/2
% intrebari(integ(+H, +W, +Lista, +Vocab), -Lista_intrebari)
% Este adevărat atunci când Lista_intrebari este o lista de tupluri
% ((R, C), Text, Dir, ID), fiecare tuplu corespunzând unei întrebări din
% integramă (rândul, coloana, textul întrebării, direcția (j/d),
% identificatorul).
%
% BONUS: intrebari are o singură soluție (o singură listă) pentru o
% anumită integramă.
intrebari(integ(_, _, [], _),[]).
intrebari(integ(H, W, [First|Rest], Vocab), Lista_intrebari):-
    caz3(First, Lista_intrebari, H, W, Rest, Vocab);
    caz2(First, Lista_intrebari, H, W, Rest, Vocab);
    caz1(First, Lista_intrebari, H, W, Rest, Vocab).

caz1(((_, _), _), Lista_intrebari, H, W, Rest, Vocab) :- 
    intrebari(integ(H, W, Rest, Vocab), Lista_intrebari).
caz2(((R, C), [A]), [((R, C), A)|Lista_intrebari], H, W,Rest, Vocab) :-
    intrebari(integ(H, W, Rest, Vocab), Lista_intrebari).
caz3(((R, C), [A,B]), [((R, C), A)|[((R, C), B)|Lista_intrebari]], H, W, Rest, Vocab) :- 
    intrebari(integ(H, W, Rest, Vocab), Lista_intrebari).


% id_intrebare/2
% id_intrebare(+Integ, ?Intrebare, ?Q_ID)
% Este adevărat dacă în integrama reprezentată ca integ(...), Intrebare
% este un text iar Q_ID este un identificator care corespund aceleași
% întrebări.
id_intrebare(integ(_, _, [], _), _, _).
id_intrebare(integ(H, W, [First|Rest], Vocab), Intrebare, Q_ID) :-
    id_helper3(H, W, First, Rest, Vocab, Intrebare, Q_ID);
    id_helper1(H, W, First, Rest, Vocab, Intrebare, Q_ID);
    id_helper2(H, W, First, Rest, Vocab, Intrebare, Q_ID).

id_helper1(H, W, ((R, C), [(T, D, I)]), Rest, Vocab, T, I):-
    id_intrebare(integ(H, W, Rest, Vocab), Intrebare, Q_ID).
id_helper2(H, W, ((_, _), _), Rest, Vocab, Intrebare, Q_ID) :-
    id_intrebare(integ(H, W, Rest, Vocab), Intrebare, Q_ID).
id_helper3(H, W, ((R, C), [(T1, D1, I1), (T2, D2, I2)]), Rest, Vocab, T2, I2):-
    id_intrebare(integ(H, W, Rest, Vocab), Intrebare, Q_ID).

% completare/3
% completare(+Integ, +Sol, -Integrama)
% Predicatul produce Integrama, o structură de forma integ(...),
% pornind de la Integ, în care au fost completate celule conform cu
% soluția Sol.
% Soluția este reprezentată ca o listă de perechi (Întrebare, Răspuns),
% unde Întrebarea este textul unei întrebări, iar Răspuns este un cuvânt
% de completat; ambele sunt atomi (literali).
% De exemplu, o soluție parțială pentru integrama 0 poate fi:
% [('Din care plouă', 'NOR'), ('Al doilea număr', 'DOI')]
%
% BONUS: lungime_spatiu are o singură soluție pentru o anumită
% întrebare.
% Puteți testa manual predicatul cu o interogare de forma:
% integrama(0, W), solutie(0, Sol), completare(W, Sol, W2),
%   print_integrama(W2).
completare(_, _, _) :- false.

% lungime_spatiu/3
% lungime_spatiu(integ(+H, +W, +Lista, +Vocab), +Intrebare, -Lungime)
% pentru Bonus:
% lungime_spatiu(integ(+H, +W, +Lista, +Vocab), ?Intrebare, ?Lungime)
%
% Returnează lungimea spațiului asociat întrebării date.
% Întrebarea este indicată prin textul ei. De exemplu:
% lungime_spatiu pentru integrama 0 și întrebarea 'Al doilea număr'
% trebuie să lege Lungime la 3.
%
% BONUS: lungime_spatiu are o singură soluție pentru o anumită
% întrebare.
% Puteți testa manual predicatul cu o interogare de forma:
% integrama(0, W), id_intrebare(W, Text, 3), lungime_spatiu(W, Text, X).
lungime_spatiu(integ(_, _, [], _), _, _).
lungime_spatiu(integ(H, W, [First|Rest], Vocab), Intrebare, Lungime) :-
    (
        (
            lungime_spatiu_helper4(H, W, First, Rest, Vocab, Intrebare, Coord, Lungime),
            (
                calc_lenD(Rest, Lungime, Coord);
                calc_lenJ(Rest, Lungime, Coord)
            )
        );
        (
            lungime_spatiu_helper3(H, W, First, Rest, Vocab, Intrebare, Coord, Lungime),
            (
                calc_lenD(Rest, Lungime, Coord);
                calc_lenJ(Rest, Lungime, Coord)
            )
        );
        (
            lungime_spatiu_helper1(H, W, First, Rest, Vocab, Intrebare,  Coord, Lungime),
            (
                calc_lenD(Rest, Lungime, Coord);
                calc_lenJ(Rest, Lungime, Coord)
            )
        );
        lungime_spatiu_helper2(H, W, First, Rest, Vocab, Intrebare,  Coord, Lungime)
    ).

calc_lenTmp([((R, C), _)|Rest], Lungime,  (R2, C2, D)):-
    Lungime is 0.


calc_lenJ([], _, _).
calc_lenJ([((R, C), _)|Rest], Lungime,  (R2, C2, D)) :-
    (
        C \= C2,
        calc_lenJ(Rest, Lungime, (R2, C2, D)), !
    );
    (
        C = C2,
        R2 < R,
        D = 'j',
        L is R - R2,
        Lungime is L - 1
    ).

calc_lenD([], _, _).
calc_lenD([((R, C), _)|Rest], Lungime,  (R, C2, D)) :-
    C2 < C,
    D = 'd',
    L is C - C2,
    Lungime is L - 1.



lungime_spatiu_helper1(H, W, ((R, C), [(T, D, I)]), Rest, Vocab, T, (R, C, D), Lungime):-
    lungime_spatiu(integ(H, W, Rest, Vocab), Intrebare, Lungime).
lungime_spatiu_helper2(H, W, ((R, C), _), Rest, Vocab, Intrebare, (R, C, _), Lungime) :-
    lungime_spatiu(integ(H, W, Rest, Vocab), Intrebare, Lungime).
lungime_spatiu_helper3(H, W, ((R, C), [(T1, D1, I1), (T2, D2, I2)]), Rest, Vocab, T2,  (R, C, D2), Lungime):-
    lungime_spatiu(integ(H, W, Rest, Vocab), Intrebare, Lungime).
lungime_spatiu_helper4(H, W, ((R, C), [(T1, D1, I1), (T2, D2, I2)]), Rest, Vocab, T1,  (R, C, D1), Lungime):-
    lungime_spatiu(integ(H, W, Rest, Vocab), Intrebare, Lungime).


% intersectie/5
% intersectie(integ(+H, +W, +Lista, +Voc), +I1, -Poz1, +I2, -Poz2)
% pentru Bonus:
% intersectie(integ(+H, +W, +Lista, +Voc), ?I1, ?Poz1, ?I2, ?Poz2)
%
% Pentru o integramă și două întrebări date prin textul lor (I1 și I2),
% al căror răspunsuri se intersectează, întoarce în Poz1 indicele din
% răspunsul la I1 la care este intersecția, și în Poz2 indicele din
% răspunsul la I2 la care este intersecția. Indecșii incep de la 0.
%
% De exemplu, în integrama 0:
%  █       █       2↓      3↓      █
%  █       0↓,1→   -       -       █
%  4→      -       -       -       █
%  5→      -       -       -       █
%  █       █       █       █       █
%
%  Întrebările 'Primii 3 din artă' și 'Afirmativ' (3, respectiv 1) se
%  intersectează la pozițiile 0, respectiv 2 (va fi litera A, de la
%  ART, respectiv DA).
intersectie(_, _, _, _, _) :- false.

% solutii_posibile/2
% solutii_posibile(integ(+H, +W, +Lista, +Vocabular), -Solutii)
% Formează o listă Solutii, conținând perechi de forma
% (Întrebare, Cuvinte), unde
% Întrebare este textul unei întrebări din integramă, iar Cuvinte este o
% listă de cuvinte sunt din Vocabular și au lungimea corectă pentru a fi
% răspuns la întrebare. Solutii conține câte o pereche pentru fiecare
% întrebare din integramă.
% Cuvintele sunt reprezentate ca liste de atomi, fiecare atom
% având lungime 1 (o singură literă).
% De exemplu, pentru integrama 0, Solutii conține 6 perechi, două dintre
% ele fiind:
% ('Afirmativ', [['D', 'A'], ['N', 'U']])
% ('Din care plouă',
% [['N','O','R'],['A','R','T'],['U','I','T'],['D','O','I']])
solutii_posibile(integ(_, _, [], _), _).
solutii_posibile(integ(H, W, Cells, Vocab), Solutii) :-
    (
        helpSol1(H, W, Cells, Vocab, Intrebare1, Solutii),
        wordFinder(H, W, Cells, Vocab, Intrebare1, Cuvinte1),
        lungime_spatiu(integ(H, W, Cells, Vocab), Intrebare1, Lungime1),
        % addToSol(Cuvinte1, ListSol1, Lungime1),
        createSol(Intrebare1, ListSol1, Solutii),
        helpSol2(H, W, Cells, Vocab, Intrebare2, Solutii),
        wordFinder(H, W, Cells, Vocab, Intrebare2, Cuvinte2),
        lungime_spatiu(integ(H, W, Cells, Vocab), Intrebare2, Lungime2),
        addToSol(Cuvinte2, ListSol2, Lungime2),
        createSol(Intrebare2, ListSol2, Solutii)
    );
    (
        helpSol3(H, W, Cells, Vocab, Intrebare, Solutii),
        wordFinder(H, W, Cells, Vocab, Intrebare, Cuvinte),
        lungime_spatiu(integ(H, W, Cells, Vocab), Intrebare, Lungime),
        addToSol(Cuvinte, ListSol, Lungime)
    );
    (
        helpSol4(H, W, Cells, Vocab, Intrebare, Solutii)
    ).


helpSol1(H, W, [((R, C), [(T1, D1, I1), (T2, D2, I2)])|Rest], Vocab, T1, Solutii) :-
    solutii_posibile(integ(H, W, Rest, Vocab), Solutii).
    
helpSol2(H, W, [((R, C), [(T1, D1, I1), (T2, D2, I2)])|Rest], Vocab, T2, Solutii) :-
    solutii_posibile(integ(H, W, Rest, Vocab), Solutii).

helpSol3(H, W, [((R, C), [(T1, D1, I1)])|Rest], Vocab, T1, Solutii) :-
    solutii_posibile(integ(H, W, Rest, Vocab), Solutii).

helpSol4(H, W, [((_, _), _)|Rest], Vocab, Intrebare, Solutii) :-
    solutii_posibile(integ(H, W, Rest, Vocab), Solutii).

wordFinder(H, W, Cells, [VocabF|VocabL], Intrebare, Cuvinte) :-
    maplist(atom_chars, [VocabF|VocabL], Cuvinte).

addToSol([], _, _).
addToSol(Cuvinte, ListSol, Lungime) :-
    cazLenTrue(Cuvinte, ListSol, Lungime);
    cazLenFalse(Cuvinte, ListSol, Lungime).

cazLenTrue([First|Rest], [First|ListSol], Lungime) :-
    length(First, Lungime),
    addToSol(Rest, ListSol, Lungime).

cazLenFalse([First|Rest], ListSol, Lungime) :-
    addToSol(Rest, ListSol, Lungime).


createSol(Intrebare1, ListSol1, [(Intrebare1, ListSol1)|Solutii]).




% rezolvare/2
% rezolvare(+Integ, -Solutie)
% Rezolvare produce în Solutie soluția integramei Integ. Soluția este
% reprezentată ca o listă de perechi de literali, fiecare pereche
% conținând textul unei întrebări și cuvântul (ca literal) care este
% răspunsul la întrebare.
%
% BONUS: rezolvare nu oferă soluții duplicate - numărul de soluții ale 
% predicatului este chiar numărul de completări posibile ale integramei.
rezolvare(_, _) :- false.
 