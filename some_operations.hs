{----- Question 1-----}
sumSquare :: Integral a => a -> a
sumSquare n
      | n == 1 = 1
      | otherwise = n * n + sumSquare(n-1)
{----- Question 1-----}

{----- Question 2-----}
modFunction :: Integral a => a -> a -> a
modFunction s n | s>=n = modFunction (s-n) n
                | otherwise = s

factors :: Int -> [Int]
factors n = [ m | m <- [1..n], modFunction n m == 0 ]
{----- Question 2-----}

{----- Question 3-----}
getPositiveNumbs :: (Ord a, Num a) => [a] -> [a]
getPositiveNumbs array = filter (0<) array
{----- Question 3-----}

main = do
  putStrLn "Seda Nur Taskan - 201180004"
{-
sumSquare 3
sumSquare 20
sumSquare 2

factors 6
factors 15
factors 11

getPositiveNumbs [-4,5,67,-2,-35,0,23]
getPositiveNumbs [234,3,-23,1,-5,90,-23]
getPositiveNumbs [4,-5,-67,2,35,0,-23]
-}