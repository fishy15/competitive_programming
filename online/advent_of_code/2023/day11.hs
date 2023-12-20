import Data.Array
import Data.List
import qualified Data.Map as M
import Data.Maybe
import qualified Data.Sequence as Seq

import System.Environment

import Text.ParserCombinators.Parsec

emptyCost = 1000000

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    grid <- lines <$> readFile fileName
    let galaxies = findGalaxies grid
    let rowPsum = getPsum grid
    let colPsum = getPsum (transpose grid)
    let getDist = \(x1, y1) (x2, y2) -> getSum rowPsum x1 x2 + getSum colPsum y1 y2
    print $ sum $ map (uncurry getDist) $ getPairs galaxies

findGalaxies :: [String] -> [(Int, Int)]
findGalaxies grid = [(x, y) | ('#', x, y) <- concat labeledGrid]
  where
    labeledGrid = zipWith (\rowNum -> zipWith (\colNum c -> (c, rowNum, colNum)) [0..]) [0..] grid

getPairs :: [a] -> [(a, a)]
getPairs xs = [(x, y) | (x:rest) <- tails xs, y <- rest]

getPsum :: [String] -> Array Int Int
getPsum grid = listArray (0, len - 1) psums
  where
    psums = psum 0 $ map (\b -> if b then emptyCost else 1) isEmpty
    len = length psums
    isEmpty = map (all (=='.')) grid

getSum :: Array Int Int -> Int -> Int -> Int
getSum ps x y
    | x > y     = getSum ps y x
    | otherwise = ps ! y - ps ! x

psum :: Num a => a -> [a] -> [a]
psum acc [] = [acc]
psum acc (x:xs) = acc : psum (acc + x) xs

myHead (x:_) = x

