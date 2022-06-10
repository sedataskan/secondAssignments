erkek(aaa).
erkek(bbb).
erkek(ccc).
erkek(ddd).
erkek(eee).
erkek(fff).
erkek(hhh).

kadin(iii).
kadin(jjj).
kadin(kkk).
kadin(lll).
kadin(mmm).

/* ebeveyn (cocuk, ebeveyn). */
ebeveyn(bbb, aaa).
ebeveyn(jjj, aaa).

ebeveyn(ccc, bbb).
ebeveyn(iii, bbb).
ebeveyn(ddd, bbb).

ebeveyn(kkk, jjj).

ebeveyn(eee, kkk).

ebeveyn(eee, hhh).

ebeveyn(iii, mmm).
ebeveyn(ccc, mmm).
ebeveyn(ddd, mmm).

ebeveyn(kkk, fff).

ebeveyn(jjj, lll).
ebeveyn(bbb, lll).

/* evli (A,B) - A B ile evli */
evli(aaa, lll).
evli(lll, aaa).

evli(bbb, mmm).
evli(mmm, bbb).

evli(jjj, fff).
evli(fff, jjj).

evli(kkk, hhh).
evli(hhh, kkk).

/*baba(X) - X ebeveyn ve erkek*/
baba(X) :- ebeveyn(_,X),erkek(X).
/*anne(X) - X ebeveyn ve kadin*/
anne(X) :- ebeveyn(_,X),kadin(X).

/*erkekkardes(X,Y) - X erkek ve kendisi olmayan Y(herhangi bir cinsiyet) ile kardes*/
erkekkardes(X,Y) :- erkek(X),ebeveyn(X,Z),ebeveyn(Y,Z), Y\=X.

/*kizkardes(X,Y) - X kadin ve kendisi olmayan Y(herhangi bir cinsiyet) ile kardes*/
kizkardes(X,Y) :- kadin(X),ebeveyn(X,Z),ebeveyn(Y,Z), Y\=X.

/*dede(X) - X bir anne ya da babanın ebeveynidir ve erkektir*/
dede(X) :-  ebeveyn(_,Y), ebeveyn(Y,X), erkek(X).