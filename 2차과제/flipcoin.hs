sEq :: String -> Integer -> [Integer]
sEq [] s = [0]
sEq [x] s
    | x == 'H' = [0]
    | x == 'T' = [s + 1, 0]
sEq (x:xs) s
    | x == y = sEq xs (s + 1)
    | otherwise = [s + 1] ++ sEq xs (s + 1)
    where y = head xs


flipCoin :: String -> [Integer]
flipCoin xs = sEq xs 0
