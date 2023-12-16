import Data.List
import Data.Maybe

import System.Environment

import Text.ParserCombinators.Parsec

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let races = case parse fileParser "day5" contents of
                    Left err -> error $ show err
                    Right out -> out
    let sols = map (uncurry numberSols) races
    print $ product sols

numberSols :: Int -> Int -> Int
numberSols time dist = length $ filter id $ map check [0..time]
  where check t = t * (time - t) > dist

fileParser :: Parser [(Int, Int)]
fileParser = do
    times <- parseRow "Time:"
    distances <- parseRow "Distance:"
    return $ zip times distances
  where
    int = read <$> many1 digit :: Parser Int
    spaces' = many1 (char ' ') :: Parser [Char]
    -- parseRow initText = string initText *> spaces' *> int `sepBy` spaces' <* newline
    parseRow initText = combine <$> (string initText *> spaces' *> int `sepBy` spaces' <* newline)
    combine xs = [read $ concat $ map show xs]

myHead (x:_) = x
