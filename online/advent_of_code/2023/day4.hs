import Data.Char
import Data.Either
import System.IO

import Control.Monad

import Control.Monad.ST
import Data.Array.ST

import Data.Array.Base
import Data.Array.MArray

import Text.ParserCombinators.Parsec

data Card = Card { winning :: [Int], have :: [Int] } deriving (Show)

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let cards = case parse fileParser "day4" contents of
                  Left err  -> error $ show err
                  Right out -> out
    -- print $ sum $ map score cards
    print $ sum $ getCardCounts cards

score :: Card -> Int
score card = if commonLen == 0 then 0 else 2 ^ (commonLen - 1)
  where commonLen = length $ intersectCards card

intersectCards :: Card -> [Int]
intersectCards (Card ws hs) = ws `intersect` hs

intersect :: (Eq a) => [a] -> [a] -> [a]
intersect xs = filter (`elem` xs)

getCardCounts :: [Card] -> [Int]
getCardCounts cards = elems $ runSTUArray $ compute cards
  where
    cardsLenEnd = length cards - 1
    compute cards = do
        counts <- newArray (0, cardsLenEnd) 1 :: ST s (STUArray s Int Int)
        forM_ [0..cardsLenEnd] $ \i -> do
            let commonLen = length $ intersectCards (cards !! i)
            curCount <- readArray counts i
            forM_ [i+1..min cardsLenEnd i+commonLen] $ \j -> do
                curValue <- readArray counts j
                writeArray counts j (curValue+curCount)
        return counts 

-- parsing

fileParser :: Parser [Card]
fileParser = sepEndBy cardParser newline

cardParser :: Parser Card
cardParser = do
    -- read "Game _: "
    skipMany1 (noneOf ":")
    string ": "
    winningCardsStr <- many (noneOf "|")
    string "|"
    haveCardsStr <- many (noneOf "\n")
    return $ Card (conv winningCardsStr) (conv haveCardsStr)
  where
    conv :: String -> [Int]
    conv s = map read $ words s

