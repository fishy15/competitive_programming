import Data.List
import Data.Maybe

import System.Environment

import Text.ParserCombinators.Parsec

data Card = Card Char deriving (Show, Eq)
data Hand = Hand [Card] deriving (Show, Eq)
data HandType = HighCard 
              | OnePair 
              | TwoPair
              | ThreeOfAKind
              | FullHouse
              | FourOfAKind 
              | FiveOfAKind
              deriving (Show, Eq, Ord)

data HandJoker = HandJoker { newHand :: Hand, oldHand :: Hand } deriving (Show, Eq)

instance Ord Card where
    compare (Card c1) (Card c2) = compare (getIndex c1) (getIndex c2)
      where
        cardOrder = "123456789TJQKA" -- 1 replacement for J later
        getIndex c = fromJust $ elemIndex c cardOrder

instance Ord Hand where
    compare hand1@(Hand h1) hand2@(Hand h2)
        = if getType hand1 == getType hand2
              then compare h1 h2
              else compare (getType hand1) (getType hand2)

instance Ord HandJoker where
    compare hand1@(HandJoker nh1 (Hand oh1)) hand2@(HandJoker nh2 (Hand oh2))
        = if getType nh1 == getType nh2
              then compare oh1 oh2
              else compare (getType nh1) (getType nh2)

getType :: Hand -> HandType
getType (Hand hand) = case groupSizes of
                    (5:_)   -> FiveOfAKind
                    (4:_)   -> FourOfAKind
                    (3:2:_) -> FullHouse
                    (3:_)   -> ThreeOfAKind
                    (2:2:_) -> TwoPair
                    (2:_)   -> OnePair
                    _       -> HighCard
  where
    groups = group $ sort hand
    groupSizes = reverse $ sort $ map length groups 

main :: IO ()
main = do
    fileName <- myHead <$> getArgs
    contents <- readFile fileName
    let handBids = case parse fileParser "day7" contents of
                       Left err  -> error $ show err
                       Right out -> out
    -- let results = sort handBids
    let results = sort $ map (\(h, bid) -> (findBestReplacement h, bid)) handBids
    print $ sum $ zipWith (\(_, bid) idx -> bid * idx) results [1..]

replaceJokers :: Hand -> [Hand]
replaceJokers hand@(Hand h) =
    case elemIndex (Card 'J') h of
        Just i  -> concat $ map replaceJokers $ map (replace i) cards
        Nothing -> [hand]
  where
    replace :: Int -> Card -> Hand
    replace i card = let (prefix, _:suffix) = splitAt i h
        in Hand $ prefix ++ [card] ++ suffix
    cardOrder = "23456789TQKA"
    cards = map Card cardOrder

findBestReplacement :: Hand -> HandJoker
findBestReplacement originalHand@(Hand oh) = HandJoker newHand originalHandSub
  where 
    newHand = maximum $ replaceJokers originalHand
    originalHandSub = Hand $ replace (Card 'J') (Card '1') oh

replace :: (Eq a) => a -> a -> [a] -> [a]
replace a b = map (\x -> if x == a then b else x)

-- parsing

fileParser :: Parser [(Hand, Int)]
fileParser = rowParser `sepEndBy` newline <* eof
    
rowParser :: Parser (Hand, Int)
rowParser = do
    cardValues <- many (letter <|> digit) <* char ' '
    bid <- int
    return (Hand $ map Card cardValues, bid)
  where
    int = read <$> many1 digit

myHead (x:_) = x
