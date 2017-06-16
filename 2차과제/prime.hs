factors :: Int -> [Int]
factors n = [x | x <- [1..n], n `mod` x == 0]

isPrime :: Int -> Bool
isPrime 1 = False
isPrime x = factors x == [1,x]

findingPrimes :: Int -> Int -> [Int]
findingPrimes a b = take b (filter isPrime [a..])
