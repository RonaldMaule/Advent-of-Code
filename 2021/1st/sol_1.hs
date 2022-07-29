import System.IO
import Data.IORef
import qualified Data.Text    as Text
import qualified Data.Text.IO as Text
import qualified Data.Text.Read as Text
import qualified Data.Either

main :: IO()
main = do
  input_txt <- fmap Text.lines (Text.readFile "input.txt")
  let input = textToInt input_txt

  let tally = snd $ calculate input
  print tally

  return ()

calculate :: [Integer] -> (Integer, Integer)
calculate [] = (-1, 0)
calculate (x:xs)
  | x < fst result = (x, 1 + snd result)
  | otherwise = (x, snd result)
  where result = calculate xs

textToInt :: [Text.Text] -> [Integer]
textToInt txt = fmap fst $ Data.Either.rights $ fmap Text.decimal $ txt
