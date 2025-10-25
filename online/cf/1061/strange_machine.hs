{-# LANGUAGE OverloadedStrings #-}

import Control.Arrow
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe
import Data.Word
import GHC.Int
import System.IO

import qualified Data.ByteString.Char8 as C
import qualified Data.ByteString.Builder as B
import qualified Data.ByteString.Lazy as L

main :: IO ()
main = do
    t <- readInt
    replicateM_ t solveIO

solveIO = do
    [n, q] <- readInts
    s <- readLine
    let allA = C.all (\c -> c == 'A') s
    queries <- readInts 
    let ans = map (\x -> if allA then x else simulate s x) queries
    printArr ans '\n'

simulate :: C.ByteString -> Int -> Int
simulate s x = go x 0
  where len = C.length s
        go 0 n = n
        go x n | C.index s (n `mod` len) == 'A' = go (x-1) (n+1)
        go x n | otherwise                      = go (x `div` 2) (n+1)

-- fast I/O operations
readLine  = fst <$> C.spanEnd isSpace <$> C.getLine
parseInt  = C.readInt >>> fromJust >>> fst
parseInts = unfoldr (C.readInt . C.dropWhile isSpace)
readInt   = parseInt <$> C.getLine
readInts  = parseInts <$> C.getLine

printArr arr sep = B.hPutBuilder stdout builder
  where builder = foldr (\x b -> B.intDec x <> B.charUtf8 sep <> b) mempty arr


