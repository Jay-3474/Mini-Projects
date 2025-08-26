#include <iostream>
#include <fstream>
#include <string>

// #include<stdio.h>
// #include<json-c/json.h>

// #include <sstream>
// #include <json/json.h>

// #include <nlohmann/json.hpp>

using namespace std;

int main()
{
  fstream newfile;

  newfile.open("./vdc-update.meta", ios::in);  // open a file to perform read operation using file object
  if (newfile.is_open())
  {  // checking whether the file is open
    string tp;
    while (getline(newfile, tp))
    {  // read data from file object and put it into string.
      cout << tp << "\n";  // print the data of the string
    }
    newfile.close();  // close the file object.
  }

  //////////////////////////////////////          jsoncpp           ////////////////////////////////////

  //  ifstream file("./vdc-update.meta", ios::binary);
  //  if (!file) {
  //      cerr << "Error: Could not open vdc-update.meta" << endl;
  //      return 1;
  //  }

  //  stringstream storage;
  //  storage << file.rdbuf();
  //  string fileContent = storage.str();

  //  Json::CharReaderBuilder builder;
  //  Json::Value completeJsonData;
  //  string errs;

  //  unique_ptr<Json::CharReader> reader(builder.newCharReader());
  //  if (!reader->parse(fileContent.c_str(),
  //                     fileContent.c_str() + fileContent.size(),
  //                     &completeJsonData, &errs)) {
  //      cerr << "Error parsing JSON: " << errs << endl;
  //      return 1;
  //  }

  //  cout << "Complete JSON data:\n" << completeJsonData << endl;
  //  cout << "productName: " << completeJsonData["productName"].asString() << endl;
  //  cout << "productCode: " << completeJsonData["productCode"].asString() << endl;
  //  cout << "mdmUpdates: " << completeJsonData["mdmUpdates"] << endl;

  //////////////////////////////////////////    json-c    /////////////////////////////////////////

  // FILE *fp;
  // char buffer[1024];

  // struct json_object *parsed_json;
  // struct json_object *productName;
  // struct json_object *productCode;
  // struct json_object *mdmUpdates;
  // struct json_object *members;

  // size_t n_member;
  // size_t i;

  // fp = fopen("./vdc-update.meta", "r");
  // fread(buffer, 4096, 1, fp);
  // fclose(fp);

  // parsed_json = json_tokener_parse(buffer);

  // json_object_object_get_ex(parsed_json, "productName", &productName);
  // json_object_object_get_ex(parsed_json, "productCode", &productCode);
  // json_object_object_get_ex(parsed_json, "mdmUpdates", &mdmUpdates);

  // printf("productName: %s\n", json_object_get_string(productName));
  // printf("productCode: %s\n", json_object_get_string(productCode));

  // n_member = json_object_array_length(mdmUpdates);
  // printf("Found %lu members\n", n_member);

  // for(i=0;i<n_member;i++){
  //    members = json_object_array_get_idx(mdmUpdates,i);
  //    printf("%lu. %s\n", i+1, json_object_get_string(members));
  // }

  /////////////////////////////////     nlohmann json     //////////////////////////////////////////

  // using json = nlohmann::json;

  //    std::ifstream f("./vdc-update.meta");
  //    json data = json::parse(f);

  //    // Print the values
  //    cout << "productName: " << data.value("productName", "not found") << endl;
  //    cout << "productCode: " << data.value("productCode", "not found") << endl;
  //    cout << "mdmUpdates: " << data.at("mdmUpdates") << endl;

  return 0;
}
