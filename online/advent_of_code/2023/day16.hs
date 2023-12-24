import Data.Containers.ListUtils
import Data.List
import qualified Data.Sequence as Seq
import qualified Data.Set as S

import Data.Array.IArray

import System.Environment

data Direction = North | South | East | West deriving (Show, Eq, Ord)
data Vertex = Vertex { vx :: Int, vy :: Int, d :: Direction } deriving (Show, Eq, Ord)
type Grid = Array (Int, Int) Char

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    grid <- conv <$> lines <$> readFile fileName
    -- print $ energized (Vertex 0 0 East) grid
    print $ part2 grid

conv :: [String] -> Grid
conv grid = array ((0, 0), (n-1, m-1)) $ concat enumGrid
  where
    enumRow rowIdx row = zipWith (\j c -> ((rowIdx, j), c)) [0..] row
    enumGrid = zipWith enumRow [0..] grid
    n = length grid
    m = length (grid !! 0)

energized v g = length $ nubOrd $ map (\(Vertex x y _) -> (x, y)) visited
  where
    visited = bfs v g

part2 :: Grid -> Int
part2 g = maximum $ map ((flip energized) g) locations
  where
    (_, (maxRow, maxCol)) = bounds g
    topRow      = map (\col -> (Vertex 0 col South))      [0..maxCol]
    bottomRow   = map (\col -> (Vertex maxRow col North)) [0..maxCol]
    leftColumn  = map (\row -> (Vertex row 0 East))       [0..maxRow]
    rightColumn = map (\row -> (Vertex row maxCol West))  [0..maxRow]
    locations = topRow ++ bottomRow ++ leftColumn ++ rightColumn

bfs :: Vertex -> Grid -> [Vertex]
bfs (Vertex x0 y0 d0) g = S.elems $ go (Seq.fromList inits) (S.fromList inits)
  where
    inits = map (Vertex x0 y0) $ lightSplit (g ! (x0, y0)) d0
    go q visited = 
        case Seq.lookup 0 q of
            Just curV -> go (newQueue curV) (newVisited curV)
            Nothing -> visited
      where
        restQ = Seq.drop 1 q
        newV s = [v | v <- follow s g, S.notMember v visited]
        newQueue v = restQ Seq.>< (Seq.fromList $ newV v)
        newVisited v = visited `S.union` (S.fromList $ newV v)

follow :: Vertex -> Grid -> [Vertex]
follow (v@(Vertex x y d)) g =
    if valid then [Vertex nx ny nd | nd <- lightSplit newSquare d] else []
  where
    (nx, ny) = move v 
    (_, (n, m)) = bounds g
    valid = nx >= 0 && nx <= n && ny >= 0 && ny <= m
    newSquare = g ! (nx, ny)

move :: Vertex -> (Int, Int)
move (Vertex x y North) = (x - 1, y)
move (Vertex x y South) = (x + 1, y)
move (Vertex x y East)  = (x, y + 1)
move (Vertex x y West)  = (x, y - 1)

lightSplit :: Char -> Direction -> [Direction]

lightSplit '.' d = [d]

lightSplit '/' North = [East]
lightSplit '/' East  = [North]
lightSplit '/' South = [West]
lightSplit '/' West  = [South]

lightSplit '\\' North = [West]
lightSplit '\\' West  = [North]
lightSplit '\\' South = [East]
lightSplit '\\' East  = [South]

lightSplit '-' East = [East]
lightSplit '-' West = [West]
lightSplit '-' _    = [East, West]

lightSplit '|' North = [North]
lightSplit '|' South = [South]
lightSplit '|' _    = [North, South]

myHead (x:_) = x
myTail (_:xs) = xs
