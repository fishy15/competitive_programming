import Control.Monad
import Data.Char
import Data.List
import Data.Maybe
import System.IO

data Range = Range Int Int

main :: IO ()
main = do
    contents <- lines <$> readFile "input.txt"
    test1 contents
    test2 contents

test1 :: [String] -> IO ()
test1 lines = do
    let ranges = map readRanges lines
    print $ length $ filter (uncurry eitherContains) ranges
    return ()

test2 :: [String] -> IO ()
test2 lines = do
    let ranges = map readRanges lines
    print $ length $ filter (uncurry overlaps) ranges
    return ()

contains :: Range -> Range -> Bool
contains outer inner = outerL <= innerL && innerR <= outerR
    where Range innerL innerR = inner
          Range outerL outerR = outer
        
overlaps :: Range -> Range -> Bool
overlaps range1 range2 = not (r1 < l2 || r2 < l1)
    where Range l1 r1 = range1
          Range l2 r2 = range2
          
eitherContains :: Range -> Range -> Bool
eitherContains r1 r2 = contains r1 r2 || contains r2 r1

splitAndRead :: Char -> (String -> a) -> (a -> a -> b) -> String -> b
splitAndRead c reader constr s = constr first second
    where first  = reader $ take idx s
          second = reader $ drop (idx + 1) s
          idx    = fromJust $ findIndex (==c) s

readRanges :: String -> (Range, Range)
readRanges = splitAndRead ',' readRange (,)

readRange :: String -> Range
readRange = splitAndRead '-' read Range