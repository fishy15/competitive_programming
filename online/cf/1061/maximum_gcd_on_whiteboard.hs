{-# LANGUAGE OverloadedStrings #-}

import Control.Arrow
import Control.Monad
import Control.Monad.ST
import Data.Array.ST
import Data.Char
import Data.List
import Data.Maybe
import Data.Word
import Debug.Trace
import GHC.Int
import System.IO

import qualified Data.Array.Unboxed as A
import qualified Data.ByteString.Char8 as C
import qualified Data.ByteString.Builder as B
import qualified Data.ByteString.Lazy as L

main :: IO ()
main = do
  t <- readInt
  replicateM_ t solveIO

solveIO = do
  [n, k] <- readInts
  nums <- readInts
  let counts = getCounts n nums
  -- acc is (Maybe ans, bigSum)
  let ans = forAcc (Nothing, 0) [n,n-1..2] $ \acc x -> 
        case acc of
          (Just ans, _) -> acc
          (_, bigSum) ->
            let newBig = bigSum
                  + (fromMaybe 0 (safeIndex counts (4 * x)))
                  + (fromMaybe 0 (safeIndex counts (4 * x + 1)))
                  + (fromMaybe 0 (safeIndex counts (4 * x + 2)))
                  + (fromMaybe 0 (safeIndex counts (4 * x + 3))) in
            let smallMultiples = (sumMultiples x counts (4 * x)) in
            let needDelete = n - newBig - smallMultiples in
            if needDelete <= k
              then (Just x, newBig)
              else (Nothing, newBig)
  print $ fromMaybe 1 $ fst ans
 
forAcc :: b -> [a] -> (b -> a -> b) -> b
forAcc init xs f = foldl' f init xs

getCounts :: Int -> [Int] -> A.UArray Int Int
getCounts n xs = runSTUArray $ do
  counts <- newArray (1, n) 0 :: ST s (STUArray s Int Int)
  forM_ xs $ \x -> do
      oldCount <- readArray counts x
      writeArray counts x (oldCount+1)
  return counts

sumMultiples :: Int -> A.UArray Int Int -> Int -> Int
sumMultiples n xs limit = go n 0
  where go cur acc = 
          if cur < limit
            then case (safeIndex xs cur) of
                  Nothing -> acc
                  Just cnt -> go (cur + n) (acc + cnt)
            else acc

safeIndex :: A.UArray Int Int -> Int -> Maybe Int
safeIndex arr x = 
  let (l, r) = A.bounds arr in
  if l <= x && x <= r
    then Just (arr A.! x) 
    else Nothing

-- fast I/O operations
readLine = fst <$> C.spanEnd isSpace <$> C.getLine
parseInt = C.readInt >>> fromJust >>> fst
parseInts = unfoldr (C.readInt . C.dropWhile isSpace)
readInt  = parseInt <$> C.getLine
readInts = parseInts <$> C.getLine

printArr arr sep = B.hPutBuilder stdout builder
  where builder = foldr (\x b -> B.intDec x <> B.charUtf8 sep <> b) mempty arr



