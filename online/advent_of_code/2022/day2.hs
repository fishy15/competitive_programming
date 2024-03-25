import Control.Monad
import Data.List
import System.IO

data Choice = Rock | Paper | Scissors deriving (Eq, Show)
data Result = Win | Draw | Loss deriving Eq

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let inputLines = lines contents
    print $ sum $ map scoreLine inputLines
    print $ sum $ map scoreLine2 inputLines

scoreLine :: String -> Int
scoreLine line = score them us
    where us   = mapUs $ line !! 2
          them = mapThem $ line !! 0

scoreLine2 :: String -> Int
scoreLine2 line = score2 them intended
    where intended = mapResult $ line !! 2
          them     = mapThem $ line !! 0

mapThem :: Char -> Choice
mapThem c
    | c == 'A' = Rock
    | c == 'B' = Paper
    | c == 'C' = Scissors

mapUs :: Char -> Choice
mapUs c
    | c == 'X' = Rock
    | c == 'Y' = Paper
    | c == 'Z' = Scissors

mapResult :: Char -> Result
mapResult c
    | c == 'X' = Loss
    | c == 'Y' = Draw
    | c == 'Z' = Win

forResult :: Choice -> Result -> Choice
forResult them result
    | beats Rock them == result     = Rock
    | beats Paper them == result    = Paper
    | beats Scissors them == result = Scissors

beats :: Choice -> Choice -> Result
beats a b
    | a == Paper && b == Rock     = Win
    | a == Scissors && b == Paper = Win
    | a == Rock && b == Scissors  = Win
    | a == b                      = Draw
    | otherwise                   = Loss

scoreHand :: Choice -> Int
scoreHand hand
    | hand == Rock     = 1
    | hand == Paper    = 2
    | hand == Scissors = 3

scoreResult :: Result -> Int
scoreResult result
    | result == Win  = 6
    | result == Draw = 3
    | result == Loss = 0

score :: Choice -> Choice -> Int
score them us = scoreHand us + scoreResult (beats us them)

score2 :: Choice -> Result -> Int
score2 them intended = score them us
    where us = forResult them intended
