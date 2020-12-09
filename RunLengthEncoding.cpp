// Nicholas Dodd, Pridhvi Myneni, Joey Rupert
#include <string.h>

// #include <cstdint>
#include <iostream>
#include <string>

#include "FileReaderWriter.cpp"
using std::cout;
using std::endl;
using std::string;

void compress(FileReaderWriter* frw) {
  //   char arr[s.length() * 5];
  //   memset(arr, 0, s.length() * 5);
  char c = '\0';
  bool started = false;
  // std::string::iterator it = s.begin();
  frw->in_file >> c;
  //   char* pointer = arr;
  uint8_t counter = 1;
  frw->in_file >> std::noskipws;
  while (!frw->in_file.eof()) {
    char e;
    frw->in_file >> e;
    if (e == c && counter < 254) {
      counter++;
    } else {
      frw->out_file << c;
      frw->out_file << char(counter & 0xff);
      // cout << "Read " << c << " times: " << (counter & 0xff) << endl;
      counter = 1;
      c = e;
    }
  }
  counter--;
  frw->out_file << c;
  frw->out_file << char(counter & 0xff);
  // cout << "Read " << c << " times: " << (counter & 0xff) << endl;
}
// aaaa*1000 -> a255 a255 a255 a255...
void decompress(FileReaderWriter* frw) {
  frw->in_file >> std::noskipws;
  while (!frw->in_file.eof()) {
    char data;
    frw->in_file >> data;
    if (frw->in_file.eof()) break;
    uint8_t times;
    char times_char;
    frw->in_file >> times;
    // cout << data << "\t";
    // cout << (times & 0xff) << endl;
    for (int i = 0; i < times; i++) {
      frw->out_file << data;
    }
  }
}

int main() {
  FileReaderWriter* frw = new FileReaderWriter("data/dummy.txt");
  compress(frw);
  frw->flush_writer();
  FileReaderWriter* frw2 =
      new FileReaderWriter("data/dummy.txtOUTPUT", "data/dummyDecoded.txt");
  decompress(frw2);
  delete frw;
  delete frw2;
  return 0;
}