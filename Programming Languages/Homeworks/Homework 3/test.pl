% Loop through Lines, where if the line is an item sentence, assert the item into database,
% and if the line is a constraint sentence, solve the constraint. 
[[NAme1, Item1 ,Val11, Val21], [Val2]

loopLines([H|T]) :-
  write(H), nl,
  (itemSentence(Name, Item, Val1, Val2, H, [])
    -> assert([Name, Item, Val1, Val2])  %ITEM % Append list instead of dealing wiht database
    ; 
    (constraintSentence(House, AttrVal1, AttrVal2, H, [])
    -> solveConstraint(House, AttrVal1, AttrVal2) ; true)
  ),
  loopLines(T, ).

solveConstraint(House, AttrVal1, AttrVal2) :-
  % Prolog search over database of items that satisfy the constraint
  % Create all combinations of sublists, use cut
  

nth0(0, Lines, FirstLine),
write(FirstLine),
write("\n"),
phrase(itemSentence(Name, Item, Val1, Val2), FirstLine), % TODO: Fix this
write("Proper Item Sentence.\n"),
write([Name, Item, Val1, Val2]),  


remove_duplicates([], []).
remove_duplicates([Head | Tail], Result) :-
    member(Head, Tail), !,
    remove_duplicates(Tail, Result).
remove_duplicates([Head | Tail], [Head | Result]) :-
    remove_duplicates(Tail, Result).


writeItems([]).
writeItems([H]) :-
  nth0(1, H, Item),
  write(Item).
writeItems([H|T]) :-
  nth0(1, H, Item),
  write(Item), write(","),
  writeItems(T).


testItemLine(Lines) :-
  nth0(0, Lines, Line1),
  write(Line1),
  phrase(itemSentence(Name, Item, Val1, Val2), Line1),
  write("\nItem Sentence\n"),
  write(Name), write(" "), write(Item), write(" "), write(Val1), write(" "), write(Val2), write("\n").

testConstraintLine(Lines) :-
  %nth0(14, Lines, Line14), % Price , Volume
  nth0(17, Lines, Line14),  % Volume, Price
  write(Line14),
  phrase(constraintSentence(House, AttrVal1, AttrVal2), Line14),
  write("\nConstraint Sentence\n"),
  write(House), write(" "), write(AttrVal1), write(" "), write(AttrVal2).