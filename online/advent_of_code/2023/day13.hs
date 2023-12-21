import Data.List

import System.Environment

import Text.ParserCombinators.Parsec

type Grid = [String]

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let grids = case parse fileParser "day13" contents of
                    Left err  -> error $ show err
                    Right out -> out
    print $ part1 grids
    print $ part2 grids

part1 :: [Grid] -> Int
part1 grids = 100 * sum (map getSplitSum grids) + sum (map (getSplitSum . transpose) grids)

part2 :: [Grid] -> Int
part2 grids = 100 * sum (map getSplitSum2 grids) + sum (map (getSplitSum2 . transpose) grids)

getSplitSum :: Grid -> Int
getSplitSum grid = sum $ [i | i <- [1..length grid - 1], checkReflect grid i]

getSplitSum2 :: Grid -> Int
getSplitSum2 grid = sum $ [i | i <- [1..length grid - 1], checkReflect2 grid i]

-- check if keeping first i rows forms a reflection
checkReflect :: Grid -> Int -> Bool
checkReflect grid i = removeExtra == reverse removeExtra
  where
    otherSplit = length grid - i
    removeExtra = drop (i - otherSplit) $ take (2 * i) grid

checkReflect2 :: Grid -> Int -> Bool
checkReflect2 grid i = sum (zipWith diffList removeExtra (reverse removeExtra)) == 2
  where
    otherSplit = length grid - i
    removeExtra = drop (i - otherSplit) $ take (2 * i) grid

-- number of different indices
diffList :: Eq a => [a] -> [a] -> Int
diffList xs ys = sum $ zipWith (\x y -> fromEnum $ x /= y) xs ys

-- parsing

fileParser :: Parser [Grid]
fileParser = gridParser `sepEndBy` newline <* eof
  where
    gridParser = many1 (oneOf "#.") `sepEndBy` newline

myHead (x:_) = x
