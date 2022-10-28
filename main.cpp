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
  int eLevel = -1;
  bool operator< (const eEntry &other) const {
    return vid < other.vid;
  }
  friend std::ostream& operator << (std::ostream& os, const eEntry& entry)
  {
    os << entry.vid << " " << entry.did << " " << entry.fee << "\n";
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

std::istream& operator>>(std::istream& is, eEntry& entry){
  return is >> entry.vid >> entry.did >> entry.fee;
}

std::istream& operator>>(std::istream& is, vEntry& entry){
  return is >> entry.vid >> entry.eLevel;
}

std::istream& operator>>(std::istream& is, dEntry& entry){
  return is >> entry.did >> entry.age;
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

void sortEntriesD(){
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
  entriesD.clear();
}

int main() {
  sortEntriesE();
  sortEntriesD();
  std::vector<vEntry> vEntries = sortEntriesV();
  std::ifstream inputFileE("SortedFiles/ESorted");
  std::ofstream outputFileEandV("SortedFiles/EandVSorted");
  eEntry entryE;
  int iterator = 0;
  while (inputFileE >> entryE) {
    while (entryE.vid >= vEntries[iterator].vid){
      if (entryE.vid > vEntries[iterator].vid){
        iterator = iterator + 1;
      }
      else if (entryE.vid = vEntries[iterator].vid) {
        entryE.eLevel = vEntries[iterator].eLevel;
        outputFileEandV << entryE;
        break;
      } 
    }
  }
}
