import qualified Data.Map as M
import Data.List

import System.Environment

import Text.ParserCombinators.Parsec

data Vertex = Vertex { vname :: String } deriving (Show, Eq, Ord)
type Graph = M.Map Vertex (Vertex, Vertex)

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let seqs = case parse fileParser "day9" contents of
                            Left err  -> error $ show err
                            Right out -> out
    -- print $ sum $ map nextElem seqs
    print $ sum $ map (nextElem . reverse) seqs

nextElem :: [Int] -> Int
nextElem seq | all (== 0) seq = 0
             | otherwise      = (last seq) + nextElem (diffs seq)

diffs :: [Int] -> [Int]
diffs [] = []
diffs (x:[]) = []
diffs (x:y:rest) = (y - x) : diffs (y:rest)

-- parsing

fileParser :: Parser [[Int]]
fileParser = nums `sepEndBy` newline <* eof
  where
    int = read <$> many1 (char '-' <|> digit)
    nums = int `sepBy` (char ' ')

myHead (x:_) = x
myLast = last
