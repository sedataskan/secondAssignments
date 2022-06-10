gcd(Z,0,Z).
gcd(X,Y,Z) :- 
    Y > 0,
    T is Y,
    Y1 is X mod Y,
    X1 is T,
    gcd(X1,Y1,Z).