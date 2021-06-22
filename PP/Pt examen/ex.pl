merge_list([],L,L ).
merge_list([H|T],L,[H|M]):-
    merge_list(T,L,M).

noRedundancies([_],_).
noRedundancies(L, X):-
    helper(L, X).

helper([], _).
helper([First|Rest], X) :-
    merge_list(First, X, X),
    not(member(First, X)),
    helper(Rest, merge_list(First, X, X)).