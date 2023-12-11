import Data.Char
import Data.Maybe
import System.IO

import Text.ParserCombinators.Parsec

main :: IO ()
main = do
    contents <- readFile "input.txt"
    print $ sum $ map (read . digs) $ lines contents
--   where
--     digs s = head (onlyDigs s) : [last (onlyDigs s)]
--     onlyDigs = filter isDigit

digWords :: [String]
digWords = [
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"]

checkPrefAndReturn :: String -> Int -> String -> Maybe Char
checkPrefAndReturn pref ret s = if take (length pref) s == pref 
                                   then Just $ intToDigit ret
                                   else Nothing

digWordFinder = zipWith checkPrefAndReturn digWords [1..]
getDigWord :: String -> Maybe Char
getDigWord s = case mapMaybe (\f -> f s) digWordFinder of
                 [] -> Nothing
                 c:_ -> Just c

getPrefixDigit :: String -> Maybe Char
getPrefixDigit []                 = Nothing
getPrefixDigit (c:cs) | isDigit c = Just c
getPrefixDigit s                  = getDigWord s

onlyDigs :: String -> String
onlyDigs [] = []
onlyDigs s = case getPrefixDigit s of
              Just c  -> c : onlyDigs (tail s)
              Nothing -> onlyDigs $ tail s

digs s = head (onlyDigs s) : [last (onlyDigs s)]

