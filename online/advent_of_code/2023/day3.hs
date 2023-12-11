import Data.Char
import Data.List
import Data.Maybe
import System.IO

import Debug.Trace

import Text.ParserCombinators.Parsec

type ThreeChar = (Char, Char, Char)
type ThreeOf a = (a, a, a)

main :: IO ()
main = do
    grid <- lines <$> readFile "input.txt"
    -- let symbolGrid = createAdjSymbolGrid grid
    -- let validNums = zipWith numbersFromRow grid symbolGrid
    -- print $ sum $ map sum validNums
    let numbersGrid = createNumbersGrid grid
    let adjNumbersGrid = map (getThreeAdj (Nothing, Nothing, Nothing) . uncurry3 zip3) $ getThreeAdj (repeat Nothing) numbersGrid
    let combinedGrid = concat $ zipWith zip grid adjNumbersGrid 
    print $ extractAns combinedGrid
    return ()

isMySymbol :: Char -> Bool
isMySymbol c = not (isDigit c || isLetter c || c == '.')

createAdjSymbolGrid :: [String] -> [[Bool]]
createAdjSymbolGrid grid = map (map anyGridSymbol) adjGrid
  where
    adjGrid = map (getThreeAdj ('.', '.', '.') . uncurry3 zip3) $ getThreeAdj (repeat '.') grid

numbersFromRow :: String -> [Bool] -> [Int]
numbersFromRow [] _ = []
numbersFromRow row valid | isDigit (head row) = 
    if validNumber then read numberStr : rest else rest
  where
    numberStr = takeWhile isDigit row
    len = length numberStr
    validNumber = or (take len valid)
    rest =  numbersFromRow (drop len row) (drop len valid)
numbersFromRow row valid = numbersFromRow (tail row) (tail valid)

getNextRow :: [a] -> a -> a
getNextRow [] def           = def
getNextRow [x] def          = def
getNextRow (fst:snd:rest) _ = snd

getThreeAdj :: a -> [a] -> [(a, a, a)]
getThreeAdj def lst = go def lst def
  where
    go :: a -> [a] -> a -> [(a, a, a)]
    go _ [] _ = []
    go prev [x] def = [(prev, x, def)]
    go prevElem (x:xs) def = (prevElem, x, head xs) : go x xs def

anyTupSymbol :: ThreeChar -> Bool
anyTupSymbol (a, b, c) = isMySymbol a || isMySymbol b || isMySymbol c

anyGridSymbol :: (ThreeChar, ThreeChar, ThreeChar) -> Bool
anyGridSymbol (a, b, c) = anyTupSymbol a || anyTupSymbol b || anyTupSymbol c

uncurry3 :: (a -> b -> c -> d) -> (a, b, c) -> d
uncurry3 f (a, b, c) = f a b c

-- part 2

-- gets the numbers containing that digit
-- also contains an identifier
createNumbersGrid :: [String] -> [[Maybe (Int, Int)]]
createNumbersGrid = zipWith convertRow [1..]
  where
    convertRow :: Int -> String -> [Maybe (Int, Int)]
    convertRow rowIdx row = go row (rowIdx * length row)
      where
        go :: String -> Int -> [Maybe (Int, Int)]
        go [] _ = []
        go row baseValue | isDigit (head row) = 
            replicate numberLen (Just (read numberStr, baseValue)) ++ rest
          where
            numberStr = takeWhile isDigit row
            numberLen = length numberStr
            newBase = baseValue + numberLen
            rest = go (drop numberLen row) newBase
        go row baseValue = Nothing : go (tail row) (baseValue + 1)

extractAns :: [(Char, ThreeOf (ThreeOf (Maybe (Int, Int))))] -> Int
extractAns [] = 0
extractAns (('*', curElem):rest) = compute curElem + extractAns rest
  where
    compute :: ThreeOf (ThreeOf (Maybe (Int, Int))) -> Int
    compute curElem = if length numbers == 2 then product (map fst numbers) else 0
      where
        numbers = nub $ concatMap (catMaybes . toList) $ toList curElem
extractAns (_:rest) = extractAns rest

toList :: ThreeOf a -> [a]
toList (a, b, c) = [a, b, c]
