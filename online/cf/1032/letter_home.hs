{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import qualified Data.ByteString.Char8 as C

import Control.Applicative
import Control.Arrow
import Control.Monad
import Control.Monad.State
import Data.Array
import Data.Maybe
import Debug.Trace

main :: IO ()
main = if multitest
    then C.interact $ runScanner (numberOf input) >>> map (showB . solve) >>> C.unlines
    else C.interact $ runScanner input >>> solve >>> showB

--- main solution

multitest = True

data TC = TC { n :: Int, xs :: Array Int Int, s :: Int }

input :: Scanner TC
input = do
    n <- int
    s <- int
    xs <- listArray (0, n-1) <$> times n int
    return TC {..}

solve TC {..}
    | s <= first = rightDist
    | s >= last = leftDist
    | otherwise = leftDist + rightDist + min leftDist rightDist
  where first = xs ! 0
        last = xs ! (n-1)
        leftDist = abs $ s - first
        rightDist = abs $ last - s

-- modified from https://github.com/byorgey/comprog-hs/blob/master/ScannerBS.hs
type Scanner = State [C.ByteString]

runScanner :: Scanner a -> C.ByteString -> a
runScanner = runScannerWith C.words

runScannerWith :: (C.ByteString -> [C.ByteString]) -> Scanner a -> C.ByteString -> a
runScannerWith t s = evalState s . t

str :: Scanner C.ByteString
str = get >>= \case { s:ss -> put ss >> return s }

int :: Scanner Int
int = (fst . fromJust . C.readInt) <$> str

integer :: Scanner Integer
integer = (read . C.unpack) <$> str

double :: Scanner Double
double = (read . C.unpack) <$> str

decimal :: Int -> Scanner Int
decimal p = (round . ((10^p)*)) <$> double

numberOf :: Scanner a -> Scanner [a]
numberOf s = int >>= flip replicateM s

times :: Int -> Scanner a -> Scanner [a]
times = replicateM

two, three, four :: Scanner a -> Scanner [a]
[two, three, four] = map times [2..4]

pair :: Scanner a -> Scanner b -> Scanner (a,b)
pair = liftA2 (,)

showB :: Show a => a -> C.ByteString
showB = C.pack . show
