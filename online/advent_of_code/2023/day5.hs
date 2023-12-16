import Data.List
import Data.Maybe

import Text.ParserCombinators.Parsec

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let (init, graph) = parseInput contents
    -- let final = map (search graph) init
    -- print $ minimum final
    let initIntervals = group2 init
    let final2 = map (search2 graph) initIntervals
    print $ minimum final2

search :: [[(Int, Int, Int)]] -> Int -> Int
search graph x = foldl' getNext x graph
  where 
    getNext x [] = x
    getNext x ((src, dest, cnt):rest) = 
        if src <= x && x < src + cnt
            then dest + (x - src)
            else getNext x rest

search2 :: [[(Int, Int, Int)]] -> (Int, Int) -> Int
search2 [] (start, _) = start
search2 (layer:rest) (start, myCount) =  minimum $ (solveIntersect ++ solveNotIntersect)
  where
    solveIntersect = mapMaybe solveRest layer
    solveNotIntersect = map (search2 rest) $ getNotCovered layer (start, myCount)
    solveRest (src, dest, groupCount) = 
        if intersectionSize >= 1
            then Just $ search2 rest (intersectionStart + (dest - src), intersectionSize)
            else Nothing
      where
        myEnd = start + myCount - 1
        groupEnd = src + groupCount - 1
        intersectionStart = max start src
        intersectionEnd = min myEnd groupEnd
        intersectionSize = intersectionEnd - intersectionStart + 1

getNotCovered :: [(Int, Int, Int)] -> (Int, Int) -> [(Int, Int)]
getNotCovered intervals (start, count) = foldr splitIntervals [(start, count)] intervals
  where
    splitIntervals t = concat . map (splitInterval t)
    splitInterval (src, _, groupCount) (start, count) 
        -- cases where they do not intersect
        | srcEnd <= start = [(start, count)]
        | myEnd <= src    = [(start, count)]
        -- interval contained in other one
        | src <= start && myEnd <= srcEnd = []
        | start < src && srcEnd < myEnd = [(start, src - start + 1), (srcEnd, myEnd - srcEnd + 1)]
        -- only partial overlap
        | srcEnd < myEnd = [(srcEnd, myEnd - srcEnd)]
        | start < src    = [(start, src - start)]
      where
        myEnd = start + count
        srcEnd = src + groupCount 

group2 :: [a] -> [(a, a)]
group2 [] = []
group2 (x1:x2:xs) = (x1, x2) : group2 xs

-- parsing

split :: (a -> Bool) -> [a] -> [[a]]
split p s = case break p s of
    (a, []) -> [a]
    (a, b) -> a : split p (drop 1 b)

-- surpress warning
myHead (x:xs) = x

parseInput :: String -> ([Int], [[(Int, Int, Int)]])
parseInput s = (parseInitSeeds (myHead inputGroups !! 0), map parseGroup (drop 1 inputGroups))
  where
    inputGroups = split (== "") $ lines s

parseInitSeeds :: String -> [Int]
parseInitSeeds s = map read numbersStr
  where
    numbersStr = split (== ' ') $ drop (length "seeds: ") s

parseGroup :: [String] -> [(Int, Int, Int)]
parseGroup group = map parseTriple (drop 1 group)
    
initLineParser :: Parser (String, String)
initLineParser = do
    src <- many (noneOf "-")
    string "-to-"
    dest <- many (noneOf " ")
    return (src, dest)

parseTriple :: String -> (Int, Int, Int)
parseTriple s = case parse tripleParser "triple" s of
    Left err -> error $ show err
    Right out -> out

tripleParser :: Parser (Int, Int, Int)
tripleParser = do
    numbersStr <- sepBy (many1 digit) spaces
    let numbers = map read numbersStr
    return (numbers !! 1, numbers !! 0, numbers !! 2)

-- fileParser :: Parser ([Vertex], Graph)
-- fileParser = do
--     initSeeds <- initSeedsParser
--     spaces
--     edges <- sepEndBy edgesParser spaces
--     return (initSeeds, foldr combine M.empty edges)

-- initSeedsParser :: Parser [Vertex]
-- initSeedsParser = do
--     string "seeds: "
--     numbersStr <- sepBy (many1 digit) spaces
--     return $ map (\s -> Vertex "seed" (read s)) numbersStr

-- edgesParser :: Parser Graph
-- edgesParser = do
--     src <- many (noneOf "-")
--     string "-to-"
--     dest <- many (noneOf " ")
--     many (noneOf "\n")
--     triples <- sepBy tripleParser spaces
--     return $ foldr (addToGraph src dest) M.empty triples 
--   where
--     addToGraph src dest (srcStart, destStart, count) g = foldr (\(x, y) -> addPair src dest x y) g allPairs
--       where
--         allPairs = [(x, y) | x <- [srcStart..srcStart+count-1], y <- [destStart..destStart+count-1]]
--     addPair src dest x y g =
--         M.insert srcV (S.insert destV oldSet) g
--       where
--         srcV = Vertex src x
--         destV = Vertex dest y
--         oldSet = case M.lookup srcV g of
--             Nothing -> S.empty
--             Just v -> v
