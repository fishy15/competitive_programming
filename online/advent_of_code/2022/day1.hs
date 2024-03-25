import Control.Monad
import Data.List
import System.IO

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let inputLines = lines contents
    let scores = compScores inputLines
    print $ maximum scores
    print $ sum $ take 3 $ reverse $ sort scores

compScores :: [String] -> [Int]
compScores input = compScores' input 0 []
    where compScores' :: [String] -> Int -> [Int] -> [Int]
          compScores' [] curScore scores = (curScore:scores)
          compScores' (line:rest) curScore scores 
            = if line == ""
                then compScores' rest 0 (curScore:scores)
                else compScores' rest (curScore + (read line)) scores