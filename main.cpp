#include "main.hpp"

dict::dict(){
  //memset(letters, 0, 26 * sizeof(int));
  std::fill(std::begin(letters), std::end(letters), 0);
  pass = true;
}

std::vector <dict> dictionary;

int get_index(const char &c){
  int temp = -1;
  if(c >= 'A' && c <= 'Z'){
    temp = static_cast<int>(c - 'A');
  }
  if(c >= 'a' && c <= 'z'){
    temp = static_cast<int>(c - 'a');
  }
  return temp;
}

dict process_word(const std::string &here){
  uint64_t i, length = here.length();
  dict temporary;
  temporary.word = here;

  for(i = 0; i < length; i++){
    int index = get_index(here[i]);
    if(index == -1){
      std::cerr << "Error happened, :(" << std::endl;
      break;
    }else{
      ++temporary.letters[index];
    }
  }
  return temporary;
}

bool check_if_pass(const dict &source, dict &current){
  uint64_t i;
  for(i = 0; i < 26; i++){
    if(current.letters[i] > source.letters[i]){
      current.pass = false;
      break;
    }
  }
  return current.pass;
}

void load_settings(std::ifstream &settings, std::string &dictionary_file){
  if(settings.is_open()){
    getline(settings, dictionary_file);
    settings.close();
  }else{
    std::ofstream new_settings("settings.cfg");
    dictionary_file = "sowpods.txt";
    new_settings << dictionary_file;
    new_settings.close();
    std::cout << "Generating config file..." << std::endl;
  }
}

void preload_dictionary(const std::string& dictionary_file){
  std::string temporary;
  std::ifstream file(dictionary_file.c_str());

  if(dictionary.size() > 0){
    dictionary.clear();
  }

  if(file.is_open()){
    std::cout << "Dictionary file found, loading dictionary..." << std::endl;
    while(!file.eof()){
      std::getline(file, temporary);
      if (temporary.size() < 1){
        continue;
      }
      dictionary.push_back(process_word(temporary));
    }
    std::cout << "Dictionary loaded" << std::endl;
    file.close();
  }else{
    std::cerr << "Error preloading dictionary file!" << std::endl;
  }
}

void scramble(const std::string &dictionary_file){
  std::stringstream text_flow;

  std::string scrambled;
  dict scrambled_dict;

  bool check = false;
  uint64_t i, leng;

  std::cout << "Enter string to scramble: ";

  while(true){
    std::cin >> scrambled;
    std::cin.ignore();

    if(scrambled.length() > MAX_SCRAMBLED_SIZE){
      std::cout << "Please re-enter again,(" << MAX_SCRAMBLED_SIZE << ") letters only!: ";
      continue;
    }
    break;
  }

  scrambled_dict = process_word(scrambled);

  //compare?
  leng = dictionary.size();

  if(leng < 1){
    std::cerr << "Looks like dictionary is not loaded or missing..." << std::endl;
  }

  for(i = 0; i < leng; i++){
    check = check_if_pass(scrambled_dict, dictionary.at(i));
    if(check){
      text_flow << "Found word: " << dictionary.at(i).word << std::endl;
    }
  }

  std::cout << text_flow.str();
  text_flow.str("");

  std::cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << std::endl;
  
  dictionary.clear();
}

void change_dictionary(std::string &dictionary_file){
  std::string temp;
  std::cout << "Enter dictionary file: ";
  std::getline(std::cin, temp);
  dictionary_file = temp;
  std::ifstream settings("settings.cfg");
  std::cout << "Setting dictionary file to " << temp << std::endl;
  load_settings(settings, temp);
  preload_dictionary(dictionary_file);
}

int main(){
  dictionary.reserve(100);

  std::cout << "Word unscrambler by pvzzombs" << std::endl;
  std::cout << __DATE__ << ", " << __TIME__ << ", " << __cplusplus << "; " << MAJOR_VER << "." << MINOR_VER << "." << CHANGE_VER << std::endl;

  std::string dictionary_file;
  std::ifstream settings("settings.cfg");

  std::cout << "Finding config file..." << std::endl;
  load_settings(settings, dictionary_file);

  std::cout << "Preloading dictionary..." << std::endl;
  preload_dictionary(dictionary_file);

  while(true){
    std::cout << "Press any key of choice: " << std::endl;
    std::cout << "(A) Scramble. (b) Change dictionary. (c) Exit." << std::endl;
    std::cout << "==============================================" << std::endl;
    char choice;
    std::cin >> choice;
    std::cin.ignore();

    switch(choice){
      case 'a': case 'A':
        scramble(dictionary_file);
      break;
      case 'b': case 'B':
        change_dictionary(dictionary_file);
      break;
      case 'c': case 'C':
        dictionary.clear();
        exit(0);
      break;
      default:
        scramble(dictionary_file);
    }

    std::cout << std::endl << std::endl;
  }

  return 0;
}
