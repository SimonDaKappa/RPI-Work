import PA1Helper
import System.Environment (getArgs)
import GHC.Read (lexP)

-- Haskell representation of lambda expression
-- data Lexp = Atom String | Lambda String Lexp | Apply Lexp  Lexp 

-- Given a filename and function for reducing lambda expressions,
-- reduce all valid lambda expressions in the file and output results.
-- runProgram :: String -> (Lexp -> Lexp) -> IO ()

-- This is the identity function for the Lexp datatype, which is
-- used to illustrate pattern matching with the datatype. "_" was
-- used since I did not need to use bound variable. For your code,
-- however, you can replace "_" with an actual variable name so you
-- can use the bound variable. The "@" allows you to retain a variable
-- that represents the entire structure, while pattern matching on
-- components of the structure.
id' :: Lexp -> Lexp
id' v@(Atom _) = v
id' lexp@(Lambda _ _) = lexp
id' lexp@(Apply _ _) = lexp 

-- You will need to write a reducer that does something more than
-- return whatever it was given, of course!

-- General structure: At every reducer application, first apply alpha conversion,
-- Next pattern match to either eta conversion and recurse on return value, or
-- beta reduction and recurse on return value, or return the input if no reduction

--                  - beta reduction -
-- #######################################################

beta :: Lexp -> Lexp
-- Just Atom, no reduction
beta v@(Atom a) = v  
-- Attempt to beta reduce, will converted if (a1 == a2)
beta (Apply (Lambda a1 l1) l2) = sub l1 a1 l2
-- Function Abstraction ("atom Lexp")
beta (Lambda a l) = Lambda a (reducerH l)
-- Function Application ("Lexp Lexp")
beta (Apply l1 l2) = Apply (reducerH l1) (reducerH l2)

-- beta reduction substitution helper function
sub :: Lexp -> String -> Lexp -> Lexp
-- (Lexp) = (Atom Lexp) = (Atom (Atom Lexp))
sub v@(Atom a1) a2 l
  | a1 == a2 = l
  | otherwise = v
-- (Lexp) = ((Apply Lexp Lexp) Lexp) = ((Apply (Lexp) (Lexp)) Atom Lexp)
-- If a1 is in l1 or l2, perform substitution on both before the apply
sub (Apply l1 l2) a1 l3 = Apply (sub l1 a1 l3) (sub l2 a1 l3)
-- (Lexp) = (Lambda Lexp Lexp) = ((Lambda (Atom Lexp)) (Atom Lexp))
-- if a2 is in l1, sub l2 into l1 
sub (Lambda a1 l1) a2 l2 = Lambda a1 (sub l1 a2 l2)


--                  - alpha conversion -
-- #######################################################
-- main alpha function, calls alphaH and iterates symbols for renaming
-- Name symbols are composed as "a" ++ show i, where i is the number of times
-- This function is called recursively. a1 is symbol, a2 is the count
alpha :: Lexp -> String -> Integer -> Lexp
-- Just atom, no conversion
alpha v@(Atom a) _ _ = v
-- Function Abstraction ("atom Lexp")
-- Rename w/ alphaH using new symbol after incrementing count and recursively calling
-- alpha rename on the sub-lexp.
alpha (Lambda a l) a2 a3 = alphaH (Lambda rename (alpha l a (a3+1))) a rename
  where rename = a2 ++ show (a3+1)
-- Function Application ("Lexp Lexp")
-- Apply main alpha conversion to both lexp in function application
alpha (Apply l1 l2) a2 a3 = Apply (alpha l1 a2 a3)(alpha l2 a2 a3)

-- alpha rename helper function, does actaul conversions 
alphaH :: Lexp -> String -> String -> Lexp
-- Replacing old name only in a atom
alphaH v@(Atom a) a2 a3
  | a == a2 = Atom a3
  | otherwise = v
-- Replace "Old name a" in atom and bound lexp / function abstraction
alphaH (Lambda a l) a2 a3 = Lambda a (alphaH l a2 a3)
-- Replace old name in both lexp of function application
alphaH(Apply l1 l2) a2 a3 = Apply (alphaH l1 a2 a3)(alphaH l2 a2 a3)

--                   - eta conversion - 
-- #######################################################

eta :: Lexp -> Lexp
-- Just atom, no reduction
eta v@(Atom a) = v
-- Actual Eta Conversion 
-- (Lexp) = (Atom Lexp) (Atom "x" (Apply (Lexp) (Atom "x"))),
-- With "x" not free (is bound) in Lexp
eta v@(Lambda a1 (Apply l1 l2))
  | Atom a1 == l1 = v  -- If "x" is bound in l1, return Lexp/v
  | otherwise = l1     -- If not, perform eta conversion
-- Function Abstraction ("atom Lexp")
eta (Lambda a l) = Lambda a (reducerH l)
-- Function Application ("Lexp Lexp")
eta (Apply l1 l2) = Apply (reducerH l1) (reducerH l2)


--   - reducer, calls alpha, beta, and eta conversion - 
-- #######################################################

reducer :: Lexp -> Lexp
reducer lexp = reducerH (alpha lexp "" 0) -- Null symbol and 0 count 

-- reducer helper function, do pattern matching on lexp and recurse on return value
-- Do eta first, beta second, and return input if no reduction
reducerH :: Lexp -> Lexp
reducerH lexp
  | eta lexp /= lexp = reducerH (eta lexp)
  | beta lexp /= lexp = reducerH (beta lexp)
  | otherwise = lexp -- no reduction



-- Entry point of program
main = do
    args <- getArgs
    let inFile = case args of { x:_ -> x; _ -> "input.lambda" }
    let outFile = case args of { x:y:_ -> y; _ -> "output.lambda"}
    -- id' simply returns its input, so runProgram will result
    -- in printing each lambda expression twice. 
    runProgram inFile outFile reducer
