{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE FlexibleInstances #-}

import qualified Data.ByteString.Char8 as C

import Control.Applicative
import Control.Arrow
import Control.Monad
import Control.Monad.State
import Data.Array
import Data.Maybe
import Debug.Trace

multitest = True

data TC = TC { s :: C.ByteString }

input :: Scanner TC
input = do
    s <- str
    return TC {..}

solve :: TC -> C.ByteString
solve TC {..} = 
    if C.count 'N' s /= 1
        then "YES" 
        else "NO"

-- modified from https://github.com/byorgey/comprog-hs/blob/master/ScannerBS.hs

main :: IO ()
main = if multitest
    then C.interact $ runScanner (numberOf input) >>> map (toString . solve) >>> C.unlines
    else C.interact $ runScanner input >>> solve >>> toString

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

class ToString a where
    toString :: a -> C.ByteString

instance ToString C.ByteString where
    toString = id

instance {-# OVERLAPPABLE #-} Show a => ToString a where
    toString = C.pack . show
