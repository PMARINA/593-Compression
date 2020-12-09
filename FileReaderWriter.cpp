// Nicholas Dodd, Pridhvi Myneni, Joey Rupert
#define FILE_TO_COMPRESS "data/cantrbry/asyoulik.txt"
#include <fstream>
#include <streambuf>
#include <string>
using std::ifstream;
using std::ofstream;
using std::string;

class FileReaderWriter {
 public:
  string in_file_name = "";
  string out_file_name = "";
  ifstream in_file;
  ofstream out_file;

  FileReaderWriter(string input_file_name = "", string output_file_name = "") {
    if (input_file_name == "") {
      input_file_name = FILE_TO_COMPRESS;
    }
    if (output_file_name == "") {
      output_file_name = input_file_name + string("OUTPUT");
    }
    this->in_file_name = input_file_name;
    this->in_file = ifstream(input_file_name, std::ios::binary);
    this->out_file = ofstream(output_file_name);
  }
  // Taken from https://stackoverflow.com/a/2602060
  string read_all() {
    string str;
    in_file.seekg(0, std::ios::end);
    str.reserve(in_file.tellg());
    in_file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(in_file)),
               std::istreambuf_iterator<char>());
    return str;
  }
  void write(string s) { out_file << s; }
  void flush_writer() { out_file.flush(); }
  ~FileReaderWriter() {
    in_file.close();
    out_file.close();
  }
};
// An example of using the FileReaderWriter class.
void copy_file() {
  FileReaderWriter *frw = new FileReaderWriter();
  string s = frw->read_all();
  frw->write(s);
  delete frw;
}
// int main() {
//   copy_file();
//   return 0;
// }