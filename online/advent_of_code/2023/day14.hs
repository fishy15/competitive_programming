import Data.List
import qualified Data.Map as M

import System.Environment

import Text.ParserCombinators.Parsec

type Grid = [String]

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    grid <- lines <$> readFile fileName
    let movedNorth = transpose $ map moveLeft $ transpose grid
    print $ compWeight (allNorth grid)
    print $ compWeight $ getCycle (genCycle grid) 1000000000

moveLeft :: String -> String
moveLeft [] = []
moveLeft ('#':rest) = '#' : moveLeft rest
moveLeft s = movedLeft ++ moveLeft rest
  where
    (untilHash, rest) = span (/= '#') s
    movedLeft = reverse $ sort untilHash

moveRight :: String -> String
moveRight [] = []
moveRight ('#':rest) = '#' : moveRight rest
moveRight s = movedLeft ++ moveRight rest
  where
    (untilHash, rest) = span (/= '#') s
    movedLeft = sort untilHash

allNorth = transpose . map moveLeft . transpose
allSouth = transpose . map moveRight . transpose
allWest = map moveLeft
allEast = map moveRight
tiltCycle = allEast . allSouth . allWest . allNorth

genCycle :: Grid -> [Grid]
genCycle grid = output
  where
    output = grid : map tiltCycle output

-- uses firstRepeat to get efficiently
getCycle :: Ord a => [a] -> Int -> a
getCycle xs i =
    if i >= idxRep
        then xs !! convIdx
        else xs !! i
  where
    (idxRep, period) = firstRepeat xs
    convIdx = (i - idxRep) `mod` period + idxRep

-- returns (index of first elem that repeats, period)
firstRepeat :: Ord a => [a] -> (Int, Int)
firstRepeat xs = go (zip xs [0..])  M.empty
  where
    go ((x, i):rest) seen =
        case M.lookup x seen of
            Just j -> (j, i - j)
            Nothing -> go rest (M.insert x i seen)

compWeight :: Grid -> Int
compWeight grid = sum $ zipWith (\s idx -> idx * cntO s) (reverse grid) [1..]
  where
    cntO = length . filter (=='O')

-- number of different indices
diffList :: Eq a => [a] -> [a] -> Int
diffList xs ys = sum $ zipWith (\x y -> fromEnum $ x /= y) xs ys

-- parsing

myHead (x:_) = x
myTail (_:xs) = xs
