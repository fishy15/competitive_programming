import Control.Monad
import Data.Char
import Data.List
import System.IO

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let inputLines = lines contents
    print $ sum $ map getCommonPriority inputLines
    print $ sum $ map getGroupCommon $ groupIn3s inputLines

getCommonPriority :: String -> Int
getCommonPriority s = getPriority common
    where common = filter (\c -> c `elem` firstHalf) secondHalf !! 0
          (firstHalf, secondHalf) = splitAt half s
          half = length s `div` 2

getGroupCommon :: (String, String, String) -> Int
getGroupCommon (first, second, third) = sum $ map getPriority common
    where common = nub $ filter (\c -> c `elem` second && c `elem` third) first

getPriority :: Char -> Int
getPriority c
    | isLower c = ord c - ord 'a' + 1
    | otherwise = ord c - ord 'A' + 27

groupIn3s :: [a] -> [(a, a, a)]
groupIn3s [] = []
groupIn3s (a:b:c:as) = ((a, b, c):rest)
    where rest = groupIn3s as