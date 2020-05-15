
class Gunslinger;

class Gun
{
  public:
  //ie 6 for a 1d6
  Gun(int damageDie_, int numDamageDie_, int range_, int rangeDisadv_, int reload_, int misfire_)
  : damageDie(damageDie_), numDamageDie(numDamageDie_), range(range_), 
  rangeDisadv(rangeDisadv_), reload(reload_), misfire(misfire_) {};

  float damageDone(Gunslinger& player, int actionsLeft);

  int damageDie = 0;
  int numDamageDie = 0;
  int range = 0;
  int rangeDisadv = 0;
  int reload = 0;
  int misfire = 0;

  //equals number of shots left to fire before needing to reload
  int currentReload = 0;
};



class Gunslinger
{
  public:
  Gunslinger(int extraAttack_, int dexMod_): extraAttack(extraAttack_), dexMod(dexMod_){};
  
  //extra attack 0 to 4
  int extraAttack = 0;
  //dexMod for 100% accurate damage and such
  int dexMod = 0;

  double damageDoneRule = 0;
  double damageDoneMusket = 0;
  double damageDoneBadNews = 0;
};


class Enemy
{
public:

  int health = 0;
  int armorClass = 0;
};

