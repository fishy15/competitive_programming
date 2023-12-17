import qualified Data.Map as M
import Data.List

import System.Environment

import Text.ParserCombinators.Parsec

data Vertex = Vertex { vname :: String } deriving (Show, Eq, Ord)
type Graph = M.Map Vertex (Vertex, Vertex)

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let (path, graph) = case parse fileParser "day8" contents of
                            Left err  -> error $ show err
                            Right out -> out
    -- print $ length $ takeWhile (/= Vertex "ZZZ") $ getPath graph path (Vertex "AAA")
    let startLocs = filter (endsWith 'A') $ M.keys graph
    let paths = map (getPath graph path) startLocs
    let lengths = map (length . takeWhile (not . endsWith 'Z')) paths
    print $ foldl1 lcm lengths
  where 
    endsWith c (Vertex name) = name !! 2 == c

getNextLocation :: Graph -> Char -> Vertex -> Vertex
getNextLocation g dir v = case M.lookup v g of
                              Just (l, r) -> if dir == 'L' then l else r
                              Nothing     -> error ("vertex not in map: " ++ show v)

getPath :: Graph -> String -> Vertex -> [Vertex]
getPath graph path v = locations
  where
    infPath = cycle path
    locations = v : zipWith (getNextLocation graph) infPath locations



-- parsing

fileParser :: Parser (String, Graph)
fileParser = do
    path <- many letter <* newline
    newline
    edges <- vertexParser `sepEndBy` newline <* eof
    return (path, M.fromList edges)
    
vertexParser :: Parser (Vertex, (Vertex, Vertex))
vertexParser = do
    vertexName <- Vertex <$> many letter
    lVertexName <- Vertex <$> (string " = (" *> many letter)
    rVertexName <- Vertex <$> (string ", " *> many letter <* string ")")
    return (vertexName, (lVertexName, rVertexName))

myHead (x:_) = x
