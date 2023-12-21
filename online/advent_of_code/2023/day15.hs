{-# LANGUAGE ScopedTypeVariables #-}

import Data.Char
import Data.List

import Control.Monad
import Control.Monad.ST

import Data.Array
import Data.Array.ST

import System.Environment

import Text.ParserCombinators.Parsec

data Operation = Set { key :: String, value :: Int}
               | Remove { key :: String }

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    -- let inits = case parse fileParser "day15" contents of 
    --                 Left err  -> error $ show err
    --                 Right out -> out
    -- print $ sum $ map hash inits
    let ops = case parse fileParser2 "day15pt2" contents of
                  Left err  -> error $ show err
                  Right out -> out
    let finalMaps = elems $ simulateOps ops
    print $ sum $ zipWith computeValue finalMaps [1..]

simulateOps :: [Operation] -> Array Int [(String, Int)]
simulateOps ops = runSTArray compute
    where
        compute :: forall s . ST s (STArray s Int [(String, Int)])
        compute = do
            myMaps <- newArray (0, 255) []
            forM_ ops $ \op -> do
                let kHash = hash (key op)
                myMap <- readArray myMaps kHash
                writeArray myMaps kHash (process op myMap)
            return myMaps
        process (Set k v) map = insertAL k v map
        process (Remove k) map = removeAL k map

computeValue :: [(String, Int)] -> Int -> Int
computeValue m i = i * (sum $ zipWith (\(_, v) j -> v * j) m [1..])

hash :: String -> Int
hash = foldl' (\acc c -> (17 * (acc + ord c)) `rem` 256) 0

-- custom assoc list

insertAL :: Eq a => a -> b -> [(a, b)] -> [(a, b)]
insertAL k v [] = [(k, v)]
insertAL k v (first@(k1, v1):rest)
    | k == k1   = (k, v) : rest
    | otherwise = first : insertAL k v rest

removeAL :: Eq a => a -> [(a, b)] -> [(a, b)]
removeAL _ [] = []
removeAL k (first@(k1, _):rest)
    | k == k1   = rest
    | otherwise = first : removeAL k rest

-- parsing

fileParser :: Parser [String]
fileParser = many1 (noneOf ",\n") `sepBy` char ',' <* newline <* eof

fileParser2 :: Parser [Operation]
fileParser2 = (try readSet <|> readRemove) `sepBy` char ',' <* newline <* eof
  where
    readSet = do
        key <- many1 letter
        char '='
        value <- int
        return $ Set key value
    readRemove = do
        key <- many1 letter
        char '-'
        return $ Remove key
    int = read <$> many1 digit

myHead (x:_) = x
myTail (_:xs) = xs
