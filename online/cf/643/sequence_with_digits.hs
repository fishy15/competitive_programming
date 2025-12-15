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
import Data.Char
import Data.Int
import Data.Maybe

import Debug.Trace (trace)
import System.IO.Unsafe (unsafePerformIO)
import System.Exit (die)
import Unsafe.Coerce (unsafeCoerce)

multitest = True

data TC = TC { a :: Int64,  k :: Int64 }

input :: Scanner TC
input = do
    [a, k] <- two int64
    return TC {..}

compute :: Int64 -> Int64 -> Int64
compute a 0 = a
compute a n
    | prod == 0 = a
    | otherwise = compute (a + prod) (n - 1)
  where a_str = show a
        minDigit = ord (minimum a_str) - ord '0'
        maxDigit = ord (maximum a_str) - ord '0'
        prod = fromIntegral $ minDigit * maxDigit

solve :: TC -> Int64
solve TC {..} = compute a (k - 1)

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

int64 :: Scanner Int64
int64 = (read . C.unpack) <$> str

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

instance {-# OVERLAPPING #-} MonadFail Scanner where
    fail err = unsafeCoerce $ unsafePerformIO (die err)

class ToString a where
    toString :: a -> C.ByteString

instance ToString C.ByteString where
    toString = id

instance {-# OVERLAPPABLE #-} Show a => ToString a where
    toString = C.pack . show
