:- [hogwarts].
:- [part2Helper].

% Hints:
%   for NLP parser make sure you match the type of the atom: 
%      it may come in handy that print and write are two different method of printing within prolog 

% Main 
main :-
  current_prolog_flag(argv, [DataFile|_]),
  open(DataFile, read, Stream),
  read_file(Stream,Lines), %Lines contain all the information within line split by spaces, comma and period.
  nlpLoopLines(Lines, []),
  %testItemLine(Lines),
  %testConstraintLine(Lines),
  close(Stream).

  % NLP Approach
  % Each line is either a item or constraint sentence
  % So, search over all lines twice, once for item and once for constraint (1 house can have many constraints, treat separately)
  % Putting into respective BagItem and BagConstraint
  % BagItem Elements are 3-Lists of form [Person, Item, Value]
  % BagConstrain Elements are 3-tuples of form [House, AttrVal_1, AttrVal_2]
  % Where AttrVal == [Atrribute = price, volume, Comparison = greater_than, less_than, Value = number, Unit = $,ft^3]
  % Note: Price and Volume are not in an enforced order! (i.e. price can be before volume or vice versa)

  % Loop lines, for each line, check if it is a constraint or item
  % If item, parse and add to BagItem
  % If constraint, parse and add to BagConstraint
  % For both bags, use unification to trick prolog into a "return value"

  



  % Then for each constraint, search for all combinations of BagItem Elements that satisfy the constraint
  % In both constraint and combination, we must preserve order
  % Constraint approach: Map each constraint to a constraintSolver function, which takes in a BagItem 
  % and returns a list of BagItem that satisfy the constraint

% ===================== LINE PARSING / DRIVER =====================
% Main loop for NLP and Constraint Solver
nlpLoopLines([], _).
nlpLoopLines([[]], ItemBag). % BC implementation somehow appends empty list to end of list of lines
nlpLoopLines([H|T], ItemBag) :-
  % NOTE: From TA, all constraints will occur after all items, so we can assume constraint
  % solver has access to fully filled Item Bag.
  (
    phrase(itemSentence(Name, Item, Val1, Val2), H) 
    -> 
    % Is item Sentence
    append(ItemBag, [[Name, Item, Val1, Val2]], NewItemBag),
    nlpLoopLines(T, NewItemBag)
    ;  
    (
      % Is constraint Sentence
      phrase(constraintSentence(House, AttrVal1, AttrVal2), H),
      constraintSolver(House, AttrVal1, AttrVal2, ItemBag),
      nlpLoopLines(T, ItemBag)
    )
  ).
  
% ===================== CONSTRAINT SOLVER =====================
constraintSolver(House, Constraint1, Constraint2, ItemBag) :-
  % Filter ItemBag, then generate all sublists 
  filterByHouse(ItemBag, House, Filtered_ItemBag),
  findall(SubBag, subset(SubBag, Filtered_ItemBag), SubBags),
  write(House), write("\n"), % Output formatting
  checkCombination(SubBags, House, Constraint1, Constraint2).

checkCombination([_], _, _, _).
checkCombination([H_combos | T_combos], House, Constraint1, Constraint2) :-
  sumByIdx(H_combos, 2, Price), 
  sumByIdx(H_combos, 3, Volume), 
  getItems(H_combos, Items),
  (
   (checkConstraint(Constraint1, Price), checkConstraint(Constraint2, Volume))
   -> write("  "), write([Price, Volume]), write(" : "), write(Items), write("\n")
   ; true
  ),
  checkCombination(T_combos, House, Constraint1, Constraint2).

% ===================== HELPER FUNCTIONS =====================

% Unrolls ItemBag into a list of Items
getItems([], []).
getItems([H|T], Items) :-
  nth0(1, H, Item),
  getItems(T, Items_T),
  append([Item], Items_T, Items).

% Selectively appends to Filtered based on House - Preserves order
filterByHouse([], _, []).
filterByHouse([H|T], House, Filtered) :-
  nth0(0, H, Name),
  houseOf(House_Item, Name),
  nth0(1, H, Item),
  filterByHouse(T, House, Filtered_T),
  (House_Item == House -> append([H], Filtered_T, Filtered) ; Filtered = Filtered_T).

% Does arithmetic comparison on Constraint and Value
checkConstraint(Constraint, Value) :-
  nth0(1, Constraint, Comp),
  nth0(2, Constraint, Constraint_Val),
  atom_number(Constraint_Val, Constraint_Val_N),
  ( Comp == greater
    -> (Value > Constraint_Val_N -> true ; false) 
    ; (Comp == less
      -> (Value < Constraint_Val_N -> true ; false) ; 
      write("ERROR: Invalid Constraint Comparison Operator\n"), fail    
    )
  ).

% Sums values of all items in Bag
sumByIdx([], Idx, 0).
sumByIdx([H|T],Idx, Sum) :-
  sumByIdx(T, Idx, Sum_T),
  nth0(Idx, H, Sum_H),
  atom_number(Sum_H, Sum_H_N),
  Sum is Sum_T + Sum_H_N.

% Checks if [X|L] is a Subset of [X|S]
subset([],[]).
subset([X|L],[X|S]) :-
    subset(L,S).
subset(L, [_|S]) :-
    subset(L,S).

% ===================== GRAMMARS =====================
% Item sentence DCG, with type checking for item and value
itemSentence(Name, Item, Val1, Val2) --> 
  personI(Name), [has], [item], itemI(Item), 
  [that], [costs], valueI(Val1), [dollars], [''], 
  [and], [occupies] , valueI(Val2), [cubic], [feet], [''].

personI(Name) --> [Name], {houseOf(_, Name)}.
itemI(Item) --> [Item], {atomic(Item), atom_string(Item, Item_S), string(Item_S)}. 
valueI(Value) --> [Value], {atomic(Value), atom_number(Value, Value_N), number(Value_N)}.

% Constraint Sentence DCG, with type checking for value and unit
% NOTE: CONSTRAINTS ARE REORDERED ON UNIFICATION SO THAT
%       PRICE IS ATTRVAL1 AND VOLUME IS ATTRVAL2

% Constraints in order Comparator Price , Comparator Volume
constraintSentence(House, [Attr1, Comp1, Val1, Unit1], [Attr2, Comp2, Val2, Unit2]) -->
  houseC(House), [house], [wants], [total],
  attributeValueC(Attr1, Comp1, Val1, Unit1), [and], [total], 
  attributeValueC(Attr2, Comp2, Val2, Unit2), [feet], [''].

% Constraints in order Comparator Volume , Comparator Price 
constraintSentence(House, [Attr2, Comp2, Val2, Unit2], [Attr1, Comp1, Val1, Unit1]) -->
  houseC(House), [house], [wants], [total],
  attributeValueC(Attr1, Comp1, Val1, Unit1), [feet], [and], [total], 
  attributeValueC(Attr2, Comp2, Val2, Unit2), [''].

attributeValueC(Attr, Comp, Val, Unit) --> 
  attributeC(Attr), comparisonC(Comp), [than],
  valueC(Val), unitC(Unit).

houseC(House) --> [House], {houseOf(House, _)}.
attributeC(Attr) --> [Attr], {Attr == price ; Attr == volume}.
comparisonC(Comp) --> [Comp], {Comp == greater ; Comp == less}.
valueC(Value) --> [Value], {atomic(Value), atom_number(Value, Value_N), number(Value_N)}.
unitC(Unit) --> [Unit], {Unit == dollars ; Unit == cubic}.
