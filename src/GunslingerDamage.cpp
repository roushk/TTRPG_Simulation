#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <map>
#include <time.h>
#include <fstream>
#include "GunslingerDamage.hpp"



int main()
{
  srand(time(NULL));

  Gun rule(8, 2, 180,600, 2, 3);

  Gun musket(12, 1, 120,480, 1, 2);
  
  Gun badNews(12, 2, 200, 600, 1, 3);

  std::ofstream myfile;
  myfile.open ("output.txt");


  Gunslinger EC0{0,5};
  Gunslinger EC1{1,5};
  Gunslinger EC2{2,5};
  Gunslinger EC3{3,5};
  Gunslinger EC4{4,5};
  std::vector<Gunslinger>gunslingers{EC0,EC1,EC2,EC3,EC4};


  double numActions = 1000000;


  for(auto& gunslinger: gunslingers)
  {
    gunslinger.damageDoneMusket += musket.damageDone(gunslinger, numActions);
    gunslinger.damageDoneRule += rule.damageDone(gunslinger, numActions);
    gunslinger.damageDoneBadNews += badNews.damageDone(gunslinger, numActions);
  }
  

  for(auto& gunslinger: gunslingers)
  {
    gunslinger.damageDoneMusket /= (numActions);
    gunslinger.damageDoneRule /= (numActions);
    gunslinger.damageDoneBadNews /= (numActions);
  }

  std::cout << numActions << " Number of Actions Simulated" << std::endl;
  myfile << numActions << " Number of Actions Simulated" << std::endl;
  for(unsigned i = 0; i < gunslingers.size(); ++i)
  {
    std::cout << "Extra Attack " << i << ":" << std::endl;
    std::cout << "  Avg Musket Damage Per Round:" << gunslingers[i].damageDoneMusket << std::endl;
    std::cout << "  Avg Rule Damage Per Round:" << gunslingers[i].damageDoneRule << std::endl;
    std::cout << "  Avg Bad News Damage Per Round:" << gunslingers[i].damageDoneBadNews << std::endl;

    myfile << "Extra Attack " << i << ":" << std::endl;
    myfile << "  Avg Musket Damage Per Round:" << gunslingers[i].damageDoneMusket << std::endl;
    myfile << "  Avg Rule Damage Per Round:" << gunslingers[i].damageDoneRule << std::endl;
    myfile << "  Avg Bad News Damage Per Round:" << gunslingers[i].damageDoneBadNews << std::endl;
  }

  myfile.close();
  return 0;
}

float Gun::damageDone(Gunslinger& player, int actionsLeft)
{
  //assuming over 2 turns to handle the repairing the weapon from a misfire in the same loop

  float damageDone = 0;
  

  while(actionsLeft > 0)  //while 1+
  {
    --actionsLeft;

    //get number of attack actions left
    int attacksLeft = player.extraAttack + 1;

    while(attacksLeft > 0)
    {
      //will subtract if reload, misfire, or attack
      --attacksLeft;

      //Case 1: if we need to reload
      if(currentReload <= 0)
      {
        //Reload
        currentReload = reload;
        //subtract from attacks left

        continue;
      }

      //Case 2: We have a bullet and can fire
      

      int chanceToHit = (rand() % 20);  //roll D20

      /*Whenever you make an attack roll with a firearm, and the dice roll is 
      equal to or lower than the weapon’s Misfire score, the weapon misfires. 
      */
      if(chanceToHit <= misfire)  //based on rule
      {
        //subtract number of actions to simulate using action to sucessfully fix the weapon
        //not dealing with if the weapon breaks as over several thousand iterations it will
        --actionsLeft;
        currentReload = 0;

        //going to return 0 damage done but doesn't deal with exactly when the misfire happens
        break;
      }
      --currentReload;
      //roll all the dice
      for(unsigned i = 0; i < numDamageDie; ++i)
      {
        //change the range to 0 to damage die - 1 then add 1
        damageDone += (rand() % damageDie) + 1;
      }

      
    }
  }

  return damageDone;
}


