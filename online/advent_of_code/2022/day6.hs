{-# LANGUAGE OverloadedStrings #-}
import Control.Monad
import Data.Array
import Data.Char
import Data.List
import Data.Maybe
import qualified Data.Text as T
import System.IO

allDiff :: String -> Bool
allDiff [] = True
allDiff (c:cs) = (not $ any (==c) cs) && allDiff cs

findDiffPos :: String -> Int -> Int
findDiffPos msg len = length msg - findDiffPos' msg len + len
    where findDiffPos' msg len = if allDiff $ take len msg
                                    then length msg
                                    else findDiffPos' (tail msg) len

main :: IO ()
main = do
    contents <- readFile "input.txt"
    print $ findDiffPos contents 4
    print $ findDiffPos contents 14