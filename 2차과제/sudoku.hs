itop :: Int -> (Int, Int)
itop i = (calcX i, calcY i)
  where calcX i   = i - 9 * (i `div` 9)
        calcY i   = i `div` 9

ptoi :: (Int, Int) -> Int
ptoi (x, y) = x + y * 9

colCand :: Int -> [(Int,Int)] -> [Int]
colCand p table = tracecolCand (itop p) table
  where tracecolCand (x, _) table = map (\y -> fst ( table !! ptoi (x, y) ) ) [0..8]

rowCand :: Int -> [(Int,Int)] -> [Int]
rowCand p table = tracerowCand (itop p) table
    where tracerowCand (_, y) table = map (\x -> fst( table !! ptoi (x, y) )) [0..8]

cmpBlk :: Int -> Int -> [(Int,Int)] -> Int
cmpBlk p n table
  | (snd (table !! p)) == (snd (table !! n)) = n
  | otherwise                = p

blkCand :: Int ->[(Int,Int)] -> [Int]
blkCand p table = traceblkCand p table
      where traceblkCand p table = map (\a ->fst ( table !!(cmpBlk p a table) ) )[0..80]

solsCand :: Int -> [(Int,Int)] -> [Int]
solsCand p table | p > length table  = []
                    | fst (table !! p) == 0 = [1..9] `delete'` (colCand p table ++ rowCand p table ++ blkCand p table)
                    | otherwise     = [fst (table !! p)]

delete' :: [Int] -> [Int] -> [Int]
delete' [] _       = []
delete' xs []      = xs
delete' xs (y:ys)  = delete' (deleteAll y xs) ys

deleteAll :: Int -> [Int] -> [Int]
deleteAll _ []     = []
deleteAll y (x:xs) | x == y    = deleteAll y xs
                   | otherwise = x : deleteAll y xs

rePlace :: Int -> [(Int,Int)] -> Int -> [(Int,Int)]
rePlace p table x = take p table ++ [(x ,snd ( table!!(p) ))] ++ drop (p + 1) table
nextBlank :: Int -> [(Int,Int)] -> Int
nextBlank p s | p == 80           = 80
              | fst(s !! (p + 1)) == 0 = p + 1
              | otherwise         = nextBlank (p + 1) s

solve :: Int -> [(Int,Int)]->[Int] -> [(Int,Int)]
solve 80 table []     = []
solve 80 table (x:[]) = rePlace 80 table x
solve k  table []     = []
solve p  table (x:xs)  | solvedNext == [] = solve p table xs
                        | otherwise        = solvedNext
      where tryNext p table = solve (nextBlank p table) table (solsCand (nextBlank p table) table)
            solvedNext          = tryNext p (rePlace p table x)

squigglySudoku :: [Int] -> [Int] -> [Int]
squigglySudoku val blk = [fst(x)|x<- solve 0 (zip val blk) (solsCand 0 (zip val blk) )]
