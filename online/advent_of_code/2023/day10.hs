import Data.Array
import Data.List
import qualified Data.Map as M
import Data.Maybe
import qualified Data.Sequence as Seq

import System.Environment

import Text.ParserCombinators.Parsec

type Grid = Array Int (Array Int Char)

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    grid <- constructGrid <$> readFile fileName
    let sloc = findSLoc grid
    let path = getPath grid sloc
    let area = shoelace path
    print $ bfs grid sloc
    print area
    print $ area - (length path `div` 2) + 1

constructGrid :: String -> Grid
constructGrid s = listArray (0, numCols - 1) $ map (listArray (0, numRows - 1)) gridList
  where
    gridList = lines s
    numRows = length gridList
    numCols = length (gridList !! 0)

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
fns = [canMoveUp, canMoveDown, canMoveLeft, canMoveRight]

upConn    = flip elem "|LJS"
downConn  = flip elem "|7FS"
leftConn  = flip elem "-7JS"
rightConn = flip elem "-LFS"

inBounds :: Grid -> Int -> Int -> Bool
inBounds grid x y = (colL <= x && x <= colR) && (rowL <= y && y <= rowR)
  where
    (colL, colR) = bounds grid
    (rowL, rowR) = bounds (grid ! 0)

canMoveUp grid x y    = inBounds grid (x - 1) y && upConn (grid ! x ! y)    && downConn (grid ! (x - 1) ! y)
canMoveDown grid x y  = inBounds grid (x + 1) y && downConn (grid ! x ! y)  && upConn (grid ! (x + 1) ! y)
canMoveLeft grid x y  = inBounds grid x (y - 1) && leftConn (grid ! x ! y)  && rightConn (grid ! x ! (y - 1))
canMoveRight grid x y = inBounds grid x (y + 1) && rightConn (grid ! x ! y) && leftConn (grid ! x ! (y + 1))

-- shoelace

cross :: (Int, Int) -> (Int, Int) -> Int
cross (x1, y1) (x2, y2) = x1 * y2 - x2 * y1

shoelace :: [(Int, Int)] -> Int
shoelace path = 
    let crosses = sum $ map (uncurry cross) $ zip path (drop 1 $ cycle path)
        in abs crosses `div` 2


bfs :: Grid -> (Int, Int) -> Int
bfs grid (x, y) = go (Seq.singleton (x, y, 0)) M.empty
 where
    go :: Seq.Seq (Int, Int, Int) -> M.Map (Int, Int) Int -> Int
    go queue visited
        | queue == Seq.empty = maximum $ M.elems visited
        | otherwise          = go newQueue newVisited
      where
        (x, y, d) = Seq.index queue 0
        droppedQueue = Seq.drop 1 queue
        newQueue = foldr (\t q -> q Seq.|> t) droppedQueue updates
        newVisited = M.insert (x, y) d visited
        checkTransition i j fn = 
            let (nx, ny) = (x+i, y+j)
                in if fn grid x y && M.notMember (nx, ny) visited then Just (nx, ny, d + 1) else Nothing
        updates = mapMaybe (uncurry3 checkTransition) $ zip3 dx dy fns

getPath :: Grid -> (Int, Int) -> [(Int, Int)]
getPath grid sloc@(sx, sy) = go first sloc
  where
    first = (mapMaybe (uncurry3 (checkTransition sloc (-1, -1))) $ zip3 dx dy fns) !! 0
    checkTransition (x, y) (px, py) i j fn = 
        let (nx, ny) = (x+i, y+j)
            in if fn grid x y && (nx, ny) /= (px, py) then Just (nx, ny) else Nothing
    go :: (Int, Int) -> (Int, Int) -> [(Int, Int)]
    go cur prev 
        | cur == sloc = [sloc]
        | otherwise   = cur : go next cur
      where
        next = (mapMaybe (uncurry3 (checkTransition cur prev)) $ zip3 dx dy fns) !! 0

findSLoc :: Grid -> (Int, Int)
findSLoc grid = mapMaybe (\(i, j) -> if grid ! i ! j == 'S' then Just (i, j) else Nothing) allIdxs !! 0
  where
    allIdxs = [(i, j) | i <- [colL..colR], j <- [rowL..rowR]]
    (colL, colR) = bounds grid
    (rowL, rowR) = bounds (grid ! 0)

uncurry3 f (a, b, c) = f a b c

-- parsing

fileParser :: Parser [[Int]]
fileParser = nums `sepEndBy` newline <* eof
  where
    int = read <$> many1 (char '-' <|> digit)
    nums = int `sepBy` (char ' ')

myHead (x:_) = x
myLast = last
