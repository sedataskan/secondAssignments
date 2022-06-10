import itertools

class Item:
  def __init__(self, id, weight, value):
    self.id     = id
    self.weight = weight
    self.value  = value

class Sack:
  def __init__(self, items):
    self.items = items

  def weight(self):
    return sum([x.weight for x in self.items])

  def value(self):
    return sum([x.value for x in self.items])

  def ids(self):
    return ', '.join([str(x.id) for x in self.items])

  def __repr__(self):
    return "{0:10} {1:10}   {2}".format(self.weight(), self.value(), self.ids())

def powerset(iterable):
  s = list(iterable)
  return itertools.chain.from_iterable(itertools.combinations(s, r) for r in range(len(s)+1))

def item_list(n,kapasite):
  items = []
  objes = ['A','B','C','D','E']
  for i in range(1,n+1):
    w =int(input(objes[i-1]+" elemani icin agirlik giriniz: "))
    while w>kapasite or w<1:
      w =int(input(objes[i-1]+" elemani icin tekrar agirlik giriniz: "))
      
    v =int(input(objes[i-1]+" elemani icin deger giriniz: "))
    while v>25 or v<1:
      v =int(input(objes[i-1]+" elemani icin tekrar deger giriniz: "))
      
    items.append(Item(id = objes[i-1], weight = w, value = v))
  return items

def knapsack(items,capacity):
  print("------------------------------")
  print("{0:>10} {1:>10}   {2}".format("Agirlik","Deger","Secilenler"))
  fit_comb = []
  all_comb = []
  for sackitems in powerset(items):
    sack = Sack(sackitems)
    if sack.weight()>capacity:
      all_comb.append(sack)
    else:
      print(sack)
      all_comb.append(sack)
      fit_comb.append(sack)

  print("------------------------------")
  optimal = max(fit_comb, key=lambda x: x.value())
  print("\nEn optimal durum \n" + str(optimal))
  
  print("\n--------Tum durumlar----------")
  print("{0:>10} {1:>10}   {2}".format("Agirlik","Deger","Secilenler"))
  
  for x in all_comb:
    print(x)

def main():
  
  kapasite  = int(input("Canta kapasitesi giriniz: "))
  while kapasite>25 or kapasite<5:
    kapasite  = int(input("Canta kapasitesini tekrar giriniz: "))
  numitems  = 5
  print("\nGirilecek urun sayisi 5'dir.\n")

  knapsack(item_list(numitems,kapasite),kapasite)

main() 
