#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class eEntry{
  public:
  int vid;
  int did;
  int fee;
  int eLevel = 0;
  bool operator< (const eEntry &other) const {
    return vid < other.vid;
  }
  friend std::ostream& operator << (std::ostream& os, const eEntry& entry)
  {
    os << entry.vid << " " << entry.did << " " << entry.fee << " " << entry.eLevel << "\n";
    return os;
  }
};


class vEntry{
  public:
  int vid;
  int eLevel;

  bool operator< (const vEntry &other) const {
    return vid < other.vid;
  }
  friend std::ostream& operator << (std::ostream& os, const vEntry& entry)
  {
    os << entry.vid  << " " << entry.eLevel << " " << "\n";
    return os;
  }
};

class dEntry{
  public:
  int did;
  int age;

  bool operator< (const dEntry &other) const {
    return did < other.did;
  }
  friend std::ostream& operator << (std::ostream& os, const dEntry& entry)
  {
    os << entry.did << " " << entry.age << "\n";
    return os;
  }
};

class evEntry{
  public:
  int vid;
  int did;
  int fee;
  int eLevel = 0;
  bool operator< (const evEntry &other) const {
    return did < other.did;
  }
  friend std::ostream& operator << (std::ostream& os, const evEntry& entry)
  {
    os << entry.vid << " " << entry.did << " " << entry.fee << " " << entry.eLevel << "\n";
    return os;
  }
};

class allEntry{
  public:
  int vid;
  int did;
  int fee;
  int eLevel = 0;
  int age = 0;
  bool operator< (const allEntry &other) const {
    return eLevel < other.eLevel;
  }
  friend std::ostream& operator << (std::ostream& os, const allEntry& entry)
  {
    os << entry.vid << " " << entry.did << " " << entry.fee << " " << entry.eLevel << " " << entry.age << "\n";
    return os;
  }
};

std::istream& operator>>(std::istream& is, eEntry& entry){
  return is >> entry.vid >> entry.did >> entry.fee;
}

std::istream& operator>>(std::istream& is, vEntry& entry){
  return is >> entry.vid >> entry.eLevel;
}

std::istream& operator>>(std::istream& is, dEntry& entry){
  return is >> entry.did >> entry.age;
}

std::istream& operator>>(std::istream& is, evEntry& entry){
  return is >> entry.vid >> entry.did >> entry.fee >> entry.eLevel;
}

std::istream& operator>>(std::istream& is, allEntry& entry){
  return is >> entry.vid >> entry.did >> entry.fee >> entry.eLevel;
}

void sortEntriesE() {
  std::ifstream inputFileE("UnsortedFiles/EFile");

  std::vector<eEntry> entriesE;
  eEntry entryE;

  while (inputFileE >> entryE)
  {
      entriesE.push_back(entryE);
  }
  inputFileE.close();

  std::sort(entriesE.begin(), entriesE.end());
  std::ofstream outputFileE("SortedFiles/ESorted");
  for (const auto &e : entriesE) outputFileE << e;
  outputFileE.close(); 
  entriesE.clear();  
}

std::vector<vEntry> sortEntriesV(){
  std::ifstream inputFileV("UnsortedFiles/VFile");
  std::vector<vEntry> entriesV;
  vEntry entryV;

  while (inputFileV >> entryV)
  {
      entriesV.push_back(entryV);
  }
  inputFileV.close();

  std::sort(entriesV.begin(), entriesV.end());
  std::ofstream outputFileV("SortedFiles/VSorted");
  for (const auto &e : entriesV) outputFileV << e;
  outputFileV.close(); 
  return entriesV;
}

std::vector<dEntry> sortEntriesD(){
  std::ifstream inputFileD("UnsortedFiles/DFile");
  std::vector<dEntry> entriesD;
  dEntry entryD;

  while (inputFileD >> entryD)
  {
      entriesD.push_back(entryD);
  }
  inputFileD.close();

  std::sort(entriesD.begin(), entriesD.end());
  std::ofstream outputFileD("SortedFiles/DSorted");
  for (const auto &e : entriesD) outputFileD << e;
  outputFileD.close(); 
  return entriesD;
}

int main() {
  sortEntriesE();
  std::vector<vEntry> vEntries = sortEntriesV();

  //SORT E AND V
  std::ifstream inputFileE("SortedFiles/ESorted");
  std::vector<evEntry> evEntries;
  evEntry entryEV;
  int iterator = 0;
  while (inputFileE >> entryEV) {
    while (entryEV.vid >= vEntries[iterator].vid){
      if (entryEV.vid > vEntries[iterator].vid){
        iterator = iterator + 1;
      }
      else if (entryEV.vid == vEntries[iterator].vid) {
        entryEV.eLevel = vEntries[iterator].eLevel;
        evEntries.push_back(entryEV);
        break;
      } 
    }
  }
  //Sort EV by DID
  std::sort(evEntries.begin(), evEntries.end());
  std::ofstream outputFileEandV("SortedFiles/EandVSorted");
  for (const auto &e : evEntries) outputFileEandV << e;
  evEntries.clear(); //Not needed
  inputFileE.close();
  outputFileEandV.close();
  std::ifstream inputFileEandV("SortedFiles/EandVSorted");
  std::vector<dEntry> dEntries = sortEntriesD();
  std::vector<allEntry> allEntries;
  allEntry entryALL;
  iterator = 0;
  while (inputFileEandV >> entryALL) {
    while (entryALL.did >= dEntries[iterator].did){
      if (entryALL.did > dEntries[iterator].did){
        iterator = iterator + 1;
      }
      else if (entryALL.did == dEntries[iterator].did) {
        entryALL.age = dEntries[iterator].age;
        allEntries.push_back(entryALL);
        break;
      } 
    }
  }
  dEntries.clear();  //Not needed anymore
  //Sort allEntries by eLevel
  std::sort(allEntries.begin(), allEntries.end());
  
  //Printing the results
  int initialE = allEntries[0].eLevel;
  int count = 0;
  double avgXFee = 0;
  double avgDAge = 0;
  std::cout << "eLevel Count AVG(X.Fee) AVG(D.Age)" << "\n";
  std::cout << "----------------------------------" << "\n";
  for (const auto &e : allEntries) {
    if (initialE == e.eLevel) {
      count++;
      avgXFee = avgXFee + e.fee;
      avgDAge = avgDAge + e.age;
    } else {
      initialE = e.eLevel;
      avgXFee = avgXFee/count;
      avgDAge = avgDAge/count;
      std::cout << initialE << " " << count << " " << avgXFee << " " << avgDAge << "\n";
      count = 1;
      avgXFee = e.fee;
      avgDAge = e.age;
    }
  }
  avgXFee = avgXFee/count;
  avgDAge = avgDAge/count;
  std::cout << initialE << " " << count << " " << avgXFee << " " << avgDAge << "\n";
  allEntries.clear();
}
