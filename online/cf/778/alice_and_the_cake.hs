{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE FlexibleInstances #-}

import qualified Data.ByteString.Char8 as C
import qualified Data.Map as Map

import Control.Applicative
import Control.Arrow
import Control.Monad
import Control.Monad.State
import Data.Array
import Data.Char
import Data.Int
import Data.Maybe

import Data.Foldable (foldl')
import Debug.Trace (trace)
import System.IO.Unsafe (unsafePerformIO)
import System.Exit (die)
import Unsafe.Coerce (unsafeCoerce)

multitest = True

newtype TC = TC { nums :: [Int] }

input :: Scanner TC
input = do
  n <- int
  nums <- times n int
  return TC {..}

solve :: TC -> C.ByteString
solve TC {..} = if aux (msSingleton sum) initMS then "YES" else "NO"
  where initMS = msFromList nums
        initSize = length nums
        sum = foldl' (+) 0 nums
        aux curValues toConstruct
          | msSize curValues > initSize   = False
          | msIsEmpty curValues           = msIsEmpty toConstruct
          | otherwise                     =
              let (nxtValues, nxtConstruct) =
                    if msMember v toConstruct
                      then (withoutV, msDelete v toConstruct)
                      else (withHalves, toConstruct)
              in
              aux nxtValues nxtConstruct
          where
            v = msFindMax curValues 
            withoutV = msDelete v curValues
            withHalves = msInsertMany [v `div` 2, v - v `div` 2] withoutV

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
int = fst . fromJust . C.readInt <$> str

int64 :: Scanner Int64
int64 = read . C.unpack <$> str

integer :: Scanner Integer
integer = read . C.unpack <$> str

double :: Scanner Double
double = read . C.unpack <$> str

decimal :: Int -> Scanner Int
decimal p = round . ((10^p)*) <$> double

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

data Multiset a = Multiset {
    msSize :: Int,
    msMap :: Map.Map a Int
}

msEmpty :: (Ord a) => Multiset a
msEmpty = Multiset { msSize = 0, msMap = Map.empty }

msSingleton :: (Ord a) => a -> Multiset a
msSingleton v = msInsert v msEmpty

msFromList :: (Ord a) => [a] -> Multiset a
msFromList = foldl' (flip msInsert) msEmpty

msInsert :: (Ord a) => a -> Multiset a -> Multiset a
msInsert v ms = Multiset { msMap = newMap, msSize = newSize }
  where newMap = Map.insertWith (+) v 1 (msMap ms)
        newSize = msSize ms + 1

msInsertMany :: (Ord a, Foldable b) => b a -> Multiset a -> Multiset a
msInsertMany vs ms = foldl' (flip msInsert) ms vs

msDelete :: (Ord a) => a -> Multiset a -> Multiset a
msDelete v ms = Multiset { msMap = newMap, msSize = newSize }
  where newMap = Map.update subOne v (msMap ms)
        subOne x
            | x == 1    = Nothing
            | otherwise = Just $ x - 1
        newSize = msSize ms - 1

msDeleteMany :: (Ord a, Foldable b) => b a -> Multiset a -> Multiset a
msDeleteMany vs ms = foldl' (flip msDelete) ms vs

msDeleteAll :: (Ord a) => a -> Multiset a -> Multiset a
msDeleteAll v ms = Multiset { msMap = newMap, msSize = newSize }
  where newMap = Map.delete v (msMap ms)
        oldCount = msMap ms Map.! v
        newSize = msSize ms - oldCount

msMember :: (Ord a) => a -> Multiset a -> Bool
msMember v ms = Map.member v $ msMap ms

msIsEmpty :: (Ord a) => Multiset a -> Bool
msIsEmpty ms = msSize ms == 0

msFindMin :: (Ord a) => Multiset a -> a
msFindMin = fst . Map.findMin . msMap

msFindMax :: (Ord a) => Multiset a -> a
msFindMax = fst . Map.findMax . msMap
