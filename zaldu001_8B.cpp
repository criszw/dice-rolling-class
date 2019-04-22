#include <iostream>
#include <cstdlib>

using namespace std;
class Dice {
  
  private:
  
    int min, max;
    
  public:
  
    Dice(){
      min = 0;
      max = 0;
    }
    
    Dice(int mn, int mx){
      min = mn;
      max = mx;
    }
    
    friend ostream & operator<<(ostream &out, Dice c);
    
    int randomRoll() {
      int roll = rand()%(max+1) + min;
      return roll;
    }
    
    int* roll(int n) {
      int* list = new int[n];
      for(int i =0; i <n; i++) {
        list[i] = randomRoll();
      }
      cout << endl;
      return list;
    }
};
    
ostream & operator<<(ostream &out, Dice c) {
  out << c.randomRoll();
  return out; 
}



int* startEndPairs(string s);

int main()
{
  srand(time(0)); // DO NOT WRITE THIS LINE AGAIN OR ANYWHERE ELSE
  cout << "What do you want to roll?  ";
  string s;
  getline(cin, s);
  int* pairs = startEndPairs(s); // DOTH NOT FORGET TO DELETE ME
  
  // here is what you have
  cout << "How many rounds do you want to roll? ";
  int n;
  cin >> n;
  
  //get total number of dice rolled per round
  int count = (pairs[0] - 1) / 2;

  
  //create dynamic array
  int* allDice[count];
  for(int i=0; i < count; i++)
  {
    Dice c_i = Dice(pairs[i], pairs[i+1]);
    allDice[i] = c_i.roll(n);
  }


  //get array of sums per round for all n rounds
  int sum[n];
  for( int i =0; i < n; i++) {
    sum[i] = 0;
  }
  
  
  for( int j =0; j < n; j++) {
    for(int k =0; k < count; k++) {
      sum[j] += allDice[k][j];
      
    }
  }
  
  
  //get min, max and avg roll
  int maximum = sum[0];
  int minimum = sum[0];
  double avg = sum[0];
  for(int k = 1; k< n; k++) {
    if (sum[k] > maximum) {
      maximum = sum[k];
    }
    if(sum[k] < minimum) {
		minimum = sum[k];
	}
    avg += sum[k];
  } 
  avg = avg/n;
  
  
  //print results
  
  cout << "Minimum roll: " << minimum << endl;
  cout << "Maximum roll: " << maximum << endl;
  cout << "Average roll: " << avg << endl;
}


int* startEndPairs(string s)
{
  // count how many '+'s or 'd's there are...
  int parts = 0;
  for(int i=0; i < static_cast<signed>(s.length()); i++)
  {
    if(s[i] == 'd' || s[i] == '+')
    {
      parts++;
    }
  }
  // ... so we can make the correct size array to store the info
  string* data = new string[2*parts];
  
  int index=0;
  unsigned d = s.find('d');
  unsigned p = s.find('+');
  while(d != static_cast<unsigned>(-1) || p != static_cast<unsigned>(-1))
  {
    bool dFirst = d < p;
    if(dFirst)
    {
      string before = s.substr(0,d); // part before the 'd' (should be just one number)
      // figure out what number is after 'd'
      int count = 0;
      bool foundDigit=false;          
      for(int i=0; i< static_cast<signed>(s.length()-d-1); i++)
      {
        if(isdigit(s[count+d+1]))
        {
          foundDigit=true;
        }
        if(!isdigit(s[count+d+1]) && foundDigit)
        {
          break;
        }
        count++;
      }
      string after = s.substr(d+1,count); //should be just the number after 'd'
      
      // store these two parts
      data[index] = before;
      data[index+1] = after;
      index+=2;
      
      
      // remove this part from the string s
      s = s.substr(d+count+1); // discard these two parts
    }
    else // same idea for the '+'
    {
      // figure out what number is after '+'
      int count = 0;          
      bool foundDigit=false;
      for(int i=0; i< static_cast<signed>(s.length()-p-1); i++)
      {
        if(isdigit(s[count+p+1]))
        {
          foundDigit=true;
        }
        if(!isdigit(s[count+p+1]) && foundDigit)
        {
          break;
        }
        count++;
      }
      string after = s.substr(p+1,count); //should be just the number after '+'

      // store this part
      data[index] = "+";
      data[index+1] = after;
      index+=2;
      
      
      // remove this part from the string s
      s = s.substr(p+count+1); // discard these two parts
    }
  
  // update d and p for next loop interation  
  d = s.find('d');
  p = s.find('+');

  }
  
  // now we need to figure out how many dice there are (as 2d4 is 2 dice)
  // we will treat "+2" as a dice that rolls [2,2]
  int diceCount = 0;
  for(int i=0; i < parts*2; i+=2)
  {
    if(data[i][0] == '+')
    {
      diceCount++;
    }
    else
    {
      diceCount+=atoi(data[i].c_str());
    }
  }
  
  int* dice = new int[diceCount*2+1]; // one extra to store the size
  dice[0] = diceCount*2+1; // put size in first index
  
  int ind=1; // index for the "dice" array (as not same as data array)
  for(int i=0; i < parts*2; i+=2)
  {
    // if we have a +, add a "Dice" that has a range of 0
    if(data[i][0] == '+')
    {
      dice[ind] = atoi(data[i+1].c_str());
      dice[ind+1] = atoi(data[i+1].c_str());
      
      ind+=2;
    }
    else // otherwise add however many of the dice requested
    {
      for(int j=0; j < atoi(data[i].c_str()); j++)
      {
        dice[ind] = 1;
        dice[ind+1] = atoi(data[i+1].c_str());
        
        ind += 2;
      }
    }
  }
  
  return dice;
}
