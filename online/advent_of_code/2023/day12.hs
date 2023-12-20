import Data.List
import Data.Array.IArray

import Debug.Trace

import System.Environment

import Text.ParserCombinators.Parsec

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let cases = case parse fileParser "day9" contents of
                            Left err  -> error $ show err
                            Right out -> out
    let cases5 = map (\(x, y) -> (intercalate "?" $ replicate 5 x, concat $ replicate 5 y)) cases
    -- print $ sum $ map (uncurry compAns) cases
    print $ sum $ map (uncurry compAns) cases5

compAns :: String -> [Int] -> Int
compAns s nums = solve lenStr lenNums
  where
    lenStr = length s
    lenNums = length nums
    dp = genArray ((0, 0), (lenStr, lenNums)) (uncurry solve) :: Array (Int, Int) Int
    -- base cases
    solve 0 0 = 1
    solve 0 _ = 0
    -- recursion
    solve i 0 = if s !! (i - 1) == '#' then 0 else dp ! (i - 1, 0)
    solve i j 
        | curC == '.' = usePeriod
        | curC == '#' = useHash
        | curC == '?' = usePeriod + useHash
      where
        curC = s !! (i - 1)
        -- if we use period, then just same as previous
        usePeriod = dp ! (i - 1, j)
        -- if we use hash, then we transition from the previous level `needed` steps ago
        useHash =
            if i >= needed && middleHash && startsWithPeriod
                then prevAns
                else 0
        middleHash = all (/='.') (substr (i - needed) i s)
        startsWithPeriod = i == needed || s !! (i - needed - 1) /= '#'
        prevAns = dp ! (max (i - needed - 1) 0, j - 1)
        needed = nums !! (j - 1)

-- substring [i, j)
substr :: Int -> Int -> [a] -> [a]
substr i j = drop i . take j

-- parsing

fileParser :: Parser [(String, [Int])]
fileParser = lineParser `sepEndBy` newline <* eof

lineParser :: Parser (String, [Int])
lineParser = do
    record <- many1 (noneOf " ") <* char ' '
    nums <- int `sepBy` char ','
    return (record, nums)
  where
    int = read <$> many1 digit

myHead (x:_) = x
