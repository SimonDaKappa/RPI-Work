Simon Gibson - 9-25-23 
Programming Languages PA #1

Overall Implementation:
My design going into this assignment was to try and implement each conversion out of order,
going with the easiest one at each stage. As such, I settled on  eta, beta, alpha being the
implementation order. Beta and Eta seem to work properly, but there are some issues with Alpha Renaming

Alpha Renaming is implemented as such. Each atom is a symbol and a counter.
So for example \x has symbol x and count 1, and \x2 has symbol x count 2. This works with
multiple layered recursion in the same alpha call, but it wont recognize numbers in a symbol
from input or previous calls. For example
Input  1: (\x99.\y.(y x99) (y w))
Result 1: \x992.(x992 (y w))
Doesn't iterate properly as the first alpha call reads "x99" as symbol and 0 the count. This 
happens deliberately in the original reducer calls.

Struggles:
I first tried to do alpha renaming in the midst of eta and beta, but this was really difficult.
This lead me to switching to a single upfront alpha conversion. Im not sure, but I think that 
this will lead the interpretor to be wrong if a eta/beta conversion/reduction creates a scenario
for this to happen. A lack of sample inputs was quite limiting.