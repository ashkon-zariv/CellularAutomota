
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
using namespace std;

class Automaton
{
private:
   bool rules[8];
   string thisGen;
   string extremeBit;
   int displayWidth; 

public:
   static const int MAX_DISPLAY_WIDTH = 79;

   Automaton(int rule);
   string toStringCurrentGen();
   bool setRule(int rule);
   void resetFirstGen();
   bool setDisplayWidth(int width);
   void propagateNewGeneration();
   string applyRule(string leftPos, string midPos, string rightPos);
};

int main()
{
   int rule;

   do
   {
      cout << "Enter Rule (0 - 255): ";
      cin >> rule;
   } while (rule < 0 || rule > 255);

   Automaton Auto(rule);

   cout << "   Generation Start (0)"  << endl;
   for (int k = 0; k < 100; k++)
   {
      cout << Auto.toStringCurrentGen() << endl;
      Auto.propagateNewGeneration();
   }
   cout << "   Generation End (100)"  << endl;
}

Automaton::Automaton(int rule)
{
   setRule(rule);
   resetFirstGen();
}

void Automaton::resetFirstGen()
{
   this->displayWidth = MAX_DISPLAY_WIDTH;
   this->extremeBit = " ";
   this->thisGen = "*";
}

string Automaton::toStringCurrentGen()
{   
   string returnString;
   returnString.resize(displayWidth, extremeBit[0]);
   int retLength = returnString.length();
   int genLength = thisGen.length();
   int startPosLess = (retLength-genLength)/2;
   int startPosGreat = (genLength-retLength)/2;

   if(thisGen.length() == displayWidth)
      return thisGen;
   else if(thisGen.length() < displayWidth)
   {
      returnString.insert(startPosLess, thisGen);
      returnString.erase(retLength, genLength);
      thisGen = returnString;
      return thisGen;
   }
   else if(thisGen.length() > displayWidth)
   {
      returnString.assign(thisGen, startPosGreat, retLength);
      thisGen = returnString;
      return thisGen;
   }
}

bool Automaton::setRule(int rule)
{
   int BitVal;

   if (rule < 0 || rule > 255)
      return false;

   for(int k = 0; k < 8; k++)
   {
      BitVal = pow(2.0, 7-k);
      if ((rule&BitVal) == 0)
         rules[7-k] = false;
      else if ((rule&BitVal) == 1)
         rules[7-k] = true;
   }

   return true;
 }

bool Automaton::setDisplayWidth(int width)
{
   if(width > 0 && width <= MAX_DISPLAY_WIDTH && 
      (width&1) == true)
   {
      this->displayWidth = width;
      return true;
   }
   else
      return false;
}

string Automaton::applyRule(string leftPos, string midPos, string rightPos)
{
   string ruleString = leftPos + midPos + rightPos;
   string retString;
   int RuleNumber = 0;
   
   for(int k = 0; k < 3; k++)
   {
      if(ruleString[k] == '*')
         RuleNumber += pow(2.0, 2-k);
   }

   if(rules[RuleNumber])
      retString = "*";
   else if (!rules[RuleNumber])
      retString = " ";

   return retString;
}

void Automaton::propagateNewGeneration()
{
   int BitValue;
   string appExtremeBit, nextGen, leftPos, midPos, rightPos;

   for(int k=0; k<2; k++)
      appExtremeBit += extremeBit;

   thisGen.insert(0, appExtremeBit);
   thisGen.append(appExtremeBit);

   for(int i = 1; i < thisGen.length()-1; i++)
      nextGen += applyRule(leftPos=thisGen[i-1], midPos=thisGen[i], 
         rightPos=thisGen[i+1]);

   thisGen = nextGen;

   extremeBit = applyRule(extremeBit, extremeBit, extremeBit);
}