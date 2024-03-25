{-# LANGUAGE OverloadedStrings #-}
import Control.Monad
import Data.Array
import Data.Char
import Data.List
import Data.Maybe
import qualified Data.Text as T
import System.IO

type Stacks = Array Int String
initStack :: Stacks
initStack = listArray (1, 9) $ [
    "PGRN",
    "CDGFLBTJ",
    "VSM",
    "PZCRSL",
    "ODWCVLSP",
    "SMDWNTC",
    "PWGDH",
    "VMCSHPLZ",
    "ZGWLFPR"
    ]

data Move = Move { count :: Int, start :: Int, end :: Int}
parse :: T.Text -> Move
parse line = Move count start end
    where splitLine = T.splitOn (T.pack " ") line
          count     = read $ T.unpack $ splitLine !! 1
          start     = read $ T.unpack $ splitLine !! 3
          end       = read $ T.unpack $ splitLine !! 5

moveSeparate :: Move -> Stacks -> Stacks
moveSeparate (Move count start end) stacks = newStack
    where oldStart = stacks ! start
          oldEnd   = stacks ! end 
          newStart = drop count oldStart
          newEnd = (reverse $ take count oldStart) ++ oldEnd
          newStack = stacks // [(start, newStart), (end, newEnd)]

moveTogether :: Move -> Stacks -> Stacks
moveTogether (Move count start end) stacks = newStack
    where oldStart = stacks ! start
          oldEnd   = stacks ! end 
          newStart = drop count oldStart
          newEnd = (take count oldStart) ++ oldEnd
          newStack = stacks // [(start, newStart), (end, newEnd)]

getTops :: Stacks -> String
getTops stacks = map (!! 0) $ elems stacks

applyMoves :: (Move -> Stacks -> Stacks) -> [Move] -> Stacks -> Stacks
applyMoves move [] stacks = stacks
applyMoves move (m:ms) stacks = applyMoves move ms (move m stacks)

main :: IO ()
main = do
    contents <- map T.pack <$> drop 10 <$> lines <$> readFile "input.txt"
    let moves = map parse contents
    print $ getTops $ applyMoves moveSeparate moves initStack
    print $ getTops $ applyMoves moveTogether moves initStack