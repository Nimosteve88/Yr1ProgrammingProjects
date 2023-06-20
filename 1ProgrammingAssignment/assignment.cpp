#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string> 

std::vector<int> string_to_digits(std::string s){
    std::vector<int> out; 
    for(int i = 0; i < s.size(); i++){
       std::string digit_string;
       digit_string.push_back(s[i]);
       int digit_int = std::stoi(digit_string);
       out.push_back(digit_int);
    }
    return out;
}
bool possible_sequence(std::string digits, std::string sequence){
  bool counter = false;
  int sequencecounter = 0, proofcounter=0;  
  std:: vector<int> digitC, sequenceC;
  for(int i=0;i<10;i++){
    digitC.push_back(0);
  }
  for(int i=0;i<10;i++){
    sequenceC.push_back(0);
  }
  for(int i=0; i<digits.size() ; i++){
    std::string p;
    p.push_back(digits[i]);
    digitC[std::stoi(p)] += 1;    
  }
  for(int i=0; i<sequence.size() ; i++){
    std::string p;
    p.push_back(sequence[i]);
    sequenceC[std:: stoi(p)] += 1;
  }  
  for(int i=0; i<sequenceC.size(); i++){
    if(sequenceC[i]> 0){
      sequencecounter +=1;
    }
  }  
  for(int i=0; i<10;i++){
    if(sequenceC[i] > 0 && sequenceC[i] <= digitC[i]){
      proofcounter += 1;
    }
}
  if(proofcounter == sequencecounter){
    return true;
  }else{
    return false;
  } 
}
int score(std::string s, const std::vector<int>& values){
    int calcscore = 0;
  std:: vector <int> ints = string_to_digits(s);
  int score1 = 0;
  for(int i=0; i<ints.size(); i++){
    int c= 1, x=0, next= c +1, order=1;
    if(ints[i]+c == ints[i+c] && next<=ints.size()){
      if(ints.size()==2){      
        score1 += (values[ints[i]]+values[ints[i+1]])*2;
        i += 2;
      }else{
        x += values[ints[i]];
      while(ints[i]+c == ints[i+c] && next<=ints.size()){ 
        x += values[ints[i+c]];
        c+=1;   
        order+=1;
      }
      score1 += x*(order)  ;
      i += (order-1);
        }
      }
    else{
      score1 += values[ints[i]];
      }
    }
  return score1;
  }

int get_best_sequence(std::string digits, const std::vector<std::string>& allowed, const std::vector<int>& values, std::string& best_sequence){
    int highestscore = -2147483545; 
 for(int i=0; i<allowed.size();i++){
    if((possible_sequence(digits , allowed[i])) == true){
      if((score(allowed[i],values)) > highestscore){
        highestscore = score(allowed[i],values);
        best_sequence = allowed[i];
      }
    } 
  }
  return highestscore;
}

int main(){
    std::ifstream allowedwordsfile, valuesfile, roundsfile;
    std::ofstream outputfile;
    std::string allowedwords, values, rounds, output;
    std::vector<std:: string> stringallowedwords, stringvalues, stringrounds, stringoutput;
    std::vector<int> intvalues;
    std:: string best_sequence;
    std:: cin >> allowedwords;

    allowedwordsfile.open(allowedwords);
    if(!allowedwordsfile.is_open()){
        std:: cout << "error opening file" << std:: endl;
        return EXIT_FAILURE;
    }else{
        std::string tmp; 
        while(allowedwordsfile >> tmp){
        stringallowedwords.push_back(tmp);
        }
        allowedwordsfile.close();
    }  
    std:: cin >> values;
    valuesfile.open(values);
    if(!valuesfile.is_open()){
        std:: cout << "error opening file" << std:: endl;
        return EXIT_FAILURE;
    }else{
        std:: string tmp; 
        while(valuesfile >> tmp){
          stringvalues.push_back(tmp);     
          }
      for(int i=0; i<stringvalues.size();i++){
            int n = std:: stoi(stringvalues[i]);
            intvalues.push_back(n);
            }
        valuesfile.close();
   }
    std:: cin >> rounds;
    roundsfile.open(rounds);
    if(!roundsfile.is_open()){
        std:: cout << "error opening file" << std:: endl;
        return EXIT_FAILURE;
    }else{
        std::string tmp; 
        while(roundsfile >> tmp){
        stringrounds.push_back(tmp);
        }
         roundsfile.close();
    }
    std:: cin >> output;
    outputfile.open(output);
    if(!outputfile.is_open()){
        std:: cout << "error opening file" << std:: endl;
        return EXIT_FAILURE;
    }else{
        outputfile.close();
    }
    for(int i = 0; i < stringrounds.size(); i++){
        int bestscore = get_best_sequence(stringrounds[i], stringallowedwords, intvalues, best_sequence);
        std:: string stringbest_score = std:: to_string(bestscore);
        std:: string line = stringrounds[i] + " " + best_sequence + " " + stringbest_score;
        stringoutput.push_back(line);
    }
    outputfile.open(output);
    if(!outputfile.is_open()){
        std:: cout << "error opening file" << std:: endl;
        return EXIT_FAILURE;
    }else{
        for(int i=0; i<stringoutput.size();i++){
          outputfile << stringoutput[i] << std:: endl;
        }
        outputfile.close();
    }
}