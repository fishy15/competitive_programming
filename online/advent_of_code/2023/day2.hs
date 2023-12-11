import Data.Char
import Data.Either
import System.IO

import Text.ParserCombinators.Parsec

data Round = Round { red :: Int
                   , green :: Int
                   , blue :: Int
                   } deriving (Show)

combine :: Round -> Round -> Round
combine r1 r2 = Round { red   = red r1 + red r2
                      , green = green r1 + green r2
                      , blue  = blue r1 + blue r2
                      }

maxCombine :: Round -> Round -> Round
maxCombine r1 r2 = Round { red   = max (red r1) (red r2)
                         , green = max (green r1) (green r2)
                         , blue  = max (blue r1) (blue r2)
                         }

newtype Game = Game [Round] deriving (Show)

main :: IO ()
main = do
    contents <- readFile "input.txt"
    let games = case parse fileParser "day2" contents of
                  Left err -> error $ show err
                  Right out -> out
    -- part1
    -- print $ sum $ map fst $ filter (\(id, g) -> validGame g) $ zip [1..] games
    -- part 2
    print $ sum $ map gamePower games


validGame :: Game -> Bool
validGame (Game rs) = all validRound rs

validRound :: Round -> Bool
validRound (Round r g b) = (r <= 12) && (g <= 13) && (b <= 14)

gamePower :: Game -> Int
gamePower (Game rs) = r * g * b
  where
    (Round r g b) = foldr maxCombine (Round 0 0 0) rs

-- parsing

fileParser :: Parser [Game]
fileParser = sepEndBy gameParser newline

gameParser :: Parser Game
gameParser = do
    -- read "Game _: "
    skipMany1 (noneOf ":")
    string ": "
    -- reads rounds
    rounds <- sepBy1 roundParser (string "; ")
    return $ Game rounds
    
roundParser :: Parser Round
roundParser = do
    turns <- sepBy1 gameTurnParser (string ", ")
    return $ constructRound turns
  where
    convertTurn :: (String, Int) -> Round
    convertTurn (color, quantity) | color == "red"   = Round { red = quantity, green = 0, blue = 0 }
    convertTurn (color, quantity) | color == "green" = Round { red = 0, green = quantity, blue = 0 }
    convertTurn (color, quantity) | color == "blue"  = Round { red = 0, green = 0, blue = quantity }
    convertTurn _                                    = error "not rgb"
    
    constructRound :: [(String, Int)] -> Round
    constructRound = foldr (combine . convertTurn) (Round 0 0 0)
    
gameTurnParser :: Parser (String, Int)
gameTurnParser = do
    quantity <- many1 digit
    spaces
    color <- many1 letter
    return (color, read quantity)
