% Number 93687 Andre Luis Raposo Marinho

% A program in SWIPROLOG developed to solve square (MxM, with M => 4) binary puzzles.

:-[codigo_comum].
:-[puzzles_publicos].

%-----------------------------------------------------------------------------
%                            Auxiliary predicates                            
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate sub_var(LIN, N, LOUT):
% To replace the variable in the input without changing LIN it is creating a 
% new list (LOUT) copying the old one without the variables. N is a flag to 
% apply different substitutions to the variables.
%-----------------------------------------------------------------------------
sub_var([], _, []) :- !.

sub_var(List, N, List) :- 
    N == 1, !.

sub_var([H|Tin], N, [H|Tout]) :-
    nonvar(H), !,
    sub_var(Tin, N, Tout).

sub_var([_|Tin], N, [1|Tout]) :-
    N == 0, !,
    sub_var(Tin, N, Tout).

sub_var([_|Tin], N, [0|Tout]) :-
    N == 2, !,
    sub_var(Tin, N, Tout).

%-----------------------------------------------------------------------------
% Predicate mat_line_elements(Mat, Line, Elements):
% Elements is a list with the line elements of Mat.
%-----------------------------------------------------------------------------
mat_line_elements(Mat, Line, Elements) :-
    nth1(Line, Mat, Elements).

%-----------------------------------------------------------------------------
% Predicate count_number_occ(Lin, Number, Occ):
% this predicate gives the number of occurrences (Occ) of a Number in a list
% (Lin).
%-----------------------------------------------------------------------------
count_number_occ(Lin, Number, Occ) :-
    findall(X, (member(X, Lin), X == Number), Number_Bag),
    length(Number_Bag, Occ).

%-----------------------------------------------------------------------------
% Predicate half_list_size(List, Half_List_Size):
% Half_List_Size is the len result of half of the given List.
%-----------------------------------------------------------------------------
half_list_size(List, Half_List_Size) :- !,
    length(List, Size),
    Half_List_Size is Size // 2.

%-----------------------------------------------------------------------------
% Predicate check_puzzle_lines(Puz, Puz_with_rules, Lines):
% Puz_with_rules is the outcome of applying rules one and two do the lines
% of a puzzle, it ends when counter exceeds the lines of the matrix.
%-----------------------------------------------------------------------------
check_puzzle_lines(Puz, Puz_with_rules, Lines) :- check_puzzle_lines(Puz, Puz_with_rules, Lines, 1).

check_puzzle_lines(Puz, Puz, _, 0) :- !.

check_puzzle_lines(Puz, Puz_with_rules, Lines, Count) :-
    Count =< Lines, !,
    mat_line_elements(Puz, Count, Line),
    aplica_R1_R2_fila(Line, Line_with_rules),
    mat_muda_linha(Puz, Count, Line_with_rules, Puz_changed),
    Next_Line is Count + 1,
    check_puzzle_lines(Puz_changed, Puz_with_rules, Lines, Next_Line).

check_puzzle_lines(Puz, Puz_with_rules, Lines, _) :- !,
    check_puzzle_lines(Puz, Puz_with_rules, Lines, 0).

%-----------------------------------------------------------------------------
% Predicate pos_to_coord(Pos, CurrentCoord, Flag, Coord):
% With the given Flag, the position (Pos) given is transformed in a coordinate
% (L,C) in Coord.
%-----------------------------------------------------------------------------
pos_to_coord(Pos, [(L,_)], Flag, Coord) :-
    Flag == 1, !,
    append([(L,Pos)], [], Coord).

pos_to_coord(Pos, [(_,C)], _, Coord) :- !,
    append([(Pos,C)], [], Coord).

%-----------------------------------------------------------------------------
% Predicate check_lists_diffs(LIN, LOUT, CurrentCoord, Flag, Coords):
% With the two lists given (LIN and LOUT), Coords are the coordinates where
% a var was changed to a number (0 or 1). Flag is given to know if it is 
% checking a line or a column of a puzzle. Current coord is where the
% differences are being made.
%-----------------------------------------------------------------------------
check_lists_diffs(LIN, LOUT, CurrentCoord, Flag, Coords) :- check_lists_diffs(LIN, LOUT, CurrentCoord, Flag, Coords, [], 1).

check_lists_diffs([], [], _, _, Res, Res, _) :- !.

check_lists_diffs([H1|T1], [H2|T2], [(L,C)], Flag, Coords, Res, Pos) :-
    var(H1), nonvar(H2), !,
    pos_to_coord(Pos, [(L,C)], Flag, Coord),
    append(Res, Coord, NewRes),
    NextPos is Pos + 1,
    check_lists_diffs(T1, T2, [(L,C)], Flag, Coords, NewRes, NextPos).

check_lists_diffs([_|T1], [_|T2],[(L,C)], Flag, Coords, Res, Pos) :- !,
    NextPos is Pos + 1,
    check_lists_diffs(T1, T2, [(L,C)], Flag, Coords, Res, NextPos).

%-----------------------------------------------------------------------------
% Predicate check_equal_lines(Line, Puz):
% Inside a Puzzle, one of his lines (Line_to_check) is compared to the next
% and so on until his end. It is true when they are all different, otherwise
% is false.
%-----------------------------------------------------------------------------
check_equal_lines(_, []) :- !.

check_equal_lines(Line_to_check, [Line|Rest]) :-
    not(Line == Line_to_check), !, 
    check_equal_lines(Line_to_check, Rest).

%-----------------------------------------------------------------------------
% Predicate verifica_R3_aux(Puz):
% Applies check_equal_lines to all the lines of a Puzzle. It is true when they
% are all different, false otherwise.
%-----------------------------------------------------------------------------
verifica_R3_aux([_|[]]) :- !.

verifica_R3_aux([Line|RestLines]) :-
    check_equal_lines(Line, RestLines),
    verifica_R3_aux(RestLines).

%-----------------------------------------------------------------------------
% Predicate find_var(Puz, Coord):
% In a given Puz, this predicate searches for a var and gives the respective
% coordinate (Coord). It is false if the puzzle has no vars.
%-----------------------------------------------------------------------------
find_var(Puz, Coord) :-
    mat_ref(Puz, Coord, El),
    var(El).

%-----------------------------------------------------------------------------
% Predicate test_values(Puz, Coord, N_Puz):
% In a given Puz coordinate (Coord and Puz) this predicate changes its value
% to zero (if propaga_posicoes fails it changes to number one; failing again
% the predicate is false).
%-----------------------------------------------------------------------------
test_values(Puz, Coord, Puz_Res) :-
    mat_muda_posicao(Puz, Coord, 0, Puz_Res).

test_values(Puz, Coord, Puz_Res) :-
    mat_muda_posicao(Puz, Coord, 1, Puz_Res).

%-----------------------------------------------------------------------------
%                     Puzzle Initialization predicates                       
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
%                             Rule One Predicates
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate aplica_R1_triplo(Triplo, N_Triplo):
% N_Triplo is a three elements list with the respective changes of Triplo.
% With none, two or three variables the are no alterations if the three elements
% in the list are not equal.
% With one variable changes happen when the two numbers are equal.
%-----------------------------------------------------------------------------
aplica_R1_triplo(Triplo, Triplo) :- 
    findall(X, (member(X, Triplo), var(X)), ResVars),
    length(ResVars, N),
    N > 1, !.

aplica_R1_triplo(Triplo, N_triplo) :- 
    findall(X, (member(X, Triplo), nonvar(X)), ResNumbers), 
    length(ResNumbers, 2), !,
    sum_list(ResNumbers, Sum),      % Substitutions only happen if the sum of the numbers of Triplo is not one,
    sub_var(Triplo, Sum, N_triplo). % meaning that zero and one are the numbers of Triplo

aplica_R1_triplo(Triplo, Triplo) :- !,
    sum_list(Triplo, Sum),
    between(1, 2, Sum).     % If Triplo has three ones or zeros the predicate is false.

%-----------------------------------------------------------------------------
% Predicate aplica_R1_fila_aux(Fila, N_Fila):
% N_Fila is list (puzzle line or column) with the possible 
% changes made in each three elements sub lists in Fila using the predicate 
% aplica_R1_triplo (Rule one). This predicate is false or true when
% aplica_R1_triplo is false or true, respectively.                 
%-----------------------------------------------------------------------------
aplica_R1_fila_aux(Fila, N_Fila) :- aplica_R1_fila_aux(Fila, N_Fila, []).

aplica_R1_fila_aux([], Res, Res) :- !.

aplica_R1_fila_aux([F,S,T|[]], N_Fila, Res) :- 
    aplica_R1_triplo([F, S, T], LastTriple), !,
    reverse(Res, OtherTriples),                      % In last Triplo, the changed list is reversed to the correct order
    append(OtherTriples, LastTriple, FinalList),     % and the last three numbers are added to end of the list.
    aplica_R1_fila_aux([], N_Fila, FinalList).    

aplica_R1_fila_aux([F, S, T|ResFila], N_Fila, Res) :-
    aplica_R1_triplo([F, S, T], [F1, S1, T1]), !,
    aplica_R1_fila_aux([S1, T1|ResFila], N_Fila, [F1|Res]).

%-----------------------------------------------------------------------------
% Predicate aplica_R1_fila(Fila, N_Fila):
% N_fila is the result of applying aplica_R1_fila_aux to Fila until N_Fila
% can not be changed again. This predicate is false or true in accordance
% with his auxiliary predicates.
%-----------------------------------------------------------------------------
aplica_R1_fila(Fila, Fila) :-
    aplica_R1_fila_aux(Fila, Fila_Res), 
    Fila == Fila_Res, !.

aplica_R1_fila(Fila, N_Fila) :- !,
    aplica_R1_fila_aux(Fila, Fila_Res), 
    aplica_R1_fila(Fila_Res, N_Fila).

%-----------------------------------------------------------------------------
%                            Rule two predicate
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate aplica_R2_fila(Fila, N_Fila):
% N_fila is the result of applying rule two to a line or column of a puzzle 
% (Fila), which means that the list must have the same number of zeros and 
% ones, filling the variables if possible. This predicate is false if a 
% number counting is higher than the half-length of Fila.
%-----------------------------------------------------------------------------
aplica_R2_fila(Fila, N_Fila) :-
    count_number_occ(Fila, 1, Size_Ones),
    half_list_size(Fila, Half_Fila_Size),
    Size_Ones == Half_Fila_Size, !,
    sub_var(Fila, 2, N_Fila).

aplica_R2_fila(Fila, N_Fila) :-
    count_number_occ(Fila, 0, Size_Zeros),
    half_list_size(Fila, Half_Fila_Size),
    Size_Zeros == Half_Fila_Size, !,
    sub_var(Fila, 0, N_Fila).

aplica_R2_fila(Fila, Fila) :-
    count_number_occ(Fila, 0, Size_Zeros),
    count_number_occ(Fila, 1, Size_Ones),
    half_list_size(Fila, Half_Fila_Size),
    Size_Zeros < Half_Fila_Size,
    Size_Ones < Half_Fila_Size, !.

%-----------------------------------------------------------------------------
%    Rule one and two connection to puzzle and respective initialization
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate aplica_R1_R2_fila(Fila, N_Fila):
% N_fila is the result line (or collumn) of a puzzle after applying Rules
% one and two with aplica_R1_fila and aplica_R2_fila predicates, respectively.
% This predicate returns false or true in accordance with his auxiliary 
% predicates.
%-----------------------------------------------------------------------------
aplica_R1_R2_fila(Fila, N_fila) :-
    aplica_R1_fila(Fila, Fila_Res),
    aplica_R2_fila(Fila_Res, N_fila).

%-----------------------------------------------------------------------------
% Predicate aplica_R1_R2_puzzle(Puz, N_Puz):
% N_Puz is the resulting puzzle after applying rules one and two to Puz,
% (it can be true or false by the rules),
% As columns are the lines when Puz is transposed, Puz is transposed after
% lines verification using the same auxiliary predicate (check_puzzle_lines).
%-----------------------------------------------------------------------------
aplica_R1_R2_puzzle(Puz, N_Puz) :-
    mat_dimensoes(Puz, Lines, Columns),
    check_puzzle_lines(Puz, Puz_lines_changed, Lines),
    mat_transposta(Puz_lines_changed, Puz_cols),
    check_puzzle_lines(Puz_cols, Puz_cols_changed, Columns),
    mat_transposta(Puz_cols_changed, N_Puz).

%-----------------------------------------------------------------------------
% Predicate inicializa(Puz, N_Puz):
% N_Puz is the resulting puzzle after applying aplica_R1_R2_puzzle until no
% more alterations can be made in Puz. This predicate is true or false after
% going through the rules in the auxiliary predicates.
%-----------------------------------------------------------------------------
inicializa(Puz, Puz) :-
    aplica_R1_R2_puzzle(Puz, Puz_with_rules),
    Puz == Puz_with_rules, !.

inicializa(Puz, N_Puz) :- !,
    aplica_R1_R2_puzzle(Puz, Puz_with_rules),
    inicializa(Puz_with_rules, N_Puz).

%-----------------------------------------------------------------------------
%                       Rule three applied to puzzle
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate verifica_R3(Puz):
% this predicate is true if there are no equal lines and columns in Puz. 
% Is false otherwise. The verification is made with the auxiliary predicate
% check_equal_lines twice,
%-----------------------------------------------------------------------------
verifica_R3(Puz) :-
    verifica_R3_aux(Puz),
    mat_transposta(Puz, Puz_Transposed),  % Columns are the lines after transposing the original puzzle.
    verifica_R3_aux(Puz_Transposed).

%-----------------------------------------------------------------------------
%                     Position propagation predicate
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate propaga_posicoes(Posicoes, Puz, N_Puz): 
% N_Puz is the result of making the alterations in the line (L) and column (C),
% (with the rules one and two), and in the Ls and Cs where vars changed to
% numbers. This changes are verified with check_lists_diffs
%-----------------------------------------------------------------------------
propaga_posicoes([], Puz, Puz) :- !.

propaga_posicoes([(L, C)|RestCoords], Puz, N_Puz) :-
    mat_line_elements(Puz, L, Puz_Line),
    aplica_R1_R2_fila(Puz_Line, Puz_Line_Res),
    check_lists_diffs(Puz_Line, Puz_Line_Res, [(L,C)], 1, Lines_coords),
    append(RestCoords, Lines_coords, Next_Coords), % Next columns to propagate.

    mat_elementos_coluna(Puz, C, Puz_Col),
    aplica_R1_R2_fila(Puz_Col, Puz_Col_Res),
    check_lists_diffs(Puz_Col, Puz_Col_Res, [(L,C)], 2, Cols_coords),
    append(Next_Coords, Cols_coords, Next_in_propaga),  % Next lines to propagate.

    mat_muda_linha(Puz, L, Puz_Line_Res, Puz_Res_Line),
    mat_muda_coluna(Puz_Res_Line, C, Puz_Col_Res, Puz_Res),  % Putting the alterations in the original puzzle.
    
    propaga_posicoes(Next_in_propaga, Puz_Res, N_Puz).

%-----------------------------------------------------------------------------
%               High level predicate which solves a puzzle
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% Predicate resolve(Puz, Sol):
% starting by initializing the puzzle(Puz) with inicializa predicate, resolve
% searches for a var and changes his value in order to propagate and solve the
% puzzle. It ends when the puzzle has no vars and is false when any rule is
% not respected.
%-----------------------------------------------------------------------------
resolve(Puz, N_Puz) :- 
    inicializa(Puz, Puz_Init),
    resolve(Puz, N_Puz, Puz_Init).

resolve(_, N_Puz, Puzzle_Init) :-
    find_var(Puzzle_Init, Coord),
    test_values(Puzzle_Init, Coord, Puz_Res),
    propaga_posicoes([Coord], Puz_Res, New_Puz), !,
    resolve(_, N_Puz, New_Puz).

resolve(_, Puzzle_Init, Puzzle_Init) :-  !,
    verifica_R3(Puzzle_Init).  % Stopping condition when there is no more vars in the puzzle.