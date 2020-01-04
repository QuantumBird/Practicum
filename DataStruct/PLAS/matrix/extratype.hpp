#include <string>
#pragma once
//////////////////////////////////////
template<typename T>
class Type {
public:
  std::string type = "";
};

template<>
class Type<int> {
public:
  std::string type = "int";
};

template<>
class Type<long> {
public:
  std::string type = "long";
};

template<>
class Type<float> {
public:
  std::string type = "float";
};

template<>
class Type<double> {
public:
  std::string type = "double";
};

template<>
class Type<char> {
public:
  std::string type = "char";
};

template<>
class Type<bool> {
public:
  std::string type = "bool";
};
////////////////////////////////////////////

template<typename T>
std::string getTypeStr() {
  return std::string("any");
}

template<>
std::string getTypeStr<int>() {
  return std::string("int");
}

template<>
std::string getTypeStr<long>() {
  return std::string("long");
}

template<>
std::string getTypeStr<float>() {
  return std::string("float");
}

template<>
std::string getTypeStr<double>() {
  return std::string("double");
}

template<>
std::string getTypeStr<char>() {
  return std::string("char");
}

template<>
std::string getTypeStr<bool>() {
  return std::string("bool");
}

/*
template<class MType>
std::string getElemTypeStr(MType mat) {
  return getTypeStr<typename MType::ElemType>();
}*/




