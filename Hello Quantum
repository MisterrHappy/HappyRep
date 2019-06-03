# # # # # # # # # # # # # # # # # # # # # # # # # # # #
#       Numero 93687 Andre Luis Raposo Marinho        #
#  Segundo projeto de FP 2018/2019 --> Hello Quantum  #
# # # # # # # # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # #
# Auxiliary functions #
# # # # # # # # # # # #


def switch(value):
    """
    switch: int --> int
    Auxiliary function that switches the value of a cell from active to inactive
    (and vice versa), keeping uncertain values
    """
    return (value + 1) % 2 if value >= 0 else value
    # taken from the solution of the first project


def adjust_coordinate_column(coord):
    """
    adjust_coordinate_column: coordinate --> int
    Auxiliary function that decrements one to the column of the coordinate
    to make the first element of the third list available
    """
    return coordenada_coluna(coord) - 1 if coordenada_linha(coord) == 2 else coordenada_coluna(coord)


def switch_in_gate_h(board, coord_x, coord_y):
    """
    switch_in_gate_h: board x coordinate x coordinate --> board
    Auxiliary function that given two coordinates, switches their values between them
    """
    coord_x_cell = tabuleiro_celula(board, coord_x)  # saving the cell in coord x
    coord_y_cell = tabuleiro_celula(board, coord_y)  # saving the cell in coord y
    return tabuleiro_substitui_celula(board, coord_y_cell, coord_x) and \
        tabuleiro_substitui_celula(board, coord_x_cell, coord_y)


def gate_x_z_aux(board, coord_x, coord_y, coord_z):
    """
    gate_x_z_aux: board x coordinate x coordinate x coordinate --> board
    Auxiliary function that reverses the state of the cells in the coordinates given as arguments
    """
    return tabuleiro_inverte_estado(board, coord_x) and tabuleiro_inverte_estado(board, coord_y) and \
        tabuleiro_inverte_estado(board, coord_z)


def user_choice(board, gate, side):
    """
    user_choice: board x str x str --> board
    Auxiliary function that selects the gate to use in the game according to the user input
    """
    return porta_x(board, side) if gate == 'X' else porta_z(board, side) if gate == 'Z' else porta_h(board, side)


# # # # # # # # # # # #
#   Main functions    #
# # # # # # # # # # # #

# Cell functions


def cria_celula(value):
    """
    cria_celula: {1, 0, -1} --> cell
    Function that creates a cell with the corresponding input value, only 1, 0 or -1 suit in the cell
    """
    if type(value) != int or value not in (-1, 0, 1):
        raise ValueError('cria_celula: argumento invalido.')
    return {'state': value}


def obter_valor(cell):
    """
    obter_valor: cell --> {1, 0, -1}
    Function that returns the value of the input cell
    """
    return cell['state']


def inverte_estado(cell):
    """
    inverte_estado: cell --> cell
    Function that reverses the given cell where 0 goes to 1 (and vice-versa) and -1 stays equal
    """
    cell['state'] = switch(obter_valor(cell))
    return cell


def eh_celula(arg):
    """
    eh_celula: universal --> boolean
    Function that recognises cells
    """
    return isinstance(arg, dict) and len(arg) == 1 and \
        all((arg[state] in (-1, 0, 1) and state == 'state' and type(arg[state]) == int for state in arg))
    # the cell is a dictionary (with only one key) having as possible values -1, 0 or 1


def celulas_iguais(c1, c2):
    """
    celulas_iguais: cell x cell --> boolean
    Function that checks if the two given cells are in the same state
    """
    return eh_celula(c1) and eh_celula(c2) and obter_valor(c1) == obter_valor(c2)
    # if they have the same value (state) then they are equal


def celula_para_str(cell):
    """
    celula_para_str: cell --> str
    Function that returns a string representing the given cell
    """
    return 'x' if obter_valor(cell) == -1 else format(obter_valor(cell))


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Coordinate functions


def cria_coordenada(l, c):
    """
    cria_coordenada: N**2 --> coordinate
    Function that returns the coordinate linked with the correspondent line and column
    """
    if type(l) == int and type(c) == int and l in (0, 1, 2) and c in (0, 1, 2):
        return {'line': l, 'column': c}
    raise ValueError('cria_coordenada: argumentos invalidos.')


def coordenada_linha(coordinate):
    """
    coordenada_linha: coordinate --> N
    Function that returns the number of the line of the coordinate given as argument
    """
    return coordinate['line']


def coordenada_coluna(coordinate):
    """
    coordenada_coluna: coordinate --> N
    Function that returns the number of the column of the coordinate given as argument
    """
    return coordinate['column']


def eh_coordenada(arg):
    """
    eh_coordenada: universal --> boolean
    Function that verifies if the given argument is a coordinate
    """
    return isinstance(arg, dict) and len(arg) == 2 and \
        all((arg[key] in (0, 1, 2) and type(arg[key]) == int and key in ('line', 'column') for key in arg))
    # the coordinate is a dictionary with two keys, both having as possible values 0, 1 or 2


def coordenadas_iguais(c1, c2):
    """
    coordenadas_iguais: coordinate x coordinate --> boolean
    Function that verifies if the two given coordinates are equal (same position in the board)
    """
    return eh_coordenada(c1) and eh_coordenada(c2) and coordenada_linha(c1) == coordenada_linha(c2) and \
        coordenada_coluna(c1) == coordenada_coluna(c2)


def coordenada_para_str(coordinate):
    """
    coordenada_para_str: coordinate --> str
    Function that returns a string representing the given coordinate
    """
    return '(' + str(coordenada_linha(coordinate)) + ', ' + str(coordenada_coluna(coordinate)) + ')'


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Board Functions


def tabuleiro_inicial():
    """
    tabuleiro_inicial: {} --> board
    Function that returns the initial board which starts the game
    """
    return str_para_tabuleiro('((-1, -1, -1), (0, 0, -1), (0, -1))')


def str_para_tabuleiro(string):
    """
    str_para_tabuleiro: str --> board
    Function that returns the matching board of the given string
    """
    try:
        board = eval(string)
        if isinstance(string, str) and isinstance(board, tuple) and all(isinstance(t, tuple) for t in board):
            board = [[cria_celula(cell) for cell in y] for y in board]
            if eh_tabuleiro(board):
                    return board
        raise ValueError('str_para_tabuleiro: argumento invalido.')
    except:
        raise ValueError('str_para_tabuleiro: argumento invalido.')
    # transforming the string in a tuple and the tuple into the chosen representation


def tabuleiro_dimensao(board):
    """
    tabuleiro_dimensao: board --> N
    Function that returns the number of lines (same number of columns) of the board
    """
    return 3


def tabuleiro_celula(board, coord):
    """
    tabuleiro_celula: board x coordinate --> cell
    Function that returns the cell in the coordinate of the given board
    """
    return board[coordenada_linha(coord)][adjust_coordinate_column(coord)]


def tabuleiro_substitui_celula(board, cell, coord):
    """
    tabuleiro_substitui_celula: board x cell x coordinate --> board
    Function that returns the board changing the current cell in the given coordinate for the cell in the argument
    """
    if eh_tabuleiro(board) and eh_celula(cell) and eh_coordenada(coord) and not \
            (coordenada_linha(coord) == 2 and coordenada_coluna(coord) == 0):
        board[coordenada_linha(coord)][adjust_coordinate_column(coord)] = cell
        return board
    raise ValueError('tabuleiro_substitui_celula: argumentos invalidos.')
    # the coordinate (2, 0) does not exist and the line and column in coordinates give the position to insert the cell


def tabuleiro_inverte_estado(board, coord):
    """
    tabuleiro_inverte_estado: board x coordinate --> board
    Function that returns the board after reversing the cell in the given coordinate
    """
    if eh_tabuleiro(board) and eh_coordenada(coord) and not \
            (coordenada_linha(coord) == 2 and coordenada_coluna(coord) == 0):
        tabuleiro_substitui_celula(board, inverte_estado(tabuleiro_celula(board, coord)), coord)
        return board  # substitute the cell for the reversed one in the same coordinate
    raise ValueError('tabuleiro_inverte_estado: argumentos invalidos.')
    # the coordinate (2, 0) does not exist


def eh_tabuleiro(arg):
    """
    eh_tabuleiro: universal --> boolean
    Function that verifies if the given argument is a board
    """
    return isinstance(arg, list) and len(arg) == 3 and \
        all(type(e) == list for e in arg) and \
        all(len(e) == 2 if i == 2 else len(e) == 3 for i, e in enumerate(arg)) and \
        all((eh_celula(cell) for e in arg for cell in e))
    # the board is a list with 3 inside lists containing the cells


def tabuleiros_iguais(board_1, board_2):
    """
    tabuleiros_iguais: board x board --> boolean
    Function that verifies if the two given boards are equal
    """
    return eh_tabuleiro(board_1) and eh_tabuleiro(board_2) and \
        all(celulas_iguais(board_1[i][j], board_2[i][j]) for i in (0, 1, 2) for j in range(len(board_1[i])))
    # going trough all the cells in the same coordinates to verify their equality


def tabuleiro_para_str(board):
    """
    tabuleiro_para_str: board --> str
    Function that returns the string representing the given board
    """
    return '+-------+\n|...{2}...|\n|..{1}.{5}..|\n|.{0}.{4}.{7}.|\n|..{3}.{6}..|\n+-------+' \
        .format(*(celula_para_str(cells) for lines in board for cells in lines))
    # going through all the cells of the board


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Gates functions linked with the board (high level functions)


def porta_x(board, side):
    """
    porta_x: board x str --> board
    Function that returns the board with a gate_x transformation. It is applied to the left or right side depending
    on the value of the second argument
    """
    if not eh_tabuleiro(board) or side not in ('E', 'D'):
        raise ValueError('porta_x: argumentos invalidos.')
    return gate_x_z_aux(board, cria_coordenada(1, 0), cria_coordenada(1, 1), cria_coordenada(1, 2)) if side == 'E' else\
        gate_x_z_aux(board, cria_coordenada(0, 1), cria_coordenada(1, 1), cria_coordenada(2, 1))

# on the left gate_x switches the value of the entire second list
# on the right gate_x switches the value of the second element
# of the first and second lists and the first element of the third list


def porta_z(board, side):
    """
    porta_z: board x str --> board
    Function that returns the board with a gate_z transformation. It is applied to the left or right side depending
    on the value of the second argument
    """
    if not eh_tabuleiro(board) or side not in ('E', 'D'):
        raise ValueError('porta_z: argumentos invalidos.')
    return gate_x_z_aux(board, cria_coordenada(0, 0), cria_coordenada(0, 1), cria_coordenada(0, 2)) if side == 'E' else\
        gate_x_z_aux(board, cria_coordenada(0, 2), cria_coordenada(1, 2), cria_coordenada(2, 2))

# on the left gate_z switches the value of the entire first list
# on the right gate_z switches the value of the third element
# of the first and second lists and the second element of the third list


def porta_h(board, side):
    """
    porta_h: board x str --> board
    Function that returns the board with a gate_h transformation. It is applied to the left or right side depending
    on the value of the second argument
    """
    if not eh_tabuleiro(board) or side not in ('E', 'D'):
        raise ValueError('porta_h: argumentos invalidos.')
    return switch_in_gate_h(board, cria_coordenada(0, 0), cria_coordenada(1, 0)) and \
        switch_in_gate_h(board, cria_coordenada(0, 1), cria_coordenada(1, 1)) and \
        switch_in_gate_h(board, cria_coordenada(0, 2), cria_coordenada(1, 2)) if side == 'E' else \
        switch_in_gate_h(board, cria_coordenada(0, 1), cria_coordenada(0, 2)) and \
        switch_in_gate_h(board, cria_coordenada(1, 1), cria_coordenada(1, 2)) and \
        switch_in_gate_h(board, cria_coordenada(2, 1), cria_coordenada(2, 2))

# on the left gate_h switches the first and second lists
# on the right gate_h switches the last two elements of each list between them

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Additional function to play the game


def hello_quantum(string):
    """
    hello_quantum: str --> boolean
    Function that makes the game playable returning True or False, if the player gets the final board
    from the initial one, in the number of plays given in the argument
    """
    print('Bem-vindo ao Hello Quantum!')
    print('O seu objetivo e chegar ao tabuleiro:')
    board_plays = string.split(':')
    board_objective = str_para_tabuleiro(board_plays[0])  # target that user wants to reach (given in the argument)
    board_init = tabuleiro_inicial()                      # initial board
    print(tabuleiro_para_str(board_objective))
    print('Comecando com o tabuleiro que se segue:')
    print(tabuleiro_para_str(board_init))
    number_of_plays = 0                                   # counter of user plays
    while not tabuleiros_iguais(board_init, board_objective):
        number_of_plays += 1
        if number_of_plays > int(board_plays[1]):         # maximum number of plays that user can make
            return False
        gate = input('Escolha uma porta para aplicar (X, Z ou H): ')
        side = input('Escolha um qubit para analisar (E ou D): ')
        user_choice(board_init, gate, side)
        print(tabuleiro_para_str(board_init))
    print('Parabens, conseguiu converter o tabuleiro em ' + str(number_of_plays) + ' jogadas!')
    return True
