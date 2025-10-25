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
    -- sols <- forM [0..t-1] $ \_ -> do
    --     [x, y] <- readInts
    --     return $ solve x y
    -- printArr sols '\n'

solveIO = do
    x <- readInt
    print $ ((x + 1) `div` 2) - 1

-- fast I/O operations
parseInt = C.readInt >>> fromJust >>> fst
parseInts = unfoldr (C.readInt . C.dropWhile isSpace)
readInt  = parseInt <$> C.getLine
readInts = parseInts <$> C.getLine

printArr arr sep = B.hPutBuilder stdout builder
  where builder = foldr (\x b -> B.intDec x <> B.charUtf8 sep <> b) mempty arr

