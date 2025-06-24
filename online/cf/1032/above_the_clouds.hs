{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import qualified Data.ByteString.Char8 as C
import qualified Data.Map as Map

import Control.Applicative
import Control.Arrow
import Control.Monad
import Control.Monad.State
import Data.Array
import Data.Maybe
import Data.Word
import Debug.Trace

main :: IO ()
main = if multitest
    then C.interact $ runScanner (numberOf input) >>> map solve >>> C.unlines
    else C.interact $ runScanner input >>> solve

--- main solution

multitest = True

data TC = TC { n :: Int, s :: C.ByteString }

input :: Scanner TC
input = do
    n <- int
    s <- str
    return TC {..}

solve TC {..} = yesno $ C.any (\c -> (Map.findWithDefault 0 c cnt) >= 2) middle
  where cnt = counter s
        middle = C.drop 1 $ C.take (n-1) s

counter :: C.ByteString -> Map.Map Char Int
counter = C.foldl' (flip $ Map.alter inc) Map.empty
  where inc = \case { Nothing -> 1; Just x -> x+1 } >>> Just

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

yesno :: Bool -> C.ByteString
yesno b = if b then "Yes" else "No"
