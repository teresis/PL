makeTable :: [int] -> [int] ->[(int, int)]
makeTable x y = zip x y

returnNthval :: [(Int,Int)]-> Int -> Int
returnNthval xs y = fst (xs!!y)

returnNthfield ::[(Int,Int)]->Int -> Int
returnNthfield xs y = snd (xs!!y)

replaceNth index iter newVal sub (x:xs) 
    | iter == 0 = (newVal, (sub!!index)):xs
    | otherwise = x:replaceNth index (iter-1) sub newVal xs

--solveSudoku :: [int]-> [int] ->[(int,int)]
--solveSudoku vals subs = setSudoku (makeTable vals subs) 0 0

--setSudoku :: [(int,int)]-> int ->int-> [(int,int)]
--setSudoku (x:xs) index val 
--      |(fst ( (x:xs)!!index))/= 0 = setSudoku xs (index-1) 0
--      | otherwise = checkingSudoku (x:xs) index val
--
--printSudoku :: [(int,int)] ->[int]
--printSudoku xs = [ d | d<-(fst c), c<-[xs] ]

